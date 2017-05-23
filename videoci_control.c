//
// Created by Walter Gamba on 09/04/17.
//
#include "videoci.h"

void main(int argc, const char **argv){
    //test
    printf("\nTesting videoci module\n");
    RASPIVIDYUV_STATE *state=raspivideo_create_status();

    MMAL_STATUS_T status = MMAL_SUCCESS;
    int exit_code = 0;

    int W=400;
    int H=280;

    //then it gets 416 x 288
    state->width = W;
    state->height = H;
    state->useRGB = 1;
    state->onlyLuma=0; //rgb and luma, mutually exclusive
    state->verbose = 1;

    exit_code = raspivideo_init(state);
    if(exit_code != 0){
        printf("Error initializing raspivideo. Aborting");
        exit(exit_code);
    }

    ////
    int _w=0;
    int _h=0;
    raspivideo_get_actual_capture_size(state, &_w, &_h);
    printf("camera_still_port dimensions as reported from camera port: %dx%d\n", _w, _h);
    char *buffer = (char *) malloc(_w * _h * 3);
    status = raspivideo_start_capture(state, buffer);
    if(status == 0) {
        //catpure for 3 secs
        vcos_sleep(3000);
        //this is useless at the moment
        status = raspivideo_end_capture(state);
    }

    //now close
    raspivideo_tear_down(state, status);
}