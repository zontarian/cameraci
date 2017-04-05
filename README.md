# cameraci
Simple "C" module to get still images from the camera of the RaspberryPi

# dependencies
This "library" is a simple rewriting of RaspiStillYUV.c, reorganizing calls so as to be simply embeddable in another program, even in a loop.
It even imports and depends on Raspi*.c/Raspi*.h which are, at the moment, included.

# install
Ue the provieded "compile.sh" file to compile the test program. The compile program if successfull, will "sudo" launch the test program.
