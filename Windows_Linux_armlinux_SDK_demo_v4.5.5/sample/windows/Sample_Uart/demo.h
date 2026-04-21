#ifndef _DEMO_H_
#define _DEMO_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <vector>
#include <string>
#include <iostream>
#include "../../../include/ai_camera.h"
using namespace std;

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#endif

//UT function declare
/*
 * FUNC_DESCRIPTION : Get image content and length of image bytes
 * FUNC_NAME : GetImageData
 * INPUT PARAMETER
 * 		pImagePath(image path)
 * OUTPUT PARAMETER
 * 		ppImageData(image data)
 * 		pImageDataLength(length of image bytes)
 * RETURN
 * 		0 : Success
 * 	   !0 : Fail
 */
int GetImageData(const char* pImagePath, char** ppImageData, int* pImageDataLength);

/*
 * FUNC_DESCRIPTION : Convert string to integer
 * FUNC_NAME : StringToInt
 * INPUT PARAMETER
 * 		str(a string)
 * OUTPUT PARAMETER
 * 		pNum(a integer)
 * RETURN
 * 		0 : Success
 * 	   !0 : Fail
 */
int StringToInt(const char* str, int* pNum);

/*
 * FUNC_DESCRIPTION : M20 disconnection from host machine
 * FUNC_NAME : DisConnectDev
 * INPUT PARAMETER
 * 		dev(device handle)
 * OUTPUT PARAMETER : NONE
 * RETURN
 * 		0 : Success
 * 	   !0 : Fail
 */
int DisConnectDev(void* dev);

/*
 * FUNC_DESCRIPTION : Face registration from M20
 * FUNC_NAME : AddFaceByID
 * INPUT PARAMETER
 * 		dev(device handle)
 * OUTPUT PARAMETER : NONE
 * RETURN
 * 		0 : Success
 * 	   !0 : Fail
 */
int AddFaceByID(void* dev);

/*
 * FUNC_DESCRIPTION : 1:1 authentication
 * FUNC_NAME : OnetoOneRecognizeSlice
 * INPUT PARAMETER
 * 		dev(device handle)
 * 		nRecMode(0 : Only recognition 1 : Recognition and liveness)
 * 		nMulMode(0 : Single-face      1 : Multi-face recognition)
 * 		pFilePath(face image file path )
 * OUTPUT PARAMETER : NONE
 * RETURN
 * 		0 : Success
 * 	   !0 : Fail
 */
int OnetoOneRecognizeSlice(void* dev, int nRecMode, int nMulMode, const char* pImagePath);

/*
 * FUNC_DESCRIPTION : Get recognition mode and Multi-face mode
 * FUNC_NAME : OnetoOneRecognizeSlice
 * INPUT PARAMETER
 * 		dev(device handle)
 * 		nRecMode(0 : Only recognition 1 : Recognition and liveness)
 * 		nMulMode(0 : Single-face      1 : Multi-face)
 * 		pFilePath(face image file path )
 * OUTPUT PARAMETER : NONE
 * RETURN
 * 		0 : Success
 * 	   !0 : Fail
 */
int GetRecModeAndMulMode(int* pRecMode, int* pMulMode);

/*
 * FUNC_DESCRIPTION : Get video frame from M20
 * FUNC_NAME : SaveFrame
 * INPUT PARAMETER
 * 		dev(device handle)
 * 		savePath(video frame picture saving path)
 * OUTPUT PARAMETER : NONE
 * RETURN
 * 		0 : Success
 * 	   !0 : Fail
 */
int SaveFrame(void* dev, const char* savePath, unsigned int frameNum = 100);

// Callback function
void getReoReportDataHandle(char* value, int len);
void getTrackReportDataHandle(char* value, int len);
// Callback function

vector<string> split(string str, string pattern);

int TestProcess();

#endif // !_DEMO_H_

