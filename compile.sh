#!/bin/sh

gcc -I . -fPIC -g -w -march=armv6 -mfpu=vfp -mfloat-abi=hard \
    -g3 -ggdb \
    -isystem /opt/vc/include/ \
    -isystem /opt/vc/include/EGL \
    -isystem /opt/vc/include/mmal \
    -isystem /opt/vc/include/interface/vcos/pthreads/ \
    -isystem /opt/vc/include/interface/vmcs_host/linux/ \
    -L /opt/vc/lib -lbcm_host -lmmal -lvcos -lpthread -lmmal_core -lmmal_util  \
   RaspiCLI.c RaspiPreview.c RaspiCamControl.c \
    videoci.c videoci_control.c -o videoci_control

#   cameraci.c   cameraci_control.c -o cameraci_control

#
# raspistill --width 400 --height 280 -n -o test.jpg
#

if [ $? -eq 0 ] ; then
    sudo ./videoci_control
fi
