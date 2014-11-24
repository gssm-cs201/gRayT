import os, sys
num_frames = 200
extension = "exr"
name = "turntable"
for frame in range(0, num_frames):
    frame_pad = str(frame).zfill(4)
    os.system("./example -num_frames " + str(num_frames) + " -frame " + str(frame) + " -name " + name + "." + frame_pad + "." + extension  + " -SX " + str(4) + " -SY " + str(4))
