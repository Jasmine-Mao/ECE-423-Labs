//
//  mjpeg423_decoder.c
//  mjpeg423app
//
//  Created by Rodolfo Pellizzoni on 12/24/13.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>
#include "../common/mjpeg423_types.h"
#include "mjpeg423_decoder.h"
#include "../common/util.h"

#include "xtime_l.h"
#include "ff.h"
#include "../ece423_vid_ctl/ece423_vid_ctl.h"

#define SEEK_FRAMES 120
#define MAX(i, j) (((i) > (j)) ? (i) : (j))
#define MIN(i, j) (((i) < (j)) ? (i) : (j))

// FatFs info
static FIL file_in;
static FRESULT f_status;
static uint32_t num_bytes_read;

//header and payload info
static uint32_t num_frames, w_size, h_size, num_iframes, payload_size;
static uint32_t Ysize, Cbsize, frame_size, frame_type;

//trailer structure
static iframe_trailer_t* trailer;

// frame index of currently playing video
static uint32_t frame_index = 0;

//main data structures. See lab manual for explanation
static int hCb_size, wCb_size, hYb_size, wYb_size;
static rgb_pixel_t* rgbblock;
static color_block_t* Yblock;
static color_block_t* Cbblock;
static color_block_t* Crblock;
static dct_block_t* YDCAC;
static dct_block_t* CbDCAC;
static dct_block_t* CrDCAC;
static uint8_t* Ybitstream;
static uint8_t* Cbbitstream;
static uint8_t* Crbitstream;


uint32_t y_memory, cr_memory, cb_memory, idct_memory, rgb_memory;
XTime start, end;


//main decoder function
void decode_entire_video(const char* filename_in)
{
    //file streams
    f_status = f_open(&file_in, filename_in, FA_READ);
    if(f_status != FR_OK) error_and_exit_error_code("cannot open input file", (uint32_t)f_status);

    //read header
    f_status = f_read(&file_in, (void*)&num_frames, sizeof(uint32_t), (UINT*)&num_bytes_read);
    if(f_status != FR_OK) error_and_exit_error_code("cannot read input file", (uint32_t)f_status);
    DEBUG_PRINT_ARG("Decoder start. Num frames #%lu\n", num_frames)

    f_status = f_read(&file_in, (void*)&w_size, sizeof(uint32_t), (UINT*)&num_bytes_read);
    if(f_status != FR_OK) error_and_exit_error_code("cannot read input file", (uint32_t)f_status);
    DEBUG_PRINT_ARG("Width %lu\n", w_size)

    f_status = f_read(&file_in, (void*)&h_size, sizeof(uint32_t), (UINT*)&num_bytes_read);
    if(f_status != FR_OK) error_and_exit_error_code("cannot read input file", (uint32_t)f_status);
    DEBUG_PRINT_ARG("Height %lu\n", h_size)

    f_status = f_read(&file_in, (void*)&num_iframes, sizeof(uint32_t), (UINT*)&num_bytes_read);
    if(f_status != FR_OK) error_and_exit_error_code("cannot read input file", (uint32_t)f_status);
    DEBUG_PRINT_ARG("Num i frames %lu\n", num_iframes)

    f_status = f_read(&file_in, (void*)&payload_size, sizeof(uint32_t), (UINT*)&num_bytes_read);
    if(f_status != FR_OK) error_and_exit_error_code("cannot read input file", (uint32_t)f_status);
    DEBUG_PRINT_ARG("Payload Size %lu\n", payload_size)

    hCb_size = h_size/8;           //number of chrominance blocks
    wCb_size = w_size/8;
    hYb_size = h_size/8;           //number of luminance blocks. Same as chrominance in the sample app
    wYb_size = w_size/8;

    //trailer structure
    trailer = malloc(sizeof(iframe_trailer_t)*num_iframes);

    //main data structures. See lab manual for explanation
    if((rgbblock = malloc(w_size*h_size*sizeof(rgb_pixel_t)))==NULL) error_and_exit("cannot allocate rgbblock");
    if((Yblock = malloc(hYb_size * wYb_size * 64))==NULL) error_and_exit("cannot allocate Yblock");
    if((Cbblock = malloc(hCb_size * wCb_size * 64))==NULL) error_and_exit("cannot allocate Cbblock");
    if((Crblock = malloc(hCb_size * wCb_size * 64))==NULL) error_and_exit("cannot allocate Crblock");;
    if((YDCAC = malloc(hYb_size * wYb_size * 64 * sizeof(DCTELEM)))==NULL) error_and_exit("cannot allocate YDCAC");
    if((CbDCAC = malloc(hCb_size * wCb_size * 64 * sizeof(DCTELEM)))==NULL) error_and_exit("cannot allocate CbDCAC");
    if((CrDCAC = malloc(hCb_size * wCb_size * 64 * sizeof(DCTELEM)))==NULL) error_and_exit("cannot allocate CrDCAC");
    //Ybitstream is assigned a size sufficient to hold all bistreams
    //the bitstream is then read from the file into Ybitstream
    //the remaining pointers simply point to the beginning of the Cb and Cr streams within Ybitstream
    if((Ybitstream = malloc(hYb_size * wYb_size * 64 * sizeof(DCTELEM) + 2 * hCb_size * wCb_size * 64 * sizeof(DCTELEM)))==NULL) error_and_exit("cannot allocate bitstream");

    //read trailer: set file to beginning of trailer
    f_status = f_lseek(&file_in, 5 * sizeof(uint32_t) + payload_size);
    if(f_status != FR_OK) error_and_exit_error_code("cannot seek into file", (uint32_t)f_status);

    for(int count = 0; count < num_iframes; count++){
        f_status = f_read(&file_in, (void*)&(trailer[count].frame_index), sizeof(uint32_t), (UINT*)&num_bytes_read);
        if(f_status != FR_OK) error_and_exit_error_code("cannot read input file", (uint32_t)f_status);
        DEBUG_PRINT_ARG("I frame index %lu, ", trailer[count].frame_index)
        f_status = f_read(&file_in, (void*)&(trailer[count].frame_position), sizeof(uint32_t), (UINT*)&num_bytes_read);
        if(f_status != FR_OK) error_and_exit_error_code("cannot read input file", (uint32_t)f_status);
        DEBUG_PRINT_ARG("position %lu\n", trailer[count].frame_position)
    }
    //read trailer: set it back to beginning of payload
    f_status = f_lseek(&file_in, 5 * sizeof(uint32_t));
    if(f_status != FR_OK) error_and_exit_error_code("cannot seek into file. error code: %d", (uint32_t)f_status);

    //read and decode frames
    for(int frame_index = 0; frame_index < num_frames; frame_index++){
        DEBUG_PRINT_ARG("\nFrame #%d\n",frame_index)

		rgbblock = buff_next();

        //read frame payload
		f_status = f_read(&file_in, (void*)&frame_size, sizeof(uint32_t), (UINT*)&num_bytes_read);
		if(f_status != FR_OK) error_and_exit_error_code("cannot read input file", (uint32_t)f_status);
        DEBUG_PRINT_ARG("Frame_size %lu\n",frame_size)

		f_status = f_read(&file_in, (void*)&frame_type, sizeof(uint32_t), (UINT*)&num_bytes_read);
		if(f_status != FR_OK) error_and_exit_error_code("cannot read input file", (uint32_t)f_status);
        DEBUG_PRINT_ARG("Frame_type %lu\n",frame_type)

		f_status = f_read(&file_in, (void*)&Ysize, sizeof(uint32_t), (UINT*)&num_bytes_read);
		if(f_status != FR_OK) error_and_exit_error_code("cannot read input file", (uint32_t)f_status);

		f_status = f_read(&file_in, (void*)&Cbsize, sizeof(uint32_t), (UINT*)&num_bytes_read);
		if(f_status != FR_OK) error_and_exit_error_code("cannot read input file", (uint32_t)f_status);

		f_status = f_read(&file_in, (void*)Ybitstream, frame_size - 4 * sizeof(uint32_t), (UINT*)&num_bytes_read);
		if(f_status != FR_OK) error_and_exit_error_code("cannot read input file", (uint32_t)f_status);

        //set the Cb and Cr bitstreams to point to the right position
        Cbbitstream = Ybitstream + Ysize;
        Crbitstream = Cbbitstream + Cbsize;

        //lossless decoding
        lossless_decode(hYb_size*wYb_size, Ybitstream, YDCAC, Yquant, frame_type);
        lossless_decode(hCb_size*wCb_size, Cbbitstream, CbDCAC, Cquant, frame_type);
        lossless_decode(hCb_size*wCb_size, Crbitstream, CrDCAC, Cquant, frame_type);

        //fdct
        for(int b = 0; b < hYb_size*wYb_size; b++) idct(YDCAC[b], Yblock[b]);
        for(int b = 0; b < hCb_size*wCb_size; b++) idct(CbDCAC[b], Cbblock[b]);
        for(int b = 0; b < hCb_size*wCb_size; b++) idct(CrDCAC[b], Crblock[b]);

        //ybcbr to rgb conversion
        for(int b = 0; b < hCb_size*wCb_size; b++)
        {
            ycbcr_to_rgb(b/wCb_size*8, b%wCb_size*8, w_size, Yblock[b], Cbblock[b], Crblock[b], rgbblock);
        }

        buff_reg();//set buffer to ready

        vdma_out();
    } //end frame iteration

    DEBUG_PRINT("\nDecoder done.\n\n\n")

    //close down
    f_close(&file_in);
    free(rgbblock);
    free(Yblock);
    free(Cbblock);
    free(Crblock);
    free(YDCAC);
    free(CbDCAC);
    free(CrDCAC);
    free(Ybitstream);
}

// Assumes that f_mount is already called.
void load_video(const char* filename_in) //HM
{
    printf("Decoding %s to VDMA\n", filename_in);

    //file streams
    f_status = f_open(&file_in, filename_in, FA_READ);
    if(f_status != FR_OK) error_and_exit_error_code("cannot open input file", (uint32_t)f_status);

    //read header
    f_status = f_read(&file_in, (void*)&num_frames, sizeof(uint32_t), (UINT*)&num_bytes_read);
    if(f_status != FR_OK) error_and_exit_error_code("cannot read input file", (uint32_t)f_status);
    DEBUG_PRINT_ARG("Decoder start. Num frames #%lu\n", num_frames)

    f_status = f_read(&file_in, (void*)&w_size, sizeof(uint32_t), (UINT*)&num_bytes_read);
    if(f_status != FR_OK) error_and_exit_error_code("cannot read input file", (uint32_t)f_status);
    DEBUG_PRINT_ARG("Width %lu\n", w_size)

    f_status = f_read(&file_in, (void*)&h_size, sizeof(uint32_t), (UINT*)&num_bytes_read);
    if(f_status != FR_OK) error_and_exit_error_code("cannot read input file", (uint32_t)f_status);
    DEBUG_PRINT_ARG("Height %lu\n", h_size)

    f_status = f_read(&file_in, (void*)&num_iframes, sizeof(uint32_t), (UINT*)&num_bytes_read);
    if(f_status != FR_OK) error_and_exit_error_code("cannot read input file", (uint32_t)f_status);
    DEBUG_PRINT_ARG("Num i frames %lu\n", num_iframes)

    f_status = f_read(&file_in, (void*)&payload_size, sizeof(uint32_t), (UINT*)&num_bytes_read);
    if(f_status != FR_OK) error_and_exit_error_code("cannot read input file", (uint32_t)f_status);
    DEBUG_PRINT_ARG("Payload Size %lu\n", payload_size)

    hCb_size = h_size/8;           //number of chrominance blocks
    wCb_size = w_size/8;
    hYb_size = h_size/8;           //number of luminance blocks. Same as chrominance in the sample app
    wYb_size = w_size/8;

    //trailer structure
    trailer = malloc(sizeof(iframe_trailer_t)*num_iframes);

    //main data structures. See lab manual for explanation
    if((rgbblock = malloc(w_size*h_size*sizeof(rgb_pixel_t)))==NULL) error_and_exit("cannot allocate rgbblock");
    if((Yblock = malloc(hYb_size * wYb_size * 64))==NULL) error_and_exit("cannot allocate Yblock");
    if((Cbblock = malloc(hCb_size * wCb_size * 64))==NULL) error_and_exit("cannot allocate Cbblock");
    if((Crblock = malloc(hCb_size * wCb_size * 64))==NULL) error_and_exit("cannot allocate Crblock");;
    if((YDCAC = malloc(hYb_size * wYb_size * 64 * sizeof(DCTELEM)))==NULL) error_and_exit("cannot allocate YDCAC");
    if((CbDCAC = malloc(hCb_size * wCb_size * 64 * sizeof(DCTELEM)))==NULL) error_and_exit("cannot allocate CbDCAC");
    if((CrDCAC = malloc(hCb_size * wCb_size * 64 * sizeof(DCTELEM)))==NULL) error_and_exit("cannot allocate CrDCAC");

    //Ybitstream is assigned a size sufficient to hold all bistreams
    //the bitstream is then read from the file into Ybitstream
    //the remaining pointers simply point to the beginning of the Cb and Cr streams within Ybitstream
    if((Ybitstream = malloc(hYb_size * wYb_size * 64 * sizeof(DCTELEM) + 2 * hCb_size * wCb_size * 64 * sizeof(DCTELEM)))==NULL) error_and_exit("cannot allocate bitstream");

    //read trailer: set file to beginning of trailer
    f_status = f_lseek(&file_in, 5 * sizeof(uint32_t) + payload_size);
    if(f_status != FR_OK) error_and_exit_error_code("cannot seek into file", (uint32_t)f_status);
    for(int count = 0; count < num_iframes; count++){
        f_status = f_read(&file_in, (void*)&(trailer[count].frame_index), sizeof(uint32_t), (UINT*)&num_bytes_read);
        if(f_status != FR_OK) error_and_exit_error_code("cannot read input file", (uint32_t)f_status);
        DEBUG_PRINT_ARG("I frame index %lu, ", trailer[count].frame_index)
        f_status = f_read(&file_in, (void*)&(trailer[count].frame_position), sizeof(uint32_t), (UINT*)&num_bytes_read);
        if(f_status != FR_OK) error_and_exit_error_code("cannot read input file", (uint32_t)f_status);
        DEBUG_PRINT_ARG("position %lu\n", trailer[count].frame_position)
    }
    //read trailer: set it back to beginning of payload
    f_status = f_lseek(&file_in, 5 * sizeof(uint32_t));
    if(f_status != FR_OK) error_and_exit_error_code("cannot seek into file. error code: %d", (uint32_t)f_status);
}


uint8_t decode_single_frame()
{
	//XTime_GetTime(&start);  // Capture time before the function call

	rgbblock = buff_next();	// this gets malloced
	if (rgbblock == NULL) return 1; // overflowing buffer
	if (frame_index >= num_frames) return 1; // reached end of video

    //read frame payload
	f_status = f_read(&file_in, (void*)&frame_size, sizeof(uint32_t), (UINT*)&num_bytes_read);
	f_status = f_read(&file_in, (void*)&frame_type, sizeof(uint32_t), (UINT*)&num_bytes_read);
	f_status = f_read(&file_in, (void*)&Ysize, sizeof(uint32_t), (UINT*)&num_bytes_read);
	f_status = f_read(&file_in, (void*)&Cbsize, sizeof(uint32_t), (UINT*)&num_bytes_read);
	f_status = f_read(&file_in, (void*)Ybitstream, frame_size - 4 * sizeof(uint32_t), (UINT*)&num_bytes_read);
    //set the Cb and Cr bitstreams to point to the right location
    Cbbitstream = Ybitstream + Ysize;
    Crbitstream = Cbbitstream + Cbsize;

    //XTime_GetTime(&start);
    lossless_decode(hYb_size*wYb_size, Ybitstream, YDCAC, Yquant, frame_type);
//	XTime_GetTime(&end);    // Capture time after the function call
//	printf("%d , %d, %llu\n",frame_index,frame_type, end - start + timer_delay);

    //XTime_GetTime(&start);
    lossless_decode(hCb_size*wCb_size, Cbbitstream, CbDCAC, Cquant, frame_type);
	//	XTime_GetTime(&end);    // Capture time after the function call
	//	printf("%d , %d, %llu\n",frame_index,frame_type, end - start + timer_delay);

    //XTime_GetTime(&start);
    lossless_decode(hCb_size*wCb_size, Crbitstream, CrDCAC, Cquant, frame_type);
//	XTime_GetTime(&end);    // Capture time after the function call
//	printf("%d , %d, %llu\n",frame_index,frame_type, end - start + timer_delay);

    //XTime_GetTime(&start);
    for(int b = 0; b < hYb_size*wYb_size; b++) idct(YDCAC[b], Yblock[b]);
	//XTime_GetTime(&end);    // Capture time after the function call
//	printf("%d , %d, %llu\n",frame_index,frame_type, end - start + timer_delay);

    for(int b = 0; b < hCb_size*wCb_size; b++) idct(CbDCAC[b], Cbblock[b]);
    for(int b = 0; b < hCb_size*wCb_size; b++) idct(CrDCAC[b], Crblock[b]);

    //ybcbr to rgb conversion
    //XTime_GetTime(&start);
    for(int b = 0; b < hCb_size*wCb_size; b++)
    {
        ycbcr_to_rgb(b/wCb_size*8, b%wCb_size*8, w_size, Yblock[b], Cbblock[b], Crblock[b], rgbblock);
    }
    //XTime_GetTime(&end);
	//printf("%d , %d, %llu\n",frame_index,frame_type, end - start + timer_delay);

//    XTime_GetTime(&start);
    buff_reg();
//    XTime_GetTime(&end);
//	printf("%d , %d, %llu\n",frame_index,frame_type, end - start + timer_delay);

    ///MEMORY STUFF////////////////////////////////////
//    uint32_t total_memory = 0;
//    // stuff from load memory
//    total_memory += sizeof(uint32_t)*9;							//header information, some frame information
//	total_memory += sizeof(iframe_trailer_t)*num_iframes;		//trailer
//
//	//ybistream -> this should be the one that's changing
//
//	total_memory += frame_size - 4 * sizeof(uint32_t);			//reading ybitstream
//	// malloced stuff
//    total_memory += w_size*h_size*sizeof(rgb_pixel_t);			//rbgblock
//    total_memory += hYb_size * wYb_size * 64;					//Yblock
//    total_memory += hCb_size * wCb_size * 64;					//Cbblock
//    total_memory += hCb_size * wCb_size * 64;					//Crblock
//    total_memory += hYb_size * wYb_size * 64 * sizeof(DCTELEM);	//YDCAC
//    total_memory += hCb_size * wCb_size * 64 * sizeof(DCTELEM); //CbDCAC
//    total_memory += hCb_size * wCb_size * 64 * sizeof(DCTELEM); //CrDCAC
//    total_memory += hYb_size * wYb_size * 64 * sizeof(DCTELEM) + 2 * hCb_size * wCb_size * 64 * sizeof(DCTELEM); //Ybitstream
    // END MEMORY STUFF////////////////////////////////

	//XTime_GetTime(&end);    // Capture time after the function call
	//printf("%d , %d, %llu\n",frame_index,frame_type, end - start + timer_delay);
    if(vdma_out() == 0)
    {
    	printf("VDMA failed");
    }
    frame_index++;
    printf("%d, %d\n", frame_type, total_memory);

    return 0;
}

uint8_t is_last_frame()
{
	return frame_index >= num_frames; //removed equals
}

void release_video()
{
	//close down the video & free all the allocated memory
	f_close(&file_in);
	free(trailer);
	free(rgbblock);
	free(Yblock);
	free(Cbblock);
	free(Crblock);
	free(YDCAC);
	free(CbDCAC);
	free(CrDCAC);
	free(Ybitstream);
	frame_index = 0;


//	underflow_count = 0;
//	memset(&sdReadTime, 0, sizeof(performance_t));
//	memset(&yTime, 0, sizeof(performance_t));
//	memset(&crTime, 0, sizeof(performance_t));
//	memset(&cbTime, 0, sizeof(performance_t));
//
//	memset(sdReadTime.min_us, DBL_MAX, 2*sizeof(double));
//	memset(yTime.min_us, DBL_MAX, 2*sizeof(double));
//	memset(crTime.min_us, DBL_MAX, 2*sizeof(double));
//	memset(cbTime.min_us, DBL_MAX, 2*sizeof(double));
//
//	idctTime_sum = 0;
//	ycbrToRgbTime_sum = 0;
//	buffRegTime_sum = 0;
//
//	memset(&frameSize, 0, sizeof(performance_m));
//	memset(frameSize.min, DBL_MAX, 2*sizeof(double));
//	yMemSum = 0;
//	cbMemSum = 0;
//	crMemSum = 0;
//    idctMemSum = 0;
//    rgbBlockMemSum = 0;;

	printf("Freed memory for file\n");
}

uint8_t forward_button() //returns 1 if valid i_frame found, 0 if not
{
	if(frame_index + SEEK_FRAMES > num_frames)
	{
		printf("Current frame %d is too close to the end, pausing video\n",frame_index);
		return 0;
	}

	for (int count = num_iframes - 1; count >=0; count--)
	{
		if (((int)trailer[count].frame_index - (int)frame_index) <= SEEK_FRAMES)
		{
		    //set file to location of I frame
			printf("Current frame %d, seeking to %d\n",frame_index,trailer[count + 1].frame_index);
		    f_status = f_lseek(&file_in, trailer[count + 1].frame_position);
		    if(f_status != FR_OK) error_and_exit("cannot seek into file");
		    frame_index = trailer[count + 1].frame_index;
		    return 1;
		}
	}

	return 0;
}

uint8_t backward_button()
{
	//check if less than 120 frames from the start
	if(frame_index <= SEEK_FRAMES)
	{
		printf("Current frame %d is too close to beginning, setting to frame 0\n",frame_index);
		return 0;
	}

	for (int count = 0; count < num_iframes; count++)
	{
		if (((int)frame_index - (int)trailer[count].frame_index) <= SEEK_FRAMES)
		{
		    //set file to location of I frame
			printf("Current frame %d, seeking to %d\n",frame_index,trailer[count-1].frame_index);
		    f_status = f_lseek(&file_in, trailer[count-1].frame_position);
		    if(f_status != FR_OK) error_and_exit_error_code("cannot seek into file", (uint32_t)f_status);
		    frame_index = trailer[count-1].frame_index;
		    return 1;
		}
	}

	return 0;
}

void reset_video() //sets the video back to first frame
{
    f_status = f_lseek(&file_in, 5 * sizeof(uint32_t));
    if(f_status != FR_OK) error_and_exit_error_code("cannot seek into file. error code: %d", (uint32_t)f_status);
    frame_index = 0;
	return;
}


double calculate_fps(double time_ellapsed)
{
	return (num_frames/time_ellapsed);
}



