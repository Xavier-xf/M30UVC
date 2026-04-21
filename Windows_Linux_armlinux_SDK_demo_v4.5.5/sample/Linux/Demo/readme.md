<!--
 * @Copyright: (c) 2014-2024 SenseTime :  All rights reserved.
 * @Description: file content
 * @Author: 洪照
 * @Date: 2024-04-18 11:00:34
 * @LastEditors: 洪照
 * @LastEditTime: 2024-04-18 17:50:11
 * @FilePath: \senseengine_lib\sample\Linux\Demo\readme.md
-->
# The directory structure is as follows

```shell
include/
├── ai_camera_errcode.h
└── ai_camera.h
sample/
├── Linux
└── windows
releaseVersion/
├── aarch64_allwinner
├── aarch64_cmitech
├── aarch64_skyj
├── aarch64_tk2s
├── arm32_allwinner
├── arm32_pi4
├── linux64_14
└── windows-msvc-64bit

SENSETIME@CN3514000153L:~/senseengine_lib/releaseVersion/linux64_14$ ls
audio                       libavcodec.so.58          libbz2.so.1             libgstvideo-1.0.so.0         libqgsttools_p.so.1       libX11-xcb.so.1      Log
bearer                      libavcodec.so.58.35.100   libbz2.so.1.0           libgthread-2.0.so.0          libqtlibpng.a             libXau.so.6          mediaservice
cmake                       libavdevice.so            libbz2.so.1.0.4         libicudata.so.56             libsndfile.so.1           libxcb-glx.so.0      pkgconfig
config.ini                  libavdevice.so.58         libdbus-1.so.3          libicui18n.so.56             libswresample.so          libxcb-present.so.0  platforminputcontexts
doc                         libavdevice.so.58.5.100   libffi.so.6             libicuuc.so.56               libswresample.so.3        libxcb-shape.so.0    platforms
hongzhao.feature            libavfilter.so            libFLAC.so.8            libjson-c.so.2               libswresample.so.3.3.100  libxcb-sync.so.1     run.sh
iconengines                 libavfilter.so.7          libgbm.so.1             libnsl.so.1                  libswscale.so             libxcb-xfixes.so.0   translations
imageformats                libavfilter.so.7.40.101   libgmodule-2.0.so.0     libogg.so.0                  libswscale.so.5           libXdamage.so.1      uvcCamera
libAICameraModule.so        libavformat.so            libgstapp-1.0.so.0      liborc-0.4.so.0              libswscale.so.5.3.100     libXdmcp.so.6        xcbglintegrations
libAICameraModule.so.4      libavformat.so.58         libgstaudio-1.0.so.0    libpcre.so.3                 libvorbisenc.so.2         libXext.so.6
libAICameraModule.so.4.5    libavformat.so.58.20.100  libgstbase-1.0.so.0     libpng12.so.0                libvorbis.so.0            libXfixes.so.3
libAICameraModule.so.4.5.0  libavutil.so              libgstpbutils-1.0.so.0  libpulsecommon-4.0.so        libwayland-client.so.0    libXi.so.6
libasyncns.so.0             libavutil.so.56           libgstreamer-1.0.so.0   libpulse-mainloop-glib.so.0  libwayland-server.so.0    libxshmfence.so.1
libavcodec.so               libavutil.so.56.22.100    libgsttag-1.0.so.0      libpulse.so.0                libwrap.so.0              libXxf86vm.so.1
```

# The method of use is as follows
```shell
SENSETIME@CN3514000153L:~/senseengine_lib/sample/Linux/Demo$ sudo ./run.sh
0:RaspberryPi
1:Linux
2:Tinker board 2s
3:Allwinner arm32
4:Allwinner aarch64
Please select platform(0/1/2) :
1
```