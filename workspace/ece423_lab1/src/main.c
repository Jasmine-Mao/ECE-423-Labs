/******************************************************************************
*
* Copyright (C) 2009 - 2014 Xilinx, Inc.  All rights reserved.
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* Use of the Software is limited solely to applications:
* (a) running on a Xilinx device, or
* (b) that interact with a Xilinx device through a bus or interconnect.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
* XILINX  BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
* WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF
* OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*
* Except as contained in this notice, the name of the Xilinx shall not be used
* in advertising or otherwise to promote the sale, use or other dealings in
* this Software without prior written authorization from Xilinx.
*
******************************************************************************/

/*
 * helloworld.c: simple test application
 *
 * This application configures UART 16550 to baud rate 9600.
 * PS7 UART (Zynq) is not initialized by this application, since
 * bootrom/bsp configures it to baud rate 115200
 *
 * ------------------------------------------------
 * | UART TYPE   BAUD RATE                        |
 * ------------------------------------------------
 *   uartns550   9600
 *   uartlite    Configurable only in HW design
 *   ps7_uart    115200 (configured by bootrom/bsp)
 */

#include <stdio.h>
#include "platform.h"
#include "xil_printf.h"
#include "xtime_l.h"

#include "ff.h"
#include "timer_gpio.h"
#include "xparameters.h"
#include "xil_types.h"
#include "common/util.h"
#include "decoder/mjpeg423_decoder.h"
#include "ece423_vid_ctl/ece423_vid_ctl.h"

#define FRAME_BUFF_SIZE 2
#define TIMER_1S 325000000 //1 second
#define ROOT "3:/"
#define MAX_FILE_NUM 3
#define MAX_FILE_NAME_LENGTH 20

volatile int8_t pin_value = -1;
volatile int8_t is_paused = 0;
volatile int8_t timer_triggered = 0;

static int8_t file_counter = 0;
static char* file_name[MAX_FILE_NUM][MAX_FILE_NAME_LENGTH];

static FATFS fatfs;
static FRESULT res;

uint32_t timer_delay;

void scan_files()
{
	DIR video_dir;
	static FILINFO fno;

	res = f_opendir(&video_dir, ROOT); // Open the root directory
    if(res != FR_OK) error_and_exit_error_code("cannot open SD card partition 3 root directory", (uint32_t)res);
	int i = 0;
    for (;;)
	{
		res = f_readdir(&video_dir, &fno); // Read a directory item
		if (res != FR_OK) error_and_exit_error_code("cannot read directory item", (uint32_t)res);
		if (fno.fname[0] == 0) break;
		if (!(fno.fattrib & AM_DIR)) { // It is a directory
			snprintf(file_name[i], sizeof(file_name[i]), "%s/%s", "3:/", fno.fname);
			printf("%s\n", file_name[i]);
			i++;
			if (i >= MAX_FILE_NUM) break;
		}
	}

	f_closedir(&video_dir);
}

void GpioHandler(void *CallBackRef, u32 Bank, u32 Status)
{
	if (pin_value == -1)
	{
		pin_value = read_pin();
	}
}
void TimerHandler(void*)
{
	timer_triggered = 1;
}

int main()
{
	// initialization
    init_platform();
    vdma_init(1280, 720, FRAME_BUFF_SIZE);
    timer_gpio_init(TimerHandler, GpioHandler);

    res = f_mount(&fatfs, ROOT, 1); // mount SD card
    if(res != FR_OK) error_and_exit("cannot mount SD card");


    scan_files();
    load_video(file_name[file_counter]);

    XTime start, end;
    XTime_GetTime(&start);  // Capture time before the function call
    XTime_GetTime(&end);    // Capture time after the function call
    timer_delay = end - start;

    // decode single frame then pause video
    is_paused = 1;

    decode_single_frame();


    //vdma_out();

    timer_start(TIMER_1S/TIMER_FPS);    // start timer
    //pin_value = -1; // reset pin value

    // Only uncomment when demonstrating no periodic timer.

    if(0)
    {
		XTime_GetTime(&start);
		decode_entire_video(file_name[1]);
		XTime_GetTime(&end);
		double time_ellapsed = (double)(end - start)/((double)325000000);
		printf("Entire video time:%f  fps:%f\n",time_ellapsed,calculate_fps(time_ellapsed));
    }

    // infinite loop
    for(;;)
    {
    	if (!is_paused && timer_triggered)
    	{ // decodes a single frame to the VDMA
    		//timer here
            decode_single_frame();
            if (is_last_frame())
			{
            	is_paused = 1;
			}
            timer_triggered = 0;
    	}

        if (pin_value != -1)
        {
            printf("button %d has been pressed!\n", pin_value);
        	if (pin_value == 0)
        	{ // switch to next video
        		is_paused = 1;
        		release_video();
        		file_counter = (file_counter + 1) % MAX_FILE_NUM;
        	    load_video(file_name[file_counter]);
        	    decode_single_frame();
        	}
        	else if (pin_value == 1)
        	{ // toggle the pause button
        		is_paused = !is_paused;
        		if (is_paused)
        			printf("Video Paused\n");
        		else
        			printf("Video Play\n");
        	}
        	else if (pin_value == 2)
        	{ // toggle the forward button and move roughly 120 frames ahead
        		if (!forward_button())
        		{
        			is_paused = 1;
        		}
        		else
        		{
        			//play the frame skipped to
        			decode_single_frame();
        			//vdma_out();
        		}
        	}
        	else if (pin_value == 3)
        	{ // seek ~120 frames backward
        		if (!backward_button()) //returns 0 if there isn't a valid I frame (too close to the beginning)
        		{
        			reset_video(); //seek back to first frame
        		}
        		decode_single_frame();
        		//vdma_out();
        	}
        	pin_value = -1;
        }
    }

    // close
    release_video();
	f_unmount(ROOT);
    vdma_close();
    cleanup_platform();
    return 0;
}
