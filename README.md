# cameraci/videoci
Simple "C" module to get a memory buffer holding the RGB/YUV data of still images from the camera of the RaspberryPi. The module has two interfaces, `cameraci` for single pics or very slow video, and `videoci` which is somehow fast and on my PiZero reaches above 10fps with some image processing.

See the pun in the names? Like cameraPy but for "C" (which is pronounced "chee" in italian). Ain't it terrbile?

# dependencies
This "library" is a simple rewriting of RaspiStillYUV.c, reorganizing calls so as to be simply embeddable in another program, even in a loop. The file is "cameraci.c" and "cameraci.h" holds the interface.

As for the fastest "videoci.c", this is a rewrite of `RaspiVidYUV.c`. 

It even imports and depends on RaspiStill*.c and RaspiStill*.h which are, at the moment, included.

# differences
In order to stick to RaspiStillYUV internal working, I've modified the `PORT_USERDATA` struct to hold a pointer to a memory buffer lrge enough to hold the image data.
Same holds for RaspiVidYUV.

# install
Ue the provieded "compile.sh" file to compile the test program. The compile program if successfull, will "sudo" launch the test program.

# usage 
See `videoci_control.c` or `cameraci_control.c` and the respecitve headers for usage. It is very simple. I will post a more detailed example in a few days.

# known issues
a part from the overall sluggishness, the code is absolutely not thread safe! I guess it doesn't take much to make it thread safe, if RaspiStillYUV is such, but I don't see the need at the moment.
Same holds 

# in the future
maybe I will build a real library.. 
