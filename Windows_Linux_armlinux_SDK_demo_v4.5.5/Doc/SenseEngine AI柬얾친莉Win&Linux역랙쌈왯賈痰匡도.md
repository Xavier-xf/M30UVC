| 版本     | 更新时间   | 描述           | 修改人      |
| -------- | ---------- | -------------- | ----------- |
| V1.3     | 2019/10/30 | 详见Change Log | Liu Rui     |
| V1.4     | 2019/11/27 | 详见Change Log | Fan Zhao    |
| V1.5     | 2019/12/31 | 详见Change Log | Fan Zhao    |
| V1.6     | 2020/3/3   | 详见Change Log | Fan Zhao    |
| V1.7     | 2020/3/30  | 详见Change Log | Fan Zhao    |
| V1.8     | 2020/4/8   | 详见Change Log | Fan Zhao    |
| V1.9     | 2020/5/9   | 详见Change Log | Fan Zhao    |
| V1.10    | 2020/6/22  | 详见Change Log | Fan Zhao    |
| V1.11    | 2020/7/20  | 详见Change Log | Fan Zhao    |
| V1.12    | 2020/9/10  | 详见Change Log | Fan Zhao    |
| V1.13    | 2020/10/13 | 详见Change Log | Fan Zhao    |
| V1.14    | 2020/12/3  | 详见Change Log | Fan Zhao    |
| V1.15    | 2021/01/05 | 详见Change Log | Long Zeyuan |
| V4.0.2   | 2021/06/24 | 详见Change Log | Cheng Lin   |
| V4.0.8   | 2021/08/10 | 详见Change Log | Cheng Lin   |
| V4.0.10  | 2021/09/18 | 详见Change Log | Cheng Lin   |
| V4.1.2   | 2021/09/18 | 详见Change Log | Cheng Lin   |
| V4.1.5   | 2022/03/07 | 详见Change Log | Cheng Lin   |
| V4.2.0   | 2022/04/29 | 详见Change Log | Cheng Lin   |
| V4.2.0.1 | 2022/05/07 | 详见Change Log | Cheng Lin   |
| V4.3.0   | 2022/08/26 | 详见Change Log | Lin Yifan   |
| V4.3.1   | 2022/12/05 | 详见Change Log | Lin Yifan   |
| V4.4.0   | 2023/05/16 | 详见Change Log | Zhou Bo     |
| V4.4.1   | 2023/06/09 | 详见Change Log | Zhou Bo     |
| V4.4.2   | 2023/06/19 | 详见Change Log | Zhou Bo     |
| V4.4.3   | 2023/06/19 | 详见Change Log | Zhou Bo     |
| V4.4.4   | 2023/07/31 | 详见Change Log | Zhou Bo     |
| V4.4.5   | 2023/07/31 | 详见Change Log | Zhou Bo     |

# SenseEngine AI视觉模组Win&Linux开发接口使用文档

[TOC]



# 概述

本文档描述单一类型的功能，主要面向开发者。主要目的是让开发者了解每种类型提供的具体用途和功能。

该使用文档所有接口适用于 M20/M20s/M30/M30 等视觉模组及 Qt，C#，VC++/CLI 等开发环境

# 日志部分

| 函数                                                     | API描述                    |
| :------------------------------------------------------- | -------------------------- |
| int SetLogConfig(int nLogLever = 1, int nLogTarget = 2); | 设置日志级别和日志输出位置 |
| int GetLogConfig(int* pLogLever, int* pLogTarget);       | 获取日志级别和日志输出位置 |

## SetLogConfig()

1）功能说明：设置日志级别和日志输出位置

2）函数原型：

```c++
int SetLogConfig(int nLogLever = 1, int nLogTarget = 2);
```

3）参数：

| 参数名称   | 参数数据类型 | 参数描述     |
| ---------- | ------------ | ------------ |
| nLogLever  | int          | 日志级别     |
| nLogTarget | int          | 日志输出位置 |

| 日志级别            | 参数描述                                       |
| ------------------- | ---------------------------------------------- |
| 0 :LOG_LEVER_TRACE  | 输出 TRACE DEBUG INFO WARN ERROR FATAL级别日志 |
| 1 :LOG_LEVER_DEBUG  | 输出  DEBUG INFO WARN ERROR FATAL级别日志      |
| 2: LOG_LEVER_INFO   | 输出  INFO WARN ERROR FATAL级别日志            |
| 3 : LOG_LEVER_WARN  | 输出  WARN ERROR FATAL级别日志                 |
| 4 :LOG_LEVER_ERROR  | 输出  ERROR FATAL级别日志                      |
| 5 : LOG_LEVER_FATAL | 输出  FATAL级别日志                            |
| 6 : LOG_LEVER_NONE  | 不打印日志                                     |

| 日志输出位置          | 参数描述                                                     |
| --------------------- | ------------------------------------------------------------ |
| 0 :LOG_TARGET_CONSOLE | 日志输出到控制台                                             |
| 1 : LOG_TARGET_FILE   | 日志输出到文件                                               |
| 2 : LOG_TARGET_ALL    | 日志输出到文件和控制台<br />注：Windows平台设置此参数只会将日志输出到文件   Linux平台设置此参数日志输出到文件和控制台 |

4）返回值：

| 返回值 | 描述                  |
| ------ | --------------------- |
| < 0    | 请参考 接口异常返回值 |
| 0      | 成功                  |

## GetLogConfig()

1）功能说明：获取日志级别和日志输出位置

2）函数原型：

```c++
int GetLogConfig(int* pLogLever, int* pLogTarget);
```

3）参数：

| 参数名称   | 参数数据类型 | 参数描述     |
| ---------- | ------------ | ------------ |
| pLogLever  | Int*         | 日志级别     |
| pLogTatget | Int*         | 日志输出位置 |

| 日志级别            | 参数描述                                       |
| ------------------- | ---------------------------------------------- |
| 0 :LOG_LEVER_TRACE  | 输出 TRACE DEBUG INFO WARN ERROR FATAL级别日志 |
| 1 :LOG_LEVER_DEBUG  | 输出  DEBUG INFO WARN ERROR FATAL级别日志      |
| 2: LOG_LEVER_INFO   | 输出  INFO WARN ERROR FATAL级别日志            |
| 3 : LOG_LEVER_WARN  | 输出  WARN ERROR FATAL级别日志                 |
| 4 :LOG_LEVER_ERROR  | 输出  ERROR FATAL级别日志                      |
| 5 : LOG_LEVER_FATAL | 输出  FATAL级别日志                            |
| 6 : LOG_LEVER_NONE  | 不打印日志                                     |

| 日志输出位置          | 参数描述               |
| --------------------- | ---------------------- |
| 0 :LOG_TARGET_CONSOLE | 日志输出到控制台       |
| 1 : LOG_TARGET_FILE   | 日志输出到文件         |
| 2 : LOG_TARGET_ALL    | 日志输出到文件和控制台 |

4）返回值：

| 返回值 | 描述                  |
| ------ | --------------------- |
| < 0    | 请参考 接口异常返回值 |
| 0      | 成功                  |

# 设备初始化部分

| 函数                                                         | API描述                    |
| :----------------------------------------------------------- | -------------------------- |
| void* Init();                                                | 初始化设备                 |
| int DeInit(void* dev);                                       | 释放设备资源               |
| int EnumDevice(char *videoDevBuf, int videoDevSize, char *serialBuf, int serialSize); | 查询目前系统连接的设备列表 |
| int ConnectSerial(void* dev, const char* portName);          | 连接串口                   |
| int ConnectCamera(void* dev, const char* mediaName);         | 连接UVC摄像头设备          |
| int DisconnectSerial(void* dev);                             | 断开串口连接               |
| int DisconnectCamera(void* dev);                             | 断开UVC摄像头设备          |

## Init()

1）功能说明：初始化设备  注：若开启日志打印功能，调用此函数时日志文件会打印SDK软件版本号，以便协助开发人员排查问题

2）函数原型：

```c++
void* Init();
```

3）参数：无

4）返回值： 返回函数句柄（例如，Init()的返回值会作为 int DeInit(void* dev)的输入参数）

## DeInit()

1）功能说明：释放设备资源,断开UVC摄像头和串口

2）函数原型：

```c++
int DeInit(void* dev);
```

3）参数：

| 参数名称 | 参数数据类型 | 参数描述                           |
| -------- | ------------ | ---------------------------------- |
| dev      | void*        | Init()初始化设备接口返回的函数句柄 |

4）返回值：

| 返回值 | 描述                  |
| ------ | --------------------- |
| < 0    | 请参考 接口异常返回值 |
| 0      | 成功                  |

## EnumDevice()

1）功能说明：查询目前系统连接的设备列表

2）函数原型：

```c++
int EnumDevice(char *videoDevBuf, int videoDevSize, char *serialBuf, int serialSize);
```

3）参数：

| 参数名称     | 参数数据类型 | 参数描述                                                     |
| ------------ | ------------ | ------------------------------------------------------------ |
| videoDevBuf  | char*        | UVC设备名称数组，如系统检测到有多个UVC设备，名称之间以"\|"分隔<br />Windows下一般格式，如：UVC Camera，且Windows上只能接入一台M20/M20s/M30设备<br />Linux下一般格式，如：/dev/video0\|/dev/video1，且Linux上可接入多台M20/M20s/M30设备 |
| videoDevSize | int          | videoDevBuf分配的字节数，一般可填1024                        |
| serialBuf    | char*        | 串口设备名称数组，如系统检测到有多个串口设备，名称之间以"\|“分隔<br />Windows下一般格式，如：COM0\|COM1\|COM4<br />Linux下一般格式，如：/dev/ttyACM0\|/dev/ttyACM1 |
| serialSize   | int          | serialBuf分配的字节数，一般可填1024                          |

4）返回值：

| 返回值 | 描述                  |
| ------ | --------------------- |
| < 0    | 请参考 接口异常返回值 |
| 0      | 成功                  |

## ConnectSerial()

1）功能说明：连接串口

2）函数原型：

```c++
int ConnectSerial(void* dev, const char* portName);
```

3）参数：

| 参数名称 | 参数数据类型 | 参数描述                                                     |
| -------- | ------------ | ------------------------------------------------------------ |
| dev      | void*        | Init()初始化设备接口返回的函数句柄                           |
| portName | const char*  | 连接的串口名称<br />Windows下通常为  "COMX"，Linux通常为"ttyACMX",X表示阿拉伯数字 |

4）返回值：

| 返回值 | 描述                                                         |
| ------ | ------------------------------------------------------------ |
| < 0    | 请参考 接口异常返回值<br />多次调用此接口有时会返回-2，为保证串口连接正常，请断开串口后重新进行连接串口，直到此接口返回0 |
| 0      | 串口连接成功                                                 |

## ConnectCamera()

1）功能说明：连接UVC摄像头设备

2）函数原型：

```c++
int ConnectCamera(void* dev, const char* mediaName);
```

3）参数：

| 参数名称  | 参数数据类型 | 参数描述                                                     |
| --------- | ------------ | ------------------------------------------------------------ |
| dev       | void*        | Init()初始化设备接口返回的函数句柄                           |
| mediaName | const char*  | 连接的UVC设备名称<br />Windows下通常为  "UVC Camera"，Linux下通常为"ttyACMX",X表示阿拉伯数字 |

4）返回值：

| 返回值 | 描述                  |
| ------ | --------------------- |
| < 0    | 请参考 接口异常返回值 |
| 0      | UVC摄像头设备连接成功 |

## DisconnectSerial()

1）功能说明：断开串口连接

2）函数原型：

```c++
int DisconnectSerial(void* dev);
```

3）参数：

| 参数名称 | 参数数据类型 | 参数描述                           |
| -------- | ------------ | ---------------------------------- |
| dev      | void*        | Init()初始化设备接口返回的函数句柄 |

4）返回值：

| 返回值 | 描述                  |
| ------ | --------------------- |
| < 0    | 请参考 接口异常返回值 |
| 0      | 断开串口连接成功      |

## DisconnectCamera()

1）功能说明：断开UVC摄像头设备

2）函数原型：

```c++
int DisconnectCamera(void* dev);
```

3）参数：

| 参数名称 | 参数数据类型 | 参数描述                           |
| -------- | ------------ | ---------------------------------- |
| dev      | void*        | Init()初始化设备接口返回的函数句柄 |

4）返回值：

| 返回值 | 描述                  |
| ------ | --------------------- |
| < 0    | 请参考 接口异常返回值 |
| 0      | 断开UVC摄像头设备成功 |

# 媒体部分

| 函数                                                         | API描述                    |
| ------------------------------------------------------------ | -------------------------- |
| int GetFrame(void* dev, char* imageBuf, int imageSize, char* verifyBuf, int verifySize); | 获取视频流帧数据及识别数据 |
| int GetResolution(void* dev, int* width, int* height);       | 获取分辨率                 |

## GetFrame()

1）功能说明：获取一帧的图像数据与验证信息，图像存储格式为位图，顺序BBGGRRAA。调用者需轮询该接口获取最新图像。 注 ： 该接口频繁调用，打印日志影响性能，故未进行日志打印

2）函数原型：

```c++
int GetFrame(void* dev, char* imageBuf, int imageSize, char* verifyBuf, int verifySize);
```

3）参数：

| 参数名称   | 参数数据类型 | 参数描述                                                     |
| ---------- | ------------ | ------------------------------------------------------------ |
| dev        | void*        | Init()初始化设备接口返回的函数句柄                           |
| imageBuf   | char *       | 图像数据                                                     |
| imageSize  | int          | 图像数据所占字节数<br />调用GetResolution(width,height);<br />imageSize = width * height * 4 |
| verifyBuf  | char *       | 存储由设备发来的识别信息，格式为 json。<br />调用OpenAutoUploadFaceInfoInFrame接口可获取到验证信息<br />调用CloseAutoUploadAiInfo接口无法获取到验证信息，即 获取到的验证信息内容为空 |
| verifySize | int          | 验证信息所占字节数，一般可填1024<br />verifySize值太小，接口会返回-4 |

4）返回值：

| 返回值 | 描述                  |
| ------ | --------------------- |
| < 0    | 请参考 接口异常返回值 |
| 0      | 成功                  |



字段含义参考：

| 参数名称                       | 参数数据类型               | 参数描述                                                     |
| ------------------------------ | -------------------------- | ------------------------------------------------------------ |
| face_info                      | array                      | 包含所有识别到的人脸数据                                     |
| rect[bottom, right, left, top] | object[int, int, int, int] | 识别到的人脸矩型坐标                                         |
| recognition_status             | int                        | 识别结果的状态值：  0：还未识别  1：非活体  2：库中人  3：陌生人  4：表示已经识别出结果 |
| recognition_id                 | string                     | 可能的值为: UNKNOWN  NOLIVENESS /库中人ID/ STRANGER          |
| recognize_score                | float                      | 第一次成功才会有该项（当recognition_status为2情况会有，当recognition_status为4则没有） |
| liveness_score                 | float                      | 与recognize_score同样情况                                    |

## GetResolution()

1）功能说明：获取一帧图像数据的宽和高 。

注：GetFrame(void* dev, char* imageBuf, int imageSize, char* verifyBuf, int verifySize)接口中第三个参数imageSize = width * height * 4

2）函数原型：

```c++
int GetResolution(void* dev, int* width, int* height);
```

3）参数：

| 参数名称 | 参数数据类型 | 参数描述                           |
| -------- | ------------ | ---------------------------------- |
| dev      | void*        | Init()初始化设备接口返回的函数句柄 |
| width    | int *        | 一帧图像数据的宽度                 |
| height   | Int *        | 一帧图像数据的高度                 |

4）返回值：

| 返回值 | 描述                  |
| ------ | --------------------- |
| < 0    | 请参考 接口异常返回值 |
| 0      | 成功                  |

# 设置部分

| 函数                                                         | API描述                        |
| ------------------------------------------------------------ | ------------------------------ |
| int SetCameraStream(void* dev, char isCloseCamera, char nCameraType); | 打开/关闭摄像头                |
| int GetCameraStream(void* dev, char nCameraType, uchar* isOpenCamera); | 获取摄像头状态                 |
| int SwitchCamRgbIr(void* dev, char nMode);                   | 切换RGB与IR视频流              |
| int MirrorCamRgbIr(void* dev, char nMode, char nMirror);     | 切换RGB与IR视频流以及对应视频流是否mirror |
| int GetLuminousSensitivityThreshold(void* dev, uint* nThreshold); | 获取当前光敏值                 |
| int GetDeviceNoFlickerHz(void* dev, char nCameraId,  uchar* pHz, uchar* isEnable); | 获取抗闪设置参数               |
| int SetDeviceNoFlickerHz(void* dev, char nCameraId,  char nHz, char isEnable); | 设置抗闪设置参数               |
| int SetResolution(void* dev, char nMode);                    | 设置分辨率/画面尺寸            |
| int GetFrameRate(void* dev, uint* pFrameRate);               | 获取当前帧率                   |
| int SetFrameRate(void* dev, int nFrameRate);                 | 设置帧率                       |
| int GetIRlight(void* dev, uchar* pLuminance,uchar* pCloseTime); | 获取IR灯亮度与当前自动关闭时长 |
| int SetIRlight(void* dev, uchar nLuminance, uchar nCloseTime); | 设置IR灯亮度与自动关闭时长     |

## SetCameraStream()

1）功能说明：设置摄像头开关

注：调用此接口同时关闭RGB/IR摄像头,调用DisconnectCamera接口断开UVC设备连接，再次调用ConnectCamera连接UVC设备时，该接口容易卡死，需要重新给设备上电才能重新成功连接到UVC设备；另外，还有一种方法可以规避此问题，每当调用此接口关闭RGB或者IR摄像头，调用SwitchCamRgbIr接口切换RGB与IR摄像头，这样就能保证RGB/IR摄像头其中有一个能够正常输出视频流。

2）函数原型：

```c++
int SetCameraStream(void* dev, char isCloseCamera, char nCameraType);
```

3）参数：

| 参数名称      | 参数数据类型 | 参数描述                               |
| ------------- | ------------ | -------------------------------------- |
| dev           | void*        | Init()初始化设备接口返回的函数句柄     |
| isCloseCamera | char         | 0x00：打开摄像头<br />0x01：关闭摄像头 |
| nCameraType   | char         | 0x00：RGB摄像头<br />0x01：IR摄像头    |

4）返回值：

| 返回值 | 描述                  |
| ------ | --------------------- |
| < 0    | 请参考 接口异常返回值 |
| 0      | 处理成功              |
| 161    | 处理失败              |

## GetCameraStream()

1）功能说明：获取摄像头开关状态

2）函数原型：

```c++
int GetCameraStream(void* dev, char nCameraType, uchar* isOpenCamera);
```

3）参数：

| 参数名称     | 参数数据类型 | 参数描述                            |
| ------------ | ------------ | ----------------------------------- |
| dev          | void*        | Init()初始化设备接口返回的函数句柄  |
| nCameraType  | char         | 0x00：RGB摄像头<br />0x01：IR摄像头 |
| isOpenCamera | uchar*       | 0x00：未打开<br />0x01：已经打开    |

4）返回值：

| 返回值 | 描述                  |
| ------ | --------------------- |
| < 0    | 请参考 接口异常返回值 |
| 0      | 处理成功              |
| 161    | 处理失败              |

## SwitchCamRgbIr()

1）功能说明：切换RGB与IR摄像头	注：仅当前有效,重启无效

2）函数原型：

```c++
int SwitchCamRgbIr(void* dev, char nMode);
```

3）参数：

| 参数名称 | 参数数据类型 | 参数描述                           |
| -------- | ------------ | ---------------------------------- |
| dev      | void*        | Init()初始化设备接口返回的函数句柄 |
| nMode    | char         | 0x00：切换RGB<br />0x01：切换IR    |

4）返回值：

| 返回值 | 描述                  |
| ------ | --------------------- |
| < 0    | 请参考 接口异常返回值 |
| 0      | 处理成功              |
| 1      | 处理失败              |

## MirrorCamRgbIr()

1）功能说明：切换RGB与IR摄像头以及对应码流是否mirror	注：仅当前有效,重启无效

2）函数原型：

```c++
int MirrorCamRgbIr(void* dev, char nMode, char nMirror);
```

3）参数：

| 参数名称 | 参数数据类型 | 参数描述                           |
| -------- | ------------ | ---------------------------------- |
| dev      | void*        | Init()初始化设备接口返回的函数句柄 |
| nMode    | char         | 0x00：切换RGB<br />0x01：切换IR    |
| nMirror    | char       | 0x00：镜像<br />0x01：不镜像    |

4）返回值：

| 返回值 | 描述                  |
| ------ | --------------------- |
| < 0    | 请参考 接口异常返回值 |
| 0      | 处理成功              |
| 1      | 处理失败              |

## GetLuminousSensitivityThreshold()

1）功能说明：获取当前光敏值

2）函数原型：

```c++
int GetLuminousSensitivityThreshold(void* dev, uint* nThreshold);
```

3）参数：

| 参数名称   | 参数数据类型 | 参数描述                           |
| ---------- | ------------ | ---------------------------------- |
| dev        | void*        | Init()初始化设备接口返回的函数句柄 |
| nThreshold | uint*        | 当前光敏值                         |

4）返回值：

| 返回值 | 描述                  |
| ------ | --------------------- |
| < 0    | 请参考 接口异常返回值 |
| 0      | 处理成功              |
| 1      | 处理失败              |

## GetDeviceNoFlickerHz()

1）功能说明：获取视频画面抗闪烁状态

2）函数原型：

```c++
int GetDeviceNoFlickerHz(void* dev, char nCameraId, uchar* pHz, uchar* isEnable);
```

3）参数：

| 参数名称  | 参数数据类型 | 参数描述                                                   |
| --------- | ------------ | ---------------------------------------------------------- |
| dev       | void*        | Init()初始化设备接口返回的函数句柄                         |
| nCameraId | char         | 摄像头ID<br />0x00：id为0的摄像头<br />0x01：id为1的摄像头 |
| pHz       | uchar*       | 频率<br />0x00：50HZ<br />0x01：60HZ                       |
| isEnable  | uchar*       | 启用状态<br />0x00：关闭<br />0x01：开启                   |

4）返回值：

| 返回值 | 描述                  |
| ------ | --------------------- |
| < 0    | 请参考 接口异常返回值 |
| 0      | 处理成功              |
| 1      | 处理失败              |

## SetDeviceNoFlickerHz()

1）功能说明：设置抗闪烁状态 注：仅当前有效,重启无效

2）函数原型：

```c++
int SetDeviceNoFlickerHz(void* dev, char nCameraId, char nHz, char isEnable);
```

3）参数：

| 参数名称  | 参数数据类型 | 参数描述                                                     |
| --------- | ------------ | ------------------------------------------------------------ |
| dev       | void*        | Init()初始化设备接口返回的函数句柄                           |
| nCameraId | char         | 摄像头ID<br />0x00：id为0的摄像头  <br />0x01：id为1的摄像头 |
| nHz       | char         | 频率<br />0x00：50HZ  <br />0x01：60HZ                       |
| isEnable  | char         | 启用状态<br />0x00：关闭  <br />0x01：开启                   |

4）返回值：

| 返回值 | 描述                  |
| ------ | --------------------- |
| < 0    | 请参考 接口异常返回值 |
| 0      | 处理成功              |
| 1      | 处理失败              |

## SetResolution()

1）功能说明：设置视频分辨率	注：仅当前有效,重启无效

2）函数原型：

```c++
int SetResolution(void* dev, char nMode);
```

3）参数：

| 参数名称 | 参数数据类型 | 参数描述                                                     |
| -------- | ------------ | ------------------------------------------------------------ |
| dev      | void*        | Init()初始化设备接口返回的函数句柄                           |
| nMode    | char         | 画面尺寸<br />0x00：W720p*H1280p<br/>0x01：W360p*H640p<br/>0x02：W720p*H720p(only Wukong)<br/>0x03：W720p*H640p(only Wukong)<br/>0x04：W720p*H480p(only Wukong)<br />注：M20s ROM V3.0.4（含V3.0.4）以上版本nMode可设置0x02~0x04,M20  nMode不可设置0x02~0x04 ; M30不支持0x04：W720p*H480p|

4）返回值：

| 返回值 | 描述                                                         |
| ------ | ------------------------------------------------------------ |
| < 0    | 请参考 接口异常返回值<br />M20s ROM V3.0.4（含V3.0.4）以上版本若返回值为-6，属于正常情况，可视为处理成功，可断开串口和UVC连接，等待20秒重新连接串口和UVC |
| 0      | 处理成功                                                     |
| 1      | 处理失败                                                     |

## GetFrameRate()

1）功能说明：获取视频帧率

2）函数原型：

```c++
int GetFrameRate(void* dev, uint* pFrameRate);
```

3）参数：

| 参数名称   | 参数数据类型 | 参数描述                           |
| ---------- | ------------ | ---------------------------------- |
| dev        | void*        | Init()初始化设备接口返回的函数句柄 |
| pFrameRate | uint*        | 视频帧率                           |

4）返回值：

| 返回值 | 描述                  |
| ------ | --------------------- |
| < 0    | 请参考 接口异常返回值 |
| 0      | 处理成功              |
| 1      | 处理失败              |

## SetFrameRate()

1）功能说明：设置帧率

2）函数原型：

```c++
int SetFrameRate(void* dev, int nFrameRate);
```

3）参数：

| 参数名称   | 参数数据类型 | 参数描述                           |
| ---------- | ------------ | ---------------------------------- |
| dev        | void*        | Init()初始化设备接口返回的函数句柄 |
| nFrameRate | int          | 视频帧率 <br />帧率设置范围：10~25 |

4）返回值：

| 返回值 | 描述                  |
| ------ | --------------------- |
| < 0    | 请参考 接口异常返回值 |
| 0      | 成功                  |

## GetIRlight()

1）功能说明：获取IR灯亮度

2）函数原型：

```c++
int GetIRlight(void* dev, uchar* pLuminance,uchar* pCloseTime);
```

3）参数：

| 参数名称   | 参数数据类型 | 参数描述                           |
| ---------- | ------------ | ---------------------------------- |
| dev        | void*        | Init()初始化设备接口返回的函数句柄 |
| pLuminance | uchar*       | IR灯亮度                           |
| pCloseTime | uchar*       | IR灯自动关闭时间                   |

4）返回值：

| 返回值 | 描述                  |
| ------ | --------------------- |
| < 0    | 请参考 接口异常返回值 |
| 0      | 处理成功              |
| 1      | 处理失败              |

## SetIRlight()

1）功能说明：设置IR灯亮度	注：仅当前有效,重启无效

2）函数原型：

```c++
int SetIRlight(void* dev, uchar nLuminance, uchar nCloseTime);
```

3）参数：

| 参数名称   | 参数数据类型 | 参数描述                                                     |
| ---------- | ------------ | ------------------------------------------------------------ |
| dev        | void*        | Init()初始化设备接口返回的函数句柄                           |
| nLuminance | uchar        | IR灯亮度，0-200之间                                          |
| nCloseTime | uchar        | IR灯自动关闭时间,单位为秒, 范围0~120,即0x00~0x78,为0时即不执行检测行为，  最后一张人脸的检测时间开始计算, 最大误差1秒   设置值超范围时以极限值为准   默认值:30 |

4）返回值：

| 返回值 | 描述                  |
| ------ | --------------------- |
| < 0    | 请参考 接口异常返回值 |
| 0      | 处理成功              |
| 1      | 处理失败              |

# AI部分

| 函数                                                         | API描述                          |
| ------------------------------------------------------------ | -------------------------------- |
| int AddFace(void* dev, const void* pID, uint nIDLength);     | 模组抓拍入库                     |
| int AddFaceByImage(void* dev, const void*  pID, uint nIDLength, const void* pImage, uint nImageLength); | 上位机传入底图                   |
| int AddFaceReturnImage(void* dev, const  void* pID, uint nIDLength, void** ppImage, uint *pImageLength); | 模组抓拍入库并导底图             |
| int AddFaceSlice(void* dev, const void*  pID, uint nIDLength, uint nImageTotalLength, uint nPosition,int isLastSlice,  const void* pSliceData, uint nSliceDataLength); | 添加底库人脸数据(分片)           |
| int DeleteFace(void* dev, int nMode,  const void* pID = nullptr, uint nIDLength = 0); | 删除底库人脸数据                 |
| int QueryFace(void* dev, const void* pID, uint nIDLength, int nMode = 0); | 查询底库ID是否存在识别底库中     |
| int StaticFaceCompare(void* dev, void** ppResImage, uint* pResImageLength); | 静态比对（不分片）由模组抓拍导入 |
| int StaticFaceCompareReturnImage(void* dev, const void* pImage, uint nImageLength, void** ppResImage, uint* pResImageLength); | 静态比对（不分片）上位机导入图片 |
| int StaticFaceCompareSlice(void* dev, int nMode, uint nImageTotalLength, uint nPosition, int isLastSlice,const void* pSliceData, uint nSliceDataLength, void**  ppResImage, uint* pResImageLength); | 静态比对（分片）                 |
| int AddFeature(void* dev, const void* pID, uint nIDLength, const void* pFeature, uint nFeatureLength); | 使用特征值添加底库人脸数据       |
| int QueryFeature(void* dev, const void* pID, uint nIDLength, void* pFeature, uint nFeatureLength); | 根据底库ID查询特征值             |
| int StartOnetoNumRecognize(void* dev, int nRecMode,  int nMulMode); | 启动1:N人脸识别                  |
| int StartOnetoOneRecognize(void* dev, int nRecMode,  int nMulMode,  const void* pImage, uint nImageLength); | 启动1:1人脸识别（不分片）        |
| int StartOnetoOneRecognizeSlice(void*  dev, int nRecMode, int nMulMode, uint nImageTotalLength, uint nPosition,int  isLastSlice, const void* pSliceData, uint nSliceDataLength); | 启动1:1人脸识别（分片）          |
| int ResumeRecognize(void* dev);                              | 继续人脸识别                     |
| int PauseRecognize(void* dev);                               | 暂停人脸识别                     |
| int QueryRecognize(void* dev);                               | 查询人脸识别状态                 |
| int SetRecConfig(void* dev, const void* pData, uint nDataLength, int nConfigType = 0); | 设置人脸识别配置                 |
| int GetRecConfig(void* dev, void* pData, uint nDataLength, int nConfigType = 0); | 获取人脸识别配置                 |
| int OpenAutoUploadFaceInfoInFrame(void* dev);                | 识别结果插入帧数据打开           |
| int CloseAutoUploadFaceInfoInFrame(void* dev);               | 识别结果插入帧数据关闭           |
| int GetDeviceFaceID(void* dev, void* pIDList, uint nIDListLength); | 导出ID列表                       |
| int SetRecognizeCount(void* dev, uchar nRecCount,  uchar nLivingCount); | 设置识别次数                     |
| int GetRecognizeCount(void* dev, uchar* pRecCount, uchar* pLivingCount); | 获取识别次数                     |
| int SetTemplateUpdate(void* dev, uchar isUpdate);            | 设置模板更新                     |
| int GetTemplateUpdate(void* dev, uchar* isUpdate);           | 获取模板更新                     |
| int SetQRCodeSwitch(void* dev, uchar isOpen, uchar interval); | 二维码识别                       |
| int GetDeviceFaceLibraryNum(void* dev, uint *nFaceNum);      | 获取底库数量                     |
| int GetSingleRecognize(void* dev, void* pData, uint nDataLength); | 获取单次识别结果                 |
| void RegisterRecoReportCb(void* dev, CallBackPtr_t handler_func); | 识别结果上报                     |
| void RegisterTrackReportCb(void* dev, CallBackPtr_t handler_func); | 检测跟踪结果上报                 |
| void RegisterImageReportCb(void* dev, CallBackPtr_t handler_func); | 图片数据上报                     |
| void RegisterFeatureReportCb(void* dev, CallBackPtr_t handler_func); | 特征数据上报                     |
| void RegisterQRCodeReportCb(void* dev, CallBackPtr_t handler_func); | 二维码识别结果上报               |

## AddFace()

1）功能说明：模组抓拍入库。注：支持JPG、JEPG图片格式

2）函数原型：

```c++
int AddFace(void* dev, const void* pID, uint nIDLength);
```

3）参数：

| 参数名称  | 参数数据类型 | 参数描述                           |
| --------- | ------------ | ---------------------------------- |
| dev       | void*        | Init()初始化设备接口返回的函数句柄 |
| pID       | const void*  | 底库ID的数据                       |
| nIDLength | uint         | 底库ID的长度                       |

4）返回值：

| 返回值 | 描述                         |
| ------ | ---------------------------- |
| < 0    | 请参考 接口异常返回值        |
| 0x00   | 成功                         |
| 0x01   | 添加失败，无人脸             |
| 0x02   | 添加失败，多人脸             |
| 0x03   | 添加失败，脸太小             |
| 0x04   | 添加失败，Align分数低        |
| 0x05   | 添加失败，侧脸               |
| 0x06   | 添加失败，脸部模糊           |
| 0x07   | 添加失败，人脸太远           |
| 0x08   | 添加失败，识别初始化失败     |
| 0x09   | 添加失败，函数入参错误       |
| 0x0A   | 添加失败，特征值不存在       |
| 0x0B   | 添加失败，加密芯片错误       |
| 0x0C   | 添加失败，证书验证失败       |
| 0x0D   | 添加失败，不存在此ID         |
| 0x0E   | 添加失败，戴口罩入库失败     |
| 0x0F   | 添加失败，此产品底库已达上限 |
| 0x10   | 添加失败，ID无效             |
| 0x11   | 添加失败，文件保存失败       |
| 0x13   | 添加失败，RPC调用失败        |
| 0x14   | 添加失败，未知的TAG          |
| 0x15   | 添加失败，无效特征值         |
| 0x16   | 处理超时                     |
| 0x17   | 检测阈值低                   |
| 0x18   | 综合质量分数低               |
| 0x19   | 添加失败，无效文件           |
| 0x1a   | 图片数据无效                 |
| 0x1b   | 图片文件过大                 |
| 0x1c   | 无效文件名                   |
| 0x1d   | 服务未准备好                 |
| 0x1e   | 未知错误                     |
| 0x1f   | 处理失败                     |
| 0x20   | 不存在                       |
| 0x21   | 已存在                       |
| 0xA0   | 添加失败，AI服务未完成初始化 |
| 0xA1   | 内部错误                     |

## AddFaceWithQuality()

1）功能说明：模组抓拍入库，返回入库质量分数。注：支持JPG、JEPG图片格式

2）函数原型：

```c++
int AddFaceWithQuality(void* dev, const void* pID, uint nIDLength, void* pQuality, uint nQualityLength);
```

3）参数：

| 参数名称       | 参数数据类型 | 参数描述                           |
| -------------- | ------------ | ---------------------------------- |
| dev            | void*        | Init()初始化设备接口返回的函数句柄 |
| pID            | const void*  | 底库ID的数据                       |
| nIDLength      | uint         | 底库ID的长度                       |
| pQuality       | void*        | 质量分数数据，以json格式返回       |
| nQualityLength | uint         | 质量分数数据长度                   |

4）返回值：

| 返回值 | 描述                         |
| ------ | ---------------------------- |
| < 0    | 请参考 接口异常返回值        |
| 0x00   | 成功                         |
| 0x01   | 添加失败，无人脸             |
| 0x02   | 添加失败，多人脸             |
| 0x03   | 添加失败，脸太小             |
| 0x04   | 添加失败，Align分数低        |
| 0x05   | 添加失败，侧脸               |
| 0x06   | 添加失败，脸部模糊           |
| 0x07   | 添加失败，人脸太远           |
| 0x08   | 添加失败，识别初始化失败     |
| 0x09   | 添加失败，函数入参错误       |
| 0x0A   | 添加失败，特征值不存在       |
| 0x0B   | 添加失败，加密芯片错误       |
| 0x0C   | 添加失败，证书验证失败       |
| 0x0D   | 添加失败，不存在此ID         |
| 0x0E   | 添加失败，戴口罩入库失败     |
| 0x0F   | 添加失败，此产品底库已达上限 |
| 0x10   | 添加失败，ID无效             |
| 0x11   | 添加失败，文件保存失败       |
| 0x13   | 添加失败，RPC调用失败        |
| 0x14   | 添加失败，未知的TAG          |
| 0x15   | 添加失败，无效特征值         |
| 0x16   | 处理超时                     |
| 0x17   | 检测阈值低                   |
| 0x18   | 综合质量分数低               |
| 0x19   | 添加失败，无效文件           |
| 0x1a   | 图片数据无效                 |
| 0x1b   | 图片文件过大                 |
| 0x1c   | 无效文件名                   |
| 0x1d   | 服务未准备好                 |
| 0x1e   | 未知错误                     |
| 0x1f   | 处理失败                     |
| 0x20   | 不存在                       |
| 0x21   | 已存在                       |
| 0xA0   | 添加失败，AI服务未完成初始化 |
| 0xA1   | 内部错误                     |

## AddFaceByImage()

1）功能说明：上位机传入底图入库, 底图的高度和宽度均需小于1080p。注：支持JPG、JEPG图片格式;图片大小小于100K时使用此接口。

2）函数原型：

```c++
int AddFaceByImage(void* dev, const void* pID, uint nIDLength, const void* pImage, uint nImageLength);
```

3）参数：

| 参数名称     | 参数数据类型 | 参数描述                           |
| ------------ | ------------ | ---------------------------------- |
| dev          | void*        | Init()初始化设备接口返回的函数句柄 |
| pID          | const void*  | 底库ID的数据                       |
| nIDLength    | uint         | 底库ID的长度                       |
| pImage       | const void*  | 底库图片数据                       |
| nImageLength | uint         | 底库图片长度                       |

4）返回值：

| 返回值 | 描述                         |
| ------ | ---------------------------- |
| < 0    | 请参考 接口异常返回值        |
| 0x00   | 成功                         |
| 0x01   | 添加失败，无人脸             |
| 0x02   | 添加失败，多人脸             |
| 0x03   | 添加失败，脸太小             |
| 0x04   | 添加失败，Align分数低        |
| 0x05   | 添加失败，侧脸               |
| 0x06   | 添加失败，脸部模糊           |
| 0x07   | 添加失败，人脸太远           |
| 0x08   | 添加失败，识别初始化失败     |
| 0x09   | 添加失败，函数入参错误       |
| 0x0A   | 添加失败，特征值不存在       |
| 0x0B   | 添加失败，加密芯片错误       |
| 0x0C   | 添加失败，证书验证失败       |
| 0x0D   | 添加失败，不存在此ID         |
| 0x0E   | 添加失败，戴口罩入库失败     |
| 0x0F   | 添加失败，此产品底库已达上限 |
| 0x10   | 添加失败，ID无效             |
| 0x11   | 添加失败，文件保存失败       |
| 0x13   | 添加失败，RPC调用失败        |
| 0x14   | 添加失败，未知的TAG          |
| 0x15   | 添加失败，无效特征值         |
| 0x16   | 处理超时                     |
| 0x17   | 检测阈值低                   |
| 0x18   | 综合质量分数低               |
| 0x19   | 添加失败，无效文件           |
| 0x1a   | 图片数据无效                 |
| 0x1b   | 图片文件过大                 |
| 0x1c   | 无效文件名                   |
| 0x1d   | 服务未准备好                 |
| 0x1e   | 未知错误                     |
| 0x1f   | 处理失败                     |
| 0x20   | 不存在                       |
| 0x21   | 已存在                       |
| 0xA0   | 添加失败，AI服务未完成初始化 |
| 0xA1   | 内部错误                     |

## AddFaceByImageWithQuality()

1）功能说明：上位机传入底图入库, 底图的高度和宽度均需小于1080p，返回入库质量分数。注：支持JPG、JEPG图片格式;图片大小小于100K时使用此接口。

2）函数原型：

```c++
int AddFaceByImageWithQuality(void* dev, const void* pID, uint nIDLength, const void* pImage, uint nImageLength, void* pQuality, uint nQualityLength);
```

3）参数：

| 参数名称       | 参数数据类型 | 参数描述                           |
| -------------- | ------------ | ---------------------------------- |
| dev            | void*        | Init()初始化设备接口返回的函数句柄 |
| pID            | const void*  | 底库ID的数据                       |
| nIDLength      | uint         | 底库ID的长度                       |
| pImage         | const void*  | 底库图片数据                       |
| nImageLength   | uint         | 底库图片长度                       |
| pQuality       | void*        | 质量分数数据，以json格式返回       |
| nQualityLength | uint         | 质量分数数据长度                   |

4）返回值：

| 返回值 | 描述                         |
| ------ | ---------------------------- |
| < 0    | 请参考 接口异常返回值        |
| 0x00   | 成功                         |
| 0x01   | 添加失败，无人脸             |
| 0x02   | 添加失败，多人脸             |
| 0x03   | 添加失败，脸太小             |
| 0x04   | 添加失败，Align分数低        |
| 0x05   | 添加失败，侧脸               |
| 0x06   | 添加失败，脸部模糊           |
| 0x07   | 添加失败，人脸太远           |
| 0x08   | 添加失败，识别初始化失败     |
| 0x09   | 添加失败，函数入参错误       |
| 0x0A   | 添加失败，特征值不存在       |
| 0x0B   | 添加失败，加密芯片错误       |
| 0x0C   | 添加失败，证书验证失败       |
| 0x0D   | 添加失败，不存在此ID         |
| 0x0E   | 添加失败，戴口罩入库失败     |
| 0x0F   | 添加失败，此产品底库已达上限 |
| 0x10   | 添加失败，ID无效             |
| 0x11   | 添加失败，文件保存失败       |
| 0x13   | 添加失败，RPC调用失败        |
| 0x14   | 添加失败，未知的TAG          |
| 0x15   | 添加失败，无效特征值         |
| 0x16   | 处理超时                     |
| 0x17   | 检测阈值低                   |
| 0x18   | 综合质量分数低               |
| 0x19   | 添加失败，无效文件           |
| 0x1a   | 图片数据无效                 |
| 0x1b   | 图片文件过大                 |
| 0x1c   | 无效文件名                   |
| 0x1d   | 服务未准备好                 |
| 0x1e   | 未知错误                     |
| 0x1f   | 处理失败                     |
| 0x20   | 不存在                       |
| 0x21   | 已存在                       |
| 0xA0   | 添加失败，AI服务未完成初始化 |
| 0xA1   | 内部错误                     |

## AddFaceReturnImage()

1）功能说明：模组抓拍入库并导出底图，注：支持JPG、JEPG图片格式;ppImage指针返回后需由上位机释放内存

2）函数原型：

```c++
int AddFaceReturnImage(void* dev, const void* pID, uint nIDLength, void** ppImage, uint *pImageLength);
```

3）参数：

| 参数名称     | 参数数据类型 | 参数描述                           |
| ------------ | ------------ | ---------------------------------- |
| dev          | void*        | Init()初始化设备接口返回的函数句柄 |
| pID          | const void*  | 底库ID的数据                       |
| nIDLength    | uint         | 底库ID的长度                       |
| ppImage      | void**       | 底库图片数据                       |
| pImageLength | uint*        | 底库图片长度                       |

4）返回值：

| 返回值 | 描述                         |
| ------ | ---------------------------- |
| < 0    | 请参考 接口异常返回值        |
| 0x00   | 成功                         |
| 0x01   | 添加失败，无人脸             |
| 0x02   | 添加失败，多人脸             |
| 0x03   | 添加失败，脸太小             |
| 0x04   | 添加失败，Align分数低        |
| 0x05   | 添加失败，侧脸               |
| 0x06   | 添加失败，脸部模糊           |
| 0x07   | 添加失败，人脸太远           |
| 0x08   | 添加失败，识别初始化失败     |
| 0x09   | 添加失败，函数入参错误       |
| 0x0A   | 添加失败，特征值不存在       |
| 0x0B   | 添加失败，加密芯片错误       |
| 0x0C   | 添加失败，证书验证失败       |
| 0x0D   | 添加失败，不存在此ID         |
| 0x0E   | 添加失败，戴口罩入库失败     |
| 0x0F   | 添加失败，此产品底库已达上限 |
| 0x10   | 添加失败，ID无效             |
| 0x11   | 添加失败，文件保存失败       |
| 0x13   | 添加失败，RPC调用失败        |
| 0x14   | 添加失败，未知的TAG          |
| 0x15   | 添加失败，无效特征值         |
| 0x16   | 处理超时                     |
| 0x17   | 检测阈值低                   |
| 0x18   | 综合质量分数低               |
| 0x19   | 添加失败，无效文件           |
| 0x1a   | 图片数据无效                 |
| 0x1b   | 图片文件过大                 |
| 0x1c   | 无效文件名                   |
| 0x1d   | 服务未准备好                 |
| 0x1e   | 未知错误                     |
| 0x1f   | 处理失败                     |
| 0x20   | 不存在                       |
| 0x21   | 已存在                       |
| 0xA0   | 添加失败，AI服务未完成初始化 |
| 0xA1   | 内部错误                     |

## AddFaceReturnImageWithQuality()

1）功能说明：模组抓拍入库并导出底图，返回质量分数。注：支持JPG、JEPG图片格式;ppImage指针返回后需由上位机释放内存

2）函数原型：

```c++
int AddFaceReturnImageWithQuality(void* dev, const void* pID, uint nIDLength, void** ppImage, uint* pImageLength, void* pQuality, uint nQualityLength);
```

3）参数：

| 参数名称       | 参数数据类型 | 参数描述                           |
| -------------- | ------------ | ---------------------------------- |
| dev            | void*        | Init()初始化设备接口返回的函数句柄 |
| pID            | const void*  | 底库ID的数据                       |
| nIDLength      | uint         | 底库ID的长度                       |
| ppImage        | void**       | 底库图片数据                       |
| pImageLength   | uint*        | 底库图片长度                       |
| pQuality       | void*        | 质量分数数据，以json格式返回       |
| nQualityLength | uint         | 质量分数数据长度                   |

4）返回值：

| 返回值 | 描述                         |
| ------ | ---------------------------- |
| < 0    | 请参考 接口异常返回值        |
| 0x00   | 成功                         |
| 0x01   | 添加失败，无人脸             |
| 0x02   | 添加失败，多人脸             |
| 0x03   | 添加失败，脸太小             |
| 0x04   | 添加失败，Align分数低        |
| 0x05   | 添加失败，侧脸               |
| 0x06   | 添加失败，脸部模糊           |
| 0x07   | 添加失败，人脸太远           |
| 0x08   | 添加失败，识别初始化失败     |
| 0x09   | 添加失败，函数入参错误       |
| 0x0A   | 添加失败，特征值不存在       |
| 0x0B   | 添加失败，加密芯片错误       |
| 0x0C   | 添加失败，证书验证失败       |
| 0x0D   | 添加失败，不存在此ID         |
| 0x0E   | 添加失败，戴口罩入库失败     |
| 0x0F   | 添加失败，此产品底库已达上限 |
| 0x10   | 添加失败，ID无效             |
| 0x11   | 添加失败，文件保存失败       |
| 0x13   | 添加失败，RPC调用失败        |
| 0x14   | 添加失败，未知的TAG          |
| 0x15   | 添加失败，无效特征值         |
| 0x16   | 处理超时                     |
| 0x17   | 检测阈值低                   |
| 0x18   | 综合质量分数低               |
| 0x19   | 添加失败，无效文件           |
| 0x1a   | 图片数据无效                 |
| 0x1b   | 图片文件过大                 |
| 0x1c   | 无效文件名                   |
| 0x1d   | 服务未准备好                 |
| 0x1e   | 未知错误                     |
| 0x1f   | 处理失败                     |
| 0x20   | 不存在                       |
| 0x21   | 已存在                       |
| 0xA0   | 添加失败，AI服务未完成初始化 |
| 0xA1   | 内部错误                     |

## AddFaceSlice()

1）功能说明：uploadAddImageByPcSlice是通过分片（每片最大8080字节）方式传输大图数据（最大支持4M），类似分片上传升级包，类似uploadPackageSlice方式。 注 ：支持的JPG、JEPG图片格式;图片大小大于100K时使用此接口。

2）函数原型：

```c++
int AddFaceSlice(void* dev, const void* pID, uint nIDLength, uint nImageTotalLength, uint nPosition,int isLastSlice, const void* pSliceData, uint nSliceDataLength);
```

3）参数：

| 参数名称          | 参数数据类型 | 参数描述                                                     |
| ----------------- | ------------ | ------------------------------------------------------------ |
| dev               | void*        | Init()初始化设备接口返回的函数句柄                           |
| pID               | const void*  | 入库人脸ID                                                   |
| nIDLength         | uint         | 入库人脸ID长度                                               |
| nImageTotalLength | uint         | 整张图片数据长度。                                           |
| nPosition         | uint         | 该片数据起始位置（举例第一片从0开始，第二片是0加上第一片长度开始） |
| isLastSlice       | int          | 是否最后一片数据<br />0x00：否   <br />0x01：是              |
| pSliceData        | const  void* | 该片数据                                                     |
| nSliceDataLength  | uint         | 该片数据的长度                                               |

4）返回值：

| 返回值 | 描述                         |
| ------ | ---------------------------- |
| < 0    | 请参考 接口异常返回值        |
| 0x00   | 成功                         |
| 0x01   | 添加失败，无人脸             |
| 0x02   | 添加失败，多人脸             |
| 0x03   | 添加失败，脸太小             |
| 0x04   | 添加失败，Align分数低        |
| 0x05   | 添加失败，侧脸               |
| 0x06   | 添加失败，脸部模糊           |
| 0x07   | 添加失败，人脸太远           |
| 0x08   | 添加失败，识别初始化失败     |
| 0x09   | 添加失败，函数入参错误       |
| 0x0A   | 添加失败，特征值不存在       |
| 0x0B   | 添加失败，加密芯片错误       |
| 0x0C   | 添加失败，证书验证失败       |
| 0x0D   | 添加失败，不存在此ID         |
| 0x0E   | 添加失败，戴口罩入库失败     |
| 0x0F   | 添加失败，此产品底库已达上限 |
| 0x10   | 添加失败，ID无效             |
| 0x11   | 添加失败，文件保存失败       |
| 0x13   | 添加失败，RPC调用失败        |
| 0x14   | 添加失败，未知的TAG          |
| 0x15   | 添加失败，无效特征值         |
| 0x16   | 处理超时                     |
| 0x17   | 检测阈值低                   |
| 0x18   | 综合质量分数低               |
| 0x19   | 添加失败，无效文件           |
| 0x1a   | 图片数据无效                 |
| 0x1b   | 图片文件过大                 |
| 0x1c   | 无效文件名                   |
| 0x1d   | 服务未准备好                 |
| 0x1e   | 未知错误                     |
| 0x1f   | 处理失败                     |
| 0x20   | 不存在                       |
| 0x21   | 已存在                       |
| 0xA0   | 添加失败，AI服务未完成初始化 |
| 0xA1   | 内部错误                     |

## AddFaceSliceWithQuality()

1）功能说明：uploadAddImageByPcSlice是通过分片（每片最大8080字节）方式传输大图数据（最大支持4M），类似分片上传升级包，类似uploadPackageSlice方式。返回质量分数。 注 ：支持的JPG、JEPG图片格式;图片大小大于100K时使用此接口。

2）函数原型：

```c++
int AddFaceSliceWithQuality(void* dev, const void* pID, uint nIDLength, uint nImageTotalLength, uint nPosition,
        int isLastSlice, const void* pSliceData, uint nSliceDataLength, void* pQuality, uint nQualityLength);
```

3）参数：

| 参数名称          | 参数数据类型 | 参数描述                                                     |
| ----------------- | ------------ | ------------------------------------------------------------ |
| dev               | void*        | Init()初始化设备接口返回的函数句柄                           |
| pID               | const void*  | 入库人脸ID                                                   |
| nIDLength         | uint         | 入库人脸ID长度                                               |
| nImageTotalLength | uint         | 整张图片数据长度。                                           |
| nPosition         | uint         | 该片数据起始位置（举例第一片从0开始，第二片是0加上第一片长度开始） |
| isLastSlice       | int          | 是否最后一片数据<br />0x00：否   <br />0x01：是              |
| pSliceData        | const  void* | 该片数据                                                     |
| nSliceDataLength  | uint         | 该片数据的长度                                               |
| pQuality          | void*        | 质量分数数据，以json格式返回                                 |
| nQualityLength    | uint         | 质量分数数据长度                                             |

4）返回值：

| 返回值 | 描述                         |
| ------ | ---------------------------- |
| < 0    | 请参考 接口异常返回值        |
| 0x00   | 成功                         |
| 0x01   | 添加失败，无人脸             |
| 0x02   | 添加失败，多人脸             |
| 0x03   | 添加失败，脸太小             |
| 0x04   | 添加失败，Align分数低        |
| 0x05   | 添加失败，侧脸               |
| 0x06   | 添加失败，脸部模糊           |
| 0x07   | 添加失败，人脸太远           |
| 0x08   | 添加失败，识别初始化失败     |
| 0x09   | 添加失败，函数入参错误       |
| 0x0A   | 添加失败，特征值不存在       |
| 0x0B   | 添加失败，加密芯片错误       |
| 0x0C   | 添加失败，证书验证失败       |
| 0x0D   | 添加失败，不存在此ID         |
| 0x0E   | 添加失败，戴口罩入库失败     |
| 0x0F   | 添加失败，此产品底库已达上限 |
| 0x10   | 添加失败，ID无效             |
| 0x11   | 添加失败，文件保存失败       |
| 0x13   | 添加失败，RPC调用失败        |
| 0x14   | 添加失败，未知的TAG          |
| 0xA0   | 添加失败，AI服务未完成初始化 |

## DeleteFace()

1）功能说明：删除底库人脸数据

2）函数原型：

```c++
int DeleteFace(void* dev, int nMode, const void* pID = nullptr, uint nIDLength = 0);
```

3）参数：

| 参数名称  | 参数数据类型 | 参数描述                                                     |
| --------- | ------------ | ------------------------------------------------------------ |
| dev       | void*        | Init()初始化设备接口返回的函数句柄                           |
| nMode     | int          | 删除底库数据的方式<br />0x00：清空全部图片 ，参数pID，nIDLength属于默认参数，可不填 <br />0x01：删除某张图片，参数pID，nIDLength必须填写 |
| pID       | const void*  | 删除底库人脸数据的ID                                         |
| nIDLength | uint         | 删除底库人脸数据的ID的长度                                   |

4）返回值：

| 返回值 | 描述                  |
| ------ | --------------------- |
| < 0    | 请参考 接口异常返回值 |
| 0      | 成功                  |
| 1      | 图片ID不存在          |

## QueryFace()

1）功能说明：获取底库人脸ID

2）函数原型：

```c++
int QueryFace(void* dev, const void* pID, uint nIDLength, int nMode = 0);
```

3）参数：

| 参数名称  | 参数数据类型 | 参数描述                               |
| --------- | ------------ | -------------------------------------- |
| dev       | void*        | Init()初始化设备接口返回的函数句柄     |
| pID       | const void*  | 查询底库ID的数据                       |
| nIDLength | uint         | 查询底库的ID的长度                     |
| nMode     | int          | 查询底库的ID<br />0x00：根据ID查询底库 |

4）返回值：

| 返回值 | 描述                  |
| ------ | --------------------- |
| < 0    | 请参考 接口异常返回值 |
| 0      | 查询成功，ID存在      |
| 1      | 查询成功，ID不存在    |
| 2      | 查询失败              |
| 13     | 不存在此ID            |

## StaticFaceCompare()

1）功能说明：静态比对（不分片）由模组抓拍导入

2）函数原型：

```c++
int StaticFaceCompare(void* dev, void** ppResImage, uint* pResImageLength);
```

3）参数：

| 参数名称        | 参数数据类型 | 参数描述                                                     |
| --------------- | ------------ | ------------------------------------------------------------ |
| dev             | void*        | Init()初始化设备接口返回的函数句柄                           |
| ppResImage      | void**       | 对比结果数据，以json格式返回<br />比对成功时，json格式如：{"code":0,"uid":"666","score":0.96654461313}<br />比对失败时，json格式如：{"code":-4,"uid":"","score":0.000000} |
| pResImageLength | uint         | 对比结果数据长度<br />当库中ID数量为空时，虽然成功执行，但uid长度0 |

4）返回值：

| 返回值 | 描述                  |
| ------ | --------------------- |
| < 0    | 请参考 接口异常返回值 |
| 0      | 静态比对成功          |
| 1      | 静态比对失败          |
| 26     | 图片数据无效          |

## StaticFaceCompareReturnImage()

1）功能说明：静态比对（不分片）上位机导入图片。 注：图片大小小于300K时使用此接口

2）函数原型：

```c++
int StaticFaceCompareReturnImage(void* dev, const void* pImage, uint nImageLength, void** ppResImage, uint* pResImageLength);
```

3）参数：

| 参数名称        | 参数数据类型 | 参数描述                                                     |
| --------------- | ------------ | ------------------------------------------------------------ |
| dev             | void*        | Init()初始化设备接口返回的函数句柄                           |
| pImage          | const void*  | 导入的图片数据                                               |
| nImageLength    | uint         | 导入的图片数据长度                                           |
| ppResImage      | void**       | 对比结果数据，以json格式返回                                 |
| pResImageLength | uint         | 对比结果数据长度<br />当库中ID数量为空时，虽然能够成功执行，但结果长度0 |

4）返回值：

| 返回值 | 描述                  |
| ------ | --------------------- |
| < 0    | 请参考 接口异常返回值 |
| 0      | 静态比对成功          |
| 1      | 静态比对失败          |
| 26     | 图片数据无效          |

## StaticFaceCompareSlice()

1）功能说明：静态比对（分片） 注：图片大小大于300K时使用此接口

2）函数原型：

```c++
int StaticFaceCompareSlice(void* dev, int nMode, uint nImageTotalLength, uint nPosition, int isLastSlice,const void* pSliceData, uint nSliceDataLength, void** ppResImage, uint* pResImageLength);
```

3）参数：

| 参数名称          | 参数数据类型 | 参数描述                                                     |
| ----------------- | ------------ | ------------------------------------------------------------ |
| dev               | void*        | Init()初始化设备接口返回的函数句柄                           |
| nMode             | int          | 比对模式  <br />0x00：由模组抓拍导入<br />0x01：上位机导入图片 |
| nImageTotalLength | uint         | 导入的图片数据总长度                                         |
| nPosition         | uint         | 当前数据分片起始位                                           |
| isLastSlice       | int          | 是否是最后一个分片  <br />0x00：否<br />0x01：是             |
| pSliceData        | const  void* | 导入的图片数据                                               |
| nSliceDataLength  | uint         | 导入的图片数据长度                                           |
| ppResImage        | void**       | 对比结果数据，以json格式返回                                 |
| pResImageLength   | uint*        | 对比结果数据长度<br />当库中ID数量为空时，虽然成功执行，但结果长度0 |

4）返回值：

| 返回值 | 描述                  |
| ------ | --------------------- |
| < 0    | 请参考 接口异常返回值 |
| 0      | 静态比对成功          |
| 1      | 静态比对失败          |
| 26     | *图片数据无效*        |

## AddFeature()

1）功能说明：使用特征值添加底库人脸数据，根据底库ID和人脸特征值，将人脸信息录入到底库中。

2）函数原型：

```c++
int AddFeature(void* dev, const void* pID, uint nIDLength, const void* pFeature, uint nFeatureLength);
```

3）参数：

| 参数名称       | 参数数据类型 | 参数描述                                         |
| -------------- | ------------ | ------------------------------------------------ |
| dev            | void*        | Init()初始化设备接口返回的函数句柄               |
| pID            | const void*  | 底库ID的数据                                     |
| nIDLength      | uint         | 底库ID的长度                                     |
| pFeature       | const void*  | 特征数据                                         |
| nFeatureLength | uint         | 底库特征长度,固定值1384，传入其他长度直接返回 -4 |

4）返回值：

| 返回值 | 描述                  |
| ------ | --------------------- |
| < 0    | 请参考 接口异常返回值 |
| 0      | 处理成功              |
| 1      | 处理失败              |
| 10     | 特征值数据格式有误    |
| 33     | 特征ID已存在          |

## UpdateFeature()

1）功能说明：使用特征值更新底库人脸数据，根据底库ID和人脸特征值，更新相应id的底库特征。

2）函数原型：

```c++
int UpdateFeature(void* dev, const void* pID, uint nIDLength, const void* pFeature, uint nFeatureLength);
```

3）参数：

| 参数名称       | 参数数据类型 | 参数描述                                         |
| -------------- | ------------ | ------------------------------------------------ |
| dev            | void*        | Init()初始化设备接口返回的函数句柄               |
| pID            | const void*  | 底库ID的数据                                     |
| nIDLength      | uint         | 底库ID的长度                                     |
| pFeature       | const void*  | 特征数据                                         |
| nFeatureLength | uint         | 底库特征长度,固定值1384，传入其他长度直接返回 -4 |

4）返回值：

| 返回值 | 描述                  |
| ------ | --------------------- |
| < 0    | 请参考 接口异常返回值 |
| 0      | 处理成功              |
| 1      | 处理失败              |
| 10     | 特征值数据格式有误    |

## QueryFeature()

1）功能说明：根据底库ID查询特征值，使用底库ID，向搜索库中查询该人脸信息中的人脸特征值。注：图片、特征值、用户ID等敏感信息不能明文输出（以参数地址形式输出），其他如版本号、串口名等不变，还是明文输出（以参数内容形式输出）

2）函数原型：

```c++
int QueryFeature(void* dev, const void* pID, uint nIDLength, void* pFeature, uint nFeatureLength);
```

3）参数：

| 参数名称       | 参数数据类型 | 参数描述                                         |
| -------------- | ------------ | ------------------------------------------------ |
| dev            | void*        | Init()初始化设备接口返回的函数句柄               |
| pID            | const void*  | 底库的ID的数据                                   |
| nIDLength      | uint         | 底库的ID的长度                                   |
| pFeature       | void*        | 底库特征值的数据                                 |
| nFeatureLength | uint         | 底库特征值的长度<br />nFeatureLength一般可填2048 |

4）返回值：

| 返回值 | 描述                  |
| ------ | --------------------- |
| < 0    | 请参考 接口异常返回值 |
| 0      | 执行成功              |
| 1      | 执行失败              |
| 13     | 不存在此ID            |

## StartOnetoNumRecognize()

1）功能说明：启动1：N人脸识别

2）函数原型：

```c++
int StartOnetoNumRecognize(void* dev, int nRecMode, int nMulMode);
```

3）参数：

| 参数名称 | 参数数据类型 | 参数描述                                                     |
| -------- | ------------ | ------------------------------------------------------------ |
| dev      | void*        | Init()初始化设备接口返回的函数句柄                           |
| nRecMode | int          | 人脸识别/活体模式<br />0：只做识别模式<br />1：活体加识别模式 |
| nMulMode | int          | 单/多人脸模式<br />1：多人模式  <br />0：单人模式            |

4）返回值：

| 返回值 | 描述                  |
| ------ | --------------------- |
| < 0    | 请参考 接口异常返回值 |
| 0      | 启动成功              |
| 1      | 不支持此识别模式      |
| 2      | 识别库异常            |
| 3      | 不支持此人脸模式      |

## StartOnetoOneRecognize()

1）功能说明：启动1：1人脸识别（不分片），注：不分片API调用分片API能够解决不分片API状态码返回异常问题；图片大小300K以下使用不分片接口

2）函数原型：

```c++
int StartOnetoOneRecognize(void* dev, int nRecMode, int nMulMode, const void* pImage, uint nImageLength);
```

3）参数：

| 参数名称     | 参数数据类型 | 参数描述                                                     |
| ------------ | ------------ | ------------------------------------------------------------ |
| dev          | void*        | Init()初始化设备接口返回的函数句柄                           |
| nRecMode     | int          | 人脸识别/活体模式<br />0：只做识别模式<br />1：活体加识别模式 |
| nMulMode     | int          | 单/多人脸模式<br />1：多人模式  <br />0：单人模式            |
| pImage       | const void*  | 比对底库图片数据                                             |
| nImageLength | uint         | 比对底库图片长度                                             |

4）返回值：

| 返回值 | 描述                  |
| ------ | --------------------- |
| < 0    | 请参考 接口异常返回值 |
| 0      | 启动成功              |
| 1      | 不支持此识别模式      |
| 2      | 识别库异常            |
| 3      | 不支持此人脸模式      |

## StartOnetoOneRecognizeSlice()

1）功能说明：启动1:1人脸识别（分片）,开启1:1的识别模式，可动态切换。注： 图片大小300K以上时使用分片

2）函数原型：

```c++
int StartOnetoOneRecognizeSlice(void* dev, int nRecMode, int nMulMode, uint nImageTotalLength, uint nPosition,int isLastSlice, const void* pSliceData, uint nSliceDataLength);
```

3）参数：

| 参数名称          | 参数数据类型 | 参数描述                                                     |
| ----------------- | ------------ | ------------------------------------------------------------ |
| dev               | void*        | Init()初始化设备接口返回的函数句柄                           |
| nRecMode          | int          | 人脸识别/活体模式<br />0：只做识别模式<br />1：活体加识别模式 |
| nMulMode          | int          | 单/多人脸模式<br />1：多人模式  <br />0：单人模式            |
| nImageTotalLength | uint         | 比对底库图片总长度                                           |
| nPosition         | uint         | 当前数据分片起始位                                           |
| isLastSlice       | int          | 是否是最后一个分片  <br />0x00：否  <br />0x01：是           |
| pSliceData        | const  void* | 比对底库图片分片内容,分片不要超过8K                          |
| nSliceDataLength  | uint         | 比对底库图片分片内容长度                                     |

4）返回值：

| 返回值 | 描述                        |
| ------ | --------------------------- |
| < 0    | 请参考 接口异常返回值       |
| 0      | 启动成功                    |
| 1      | 不支持                      |
| 2      | 识别库异常                  |
| 3      | 不支持此人脸模式            |
| 4      | 参数 nImageTotalLength 过小 |

## StartOnetoOneRecognizeFeature()

1）功能说明：启动1：1人脸识别（输入特征）

2）函数原型：

```c++
int StartOnetoOneRecognizeFeature(void* dev, int nRecMode, int nMulMode, const void* pFeature, uint nFeatureLength);
```

3）参数：

| 参数名称       | 参数数据类型 | 参数描述                                                     |
| -------------- | ------------ | ------------------------------------------------------------ |
| dev            | void*        | Init()初始化设备接口返回的函数句柄                           |
| nRecMode       | int          | 人脸识别/活体模式<br />0：只做识别模式<br />1：活体加识别模式 |
| nMulMode       | int          | 单/多人脸模式<br />1：多人模式  <br />0：单人模式            |
| pFeature       | const void*  | 比对底库特征数据                                             |
| nFeatureLength | uint         | 比对底库特征长度                                             |

4）返回值：

| 返回值 | 描述                  |
| ------ | --------------------- |
| < 0    | 请参考 接口异常返回值 |
| 0      | 启动成功              |
| 1      | 不支持此识别模式      |
| 2      | 识别库异常            |
| 3      | 不支持此人脸模式      |

## ResumeRecognize()

1）功能说明：开启人脸识别

2）函数原型：

```c++
int ResumeRecognize(void* dev);
```

3）参数：

| 参数名称 | 参数数据类型 | 参数描述                           |
| -------- | ------------ | ---------------------------------- |
| dev      | void*        | Init()初始化设备接口返回的函数句柄 |

4）返回值：

| 返回值 | 描述                  |
| ------ | --------------------- |
| < 0    | 请参考 接口异常返回值 |
| 0      | 继续成功              |
| 1      | 继续失败              |

## PauseRecognize()

1）功能说明：暂停人脸识别

2）函数原型：

```c++
int PauseRecognize(void* dev);
```

3）参数：

| 参数名称 | 参数数据类型 | 参数描述                           |
| -------- | ------------ | ---------------------------------- |
| dev      | void*        | Init()初始化设备接口返回的函数句柄 |

4）返回值：

| 返回值 | 描述                  |
| ------ | --------------------- |
| < 0    | 请参考 接口异常返回值 |
| 0      | 暂停成功              |
| 1      | 暂停失败              |

## QueryRecognize()

1）功能说明：查询人脸识别状态

2）函数原型：

```c++
int QueryRecognize(void* dev);
```

3）参数：

| 参数名称 | 参数数据类型 | 参数描述                           |
| -------- | ------------ | ---------------------------------- |
| dev      | void*        | Init()初始化设备接口返回的函数句柄 |

4）返回值：

| 返回值 | 描述                                     |
| ------ | ---------------------------------------- |
| < 0    | 失败，一般是调用传入参数或者设备通讯异常 |
| 0      | 识别已开启                               |
| 1      | 识别已关闭                               |

## SetRecConfig()

1）功能说明：设置人脸识别配置

2）函数原型：

```c++
int SetRecConfig(void* dev, const void* pData, uint nDataLength, int nConfigType = 0);
```

3）参数：

| 参数名称    | 参数数据类型 | 参数描述                                     |
| ----------- | ------------ | -------------------------------------------- |
| dev         | void*        | Init()初始化设备接口返回的函数句柄           |
| pData       | const  void* | 配置字符串的数据(Json数据)                   |
| nDataLength | uint         | 配置字符串的长度                             |
| nConfigType | int          | 配置类型<br />0x00 算法配置  <br />0xxx 待续 |

4）返回值：

| 返回值 | 描述                  |
| ------ | --------------------- |
| < 0    | 请参考 接口异常返回值 |
| 0      | 设置成功              |
| 1      | 设置失败              |
| 9      | 参数异常              |

## GetRecConfig()

1）功能说明：获取人脸识别配置

2）函数原型：

```c++
int GetRecConfig(void* dev, void* pData, uint nDataLength, int nConfigType = 0);
```

3）参数：

| 参数名称    | 参数数据类型 | 参数描述                                                     |
| ----------- | ------------ | ------------------------------------------------------------ |
| dev         | void*        | Init()初始化设备接口返回的函数句柄                           |
| pData       | void*        | 配置字符串的数据(Json数据)                                   |
| nDataLength | uint         | 配置字符串的长度，一般可填2048                               |
| nConfigType | int          | 配置类型<br />0x00 算法配置  <br />0xxx 待续<br />默认值为 0x00 |

4）返回值：

| 返回值 | 描述                  |
| ------ | --------------------- |
| < 0    | 请参考 接口异常返回值 |
| 0      | 获取成功              |
| 1      | 获取失败              |
| 9      | 参数异常              |

## OpenAutoUploadFaceInfoInFrame()

1）功能说明：开启识别结果插入帧数据开关（调用该接口才能有人脸识别数据，getFrame函数才能获取到人脸识别信息）

2）函数原型：

```c++
int OpenAutoUploadFaceInfoInFrame(void* dev);
```

3）参数：

| 参数名称 | 参数数据类型 | 参数描述                           |
| -------- | ------------ | ---------------------------------- |
| dev      | void*        | Init()初始化设备接口返回的函数句柄 |

4）返回值：

| 返回值 | 描述                  |
| ------ | --------------------- |
| < 0    | 请参考 接口异常返回值 |
| 0      | 开启成功              |
| 1      | 开启失败              |

## CloseAutoUploadFaceInfoInFrame()

1）功能说明：关闭识别结果插入帧数据开关

2）函数原型：

```c++
int CloseAutoUploadFaceInfoInFrame(void* dev);
```

3）参数：

| 参数名称 | 参数数据类型 | 参数描述                           |
| -------- | ------------ | ---------------------------------- |
| dev      | void*        | Init()初始化设备接口返回的函数句柄 |

4）返回值：

| 返回值 | 描述                  |
| ------ | --------------------- |
| < 0    | 请参考 接口异常返回值 |
| 0      | 关闭成功              |
| 1      | 关闭失败              |

## GetDeviceFaceID()

1）功能说明：导出ID列表

2）函数原型：

```c++
int GetDeviceFaceID(void* dev, void* pIDList, uint nIDListLength);
```

3）参数：

| 参数名称      | 参数数据类型 | 参数描述                           |
| ------------- | ------------ | ---------------------------------- |
| dev           | void*        | Init()初始化设备接口返回的函数句柄 |
| pIDList       | void*        | ID列表数据内容                     |
| nIDListLength | uint         | ID列表数据长度                     |

4）返回值：

| 返回值 | 描述                  |
| ------ | --------------------- |
| < 0    | 请参考 接口异常返回值 |
| 0      | 处理成功              |
| 1      | 算法接口调用失败      |
| 2      | 文件长度获取失败      |
| 3      | 分片数据位置无效      |
| 4      | 文件读取失败          |

## SetRecognizeCount()

1）功能说明：设置识别次数

2）函数原型：

```c++
int SetRecognizeCount(void* dev, uchar nRecCount, uchar nLivingCount);
```

3）参数：

| 参数名称     | 参数数据类型 | 参数描述                           |
| ------------ | ------------ | ---------------------------------- |
| dev          | void*        | Init()初始化设备接口返回的函数句柄 |
| nRecCount    | uchar        | 1-10：识别次数，默认是10次。       |
| nLivingCount | uchar        | 1-10：活体次数，默认是10次。       |

4）返回值：

| 返回值    | 描述                  |
| --------- | --------------------- |
| < 0       | 请参考 接口异常返回值 |
| 0         | 设置成功              |
| 0x01~0x16 | 算法定义的错误        |

## GetRecognizeCount()

1）功能说明：获取识别次数

2）函数原型：

```c++
int GetRecognizeCount(void* dev, uchar* pRecCount, uchar* pLivingCount);
```

3）参数：

| 参数名称     | 参数数据类型 | 参数描述                           |
| ------------ | ------------ | ---------------------------------- |
| dev          | void*        | Init()初始化设备接口返回的函数句柄 |
| pRecCount    | uchar*       | 查询识别次数                       |
| pLivingCount | uchar*       | 查询活体次数                       |

4）返回值：

| 返回值    | 描述                  |
| --------- | --------------------- |
| < 0       | 请参考 接口异常返回值 |
| 0         | 查询成功              |
| 0x01~0x16 | 算法定义的错误        |

## SetTemplateUpdate()

1）功能说明：一个人做识别，是用现场图提的特征来对比库里面的特征，识别成功意思就是在库中找到一个高分数的特征。开启模板更新，会把现场图特征融合到这一底图特征；关闭模板更新就不会把现场图特征融合到底图特征。这样做好处是识别成功率会越来越好，缺点是如果一个人误识别，分数又很高，那么多次模板更新导致原来入库那个人反而不能识别了设置模板更新  注：每一次更新设置后，需要重启模组才能生效。

2）函数原型：

```c++
int SetTemplateUpdate(void* dev, uchar  isUpdate);
```

3）参数：

| 参数名称 | 参数数据类型 | 参数描述                                                     |
| -------- | ------------ | ------------------------------------------------------------ |
| dev      | void*        | Init()初始化设备接口返回的函数句柄                           |
| isUpdate | uchar        | 更新状态值<br />0x00：关闭更新 <br />0x01：开启更新<br />设置后必须重启模组生效 |

4）返回值：

| 返回值    | 描述                  |
| --------- | --------------------- |
| < 0       | 请参考 接口异常返回值 |
| 0         | 处理成功              |
| 0x01~0x16 | 算法定义的错误        |

## GetTemplateUpdate()

1）功能说明：获取模板更新

2）函数原型：

```c++
int GetTemplateUpdate(void* dev, uchar* isUpdate);
```

3）参数：

| 参数名称 | 参数数据类型 | 参数描述                                                     |
| -------- | ------------ | ------------------------------------------------------------ |
| dev      | void*        | Init()初始化设备接口返回的函数句柄                           |
| isUpdate | uchar*       | 返回查询是否模板更新，一个字节  0x00：关闭更新  0x01：开启更新 |

4）返回值：

| 返回值    | 描述                  |
| --------- | --------------------- |
| < 0       | 请参考 接口异常返回值 |
| 0         | 处理成功              |
| 0x01~0x16 | 算法定义的错误        |

## SetQRCodeSwitch()

1）功能说明：设置二维码识别参数

注：1.仅当前有效,重启无效

​        2.M20不支持设置二维码识别参数

2）函数原型：

```c++
int SetQRCodeSwitch(void* dev, uchar isOpen, uchar interval);
```

3）参数：

| 参数名称 | 参数数据类型 | 参数描述                                               |
| -------- | ------------ | ------------------------------------------------------ |
| dev      | void*        | Init()初始化设备接口返回的函数句柄                     |
| isOpen   | uchar        | 二维码识别功能开关  <br />0x00: 关闭  <br />0x01: 开启 |
| interval | uchar        | 设置识别上报间隔<br />默认值为5秒                      |

4）返回值：

| 返回值 | 描述                  |
| ------ | --------------------- |
| < 0    | 请参考 接口异常返回值 |
| 0      | 处理成功              |
| 1      | 处理失败              |

## GetDeviceFaceLibraryNum()

1）功能说明：获取底库数量

2）函数原型：

```c++
int GetDeviceFaceLibraryNum(void* dev, uint *nFaceNum);
```

3）参数：

| 参数名称 | 参数数据类型 | 参数描述                           |
| -------- | ------------ | ---------------------------------- |
| dev      | void*        | Init()初始化设备接口返回的函数句柄 |
| nFaceNum | uint         | 查询到的底库数量                   |

4）返回值：

| 返回值 | 描述                  |
| ------ | --------------------- |
| < 0    | 请参考 接口异常返回值 |
| 0      | 查询成功              |
| 1      | 查询失败              |

## GetSingleRecognize()

1）功能说明：获取单次识别结果；若在视频中检测到了人脸，则返回识别结果；若在视频未检测到人脸，则返回的字符串为空

2）函数原型：

```c++
int GetSingleRecognize(void* dev, void* pData, uint nDataLength);
```

3）参数：

| 参数名称    | 参数数据类型 | 参数描述                           |
| ----------- | ------------ | ---------------------------------- |
| dev         | void*        | Init()初始化设备接口返回的函数句柄 |
| pData       | void*        | 识别结果，数据格式是Json数据       |
| nDataLength | uint         | 识别结果字符串长度，一般可填1024   |

4）返回值：

| 返回值 | 描述                  |
| ------ | --------------------- |
| < 0    | 请参考 接口异常返回值 |
| 0      | 获取成功              |
| 1      | 获取失败              |

## RegisterRecoReportCb()

1）功能说明：注册回调上报识别函数（该函数是主动上报，回调获取识别结果数据，注意可以参考demo中的getReoReportDataHandle回调函数源码。）

2）函数原型：

```c++
void  RegisterRecoReportCb(void* dev, CallBackPtr_t handler_func);
```

3）参数：

| 参数名称     | 参数数据类型  | 参数描述                           |
| ------------ | ------------- | ---------------------------------- |
| dev          | void*         | Init()初始化设备接口返回的函数句柄 |
| handler_func | CallBackPtr_t | 回调函数的句柄                     |

4）返回值：无

## RegisterTrackReportCb()

1）功能说明：注册回调上报跟踪函数（该函数是主动上报，回调获取跟踪结果数据，注意可以参考demo中的getReoTrackHandle回调函数源码。）

2）函数原型：

```c++
void  RegisterTrackReportCb(void* dev, CallBackPtr_t handler_func);
```

3）参数：

| 参数名称     | 参数数据类型  | 参数描述                           |
| ------------ | ------------- | ---------------------------------- |
| dev          | handle*       | Init()初始化设备接口返回的函数句柄 |
| handler_func | CallBackPtr_t | 回调函数的句柄                     |

4）返回值：无

## RegisterImageReportCb()

1）功能说明：注册回调上报图片函数（该函数是主动上报，回调获取识别图片结果数据，注意可以参考demo中的getReoImageHandle回调函数源码。）

2）函数原型：

```c++
void  RegisterImageReportCb(void* dev, CallBackPtr_t handler_func);
```

3）参数：

| 参数名称     | 参数数据类型  | 参数描述                           |
| ------------ | ------------- | ---------------------------------- |
| dev          | void*         | Init()初始化设备接口返回的函数句柄 |
| handler_func | CallBackPtr_t | 回调函数的句柄                     |

4）返回值：无

## RegisterFeatureReportCb()

1）功能说明：注册回调上报特征值函数（该函数是主动上报，回调获取识别特征值结果数据，注意可以参考demo中的getReoFeatureHandle回调函数源码。）注意：当模组识别结果过多时，部分识别特征值会不上报，所以前面开启主动上报开关函数openAutoUploadAiInfo参数建议为mode为0x02，并且demo调用设置也是。

2）函数原型：

```c++
void  RegisterFeatureReportCb(void* dev, CallBackPtr_t handler_func);
```

3）参数：

| 参数名称     | 参数数据类型  | 参数描述                           |
| ------------ | ------------- | ---------------------------------- |
| dev          | void*         | Init()初始化设备接口返回的函数句柄 |
| handler_func | CallBackPtr_t | 回调函数的句柄                     |

4）返回值：无

## RegisterQRCodeReportCb()

1）功能说明：注册回调上报二维码函数（该函数是主动上报，回调获取识别二维码结果数据，注意可以参考demo中的getQRCodeReportHandle回调函数源码。）注意：当调用SetQRCodeSwitch函数开启二维码上报开关，回调函数才可接收到二维码结果数据；M20不支持二维码结果数据上报

2）函数原型：

```c++
 void  RegisterQRCodeReportCb(void* dev, CallBackPtr_t handler_func);
```

3）参数：

| 参数名称     | 参数数据类型  | 参数描述                           |
| ------------ | ------------- | ---------------------------------- |
| dev          | void*         | Init()初始化设备接口返回的函数句柄 |
| handler_func | CallBackPtr_t | 回调函数的句柄                     |

4）返回值：无

视频帧验证信息示例：

```c++
{
    "track_info": [
        {
            "recognition_id": "UNKNOWN",
            "recognition_status": 0,
            "mask_sign": -1,
            "safety_hat": -1,
            "face_info": {
                "rect": {
                    "bottom": 611,
                    "left": 143,
                    "right": 657,
                    "top": 111
                },
                "headpose": {
                    "yaw": 0.640000,
                    "pitch": 4.160000,
                    "roll": -4.410000
                },
                "track_id": 3
            }
        }
    ]
}
```

| track_info (识别结果) | 描述                                                         | 备注                                                         |
| --------------------- | ------------------------------------------------------------ | ------------------------------------------------------------ |
| recognition_status    | 识别状态                                                     | 可能的值为0，1，2，3，4                                      |
| liveness_score        | 活体匹配分值                                                 | 只有识别成功后会出现                                         |
| recognize_score       | 识别匹配分值                                                 | 只有识别成功后会出现                                         |
| face_info             | 人脸信息                                                     | 包括rect (脸部坐标)，track_id (人脸追踪ID)，headpose(人脸角度) |
| mask_sign             | 是否戴口罩：  -1 未判断是否戴口罩    1 判断未戴口罩  2  判断戴了口罩  3 判断戴了口罩，但口罩未戴整齐 | 需要setReoconfig设置。如果enable_mask_sign设置为false则mask_sign一直会为-1。如果开启口罩检测，建议以有识别分数和活体分数项的json为准，不以未带识别分数与活体分数项的追踪结果的json为准。可以参考demo源码 |
| safety_hat            | 是否戴安全帽                                                 | 不推荐开启安全帽检测，默认关闭                               |

# 设备部分

| 函数                                                         | API描述            |
| ------------------------------------------------------------ | ------------------ |
| int Ping(void* dev, const void* pTestData, uint nTestDataLength); | 设备连通性测试     |
| int UploadPackageSlice(void* dev, uint nPosition,  const void* pPacketData, uint nPacketDataLength); | 固件升级包上传     |
| int GetDevModelAppVer(void* dev, void* pModelVersion, uint nModelVersionLength); | 获取模组硬件版本号 |
| int ApplyUpgrade(void* dev, const void* pHashData,  uint nHashDataLength); | 固件升级包应用     |
| int GetDeviceVersion(void* dev, void* pVersion, uint nLength); | 查询系统版本号     |
| int Recovery(void* dev, int nMode);                          | 恢复出厂设置       |
| int GetDevSn(void* dev, char nMode, void* pDevSn, uint nDevsnLength); | 获取设备SN号       |
| int GetDevModel(void* dev, void* pDevModel, uint nDevModelLength); | 获取设备型号       |
| int GetCpuTemperature(void* dev, uint* nTemperature);        | 查询CPU温度        |
| int GetAESensorModel(void* dev, uint* pSensorModel);         | 查询镜头sensor类型 |
| int CloseAutoUploadAiInfo(void* dev);                        | 主动上报数据关闭   |
| int OpenAutoUploadAiInfo(void* dev, char nUploadMode,char nImageMode); | 主动上报数据打开   |

## Ping()

1）功能说明：设备连通性测试

2）函数原型：

```c++
int Ping(void* dev, const void* pTestData, uint nTestDataLength);
```

3）参数：

| 参数名称        | 参数数据类型 | 参数描述                           |
| --------------- | ------------ | ---------------------------------- |
| dev             | void*        | Init()初始化设备接口返回的函数句柄 |
| pTestData       | const void*  | 发送到设备的n个随机字节            |
| nTestDataLength | uint         | 发送到设备的n个随机字节长度        |

4）返回值：

| 返回值 | 描述                  |
| ------ | --------------------- |
| < 0    | 请参考 接口异常返回值 |
| 0      | 成功                  |

## UploadPackageSlice()

1）功能说明：开始上传升级包,该函数将启动一个新的线程用于上传，该函数内部发生内存拷贝，返回后可立即传入数据。

2）函数原型：

```c++
int UploadPackageSlice(void* dev, uint nPosition, const void* pPacketData, uint nPacketDataLength);
```

3）参数：

| 参数名称          | 参数数据类型 | 参数描述                                                     |
| ----------------- | ------------ | ------------------------------------------------------------ |
| dev               | void*        | Init()初始化设备接口返回的函数句柄                           |
| nPosition         | uint         | 当前片数据片的起始位置，比如第一片为0，第二片为0加第一片长度。具体请参考demo部分调用。 |
| pPacketData       | const void*  | 升级包的数据                                                 |
| nPacketDataLength | uint         | 数据的长度,建议分片不要超过8K长度                            |

4）返回值：

| 返回值 | 描述                  |
| ------ | --------------------- |
| < 0    | 请参考 接口异常返回值 |
| 0      | 处理成功              |
| 1      | 处理失败              |

## GetDevModelAppVer()

1）功能说明：获取模组硬件版本号

2）函数原型：

```c++
int GetDevModelAppVer(void* dev, void* pModelVersion, uint nModelVersionLength);
```

3）参数：

| 参数名称            | 参数数据类型 | 参数描述                           |
| ------------------- | ------------ | ---------------------------------- |
| dev                 | void*        | Init()初始化设备接口返回的函数句柄 |
| pModelVersion       | void*        | 版本号数据                         |
| nModelVersionLength | uint         | 版本号数据长度，一般可填1024       |

4）返回值：

| 返回值 | 描述                  |
| ------ | --------------------- |
| < 0    | 请参考 接口异常返回值 |
| 0      | 获取成功              |
| 1      | 获取失败              |

## SetDeviceName()

1）功能说明：设置模组名称

2）函数原型：

```c++
int SetDeviceName(void* dev, const void* pData, uint nDataLength);
```

3）参数：

| 参数名称    | 参数数据类型 | 参数描述                           |
| ----------- | ------------ | ---------------------------------- |
| dev         | void*        | Init()初始化设备接口返回的函数句柄 |
| pData       | void*        | 设备名称                           |
| nDataLength | uint         | 设备名称长度，长度应小于50         |

4）返回值：

| 返回值 | 描述                  |
| ------ | --------------------- |
| < 0    | 请参考 接口异常返回值 |
| 0      | 获取成功              |
| 1      | 获取失败              |

## GetDeviceName()

1）功能说明：获取模组名称

2）函数原型：

```c++
int GetDeviceName(void* dev, void* pDeviceName, uint nDeviceNameLength);
```

3）参数：

| 参数名称          | 参数数据类型 | 参数描述                           |
| ----------------- | ------------ | ---------------------------------- |
| dev               | void*        | Init()初始化设备接口返回的函数句柄 |
| pDeviceName       | void*        | 设备名称，默认设备名称为设备SN号   |
| nDeviceNameLength | uint         | 设备名称长度                       |

4）返回值：

| 返回值 | 描述                  |
| ------ | --------------------- |
| < 0    | 请参考 接口异常返回值 |
| 0      | 获取成功              |
| 1      | 获取失败              |

## ApplyUpgrade()

1）功能说明：固件升级包应用。注意：请将传入的md5值转为hex并保持小写，否则设备将不能识别。

2）函数原型：

```c++
int ApplyUpgrade(void* dev, const void* pHashData, uint nHashDataLength);
```

3）参数：

| 参数名称        | 参数数据类型 | 参数描述                             |
| --------------- | ------------ | ------------------------------------ |
| dev             | void*        | Init()初始化设备接口返回的函数句柄   |
| pHashData       | const void*  | 升级包的MD5值                        |
| nHashDataLength | uint         | 升级包的MD5加密数据长度，一般可填128 |

4）返回值：

| 返回值 | 描述                  |
| ------ | --------------------- |
| < 0    | 请参考 接口异常返回值 |
| 0      | 应用成功              |
| 1      | MD5值不匹配           |
| 2      | 非此设备固件          |

## GetDeviceVersion()

1）功能说明：查询系统版本信息

2）函数原型：

```c++
int GetDeviceVersion(void* dev, void* pVersion, uint nLength);
```

3）参数：

| 参数名称 | 参数数据类型 | 参数描述                           |
| -------- | ------------ | ---------------------------------- |
| dev      | void*        | Init()初始化设备接口返回的函数句柄 |
| pVersion | void*        | 获取的系统版本信息                 |
| nLength  | uint         | 系统版本信息长度                   |

4）返回值：

| 返回值 | 描述                  |
| ------ | --------------------- |
| < 0    | 请参考 接口异常返回值 |
| 0      | 查询成功              |
| 1      | 查询失败              |

## Recovery()

1）功能说明：恢复出厂设置

2）函数原型：

```c++
int Recovery(void* dev, int nMode);
```

3）参数：

| 参数名称 | 参数数据类型 | 参数描述                                                 |
| -------- | ------------ | -------------------------------------------------------- |
| dev      | void*        | Init()初始化设备接口返回的函数句柄                       |
| nMode    | int          | 处理方式<br />0x00：清空用户配置<br />0x01：保存用户配置 |

4）返回值：

| 返回值 | 描述                  |
| ------ | --------------------- |
| < 0    | 请参考 接口异常返回值 |
| 0      | 处理成功              |
| 1      | 处理失败              |

## Reset()

1）功能说明：重启设备

2）函数原型：

```c++
int Reset(void* dev);
```

3）参数：

| 参数名称 | 参数数据类型 | 参数描述                           |
| -------- | ------------ | ---------------------------------- |
| dev      | void*        | Init()初始化设备接口返回的函数句柄 |

4）返回值：

| 返回值 | 描述                  |
| ------ | --------------------- |
| < 0    | 请参考 接口异常返回值 |
| 0      | 处理成功              |
| 9      | 参数错误              |
| 其他   | 处理错误              |

## GetDevSn()

1）功能说明：获取设备SN号

2）函数原型：

```c++
int GetDevSn(void* dev, char nMode, void* pDevSn, uint nDevsnLength);
```

3）参数：

| 参数名称     | 参数数据类型 | 参数描述                               |
| ------------ | ------------ | -------------------------------------- |
| dev          | void*        | Init()初始化设备接口返回的函数句柄     |
| nMode        | char         | SN类型<br />0x00：PCB<br/>0x01：Device |
| pDevSn       | void*        | SN号                                   |
| nDevsnLength | uint         | SN号的长度                             |

4）返回值：

| 返回值 | 描述                                     |
| ------ | ---------------------------------------- |
| < 0    | 失败，一般是调用传入参数或者设备通讯异常 |
| 0      | 获取成功                                 |
| 1      | 获取失败                                 |

## GetDevModel()

1）功能说明：获取设备型号

2）函数原型：

```c++
int GetDevModel(void* dev, void* pDevModel, uint nDevModelLength);
```

3）参数：

| 参数名称        | 参数数据类型 | 参数描述                           |
| --------------- | ------------ | ---------------------------------- |
| dev             | void*        | Init()初始化设备接口返回的函数句柄 |
| pDevModel       | void*        | 设备型号                           |
| nDevModelLength | uint         | 设备型号的长度                     |

4）返回值：

| 返回值 | 描述                  |
| ------ | --------------------- |
| < 0    | 请参考 接口异常返回值 |
| 0      | 获取成功              |
| 1      | 获取失败              |

## GetCpuTemperature()

1）功能说明：查询CPU温度

2）函数原型：

```c++
int GetCpuTemperature(void* dev, uint* nTemperature);
```

3）参数：

| 参数名称     | 参数数据类型 | 参数描述                           |
| ------------ | ------------ | ---------------------------------- |
| dev          | void*        | Init()初始化设备接口返回的函数句柄 |
| nTemperature | uint         | CPU温度                            |

4）返回值：

| 返回值 | 描述                  |
| ------ | --------------------- |
| < 0    | 请参考 接口异常返回值 |
| 0      | 获取成功              |
| 1      | 获取失败              |

## GetAESensorModel()

1）功能说明：查询镜头sensor类型

​		注：M20 ROM2.6.16（包含2.6.16）之后的版本才能查询镜头sensor类型

​                M20s不支持查询镜头sensor类型

2）函数原型：

```c++
int GetAESensorModel(void* dev, uint* pSensorModel);
```

3）参数：

| 参数名称     | 参数数据类型 | 参数描述                                                     |
| ------------ | ------------ | ------------------------------------------------------------ |
| dev          | void*        | Init()初始化设备接口返回的函数句柄                           |
| pSensorModel | uint*        | 0x0: 未知sensor<br/>0x2238: sensor 2315E<br/>0xCB14: sensor 2335 |

4）返回值：

| 返回值 | 描述                  |
| ------ | --------------------- |
| < 0    | 请参考 接口异常返回值 |
| 0      | 处理成功              |
| 1      | 处理失败              |

## CloseAutoUploadAiInfo()

1）功能说明：关闭识别结果串口数据主动上报开关（调用该接口会关闭人脸识别数据上报，对应参考注册回调函数registerRecoReportCb、registerTrackReportCb、registerImageReportCb、registerFeatureReportCb）

2）函数原型：

```c++
int CloseAutoUploadAiInfo(void* dev);
```

3）参数：

| 参数名称 | 参数数据类型 | 参数描述                           |
| -------- | ------------ | ---------------------------------- |
| dev      | void*        | Init()初始化设备接口返回的函数句柄 |

4）返回值：

| 返回值 | 描述                  |
| ------ | --------------------- |
| < 0    | 请参考 接口异常返回值 |
| 0      | 处理成功              |
| 1      | 处理失败              |

## OpenAutoUploadAiInfo()

1）功能说明：开启识别结果串口数据主动上报开关（调用该接口会有人脸识别数据上报，对应参考注册回调函数registerRecoReportCb、registerTrackReportCb、registerImageReportCb、registerFeatureReportCb）。

说明如果不需要上报识别图片、识别特征值，建议不开启该主动上报，只需要开启帧数据上报openAutoUploadFaceInfoInFrame。

调用此接口，接口GetFrame(void* dev, char* imageBuf, int imageSize, char* verifyBuf, int verifySize)中的verifyBuf参数会输出验证信息

2）函数原型：

```c++
int OpenAutoUploadAiInfo(void* dev, char nUploadMode,char nImageMode);
```

3）参数：

| 参数名称    | 参数数据类型 | 参数描述                                                     |
| ----------- | ------------ | ------------------------------------------------------------ |
| dev         | void*        | Init()初始化设备接口返回的函数句柄                           |
| nUploadMode | char         | 0x00: 上报所有信息<br />0x02: 上报图片与识别 （建议设置该参数，demo中也是使用该参数，因为特征值数据在识别结果过多时会不上报一部分）<br />0x03: 上报特征值与识别<br />0x04: 上报识别 |
| nImageMode  | char         | 0x00：RGB人脸，RGB背景，IR图都不上报。<br />0x01：只上报RGB人脸图数据。<br />0x02：只上报RGB背景图数据。<br />0x03：上报RGB人脸与RGB背景图。<br />0x04：只上报IR图数据。<br />0x05：上报IR图与RGB人脸图。<br />0x06：上报IR图与RGB背景图。<br />0x07：上报RGB人脸，RGB背景，IR图数据。 |

4）返回值：

| 返回值 | 描述                  |
| ------ | --------------------- |
| < 0    | 请参考 接口异常返回值 |
| 0      | 处理成功              |
| 1      | 处理失败              |

# 接口异常返回值

| 返回值 | 错误码定义                   | 描述                   | 产生原因                                                     |
| ------ | ---------------------------- | ---------------------- | ------------------------------------------------------------ |
| -1     | AC_ERR_NOT_INIT              | 未初始化               | 调用其他接口之前，未调用以下接口： <br />1.未初始化接口  Init() <br />2.调用设置&AI&设备接口未连接串口 ConnectSerial() <br />3.调用媒体接口未连接UVC  ConnectCamera() |
| -2     | AC_ERR_INIT_FAIL             | 初始化失败             | 1.打开串口失败 ConnectSerial() <br />2.打开UVC失败 ConnectCamera() |
| -3     | AC_ERR_ALREADY_INIT          | 重复初始化             | 1.重复调用初始化接口  Init() <br />2.重复调用连接串口接口 ConnectSerial() <br />3.重复调用连接UVC接口  ConnectCamera() |
| -4     | AC_ERR_INPUT_ARG             | 输入参数异常           | 1.输入参数越界 <br />2.指针参数为NULL<br />3.int类型变量值太小 |
| -5     | AC_ERR_OUTPUT_ARG            | 输出参数异常           | 指针参数为NULL                                               |
| -6     | AC_ERR_COM_TIMEOUT           | 串口通讯超时           | 下位机未对上位机请求进行回复                                 |
| -7     | AC_ERR_TLV_FORMAT            | TLV数据格式异常        | 下位机回复数据格式异常                                       |
| -8     | AC_ERR_TLV_LENGTH            | TLV数据长度异常        | 下位机回复长度格式异常                                       |
| -9     | AC_ERR_CALLBACK_REGISTERED   | 回调函数已注册         | 回调函数被重复注册                                           |
| -10    | AC_ERR_UVC_CONNECT           | 摄像头连接异常         | 1.设备未连接 <br />2.连接UVC设备名称有误                     |
| -11    | AC_ERR_UVC_NEWFRAME_UNARRIVE | 摄像头新的视频帧未到达 | GetFrame()返回此返回值属正常现象，代表未获取到新的视频帧     |
| -12    | AC_ERR_SERIAL_CONNECT        | 串口连接异常           | 1.设备未连接 <br />2.连接串口设备名称有误                    |

# 附件

## SetReoconfig jsonData

功能：设置ai服务的配置信息

jsonData的数据结构

```json
{
    "ae_flicker_freq": 0,
    "ae_mode": 1,
    "db_quality_param": {
        "align_confidence": 0.4000000059604645,
        "blur": 0.699999988079071,
        "detect_confidence": 0.30000001192092896,
        "face_size_min": 100,
        "pitch_max": 30.000999450683594,
        "pitch_min": -30.000999450683594,
        "roll_max": 30.000999450683594,
        "roll_min": -30.000999450683594,
        "sum_quality": 0.30000001192092896,
        "yaw_max": 30.000999450683594,
        "yaw_min": -30.000999450683594
    },
    "enable_db_mask_sign": false,
    "enable_extra_attribute": false,
    "enable_feature_export": true,
    "enable_image_export": true,
    "enable_mask_sign": true,
    "enable_qr_code": false,
    "enable_safety_hat": false,
    "enable_track_box": true,
    "face_mode": 1,
    "face_size": 30,
    "liveness_thresh": 0.9800000190734863,
    "max_face_cnt": 4,
    "recognition_interval": 5,
    "recognition_thresh": 0.8999999761581421,
    "recognize_mode": 1,
    "recognize_quality_param": {
        "align_confidence": 0.4000000059604645,
        "blur": 0.699999988079071,
        "detect_confidence": 0.30000001192092896,
        "face_size_min": 100,
        "pitch_max": 30.000999450683594,
        "pitch_min": -30.000999450683594,
        "roll_max": 30.000999450683594,
        "roll_min": -30.000999450683594,
        "sum_quality": 0.30000001192092896,
        "yaw_max": 30.000999450683594,
        "yaw_min": -30.000999450683594
    },
    "report_interval": 5,
    "temper_strategy": [
        {
            "freq": 1400,
            "temper": 80
        },
        {
            "freq": 1200,
            "temper": 88
        },
        {
            "freq": 1000,
            "temper": 96
        },
        {
            "freq": 800,
            "temper": 100
        }
    ],
    "track_fps": 25,
    "verify_thresh": 0.8999999761581421,
    "work_mode": 0
}
```

| 参数名                  | 参数类型   | 参数范围及默认值                                             |
| ----------------------- | ---------- | ------------------------------------------------------------ |
| work_mode               | enum(枚举) | 工作模式<br />0：1:N的搜索<br />1：1:1的认证<br />默认值为 0 |
| recognize_mode          | enum       | 识别模式<br />0：只做识别<br />1：做识别和活体<br />2：只做活体检测<br />默认值为1 |
| face_mode               | enum       | 人脸模式<br />0：单人脸<br />1：多人脸<br />默认值为0        |
| enable_qr_code          | Boolean    | 开启二维码识别方式<br />false：不开启二维码识别方式<br />true： 开启二维码识别方式<br />此参数不起作用，若要开启二维码识别功能，请使用SetQRCoreSwitch接口进行设置<br />默认值：false <br>注:M30该字段功能无效 |
| enable_track_box        | Boolean    | 开启track反馈框<br />false：不开启track反馈框<br />true： 开启track反馈框<br />默认值：true |
| liveness_thresh         | Float      | 活体阈值，取值0—1<br />默认值：0.98                          |
| recognition_thresh      | Float      | 识别阈值，取值0—1<br />默认值：0.905                         |
| verify_thresh           | float      | 1:1认证阈值，取值0—1<br />默认值：0.6 （M20/M20S 0.9）       |
| recognition_interval    | Int        | 同一个track id连续识别的时间间隔<br />设置此值跟注册回调上报图片速率有关<br />默认值为：5 |
| report_interval         | Int        | 同一个user id连续上报库中人时间间隔<br />此参数不起作用<br />默认值：1（M20/M20S 5） |
| max_face_cnt            | Int        | track最大人脸个数<br />face_mode为0时，max_face_cnt为1<br />face_mode为1时，max_face_cnt为2~4<br />默认值：1 |
| face_size               | Int        | 过滤的最小人脸像素宽度<br />默认值：30                       |
| enable_feature_export   | boolean    | 是否回传特征值<br />false: 不回传feature<br />true：回传feature<br />默认值：true |
| enable_image_export     | boolean    | 是否回传现场底图<br/>false: 不回传现场底图<br />true：回传现场底图<br />默认值：false (M20/M20S true) |
| ae_mode                 | int        | AE模式（M30无效）<br />0：模组自带的ae<br />1：自研的ae<br />默认值：0 注:M30该字段功能无效 |
| ae_flicker_freq         | int        | AE防闪烁频率模式（M30无效）<br />0：不开启防闪烁<br />50：开启50hz防闪烁<br />60：开启6ohz防闪烁<br />默认关闭：0 |
| enable_safety_hat       | Boolean    | 是否开启安全帽检测<br />false：关闭检测是否带了安全帽<br />true：开启检测是否带了安全帽<br />默认关闭，建议不需要开启。 |
| enable_mask_sign        | Boolean    | 检测时是否开启口罩检测<br />false：关闭检测是否带了口罩<br />true：开启检测是否带了口罩<br />默认关闭。 |
| enable_db_mask_sign     | Boolean    | 入库时是否开启口罩检测<br />false：关闭检测是否带了口罩<br />true：开启检测是否带了口罩<br />默认关闭。 |
| enable_extra_attribute  | Boolean    | 是否开启附加信息检测<br />false：关闭attr_info检测<br />true：attr_info检测<br />默认关闭。 |
| track_fps               | Int        | 检测的帧率<br /> 范围：1-25， 默认为25                       |
| temper_strategy         | Array      | 温度策略（根据不同的温度来设定CPU的频率）<br />temper：温度值，单位：摄氏度<br />freq：CPU频率，单位：MHz，范围：408-1512，默认1512<br />当温度大于等于所设定值时，CPU频率将更新为所设定的符合范围的值 |
| db_quality_param        | Object     | 入库质量阈值:各参数范围如下：<br>roll_max:0-30， 默认为30<br/>roll_min: -30-0， 默认为-30<br/>yaw_max: 0-30， 默认为30<br/>yaw_min: -30-0， 默认为-30<br/>pitch_max: 0-30， 默认为30<br/>pitch_min: -30-0， 默认为-30<br/>face_size_min: 1-1000， 默认为30<br/>align_confidence: 0-1.0， 默认为0.4<br/>blur: 0-1.0， 默认为0.7<br/>detect_confidence:0-1.0， 默认为0.3<br/>sum_quality: 0-1.0， 默认为0.3 |
| recognize_quality_param | Object     | 识别质量阈值:各参数范围如下：<br/>roll_max:0-30， 默认为30<br/>roll_min: -30-0， 默认为-30<br/>yaw_max: 0-30， 默认为30<br/>yaw_min: -30-0， 默认为-30<br/>pitch_max: 0-30， 默认为30<br/>pitch_min: -30-0， 默认为-30<br/>face_size_min: 1-1000， 默认为30<br/>align_confidence: 0-1.0， 默认为0.4<br/>blur: 0-1.0， 默认为0.7<br/>detect_confidence:0-1.0， 默认为0.3<br/>sum_quality: 0-1.0， 默认为0.3 |

## GetSingleRecognize jsonData

```
{
    "face_info": {
        "headpose": {
            "pitch": -2.349996328353882,
            "roll": 2.8288185596466064,
            "yaw": 15.099594116210938
        },
        "rect": {
            "bottom": 737,
            "left": 220,
            "right": 590,
            "top": 346
        }
    },
    "mask_sign": 0,
    "recognition_id": "666",
    "recognition_status": 2,
    "safety_hat": 0
}
```

| 参数名             | 参数描述                                                     |
| ------------------ | ------------------------------------------------------------ |
| face_info          | 人脸信息                                                     |
| headpose           | 姿态信息                                                     |
| rect               | 脸部坐标                                                     |
| mask_sign          | 是否佩戴口罩， 0：未戴口罩； 1：戴好； 2：戴了但未戴好       |
| recognition_id     | 识别ID，可能的值为入库ID、UNKNOW、STRANGER、NONLIVENESS      |
| recognition_status | 识别结果 0：状态未知； 1：非活体； 2：库中人； 3：陌生人； 4：已识别，复用之前的识别结果； 5：认证通过； 6：认证失败； 7：认证时无人脸； |
| safety_hat         | 是否佩戴安全帽 0：未戴； 1：戴了                             |

## AutoUploadRecognize jsonData

```c++
{
    "face_info":{
        "rect":{
            "bottom":792,
            "left":280,
            "right":584,
            "top":480},
        "headpose":		{
            "yaw":29.783628463745118,
			"pitch":7.847351551055908,
            "roll":-0.4080696702003479
        },
        "track_id":20208  },
  		"recognize_score":0.9848372936248779,
		"liveness_score":0.6991509199142456,
		"feature":"",
    	"timestamp":0,
    	"recognition_id":"cl",
    	"recognition_status":2,
    	"safety_hat":0,
    	"mask_sign":0,
    	"attr_info":{
            "gender":1,
            "age":30,
            "skin":0,
            "glass":1,
            "mustache":1,
            "expression":3,
            "cap":0
        }
}
```

| 参数名             | 参数描述                                                     |
| ------------------ | ------------------------------------------------------------ |
| face_info          | 人脸信息                                                     |
| rect               | 脸部坐标                                                     |
| headpose           | 姿态信息                                                     |
| track_id           | 人脸追踪ID                                                   |
| recognize_score    | 识别匹配分值，只有识别成功后会出现                           |
| liveness_score     | 活体匹配分值，只有识别成功后会出现                           |
| feature            | 特征值                                                       |
| timestamp          | 时间戳                                                       |
| recognition_id     | 识别ID，可能的值为入库ID、UNKNOW、STRANGER、NONLIVENESS      |
| recognition_status | 识别结果<br />0：状态未知；<br />1：非活体；<br />2：库中人；<br />3：陌生人；<br />4：已识别，复用之前的识别结果；<br />5：认证通过；<br />6：认证失败；<br />7：认证时无人脸； |
| safety_hat         | 是否佩戴安全帽<br />0：未戴；<br />1：戴了                   |
| mask_sign          | 是否佩戴口罩，<br />0：未戴口罩；<br />1：戴好；<br />2：戴了但未戴好 |
| attr_info          | 附加信息                                                     |
| gender             | 性别<br />0：女性；<br />1：男性                             |
| age                | 年龄                                                         |
| skin               | 肤色 <br />0：黄种人<br />1：黑人<br />2：白人               |
| glass              | 是否戴眼镜<br />0：未戴眼镜；<br />1：戴了眼镜；<br />2：戴太阳镜 |
| mustache           | 是否有胡子<br />0：无胡子<br />1：有胡子                     |
| expression         | 表情<br />0：生气；<br />1：开心；<br />2：悲伤；<br />3：平静；<br />4：惊讶；<br />5：害怕；<br />6：厌恶；<br />7：瞌睡 |
| cap                | 是否戴帽子<br />0：未戴；<br />1：戴了                       |

## Quality jsonData

质量分数

```
{
    "align_confidence": 0.999756,
    "bbox": [
        219,
        371,
        546,
        537
    ],
    "blur": 0.987713,
    "detect_confidence": 0.886963,
    "pitch": 5.46669,
    "roll": 0.515283,
    "sum_quality": 0.85679,
    "yaw": -4.221737
}
```

| Parameter Name    | Remark       |
| ----------------- | ------------ |
| align_confidence  | 关键点置信度 |
| bbox              | 人脸框       |
| detect_confidence | 人脸框置信度 |
| blur              | 模糊度       |
| pitch             | 俯仰角       |
| roll              | 旋转角       |
| yaw               | 偏航角       |
| sum_quality       | 综合质量     |

