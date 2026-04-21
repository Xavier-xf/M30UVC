#!/bin/bash
rm RecoDemo

echo "0:RaspberryPi"
echo "1:Linux"
echo "2:Tinker board 2s"
echo "3:Allwinner arm32"
echo "4:Allwinner aarch64"
echo "5:imx6ull"
echo 'Please select platform(0/1/2) : '

read num
case $num in
	0) PLATFORM="../../../releaseVersion/arm32_pi4"
	;;
	1) PLATFORM="../../../releaseVersion/linux64_14"
	;;
	2) PLATFORM="../../../releaseVersion/aarch64_tk2s"
	;;
	3) PLATFORM="../../../releaseVersion/arm32_allwinner"
	;;
	4) PLATFORM="../../../releaseVersion/aarch64_allwinner"
	;;
	5) PLATFORM="../../../releaseVersion/imx6ull"
	;;
	*) echo "Select platform error"
	   exit 
	;;
esac	

gcc RecoDemo.cpp rgb2bmp.cpp -L$PLATFORM -lAICameraModule -lavutil \
            -lavcodec \
            -lswscale \
            -lavformat \
            -lavdevice \
            -lswresample \
            -lavfilter -o RecoDemo

export LD_LIBRARY_PATH="${LD_LIBRARY_PATH}:${PLATFORM}"
./RecoDemo
