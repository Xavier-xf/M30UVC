#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include "../../../include/ai_camera.h"

#ifdef WIN32
#include <windows.h>
#else
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

// Callback function
void getReoReportDataHandle(char* value, int len);
void getTrackReportDataHandle(char* value, int len);
// Callback function

//UT function declare


//UT function implement

//Get image content and length of image bytes 
int GetImageData(const char* pImagePath, char** ppImageData, int* pImageDataLength)
{	
	if(!(pImagePath && strlen(pImagePath)))
	{
		printf("!(pImagePath && strlen(pImagePath))\n");
		return -1;
	}
	
	if(!pImageDataLength)
	{
		printf("!pImageDataLength\n");
		return -2;
	}
	
	unsigned int nLen = 0;
	unsigned int imageLength = 0;
		
#ifdef WIN32
	/*refer:
	 * https://bbs.csdn.net/topics/390431172?list=4181305
	 * https://jingyan.baidu.com/article/cbcede0741ef6902f50b4d6d.html
	 * https://www.cnblogs.com/l1pe1/p/14436808.html
	 */ 
	HANDLE hFile = CreateFile(pImagePath,GENERIC_READ,FILE_SHARE_READ,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
	if(hFile == INVALID_HANDLE_VALUE)
	{
		printf("file(%s) open fail\n", pImagePath);
		return -3;
	}
	
	imageLength = GetFileSize(hFile,NULL);
	if(INVALID_FILE_SIZE == dwLength)
	{
		printf("file(%s) content is empty\n", pImagePath);
		CloseHandle(hFile);
		return -4;
	}
	
	(*ppImageData) = (char*)malloc(imageLength);
	if((*ppImageData) == NULL)
	{
		printf("malloc fail\n");
		CloseHandle(hFile);
		return -5;
	}
	
	ReadFile(hFile, (*ppImageData), imageLength, &nLen,NULL);
	if(nLen != imageLength)
	{
		printf("read image data is not complete nLen = %d imageLength = %d\n", nLen, imageLength);
		free(*ppImageData);
		(*ppImageData) = NULL;
		CloseHandle(hFile);	
		return -6;
	}		
	CloseHandle(hFile);			
	(*pImageDataLength) = imageLength;		  
#else	
	int fd = -1;	
	
	/* Load image data */		
	if((fd = open(pImagePath, O_RDONLY)) < 0)
	{
		printf("file(%s) open fail\n", pImagePath);
		return -3;
	}
	
	imageLength = lseek(fd, 0, SEEK_END); //文件指针移到文件尾,得到当前指针位置，既文件的长度
	printf("imageLength = %d\n", imageLength);	
	
	if(imageLength == 0)
	{
		printf("file(%s) content is empty\n", pImagePath);
		close(fd);
		return -4;
	}
	
	(*ppImageData) = (char*)malloc(imageLength);
	if((*ppImageData) == NULL)
	{
		printf("malloc fail\n");
		close(fd);
		return -5;
	}
	
	lseek(fd, 0, SEEK_SET); //文件指针恢复到文件头位置
	nLen = read(fd, (*ppImageData), imageLength);		
	if(nLen != imageLength)
	{
		printf("read image data is not complete nLen = %d imageLength = %d\n", nLen, imageLength);
		free(*ppImageData);
		(*ppImageData) = NULL;
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
	if(!dev)
	{
		printf("dev is null\n");
		return -1;	
	}
	
	char faceID[32] = {0};
	int addFaceRet = 0;
	char faceRetDesc[1024] = {0};
	printf("\nInput FaceID : ");
	scanf("%s",faceID);
	
	// Add face photo to M20 device
	addFaceRet = AddFace(dev, faceID, strlen(faceID));
	
	// Check whether the face photo is added successful or not
	switch(addFaceRet)
	{			
		case 0:strcpy(faceRetDesc,"Add image ok.");break;    
		case 1:strcpy(faceRetDesc,"Add image failed,The picture without faces!");break;
		case 2:strcpy(faceRetDesc,"Add image failed,The picture has multi-faces !");break;
		case 3:strcpy(faceRetDesc,"Add image failed,The face area is too small !");break;
		case 4:strcpy(faceRetDesc,"Add image failed,The Align score is too low!");break;
		case 5:strcpy(faceRetDesc,"Add image failed,The picture has a side face!");break;
		case 6:strcpy(faceRetDesc,"Add image failed,The face image is fuzzy !");break;
		case 7:strcpy(faceRetDesc,"Add image failed,The picture faces is too far!");break;
		case 8:strcpy(faceRetDesc,"Add image failed,init process failed!");break;
		case 9:strcpy(faceRetDesc,"Add image failed,the function arg is invalid !");break;
		case 10:strcpy(faceRetDesc,"Add image failed,the feature file is invalid !");break;
		case 11:strcpy(faceRetDesc,"Add image failed,HW_AUTH init failed!");break;
		case 12:strcpy(faceRetDesc,"Add image failed,the LICENSE add failed!");break;
		case 13:strcpy(faceRetDesc,"Add image failed,the id is not exist!");break;
		case 14:strcpy(faceRetDesc,"Add image failed,please take off your mask!");break;
		case 15:strcpy(faceRetDesc,"Add image failed,the Face database is full!");break;
		case 16:strcpy(faceRetDesc,"Add image failed,the id is is invalid!");break;
		case 17:strcpy(faceRetDesc,"Add image failed,the files saved failed");break;
		case 18:strcpy(faceRetDesc,"Add image failed,the file is not jpg!");break;
		case 19:strcpy(faceRetDesc,"Add image failed,the RPC op-failed!");break;
		case 20:strcpy(faceRetDesc,"Add image failed,the unknown TAG!");break;
		default:strcpy(faceRetDesc,"Add image Timeout!");break;
    }    
				
	printf("AddFace return : %d faceRetDesc : %s\n", addFaceRet, faceRetDesc);	

	return 0;
}

// 1:1 authentication
int OnetoOneRecognizeSlice(void* dev, int nRecMode, int nMulMode, const char* pImagePath)
{	
	/*Input parameter check*/
	if(!dev)
	{
		printf("dev is null\n");
		return -1;	
	}
	
	if(nRecMode != 0x00 && nRecMode != 0x01)
	{
		printf("nRecMode != 0x00 && nRecMode != 0x01\n");
		return -2;	
	}
	
	if(nMulMode != 0x00 && nMulMode != 0x01)
	{
		printf("nMulMode != 0x00 && nMulMode != 0x01\n");
		return -3;	
	}
	
	if(!pImagePath)
	{
		printf("pImagePath is null\n");		
		return -4;	
	}
	
	if(!strlen(pImagePath))
	{
		printf("length of pImagePath is empty\n");		
		return -5;	
	}
	/*Input parameter check*/				
	char* imageData = NULL;
	int imageLength = 0;	
	const int packageBytes = 8080;
	int curPos = 0;
	char buff[1024] = {0};	
	
	/* Load image data */	
	int nRet0 = 0;	
	if(nRet0 = GetImageData(pImagePath, &imageData, &imageLength))
	{
		printf("GetImageData fail nRetGetImageData = %d\n", nRet0);		
		return -6;	
	}						
	printf("imageLength : %d\n", imageLength);	
		
	if(!imageLength)
	{
		printf("imageData is empty\n");
		if(imageData)
		{
			free(imageData);
			imageData = NULL;
		}
		return -7;
	}
	
	if(imageLength > 1024*1024*4)
	{
		printf("image size is more than 4M\n");
		if(imageData)
		{
			free(imageData);
			imageData = NULL;
		}
		return -8;
	}
	/* Load image data */
	
	/* 1:1 Face Recognition */
	int nRet = 0;		
	while(curPos <= imageLength)
	{				
		if((curPos + packageBytes) < imageLength) //Not last package
		{
			if(nRet = StartOnetoOneRecognizeSlice(dev, nRecMode, nMulMode, imageLength, curPos, 0, imageData + curPos, packageBytes))  //packet(Not last package) send fail
			{
				printf("packet(Not last package) send fail  nRet = %d\n", nRet);
				if(imageData)
				{
					free(imageData);
					imageData = NULL;
				}
				return -9;
			}
			
			curPos += packageBytes;
		}
		else //Last package
		{
			if(nRet = StartOnetoOneRecognizeSlice(dev, nRecMode, nMulMode, imageLength, curPos, 1, imageData + curPos, imageLength - curPos))  //packet(Last package) send fail
			{
				printf("packet(Last package) send fail  nRet = %d\n", nRet);						
			}
			else
			{
				printf("StartOnetoOneRecognize success nRet = %d\n", nRet);
				RegisterTrackReportCb(dev,getTrackReportDataHandle);				
				RegisterRecoReportCb(dev,getReoReportDataHandle);
			}
			break;	
		}																			    
	}
	/* 1:1 Face Recognition */
	
	if(imageData)
	{
		free(imageData);
		imageData = NULL;
	}	
	return nRet;
}

// M20 disconnection from host machine
int DisConnectDev(void* dev)
{
	if(DisconnectSerial(dev))
	{
	
		printf("DisonnectSerial failed\n");
		return -1;
	}
	else
	{	
		printf("DisonnectSerial success\n");
	}

	if(DeInit(dev))
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
	if(len > 4)
	{
		printf("RecoData : %s\n",value + 4);
	}
}

// Callback function
void getTrackReportDataHandle(char* value, int len)
{
	if(len > 4)
	{
		printf("TrackData : %s\n",value + 4);
	}
}

//Get recognition mode and Multi-face mode
int GetRecModeAndMulMode(int* pRecMode, int* pMulMode)
{
	int cmdNum = -1;
	char cmdStr[10] = {0};
	if(pRecMode == NULL || pMulMode == NULL)
	{
		printf("pRecMode == NULL || pMulMode == NULL\n");
		return -1;
	}
	
	printf("\n0:Single-face + Only recognition\n");
	printf("1:Single-face + Recognition and liveness\n");
	printf("2:Multi-face  + Only recognition\n");
	printf("3:Multi-face  + Recognition and liveness\n");
	printf("Please input num(0/1/2/3) : ");
	scanf("%s", cmdStr);	
	if(StringToInt(cmdStr, &cmdNum))
	{
		printf("input num is invalid\n");
		return -2;
	}
	
	if(cmdNum < 0 || cmdNum > 3)
	{
		return -3;
	}
		
	switch(cmdNum)
	{
		case 0 : *pRecMode = 0; *pMulMode = 0; break;
		case 1 : *pRecMode = 1; *pMulMode = 0; break;
		case 2 : *pRecMode = 0; *pMulMode = 1; break;
		case 3 : *pRecMode = 1; *pMulMode = 1; break;
		default : return -4;															
	}
	
	return 0;
}

//Convert string to integer
int StringToInt(const char* str, int* pNum)
{

	if(!(str && strlen(str)))
	{
		return -1;
	}
	
	if(!pNum)
	{
		return -2;
	}
	
	*pNum = atoi(str);
	
	if(*pNum == 0 && (!(strlen(str) == sizeof(char) && str[0] == '0')))
	{			
		return -3;	
	}

	return 0;
}

//UT function implement

int main()
{	
	char videoDevBuf[1024] = {0};
	char serialBuf[1024]   = {0};

    /* Detect whether M20 plugged into Raspberry */
	EnumDevice(videoDevBuf,
		   sizeof(videoDevBuf),
		   serialBuf,
		   sizeof(serialBuf));
	printf("videoDevBuf : %s serialBuf : %s \n", videoDevBuf ,serialBuf);

	if(!strlen(serialBuf))
	{
		printf("devices(M20) is not connected\n");
		return -1;
	}
	if(strchr(serialBuf,'|'))
	{
		printf("more than one devices is connected\n");
		return -2;
	}
	printf("one device(%s) is connected\n",serialBuf);
    /* Detect whether M20 plugged into Raspberry */
	
	/* Initialize M20 SDK */
	void* dev = Init();
	if(!dev)
	{
		printf("Init failed\n");
		return -3;
	}
	else
	{
		printf("Init success\n");
	}
    /* Initialize M20 SDK */
	
	/* Connect M20 to host machine */
	if(ConnectSerial(dev, serialBuf))
	{
		printf("ConnectSerial failed\n");
		return -4;
	}
	else
	{
		printf("ConnectSerial success\n");
	}
	/* Connect M20 to host machine */
	
	/* Check whether M20 connection is succesful */
	if(Ping(dev, "PingTest...", strlen("PingTest...")))
	{
		printf("Ping failed\n");
		return -5;
	}
	else
	{
		printf("Ping success\n");
	}
	/* Check whether M20 connection is succesful */
	

	int cmdNum;
	char cmdStr[10] = {0};
	bool isStop = false;
	while(!isStop)
	{
		printf("\n0:Add Face\n1:Start 1:N Recognize\n2:Start 1:1 Recognize\n3:Quit\n");
		printf("Please input num(0/1/2/3) : ");
		scanf("%s", cmdStr);
		CloseAutoUploadAiInfo(dev);	// M20 SDK API
		if(StringToInt(cmdStr, &cmdNum))
		{
			printf("input num is invalid\n");
			continue;
		}		
		switch(cmdNum)
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
				if(!GetRecModeAndMulMode(&nRecMode, &nMulMode))  		 // UT function
				{
					OpenAutoUploadAiInfo(dev, 0, 0);					 // M20 SDK API
					StartOnetoNumRecognize(dev, nRecMode, nMulMode);     // M20 SDK API
					RegisterTrackReportCb(dev,getTrackReportDataHandle); // M20 SDK API			
					RegisterRecoReportCb(dev,getReoReportDataHandle);	 // M20 SDK API	
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
				if(!GetRecModeAndMulMode(&nRecMode, &nMulMode))  		 					// UT function
				{
					OpenAutoUploadAiInfo(dev, 0, 0);					 					// M20 SDK API
					OnetoOneRecognizeSlice(dev, nRecMode, nMulMode, (const char*)"1.jpg");  // UT function
				}
				else
				{
					printf("GetRecModeAndMulMode fail\n");
				}
				break;							
			}			
			// Quit
			case 3:
				DisConnectDev(dev);             // UT function
				isStop = true;
				break;
						
			default :
				break;
		}
	}

	return 0;
}
