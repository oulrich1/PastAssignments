IGV
===

Simplified version of the IGV's old code..

This version has 3 threads: MakeDecisions, StereoProcessing, MotionLoop.

MotionLoop connects to the galil and sends Galil Commands. The galil
handles the motion of the bot and provides the control loop with the
motors.

Make decisions is a template for our decision making code

StereoProcessing is where we get the images and possibly even analyse
the images. (not sure if they should be seperate threads or just the
same thread running subroutines that not only look at images (possibly
storing some images) but also processes these images.

IGV main is simpler yet similar to the original code... I think we could
get a prototype of the Stereo Processing going on this code..

NOTE: This project is a visual studio project.. you guys have access to
visual studio for free with your chico MSDNAA accounts... among other
free software.. However it's not that MUCH code to convert to a linux
setup, I do now know how to translate windows system constructs directly
to Linux system constructs..
