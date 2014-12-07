import os, sys
num_frames = 24
extension = "exr"
name = "turntable"
for frame in range(0, num_frames):
    frame_pad = str(frame).zfill(4)
    os.system("./example -nframes " + str(num_frames) + " -frame " + str(frame) + " -name " + name + "." + frame_pad + "." + extension  + " -SX " + str(1) + " -SY " + str(1) + " -CY 0 -radius 7 -obj monkey.obj")
