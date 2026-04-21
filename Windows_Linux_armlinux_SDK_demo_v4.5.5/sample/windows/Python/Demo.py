import ctypes
import os.path
from ctypes import *

#load AICameraModule.dll
#w = ctypes.WinDLL(r'D:\WorkSpace\senseengine_lib\uvcCamera\release\AICameraModule.dll')
dll_name = "AICameraModule.dll"
dllabspath = os.path.dirname(os.path.abspath(__file__)) + os.path.sep + dll_name
w = ctypes.WinDLL(dllabspath)

#void* Init()
w.Init.restype = ctypes.c_void_p
handle = w.Init()
print( "Init handle =" , end=" " )
print(handle , end="\n\n" )

#int EnumDevice(char *videoDevBuf, int videoDevSize, char *serialBuf, int serialSize)
videoDevBuf = create_string_buffer(b'\0' * 2048)
serialBuf = create_string_buffer(b'\0' * 2048)
result = w.EnumDevice(videoDevBuf, c_uint(2048), serialBuf, c_uint(2048))
print( "EnumDevice result =" , end=" " )
print(result)
print( "EnumDevice videoDevBuf =" , end=" " )
print(videoDevBuf.value)
print( "EnumDevice serialBuf =" , end=" " )
print(serialBuf.value , end="\n\n" )

#int ConnectSerial(void* dev, const char* portName)
rescult = w.ConnectSerial(ctypes.c_void_p(handle), ctypes.c_char_p(bytes("COM3", 'utf-8')))
print( "ConnectSerial result =" , end=" " )
print(result , end="\n\n" )

#int GetDeviceVersion(void* dev, void* pVersion, uint nLength)
pVersion  = create_string_buffer(b'\0' * 2048)
result = w.GetDeviceVersion(ctypes.c_void_p(handle), pVersion, c_uint(2048))
print( "GetDeviceVersion result =" , end=" " )
print(result)
print( "GetDeviceVersion pVersion =" , end=" " )
print(pVersion.value , end="\n\n" )

#int DisconnectSerial(void* dev);
result = w.DisconnectSerial(ctypes.c_void_p(handle))
print( "DisconnectSerial result =" , end=" " )
print(result , end="\n\n" )

#int DeInit(void* dev);
result = w.DeInit(ctypes.c_void_p(handle))
print( "DeInit result =" , end=" " )
print(result , end="\n\n" )



