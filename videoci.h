//
// Created by Walter Gamba on 09/04/17.
//

#ifndef BIKAMERA_VIDEOCI_H
#define BIKAMERA_VIDEOCI_H
#include <stdio.h>

#include "bcm_host.h"
#include "interface/vcos/vcos.h"

#include "interface/mmal/mmal.h"
#include "interface/mmal/mmal_logging.h"
#include "interface/mmal/mmal_buffer.h"
#include "interface/mmal/util/mmal_util.h"
#include "interface/mmal/util/mmal_util_params.h"
#include "interface/mmal/util/mmal_default_components.h"
#include "interface/mmal/util/mmal_connection.h"


#include "RaspiCamControl.h"
#include "RaspiPreview.h"
#include "RaspiCLI.h"

// Forward
typedef struct RASPIVIDYUV_STATE_S RASPIVIDYUV_STATE;

/** Struct used to pass information in camera video port userdata to callback
 */
typedef struct
{
    void *buffer;                        /// Memory buffer
    FILE *file_handle;                   /// File handle to write buffer data to.
    RASPIVIDYUV_STATE *pstate;           /// pointer to our state in case required in callback
    int abort;                           /// Set to 1 in callback if an error occurs to attempt to abort the capture
    int frame_count;                     /// used to keep track of frames
    void (*frame_callback_function)(char *); //call this callback for every frame
} PORT_USERDATA;

/** Structure containing all state information for the current run
 */
struct RASPIVIDYUV_STATE_S
{
    int timeout;                        /// Time taken before frame is grabbed and app then shuts down. Units are milliseconds
    int width;                          /// Requested width of image
    int height;                         /// requested height of image
    int framerate;                      /// Requested frame rate (fps)
    char *filename;                     /// filename of output file
    int verbose;                        /// !0 if want detailed run information
    int demoMode;                       /// Run app in demo mode
    int demoInterval;                   /// Interval between camera settings changes
    int waitMethod;                     /// Method for switching between pause and capture

    int onTime;                         /// In timed cycle mode, the amount of time the capture is on per cycle
    int offTime;                        /// In timed cycle mode, the amount of time the capture is off per cycle

    int onlyLuma;                       /// Only output the luma / Y plane of the YUV data
    int useRGB;                         /// Output RGB data rather than YUV

    RASPIPREVIEW_PARAMETERS preview_parameters;   /// Preview setup parameters
    RASPICAM_CAMERA_PARAMETERS camera_parameters; /// Camera setup parameters

    MMAL_COMPONENT_T *camera_component;    /// Pointer to the camera component
    MMAL_CONNECTION_T *preview_connection; /// Pointer to the connection from camera to preview

    MMAL_POOL_T *camera_pool;            /// Pointer to the pool of buffers used by camera video port

    PORT_USERDATA callback_data;         /// Used to move data to the camera callback

    int bCapturing;                      /// State of capture/pause

    int cameraNum;                       /// Camera number
    int settings;                        /// Request settings from the camera
    int sensor_mode;                     /// Sensor mode. 0=auto. Check docs/forum for modes selected by other values.
};


RASPIVIDYUV_STATE *raspivideo_create_status();

void raspivideo_get_actual_capture_size(RASPIVIDYUV_STATE *state, int *width, int *height);
int  raspivideo_init(RASPIVIDYUV_STATE *state);
int raspivideo_start_capture(RASPIVIDYUV_STATE *state, char *buffer);
int raspivideo_end_capture(RASPIVIDYUV_STATE *state);
int raspivideo_tear_down(RASPIVIDYUV_STATE *state, MMAL_STATUS_T status);
#endif //BIKAMERA_VIDEOCI_H
