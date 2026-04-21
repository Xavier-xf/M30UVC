/*
 * m30_sdk.h  -  纯 C 前向声明，引用厂商 libAICameraModule 导出符号
 *
 *   厂商 ai_camera.h 是 C++ 格式（默认参数、无 #ifdef __cplusplus guard），
 *   无法在 C 编译单元中包含。所有符号均以 C linkage 导出，
 *   此处用纯 C 重新声明，链接器直接解析到同名未修饰符号。
 */
#ifndef M30_SDK_H
#define M30_SDK_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/* 回调函数类型：SDK 上报数据时调用 */
typedef void (*m30_cb_t)(char *data, int len);

/* ======================================================================== */
/*  日志管理                                                                 */
/* ======================================================================== */

/* 设置日志级别(0~6)和输出位置(0=控制台,1=文件,2=两者) */
int   SetLogConfig(int log_level, int log_target);
/* 获取日志级别和输出位置 */
int   GetLogConfig(int *log_level, int *log_target);

/* ======================================================================== */
/*  会话生命周期                                                             */
/* ======================================================================== */

void *Init(void);
int   DeInit(void *dev);

/* ======================================================================== */
/*  设备枚举与传输链路                                                       */
/* ======================================================================== */

int   EnumDevice(char *video_buf, int video_size,
                 char *serial_buf, int serial_size);
int   ConnectSerial(void *dev, const char *port_name);
int   ConnectCamera(void *dev, const char *media_name);
int   DisconnectSerial(void *dev);
int   DisconnectCamera(void *dev);

/* ======================================================================== */
/*  视频帧获取                                                               */
/* ======================================================================== */

/* 获取一帧 BGRA 图像及识别信息(json)，imageSize = w*h*4 */
int   GetFrame(void *dev, char *image_buf, int image_size,
               char *verify_buf, int verify_size);
/* 获取当前分辨率 */
int   GetResolution(void *dev, int *width, int *height);

/* ======================================================================== */
/*  视频流配置 / 开关                                                        */
/* ======================================================================== */

/* UVC 视频输出总开关, nMode: 0=开启, 1=关闭 (语义与布尔值相反) */
int   SetUvcSwitch(void *dev, char nMode);

/* 打开/关闭摄像头, isCloseCamera: 0=打开 1=关闭, nCameraType: 0=RGB 1=IR */
int   SetCameraStream(void *dev, char isCloseCamera, char nCameraType);
/* 获取摄像头开关状态, isOpenCamera输出: 1=已打开 0=已关闭 */
int   GetCameraStream(void *dev, char nCameraType, unsigned char *isOpenCamera);

/* 切换RGB/IR视频流, nMode: 0=RGB 1=IR (仅当前有效,重启无效) */
int   SwitchCamRgbIr(void *dev, char nMode);
/* 切换RGB/IR并设置镜像, nMirror: 0=镜像 1=不镜像 */
int   MirrorCamRgbIr(void *dev, char nMode, char nMirror);

/* 获取当前光敏值 */
int   GetLuminousSensitivityThreshold(void *dev, unsigned int *nThreshold);

/* 获取抗闪设置, nCameraId: 0/1, pHz: 0=50Hz 1=60Hz, isEnable: 0=关 1=开 */
int   GetDeviceNoFlickerHz(void *dev, char nCameraId,
                           unsigned char *pHz, unsigned char *isEnable);
/* 设置抗闪参数 (仅当前有效,重启无效) */
int   SetDeviceNoFlickerHz(void *dev, char nCameraId,
                           char nHz, char isEnable);

/* 设置分辨率, nMode: 0=720x1280, 1=360x640, 2=720x720, 3=720x640 */
int   SetResolution(void *dev, char nMode);

/* 获取帧率 */
int   GetFrameRate(void *dev, unsigned int *pFrameRate);
/* 设置帧率, 范围10~25 */
int   SetFrameRate(void *dev, int nFrameRate);

/* 获取IR灯亮度(0~200)和自动关闭时间(0~120秒) */
int   GetIRlight(void *dev, unsigned char *pLuminance, unsigned char *pCloseTime);
/* 设置IR灯亮度和自动关闭时间 (仅当前有效,重启无效) */
int   SetIRlight(void *dev, unsigned char nLuminance, unsigned char nCloseTime);

/* ======================================================================== */
/*  系统诊断 / 设备信息                                                      */
/* ======================================================================== */

int   Ping(void *dev, const void *pTestData, unsigned int nTestDataLength);
int   GetDeviceVersion(void *dev, void *pVersion, unsigned int nLength);
int   GetDevSn(void *dev, char nMode, void *pDevSn, unsigned int nDevsnLength);
int   GetDevModel(void *dev, void *pDevModel, unsigned int nDevModelLength);
int   GetCpuTemperature(void *dev, unsigned int *nTemperature);
int   GetAESensorModel(void *dev, unsigned int *pSensorModel);
int   GetDevModelAppVer(void *dev, void *pModelVersion, unsigned int nLength);
int   SetDeviceName(void *dev, const void *pData, unsigned int nDataLength);
int   GetDeviceName(void *dev, void *pDeviceName, unsigned int nDeviceNameLength);

/* 恢复出厂设置, nMode: 0=清空用户配置, 1=保留用户配置 */
int   Recovery(void *dev, int nMode);
/* 重启设备 */
int   Reset(void *dev);

/* 固件升级: 分片上传 (每片<=8K) */
int   UploadPackageSlice(void *dev, unsigned int nPosition,
                         const void *pPacketData, unsigned int nPacketDataLength);
/* 固件升级: 应用升级包 (传入md5 hex小写) */
int   ApplyUpgrade(void *dev, const void *pHashData, unsigned int nHashDataLength);

/* ======================================================================== */
/*  AI 人脸底库管理                                                          */
/* ======================================================================== */

/* 模组抓拍入库 */
int   AddFace(void *dev, const void *pID, unsigned int nIDLength);
/* 模组抓拍入库，返回质量分数(json) */
int   AddFaceWithQuality(void *dev, const void *pID, unsigned int nIDLength,
                         void *pQuality, unsigned int nQualityLength);
/* 上位机传入底图入库 (图片<100K) */
int   AddFaceByImage(void *dev, const void *pID, unsigned int nIDLength,
                     const void *pImage, unsigned int nImageLength);
/* 上位机传入底图入库，返回质量分数 */
int   AddFaceByImageWithQuality(void *dev, const void *pID, unsigned int nIDLength,
                                const void *pImage, unsigned int nImageLength,
                                void *pQuality, unsigned int nQualityLength);
/* 模组抓拍入库并导出底图 (ppImage需调用者free) */
int   AddFaceReturnImage(void *dev, const void *pID, unsigned int nIDLength,
                         void **ppImage, unsigned int *pImageLength);
/* 分片入库 (图片>100K, 每片<=8080字节) */
int   AddFaceSlice(void *dev, const void *pID, unsigned int nIDLength,
                   unsigned int nImageTotalLength, unsigned int nPosition,
                   int isLastSlice, const void *pSliceData,
                   unsigned int nSliceDataLength);
/* 删除底库, nMode: 0=清空全部, 1=按ID删除 */
int   DeleteFace(void *dev, int nMode, const void *pID, unsigned int nIDLength);
/* 查询底库ID是否存在, 返回0=存在 1=不存在 */
int   QueryFace(void *dev, const void *pID, unsigned int nIDLength, int nMode);
/* 导出底库ID列表 */
int   GetDeviceFaceID(void *dev, void *pIDList, unsigned int nIDListLength);
/* 获取底库数量 */
int   GetDeviceFaceLibraryNum(void *dev, unsigned int *nFaceNum);

/* 用特征值添加底库 (特征长度固定1384) */
int   AddFeature(void *dev, const void *pID, unsigned int nIDLength,
                 const void *pFeature, unsigned int nFeatureLength);
/* 用特征值更新底库 */
int   UpdateFeature(void *dev, const void *pID, unsigned int nIDLength,
                    const void *pFeature, unsigned int nFeatureLength);
/* 查询底库特征值 */
int   QueryFeature(void *dev, const void *pID, unsigned int nIDLength,
                   void *pFeature, unsigned int nFeatureLength);

/* ======================================================================== */
/*  AI 人脸识别控制                                                          */
/* ======================================================================== */

/* 启动1:N识别, nRecMode: 0=仅识别 1=活体+识别, nMulMode: 0=单人 1=多人 */
int   StartOnetoNumRecognize(void *dev, int nRecMode, int nMulMode);
/* 启动1:1识别(不分片), 图片<300K */
int   StartOnetoOneRecognize(void *dev, int nRecMode, int nMulMode,
                             const void *pImage, unsigned int nImageLength);
/* 启动1:1识别(分片), 图片>300K */
int   StartOnetoOneRecognizeSlice(void *dev, int nRecMode, int nMulMode,
                                  unsigned int nImageTotalLength,
                                  unsigned int nPosition, int isLastSlice,
                                  const void *pSliceData,
                                  unsigned int nSliceDataLength);
/* 启动1:1识别(特征值输入) */
int   StartOnetoOneRecognizeFeature(void *dev, int nRecMode, int nMulMode,
                                    const void *pFeature,
                                    unsigned int nFeatureLength);
/* 继续识别 */
int   ResumeRecognize(void *dev);
/* 暂停识别 */
int   PauseRecognize(void *dev);
/* 查询识别状态, 返回0=已开启 1=已关闭 */
int   QueryRecognize(void *dev);

/* 设置识别配置(json), nConfigType: 0=算法配置 */
int   SetRecConfig(void *dev, const void *pData, unsigned int nDataLength,
                   int nConfigType);
/* 获取识别配置(json) */
int   GetRecConfig(void *dev, void *pData, unsigned int nDataLength,
                   int nConfigType);
/* 获取单次识别结果(json) */
int   GetSingleRecognize(void *dev, void *pData, unsigned int nDataLength);

/* 设置识别次数, 范围1~10 */
int   SetRecognizeCount(void *dev, unsigned char nRecCount,
                        unsigned char nLivingCount);
/* 获取识别次数 */
int   GetRecognizeCount(void *dev, unsigned char *pRecCount,
                        unsigned char *pLivingCount);

/* 设置模板更新开关 (重启后生效), 0=关闭 1=开启 */
int   SetTemplateUpdate(void *dev, unsigned char isUpdate);
/* 获取模板更新状态 */
int   GetTemplateUpdate(void *dev, unsigned char *isUpdate);

/* 设置二维码识别 (仅当前有效), isOpen: 0=关 1=开, interval: 上报间隔秒 */
int   SetQRCodeSwitch(void *dev, unsigned char isOpen, unsigned char interval);

/* 静态比对: 模组抓拍 (ppResImage是json结果,需调用者free) */
int   StaticFaceCompare(void *dev, void **ppResImage,
                        unsigned int *pResImageLength);
/* 静态比对: 上位机导入图片(<300K) */
int   StaticFaceCompareReturnImage(void *dev, const void *pImage,
                                   unsigned int nImageLength,
                                   void **ppResImage,
                                   unsigned int *pResImageLength);
/* 静态比对: 分片(>300K) */
int   StaticFaceCompareSlice(void *dev, int nMode,
                             unsigned int nImageTotalLength,
                             unsigned int nPosition, int isLastSlice,
                             const void *pSliceData,
                             unsigned int nSliceDataLength,
                             void **ppResImage,
                             unsigned int *pResImageLength);

/* ======================================================================== */
/*  AI 数据上报开关                                                          */
/* ======================================================================== */

/* 开启帧内识别数据插入 (GetFrame的verifyBuf才有数据) */
int   OpenAutoUploadFaceInfoInFrame(void *dev);
/* 关闭帧内识别数据插入 */
int   CloseAutoUploadFaceInfoInFrame(void *dev);

/* 开启串口主动上报, nUploadMode: 0=全部 2=图片+识别 3=特征+识别 4=仅识别 */
/* nImageMode: 0~7 控制上报图片类型组合 */
int   OpenAutoUploadAiInfo(void *dev, char nUploadMode, char nImageMode);
/* 关闭串口主动上报 */
int   CloseAutoUploadAiInfo(void *dev);

/* ======================================================================== */
/*  回调注册 (主动上报)                                                      */
/* ======================================================================== */

void  RegisterRecoReportCb(void *dev, m30_cb_t handler_func);
void  RegisterTrackReportCb(void *dev, m30_cb_t handler_func);
void  RegisterImageReportCb(void *dev, m30_cb_t handler_func);
void  RegisterFeatureReportCb(void *dev, m30_cb_t handler_func);
void  RegisterQRCodeReportCb(void *dev, m30_cb_t handler_func);

/* ======================================================================== */
/*  厂商错误码                                                               */
/* ======================================================================== */
#define AC_ERR_SUCCESS                 0
#define AC_ERR_NOT_INIT               -1
#define AC_ERR_INIT_FAIL              -2
#define AC_ERR_ALREADY_INIT           -3
#define AC_ERR_INPUT_ARG              -4
#define AC_ERR_OUTPUT_ARG             -5
#define AC_ERR_COM_TIMEOUT            -6
#define AC_ERR_TLV_FORMAT             -7
#define AC_ERR_TLV_LENGTH             -8
#define AC_ERR_CALLBACK_REGISTERED    -9
#define AC_ERR_UVC_CONNECT           -10
#define AC_ERR_UVC_NEWFRAME_UNARRIVE -11
#define AC_ERR_SERIAL_CONNECT        -12

#ifdef __cplusplus
}
#endif
#endif /* M30_SDK_H */
