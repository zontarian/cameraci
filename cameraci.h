//
// Created by Walter Gamba on 31/03/17.
//

#ifndef BIKAMERA_CAMERACI_H
#define BIKAMERA_CAMERACI_H


#include "interface/mmal/mmal.h"
#include "interface/mmal/mmal_logging.h"
#include "interface/mmal/mmal_buffer.h"
#include "interface/mmal/util/mmal_util.h"
#include "interface/mmal/util/mmal_util_params.h"
#include "interface/mmal/util/mmal_default_components.h"
#include "interface/mmal/util/mmal_connection.h"
#include "interface/mmal/mmal_parameters_camera.h"


#include "RaspiCamControl.h"
#include "RaspiPreview.h"
#include "RaspiCLI.h"


typedef struct
{
    int timeout;                        /// Time taken before frame is grabbed and app then shuts down. Units are milliseconds
    int width;                          /// Requested width of image
    int height;                         /// requested height of image
    char *filename;                     /// filename of output file
    char *linkname;                     /// filename of output file
    int verbose;                        /// !0 if want detailed run information
    int timelapse;                      /// Delay between each picture in timelapse mode. If 0, disable timelapse
    int useRGB;                         /// Output RGB data rather than YUV
    int fullResPreview;                 /// If set, the camera preview port runs at capture resolution. Reduces fps.
    int frameNextMethod;                /// Which method to use to advance to next frame
    int settings;                       /// Request settings from the camera
    int cameraNum;                      /// Camera number
    int burstCaptureMode;               /// Enable burst mode
    int onlyLuma;                       /// Only output the luma / Y plane of the YUV data

    RASPIPREVIEW_PARAMETERS preview_parameters;    /// Preview setup parameters
    RASPICAM_CAMERA_PARAMETERS camera_parameters; /// Camera setup parameters

    MMAL_COMPONENT_T *camera_component;    /// Pointer to the camera component
    MMAL_COMPONENT_T *null_sink_component;    /// Pointer to the camera component
    MMAL_CONNECTION_T *preview_connection; /// Pointer to the connection from camera to preview
    MMAL_POOL_T *camera_pool;              /// Pointer to the pool of buffers used by camera stills port
} RASPISTILLYUV_STATE;

RASPISTILLYUV_STATE *raspistill_create_status();
int raspistill_init(RASPISTILLYUV_STATE *state);
void raspistill_get_actual_capture_size(RASPISTILLYUV_STATE *state, int *width, int *height);
int raspistill_capture(RASPISTILLYUV_STATE *state, void *dest_buffer);
int raspistill_tear_down(RASPISTILLYUV_STATE *state, int status);


int cameraci_test();
#endif //BIKAMERA_CAMERACI_H
