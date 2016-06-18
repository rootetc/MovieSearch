@echo off

ffmpeg -y -i c:\\test.mp4 -r 15 -f image2 -s vga "c:\\output\\%%05d.bmp"
