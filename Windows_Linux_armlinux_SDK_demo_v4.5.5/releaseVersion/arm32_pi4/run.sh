#!/bin/bash
if (( $EUID != 0 )); then
  echo "Root is required!"
  exit 1
fi
QTDIR=/usr/lib/arm-linux-gnueabihf/qt5
#LD_LIBRARY_PATH='/home/pi/Examples/senseengine_lib-develop/uvcCamera/../ffmpeg/lib/linux64_14:/home/pi/Examples/senseengine_lib-develop/uvcCamera/../lib/linux64_14/release:/usr/lib/arm-linux-gnueabihf' ./uvcCamera
#LD_LIBRARY_PATH='-linux-gnueabihf' ./uvcCamera
LD_LIBRARY_PATH=$LD_LIBRARY_PATH:./ ./uvcCamera

