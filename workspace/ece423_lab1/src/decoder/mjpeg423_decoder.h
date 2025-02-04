//
//  mjpeg423_decoder.h
//  mjpeg423app
//
//  Created by Rodolfo Pellizzoni on 12/24/13.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#ifndef mjpeg423app_mjpeg423_decoder_h
#define mjpeg423app_mjpeg423_decoder_h

#include "../common/mjpeg423_types.h"

typedef struct {
    double max_us[2];
    double min_us[2];
    double sum_us[2];
} performance_t;

typedef struct {
    uint32_t max[2];
    uint32_t min[2];
    uint32_t sum[2];
} performance_m;


#define TIMER_FPS 12

void decode_entire_video(const char* filename_in);
void load_video(const char* filename_in);
uint8_t decode_single_frame();
uint8_t is_last_frame();
void release_video();
void mjpeg423_decode_to_vdma_print_stats();
uint8_t forward_button();
uint8_t backward_button();
void reset_video();
void set_underflow_count();
void ycbcr_to_rgb(int h, int w, uint32_t w_size, pcolor_block_t Y, pcolor_block_t Cb, pcolor_block_t Cr, rgb_pixel_t* rgbblock);
void idct(dct_block_t DCAC, color_block_t block);
void lossless_decode(int num_blocks, void* bitstream, dct_block_t* DCACq, dct_block_t quant, BOOL P);
double calculate_fps(double time_ellapsed);

extern uint32_t timer_delay;
#endif
