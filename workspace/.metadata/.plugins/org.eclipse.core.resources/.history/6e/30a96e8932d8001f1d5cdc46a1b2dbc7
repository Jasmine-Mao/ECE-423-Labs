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
    uint32_t* vdma_reg_status;
    uint32_t num_bytes_read;

    rgbblock = buff_next();

    //read frame payload
    if(f_read(&fil, &frame_size, sizeof(uint32_t), &num_bytes_read) != 0) error_and_exit("COULD NOT GET FRAME SIZE");

    if(f_read(&fil, &frame_type, sizeof(uint32_t), &num_bytes_read) != 0) error_and_exit("COULD NOT GET FRAME TYPE");

    if(f_read(&fil, &Ysize, sizeof(uint32_t), &num_bytes_read) != 0) error_and_exit("COULD NOT READ Y SIZE");
    if(f_read(&fil, &Cbsize, sizeof(uint32_t), &num_bytes_read) != 0) error_and_exit("COULD NOT READ CB SIZE");
    if(f_read(&fil, Ybitstream, (frame_size - 4 * sizeof(uint32_t)), &num_bytes_read) != 0) error_and_exit("COULD NOT READ YBITSTREAM");

    Cbbitstream = Ybitstream + Ysize;
    Crbitstream = Cbbitstream + Cbsize;

    lossless_decode(hYb_size*wYb_size, Ybitstream, YDCAC, Yquant, frame_type);
    lossless_decode(hCb_size*wCb_size, Cbbitstream, CbDCAC, Cquant, frame_type);
    lossless_decode(hCb_size*wCb_size, Crbitstream, CrDCAC, Cquant, frame_type);
    
    //fdct
    for(int b = 0; b < hYb_size*wYb_size; b++) idct(YDCAC[b], Yblock[b]);
    for(int b = 0; b < hCb_size*wCb_size; b++) idct(CbDCAC[b], Cbblock[b]);
    for(int b = 0; b < hCb_size*wCb_size; b++) idct(CrDCAC[b], Crblock[b]);

    //ybcbr to rgb conversion
    for(int b = 0; b < hCb_size*wCb_size; b++)
        ycbcr_to_rgb(b/wCb_size*8, b%wCb_size*8, w_size, Yblock[b], Cbblock[b], Crblock[b], rgbblock);

    vdma_reg_status = buff_reg();
    vdma_out();
    DEBUG_PRINT("\nDecoder done.\n\n\n")
    //close down
    //fclose(file_in);
    //f_close(&fil);
//    vdma_close();
    //free(rgbblock);
    // free(Yblock);
    // free(Cbblock);
    // free(Crblock);
    // free(YDCAC);
    // free(CbDCAC);
    // free(CrDCAC);
    // free(Ybitstream);
    // these frees need to be in the cycle vide function
}
