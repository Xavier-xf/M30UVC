# SenseEngine M20/M20s/M30 SDK开发包文档结构说明



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

# 开发包文档结构说明

- Doc ：存放SDK API接口文档
- - SenseEngine      AI Visual Module Windows API User Guide-VX.X.X-yyyymmdd.md : SDK API中文接口文档
  - SenseEngine      AI视觉模组Win&Linux开发接口使用文档-VX.X.X-yyyymmdd.md : SDK API英文接口文档
- ffmpeg ：存放各个平台编译出来的ffmpeg的开发文件，包含的开发文件包括：
- - bin ：存放Windows平台关于ffmpeg 编译出来的动态链接库（dll）文件 注：编译出来的动态链接库（dll）文件对QtCreator框架没有依赖
  - - windows-mingw-32bit：存放minGW 32bit 动态链接库（dll）
    - windows-msvc-64bit：       存放msvc 64bit 动态链接库（dll）
  - include      ：存放ffmpeg相关的头文件
  - lib ：存放各个平台ffmpeg相关静态链接库（lib）文件 注：编译出来的动态链接库（lib）文件对QtCreator框架没有依赖
  - - aarch64_cmitech
    - aarch64_skyj
    - arm32_pi4
    - linux64_14
    - linux64_16
    - windows-msvc-64bit
    - wukong32
    - wukong64
- include ：存放SDK 头文件
- lib ：存放各个平台SDK库文件
- releaseVersion     ：存放各个平台程序发布安装包
- sample ：存放 Windows平台简易示例 (开发语言包括C++/C#/Python)/Linux Demo(开发语言包括C++)
- tools ：存放程序打包工具脚本及驱动程序
- uvcCamera ：存放示例源码(Sample Demo Source Code) 注：考虑到Windows/Linux/Raspberry不同平台的兼容性问题,示例源码对QtCreator框架有依赖
- MtcControlLibuvcCamera.pro     ：(Qt 示例工程配置文件)
- MtcControlLibuvcCamera     ： (VS示例工程配置文件)
