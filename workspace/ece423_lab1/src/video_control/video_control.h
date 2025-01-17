#ifndef video_control_h
#define video_control_h

#include "../common/mjpeg423_types.h"

video_info_t load_video(const TCHAR* file_name);
void display_next_frame(uint32_t* frame_index);
void pause_button(BOOL* not_paused_ptr);

typedef struct {
    uint32_t num_frames;
    uint32_t w_size;
    uint32_t h_size;
    uint32_t num_iframes;
    uint32_t payload_size;
    uint32_t Ysize;
    uint32_t Cbsize;
    uint32_t frame_size;
    uint32_t frame_type;
    int hCb_size;
    int wCb_size;
    int hYb_size;
    int wYb_size;
    iframe_trailer_t* trailer;
    color_block_t* Yblock;
    color_block_t* Cbblock;
    color_block_t* Crblock;
    dct_block_t* YDCAC;
    dct_block_t* CbDCAC;
    dct_block_t* CrDCAC;
    uint8_t* Ybitstream;
    uint8_t* Cbbitstream;
    uint8_t* Crbitstream;
} video_info_t;

#endif
