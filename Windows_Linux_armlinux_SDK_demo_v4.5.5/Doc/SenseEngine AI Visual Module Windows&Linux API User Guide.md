| 版本     | 更新时间   | 描述                       | 修改人      |
| -------- | ---------- | -------------------------- | ----------- |
| V1.3     | 2019/10/30 | See Change Log for details | Liu Rui     |
| V1.4     | 2019/11/27 | See Change Log for details | Fan Zhao    |
| V1.5     | 2019/12/31 | See Change Log for details | Fan Zhao    |
| V1.6     | 2020/3/3   | See Change Log for details | Fan Zhao    |
| V1.7     | 2020/3/30  | See Change Log for details | Fan Zhao    |
| V1.8     | 2020/4/8   | See Change Log for details | Fan Zhao    |
| V1.9     | 2020/5/9   | See Change Log for details | Fan Zhao    |
| V1.10    | 2020/6/22  | See Change Log for details | Fan Zhao    |
| V1.11    | 2020/7/20  | See Change Log for details | Fan Zhao    |
| V1.12    | 2020/9/10  | See Change Log for details | Fan Zhao    |
| V1.13    | 2020/10/13 | See Change Log for details | Fan Zhao    |
| V1.14    | 2020/12/3  | See Change Log for details | Fan Zhao    |
| V1.15    | 2021/01/05 | See Change Log for details | Long Zeyuan |
| V4.0.2   | 2021/06/24 | See Change Log for details | Cheng Lin   |
| V4.0.8   | 2021/08/10 | Change Log                 | Cheng Lin   |
| V4.0.10  | 2021/09/18 | Change Log                 | Cheng Lin   |
| V4.1.2   | 2021/09/18 | Change Log                 | Cheng Lin   |
| V4.2.0   | 2022/04/29 | Change Log                 | Cheng Lin   |
| V4.2.0.1 | 2022/05/07 | Change Log                 | Cheng Lin   |
| V4.3.0   | 2022/08/26 | Change Log                 | Lin Yifan   |
| V4.4.0   | 2023/05/16 | Change Log                 | Zhou Bo     |
| V4.4.1   | 2023/06/09 | Change Log                 | Zhou Bo     |
| V4.4.2   | 2023/06/19 | Change Log                 | Zhou Bo     |
| V4.4.3   | 2023/06/19 | Change Log                 | Zhou Bo     |
| V4.4.4   | 2023/07/31 | Change Log                 | Zhou Bo     |
| V4.4.5   | 2023/07/31 | Change Log                 | Zhou Bo     |

# SenseEngine AI Visual Module Windows&Linux API User Guide

[TOC]



# Overview

This document describes every single type of function, mainly for developers. The main purpose is to let developers understand the specific uses and functions provided by each type.

All interfaces of this guide document are applicable to visual modules such as M20/M20s/M30/M30 and development environments such as Qt, C#, VC++/CLI, etc.

# Log

| Function Name                                            | Remark                   |
| :------------------------------------------------------- | ------------------------ |
| int SetLogConfig(int nLogLever = 1, int nLogTarget = 2); | Set log level and target |
| int GetLogConfig(int* pLogLever, int* pLogTarget);       | Get log level and target |

## SetLogConfig()

1）Description：Set log parameters

2）Function：

```c++
int SetLogConfig(int nLogLever = 1, int nLogTarget = 2);
```

3）Parameters：

| Parameter Name | Type | Remark     |
| -------------- | ---- | ---------- |
| nLogLever      | int  | Log level  |
| nLogTatget     | int  | Log target |

| Log Level           | Remark                                             |
| ------------------- | -------------------------------------------------- |
| 0 :LOG_LEVER_TRACE  | Output TRACE DEBUG INFO WARN ERROR FATAL level log |
| 1 :LOG_LEVER_DEBUG  | Output DEBUG INFO WARN ERROR FATAL level log       |
| 2: LOG_LEVER_INFO   | Output INFO WARN ERROR FATAL level log             |
| 3 : LOG_LEVER_WARN  | Output WARN ERROR FATAL level log                  |
| 4 :LOG_LEVER_ERROR  | Output ERROR FATAL level log                       |
| 5 : LOG_LEVER_FATAL | Output FATAL level log                             |
| 6 : LOG_LEVER_NONE  | Do not print logs                                  |

| Log Target            | Remark                         |
| --------------------- | ------------------------------ |
| 0 :LOG_TARGET_CONSOLE | Log output to the console      |
| 1 : LOG_TARGET_FILE   | Log output to file             |
| 2 : LOG_TARGET_ALL    | Log output to file and console |

4）Return：

| Return Value | Remark                                         |
| ------------ | ---------------------------------------------- |
| <0           | Please refer to the API exception return value |
| 0            | Success                                        |

## GetLogConfig()

1）Description：Get log level and target.

2）Function：

```c++
int GetLogConfig(int* pLogLever, int* pLogTarget);
```

3）Parameters：

| Parameter Name | Type | Remark     |
| -------------- | ---- | ---------- |
| pLogLever      | Int* | Log level  |
| pLogTatget     | Int* | Log target |

| Log Level           | Remark                                             |
| ------------------- | -------------------------------------------------- |
| 0 :LOG_LEVER_TRACE  | Output TRACE DEBUG INFO WARN ERROR FATAL level log |
| 1 :LOG_LEVER_DEBUG  | Output DEBUG INFO WARN ERROR FATAL level log       |
| 2: LOG_LEVER_INFO   | Output INFO WARN ERROR FATAL level log             |
| 3 : LOG_LEVER_WARN  | Output WARN ERROR FATAL level log                  |
| 4 :LOG_LEVER_ERROR  | Output ERROR FATAL level log                       |
| 5 : LOG_LEVER_FATAL | Output FATAL level log                             |
| 6 : LOG_LEVER_NONE  | Do not print logs                                  |

| Log Target            | Remark                         |
| --------------------- | ------------------------------ |
| 0 :LOG_TARGET_CONSOLE | Log output to the console      |
| 1 : LOG_TARGET_FILE   | Log output to file             |
| 2 : LOG_TARGET_ALL    | Log output to file and console |

4）Return：

| Return Value | Remark                                         |
| ------------ | ---------------------------------------------- |
| <0           | Please refer to the API exception return value |
| 0            | Success                                        |

# Device initialization

| Function Name                                                | Remark                                                      |
| :----------------------------------------------------------- | ----------------------------------------------------------- |
| void* Init();                                                | Initialize the device                                       |
| int DeInit(void* dev);                                       | Release device resources                                    |
| int EnumDevice(char *videoDevBuf, int videoDevSize, char *serialBuf, int serialSize); | Query the list of devices currently connected to the system |
| int ConnectSerial(void* dev, const char* portName);          | Connect to the serial port                                  |
| int ConnectCamera(void* dev, const char* mediaName);         | Connect UVC camera device                                   |
| int DisconnectSerial(void* dev);                             | Disconnect the serial port                                  |
| int DisconnectCamera(void* dev);                             | Disconnect the UVC camera device                            |

## Init()

1）Description ：Initialize the device. Note: If the log printing function is enabled, the log file will print the SDK software version number when this function is called to assist developers in locating problems.

2）Function：

```c++
void* Init();
```

3）Parameters ：null

4）Return ：Return the function handle (for example, the Return value of Init() will be used as the input parameter of int DeInit(void* dev) )

## DeInit()

1）Description ：DeInitDev

2）Function：

```c++
int DeInit(void* dev);
```

3）Parameters ：

| Parameter Name | Type   | Remark                                 |
| -------------- | ------ | -------------------------------------- |
| dev            | void * | The function handle returned by Init() |

4）Return ：

| Return Value | Remark                                         |
| ------------ | ---------------------------------------------- |
| <0           | Please refer to the API exception return value |
| 0            | Success                                        |

## EnumDevice()

1）Description ：Query the list of devices currently connected to the system.

2）Function：

```c++
int EnumDevice(char *videoDevBuf, int videoDevSize, char *serialBuf, int serialSize);
```

3）Parameters：

| Name         | Type  | Remark                                                       |
| ------------ | ----- | ------------------------------------------------------------ |
| videoDevBuf  | char* | An array of UVC device names. If the system detects multiple UVC devices, the names will be separated by "\|". <br />General format under Windows: UVC Camera, and only one M20/M20s/M30 can be connected to Windows device<br />General format under Linux: /dev/video0\|/dev/video1, and multiple M20/M20s/M30 devices can be connected to Linux device |
| videoDevSize | int   | The number of bytes allocated by videoDevBuf, generally 1024 |
| serialBuf    | char* | An array of serial device names, if the system detects multiple serial devices, the names will be separated by "\|"<br />General format under Windows: COM0\|COM1\|COM4<br />General format under Linux: /dev/ttyACM0\|/dev/ttyACM1 |
| serialSize   | int   | The number of bytes allocated by serialBuf, generally 1024   |

4）Return ：

| Return Value | Remark                                         |
| ------------ | ---------------------------------------------- |
| <0           | Please refer to the API exception return value |
| 0            | Success                                        |

## ConnectSerial()

1）Description ：Connect serial

2）Function：

```c++
int ConnectSerial(void* dev, const char* portName);
```

3）Parameters：

| Parameter Name | Type        | Remark                                                       |
| -------------- | ----------- | ------------------------------------------------------------ |
| dev            | void*       | The function handle returned by Init()                       |
| portName       | const char* | The connected port name<br/>General format under Windows: "COMX"<br />General format under Linux: "ttyACMX",X stands for Arabic numerals |

4）Return：

| Return Value | Remark                                                       |
| ------------ | ------------------------------------------------------------ |
| <0           | Please refer to the API exception return value<br/>When calling this interface for many times, it will sometimes return -2. In order to ensure the serial port connection is normal, please disconnect the serial port and then reconnect the serial port until the interface returns 0. |
| 0            | Success                                                      |

## ConnectCamera()

1）Description ：Connect UVC camera

2）Function：

```c++
int ConnectCamera(void* dev, const char* mediaName);
```

3）Parameters：

| Name      | Type        | Remark                                                       |
| --------- | ----------- | ------------------------------------------------------------ |
| dev       | void*       | The function handle returned by Init()                       |
| mediaName | const char* | The connected UVC media name<br/>General format under Windows: "UVC Camera"<br />General format under Linux: "ttyACMX",X stands for Arabic numerals |

4）Return：

| Return | Remark                                         |
| ------ | ---------------------------------------------- |
| <0     | Please refer to the API exception return value |
| 0      | Success                                        |

## DisconnectSerial()

1）Description ：Disconnect the serial port

2）Function：

```c++
int DisconnectSerial(void* dev);
```

3）Parameters：

| Parameter Name | Type  | Remark                                 |
| -------------- | ----- | -------------------------------------- |
| dev            | void* | The function handle returned by Init() |

4）Return：

| Return Value | Remark                                         |
| ------------ | ---------------------------------------------- |
| <0           | Please refer to the API exception return value |
| 0            | Success                                        |

## DisconnectCamera()

1）Description ：Disconnect UVC camera

2）Function：

```c++
int DisconnectCamera(void* dev);
```

3）Parameters：

| Parameter Name | Type  | Remark                                 |
| -------------- | ----- | -------------------------------------- |
| dev            | void* | The function handle returned by Init() |

4）Return：

| Return Value | Remark                                         |
| ------------ | ---------------------------------------------- |
| -1           | Please refer to the API exception return value |
| 0            | Success                                        |

# Media

| Function Name                                                | Remark                                                 |
| ------------------------------------------------------------ | ------------------------------------------------------ |
| int GetFrame(void* dev, char* imageBuf, int imageSize, char* verifyBuf, int verifySize); | Obtain video stream frame data and identification data |
| int GetResolution(void* dev, int* width, int* height);       | Get resolution                                         |

## GetFrame()

1）Description：

Get a frame of image and verification information, the image storage format is bitmap, the order is BBGGRRAA. The caller needs to poll this interface to get the latest image.  Note: This interface is called frequently, and printing the log will affect the performance, so this interface doesn't print logs.

```c++
int GetFrame(void* dev, char* imageBuf, int imageSize, char* verifyBuf, int verifySize);
```

3）Parameters：

| Parameter Name | Type   | Remark                                                       |
| -------------- | ------ | ------------------------------------------------------------ |
| dev            | void*  | The function handle returned by Init()                       |
| imageBuf       | char * | Image data                                                   |
| imageSize      | int    | The number of bytes occupied by the image data<br />Call GetResolution(width,height);<br />imageSize = width * height * 4 |
| verifyBuf      | char * | The identification information sent by the device is stored in json format. Call OpenAutoUploadFaceInfoInFrame interface available to verify information. Unable to get the authentication information after calling the CloseAutoUploadAiInfo interface, that is, the obtained authentication information is empty |
| verifySize     | int    | The number of bytes occupied by verification information, generally fill in 1024 |

4）Return：

| Return Value | Remark                                         |
| ------------ | ---------------------------------------------- |
| <0           | Please refer to the API exception return value |
| 0            | Success                                        |

The verifyBuf stores the verification information sent by the device, the format is json.

Field meaning reference:

| Parameter Name     | Type   | Remark                                                       |
| ------------------ | ------ | ------------------------------------------------------------ |
| face_info          | array  | Contains all recognized face data                            |
| rect               | object | Rectangular coordinates of an identified face                |
| recognition_status | int    | Status  value of the recognition result:  0: Not  yet recognized  1: Non-liveness  2: Person in library  3: Stranger  4: Indicates  that the result has been recognized |
| recognition_id     | string | Possible values are: UNKNOWN NOLIVENESS /Person ID(in library)/STRANGER |
| recognize_score    | float  | This item will be available only when the first recognition is successful (which means that only when recognition_status is 2, there will be no recognize_score  when recognition_status is 4) |
| liveness_score     | float  | Same situation as recognize_score.                           |

## GetResolution()

1）Description ：Get the width/height of a frame of image data.

Note: The third parameter of GetFrame(void* dev, char* imageBuf, int imageSize, char* verifyBuf, int verifySize) imageSize = width * height * 4

2）Function：

```c++
int GetResolution(void* dev, int* width, int* height);
```

3）Parameters：

| Parameter Name | Type  | Remark                                 |
| -------------- | ----- | -------------------------------------- |
| dev            | void* | The function handle returned by Init() |
| width          | int * | Width of a frame of image data         |
| height         | Int * | Height of a frame of image data        |

4）Return：

| Return Value | Remark                                         |
| ------------ | ---------------------------------------------- |
| <0           | Please refer to the API exception return value |
| 0            | Success                                        |

# Settings

| Function Name                                                | Remark                                                       |
| ------------------------------------------------------------ | ------------------------------------------------------------ |
| int SetUvcSwitch(void* dev, char nMode);                     | Set the UVC switch                                           |
| int SetCameraStream(void* dev, char isCloseCamera, char nCameraType); | Turn on/off the camera                                       |
| int GetCameraStream(void* dev, char nCameraType, uchar* isOpenCamera); | Get camera status                                            |
| int SwitchCamRgbIr(void* dev, char nMode);                   | Switch between RGB and IR video streams                      |
| int MirrorCamRgbIr(void* dev, char nMode, char nMirror);     | Switch between RGB and IR video streams, mirror stream       |
| int SetStreamFormat(void* dev, char nMode);                  | Set the stream format (default MJPEG format, currently cannot switch the stream format) |
| int GetLuminousSensitivityThreshold(void* dev, uint* nThreshold); | Get the current light sensitivity value                      |
| int GetDeviceNoFlickerHz(void* dev, char nCameraId,  uchar* pHz, uchar* isEnable); | Get anti-flash setting parameters                            |
| int SetDeviceNoFlickerHz(void* dev, char nCameraId,  char nHz, char isEnable); | Set anti-flash setting parameters                            |
| int SetResolution(void* dev, char nMode);                    | Set resolution/screen size                                   |
| int GetFrameRate(void* dev, uint* pFrameRate);               | Get the current frame rate                                   |
| int SetFrameRate(void* dev, int nFrameRate);                 | Set frame rate                                               |
| int GetIRlight(void* dev, uchar* pLuminance,uchar* pCloseTime); | Get the IR light brightness and the auto-off time            |
| int SetIRlight(void* dev, uchar nLuminance, uchar nCloseTime); | Set IR light brightness and auto-off time                    |

## SetCameraStream()

1）Description ：Set camera switch

2）Function：

```c++
int SetCameraStream(void* dev, char isCloseCamera, char nCameraType);
```

3）Parameters：

| Parameter Name | Type  | Remark                                        |
| -------------- | ----- | --------------------------------------------- |
| dev            | void* | The function handle returned by Init()        |
| isCloseCamera  | char  | 0x00：Open the camera  0x01：Close the camera |
| nCameraType    | char  | 0x00：RGB camera  0x01：IR camera             |

4）Return：

| Return Value | Remark                                         |
| ------------ | ---------------------------------------------- |
| <0           | Please refer to the API exception return value |
| 0            | Success                                        |
| 1            | Already open/close                             |

## GetCameraStream()

1）Description ：Get camera switch status

2）Function：

```c++
int GetCameraStream(void* dev, char nCameraType, uchar* isOpenCamera);
```

3）Parameters：

| Name         | Type   | Remark                                 |
| ------------ | ------ | -------------------------------------- |
| dev          | void*  | The function handle returned by Init() |
| nCameraType  | char   | 0x00：RGB camera  0x01：IR camera      |
| isOpenCamera | uchar* | 0x00：not open  0x01：already opened   |

4）Return：

| Return Value | Remark                                         |
| ------------ | ---------------------------------------------- |
| <0           | Please refer to the API exception return value |
| 0            | Success                                        |
| 1            | Failed                                         |

## SwitchCamRgbIr()

1）Description ：Switch RGB and IR camera. Note: Only valid currently, invalid after restart.

2）Function：

```c++
int SwitchCamRgbIr(void* dev, char nMode);
```

3）Parameters：

| Parameter Name | Type  | Remark                                 |
| -------------- | ----- | -------------------------------------- |
| dev            | void* | The function handle returned by Init() |
| nMode          | char  | 0x00：switch RGB  0x01：Switch IR      |

4）Return：

| Return Value | Remark                                         |
| ------------ | ---------------------------------------------- |
| <0           | Please refer to the API exception return value |
| 0            | Success                                        |
| 1            | Failed                                         |

## MirrorCamRgbIr()

1）Description ：Switch RGB and IR camera, mirror stream Note: Only valid currently, invalid after restart.

2）Function：

```c++
int MirrorCamRgbIr(void* dev, char nMode, char nMirror);
```

3）Parameters：

| Parameter Name | Type  | Remark                                 |
| -------------- | ----- | -------------------------------------- |
| dev            | void* | The function handle returned by Init() |
| nMode          | char  | 0x00：switch RGB  0x01：Switch IR      |
| nMirror        | char  | 0x00：mirror <br />0x01：no mirror     |

4）Return：

| Return Value | Remark                                         |
| ------------ | ---------------------------------------------- |
| <0           | Please refer to the API exception return value |
| 0            | Success                                        |
| 1            | Failed                                         |

## GetLuminousSensitivityThreshold()

1）Description ：Get the current light sensitivity value

2）Function：

```c++
int GetLuminousSensitivityThreshold(void* dev, uint* nThreshold);
```

3）Parameters：

| Parameter Name | Type   | Remark                                 |
| -------------- | ------ | -------------------------------------- |
| dev            | void*  | The function handle returned by Init() |
| nThreshold     | uint * | Current light sensitivity value        |

4）Return：

| Return Value | Remark                                         |
| ------------ | ---------------------------------------------- |
| <0           | Please refer to the API exception return value |
| 0            | Success                                        |
| 1            | Failed                                         |

## GetDeviceNoFlickerHz()

1）Description ：Get anti-flicker status

2）Function：

```c++
int GetDeviceNoFlickerHz(void* dev, char nCameraId, uchar* pHz, uchar* isEnable);
```

3）Parameters：

| Name      | Type   | Remark                                                       |
| --------- | ------ | ------------------------------------------------------------ |
| dev       | void*  | The function handle returned by Init()                       |
| nCameraId | char   | Camera ID<br/>0x00：camera with id 0  0x01：camera with id 1 |
| pHz       | uchar* | Frequency<br/>0x00：50HZ  0x01：60HZ                         |
| isEnable  | uchar* | Enable status<br/>0x00：Disable  0x01： Enable               |

4）Return：

| Return Value | Remark                                         |
| ------------ | ---------------------------------------------- |
| <0           | Please refer to the API exception return value |
| 0            | Success                                        |
| 1            | Failed                                         |

## SetDeviceNoFlickerHz()

1）Description ：Set anti-flicker status. Note: Only valid currently, invalid after restart.

2）Function：

```c++
int SetDeviceNoFlickerHz(void* dev, char nCameraId, char nHz, char isEnable);
```

3）Parameters：

| Parameter Name | Type  | Remark                                                       |
| -------------- | ----- | ------------------------------------------------------------ |
| dev            | void* | The function handle returned by Init()                       |
| nCameraId      | char  | Camera ID<br/>0x00：camera with id 0  0x01：camera with id 1 |
| nHz            | char  | Frequency<br/>0x00：50HZ  0x01：60HZ                         |
| isEnable       | char  | Enable status<br/>0x00：Disable  0x01：enable                |

4）Return：

| Return Value | Remark                                         |
| ------------ | ---------------------------------------------- |
| <0           | Please refer to the API exception return value |
| 0            | Success                                        |
| 1            | Failed                                         |

## SetResolution()

1）Description ：Set the screen size, note that after switching 360P, do not immediately unplug the USB and power off, wait 5 seconds for the module to synchronize settings. Note: Only valid currently, invalid after restart.

2）Function：

```c++
int SetResolution(void* dev, char nMode);
```

3）Parameters：

| Name  | Type  | Remark                                                       |
| ----- | ----- | ------------------------------------------------------------ |
| dev   | void* | The function handle returned by Init()                       |
| nMode | char  | Image size<br />0x00: 720P, corresponding video resolution is 720 * 1280<br />0x01: 360P, corresponding video resolution is 360 * 540<br/>0x02：W720p*H720p (only Wukong)<br/>0x03：W720p*H640p (only Wukong)<br/>0x04：W720p*H480p (only Wukong)<br />Note：For M20s ROM V3.0.4 and above, nMode can be set to 0x02~0x04, and M20 nMode cannot be set to 0x02~0x04 |

4）Return：

| Return Value | Remark                                                       |
| ------------ | ------------------------------------------------------------ |
| <0           | Please refer to the API exception return value<br/>If the return value of M20s ROM V3.0.4 or above is -6, it is a normal situation, it can be regarded as a successful process, you can disconnect the serial port and UVC connection, and wait 20 seconds to reconnect the serial port and UVC |
| 0            | Success                                                      |
| 1            | Failed                                                       |

## GetFrameRate()

1）Description ：Get frame rate

2）Function：

```c++
int GetFrameRate(void* dev, uint* pFrameRate);
```

3）Parameters：

| Parameter Name | Type  | Remark                                 |
| -------------- | ----- | -------------------------------------- |
| dev            | void* | The function handle returned by Init() |
| pFrameRate     | uint* | Frame rate                             |

4）Return：

| Return Value | Remark                                         |
| ------------ | ---------------------------------------------- |
| <0           | Please refer to the API exception return value |
| 0            | Success                                        |
| 1            | Failed                                         |

## SetFrameRate()

1）Description ：Set frame rate

2）Function：

```c++
int SetFrameRate(void* dev, int nFrameRate);
```

3）Parameters：

| Parameter Name | Type  | Remark                                 |
| -------------- | ----- | -------------------------------------- |
| dev            | void* | The function handle returned by Init() |
| nFrameRate     | int   | Frame rate. Range:10~25                |

4）Return：

| Return Value | Remark                                         |
| ------------ | ---------------------------------------------- |
| <0           | Please refer to the API exception return value |
| 0            | Success                                        |

## GetIRlight()

1）Description ：Get IR light brightness

2）Function：

```c++
int GetIRlight(void* dev, uchar* pLuminance,uchar* pCloseTime);
```

3）Parameters：

| Parameter Name | Type   | Remark                                 |
| -------------- | ------ | -------------------------------------- |
| dev            | void*  | The function handle returned by Init() |
| pLuminance     | uchar* | IR light brigntness                    |
| pCloseTime     | uchar* | IR light auto-off time                 |

4）Return：

| Return Value | Remark                                         |
| ------------ | ---------------------------------------------- |
| <0           | Please refer to the API exception return value |
| 0            | Success                                        |
| 1            | Failed                                         |

## SetIRlight()

1）Description ：Set IR light brightness

2）Function：

```c++
int SetIRlight(void* dev, uchar nLuminance, uchar nCloseTime);
```

3）Parameters：

| Parameter Name | Type  | Remark                                                       |
| -------------- | ----- | ------------------------------------------------------------ |
| dev            | void* | The function handle returned by Init()                       |
| nLuminance     | uchar | IR light brightness, between 0-200                           |
| nCloseTime     | uchar | IR light automatically turn off time, the unit is second, the range is 0~120, that is, 0x00~0x78, when it is 0, the detection will not be performed. Start timing from the last face detection time, and the maximum error is 1 second. Only valid at the current time, invalid after restarting, when the setting value exceeds the range, the limit value shall prevail. Default value: 30. |

4）Return：

| Return Value | Remark                                         |
| ------------ | ---------------------------------------------- |
| <0           | Please refer to the API exception return value |
| 0            | Success                                        |
| 1            | Failed                                         |

# AI

| Function Name                                                | Remark                                                       |
| ------------------------------------------------------------ | ------------------------------------------------------------ |
| int AddFace(void* dev, const void* pID, uint nIDLength);     | Add face by module capturing                                 |
| int AddFaceByImage(void* dev, const void*  pID, uint nIDLength, const void* pImage, uint nImageLength); | Add face by uploading picture from host device               |
| int AddFaceReturnImage(void* dev, const  void* pID, uint nIDLength, void** ppImage, uint *pImageLength); | Add face by module capturing and import base image           |
| int AddFaceSlice(void* dev, const void*  pID, uint nIDLength, uint nImageTotalLength, uint nPosition,int isLastSlice,  const void* pSliceData, uint nSliceDataLength); | Add face data to base library(fragmentation)                 |
| int DeleteFace(void* dev, int nMode,  const void* pID = nullptr, uint nIDLength = 0); | Delete face data from base library                           |
| int QueryFace(void* dev, const void* pID, uint nIDLength, int nMode = 0); | Query whether the ID exists in the base library              |
| int StaticFaceCompare(void* dev, void** ppResImage, uint* pResImageLength); | Static comparison (without fragmentation) imported by the module capture |
| int StaticFaceCompareReturnImage(void* dev, const void* pImage, uint nImageLength, void** ppResImage, uint* pResImageLength); | Static comparison (without fragmentation) imported by host device |
| int StaticFaceCompareSlice(void* dev, int nMode, uint nImageTotalLength, uint nPosition, int isLastSlice,const void* pSliceData, uint nSliceDataLength, void**  ppResImage, uint* pResImageLength); | Static comparison (fragmentation)                            |
| int AddFeature(void* dev, const void* pID, uint nIDLength, const void* pFeature, uint nFeatureLength); | Add face data using feature value                            |
| int QueryFeature(void* dev, const void* pID, uint nIDLength, void* pFeature, uint nFeatureLength); | Query feature value by library ID                            |
| int StartOnetoNumRecognize(void* dev, int nRecMode,  int nMulMode); | Start 1:N face recognition                                   |
| int StartOnetoOneRecognize(void* dev, int nRecMode,  int nMulMode,  const void* pImage, uint nImageLength); | Start 1:1 face recognition (without fragmentation)           |
| int StartOnetoOneRecognizeSlice(void*  dev, int nRecMode, int nMulMode, uint nImageTotalLength, uint nPosition,int  isLastSlice, const void* pSliceData, uint nSliceDataLength); | Start 1:1 face recognition (fragmentation)                   |
| int ResumeRecognize(void* dev);                              | Resume face recognition                                      |
| int PauseRecognize(void* dev);                               | Pause face recognition                                       |
| int QueryRecognize(void* dev);                               | Query face recognition status                                |
| int SetRecConfig(void* dev, const void* pData, uint nDataLength, int nConfigType = 0); | Set face recognition configuration                           |
| int GetRecConfig(void* dev, void* pData, uint nDataLength, int nConfigType = 0); | Get face recognition configuration                           |
| int OpenAutoUploadFaceInfoInFrame(void* dev);                | Open inserting recognition result into the frame data        |
| int CloseAutoUploadFaceInfoInFrame(void* dev);               | Close inserting recognition result into the frame data       |
| int GetDeviceFaceID(void* dev, void* pIDList, uint nIDListLength); | Export ID list                                               |
| int SetRecognizeCount(void* dev, uchar nRecCount,  uchar nLivingCount); | Set recognition times                                        |
| int GetRecognizeCount(void* dev, uchar* pRecCount, uchar* pLivingCount); | Get recognition times                                        |
| int SetTemplateUpdate(void* dev, uchar isUpdate);            | Set template update                                          |
| int GetTemplateUpdate(void* dev, uchar* isUpdate);           | Get template update                                          |
| int SetQRCodeSwitch(void* dev, uchar isOpen, uchar interval); | QR code recognition                                          |
| int GetDeviceFaceLibraryNum(void* dev, uint *nFaceNum);      | Get the number of base libraries                             |
| int GetSingleRecognize(void* dev, void* pData, uint nDataLength); | Get a single recognition result                              |
| void RegisterRecoReportCb(void* dev, CallBackPtr_t handler_func); | Recognition result report                                    |
| void RegisterTrackReportCb(void* dev, CallBackPtr_t handler_func); | Detection and track result report                            |
| void RegisterImageReportCb(void* dev, CallBackPtr_t handler_func); | Picture data report                                          |
| void RegisterFeatureReportCb(void* dev, CallBackPtr_t handler_func); | Feature data reporting                                       |
| void RegisterQRCodeReportCb(void* dev, CallBackPtr_t handler_func); | Report the result of QR code recognition                     |

## AddFace()

1）description ：Add face by module capturing. Note: support JPG, JPEG image format

2）Function：

```c++
int AddFace(void* dev, const void* pID, uint nIDLength);
```

3）Parameters：

| Name      | Type        | Remark                                 |
| --------- | ----------- | -------------------------------------- |
| dev       | void*       | The function handle returned by Init() |
| pID       | const void* | Library ID                             |
| nIDLength | uint        | Length of library ID                   |

4）Return：

| Status Code | Name                                                         |
| ----------- | ------------------------------------------------------------ |
| <0          | Please refer to the API exception return value               |
| 0x00        | Success                                                      |
| 0x01        | Failed to add, no face                                       |
| 0x02        | Failed to add, multiple faces                                |
| 0x03        | Failed to add, face is too small                             |
| 0x04        | Failed to add, low align score                               |
| 0x05        | Failed to add, side face                                     |
| 0x06        | Failed to add, blurred face                                  |
| 0x07        | Failed to add, the face is too far away                      |
| 0x08        | Failed to add, identification initialization failed          |
| 0x09        | Failed to add, function input error                          |
| 0x0A        | Failed to add, feature does not exist                        |
| 0x0B        | Failed to add, encryption chip error                         |
| 0x0C        | Failed to add, the ID does not exist                         |
| 0x0F        | Failed to add, the library of this product has reached the upper limit |
| 0x10        | Failed to add, invalid ID                                    |
| 0x11        | Failed to add, failed to save file                           |
| 0x13        | Failed to add, RPC call failed                               |
| 0x14        | Failed to add, unknown TAG                                   |
| 0xA0        | Failed to add, AI service did not complete initialization    |

## AddFaceWithQuality()

1）description ：Add face by module capturing,return quality.

2）Function：

```c++
int AddFaceWithQuality(void* dev, const void* pID, uint nIDLength, void* pQuality, uint nQualityLength);
```

3）Parameters：

| Name           | Type        | Remark                                                  |
| -------------- | ----------- | ------------------------------------------------------- |
| dev            | void*       | The function handle returned by Init()                  |
| pID            | const void* | Library ID                                              |
| nIDLength      | uint        | Length of library ID                                    |
| pQuality       | void*       | The result data of the quality, returned in json format |
| nQualityLength | uint        | Quality result data length                              |

4）Return：

| Status Code | Name                                                         |
| ----------- | ------------------------------------------------------------ |
| <0          | Please refer to the API exception return value               |
| 0x00        | Success                                                      |
| 0x01        | Failed to add, no face                                       |
| 0x02        | Failed to add, multiple faces                                |
| 0x03        | Failed to add, face is too small                             |
| 0x04        | Failed to add, low align score                               |
| 0x05        | Failed to add, side face                                     |
| 0x06        | Failed to add, blurred face                                  |
| 0x07        | Failed to add, the face is too far away                      |
| 0x08        | Failed to add, identification initialization failed          |
| 0x09        | Failed to add, function input error                          |
| 0x0A        | Failed to add, feature does not exist                        |
| 0x0B        | Failed to add, encryption chip error                         |
| 0x0C        | Failed to add, the ID does not exist                         |
| 0x0F        | Failed to add, the library of this product has reached the upper limit |
| 0x10        | Failed to add, invalid ID                                    |
| 0x11        | Failed to add, failed to save file                           |
| 0x13        | Failed to add, RPC call failed                               |
| 0x14        | Failed to add, unknown TAG                                   |
| 0xA0        | Failed to add, AI service did not complete initialization    |

## AddFaceByImage()

1）Description ：Add face by uploading picture from host device, the image height and width need to be less than 1080p. Note: JPG and JPEG image formats are supported; this interface is used when the image size is less than 100K.

2）Function：

```c++
int AddFaceByImage(void* dev, const void* pID, uint nIDLength, const void* pImage, uint nImageLength);
```

3）Parameters：

| Parameter Name | Parameter Type | Remark                                 |
| -------------- | -------------- | -------------------------------------- |
| dev            | void*          | The function handle returned by Init() |
| pID            | const void*    | Library ID                             |
| nIDLength      | uint           | Length of library id                   |
| pImage         | const void*    | Image data                             |
| nImageLength   | uint           | Data length of image                   |

4）Return：

| Return Value | Remark                                                       |
| ------------ | ------------------------------------------------------------ |
| <0           | Please refer to the API exception return value               |
| 0x00         | Success                                                      |
| 0x01         | Failed to add, no face                                       |
| 0x02         | Failed to add, multiple faces                                |
| 0x03         | Failed to add, face is too small                             |
| 0x04         | Failed to add, low align score                               |
| 0x05         | Failed to add, side face                                     |
| 0x06         | Failed to add, blurred face                                  |
| 0x07         | Failed to add, the face is too far away                      |
| 0x08         | Failed to add, identification initialization failed          |
| 0x09         | Failed to add, function input error                          |
| 0x0A         | Failed to add, feature does not exist                        |
| 0x0B         | Failed to add, encryption chip error                         |
| 0x0C         | Failed to add, this ID does not exist                        |
| 0x0F         | Failed to add, the library of this product has reached the upper limit |
| 0x10         | Failed to add, invalid ID                                    |
| 0x11         | Failed to add, failed to save file                           |
| 0x13         | Failed to add, RPC call failed                               |
| 0x14         | Failed to add, unknown TAG                                   |
| 0xA0         | Failed to add, AI service did not complete initialization    |

## AddFaceByImageWithQuality()

1）Description ：Add face by uploading picture from host device, the image height and width need to be less than 1080p.Return quality Note: JPG and JPEG image formats are supported; this interface is used when the image size is less than 100K.

2）Function：

```c++
int AddFaceByImageWithQuality(void* dev, const void* pID, uint nIDLength, const void* pImage, uint nImageLength, void* pQuality, uint nQualityLength);
```

3）Parameters：

| Parameter Name | Parameter Type | Remark                                                  |
| -------------- | -------------- | ------------------------------------------------------- |
| dev            | void*          | The function handle returned by Init()                  |
| pID            | const void*    | Library ID                                              |
| nIDLength      | uint           | Length of library id                                    |
| pImage         | const void*    | Image data                                              |
| nImageLength   | uint           | Data length of image                                    |
| pQuality       | void*          | The result data of the quality, returned in json format |
| nQualityLength | uint           | Quality result data length                              |

4）Return：

| Return Value | Remark                                                       |
| ------------ | ------------------------------------------------------------ |
| <0           | Please refer to the API exception return value               |
| 0x00         | Success                                                      |
| 0x01         | Failed to add, no face                                       |
| 0x02         | Failed to add, multiple faces                                |
| 0x03         | Failed to add, face is too small                             |
| 0x04         | Failed to add, low align score                               |
| 0x05         | Failed to add, side face                                     |
| 0x06         | Failed to add, blurred face                                  |
| 0x07         | Failed to add, the face is too far away                      |
| 0x08         | Failed to add, identification initialization failed          |
| 0x09         | Failed to add, function input error                          |
| 0x0A         | Failed to add, feature does not exist                        |
| 0x0B         | Failed to add, encryption chip error                         |
| 0x0C         | Failed to add, this ID does not exist                        |
| 0x0F         | Failed to add, the library of this product has reached the upper limit |
| 0x10         | Failed to add, invalid ID                                    |
| 0x11         | Failed to add, failed to save file                           |
| 0x13         | Failed to add, RPC call failed                               |
| 0x14         | Failed to add, unknown TAG                                   |
| 0xA0         | Failed to add, AI service did not complete initialization    |

## AddFaceReturnImage()

1）Description：Add face by module capturing and import base image. Note: JPG and JPEG image formats are supported; After the ppImage pointer returns, the memory needs to be released by the host device.

2）Function：

```c++
int AddFaceReturnImage(void* dev, const void* pID, uint nIDLength, void** ppImage, uint *pImageLength);
```

3）Parameters：

| Parameter Name | Type        | Remark                                 |
| -------------- | ----------- | -------------------------------------- |
| dev            | void*       | The function handle returned by Init() |
| pID            | const void* | Library ID                             |
| nIDLength      | uint        | Length of library ID                   |
| ppImage        | void**      | Image data                             |
| pImageLength   | uint*       | Data length of ppImage                 |

4）Return：

| Return Value | Remark                                                       |
| ------------ | ------------------------------------------------------------ |
| <0           | Please refer to the API exception return value               |
| 0x00         | Success                                                      |
| 0x01         | Failed to add, no face                                       |
| 0x02         | Failed to add, multiple faces                                |
| 0x03         | Failed to add, face is too small                             |
| 0x04         | Failed to add, low align score                               |
| 0x05         | Failed to add, side face                                     |
| 0x06         | Failed to add, blurred face                                  |
| 0x07         | Failed to add, the face is too far away                      |
| 0x08         | Failed to add, identification initialization failed          |
| 0x09         | Failed to add, function input error                          |
| 0x0A         | Failed to add, feature does not exist                        |
| 0x0B         | Failed to add, encryption chip error                         |
| 0x0C         | Failed to add, this ID does not exist                        |
| 0x0F         | Failed to add, the library of this product has reached the upper limit |
| 0x10         | Failed to add, invalid ID                                    |
| 0x11         | Failed to add, failed to save file                           |
| 0x13         | Failed to add, RPC call failed                               |
| 0x14         | Failed to add, unknown TAG                                   |
| 0xA0         | Failed to add, AI service did not complete initialization    |

## AddFaceReturnImageWithQuality()

1）Description：Add face by module capturing and import base image,return quality. Note: JPG and JPEG image formats are supported; After the ppImage pointer returns, the memory needs to be released by the host device.

2）Function：

```c++
int AddFaceReturnImageWithQuality(void* dev, const void* pID, uint nIDLength, void** ppImage, uint* pImageLength, void* pQuality, uint nQualityLength);
```

3）Parameters：

| Parameter Name | Type        | Remark                                                  |
| -------------- | ----------- | ------------------------------------------------------- |
| dev            | void*       | The function handle returned by Init()                  |
| pID            | const void* | Library ID                                              |
| nIDLength      | uint        | Length of library ID                                    |
| ppImage        | void**      | Image data                                              |
| pImageLength   | uint*       | Data length of ppImage                                  |
| pQuality       | void*       | The result data of the quality, returned in json format |
| nQualityLength | uint        | Quality result data length                              |

4）Return：

| Return Value | Remark                                                       |
| ------------ | ------------------------------------------------------------ |
| <0           | Please refer to the API exception return value               |
| 0x00         | Success                                                      |
| 0x01         | Failed to add, no face                                       |
| 0x02         | Failed to add, multiple faces                                |
| 0x03         | Failed to add, face is too small                             |
| 0x04         | Failed to add, low align score                               |
| 0x05         | Failed to add, side face                                     |
| 0x06         | Failed to add, blurred face                                  |
| 0x07         | Failed to add, the face is too far away                      |
| 0x08         | Failed to add, identification initialization failed          |
| 0x09         | Failed to add, function input error                          |
| 0x0A         | Failed to add, feature does not exist                        |
| 0x0B         | Failed to add, encryption chip error                         |
| 0x0C         | Failed to add, this ID does not exist                        |
| 0x0F         | Failed to add, the library of this product has reached the upper limit |
| 0x10         | Failed to add, invalid ID                                    |
| 0x11         | Failed to add, failed to save file                           |
| 0x13         | Failed to add, RPC call failed                               |
| 0x14         | Failed to add, unknown TAG                                   |
| 0xA0         | Failed to add, AI service did not complete initialization    |

## AddFaceSlice()

1）Description ：uploadAddImageByPcSlice is to transmit large image data (maximum 4M) by sharding (maximum 8080 bytes per slice), similar to uploading upgrade packages in shards, similar to uploadPackageSlice(). Note: JPG and JPEG image formats are supported; this interface is used when the image size is greater than 100K.

2）Function：

```c++
int AddFaceSlice(void* dev, const void* pID, uint nIDLength, uint nImageTotalLength, uint nPosition,int isLastSlice, const void* pSliceData, uint nSliceDataLength);
```

3）Parameters：

| Parameter Name    | Type         | Remark                                                       |
| ----------------- | ------------ | ------------------------------------------------------------ |
| dev               | void*        | The function handle returned by Init()                       |
| pID               | const void*  | Image ID                                                     |
| nIDLength         | uint         | Length of image ID                                           |
| nImageTotalLength | uint         | The data length of the entire picture                        |
| nPosition         | uint         | The starting position of the slice data (for example, the first slice starts from 0, and the second slice starts from 0 plus the length of the first slice) |
| isLastSlice       | int          | Whether the last piece of data <br/>0x00：No   0x01：Yes     |
| pSliceData        | const  void* | This slice of data                                           |
| nSliceDataLength  | uint         | The length of the slice of data                              |

4）Return：

| Return Value | Remark                                                       |
| ------------ | ------------------------------------------------------------ |
| <0           | Please refer to the API exception return value               |
| 0x00         | Success                                                      |
| 0x01         | Failed to add, no face                                       |
| 0x02         | Failed to add, multiple faces                                |
| 0x03         | Failed to add, face is too small                             |
| 0x04         | Failed to add, low align score                               |
| 0x05         | Failed to add, side face                                     |
| 0x06         | Failed to add, blurred face                                  |
| 0x07         | Failed to add, the face is too far away                      |
| 0x08         | Adding failed, identification initialization failed          |
| 0x09         | Adding failed, function input error                          |
| 0x0A         | Failed to add, feature does not exist                        |
| 0x0B         | Failed to add, encryption chip error                         |
| 0x0C         | Failed to add, this ID does not exist                        |
| 0x0F         | Failed to add, the library of this product has reached the upper limit |
| 0x10         | Failed to add, invalid ID                                    |
| 0x11         | Failed to add, failed to save file                           |
| 0x13         | Failed to add, RPC call failed                               |
| 0x14         | Failed to add, unknown TAG                                   |
| 0xA0         | Failed to add, AI service did not complete initialization    |

## AddFaceSliceWithQuality()

1）Description ：uploadAddImageByPcSlice is to transmit large image data (maximum 4M) by sharding (maximum 8080 bytes per slice), similar to uploading upgrade packages in shards, similar to uploadPackageSlice().Return quality. Note: JPG and JPEG image formats are supported; this interface is used when the image size is greater than 100K.

2）Function：

```c++
int AddFaceSliceWithQuality(void* dev, const void* pID, uint nIDLength, uint nImageTotalLength, uint nPosition,
        int isLastSlice, const void* pSliceData, uint nSliceDataLength, void* pQuality, uint nQualityLength);
```

3）Parameters：

| Parameter Name    | Type         | Remark                                                       |
| ----------------- | ------------ | ------------------------------------------------------------ |
| dev               | void*        | The function handle returned by Init()                       |
| pID               | const void*  | Image ID                                                     |
| nIDLength         | uint         | Length of image ID                                           |
| nImageTotalLength | uint         | The data length of the entire picture                        |
| nPosition         | uint         | The starting position of the slice data (for example, the first slice starts from 0, and the second slice starts from 0 plus the length of the first slice) |
| isLastSlice       | int          | Whether the last piece of data <br/>0x00：No   0x01：Yes     |
| pSliceData        | const  void* | This slice of data                                           |
| nSliceDataLength  | uint         | The length of the slice of data                              |
| pQuality          | void*        | The result data of the quality, returned in json format      |
| nQualityLength    | uint         | Quality result data length                                   |

4）Return：

| Return Value | Remark                                                       |
| ------------ | ------------------------------------------------------------ |
| <0           | Please refer to the API exception return value               |
| 0x00         | Success                                                      |
| 0x01         | Failed to add, no face                                       |
| 0x02         | Failed to add, multiple faces                                |
| 0x03         | Failed to add, face is too small                             |
| 0x04         | Failed to add, low align score                               |
| 0x05         | Failed to add, side face                                     |
| 0x06         | Failed to add, blurred face                                  |
| 0x07         | Failed to add, the face is too far away                      |
| 0x08         | Adding failed, identification initialization failed          |
| 0x09         | Adding failed, function input error                          |
| 0x0A         | Failed to add, feature does not exist                        |
| 0x0B         | Failed to add, encryption chip error                         |
| 0x0C         | Failed to add, this ID does not exist                        |
| 0x0F         | Failed to add, the library of this product has reached the upper limit |
| 0x10         | Failed to add, invalid ID                                    |
| 0x11         | Failed to add, failed to save file                           |
| 0x13         | Failed to add, RPC call failed                               |
| 0x14         | Failed to add, unknown TAG                                   |
| 0xA0         | Failed to add, AI service did not complete initialization    |

## DeleteFace()

1）Description ：Delete face data from base library

2）Function：

```c++
int DeleteFace(void* dev, int nMode, const void* pID = nullptr, uint nIDLength = 0);
```

3）Parameters：

| Parameter Name | Type        | Remark                                                       |
| -------------- | ----------- | ------------------------------------------------------------ |
| dev            | void*       | The function handle returned by Init()                       |
| nMode          | int         | The way to delete the database data<br />0x00: clear all pictures <br />0x01: delete one picture |
| pID            | const void* | The data ID to be deleted, optional                          |
| nIDLength      | uint        | The length of data ID to be deleted, optional                |

4）Return：

| Status Code | Remark                                         |
| ----------- | ---------------------------------------------- |
| <0          | Please refer to the API exception return value |
| 0           | Success                                        |
| 1           | ID doesn't exist                               |

## QueryFace()

1）Description ：Query whether the ID exists in the base library.

2）Function：

```c++
int QueryFace(void* dev, const void* pID, uint nIDLength, int nMode = 0);
```

3）Parameters：

| Name      | Type        | Remark                                                       |
| --------- | ----------- | ------------------------------------------------------------ |
| dev       | void*       | The function handle returned by Init()                       |
| pID       | const void* | The library ID to be queried                                 |
| nIDLength | uint        | The length of library ID to be queried                       |
| nMode     | int         | Query the ID of the library<br />0x00: Query the library according to the ID |

4）Return：

| Return Value | Remark                                         |
| ------------ | ---------------------------------------------- |
| <0           | Please refer to the API exception return value |
| 0            | Query successfully, ID exists                  |
| 1            | Query successfully, ID doesn't exist           |
| 2            | Query failed                                   |
| 14           | The ID doesn't exist                           |

## StaticFaceCompare()

1）Description ：Static comparison (without fragmentation) imported by the module capture

2）Function：

```c++
int StaticFaceCompare(void* dev, void** ppResImage, uint* pResImageLength);
```

3）Parameters：

| Parameter Name  | Type   | Remark                                                       |
| --------------- | ------ | ------------------------------------------------------------ |
| dev             | void*  | The function handle returned by Init()                       |
| ppResImage      | void** | The result data of the comparison, returned in json format   |
| pResImageLength | uint   | Comparison result data length<br />When the number of IDs in the library is 0, although the function is successfully executed, the result length will be 0 |

4）Return：

| Return Value | Remark                                         |
| ------------ | ---------------------------------------------- |
| <0           | Please refer to the API exception return value |
| 0            | Static comparison successful                   |
| 1            | Static comparison failed                       |

## StaticFaceCompareReturnImage()

1）Description ：Static comparison (without fragmentation) imported by host device. Note: this interface is used when the image size is less than 300K.

2）Function：

```c++
int StaticFaceCompareReturnImage(void* dev, const void* pImage, uint nImageLength, void** ppResImage, uint* pResImageLength);
```

3）Parameters：

| Parameter Name  | Type        | Remark                                                       |
| --------------- | ----------- | ------------------------------------------------------------ |
| dev             | void*       | The function handle returned by Init()                       |
| pImage          | const void* | Imported image data                                          |
| nImageLength    | uint        | Imported image data length                                   |
| ppResImage      | void**      | The result data of the comparison, returned in json format   |
| pResImageLength | uint        | Comparison result data length<br />When the number of IDs in the library is 0, although the function is successfully executed, the result length will be 0 |

4）Return：

| Return Value | Remark                                         |
| ------------ | ---------------------------------------------- |
| <0           | Please refer to the API exception return value |
| 0            | Static comparison successful                   |
| 1            | Static comparison failed                       |

## StaticFaceCompareSlice()

1）Description ：Static comparison (fragmentation). Note: this interface is used when the image size is greater than 300K.

2）Function：

```c++
int StaticFaceCompareSlice(void* dev, int nMode, uint nImageTotalLength, uint nPosition, int isLastSlice,const void* pSliceData, uint nSliceDataLength, void** ppResImage, uint* pResImageLength);
```

3）Parameters：

| Parameter Name    | Type         | Remark                                                       |
| ----------------- | ------------ | ------------------------------------------------------------ |
| dev               | void*        | The function handle returned by Init()                       |
| nMode             | int          | Comparison mode <br />0x00: Imported by module capturing<br />0x01: Imported from the host device |
| nImageTotalLength | uint         | Total length of imported image data                          |
| nPosition         | uint         | Current data slice start position                            |
| isLastSlice       | int          | Whether it is the last slice<br/>  0x00：No   0x01：yes      |
| pSliceData        | const  void* | Imported image data                                          |
| nSliceDataLength  | uint         | Imported image data length                                   |
| ppResImage        | void**       | Comparing the length of the result data, when the number of IDs in the library is empty, although the execution is successful, the result length is 0 |
| pResImageLength   | uint*        | Compare the result data                                      |

4）Return：

| Return Value | Remark                                         |
| ------------ | ---------------------------------------------- |
| <0           | Please refer to the API exception return value |
| 0            | Static comparison successful                   |
| 1            | Static comparison failed                       |

## AddFeature()

1）Description ：Add face data using feature value

2）Function：

```c++
int AddFeature(void* dev, const void* pID, uint nIDLength, const void* pFeature, uint nFeatureLength);
```

3）Parameters：

| Parameter Name | Type        | Remark                                 |
| -------------- | ----------- | -------------------------------------- |
| dev            | void*       | The function handle returned by Init() |
| pID            | const void* | ID                                     |
| nIDLength      | uint        | ID length                              |
| pFeature       | const void* | Feature data                           |
| nFeatureLength | uint        | Feature length                         |

4）Return：

| Return Value | Remark                                         |
| ------------ | ---------------------------------------------- |
| <0           | Please refer to the API exception return value |
| 0            | Add successfully                               |
| 1            | Add failed                                     |
| 10           | Feature data format is wrong                   |

## UpdateFeature()

1）Description ：Update face data using feature value

2）Function：

```c++
int UpdateFeature(void* dev, const void* pID, uint nIDLength, const void* pFeature, uint nFeatureLength);
```

3）Parameters：

| Parameter Name | Type        | Remark                                 |
| -------------- | ----------- | -------------------------------------- |
| dev            | void*       | The function handle returned by Init() |
| pID            | const void* | ID                                     |
| nIDLength      | uint        | ID length                              |
| pFeature       | const void* | Feature data                           |
| nFeatureLength | uint        | Feature length                         |

4）Return：

| Return Value | Remark                                         |
| ------------ | ---------------------------------------------- |
| <0           | Please refer to the API exception return value |
| 0            | Add successfully                               |
| 1            | Add failed                                     |
| 10           | Feature data format is wrong                   |

## QueryFeature()

1）Description ：Query feature value by library ID. Note: Sensitive information such as pictures, feature values, and user IDs cannot be output in plain text (output in the form of parameter addresses). Others, such as version numbers, serial port names, etc., are still output in plain text (output in the form of parameter content).

2）Function：

```c++
int QueryFeature(void* dev, const void* pID, uint nIDLength, void* pFeature, uint nFeatureLength);
```

3）Parameters：

| Parameter Name | Type        | Remark                                                |
| -------------- | ----------- | ----------------------------------------------------- |
| dev            | void*       | The function handle returned by Init()                |
| pID            | const void* | Library ID                                            |
| nIDLength      | uint        | Library ID length                                     |
| pFeature       | void*       | Output parameter, Returned query characteristic value |
| nFeatureLength | uint        | pFeature application space size                       |

4）Return：

| Return Value | Remark                                         |
| ------------ | ---------------------------------------------- |
| <0           | Please refer to the API exception return value |
| 0            | Query successfully                             |
| 1            | Query failed                                   |
| 10           | The ID doesn't exist                           |

## StartOnetoNumRecognize()

1）Description ：Start 1:N face recognition

2）Function：

```c++
int StartOnetoNumRecognize(void* dev, int nRecMode, int nMulMode);
```

3）Parameters：

| Parameter Name | Type  | Remark                                                       |
| -------------- | ----- | ------------------------------------------------------------ |
| dev            | void* | The function handle returned by Init()                       |
| nRecMode       | int   | Face recognition/liveness detection mode<br />0: Only face recognition mode<br />1: Liveness detection and face recognition |
| nMulMode       | int   | Single/multiple face mode<br />0: Multiple face mode<br />1: Single face mode |

4）Return：

| Return Value | Remark                                         |
| ------------ | ---------------------------------------------- |
| <0           | Please refer to the API exception return value |
| 0            | Success                                        |
| 1            | Recognition library is abnormal                |
| 2            | Library error                                  |
| 3            | The face mode is not supported                 |

## StartOnetoOneRecognize()

1）Description ：Start 1:1 face recognition (without fragmentation). Note:  The API with fragmentation calling the API without fragmentation can solve the problem of abnormal status codes returned by the API without fragmentation; this interface is used when the image size is smaller than 300K.

2）Function：

```c++
int StartOnetoOneRecognize(void* dev, int nRecMode, int nMulMode, const void* pImage, uint nImageLength);
```

3）Parameters：

| Parameter Name | Type        | Remark                                                       |
| -------------- | ----------- | ------------------------------------------------------------ |
| dev            | void*       | The function handle returned by Init()                       |
| nRecMode       | int         | Face recognition/liveness detection mode<br />0: Only face recognition mode<br />1: Liveness detection and face recognition |
| nMulMode       | int         | Single/multiple face mode<br />0: Multiple face mode<br />1: Single face mode |
| pImage         | const void* | Base image data to be compared                               |
| nImageLength   | uint        | Length of base image to be compared                          |

4）Return：

| Return Value | Remark                                         |
| ------------ | ---------------------------------------------- |
| <0           | Please refer to the API exception return value |
| 0            | Success                                        |
| 1            | The recognition mode is not supported          |
| 2            | Library error                                  |
| 3            | The face mode is not supported                 |

## StartOnetoOneRecognizeSlice()

1）Description ：Start 1:1 face recognition (with fragmentation), start 1:1 recognition mode, and you can switch the mode dynamically. Note:this interface is used when the image size is greater than 300K.

2）Function：

```c++
int StartOnetoOneRecognizeSlice(void* dev, int nRecMode, int nMulMode, uint nImageTotalLength, uint nPosition,int isLastSlice, const void* pSliceData, uint nSliceDataLength);
```

3）Parameters：

| Parameter Name    | Type         | Remark                                                       |
| ----------------- | ------------ | ------------------------------------------------------------ |
| dev               | void*        | The function handle returned by Init()                       |
| nRecMode          | int          | Face recognition/liveness detection mode<br />0: Only face recognition mode<br />1: Liveness detection and face recognition |
| nMulMode          | int          | Single/multiple face mode<br />0: Multiple face mode<br />1: Single face mode |
| nImageTotalLength | uint         | Total length of the base library images                      |
| nPosition         | uint         | Current data slice start position                            |
| isLastSlice       | int          | Whether it is the last slice<br/>  0x00：No<br/>  0x01：Yes  |
| pSliceData        | const  void* | Compare the content of the image slice in the base library, and the slice should not exceed 8K |
| nSliceDataLength  | uint         | Compare the content length of the image slice in the base library |

4）Return：

| Return Value | Remark                                         |
| ------------ | ---------------------------------------------- |
| <0           | Please refer to the API exception return value |
| 0            | Success                                        |
| 1            | The recognition mode is not supported          |
| 2            | Library error                                  |
| 3            | The face mode is not supported                 |
| 4            | nImagetotalLength is too smal                  |

## StartOnetoOneRecognizeFeature()

1）Description ：Start 1:1 face recognition (use feature),

2）Function：

```c++
int StartOnetoOneRecognizeFeature(void* dev, int nRecMode, int nMulMode, const void* pFeature, uint nFeatureLength);
```

3）参数：

| Parameter Name | Type        | Remark                                                       |
| -------------- | ----------- | ------------------------------------------------------------ |
| dev            | void*       | The function handle returned by Init()                       |
| nRecMode       | int         | Face recognition/liveness detection mode<br />0: Only face recognition mode<br />1: Liveness detection and face recognition |
| nMulMode       | int         | Single/multiple face mode<br />0: Multiple face mode<br />1: Single face mode |
| pFeature       | const void* | Feature data to be compared                                  |
| nFeatureLength | uint        | Length of feature to be compared                             |

4）返回值：

| Return Value | Remark                                         |
| ------------ | ---------------------------------------------- |
| <0           | Please refer to the API exception return value |
| 0            | Success                                        |
| 1            | The recognition mode is not supported          |
| 2            | Library error                                  |
| 3            | The face mode is not supported                 |

## ResumeRecognize()

1）Description ：Resume face recognition

2）Function：

```c++
int ResumeRecognize(void* dev);
```

3）Parameters：

| Parameter Name | Type  | Remark                                 |
| -------------- | ----- | -------------------------------------- |
| dev            | void* | The function handle returned by Init() |

4）Return：

| Return Value | Remark                                         |
| ------------ | ---------------------------------------------- |
| <0           | Please refer to the API exception return value |
| 0            | Success                                        |
| 1            | Failed                                         |

## PauseRecognize()

1）Description ：Pause face recognition

2）Function：

```c++
int PauseRecognize(void* dev);
```

3）Parameters：

| Parameter Name | Type  | Remark                                 |
| -------------- | ----- | -------------------------------------- |
| dev            | void* | The function handle returned by Init() |

4）Return：

| Return Value | Remark                                         |
| ------------ | ---------------------------------------------- |
| <0           | Please refer to the API exception return value |
| 0            | Success                                        |
| 1            | Failed                                         |

## QueryRecognize()

1）Description ：Query face recognition status

2）Function：

```c++
int QueryRecognize(void* dev);
```

3）Parameters：

| Parameter Name | Type  | Remark                                 |
| -------------- | ----- | -------------------------------------- |
| dev            | void* | The function handle returned by Init() |

4）Return：

| Return Value | Remark                                         |
| ------------ | ---------------------------------------------- |
| <0           | Please refer to the API exception return value |
| 0            | Success                                        |
| 1            | Failed                                         |

## SetRecConfig()

1）Description ：Set face recognition configuration

2）Function：

```c++
int SetRecConfig(void* dev, const void* pData, uint nDataLength, int nConfigType = 0);
```

3）Parameters：

| Parameter Name | Type         | Remark                                                       |
| -------------- | ------------ | ------------------------------------------------------------ |
| dev            | void*        | The function handle returned by Init()                       |
| pData          | const  void* | Configuration string data (Json data)                        |
| nDataLength    | uint         | The length of Json data                                      |
| nConfigType    | int          | Configuration Type<br />0x00 Algorithm Configuration<br />0xxx To be continued |

4）Return：

| Return Value | Remark                                         |
| ------------ | ---------------------------------------------- |
| <0           | Please refer to the API exception return value |
| 0            | Success                                        |
| 1            | Failed                                         |

## GetRecConfig()

1）Description ：Get face recognition configuration

2）Function：

```c++
int GetRecConfig(void* dev, void* pData, uint nDataLength, int nConfigType = 0);
```

3）Parameters：

| Parameter Name | Type         | Remark                                                       |
| -------------- | ------------ | ------------------------------------------------------------ |
| dev            | void*        | The function handle returned by Init()                       |
| pData          | const  void* | Configuration string data (Json data)                        |
| nDataLength    | uint         | The length of Json data, generally, 2048 can be filled       |
| nConfigType    | int          | Configuration Type<br />0x00 Algorithm Configuration<br />0xxx To be continued<br/>Default is 0x00 |

4）Return：

| Return Value | Remark                                         |
| ------------ | ---------------------------------------------- |
| <0           | Please refer to the API exception return value |
| 0            | Success                                        |
| 1            | Failed                                         |

## OpenAutoUploadFaceInfoInFrame()

1）Description ：Open inserting recognition result into the frame data (Only using this interface can face recognition data be obtained, and the getFrame function can obtain face recognition information)

2）Function：

```c++
int OpenAutoUploadFaceInfoInFrame(void* dev);
```

3）Parameters：

| Parameter Name | Type  | Remark                                 |
| -------------- | ----- | -------------------------------------- |
| dev            | void* | The function handle returned by Init() |

4）Return：

| Return Value | Remark                                         |
| ------------ | ---------------------------------------------- |
| <0           | Please refer to the API exception return value |
| 0            | Success                                        |
| 1            | Failed                                         |

## CloseAutoUploadFaceInfoInFrame()

1）Description ：Turn off the recognition result into the frame data switch

2）Function：

```c++
int CloseAutoUploadFaceInfoInFrame(void* dev);
```

3）Parameters：

| Parameter Name | Type  | Remark                                 |
| -------------- | ----- | -------------------------------------- |
| dev            | void* | The function handle returned by Init() |

4）Return：

| Return Value | Remark                                         |
| ------------ | ---------------------------------------------- |
| <0           | Please refer to the API exception return value |
| 0            | Success                                        |
| 1            | Failed                                         |

## GetDeviceFaceID()

1）Description ：Export ID list

2）Function：

```c++
int GetDeviceFaceID(void* dev, void* pIDList, uint nIDListLength);
```

3）Parameters：

| Parameter Name | Type  | Remark                                 |
| -------------- | ----- | -------------------------------------- |
| dev            | void* | The function handle returned by Init() |
| pIDList        | void* | ID list data content                   |
| nIDListLength  | uint  | ID list data length                    |

4）Return：

| Return Value | Remark                                         |
| ------------ | ---------------------------------------------- |
| <0           | Please refer to the API exception return value |
| 0            | Success                                        |
| 1            | Failed to call algorithm interface             |
| 2            | Failed to obtain file length                   |
| 3            | Invalid slice data position                    |
| 4            | Failed to read file                            |

## SetRecognizeCount()

1）Description ：Set recognition times

2）Function：

```c++
int SetRecognizeCount(void* dev, uchar nRecCount, uchar nLivingCount);
```

3）Parameters：

| Parameter Name | Type  | Remark                                               |
| -------------- | ----- | ---------------------------------------------------- |
| dev            | void* | The function handle returned by Init()               |
| nRecCount      | uchar | 1-10 ：Recognition times, the default is 10.         |
| nLivingCount   | uchar | 1-10 ：Liveness detection times,  the default is 10. |

4）Return：

| Return Value | Remark                                         |
| ------------ | ---------------------------------------------- |
| <0           | Please refer to the API exception return value |
| 0            | Success                                        |
| 0x01~0x16    | Error defined by algorithm                     |

## GetRecognizeCount()

1）Description ：Get recognition times

2）Function：

```c++
int GetRecognizeCount(void* dev, uchar* pRecCount, uchar* pLivingCount);
```

3）Parameters：

| Parameter Name | Type  | Remark                                               |
| -------------- | ----- | ---------------------------------------------------- |
| dev            | void* | The function handle returned by Init()               |
| nRecCount      | uchar | 1-10 ：Recognition times, the default is 10.         |
| nLivingCount   | uchar | 1-10 ：Liveness detection times,  the default is 10. |

4）Return：

| Return Value | Remark                                         |
| ------------ | ---------------------------------------------- |
| <0           | Please refer to the API exception return value |
| 0            | Success                                        |
| 0x01~0x16    | Error defined by algorithm                     |

## SetTemplateUpdate()

1）Description ：A person doing recognition is to compare the features in the library with the features of the scene map. Successful recognition means finding a high score feature in the library. When the template update is enabled, the site map features will be integrated into this base map feature; Turning off template update will not fuse the field map features to the bottom map features. The advantage of this is that the recognition success rate will be better and better. The disadvantage is that if a person misidentifies and has a high score, the person who originally entered the database will not be able to recognize the set template update because of multiple template updates. Note: after each update of the settings, you need to restart the module to take effect.

2）Function：

```c++
int SetTemplateUpdate(void* dev, uchar  isUpdate);
```

3）Parameters：

| Parameter Name | Type  | Remark                                                       |
| -------------- | ----- | ------------------------------------------------------------ |
| dev            | void* | The function handle returned by Init()                       |
| isUpdate       | uchar | Update status value<br />0x00: Disable update<br />0x01: Enable update<br />After setting, the module must be restarted to take effect |

4）Return：

| Return Value | Remark                                         |
| ------------ | ---------------------------------------------- |
| <0           | Please refer to the API exception return value |
| 0            | Success                                        |
| 0x01~0x16    | Error defined by algorithm                     |

## GetTemplateUpdate()

1）Description ：Get template update

2）Function：

```c++
int GetTemplateUpdate(void* dev, uchar* isUpdate);
```

3）Parameters：

| Parameter Name | Type   | Remark                                                       |
| -------------- | ------ | ------------------------------------------------------------ |
| dev            | void*  | The function handle returned by Init()                       |
| isUpdate       | uchar* | Return whether the query template update is enabled, one byte<br/>0x00：Disable  0x01：Enable |

4）Return：

| Return Value | Remark                                         |
| ------------ | ---------------------------------------------- |
| <0           | Please refer to the API exception return value |
| 0            | Success                                        |
| 0x01~0x16    | Error defined by algorithm                     |

## SetQRCodeSwitch()

1）Description ：Set QR code recognition parameters. Note: The current version of M20 does not support setting QR code recognition parameters. Only valid currently, invalid after restart.

2）Function：

```c++
int SetQRCodeSwitch(void* dev, uchar isOpen, uchar interval);
```

3）Parameters：

| Parameter Name | Type  | Remark                                                       |
| -------------- | ----- | ------------------------------------------------------------ |
| dev            | void* | The function handle returned by Init()                       |
| isOpen         | uchar | QR code recognition function switch <br/>0x00: Close  0x01: Open |
| interval       | uchar | Set the identification reporting interval, the default is 5s |

4）Return：

| Return Value | Remark                                         |
| ------------ | ---------------------------------------------- |
| <0           | Please refer to the API exception return value |
| 0            | Success                                        |
| 1            | Failed                                         |

## GetDeviceFaceLibraryNum()

1）Description ：Get the number of base libraries

2）Function：

```c++
int GetDeviceFaceLibraryNum(void* dev, uint *nFaceNum);
```

3）Parameters：

| Parameter Name | Type  | Remark                                 |
| -------------- | ----- | -------------------------------------- |
| dev            | void* | The function handle returned by Init() |
| nFaceNum       | uint  | The number of base libraries           |

4）Return：

| Return Value | Remark                                         |
| ------------ | ---------------------------------------------- |
| <0           | Please refer to the API exception return value |
| 0            | Success                                        |
| 1            | Failed                                         |

## GetSingleRecognize()

1）Description ：Get a single recognition result; If a face is detected in the video, the recognition result will be returned; if no face is detected in the video, the returned string will be empty

2）Function：

```c++
int GetSingleRecognize(void* dev, void* pData, uint nDataLength);
```

3）Parameters：

| Parameter Name | Type  | Remark                                 |
| -------------- | ----- | -------------------------------------- |
| dev            | void* | The function handle returned by Init() |
| pData          | void* | Recognition result                     |
| nDataLength    | uint  | Length of recognition result string    |

4）Return：

| Return Value | Remark                                         |
| ------------ | ---------------------------------------------- |
| <0           | Please refer to the API exception return value |
| 0            | Success                                        |
| 1            | Failed                                         |

## RegisterRecoReportCb()

1）Description ：Register callback reporting identification function (This function is actively reported, and the callback obtains the recognition result data. Note that you can refer to the source code of the getReoReportDataHandle callback function in the demo.)

2）Function：

```c++
void  RegisterRecoReportCb(void* dev, CallBackPtr_t handler_func);
```

3）Parameters：

| Parameter Name | Type          | Remark                                 |
| -------------- | ------------- | -------------------------------------- |
| dev            | void*         | The function handle returned by Init() |
| handler_func   | CallBackPtr_t | The handle of the callback function    |

4）Return：None

## RegisterTrackReportCb()

1）description ：Register callback reporting track function (This function is actively reported, and the callback obtains the recognition result data. Note that you can refer to the source code of the getReoTrackHandle callback function in the demo.)

2）Function：

```c++
void  RegisterTrackReportCb(void* dev, CallBackPtr_t handler_func);
```

3）Parameters：

| Parameter Name | Type          | Remark                                 |
| -------------- | ------------- | -------------------------------------- |
| dev            | void*         | The function handle returned by Init() |
| handler_func   | CallBackPtr_t | The handle of the callback function    |

4）Return：None

## RegisterImageReportCb()

1）Description ：Register callback reporting image picture function (This function is actively reported, and the callback obtains the recognition result data. Note that you can refer to the source code of the getReoImageHandle callback function in the demo.)

2）Function：

```c++
void  RegisterImageReportCb(void* dev, CallBackPtr_t handler_func);
```

3）Parameters：

| Parameter Name | Type          | Remark                                 |
| -------------- | ------------- | -------------------------------------- |
| dev            | void*         | The function handle returned by Init() |
| handler_func   | CallBackPtr_t | The handle of the callback function    |

4）Return：None

## RegisterFeatureReportCb()

1）Description ：Register callback reporting feature function (This function is actively reported, and the callback obtains the identification feature value result data. Note that you can refer to the source code of the getReoFeatureHandle callback function in the demo.) Note: When there are too many module identification results, some identification feature values will not be reported, therefore, the mode parameter of the previous openAutoUploadAiInfo function is recommended to be set to 2, and the demo call setting is the same.

2）Function：

```c++
void  RegisterFeatureReportCb(void* dev, CallBackPtr_t handler_func);
```

3）Parameters：

| Parameter Name | Type          | Remark                                 |
| -------------- | ------------- | -------------------------------------- |
| dev            | void*         | The function handle returned by Init() |
| handler_func   | CallBackPtr_t | The handle of the callback function    |

4）Return：None

## RegisterQRCodeReportCb()

1）Description ：Register callback reporting QR code function(This function is active reporting, and the callback is used to obtain the result data of the QR code recognition. Note that you can refer to the source code of the getQRCodeReportHandle callback function in the demo.) Note: When the SetQRCodeSwitch function is called to turn on the QR code reporting switch, the callback function can receive the QR code result data; M20 does not support QR code result data reporting

2）Function：

```c++
 void  RegisterQRCodeReportCb(void* dev, CallBackPtr_t handler_func);
```

3）Parameters：

| Parameter Name | Type          | Remark                                 |
| -------------- | ------------- | -------------------------------------- |
| dev            | void*         | The function handle returned by Init() |
| handler_func   | CallBackPtr_t | The handle of the callback function    |

4）Return：None

Example of video frame verification information:

```c++
{
	"track_info": [
		{
			"recognize_score": 0.986865,
			"liveness_score": 0.967434,
			"recognition_id": "fanzhao",
			"recognition_status": 0,
			"mask_sign": -1,
			"safety_hat": -1,
			"face_info": {
				"rect": {
					"bottom": 1113,
					"left": 30,
					"right": 442,
					"top": 637
				},
				"track_id": 1196
			}
		}
	]
}
```

| track_info    (Recognition result) | Remark                                                       | Note                                                         |
| ---------------------------------- | ------------------------------------------------------------ | ------------------------------------------------------------ |
| recognition_status                 | Recognition status                                           | Possible values are 0,1,2,3,4                                |
| liveness_score                     | Liveness score                                               | Appears only after successful identification                 |
| recognize_score                    | Recognition score                                            | Appears only after successful identification                 |
| face_info                          | Face information                                             | Including rect (face coordinates), track_id (face tracking ID) |
| mask_sign                          | Whether wearing a mask: <br/>-1 It is not judged whether a mask is worn<br/>1 It is judged that a mask is not worn<br/>2 It is judged that a mask is worn<br/>3 It is judged that a mask is worn, but the mask is not neatly worn | Requires setReoconfig setting. If enable_mask_sign is set to false then mask_sign will always be -1. If mask detection is turned on, it is recommended that the json with the recognition score and the liveness score shall prevail, not the json of the tracking result without the recognition score and the liveness score. You can refer to the demo source code. |
| safety_hat                         | Whether                                                      | It is not recommended to turn on helmet detection, it is turned off by default |

# Device

| Function Name                                                | Remark                               |
| ------------------------------------------------------------ | ------------------------------------ |
| int Ping(void* dev, const void* pTestData, uint nTestDataLength); | Device connectivity test             |
| int UploadPackageSlice(void* dev, uint nPosition,  const void* pPacketData, uint nPacketDataLength); | Firmware upgrade package upload      |
| int GetDevModelAppVer(void* dev, void* pModelVersion, uint nModelVersionLength); | Get the module hardware version      |
| int ApplyUpgrade(void* dev, const void* pHashData,  uint nHashDataLength); | Firmware upgrade package application |
| int GetDeviceVersion(void* dev, void* pVersion, uint nLength); | Query system version                 |
| int Recovery(void* dev, int nMode);                          | Restore factory settings             |
| int GetDevSn(void* dev, char nMode, void* pDevSn, uint nDevsnLength); | Get device SN                        |
| int GetDevModel(void* dev, void* pDevModel, uint nDevModelLength); | Get device model                     |
| int GetCpuTemperature(void* dev, uint* nTemperature);        | Query CPU temperature                |
| int GetAESensorModel(void* dev, uint* pSensorModel)          | Query AE sensor model of device      |
| int CloseAutoUploadAiInfo(void* dev);                        | Actively report data close           |
| int OpenAutoUploadAiInfo(void* dev, char nUploadMode,char nImageMode); | Actively report data open            |

## Ping()

1）Description ：Device connectivity test

2）Function：

```c++
int Ping(void* dev, const void* pTestData, uint nTestDataLength);
```

3）Parameters：

| Parameter Name  | Type        | Remark                                             |
| --------------- | ----------- | -------------------------------------------------- |
| dev             | void*       | The function handle returned by Init()             |
| pTestData       | const void* | N random bytes to send to the device               |
| nTestDataLength | uint        | The length of N random bytes to send to the device |

4）Return：

| Return Value | Remark                                         |
| ------------ | ---------------------------------------------- |
| <0           | Please refer to the API exception return value |
| 0            | Success                                        |

## UploadPackageSlice()

1）Description ：Start uploading the upgrade package. This function will start a new thread for uploading, the memory copy will occur inside the function, and the data can be passed in immediately after returning.

2）Function：

```c++
int UploadPackageSlice(void* dev, uint nPosition, const void* pPacketData, uint nPacketDataLength);
```

3）Parameters：

| Parameter Name    | Type        | Remark                                                       |
| ----------------- | ----------- | ------------------------------------------------------------ |
| dev               | void*       | The function handle returned by Init()                       |
| nPosition         | uint        | The starting position of the current slice of data, for example, the first slice start position is 0, and the second slice start position should be 0 plus the length of the first slice. Please refer to the demo for details. |
| pPacketData       | const void* | Upgrade package data                                         |
| nPacketDataLength | uint        | Data length, it is recommended that each slice not exceed 8k |

4）Return：

| Return Value | Remark                                         |
| ------------ | ---------------------------------------------- |
| <0           | Please refer to the API exception return value |
| 0            | Success                                        |
| 1            | Failed                                         |

## GetDevModelAppVer()

1）Description ：Get the module hardware version number

2）Function：

```c++
int GetDevModelAppVer(void* dev, void* pModelVersion, uint nModelVersionLength);
```

3）Parameters：

| Parameter Name      | Type  | Remark                                               |
| ------------------- | ----- | ---------------------------------------------------- |
| dev                 | void* | The function handle returned by Init()               |
| pModelVersion       | void* | Version data                                         |
| nModelVersionLength | uint  | Version data length, generally 1024 can be filled in |

4）Return：

| Return Value | Remark                                         |
| ------------ | ---------------------------------------------- |
| <0           | Please refer to the API exception return value |
| 0            | Success                                        |
| 1            | Failed                                         |

## SetDeviceName()

1）Description ：Get the module name

2）Function：

```c++
int SetDeviceName(void* dev, const void* pData, uint nDataLength);
```

3）Parameters：

| Parameter Name | Type  | Remark                                    |
| -------------- | ----- | ----------------------------------------- |
| dev            | void* | The function handle returned by Init()    |
| pData          | void* | Device name data                          |
| nDataLength    | uint  | Device name data length, must be under 50 |

4）Return：

| Return Value | Remark                                         |
| ------------ | ---------------------------------------------- |
| <0           | Please refer to the API exception return value |
| 0            | Success                                        |
| 1            | Failed                                         |

## GetDeviceName()

1）Description ：Get the module name

2）Function：

```c++
int GetDeviceName(void* dev, void* pDeviceName, uint nDeviceNameLength);
```

3）Parameters：

| Parameter Name | Type  | Remark                                     |
| -------------- | ----- | ------------------------------------------ |
| dev            | void* | The function handle returned by Init()     |
| pData          | void* | Device name data,default name is module SN |
| nDataLength    | uint  | Device name data length                    |

4）Return：

| Return Value | Remark                                         |
| ------------ | ---------------------------------------------- |
| <0           | Please refer to the API exception return value |
| 0            | Success                                        |
| 1            | Failed                                         |

## ApplyUpgrade()

1）Description ：Firmware upgrade package application. Note: Please convert the incoming md5 value to hex and keep it in lowercase, otherwise the device will not recognize it.

2）Function：

```c++
int ApplyUpgrade(void* dev, const void* pHashData, uint nHashDataLength);
```

3）Parameters：

| Parameter Name  | Type        | Remark                                 |
| --------------- | ----------- | -------------------------------------- |
| dev             | void*       | The function handle returned by Init() |
| pHashData       | const void* | MD5 value of upgrade package           |
| nHashDataLength | uint        | Length of MD5                          |

4）Return：

| Return Value | Remark                                         |
| ------------ | ---------------------------------------------- |
| <0           | Please refer to the API exception return value |
| 0            | Success                                        |
| 1            | MD5 doesn't match                              |
| 2            | It is not the firmware of this device          |

## GetDeviceVersion()

1）Description ：Query system version information

2）Function：

```c++
int GetDeviceVersion(void* dev, void* pVersion, uint nLength);
```

3）Parameters：

| Parameter Name | Type  | Remark                                 |
| -------------- | ----- | -------------------------------------- |
| dev            | void* | The function handle returned by Init() |
| pVersion       | void* | System version information             |
| nLength        | uint  | System version information length      |

4）Return：

| Return Value | Remark                                         |
| ------------ | ---------------------------------------------- |
| <0           | Please refer to the API exception return value |
| 0            | Success                                        |
| 1            | Failed                                         |

## Recovery()

1）Description ：Restore factory settings

2）Function：

```c++
int Recovery(void* dev, int nMode);
```

3）Parameters：

| Parameter Name | Type  | Remark                                                       |
| -------------- | ----- | ------------------------------------------------------------ |
| dev            | void* | The function handle returned by Init()                       |
| nMode          | int   | Processing method<br />0x00: Clear user configuration<br />0x01: Save user configuration |

4）Return：

| Return Value | Remark                                         |
| ------------ | ---------------------------------------------- |
| <0           | Please refer to the API exception return value |
| 0            | Success                                        |
| 1            | Failed                                         |

## Reset()

1）Description ：Reboot device

2）Function：

```c++
int Reset(void* dev);
```

3）Parameters：

| Parameter Name | Type  | Remark                                 |
| -------------- | ----- | -------------------------------------- |
| dev            | void* | The function handle returned by Init() |

4）Return：

| Return Value | Remark                                         |
| ------------ | ---------------------------------------------- |
| <0           | Please refer to the API exception return value |
| 0            | Success                                        |
| 9            | invalid param                                  |
| other        | Failed                                         |

## GetDevSn()

1）Description ：Get device SN

2）Function：

```c++
int GetDevSn(void* dev, char nMode, void* pDevSn, uint nDevsnLength);
```

3）Parameters：

| Parameter Name | Type  | Remark                                   |
| -------------- | ----- | ---------------------------------------- |
| dev            | void* | The function handle returned by Init()   |
| nMode          | char  | SN type<br />0x00: PCB<br />0x01: Device |
| pDevSn         | void* | SN                                       |
| nDevsnLength   | uint  | Length of SN                             |

4）Return：

| Return Value | Remark                                         |
| ------------ | ---------------------------------------------- |
| <0           | Please refer to the API exception return value |
| 0            | Success                                        |
| 1            | Failed                                         |

## GetDevModel()

1）Description ：Get device model

2）Function：

```c++
int GetDevModel(void* dev, void* pDevModel, uint nDevModelLength);
```

3）Parameters：

| Parameter Name  | Type  | Remark                                 |
| --------------- | ----- | -------------------------------------- |
| dev             | void* | The function handle returned by Init() |
| pDevModel       | void* | Device model                           |
| nDevModelLength | uint  | Length of device model                 |

4）Return：

| Return Value | Remark                                         |
| ------------ | ---------------------------------------------- |
| <0           | Please refer to the API exception return value |
| 0            | Success                                        |
| 1            | Failed                                         |

## GetCpuTemperature()

1）Description：Query CPU temperature

2）Function：

```c++
int GetCpuTemperature(void* dev, uint* nTemperature);
```

3）Parameters：

| Parameter Name | Type  | Remark                                 |
| -------------- | ----- | -------------------------------------- |
| dev            | void* | The function handle returned by Init() |
| nTemperature   | uint  | CPU temperature                        |

4）Return：

| Return Value | Remark                                         |
| ------------ | ---------------------------------------------- |
| <0           | Please refer to the API exception return value |
| 0            | Success                                        |
| 1            | Failed                                         |

## GetAESensorModel()

1）Description：query AE sensor model of the device

​	   Note：The M20 ROM version after 2.6.16 (including 2.6.16) can query the lens sensor type; M20s does not support querying the lens sensor type

2）Function：

```c++
int GetAESensorModel(void* dev, uint* pSensorModel);
```

3）Parameters：

| Parameter Name | Type  | Remark                                                       |
| -------------- | ----- | ------------------------------------------------------------ |
| dev            | void* | The function handle returned by Init()                       |
| pSensorModel   | uint* | 0x0: unknown sensor<br/>0x2238: sensor 2315E<br/>0xCB14: sensor 2335 |

4）Return：

| Return Value | Remark                                         |
| ------------ | ---------------------------------------------- |
| < 0          | Please refer to the API exception return value |
| 0            | Success                                        |
| 1            | Failed                                         |

## CloseAutoUploadAiInfo()

1）Description ：Turn off the active reporting switch of the serial port data of the recognition result (calling this interface will turn off the face recognition data reporting, corresponding to the registration callback function registerRecoReportCb, registerTrackReportCb, registerImageReportCb, registerFeatureReportCb)

2）Function：

```c++
int CloseAutoUploadAiInfo(void* dev);
```

3）Parameters：

| Parameter Name | Type  | Remark                                 |
| -------------- | ----- | -------------------------------------- |
| dev            | void* | The function handle returned by Init() |

4）Return：

| Return Value | Remark                                         |
| ------------ | ---------------------------------------------- |
| <0           | Please refer to the API exception return value |
| 0            | Success                                        |
| 1            | Failed                                         |

## OpenAutoUploadAiInfo()

1）Description ：Turn on the active reporting switch of serial port data of recognition results (if you call this interface, face recognition data will be reported, please refer to the registration callback functions registerRecoReportCb, registerTrackReportCb, registerImageReportCb, registerFeatureReportCb).

Note If you do not need to report the identification image and identification feature value, it is recommended not to enable the active reporting, and you only need to enable the frame data reporting openAutoUploadFaceInfoInFrame.

2）Function：

```c++
int OpenAutoUploadAiInfo(void* dev, char nUploadMode,char nImageMode);
```

3）Parameters：

| Parameter Name | Type  | Remark                                                       |
| -------------- | ----- | ------------------------------------------------------------ |
| dev            | void* | The function handle returned by Init()                       |
| nUploadMode    | char  | 0x00: report all information<br />0x02: report images and identification (it is recommended to set this parameter, and this parameter is also used in the demo, because part of the feature data will not be reported when there are too many identification results)<br />0x03: report features and identification<br />0x04: report identification |
| nImageMode     | char  | 0x00: RGB faces, RGB backgrounds, and IR images are all not reported. <br />0x01: Only RGB face image data is reported. <br />0x02: Only RGB background image data is reported. <br />0x03: Report RGB face and RGB background image. <br />0x04: Only IR image data is reported. <br />0x05: Report the IR image and the RGB face image. <br />0x06: Report the IR image and RGB background image. <br />0x07: Report RGB face, RGB background, and IR image data. |

4）Return：

| Return Value | Remark                                         |
| ------------ | ---------------------------------------------- |
| <0           | Please refer to the API exception return value |
| 0            | Success                                        |
| 1            | unknown error                                  |

# API Exception Return Value

| Return value | Definition of error code     | Remark                                  | Cause                                                        |
| ------------ | ---------------------------- | --------------------------------------- | ------------------------------------------------------------ |
| -1           | AC_ERR_NOT_INIT              | Uninitialized                           | Before calling other interfaces, the following interfaces are not called: <br />1. The interface Init() is not initialized <br />2. The setting & AI& device interface is not connected to the serial port ConnectSerial() <br />3. The media interface is not connected UVC ConnectCamera() |
| -2           | AC_ERR_INIT_FAIL             | initialization failed                   | 1. Failed to open serial port ConnectSerial() <br />2. Failed to open UVC ConnectCamera() |
| -3           | AC_ERR_ALREADY_INIT          | repeated initialization                 | 1. Repeatedly calling the initialization interface Init() <br />2. Repeatedly calling the connecting serial interface ConnectSerial() <br />3. Repeatingly calling the connected UVC interface ConnectCamera() |
| -4           | AC_ERR_INPUT_ARG             | input parameter exception               | 1. The input parameter is out of bounds <br />2. The pointer parameter is NULL<br />3. The value of the int type variable is too small |
| -5           | AC_ERR_OUTPUT_ARG            | output parameter exception              | The pointer parameter is NULL                                |
| -6           | AC_ERR_COM_TIMEOUT           | Serial communication timeout            | The lower computer did not reply to the request of the upper computer |
| -7           | AC_ERR_TLV_FORMAT            | TLV abnormal data format                | The data format of the reply from the lower computer is abnormal |
| -8           | AC_ERR_TLV_LENGTH            | TLV abnormal data length                | The data length of the reply from the lower computer is abnormal |
| -9           | AC_ERR_CALLBACK_REGISTERED   | Callback function is already registered | Callback function is registered repeatedly                   |
| -10          | AC_ERR_UVC_CONNECT           | The camera connection is abnormal       | 1. The device is not connected <br />2. The name of the connected UVC device is wrong |
| -11          | AC_ERR_UVC_NEWFRAME_UNARRIVE | Camera new video frame did not arrive   | It is normal for GetFrame() to return this value, which means that no new video frame has been obtained. |
| -12          | AC_ERR_SERIAL_CONNECT        | The serial port connection is abnormal  | 1. The device is not connected <br />2. The name of the device connected to the serial port is incorrect |

# Appendix

## SetReoconfig jsonData

Description: Set the configuration information of the AI service

The data structure of jsonData

```c++
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
    "verify_thresh": 0.8999999761581421,
    "work_mode": 0
}
```

| Parameter Name          | Type    | Parameter ranges and default values                          |
| ----------------------- | ------- | ------------------------------------------------------------ |
| work_mode               | enum    | Working mode<br />0: 1:N search<br />1: 1:1 verification<br />The default value is 0 |
| recognize_mode          | enum    | Recognition mode<br />0：Only indentification<br />1：Both identification and liveness detection<br />2：Only liveness detection<br />The default value is 1 |
| face_mode               | enum    | Face mode<br />0：Single face mode<br />1：Multiple face mode<br />The default value is 1 |
| enable_qr_code          | Boolean | Whether enable QR recognition mode<br />false：disable<br />true： enable<br />The default value is false |
| enable_track_box        | Boolean | Whether enable track box<br />false：disable<br />true： enable<br />The default value is true |
| liveness_thresh         | Float   | Liveness threshold, the value range is 0—1<br />The default value is 0.98 |
| recognition_thresh      | Float   | Recognition threshold, the value range is 0—1<br />The default value is 0.90 |
| verify_thresh           | float   | Verification threshold, the value range is 0—1<br />The default value is 0.90 |
| recognition_interval    | Int     | The time interval for continuous recognition of the same track id<br />The default value is 5 |
| report_interval         | Int     | The time interval for continuous reporting of the same user id<br />The default value is 5 |
| max_face_cnt            | Int     | The maximum number of faces<br />The default value is 4      |
| face_size               | Int     | Minimum face pixel width to filter<br />The default value is 10 |
| enable_feature_export   | boolean | Whether enable feature export<br />false: disable<br />true：enable<br />The default value is false |
| enable_image_export     | boolean | Whether enable image export<br />false: disable<br />true：enable<br />The default value is true |
| ae_mode                 | int     | AE mode<br />0: ae that comes with the module<br />1: self-developed ae<br />The default value is 0 |
| ae_flicker_freq         | int     | AE anti-flicker frequency<br />0: Disable anti-flicker<br />50: Enable 50hz anti-flicker<br />60: Enable 60hz anti-flicker<br />Default off: 0 |
| enable_safety_hat       | Boolean | Whether enable safe hat detection<br />false：disable<br />true：enable<br />It is disabled by default, and it is not recommended to enable it. |
| enable_mask_sign        | Boolean | Whether enable mask detection when tracking<br />false：disable<br />true：enable<br />The default value is false |
| enable_db_mask_sign     | Boolean | Whether enable mask detection when adding face base<br />false：disable<br />true：enable<br />The default value is false |
| enable_extra_attribute  | Boolean | Whether enable extra attribute detection<br />false：disable<br />true：enable<br />The default value is false |
| db_quality_param        | Object  | Add face base quality thershold                              |
| recognize_quality_param | Object  | Recognize quality thershold                                  |

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

| Parameter Name     | Remark                                                       |
| ------------------ | ------------------------------------------------------------ |
| face_info          | Face information                                             |
| rect               | Face coordinates                                             |
| headpose           | Head pose information                                        |
| mask_sign          | Whether wearing mask<br />0：No；<br />1：Yes<br />2：Wearing but not neatly |
| recognition_id     | Recognition ID, possible values are ID in library, UNKNOW, STRANGER, NONLIVENESS |
| recognition_status | Recognition result<br />0: status unknown;<br />1: non-liveness;<br />2: person in library;<br />3: stranger;<br />4: already identified, reused the previous recognition result;<br />5: identification passed;<br />6: identification failed;<br />7: no face; |
| safety_hat         | Whether wearing safe hat<br />0：No；<br />1：Yes            |

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
            "expression":
            3,"cap":0
        }
}
```

| Parameter Name     | Remark                                                       |
| ------------------ | ------------------------------------------------------------ |
| face_info          | Face information                                             |
| rect               | Face coordinates                                             |
| headpose           | Head pose information                                        |
| track_id           | Face tracking ID                                             |
| recognize_score    | Recognition score, which will only appear after the identification is successful |
| liveness_score     | Liveness score, which will only appear after the identification is successful |
| feature            | Feature value                                                |
| timestamp          | Time stamp                                                   |
| recognition_id     | Recognition ID, possible values are ID in library, UNKNOW, STRANGER, NONLIVENESS |
| recognition_status | Recognition result<br />0: status unknown;<br />1: non-liveness;<br />2: person in library;<br />3: stranger;<br />4: already identified, reused the previous recognition result;<br />5: identification passed;<br />6: identification failed;<br />7: no face; |
| safety_hat         | Whether wearing safe hat<br />0：No；<br />1：Yes            |
| mask_sign          | Whether wearing mask<br />0：No；<br />1：Yes<br />2：Wearing but not neatly |
| attr_info          | Attribute information                                        |
| gender             | Gender<br />0：Female；<br />1：Male                         |
| age                | Age                                                          |
| skin               | Skin color<br />0：Yellow<br />1：Black<br />2：White        |
| glass              | Whether wearing glasses<br />0: No;<br />1: Wearing glasses;<br />2: Wearing sunglasses |
| mustache           | Whether having mustache<br />0：No<br />1：Yes               |
| expression         | Expression<br />0: Angry;<br />1: Happy;<br />2: Sad;<br />3: Calm;<br />4: Surprised;<br />5: Scared;<br />6: Disgust;<br />7: Drowsiness |
| cap                | Whether wearing cap<br />0：No；<br />1：Yes                 |

## Quality jsonData

Quality data

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

| Parameter Name    | Remark                  |
| ----------------- | ----------------------- |
| align_confidence  | Key point confidence    |
| bbox              | Face contour            |
| detect_confidence | Face contour confidence |
| blur              | Blur                    |
| pitch             | Pitch                   |
| roll              | Roll                    |
| yaw               | Yaw                     |
| sum_quality       | Integrated quality      |





