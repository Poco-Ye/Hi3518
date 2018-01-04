#include "LocalSDK/LocalSdk.h"
#include <string.h>
#include <stdio.h>
#include <sys/times.h>
#include <sys/time.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>



static long g_Handle[32];
static FILE *g_pFile[32];
LOCALSDK_DEVICE_INFO_V2 g_DevInfo;

char *picture_buff;
int picture_Index;



void CatchJPGPic(int)
{

		memset(picture_buff, 0, 2000000);
		int length = 0;
		LOCALSDK_TrigerSnap(0,1);
		LOCALSDK_CatchJPGPic(0, picture_buff, 2000000, &length);
		if (length > 0)
		{
			char szFileName[32];
			snprintf(szFileName, sizeof(szFileName), "/home/sdk_%dr.jpg", picture_Index);
			FILE *pFile = fopen(szFileName, "w+");
			fwrite(picture_buff, 1, length, pFile);
			fclose(pFile);
			picture_Index++;
			printf("get pic %s\n",szFileName);
		}
		printf("===> cat  nret (%d)   \n", length);
		signal(SIGALRM, CatchJPGPic);

}





int TalkCallBack(long lRealHandle, unsigned char *pBuffer, int nLen, unsigned long dwUser)
{
  	printf("lRealHandle: %x, nLen: %d, dwUser:%d \n", lRealHandle, nLen, dwUser);
	if (g_pFile[dwUser] == NULL)
	{     
	      printf("g_pFile[dwUser] ===\n");
		char szFile[64];
		snprintf(szFile, sizeof(szFile), "/home/Talk.pcm", dwUser);
		g_pFile[dwUser] = fopen(szFile, "wb+");
		if (g_pFile[dwUser] == NULL)
		{
			printf("file open fail \n");
			return -1;
		}
	}
	if(nLen != fwrite(pBuffer, 1, nLen, g_pFile[dwUser]))
	{	
		printf("chn: %d write fail \n", dwUser);
	}
	return 0;
}

int Talk()
{

	LOCALSDK_AUDIOIN_FORMAT audioInFormat;
	audioInFormat.iBitRate = 128;
	audioInFormat.iEncodeType = AUDIO_ENCODE_G711_ALAW;
	audioInFormat.iSampleBit = 8;
	audioInFormat.iSampleRate = 8000;
	int nRet = LOCALSDK_SetAudioFormatInfo(&audioInFormat);
	if (nRet != LOCALSDK_SUCCESS)
	{
		printf("LOCALSDK_SetAudioFormatInfo Fail, error %d", nRet);
		return -1;
	}
	int TuRt = LOCALSDK_VoiceCommStart(TalkCallBack, 0);
	printf("============TuRt=%d\n",TuRt);

}

int main()
{

	struct itimerval value,ovalue;
	memset(g_Handle, 0, sizeof(g_Handle));
	memset(g_pFile, 0, sizeof(g_pFile));
    picture_buff =(char*)malloc(2000000*sizeof(char));	
	LOCALSDK_StartUp();

	signal(SIGALRM, CatchJPGPic);
	value.it_value.tv_sec = 3;
	value.it_value.tv_usec = 0;
	value.it_interval.tv_sec = 3;
	value.it_interval.tv_usec = 0;
	setitimer(ITIMER_REAL, &value, &ovalue);


	

    int nRet = LOCALSDK_SUCCESS;
	printf("start Get DevInfo   \n");
	nRet = LOCALSDK_GetDevInfo(&g_DevInfo);
	if(LOCALSDK_SUCCESS == nRet)
	{
		printf("nAlarmInNum: %d, nAlarmOutNum: %d, nAudioNum: %d, nHddNum: %d, nPlaybackNum: %d, nSubstreamNum: %d, nVideoNum: %d, \
			szDeviceName: %s, szDeviceType: %s, uiIP: %x, usPort: %d, Version: %s, SerialNum: %s, DevMaxSupportCh:%d;videostandard:%d;\n",
			  g_DevInfo.nAlarmInNum, g_DevInfo.nAlarmOutNum, g_DevInfo.nAudioNum, g_DevInfo.nHddNum, g_DevInfo.nPlaybackNum,
			  g_DevInfo.nSubstreamNum, g_DevInfo.nVideoNum, g_DevInfo.szDeviceName, g_DevInfo.szDeviceType, g_DevInfo.uiIP, 
			  g_DevInfo.usPort, g_DevInfo.szVersion, g_DevInfo.szSerialNo, g_DevInfo.maxchnum,g_DevInfo.videostandard);
		LOCALSDK_PlayBackInit(1);
		printf("nRet = %d\n",nRet);
	}
	else
	{
		printf("LOCALSDK_GetDevInfo Fail, error %d\n", nRet);
		return -1;
	}

    
    Talk();


    while(1);

	LOCALSDK_VoiceCommStop(0);


	for (int i = 0; i < 32; i++)
	{
		if (g_pFile[i] != NULL)
		{
			fclose(g_pFile[i]);
			g_pFile[i] = NULL;
		}
	}
	free(picture_buff);
	picture_buff =NULL;
	LOCALSDK_CleanUp();
	return 0;
}






