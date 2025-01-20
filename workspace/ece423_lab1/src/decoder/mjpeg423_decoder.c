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
#include "../common/mjpeg423_types.h"
#include "mjpeg423_decoder.h"
#include "../common/util.h"
#include "ff.h"
#include "../ece423_vid_ctl/ece423_vid_ctl.h"

//extern FATFS fatfs;
//extern  FIL fil;

//declaration. Function implemented in libnsbmp
//void encode_bmp(rgb_pixel_t* rgbblock, uint32_t w_size, uint32_t h_size, const char* filename);

//main decoder function
//void mjpeg423_decode(const char* filename_in, const char* filenamebase_out)
void mjpeg423_decode(uint32_t frame_index)
{
    // initialize stuff
    rgb_pixel_t* rgbblock;
    if((rgbblock = malloc(current_video.w_size*current_video.h_size*sizeof(rgb_pixel_t)))==NULL) error_and_exit("cannot allocate rgbblock");
    uint32_t* vdma_reg_status;
    uint32_t num_bytes_read;

    rgbblock = buff_next();

    //read frame payload
    if(f_read(&fil, &current_video.frame_size, sizeof(uint32_t), &num_bytes_read) != 0) error_and_exit("COULD NOT GET FRAME SIZE");

    if(f_read(&fil, &current_video.frame_type, sizeof(uint32_t), &num_bytes_read) != 0) error_and_exit("COULD NOT GET FRAME TYPE");

    if(f_read(&fil, &current_video.Ysize, sizeof(uint32_t), &num_bytes_read) != 0) error_and_exit("COULD NOT READ Y SIZE");
    if(f_read(&fil, &current_video.Cbsize, sizeof(uint32_t), &num_bytes_read) != 0) error_and_exit("COULD NOT READ CB SIZE");
    if(f_read(&fil, current_video.Ybitstream, (current_video.frame_size - 4 * sizeof(uint32_t)), &num_bytes_read) != 0) error_and_exit("COULD NOT READ YBITSTREAM");

    current_video.Cbbitstream = current_video.Ybitstream + current_video.Ysize;
    current_video.Crbitstream = current_video.Cbbitstream + current_video.Cbsize;

    lossless_decode(current_video.hYb_size*current_video.wYb_size, current_video.Ybitstream, current_video.YDCAC, Yquant, current_video.frame_type);
    lossless_decode(current_video.hCb_size*current_video.wCb_size, current_video.Cbbitstream, current_video.CbDCAC, Cquant, current_video.frame_type);
    lossless_decode(current_video.hCb_size*current_video.wCb_size, current_video.Crbitstream, current_video.CrDCAC, Cquant, current_video.frame_type);
    
    //fdct
    for(int b = 0; b < current_video.hYb_size*current_video.wYb_size; b++) idct(current_video.YDCAC[b], current_video.Yblock[b]);
    for(int b = 0; b < current_video.hCb_size*current_video.wCb_size; b++) idct(current_video.CbDCAC[b], current_video.Cbblock[b]);
    for(int b = 0; b < current_video.hCb_size*current_video.wCb_size; b++) idct(current_video.CrDCAC[b], current_video.Crblock[b]);
    


    //ybcbr to rgb conversion
    for(int b = 0; b < current_video.hCb_size*current_video.wCb_size; b++)
        ycbcr_to_rgb(b/current_video.wCb_size*8, b%current_video.wCb_size*8, current_video.w_size, current_video.Yblock[b], current_video.Cbblock[b], current_video.Crblock[b], rgbblock);


    vdma_reg_status = buff_reg();
    vdma_out();
    DEBUG_PRINT("\nDecoder done.\n\n\n")
    //close down
    //fclose(file_in);
    //f_close(&fil);
//    vdma_close();
    free(rgbblock);
    // free(Yblock);
    // free(Cbblock);
    // free(Crblock);
    // free(YDCAC);
    // free(CbDCAC);
    // free(CrDCAC);
    // free(Ybitstream);
    // these frees need to be in the cycle vide function
}
