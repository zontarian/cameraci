#include "cameraci.h"
#include <sysexits.h>
#include <signal.h>
#include <time.h>

/* utils */
double time_in_millis(){
    struct timeval  tv;
    gettimeofday(&tv, NULL);

    double time_in_mill =  (tv.tv_sec) * 1000 + (tv.tv_usec) / 1000 ;
    return time_in_mill;
}

static volatile int keep_running = 1;

void intHandler(int dummy) {
    printf("Camera capture Interrupted. Exiting\n");
    keep_running = 0;
}

/* main
 * Does an infinite loop
 */
int main(int argc, const char **argv){

    RASPISTILLYUV_STATE *state=raspistill_create_status();
    printf("here\n");
    MMAL_STATUS_T status = MMAL_SUCCESS;
    int exit_code = EX_OK;

    int W=400;
    int H=280;

    //then it gets 416 x 288
    state->width = W;
    state->height = H;
    state->useRGB = 1;
    state->onlyLuma=0; //rgb and luma, mutually exclusive
    state->verbose = 0;

    exit_code = raspistill_init(state);
    printf("RaspiStill initted\n");

    if(exit_code==0){

        int _w=0;
        int _h=0;
        rapistill_get_actual_capture_size(state, &_w, &_h);
        printf( "camera_still_port dimensions as reported from camera port: %dx%d\n", _w, _h);
        W=_w;
        H=_h;

        char *buffer=(char*)malloc(W*H*3);
        printf("buffer 0 %02x\n",buffer[0]);

        // main loop
        double start = time_in_millis();
        double sample_start = start;
        int count = 0;
        int i=0;
        //for(i=0;i<num_frames;i++){
        signal(SIGINT, intHandler);
        while(keep_running){

            int status=raspistill_capture(state, buffer);
            if(status!=0){
                printf("Error from capture %d\n", status);
            }

            double elapsed = time_in_millis();
            if(elapsed - sample_start > 5000){
                printf("%d frames in %.1f ms: %f fps\n",i,(elapsed-sample_start),(float)count/(elapsed-sample_start)*1000);
                sample_start = elapsed;
                count = 0;
            }
            count ++;
            i ++;
            // to do just one pass, uncomment this
            // keep_running = 0;
        }
        double end = time_in_millis();
        printf("end sending bits to SPI: %d frames in %.1f ms: %f fps\n",i,(end-start),(float)i/(end-start)*1000);

        int status=raspistill_capture(state, buffer);
        printf("buffer 0 %02x\n",buffer[0]);


        // tear down camera
        printf( "camera teardown\n");
        raspistill_tear_down(state,status);
        printf( "camera teardown done. Exiting\n");
    }

}