# SenseEngine M20/M20s/M30 SDK# Development kit structure description



![img](Images\clip_image001.png)

├── Doc

├── ffmpeg

├── include

├── lib

├── MtcControlLibuvcCamera

├── MtcControlLibuvcCamera.pro

├── releaseVersion

├── sample

├── tools

└── uvcCamera

# Structure Description

- Doc ：This folder stores SDK API documentation
- - SenseEngine      AI Visual Module Windows&Linux API User Guide-VX.X.X-yyyymmdd.md : SDK API documentation in English
  - SenseEngine      AI视觉模组Win&Linux开发接口使用文档-VX.X.X-yyyymmdd.md : SDK API decumentation in Chinese
- ffmpeg ：This folder stores the development files of ffmpeg compiled by each platform. The development files include:
- - bin ：This folder stores the dynamic link library (dll) files compiled by ffmpeg on the Windows platform. Note: The compiled dynamic link library (dll) files do not depend on the QtCreator framework.
  - - windows-mingw-32bit：minGW 32bit dynamic link library （dll）
    - windows-msvc-64bit：msvc 64bit dynamic link library （dll）
  - include ：This folder stores ffmpeg related header files
  - lib ：This folder stores ffmpeg-related static link library (lib) files for each platform. Note: The compiled dynamic link library (lib) files have no dependencies on the QtCreator framework.
  - - aarch64_cmitech
    - aarch64_skyj
    - arm32_pi4
    - linux64_14
    - linux64_16
    - windows-msvc-64bit
    - wukong32
    - wukong64
- include ：This folder stores SDK  head files
- lib ：This folder stores libraries for each platform
- releaseVersion     ：This folder stores program release installation package for each platform
- sample ：This folder stores simple example of windows platform (Development languages include C++/C#/Python) / Linux Demo (Development languages include C++)
- tools ：This folder stores program packaging tool scripts and drivers
- uvcCamera ：The folder stores the sample source code (Sample Demo Source Code) Note: Considering the compatibility of different platforms of Windows/Linux/Raspberry, the sample source code depends on the QtCreator framework
- MtcControlLibuvcCamera.pro     ：(Qt example project configuration file)
- MtcControlLibuvcCamera     ： (VS example project configuration file)
