#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../common/mjpeg423_types.h"
#include "mjpeg423_decoder.h"
#include "../common/util.h"
#include "ff.h"
#include "../ece423_vid_ctl/ece423_vid_ctl.h"
#include "video_control.h"

static FATFS fatfs;
static FIL fil;

video_info_t load_video(const TCHAR* file_name)
{
	video_info_t video_info;

    //uint32_t num_frames, w_size, h_size, num_iframes, payload_size;
    //uint32_t Ysize, Cbsize, frame_size, frame_type;

    //open file
    status = f_open(&fil, file_name, FA_READ); //change to filename_in to generalize later on
    uint32_t num_bytes_read;

    //read header
    if(f_read(&fil, &video_info.num_frames, sizeof(uint32_t), &num_bytes_read) != 0) error_and_exit("FAILED TO READ NUMBER OF FRAMES");
    if(f_read(&fil, &video_info.w_size, sizeof(uint32_t), &num_bytes_read) != 0) error_and_exit("FAILED TO READ WIDTH");
    if(f_read(&fil, &video_info.h_size, sizeof(uint32_t), &num_bytes_read) != 0) error_and_exit("FAILED TO READ HEIGHT");
    if(f_read(&fil, &video_info.num_iframes, sizeof(uint32_t), &num_bytes_read) != 0) error_and_exit("FAILED TO READ NUM I-FRAMES");
    if(f_read(&fil, &video_info.payload_size, sizeof(uint32_t), &num_bytes_read) != 0) error_and_exit("FAILED TO READ PAYLOAD SIZE");

    //read trailer
    video_info.hCb_size = video_info.h_size/8;           //number of chrominance blocks
    video_info.wCb_size = video_info.w_size/8;
    video_info.hYb_size = video_info.h_size/8;           //number of luminance blocks. Same as chrominance in the sample app
    video_info.wYb_size = video_info.w_size/8;

    //trailer structure
    video_info.trailer = malloc(sizeof(iframe_trailer_t)*video_info.num_iframes);

    //main data structures. See lab manual for explanation
    //gb_pixel_t* rgbblock;
    // rgbblock = buff_next(); this is probably wrong
    //if((rgbblock = malloc(w_size*h_size*sizeof(rgb_pixel_t)))==NULL) error_and_exit("cannot allocate rgbblock");
    //color_block_t* Yblock;
    if((video_info.Yblock = malloc(video_info.hYb_size * video_info.wYb_size * 64))==NULL) error_and_exit("cannot allocate Yblock");
    //color_block_t* Cbblock;
    if((video_info.Cbblock = malloc(video_info.hCb_size * video_info.wCb_size * 64))==NULL) error_and_exit("cannot allocate Cbblock");
    //color_block_t* Crblock;
    if((video_info.Crblock = malloc(video_info.hCb_size * video_info.wCb_size * 64))==NULL) error_and_exit("cannot allocate Crblock");;
    //dct_block_t* YDCAC;
    if((video_info.YDCAC = malloc(video_info.hYb_size * video_info.wYb_size * 64 * sizeof(DCTELEM)))==NULL) error_and_exit("cannot allocate YDCAC");
    //dct_block_t* CbDCAC;
    if((video_info.CbDCAC = malloc(video_info.hCb_size * video_info.wCb_size * 64 * sizeof(DCTELEM)))==NULL) error_and_exit("cannot allocate CbDCAC");
    //dct_block_t* CrDCAC;
    if((video_info.CrDCAC = malloc(video_info.hCb_size * video_info.wCb_size * 64 * sizeof(DCTELEM)))==NULL) error_and_exit("cannot allocate CrDCAC");
    //Ybitstream is assigned a size sufficient to hold all bistreams
    //the bitstream is then read from the file into Ybitstream
    //the remaining pointers simply point to the beginning of the Cb and Cr streams within Ybitstream
    //uint8_t* Ybitstream;
    if((video_info.Ybitstream = malloc(video_info.hYb_size * video_info.wYb_size * 64 * sizeof(DCTELEM) + 2 * video_info.hCb_size * video_info.wCb_size * 64 * sizeof(DCTELEM)))==NULL) error_and_exit("cannot allocate bitstream");

    //read trailer. Note: the trailer information is not used in the sample decoder app
    //set file to beginning of trailer
    //if(fseek(file_in, 5 * sizeof(uint32_t) + payload_size, SEEK_SET) != 0) error_and_exit("cannot seek into file");
    if(f_lseek(&fil, 5 * sizeof(uint32_t) + video_info.payload_size) != 0) error_and_exit("ERROR GETTING TO TRAILER");
    for(int count = 0; count < video_info.num_iframes; count++){
    	if(f_read(&fil, &(video_info.trailer[count].frame_index), sizeof(uint32_t), &num_bytes_read) != 0) error_and_exit("FAILED TO GET FRAME INDEX");
//        if(fread(&(trailer[count].frame_index), sizeof(uint32_t), 1, file_in) != 1) error_and_exit("cannot read input file");

    	if(f_read(&fil, &(video_info.trailer[count].frame_position), sizeof(uint32_t), &num_bytes_read) != 0) error_and_exit ("FAILED TO GET FRAME POSITION");
//        if(fread(&(trailer[count].frame_position), sizeof(uint32_t), 1, file_in) != 1) error_and_exit("cannot read input file");
        //DEBUG_PRINT_ARG("I frame index %u, ", trailer[count].frame_index)
        //DEBUG_PRINT_ARG("position %u\n", trailer[count].frame_position)
    }
    //set it back to beginning of payload
//    if(fseek(file_in,5 * sizeof(uint32_t),SEEK_SET) != 0) error_and_exit("cannot seek into file");
    if(f_lseek(&fil, 5 * sizeof(uint32_t)) != 0) error_and_exit("COULD NOT SEEK BACK TO BEGINNING");

    return video_info;
}

void display_next_frame(uint32_t* frame_index){
	// basically just runs decoder

}

void pause_button(uint8_t* not_paused_ptr){
	// when pressed, this should suspend the
	*not_paused_ptr = !(*not_paused_ptr);
}
