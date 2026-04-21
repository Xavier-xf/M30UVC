/************************************************************************
Copyright  : 2021-2031,Shenzhen SenseTime Co.,Ltd
File name  : ai_camera.h
Description: the interface of AI Camera Library.
Author     : pengenhou
Date       : 2021/05/25
Version    : V0.0.1
History    : 2021/05/25, Create it by pengenhou@sensetime.com
************************************************************************/

#ifdef  __GNUC__
#define DLL_EXPORT
#elif _MSC_VER
#define DLL_EXPORT _declspec(dllexport)
#endif
extern "C"
{
    typedef void CallBackPtr_t(char *, int);
    typedef void CallBackPtr_p(char, char *, char);
    typedef unsigned int uint;
    typedef unsigned char uchar;

    /**
     * @brief SetLogConfig
     * @param nLogLever  0 : LOG_LEVER_TRACE
     *                   1 : LOG_LEVER_DEBUG
     *                   2 : LOG_LEVER_INFO
     *                   3 : LOG_LEVER_WARN
     *                   4 : LOG_LEVER_ERROR
     *                   5 : LOG_LEVER_FATAL
     *                   6 : LOG_LEVER_NONE
     *
     * @param nLogTatget 0 : LOG_TARGET_CONSOLE
     *                   1 : LOG_TARGET_FILE
     *                   2 : LOG_TARGET_ALL
     * @return 0 : Success Other : Fail
     */
    DLL_EXPORT int   SetLogConfig(int nLogLever = 1, int nLogTarget = 2);
    DLL_EXPORT int   GetLogConfig(int* pLogLever, int* pLogTarget);
    DLL_EXPORT void* Init();
    DLL_EXPORT void* InitDev();
    DLL_EXPORT int DeInit(void* dev);
    DLL_EXPORT int DeInitDev(void* dev);

    DLL_EXPORT int EnumDevice(char *videoDevBuf, int videoDevSize, char *serialBuf, int serialSize);
    DLL_EXPORT int ConnectSerial(void* dev, const char* portName);
    DLL_EXPORT int ConnectCamera(void* dev, const char* mediaName);
    DLL_EXPORT int DisconnectSerial(void* dev);
    DLL_EXPORT int DisconnectCamera(void* dev);

    //Video
    DLL_EXPORT int GetFrame(void* dev, char* imageBuf, int imageSize, char* verifyBuf, int verifySize);
    DLL_EXPORT int GetResolution(void* dev, int* width, int* height);

    //AI Control
    DLL_EXPORT int AddFace(void* dev, const void* pID, uint nIDLength);
    DLL_EXPORT int AddFaceWithQuality(void* dev, const void* pID, uint nIDLength, void* pQuality, uint nQualityLength);
    DLL_EXPORT int AddFaceByImage(void* dev, const void* pID, uint nIDLength, const void* pImage, uint nImageLength);
    DLL_EXPORT int AddFaceByImageWithQuality(void* dev, const void* pID, uint nIDLength, const void* pImage, uint nImageLength, void* pQuality, uint nQualityLength);
    DLL_EXPORT int AddFaceReturnImage(void* dev, const void* pID, uint nIDLength, void** ppImage, uint *pImageLength);
    DLL_EXPORT int AddFaceReturnImageWithQuality(void* dev, const void* pID, uint nIDLength, void** ppImage, uint* pImageLength, void* pQuality, uint nQualityLength);
    DLL_EXPORT int AddFaceSlice(void* dev, const void* pID, uint nIDLength, uint nImageTotalLength, uint nPosition,
                          int isLastSlice, const void* pSliceData, uint nSliceDataLength);
    DLL_EXPORT int AddFaceSliceWithQuality(void* dev, const void* pID, uint nIDLength, uint nImageTotalLength, uint nPosition,
        int isLastSlice, const void* pSliceData, uint nSliceDataLength, void* pQuality, uint nQualityLength);
    DLL_EXPORT int DeleteFace(void* dev, int nMode, const void* pID = nullptr, uint nIDLength = 0);
    DLL_EXPORT int QueryFace(void* dev, const void* pID, uint nIDLength, int nMode = 0);
    DLL_EXPORT int StaticFaceCompare(void* dev, void** ppResImage, uint* pResImageLength);
    DLL_EXPORT int StaticFaceCompareReturnImage(void* dev, const void* pImage, uint nImageLength, void** ppResImage, uint* pResImageLength);
    DLL_EXPORT int StaticFaceCompareSlice(void* dev, int nMode, uint nImageTotalLength, uint nPosition, int isLastSlice,
                                    const void* pSliceData, uint nSliceDataLength, void** ppResImage, uint* pResImageLength);
    DLL_EXPORT int AddFeature(void* dev, const void* pID, uint nIDLength, const void* pFeature, uint nFeatureLength);
    DLL_EXPORT int QueryFeature(void* dev, const void* pID, uint nIDLength, void* pFeature, uint nFeatureLength);
    DLL_EXPORT int UpdateFeature(void* dev, const void* pID, uint nIDLength, const void* pFeature, uint nFeatureLength);
    DLL_EXPORT int StartOnetoNumRecognize(void* dev, int nRecMode, int nMulMode);
    DLL_EXPORT int StartOnetoOneRecognize(void* dev, int nRecMode, int nMulMode, const void* pImage, uint nImageLength);
    DLL_EXPORT int StartOnetoOneRecognizeFeature(void* dev, int nRecMode, int nMulMode, const void* pFeature, uint nFeatureLength);
    DLL_EXPORT int StartOnetoOneRecognizeSlice(void* dev, int nRecMode, int nMulMode, uint nImageTotalLength, uint nPosition,
                                         int isLastSlice, const void* pSliceData, uint nSliceDataLength);
    DLL_EXPORT int ResumeRecognize(void* dev);
    DLL_EXPORT int PauseRecognize(void* dev);
    DLL_EXPORT int QueryRecognize(void* dev);
    DLL_EXPORT int SetRecConfig(void* dev, const void* pData, uint nDataLength, int nConfigType = 0);
    DLL_EXPORT int GetRecConfig(void* dev, void* pData, uint nDataLength, int nConfigType = 0);
    DLL_EXPORT int OpenAutoUploadFaceInfoInFrame(void* dev);
    DLL_EXPORT int CloseAutoUploadFaceInfoInFrame(void* dev);
    DLL_EXPORT int GetDeviceFaceID(void* dev, void* pIDList, uint nIDListLength);
    DLL_EXPORT int SetRecognizeCount(void* dev, uchar nRecCount, uchar nLivingCount);
    DLL_EXPORT int GetRecognizeCount(void* dev, uchar* pRecCount, uchar* pLivingCount);
    DLL_EXPORT int SetTemplateUpdate(void* dev, uchar  isUpdate);
    DLL_EXPORT int GetTemplateUpdate(void* dev, uchar* isUpdate);
    DLL_EXPORT int SetQRCodeSwitch(void* dev, uchar isOpen, uchar interval);
    DLL_EXPORT int GetDeviceFaceLibraryNum(void* dev, uint *nFaceNum);
    DLL_EXPORT int GetSingleRecognize(void* dev, void* pData, uint nDataLength);

    //System Control
    DLL_EXPORT int Ping(void* dev, const void* pTestData, uint nTestDataLength);
    DLL_EXPORT int UploadPackageSlice(void* dev, uint nPosition, const void* pPacketData, uint nPacketDataLength);
    DLL_EXPORT int ApplyUpgrade(void* dev, const void* pHashData, uint nHashDataLength);
    DLL_EXPORT int GetDeviceVersion(void* dev, void* pVersion, uint nLength);
    DLL_EXPORT int Reboot(void* dev, int nMode);
    DLL_EXPORT int SetUmodeToEngin(void* dev);
    DLL_EXPORT int Reset(void* dev);
    DLL_EXPORT int Recovery(void* dev, int nMode);
    DLL_EXPORT int Standby(void* dev, int nMode);
    
    //Device Control
    DLL_EXPORT int GetDevSn(void* dev, char nMode, void* pDevSn, uint nDevsnLength);
    DLL_EXPORT int GetDevModel(void* dev, void* pDevModel, uint nDevModelLength);
    DLL_EXPORT int SetUvcSwitch(void* dev, char nMode);
    DLL_EXPORT int SetCameraStream(void* dev, char isCloseCamera, char nCameraType);
    DLL_EXPORT int GetCameraStream(void* dev, char nCameraType, uchar* isOpenCamera);
    DLL_EXPORT int SwitchCamRgbIr(void* dev, char nMode);
    DLL_EXPORT int MirrorCamRgbIr(void* dev, char nMode, char nMirror);
    DLL_EXPORT int SetStreamFormat(void* dev, char nMode);
    DLL_EXPORT int GetDevModelAppVer(void* dev, void* pModelVersion, uint nModelVersionLength);
    DLL_EXPORT int SetDeviceName(void* dev, const void* pData, uint nDataLength);
    DLL_EXPORT int GetDeviceName(void* dev, void* pDeviceName, uint nDeviceNameLength);
    DLL_EXPORT int GetLuminousSensitivityThreshold(void* dev, uint* nThreshold);
    DLL_EXPORT int GetDeviceNoFlickerHz(void* dev, char nCameraId, uchar* pHz, uchar* isEnable);
    DLL_EXPORT int SetDeviceNoFlickerHz(void* dev, char nCameraId, char nHz, char isEnable);
    DLL_EXPORT int SetRotateAngle(void* dev, char nMode);
    DLL_EXPORT int GetScreenDirection(void* dev, uchar* pMode);
    DLL_EXPORT int SetScreenDirection(void* dev, char nMode);
    DLL_EXPORT int SetResolution(void* dev, char nMode);
    DLL_EXPORT int GetFrameRate(void* dev, uint* pFrameRate);
    DLL_EXPORT int SetFrameRate(void* dev, int nFrameRate);
    DLL_EXPORT int GetIRlight(void* dev, uchar* pLuminance,uchar* pCloseTime);
    DLL_EXPORT int SetIRlight(void* dev, uchar nLuminance, uchar nCloseTime);
    DLL_EXPORT int GetCpuTemperature(void* dev, uint* nTemperature);
    DLL_EXPORT int GetAESensorModel(void* dev, uint* pSensorModel);

    DLL_EXPORT int CloseAutoUploadAiInfo(void* dev);
    DLL_EXPORT int OpenAutoUploadAiInfo(void* dev, char nUploadMode,char nImageMode);

    DLL_EXPORT void  RegisterRecoReportCb(void* dev, CallBackPtr_t handler_func);
    DLL_EXPORT void  RegisterTrackReportCb(void* dev, CallBackPtr_t handler_func);
    DLL_EXPORT void  RegisterImageReportCb(void* dev, CallBackPtr_t handler_func);
    DLL_EXPORT void  RegisterFeatureReportCb(void* dev, CallBackPtr_t handler_func);
    DLL_EXPORT void  RegisterQRCodeReportCb(void* dev, CallBackPtr_t handler_func);
}




