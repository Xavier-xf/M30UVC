#include <io.h>
#include <direct.h>
#include "demo.h"

//Get image content and length of image bytes
int GetImageData(const char* pImagePath, char** ppImageData, int* pImageDataLength)
{
	if (!(pImagePath && strlen(pImagePath)))
	{
		printf("!(pImagePath && strlen(pImagePath))\n");
		return -1;
	}

	if (!pImageDataLength)
	{
		printf("!pImageDataLength\n");
		return -2;
	}

	unsigned long nLen = 0;
	unsigned int imageLength = 0;

#ifdef _WIN32
	/*refer:
	 * https://bbs.csdn.net/topics/390431172?list=4181305
	 * https://jingyan.baidu.com/article/cbcede0741ef6902f50b4d6d.html
	 * https://www.cnblogs.com/l1pe1/p/14436808.html
	 */
	HANDLE hFile = CreateFileA(pImagePath, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		printf("file(%s) open fail\n", pImagePath);
		return -3;
	}

	imageLength = GetFileSize(hFile, NULL);
	if (INVALID_FILE_SIZE == imageLength)
	{
		printf("file(%s) content is empty\n", pImagePath);
		CloseHandle(hFile);
		return -4;
	}

	(*ppImageData) = (char*)malloc(imageLength);
	if ((*ppImageData) == nullptr)
	{
		printf("malloc fail\n");
		CloseHandle(hFile);
		return -5;
	}

	ReadFile(hFile, (*ppImageData), imageLength, &nLen, NULL);
	if (nLen != imageLength)
	{
		printf("file(%s) read image data is not complete nLen = %d imageLength = %d\n", pImagePath, nLen, imageLength);
		free(*ppImageData);
		(*ppImageData) = nullptr;
		CloseHandle(hFile);
		return -6;
	}
	CloseHandle(hFile);
	(*pImageDataLength) = imageLength;
#else
	int fd = -1;

	/* Load image data */
	if ((fd = open(pImagePath, O_RDONLY)) < 0)
	{
		printf("file(%s) open fail\n", pImagePath);
		return -3;
	}

	imageLength = lseek(fd, 0, SEEK_END); //文件指针移到文件尾,得到当前指针位置，既文件的长度
	printf("imageLength = %d\n", imageLength);

	if (imageLength == 0)
	{
		printf("file(%s) content is empty\n", pImagePath);
		close(fd);
		return -4;
	}

	(*ppImageData) = (char*)malloc(imageLength);
	if ((*ppImageData) == nullptr)
	{
		printf("malloc fail\n");
		close(fd);
		return -5;
	}

	lseek(fd, 0, SEEK_SET); //文件指针恢复到文件头位置
	nLen = read(fd, (*ppImageData), imageLength);
	if (nLen != imageLength)
	{
		printf("read image data is not complete nLen = %d imageLength = %d\n", nLen, imageLength);
		free(*ppImageData);
		(*ppImageData) = nullptr;
		close(fd);
		return -6;
	}
	close(fd);
	(*pImageDataLength) = imageLength;
	/* Load image data */
#endif

	return 0;
}

// Face registration from M20
int AddFaceByID(void* dev)
{
	if (!dev)
	{
		printf("dev is null\n");
		return -1;
	}

	char faceID[32] = { 0 };
	int addFaceRet = 0;
	char faceRetDesc[1024] = { 0 };
	printf("\nInput FaceID : ");
	scanf("%s", faceID);

	// Add face photo to M20 device
	addFaceRet = AddFace(dev, faceID, strlen(faceID));

	// Check whether the face photo is added successful or not
	switch (addFaceRet)
	{
	case 0:strcpy(faceRetDesc, "Add image ok."); break;
	case 1:strcpy(faceRetDesc, "Add image failed,The picture without faces!"); break;
	case 2:strcpy(faceRetDesc, "Add image failed,The picture has multi-faces !"); break;
	case 3:strcpy(faceRetDesc, "Add image failed,The face area is too small !"); break;
	case 4:strcpy(faceRetDesc, "Add image failed,The Align score is too low!"); break;
	case 5:strcpy(faceRetDesc, "Add image failed,The picture has a side face!"); break;
	case 6:strcpy(faceRetDesc, "Add image failed,The face image is fuzzy !"); break;
	case 7:strcpy(faceRetDesc, "Add image failed,The picture faces is too far!"); break;
	case 8:strcpy(faceRetDesc, "Add image failed,init process failed!"); break;
	case 9:strcpy(faceRetDesc, "Add image failed,the function arg is invalid !"); break;
	case 10:strcpy(faceRetDesc, "Add image failed,the feature file is invalid !"); break;
	case 11:strcpy(faceRetDesc, "Add image failed,HW_AUTH init failed!"); break;
	case 12:strcpy(faceRetDesc, "Add image failed,the LICENSE add failed!"); break;
	case 13:strcpy(faceRetDesc, "Add image failed,the id is not exist!"); break;
	case 14:strcpy(faceRetDesc, "Add image failed,please take off your mask!"); break;
	case 15:strcpy(faceRetDesc, "Add image failed,the Face database is full!"); break;
	case 16:strcpy(faceRetDesc, "Add image failed,the id is is invalid!"); break;
	case 17:strcpy(faceRetDesc, "Add image failed,the files saved failed"); break;
	case 18:strcpy(faceRetDesc, "Add image failed,the file is not jpg!"); break;
	case 19:strcpy(faceRetDesc, "Add image failed,the RPC op-failed!"); break;
	case 20:strcpy(faceRetDesc, "Add image failed,the unknown TAG!"); break;
	default:strcpy(faceRetDesc, "Add image Timeout!"); break;
	}

	printf("AddFace return : %d faceRetDesc : %s\n", addFaceRet, faceRetDesc);

	return 0;
}

// 1:1 authentication
int OnetoOneRecognizeSlice(void* dev, int nRecMode, int nMulMode, const char* pImagePath)
{
	/*Input parameter check*/
	if (!dev)
	{
		printf("dev is null\n");
		return -1;
	}

	if (nRecMode != 0x00 && nRecMode != 0x01)
	{
		printf("nRecMode != 0x00 && nRecMode != 0x01\n");
		return -2;
	}

	if (nMulMode != 0x00 && nMulMode != 0x01)
	{
		printf("nMulMode != 0x00 && nMulMode != 0x01\n");
		return -3;
	}

	if (!pImagePath)
	{
		printf("pImagePath is null\n");
		return -4;
	}

	if (!strlen(pImagePath))
	{
		printf("length of pImagePath is empty\n");
		return -5;
	}
	/*Input parameter check*/
	char* imageData = nullptr;
	int imageLength = 0;
	const int packageBytes = 8080;
	int curPos = 0;
	char buff[1024] = { 0 };

	/* Load image data */
	int nRet0 = 0;
	if (nRet0 = GetImageData(pImagePath, &imageData, &imageLength))
	{
		printf("GetImageData fail nRetGetImageData = %d\n", nRet0);
		return -6;
	}
	printf("imageLength : %d\n", imageLength);

	if (!imageLength)
	{
		printf("imageData is empty\n");
		if (imageData)
		{
			free(imageData);
			imageData = nullptr;
		}
		return -7;
	}

	if (imageLength > 1024 * 1024 * 4)
	{
		printf("image size is more than 4M\n");
		if (imageData)
		{
			free(imageData);
			imageData = nullptr;
		}
		return -8;
	}
	/* Load image data */

	/* 1:1 Face Recognition */
	int nRet = 0;
	while (curPos <= imageLength)
	{
		if ((curPos + packageBytes) < imageLength) //Not last package
		{
			if (nRet = StartOnetoOneRecognizeSlice(dev, nRecMode, nMulMode, imageLength, curPos, 0, imageData + curPos, packageBytes))  //packet(Not last package) send fail
			{
				printf("packet(Not last package) send fail  nRet = %d\n", nRet);
				if (imageData)
				{
					free(imageData);
					imageData = nullptr;
				}
				return -9;
			}

			curPos += packageBytes;
		}
		else //Last package
		{
			if (nRet = StartOnetoOneRecognizeSlice(dev, nRecMode, nMulMode, imageLength, curPos, 1, imageData + curPos, imageLength - curPos))  //packet(Last package) send fail
			{
				printf("packet(Last package) send fail  nRet = %d\n", nRet);
			}
			else
			{
				printf("StartOnetoOneRecognize success nRet = %d\n", nRet);
				RegisterTrackReportCb(dev, getTrackReportDataHandle);
				RegisterRecoReportCb(dev, getReoReportDataHandle);
			}
			break;
		}
	}
	/* 1:1 Face Recognition */

	if (imageData)
	{
		free(imageData);
		imageData = nullptr;
	}
	return nRet;
}

// M20 disconnection from host machine
int DisConnectDev(void* dev)
{
	if (DisconnectSerial(dev))
	{

		printf("DisonnectSerial failed\n");
		return -1;
	}
	else
	{
		printf("DisonnectSerial success\n");
	}

	if (DisconnectCamera(dev))
	{

		printf("DisconnectCamera failed\n");
		return -1;
	}
	else
	{
		printf("DisconnectCamera success\n");
	}

	if (DeInit(dev))
	{
		printf("DeInit failed\n");
		return -2;
	}
	else
	{
		printf("DeInit success\n");
	}

	return 0;
}

// Callback function
void getReoReportDataHandle(char* value, int len)
{
	if (len > 4)
	{
		printf("RecoData : %s\n", value + 4);
	}
}

// Callback function
void getTrackReportDataHandle(char* value, int len)
{
	if (len > 4)
	{
		printf("TrackData : %s\n", value + 4);
	}
}

//Get recognition mode and Multi-face mode
int GetRecModeAndMulMode(int* pRecMode, int* pMulMode)
{
	int cmdNum = -1;
	char cmdStr[10] = { 0 };
	if (pRecMode == nullptr || pMulMode == nullptr)
	{
		printf("pRecMode == nullptr || pMulMode == pMulMode\n");
		return -1;
	}

	printf("\n0:Single-face + Only recognition\n");
	printf("1:Single-face + Recognition and liveness\n");
	printf("Please input num(0/1) : ");
	scanf("%s", cmdStr);
	if (StringToInt(cmdStr, &cmdNum))
	{
		printf("input num is invalid\n");
		return -2;
	}

	if (cmdNum < 0 || cmdNum > 1)
	{
		return -3;
	}

	switch (cmdNum)
	{
	case 0: *pRecMode = 0; *pMulMode = 0; break;
	case 1: *pRecMode = 1; *pMulMode = 0; break;
	default: return -4;
	}

	return 0;
}

//Convert string to integer
int StringToInt(const char* str, int* pNum)
{

	if (!(str && strlen(str)))
	{
		return -1;
	}

	if (!pNum)
	{
		return -2;
	}

	*pNum = atoi(str);

	if (*pNum == 0 && (!(strlen(str) == sizeof(char) && str[0] == '0')))
	{
		return -3;
	}

	return 0;
}

vector<string> split(string str, string pattern)
{
	string::size_type pos;
	vector<string> result;
	str += pattern;//扩展字符串以方便操作
	int size = str.size();
	for (int i = 0; i < size; i++)
	{
		pos = str.find(pattern, i);
		if (pos < size)
		{
			string s = str.substr(i, pos - i);
			result.push_back(s);
			i = pos + pattern.size() - 1;
		}
	}
	return result;
}

int TestProcess()
{
	char videoDevBuf[1024] = { 0 };
	char serialBuf[1024] = { 0 };

	/* Detect whether M20 plugged into Raspberry */
	EnumDevice(videoDevBuf,
		sizeof(videoDevBuf),
		serialBuf,
		sizeof(serialBuf));
	printf("videoDevBuf : %s serialBuf : %s \n", videoDevBuf, serialBuf);

	if (!strlen(serialBuf))
	{
		printf("devices(M20) is not connected\n");
		return -1;
	}

	int serialNum = 0;
	vector<string> serialVec = split(string(serialBuf), "|");
	if (serialVec.size() > 1)
	{
		for (int i = 0; i < serialVec.size(); i++)
		{
			printf("(%d)%s\n", i, serialVec.at(i).c_str());
		}
		printf("Select serial num(0 - %d) : ", (int)(serialVec.size() - 1));
		scanf("%d", &serialNum);
		if (serialNum < 0 || serialNum >= serialVec.size())
		{
			printf("serial num input invalid\n");
			return -3;
		}
	}

	void* dev = Init();
	if (!dev)
	{
		printf("Init failed\n");
		return -4;
	}
	else
	{
		printf("Init success\n");
	}

	if (ConnectSerial(dev, serialVec.at(serialNum).c_str()))
	{
		printf("ConnectSerial failed\n");
		return -6;
	}
	else
	{
		printf("ConnectSerial success\n");
	}
	/* Connect M20 to host machine */

	/* Check whether M20 connection is succesful */
	if (Ping(dev, "PingTest...", strlen("PingTest...")))
	{
		printf("Ping failed\n");
		return -7;
	}
	else
	{
		printf("Ping success\n");
	}
	/* Check whether M20 connection is succesful */


	int cmdNum;
	char cmdStr[10] = { 0 };
	bool isStop = false;
	CloseAutoUploadFaceInfoInFrame(dev);
	while (!isStop)
	{
		printf("\n0:Add Face\n1:Start 1:N Recognize\n2:Start 1:1 Recognize\n3:Quit\n");
		printf("Please input num(0 - 3) : ");
		scanf("%s", cmdStr);
		CloseAutoUploadAiInfo(dev);	// M20 SDK API
		if (StringToInt(cmdStr, &cmdNum))
		{
			printf("input num is invalid\n");
			continue;
		}
		switch (cmdNum)
		{
			// Add Face photo into M20
		case 0:
			AddFaceByID(dev);           // UT function
			break;

			// 1:N Face Recognition
		case 1:
		{
			int nRecMode = -1;
			int nMulMode = -1;
			if (!GetRecModeAndMulMode(&nRecMode, &nMulMode))  		 // UT function
			{
				OpenAutoUploadAiInfo(dev, 0, 0);					 // M20 SDK API
				StartOnetoNumRecognize(dev, nRecMode, nMulMode);     // M20 SDK API
				RegisterTrackReportCb(dev, getTrackReportDataHandle); // M20 SDK API
				RegisterRecoReportCb(dev, getReoReportDataHandle);	 // M20 SDK API
			}
			else
			{
				printf("GetRecModeAndMulMode fail\n");
			}
			break;
		}
		// 1:1 Face Recognition
		case 2:
		{
			int nRecMode = -1;
			int nMulMode = -1;
			if (!GetRecModeAndMulMode(&nRecMode, &nMulMode))  		 					// UT function
			{
				OpenAutoUploadAiInfo(dev, 0, 0);					 					// M20 SDK API
				OnetoOneRecognizeSlice(dev, nRecMode, nMulMode, (const char*)"2.jpg");  // UT function
			}
			else
			{
				printf("GetRecModeAndMulMode fail\n");
			}
			break;
		}
		// Quit
		case 3:
		{
			DisConnectDev(dev);             // UT function
			isStop = true;
			break;
		}
		default:
			break;
		}
	}

	return 0;
}
