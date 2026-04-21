using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;

/*
typedef void CallBackPtr_t(char *, int);
typedef void CallBackPtr_p(char, char *, char);
typedef unsigned int uint;
typedef unsigned char uchar; 

_declspec(dllexport) int   SetLogConfig(int nLogLever = 1, int nLogTarget = 2);
_declspec(dllexport) int   GetLogConfig(int* pLogLever, int* pLogTarget);
_declspec(dllexport) void* Init();
_declspec(dllexport) void* InitDev();
_declspec(dllexport) int DeInit(void* dev);
_declspec(dllexport) int DeInitDev(void* dev);

_declspec(dllexport) int EnumDevice(char *videoDevBuf, int videoDevSize, char *serialBuf, int serialSize);
_declspec(dllexport) int ConnectSerial(void* dev, const char* portName);
_declspec(dllexport) int ConnectCamera(void* dev, const char* mediaName);
_declspec(dllexport) int DisconnectSerial(void* dev);
_declspec(dllexport) int DisconnectCamera(void* dev);

//Video
_declspec(dllexport) int GetFrame(void* dev, char* imageBuf, int imageSize, char* verifyBuf, int verifySize);
_declspec(dllexport) int GetResolution(void* dev, int* width, int* height);

//AI Control
_declspec(dllexport) int AddFace(void* dev, const void* pID, uint nIDLength);
_declspec(dllexport) int AddFaceByImage(void* dev, const void* pID, uint nIDLength, const void* pImage, uint nImageLength);
_declspec(dllexport) int AddFaceReturnImage(void* dev, const void* pID, uint nIDLength, void** ppImage, uint *pImageLength);
_declspec(dllexport) int AddFaceSlice(void* dev, const void* pID, uint nIDLength, uint nImageTotalLength, uint nPosition,
                        int isLastSlice, const void* pSliceData, uint nSliceDataLength);
_declspec(dllexport) int DeleteFace(void* dev, int nMode, const void* pID = nullptr, uint nIDLength = 0);
_declspec(dllexport) int QueryFace(void* dev, const void* pID, uint nIDLength, int nMode = 0);
_declspec(dllexport) int StaticFaceCompare(void* dev, void** ppResImage, uint* pResImageLength);
_declspec(dllexport) int StaticFaceCompareReturnImage(void* dev, const void* pImage, uint nImageLength, void** ppResImage, uint* pResImageLength);
_declspec(dllexport) int StaticFaceCompareSlice(void* dev, int nMode, uint nImageTotalLength, uint nPosition, int isLastSlice,
                                const void* pSliceData, uint nSliceDataLength, void** ppResImage, uint* pResImageLength);
_declspec(dllexport) int AddFeature(void* dev, const void* pID, uint nIDLength, const void* pFeature, uint nFeatureLength);
_declspec(dllexport) int QueryFeature(void* dev, const void* pID, uint nIDLength, void* pFeature, uint nFeatureLength);
_declspec(dllexport) int StartOnetoNumRecognize(void* dev, int nRecMode, int nMulMode);
_declspec(dllexport) int StartOnetoOneRecognize(void* dev, int nRecMode, int nMulMode, const void* pImage, uint nImageLength);
_declspec(dllexport) int StartOnetoOneRecognizeSlice(void* dev, int nRecMode, int nMulMode, uint nImageTotalLength, uint nPosition,
                                        int isLastSlice, const void* pSliceData, uint nSliceDataLength);
_declspec(dllexport) int ResumeRecognize(void* dev);
_declspec(dllexport) int PauseRecognize(void* dev);
_declspec(dllexport) int QueryRecognize(void* dev);
_declspec(dllexport) int SetRecConfig(void* dev, const void* pData, uint nDataLength, int nConfigType = 0);
_declspec(dllexport) int GetRecConfig(void* dev, void* pData, uint nDataLength, int nConfigType = 0);
_declspec(dllexport) int OpenAutoUploadFaceInfoInFrame(void* dev);
_declspec(dllexport) int CloseAutoUploadFaceInfoInFrame(void* dev);
_declspec(dllexport) int GetDeviceFaceID(void* dev, void* pIDList, uint nIDListLength);
_declspec(dllexport) int SetRecognizeCount(void* dev, uchar nRecCount, uchar nLivingCount);
_declspec(dllexport) int GetRecognizeCount(void* dev, uchar* pRecCount, uchar* pLivingCount);
_declspec(dllexport) int SetTemplateUpdate(void* dev, uchar  isUpdate);
_declspec(dllexport) int GetTemplateUpdate(void* dev, uchar* isUpdate);
_declspec(dllexport) int SetQRCodeSwitch(void* dev, uchar isOpen, uchar interval);
_declspec(dllexport) int GetDeviceFaceLibraryNum(void* dev, uint *nFaceNum);
_declspec(dllexport) int GetSingleRecognize(void* dev, void* pData, uint nDataLength);

//System Control
_declspec(dllexport) int Ping(void* dev, const void* pTestData, uint nTestDataLength);
_declspec(dllexport) int UploadPackageSlice(void* dev, uint nPosition, const void* pPacketData, uint nPacketDataLength);
_declspec(dllexport) int ApplyUpgrade(void* dev, const void* pHashData, uint nHashDataLength);
_declspec(dllexport) int GetDeviceVersion(void* dev, void* pVersion, uint nLength);
_declspec(dllexport) int Reboot(void* dev, int nMode);
_declspec(dllexport) int SetUmodeToEngin(void* dev);
_declspec(dllexport) int Reset(void* dev);
_declspec(dllexport) int Recovery(void* dev, int nMode);

//Device Control
_declspec(dllexport) int GetDevSn(void* dev, char nMode, void* pDevSn, uint nDevsnLength);
_declspec(dllexport) int GetDevModel(void* dev, void* pDevModel, uint nDevModelLength);
_declspec(dllexport) int SetUvcSwitch(void* dev, char nMode);
_declspec(dllexport) int SetCameraStream(void* dev, char isCloseCamera, char nCameraType);
_declspec(dllexport) int GetCameraStream(void* dev, char nCameraType, uchar* isOpenCamera);
_declspec(dllexport) int SwitchCamRgbIr(void* dev, char nMode);
_declspec(dllexport) int SetStreamFormat(void* dev, char nMode);
_declspec(dllexport) int GetDevModelAppVer(void* dev, void* pModelVersion, uint nModelVersionLength);
_declspec(dllexport) int GetLuminousSensitivityThreshold(void* dev, uint* nThreshold);
_declspec(dllexport) int GetDeviceNoFlickerHz(void* dev, char nCameraId, uchar* pHz, uchar* isEnable);
_declspec(dllexport) int SetDeviceNoFlickerHz(void* dev, char nCameraId, char nHz, char isEnable);
_declspec(dllexport) int SetRotateAngle(void* dev, char nMode);
_declspec(dllexport) int GetScreenDirection(void* dev, uchar* pMode);
_declspec(dllexport) int SetScreenDirection(void* dev, char nMode);
_declspec(dllexport) int SetResolution(void* dev, char nMode);
_declspec(dllexport) int GetFrameRate(void* dev, uint* pFrameRate);
_declspec(dllexport) int SetFrameRate(void* dev, int nFrameRate);
_declspec(dllexport) int GetIRlight(void* dev, uchar* pLuminance,uchar* pCloseTime);
_declspec(dllexport) int SetIRlight(void* dev, uchar nLuminance, uchar nCloseTime);
_declspec(dllexport) int GetCpuTemperature(void* dev, uint* nTemperature);
_declspec(dllexport) int GetAESensorModel(void* dev, uint* pSensorModel);

_declspec(dllexport) int CloseAutoUploadAiInfo(void* dev);
_declspec(dllexport) int OpenAutoUploadAiInfo(void* dev, char nUploadMode,char nImageMode);

_declspec(dllexport) void  RegisterRecoReportCb(void* dev, CallBackPtr_t handler_func);
_declspec(dllexport) void  RegisterTrackReportCb(void* dev, CallBackPtr_t handler_func);
_declspec(dllexport) void  RegisterImageReportCb(void* dev, CallBackPtr_t handler_func);
_declspec(dllexport) void  RegisterFeatureReportCb(void* dev, CallBackPtr_t handler_func);
_declspec(dllexport) void  RegisterQRCodeReportCb(void* dev, CallBackPtr_t handler_func);

[DllImport("AICameraModule.dll", CallingConvention = CallingConvention.StdCall)]
        public extern static 
 */

namespace CSharpDemo
{
    class Program
    {
        [UnmanagedFunctionPointer(CallingConvention.Cdecl)] public delegate void CallBackPtr_t(string data, int dataLen);        
                
        [DllImport("AICameraModule.dll")] public static extern IntPtr Init();
        [DllImport("AICameraModule.dll")] public static extern int DeInit(IntPtr dev);
        [DllImport("AICameraModule.dll")] public static extern int EnumDevice(StringBuilder videoDevBuf, int videoDevSize, StringBuilder serialBuf, int serialSize);
        [DllImport("AICameraModule.dll")] public static extern int ConnectSerial(IntPtr dev, string portName);
        [DllImport("AICameraModule.dll")] public static extern int ConnectCamera(IntPtr dev, string mediaName);
        [DllImport("AICameraModule.dll")] public static extern int DisconnectSerial(IntPtr dev);
        [DllImport("AICameraModule.dll")] public static extern int DisconnectCamera(IntPtr dev);
        [DllImport("AICameraModule.dll")] public static extern int GetResolution(IntPtr dev, out IntPtr width, out IntPtr height);
        [DllImport("AICameraModule.dll")] public static extern int GetFrame(IntPtr dev, StringBuilder imageBuf, int imageSize, StringBuilder verifyBuf, int verifySize);
        [DllImport("AICameraModule.dll")] public static extern int GetDeviceVersion(IntPtr dev, StringBuilder pVersion, uint nLength);
        [DllImport("AICameraModule.dll")] public static extern int AddFaceReturnImage(IntPtr dev, string pID, uint nIDLength, out StringBuilder ppImage, out IntPtr pImageLength);
        [DllImport("AICameraModule.dll")] public static extern int CloseAutoUploadAiInfo(IntPtr dev);
        [DllImport("AICameraModule.dll")] public static extern int OpenAutoUploadAiInfo(IntPtr dev, char nUploadMode, char nImageMode);
        [DllImport("AICameraModule.dll")] public extern static void RegisterRecoReportCb(IntPtr dev, CallBackPtr_t handler_func);
        [DllImport("AICameraModule.dll")] public extern static void RegisterTrackReportCb(IntPtr dev, CallBackPtr_t handler_func);
        
        public static void RegisterRecoReportCb(string data, int dataLen)
        {           
            Console.WriteLine("getReoReportDataHandle dataLen : {0} \n", dataLen);                        
        }

        static void Main(string[] args)
        {
            int ret;
            
            IntPtr dev = Init();
            Console.WriteLine("EnumDevice dev : " + dev + "\n");

            StringBuilder videoDevBuf = new StringBuilder(1024);
            StringBuilder serialBuf   = new StringBuilder(1024);            
            ret = EnumDevice(videoDevBuf, videoDevBuf.Capacity, serialBuf, serialBuf.Capacity);
            //Console.WriteLine("EnumDevice videoDevBuf : " + videoDevBuf);
            //Console.WriteLine("EnumDevice serialBuf : "   + serialBuf);
            //Console.WriteLine("EnumDevice ret : "         + ret + "\n");
            //Console.WriteLine("EnumDevice videoDevBuf : {0} | serialBuf : {1} | ret : {2}\n" , videoDevBuf, serialBuf, ret);
            Console.WriteLine($"EnumDevice videoDevBuf : {videoDevBuf} | serialBuf : {serialBuf} | ret : {ret}\n");

            if (videoDevBuf.ToString().Length == 0)
            {
                Console.WriteLine("videoDevBuf length is empty");
                return;
            }

            if (serialBuf.ToString().Length == 0)
            {
                Console.WriteLine("serialBuf length is empty");
                return;
            }

            int videoNum = 0;
            string[] videoList = videoDevBuf.ToString().Split('|');
            if (videoList.Length != 1)
            {
                for (int i = 0; i < videoDevBuf.Length; i++)
                {
                    Console.WriteLine($"({i}){videoDevBuf[i]}");
                }
                Console.WriteLine("Please input video num(0 - {0}) : ", videoList.Length - 1);
                videoNum = Convert.ToInt32(Console.ReadLine());
                if (videoNum < 0 || videoNum >= videoList.Length)
                {
                    Console.WriteLine("Input videoNum invalid");
                    return;
                }
            }
            ret = ConnectCamera(dev, videoList[videoNum]);
            Console.WriteLine("ConnectCamera ret : " + ret + "\n");
            if (ret != 0)
            {
                Console.WriteLine("ConnectCamera fail");
                return;
            }

            int serialNum = 0;
            string[] serialList = serialBuf.ToString().Split('|');
            int serialCount = serialList.Length;
            if (serialCount != 1)
            {
                for (int i = 0; i < serialCount; i++)
                {
                    Console.WriteLine($"({i}){serialList[i]}");
                }
                Console.Write("Please input serial num(0 - {0}) : ", serialCount - 1);
                serialNum = Convert.ToInt32(Console.ReadLine());
                if (serialNum < 0 || serialNum >= serialCount)
                {
                    Console.WriteLine("Input serialNum invalid");
                    return;
                }                
            }
            ret = ConnectSerial(dev, serialList[serialNum]);
            Console.WriteLine("ConnectSerial ret : " + ret + "\n");
            if(ret != 0)
            {
                Console.WriteLine("ConnectSerial fail");
                return;
            }
            
            IntPtr width  = new IntPtr();
            IntPtr height = new IntPtr();
            ret = GetResolution(dev, out width, out height);
            Console.WriteLine("GetResolution width : "  + width);
            Console.WriteLine("GetResolution height : " + height);
            Console.WriteLine("GetResolution ret : " + ret + "\n");
            Console.ReadLine();

            int w = width.ToInt32();
            int h = width.ToInt32();
            int imageSize = w * h * 4;
            StringBuilder imageBuf = new StringBuilder(imageSize);
            StringBuilder verifyBuf = new StringBuilder(1024);
            ret = GetFrame(dev, imageBuf, imageSize, verifyBuf, verifyBuf.Capacity);
            Console.WriteLine("GetFrame verifyBuf : " + verifyBuf);
            Console.WriteLine("GetFrame ret : " + ret + "\n");

            StringBuilder pVersion = new StringBuilder(1024);
            ret = GetDeviceVersion(dev, pVersion, (uint)pVersion.Capacity);
            Console.WriteLine("GetDeviceVersion pVersion : " + pVersion);
            Console.WriteLine("GetDeviceVersion ret : " + ret + "\n");

            Console.Write("Input pID : ");
            string pID = Console.ReadLine();            
            StringBuilder ppImage;
            IntPtr pImageLength = new IntPtr();
            ret = AddFaceReturnImage(dev, pID, (uint)pID.Length, out ppImage, out pImageLength);
            Console.WriteLine("AddFaceReturnImage pImageLength : " + pImageLength);
            Console.WriteLine("AddFaceReturnImage ret : " + ret + "\n");

            ret = OpenAutoUploadAiInfo(dev, (char)0, (char)1);
            Console.WriteLine("OpenAutoUploadAiInfo ret : " + ret + "\n");
            CallBackPtr_t reoReportCallBack;
            reoReportCallBack = new CallBackPtr_t(Program.RegisterRecoReportCb);            
            RegisterRecoReportCb(dev, reoReportCallBack);
            Console.ReadLine();
            ret = CloseAutoUploadAiInfo(dev);
            Console.WriteLine("CloseAutoUploadAiInfo ret : " + ret + "\n");

            ret = DisconnectSerial(dev);
            Console.WriteLine("DisconnectSerial ret : " + ret + "\n");

            ret = DisconnectCamera(dev);
            Console.WriteLine("DisconnectCamera ret : " + ret + "\n");

            ret = DeInit(dev);
            Console.WriteLine("DeInit ret : " + ret + "\n");   
            
            Console.ReadLine();
        }
    }
}