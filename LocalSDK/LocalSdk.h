#ifndef _LOCAL_SDK_H_
#define _LOCAL_SDK_H_

#include "dataAssist.h"

// callback for realtime data
typedef int(*fRealDataCallBack) (long lRealHandle, SDK_H264_FRAME_INFO *pFrameInfo, unsigned long dwUser);

// callback for play and download
typedef int(*fPlayBackCallBack) (long lRealHandle, unsigned char *pBuffer, int nBufLen, unsigned long dwUser);
typedef int(*fPlayBackCallBackV2) (long lRealHandle, SDK_H264_FRAME_INFO *pFrameInfo, unsigned long dwUser);
typedef int(*fGetFileByTimeCallBack) (long lRealHandle, SDK_H264_FRAME_INFO *pFrameInfo, unsigned long dwUser);


typedef int(*fTalkCallBack) (long lRealHandle, unsigned char* pBuffer, int nBufLen, unsigned long dwUser);

// callback for download finish
typedef int(*fEndCallBack) (long lRealHandle, unsigned long dwUser);

// callback for upgrade
typedef int(*fProgressCallBack) (int nPos, unsigned long dwUser);

// callback for Device in abnormal, 
typedef int(*fAbnormalCallBack) (LOCAL_ALARM_MSG *pMsg, unsigned long dwUser);

// callback for RS485
typedef int(*fRS485CallBack) (unsigned char* pBuffer, int nBufLen, unsigned long dwUser);
// callback for RS232
typedef int(*fRS232CallBack) (unsigned char* pBuffer, int nBufLen, unsigned long dwUser);
// callback for GPS
typedef int(*fGPSCallBack) (unsigned char* pBuffer, int nBufLen, unsigned long dwUser);

//callback for PreRecord
typedef int(*fPRCallBack)(SDK_H264_FRAME_INFO *pFrameInfo);

// callback for get static pages info, XML info as below
//<_PAGE_ _NAME_="PGCustomInfoSub" _CONTENT_="SubPag"  _W_="112" _H_="332">
//<_STATIC_ _NAME_="aaaa Line111" _CONTENT_="Line111" _W_="54" _H_="28" _RX_="24" _RY_="28"/>
//<_STATIC_ _NAME_="aaaa Line222" _CONTENT_="Line222" _W_="54" _H_="28" _RX_="24" _RY_="56"/>
//<_STATIC_ _NAME_="aaaa Line333" _CONTENT_="Line333" _W_="54" _H_="28" _RX_="24" _RY_="74"/>
//<_STATIC_ _NAME_="aaaa Line444" _CONTENT_="Line333" _W_="54" _H_="28" _RX_="24" _RY_="102"/>
//</_PAGE_>
//<_PAGE_ _NAME_="PGCustomInfo" _CONTENT_="11222222222222"  _W_="444" _H_="555">
//<_STATIC_ _NAME_="Line111" _CONTENT_="Line111" _W_="54" _H_="28" _RX_="24" _RY_="28"/>
//<_STATIC_ _NAME_="Line222" _CONTENT_="Line222" _W_="54" _H_="28" _RX_="24" _RY_="56"/>
//<_STATIC_ _NAME_="Line333" _CONTENT_="Line333" _W_="54" _H_="28" _RX_="24" _RY_="74"/>
//<_STATIC_ _NAME_="44444" _CONTENT_="55555" _W_="154" _H_="28" _RX_="24" _RY_="155"/>
//<_BUTTON_ _NAME_="SubPageButton" _CONTENT_="Line333" _LINKPAGE_="SubPag" _W_="54" _H_="28" _RX_="24" _RY_="102"/>
//</_PAGE_>
/// \param [out] pPageXML, page info describe by XML
/// \param [in] nBufLen, buffer len of pPageXML
/// \param [in] dwUser self-defined data 
/// \retval <0 fail
/// \retval 0 succ
typedef int(*fPagesInfoCallBack) (char *pPageXML, int nBufLen, unsigned long dwUser);

#ifdef __cplusplus
extern "C"{
#endif

/// SDK initialize, must call at begin
/// \retval <0 fail
/// \retval 0 succ
int LOCALSDK_StartUp();

/// SDK clear, call for clean all resource, after using SDK finished
/// \retval <0 fail
/// \retval 0 succ
int LOCALSDK_CleanUp();

/// callback for Device in abnormal,
/// \param [in] pCBFun 
/// \param [in] dwUser self-defined data 
void LOCALSDK_SetAbnormalCallBack(fAbnormalCallBack pCBFun, unsigned long dwUser);

/// Get system info, must call after sdk initialize.
/// \param [out] pDevInfo device info
/// \retval <0 fail
/// \retval =0 succ
int LOCALSDK_GetDevInfo(LOCALSDK_DEVICE_INFO_V2 *pDevInfo);

//��ʼ���ط�
int LOCALSDK_PlayBackInit(int VedioNum);

/// start real-time play
/// \param [in] nChannel video channel
/// \param [in] nStream refer to SDK_CaptureChannelTypes
/// \param [in] pCBFun callback for realtime data
/// \param [in] dwUser self-defined data 
/// \param [out] pHandle return hHandle if succ
/// \retval <0 fail
/// \retval =0 succ
int LOCALSDK_RealPlayStart(int nChannel, int nStream, fRealDataCallBack pCBFun, unsigned long dwUser, long *pHandle);

/// close rela-time play
/// \param [in] the hHandle return by LOCALSDK_RealPlayStart
/// \param [in] pCBFun callback for callback for realtime data
/// \param [in] dwUser self-defined data 
/// \retval <0 fail
/// \retval =0 succ
int LOCALSDK_RealPlayStop(int hHandle, fRealDataCallBack pCBFun, unsigned long dwUser);


/// record search
/// \param [in] lpFindInfo search condition
/// \param [in] pFindRet result of search
/// \param [in] nWaitTime search timeout value
/// \retval <0 fail
/// \retval =0 succ
int LOCALSDK_FindFile(LOCALSDK_FINDINFO* pFindInfo, LOCALSDK_FIND_FILE_RET *pFindRet, int nWaitTime = 20);
int LOCALSDK_FindFileV2(LOCALSDK_FINDINFOV2* pFindInfo, LOCALSDK_FIND_FILE_RET *pFindRet, int nWaitTime = 20);

/// record download
/// \param [in] pFileInfo file info, return by LOCALSDK_FindFile in pFindInfo
/// \param [in] pCBFun callback for record data
/// \param [in] dwUser self-defined data
/// \param [in] pEndCBFun callback for download progress
/// \param [in] dwEndUser self-defined data
/// \param [out] pHandle return hHandle if succ
/// \retval <0 fail
/// \retval =0 succ
int LOCALSDK_GetFileByName(LOCALSDK_FILE_DATA* pFileInfo, fPlayBackCallBack pCBFun, unsigned long dwUser, 
						   fEndCallBack pEndCBFun, unsigned long dwEndUser, long *pHandle);

/// record download v2 version, return one full-frame with frame info each time
/// \param [in] pFileInfo file info, return by LOCALSDK_FindFile in pFindInfo
/// \param [in] pCBFun callback for record data
/// \param [in] dwUser self-defined data
/// \param [in] pEndCBFun callback for download progress
/// \param [in] dwEndUser self-defined data
/// \param [out] pHandle return hHandle if succ
/// \retval <0 fail
/// \retval =0 succ
int LOCALSDK_GetFileByNameV2(LOCALSDK_FILE_DATA* pFileInfo, fPlayBackCallBackV2 pCBFun, unsigned long dwUser, 
						   fEndCallBack pEndCBFun, unsigned long dwEndUser, long *pHandle, int streamtype = 2);

/// stop record download
/// \param [in] lHandle, return value of LOCALSDK_GetFileByName
/// \retval <0 fail
/// \retval =0 succ
int LOCALSDK_StopGetFile(long lHandle);

/// get frame info
/// \param [in] pFileInfo file info, return by LOCALSDK_FindFile in pFindInfo
/// \param [in] pIndexFileName full path for frame info to save,(directory writeable in DVR is /var),
///             must delete this file after using finished
///				content of frame info: FRAME_INDEX. item number of FRAME_INDEX is frame number of record file
/// \retval <0 fail
/// \retval =0 succ
int LOCALSDK_GetFrameIndexs(LOCALSDK_FILE_DATA *pFileInfo, char *pIndexFileName);

/// get file attribute
/// \param [in] pFileInfo file info, return by LOCALSDK_FindFile in pFindInfo
/// \param [out] pFileAttr file attribute
/// \retval <0 fail
/// \retval =0 succ
int LOCALSDK_GetFileAttr(LOCALSDK_FILE_DATA *pFileInfo, LOCAL_FILE_ATTR *pFileAttr);

/// remote record play
/// \param [in] pFileInfo file info, return by LOCALSDK_FindFile in pFindInfo
/// \param [in] pCBFun callback for record data
/// \param [in] dwUser self-defined data
/// \param [in] pEndCBFun callback for download progress
/// \param [in] dwEndUser self-defined data
/// \param [out] pHandle return hHandle if succ
/// \retval <0 fail
/// \retval =0 succ
int LOCALSDK_PlayBackByName(LOCALSDK_FILE_DATA *pFileInfo, fPlayBackCallBack pCBFun, unsigned long dwUser,
							fEndCallBack pEndCBFun, unsigned long dwEndUser, long *pHandle);

/// stop remote record play
/// \param [in] lHandle, return value of LOCALSDK_GetFileByName or LOCALSDK_GetFileByNameV2
/// \retval <0 fail
/// \retval =0 succ
bool LOCALSDK_StopPlayBack(long lHandle);

/// local record play
/// \param [in] pFileName full path of file name
/// \param [in] pCBFun callback for play over
/// \param [in] dwEndUser self-defined data
/// \retval <0 fail
/// \retval =0 succ
bool LOCALSDK_PlayBackLocalFile(LOCALSDK_FILE_INFO * PlayBackControl);

/// stop local record play
/// \param [in] bDesktop true - return to desktop, false- stop play,no to return desktop
/// \retval <0 fail
/// \retval =0 succ
bool LOCALSDK_StopPlayBackLocalFile(bool bDesktop);

/// get server info
/// \param [out] pSvrInfo server info
/// \retval <0 fail
/// \retval =0 succ
int LOCALSDK_GetXingWanInfo(LOCALSDK_XINGWAN_INFO *pSvrInfo);

/// get wellsun server info
/// \param [out] pSvrInfo wellsun server info
/// \retval <0 fail
/// \retval =0 succ
int LOCALSDK_GetWellSunSvrInfo(LOCALSDK_WELLSUN_INFO *pSvrInfo);

/// set system time
/// \param [int] pSysTime system time
/// \retval <0 fail
/// \retval =0 succ
int LOCALSDK_SetSystemTime(LOCALSDK_TIME *pSysTime);

/// video color
/// \param [in] nChannel: channel No. begin at 0
/// \param [in] pColor: video color
/// \retval <0 fail
/// \retval =0 succ
int LOCALSDK_SetVideoColor(int nChannel, LOCALSDK_VIDEOCOLOR *pColor);

/// get video color
/// \param [in] nChannel: channel No. begin at 0
/// \param [in] pColor: video color
/// \retval <0 fail
/// \retval =0 succ
int LOCALSDK_GetVideoColor(int nChannel, LOCALSDK_VIDEOCOLOR *pColor);

/// get encode config
/// \param [in] nChannel: channel No. begin at 0
/// \param [in] pEncode: encode config
/// \retval <0 fail
/// \retval =0 succ
int LOCALSDK_GetVideoEncode(int nChannel, LOCALSDK_VIDEOENCODE *pEncode);

/// get digitchannel config
/// \param [in] nChannel: channel No. begin at 0
/// \param [in] pEncode: digitchnnel config
/// \retval <0 fail
/// \retval =0 succ
int LOCALSDK_GetNetDigitChnConfig(int nChannel, LOCALSDK_NETDIGITCHNCONFIG *pConfig);

/// get digitchannel config
/// \param [in] nChannel: channel No. begin at 0
/// \param [in] pEncode: digitchnnel config
/// \retval <0 fail
/// \retval =0 succ 
int LOCALSDK_SetNetDigitChnConfig(int nChannel, LOCALSDK_NETDIGITCHNCONFIG *pConfig);

/// set encode config
/// \param [in] nChannel: channel No. begin at 0
/// \param [in] pEncode: encode config
/// \retval <0 fail
/// \retval =0 succ
int LOCALSDK_SetVideoEncode(int nChannel, LOCALSDK_VIDEOENCODE *pEncode);

/// get motion config
/// \param [in] nChannel: channel No. begin at 0
/// \param [in] pMotion: motion detect config
/// \retval <0 fail
/// \retval =0 succ
int LOCALSDK_GetMotionConfig(int nChannel, LOCALSDK_MOTION_DETECT *pMotion);

/// set motion config
/// \param [in] nChannel: channel No. begin at 0
/// \param [in] pEncode: motion detect config
/// \retval <0 fail
/// \retval =0 succ
int LOCALSDK_SetMotionConfig(int nChannel, LOCALSDK_MOTION_DETECT *pMotion);

/// PTZ control
/// \param [in] nChannel: channel No. begin at 0
/// \param [in] pPtzOpt PTZ cmd
/// \retval <0 fail
/// \retval =0 succ
int LOCALSDK_PtzControl(int nChannel, LOCALSDK_PTZ_OPT *pPtzOpt);

/// system state
/// \param [in] pWorkState: system state
/// \retval <0 fail
/// \retval =0 succ
int LOCALSDK_GetSystemState(LOCALSDK_WORKSTATE *pWorkState);

/// set alarm out
/// \param [in] nChannel: channel No., begin at 0, 0xff: all channel
/// \param [in] nStatus: Status - 0��config 1��open 2��close
/// \retval <0 fail
/// \retval =0 succ
int LOCALSDK_SetAlarmOut(int nChannel, int nStatus);

/// read data from 485
/// \param [in] pBuf: buffer for data read
/// \param [in] nLen: data len, less than 255
/// \retval <0 fail
/// \retval >0 data len have readed
int LOCALSDK_RS485Read(char *pBuf, int nLen);

int LOCALSDK_RS485Start(fRS485CallBack fRS485CB, unsigned long dwUser);
int LOCALSDK_RS485Stop(long lRealHandle);

//Rs232 callback mode 
int LOCALSDK_RS232Start(fRS232CallBack fRS232CB, unsigned long dwUser);
int LOCALSDK_RS232Stop(long lRealHandle);

int LOCALSDK_GPSStart(fGPSCallBack fGPSCB, unsigned long dwUser);
int LOCALSDK_GPSStop(long lRealHandle);

/// write data to 485
/// \param [in] pBuf: data buffer
/// \param [in] nLen: data len, less than 255
/// \retval <0 fail
/// \retval >0 data len have written
int LOCALSDK_RS485Write(const char *pBuf, int nLen);

/// read 232 data
/// \param [in] pBuf: data buffer
/// \param [in] nLen data len, less than 255
/// \retval <0 fail
/// \retval >0 data len have readed
int LOCALSDK_RS232Read(char *pBuf, int nLen);

/// write data to 232
/// \param [in] pBuf: data buffer
/// \param [in] nLen: data len, less than 255
/// \retval <0 fail
/// \retval >0 data len have written
int LOCALSDK_RS232Write(const char *pBuf, int nLen);

/// reboot system
int LOCALSDK_Reboot();

/// shutdown system
int LOCALSDK_ShutDown();

/// must call it before upgrade
/// \retval <0 fail
/// \retval >0 data len have readed
int LOCALSDK_SyetemUpgradeInit();

/// upgrade fireware
/// \param [in] pUpgradeFile: full name of fireware
/// \retval <0 fail
/// \retval >0 data len have readed
int LOCALSDK_SyetemUpgrade(const char *pUpgradeFile, fProgressCallBack pCBFun,  unsigned long dwUser);

//�����������Ȼص�
void LOCALSDK_SetUpgradeProcessCallBack(fProgressCallBack pCBFun, unsigned long dwUser);

/// set osd info
/// \param [in] nChannel: channel No. begin at 0, 0xff means all channels
/// \param [in] pOSDInfo: refer to OSD_INFO
/// \retval <0 fail
/// \retval =0 succ
int LOCALSDK_SetOSDInfo(int nChannel, LOCALSDK_OSD_INFO *pOSDInfo);

/// set osd info
/// \param [in] nChannel: channel No. begin at 0, 0xff means all channels
/// \param [in] pOSDInfo: refer to LOCALSDK_OSD_INFO_V2
/// \retval <0 fail
/// \retval =0 succ
int LOCALSDK_SetOSDInfoV2(int nChannel, LOCALSDK_OSD_INFO_V2 *pOSDInfo);

/// get motion detect info
/// \param [in] nChannel: channel No. begin at 0
/// \param [in] pResult: refer to MOTION_DETECT_RESULT
/// \retval <0 fail
/// \retval =0 succ
int LOCALSDK_GetMotionResult(int nChannel, MOTION_DETECT_RESULT *pResult);

/// create static GUI page
/// \param [in] pCBFun: callback for get pages info
/// \param [in] dwUser: self-defined data
/// \retval <0 fail
/// \retval =0 succ
void LOCALSDK_SetCreateGUIPageCallBack(fPagesInfoCallBack pCBFun, unsigned long dwUser);

/// catch jpg picture 
/// \param [in] nChannel: channel No. begin at 0
/// \param [in] pBuffer: picture data buffer
/// \param [in] nChannel: buffer len
/// \param [out] pPicLen: point of picture len 
/// \retval <0 fail
/// \retval =0 succ
int LOCALSDK_CatchJPGPic(int nChannel, char *pBuffer, int nBufLen, int *pPicLen);


int LOCALSDK_GetRecordSetting(int nChannel, LOCALSDK_RECORD_CFG *pRecConf, int StreamType = SDK_CAPTURE_CHN_MAIN);
int LOCALSDK_SetRecordSetting(int nChannel, LOCALSDK_RECORD_CFG *pRecConf, int StreamType = SDK_CAPTURE_CHN_MAIN);

int LOCALSDK_GetSnapshotSetting(int nChannel, LOCALSDK_SNAPSHOT_CFG *pRecConf);
int LOCALSDK_SetSnapshotSetting(int nChannel, LOCALSDK_SNAPSHOT_CFG *pRecConf);

//AlarmSetting
int LOCALSDK_GetVideoBlindConfig(int nChannel, LOCALSDK_BLIND_DETECT *pBlindConf);	
int LOCALSDK_SetVideoBlindConfig(int nChannel, LOCALSDK_BLIND_DETECT *pBlindConf);
int LOCALSDK_GetVideoLossConfig(int nChannel, LOCALSDK_GENERAL_CFG *pLossConf);
int LOCALSDK_SetVideoLossConfig(int nChannel, LOCALSDK_GENERAL_CFG *pLossConf);
int LOCALSDK_GetAlarmInputSetting(int nChannel, LOCALSDK_ALARM_CFG *pAlarmInConf);
int LOCALSDK_SetAlarmInputSetting(int nChannel, LOCALSDK_ALARM_CFG *pAlarmInConf);
int LOCALSDK_GetAlarmOutputSetting(LOCALSDK_ALARMOUT_CFG_ALL *pAlarmOutConf);
int LOCALSDK_SetAlarmOutputSetting(LOCALSDK_ALARMOUT_CFG_ALL *pAlarmOutConf);
int LOCALSDK_GetNetAlarmSetting(int nChannel, LOCALSDK_GENERAL_CFG *pNetAlarmConf);
int LOCALSDK_SetNetAlarmSetting(int nChannel, LOCALSDK_GENERAL_CFG *pNetAlarmConf);

//SystemSetting
int LOCALSDK_GetNetworkSetting(LOCALSDK_NETCOMMON *pNetworkCfg);
int LOCALSDK_SetNetworkSetting(LOCALSDK_NETCOMMON *pNetworkCfg);
int LOCALSDK_GetPPPoESetting(LOCALSDK_PPPOE_CFG *pNetPPPoECfg);
int LOCALSDK_SetPPPoESetting(LOCALSDK_PPPOE_CFG *pNetPPPoECfg);
int LOCALSDK_GetCamName(int nChannel, char *pCamName, int nLen);
int LOCALSDK_SetCamName(int nChannel, char *pCamName, int nLen);
int LOCALSDK_GetPTZConfigSetting(int nChannel, LOCALSDK_PTZ_CFG *pPTZConfig);
int LOCALSDK_SetPTZConfigSetting(int nChannel, LOCALSDK_PTZ_CFG *pPTZConfig);
int LOCALSDK_GetRS232Setting(LOCALSDK_COMM_CFG *pCommConfig);
int LOCALSDK_SetRS232Setting(LOCALSDK_COMM_CFG *pCommConfig);
int LOCALSDK_GetWIFISetting(LOCALSDK_WIFI_CONFIG *pWifiConfig);
int LOCALSDK_SetWIFISetting(LOCALSDK_WIFI_CONFIG *pWifiConfig);
int LOCALSDK_GetDNSSetting(LOCALSDK_DNS_CONFIG *pConfig);
int LOCALSDK_SetDNSSetting(LOCALSDK_DNS_CONFIG *pConfig);
int LOCALSDK_GetDHCPSetting(LOCALSDK_DHCP_CONFIGALL *pConfig);
int LOCALSDK_SetDHCPSetting(LOCALSDK_DHCP_CONFIGALL *pConfig);
int LOCALSDK_GetNTPSetting(LOCALSDK_NTP_CONFIG *pConfig);
int LOCALSDK_SetNTPSetting(LOCALSDK_NTP_CONFIG *pConfig);
int LOCALSDK_GetRTSPSetting(LOCALSDK_RTSP_CONFIG *pConfig);
int LOCALSDK_SetRTSPSetting(LOCALSDK_RTSP_CONFIG *pConfig);
int LOCALSDK_GetARSPSetting(LOCALSDK_ARSP_CONFIG *pConfig);
int LOCALSDK_SetARSPSetting(LOCALSDK_ARSP_CONFIG *pConfig);
int LOCALSDK_GetAutoMaintainSetting(LOCALSDK_AUTO_MAINTAIN_CONFIG *pConfig);
int LOCALSDK_SetAutoMaintainSetting(LOCALSDK_AUTO_MAINTAIN_CONFIG *pConfig);
int LOCALSDK_GetUPNPSetting(LOCALSDK_NETUPNP_CONFIG *pConfig);
int LOCALSDK_SetUPNPSetting(LOCALSDK_NETUPNP_CONFIG *pConfig);
int LOCALSDK_GetEncodeStaticSetting(int nChannel,LOCALSDK_ENCODESTATIC_CFG*pConfig);
int LOCALSDK_SetEncodeStaticSetting(int nChannel,LOCALSDK_ENCODESTATIC_CFG *pConfig);

int LOCALSDK_GetNetPlatfromSetting(LOCALSDK_NET_PLATFORM_CONFIG *pConfig);
int LOCALSDK_SetNetPlatfromSetting(LOCALSDK_NET_PLATFORM_CONFIG *pConfig);

//��ȡ(����)3G������Ϣ
int LOCALSDK_GetWirelessSetting(LOCALSDK_WIRELESS_CONFIG *pConfig);
int LOCALSDK_SetWirelessSetting(LOCALSDK_WIRELESS_CONFIG *pConfig);

int LOCALSDK_GetOSDChannelSetting(int nChannel,LOCALSDK_OSD_CHANNELINFO *pConfig);
int LOCALSDK_SetOSDChannelSetting(int nChannel,LOCALSDK_OSD_CHANNELINFO *pConfig);


int LOCALSDK_ManualStartRecord(int nChannel);  //�ֹ���¼��,�������޹�
int LOCALSDK_ManualEndRecord(int nChannel);
int LOCALSDK_ManualStartSnap(int nChannel);     //�ֹ�������,�������޹�
int LOCALSDK_ManualEndSnap(int nChannel);


int LOCALSDK_ManualGetEncode(int nChannel,LOCALSDK_MANUAL_VIDEOENCODE *pEncodeConfig);//�ֹ���ȡ��ǰ��������,�������ļ��޹�
int LOCALSDK_ManualSetEncode(int nChannel,LOCALSDK_MANUAL_VIDEOENCODE *pEncodeConfig);

int LOCALSDK_AddUPNPPort(int nPort);
int LOCALSDK_DelUPNPPort(int nPort);
int LOCALSDK_GetUPNPExPort(int *nPort);
//for ipc only
int LOCALSDK_SetOSDDotMatrix(int nChannel,LOCALSDK_OSD_DOT_MATRIX *pConfig);
int LOCALSDK_SetOSDDotMatrixV2(int nChannel,LOCALSDK_OSD_DOT_MATRIX_V2*pConfig);

//Dev Info
int LOCALSDK_GetHDDInfo(LOCALSDK_STORAGE_INFO_ALL *pHDDInfo);

//��ȡ3g��ϸ״̬
int LOCALSDK_GetWirelessState(LOCALSDK_WIRELESS_STATE *pState);

int LOCALSDK_VoiceCommStart(fTalkCallBack fTalkCB, unsigned long dwUser);
int LOCALSDK_VoiceCommStop(long lRealHandle);
int LOCALSDK_SetAudioFormatInfo(LOCALSDK_AUDIOIN_FORMAT *pAudioFormat);
int LOCALSDK_SendVoiceCommData(char *pBuffer, int nLen);
int LOCALSDK_IsEthernetConnected();
int LOCALSDK_IsWifiConnected();
int LOCALSDK_IsWirelessConnected();

//��ȡ���������
int LOCALSDK_GetCameraSetting(int nChannel, LOCALSDK_CAMERAPARA_CONFIG *pCameraConfig);
int LOCALSDK_SetCameraSetting(int nChannel, LOCALSDK_CAMERAPARA_CONFIG *pCameraConfig);

//��ȡ�������չ����
int LOCALSDK_GetCameraExSetting(int nChannel, LOCALSDK_CAMERAPARA_EX_CONFIG *pCameraConfig);
int LOCALSDK_SetCameraExSetting(int nChannel, LOCALSDK_CAMERAPARA_EX_CONFIG *pCameraConfig);

//�ָ�Ĭ������
int LOCALSDK_SetDefaultConfig(LOCALSDK_DEFAULT_CONFIG *pconfig);

//���÷���������
int LOCALSDK_BeepSetting(LOCALSDK_BEEP_CONFIG* pBeepConfig);

//��ͨ����
int LOCALSDK_GetLocationSetting(int nChannel, LOCALSDK_LOCATION_CONFIG *pLocationConfig);
int LOCALSDK_SetLocationSetting(int nChannel, LOCALSDK_LOCATION_CONFIG *pLocationConfig);

//�ֻ��������
int LOCALSDK_GetMobileSetting(LOCALSDK_MOBILE_CONFIG * pMobileConfig);
int LOCALSDK_SetMobileSetting(	LOCALSDK_MOBILE_CONFIG * pMobileConfig);

//��ȡ�汾��Ϣ
int LOCALSDK_GetVersion(char* pVersion, int Length);//Length ΪpVersionָ���ڴ�ĳ��ȣ��������32�ֽ�

//��ȡ�û�Ȩ���б�
int LOCALSDK_GetAthorityList(LOCALSDK_ATHORITY_INFO * pUserInfoConfig);

//��ȡ���б�
int LOCALSDK_GetGroupList(LOCALSDK_GROUP_LIST * pGroupInfoConfig);

//�����û�
int LOCALSDK_SetAddUser(LOCALSDK_USER_INFO* pUserInfo);

//�޸��û�����
int LOCALSDK_SetModifyPassword(LOCALSDK_MODIFY_PASSWORD * PasswordInfo);

//��ȡ�û��б�
int LOCALSDK_GetUserList(LOCALSDK_USER_LIST *pUserList);

//¼��طŶ�λ
int LOCALSDK_SetSeekPlayBack(LOCALSDK_FILE_DATA * pFileData);

//�طű���¼��
int LOCALSDK_PlayBackLocalRec(LOCALSDK_FILE_DATA *pFileData);

//�����طű���¼��
int LOCALSDK_StopPlayBackLocalRec();

//ǿ��I֡
int LOCALSDK_ForceIFrame(LOCALSDK_FORCE_I_FRAME * pIFrame);

//������������
int LOCALSDK_SendUpgradeData(LOCALSDK_UPGRADE_DATA * pUpgradeData);

//����VPN����
int LOCALSDK_VPNConfigSetting(LOCALSDK_NET_VPN_CONFIG *PVpnConfig);

//��ȡVPN����
int LOCALSDK_VPNConfigGetting(LOCALSDK_NET_VPN_CONFIG *PVpnConfig);

//��ȡDAS����
int LOCALSDK_DASConfigGetting(LOCALSDK_DAS_SER_INFO *pDasInfo);

//����DAS����
int LOCALSDK_DASConfigSetting(LOCALSDK_DAS_SER_INFO *pDasInfo);

//��ȡVPN ״̬
int LOCALSDK_VPNStateGetting(LOCALSDK_VPN_STATE *pVpnState);

//Add Gui Osd Title
int LOCALSDK_AddGuiTitle(LOCALSDK_ADD_GUI_INFO *pGuiInfo);

//���ݿ������ûص� �� ��Ϣ����
typedef int(*fKaiNengCallBack) (LOCALSDK_CBCONFIG_KAINENG_INFO * pInfo);
int LOCALSDK_KaiNengInfoSetting(LOCALSDK_CONFIG_KAINENG_INFO *pInfo);
int LOCALSDK_KaiNengInfoGetting(LOCALSDK_CONFIG_KAINENG_INFO *pInfo);

//���øı�ص�������ע��ͽ��
int LOCALSDK_KaiNengInfoRegister(fKaiNengCallBack fKaiNengCB);
int LOCALSDK_KaiNengInfoUnRegister();

//����ƽ̨���󣬻�ȡԤ¼����
int LOCALSDK_GetPreRecord_Star(LOCALSDK_PRERECORD_INFO* pinfo, fPRCallBack fPreRecordCB);
int LOCALSDK_GetPreRecord_Stop();

//������һ���ͻ���Ҫ����һЩ�Զ�����Ϣ���úͶ�ȡ�Ľӿ�
int LOCALSDK_GetDevicePinId(LOCALSDK_CUSTOMINFO *);
int LOCALSDK_SetDevicePinId(LOCALSDK_CUSTOMINFO *);

//�ӱ��Ŀͻ������̸�ʽ��,����ʱ���ȡ�ط���Ϣ��
int LOCALSDK_SetDiskFomat(uint iPhysicalNo = 0, uint iPartNumber = 0);
int LOCALSDK_DownLoadFileByTime(LOCALSDK_FINDINFO* pFileInfo, fGetFileByTimeCallBack pCBFun, unsigned long dwUser, 
						   fEndCallBack pEndCBFun, unsigned long dwEndUser, long *pHandle);

//�ж��û������Ƿ���Ч
int LOCALSDK_IsPasswdValid(LOCALSDK_USERPW_ISVALID *);

//���մ���C7ƽ̨
int LOCALSDK_SetChuangShiInfo(LOCALSDK_CHUANGSHI_INFO *);
int LOCALSDK_GetChuangShiInfo(LOCALSDK_CHUANGSHI_INFO *);
int LOCALSDK_SetChuangShiStatus(char *);
int LOCALSDK_GetChuangShiStatus(char *);

#ifdef  _OEM_BeiJingHongTaiHeng
//������̩��ƽ̨
int LOCALSDK_SetBJHongTaiHengInfo(LOCALSDK_BJHONGTAIHENG_INFO *pInfo);
int LOCALSDK_GetBJHongTaiHengInfo(LOCALSDK_BJHONGTAIHENG_INFO *pInfo);
#endif

//��ȡͨ����Ϣ(��ǰͨ�������͸�ͨ������)
int LOCALSDK_GetChannelInfo(LOCALSDK_CHANNEL_INFO *);

int LOCALSDK_GetChannelResolution(LOCALSDK_CAPTURE_DSPINFO *pInfo);
int LOCALSDK_GetChannelResolutionV2(LOCALSDK_CAPTURE_DSPINFO_V2 *pInfo);

//�����Ϣ֡
int LOCALSDK_AddInfo(LOCALSDK_INFO_FRAME *pInfo);

int LOCALSDK_GetEmailCfg(LOCALSDK_EMAIL_CFG *pCfg);
int LOCALSDK_SetEmailCfg(LOCALSDK_EMAIL_CFG *pCfg);
//��ȡͨ������״̬
int LOCALSDK_GetDigChnState(int nChannel, LOCALSDK_DIGIT_CHN_STATE *pInfo);
//28181����
int LOCALSDK_GetSPVMNCfg(LOCALSDK_ASB_NET_VSP_CFG *pCfg);
int LOCALSDK_SetSPVMNCfg(LOCALSDK_ASB_NET_VSP_CFG *pCfg);
//wifi�����ӿ�
int LOCALSDK_WiFiSearch(LOCALSDK_WLAN_DEVICE_LIST *pCfg);

int LOCALSDK_GetChannelInfoV2(LOCALSDK_CHANNEL_INFO_V2* pInfo);
int LOCALSDK_GetNetAlarmSettingV2(int nChannel, LOCALSDK_GENERAL_CFG_V2* pNetAlarmConf);
int LOCALSDK_SetNetAlarmSettingV2(int nChannel, LOCALSDK_GENERAL_CFG_V2* pNetAlarmConf);
int LOCALSDK_SetAlarmOutputSettingV2(LOCALSDK_ALARMOUT_CFG_ALL_V2* pAlarmOutConf);
int LOCALSDK_GetAlarmOutputSettingV2(LOCALSDK_ALARMOUT_CFG_ALL_V2* pAlarmOutConf);
int LOCALSDK_SetAlarmInputSettingV2(int nChannel, LOCALSDK_ALARM_CFG_V2* pAlarmInConf);
int LOCALSDK_GetAlarmInputSettingV2(int nChannel, LOCALSDK_ALARM_CFG_V2* pAlarmInConf);
int LOCALSDK_SetVideoLossConfigV2(int nChannel, LOCALSDK_GENERAL_CFG_V2* pLossConf);
int LOCALSDK_GetVideoLossConfigV2(int nChannel, LOCALSDK_GENERAL_CFG_V2* pLossConf);
int LOCALSDK_SetVideoBlindConfigV2(int nChannel, LOCALSDK_BLIND_DETECT_V2* pBlindConf);
int LOCALSDK_GetVideoBlindConfigV2(int nChannel, LOCALSDK_BLIND_DETECT_V2* pBlindConf);
int LOCALSDK_GetMotionConfigV2(int nChannel, LOCALSDK_MOTION_DETECT_V2* pMotion);
int LOCALSDK_SetMotionConfigV2(int nChannel, LOCALSDK_MOTION_DETECT_V2* pMotion);
int LOCALSDK_GetSystemStateV2(LOCALSDK_WORKSTATE_V2*pWorkState);
//����PPPOE���ŵ���������eth0,eth2
int LOCALSDK_NetSetPPPoeIfName(char *pInfo);

//��ͨ���õĻ�ȡ������
int LOCALSDK_GetGeneralConfig(LOCALSDK_GENERAL_CONFIG *pInfo);
int LOCALSDK_SetGeneralConfig(LOCALSDK_GENERAL_CONFIG *pInfo);

int LOCALSDK_GetRealPlayBufSize();

//��ǰUTCʱ��Ļ�ȡ������
int LOCALSDK_GetCurrentUTCTime(LOCALSDK_TIME *pInfo);
int LOCALSDK_SetCurrentUTCTime(LOCALSDK_TIME *pInfo);

//ʱ���Ļ�ȡ������; �������������UTCʱ��-��ǰʱ��ʱ��ķ���������UTC+03:00������������� -180
int LOCALSDK_GetTimeZone(int *minuteswest);
int LOCALSDK_SetTimeZone(int minuteswest);

//����ͨ��ʱ��ͬ�������������ȡ
int LOCALSDK_GetTimeSyn(LOCALSDK_TIMESYNC_CONFIG *pInfo);
int LOCALSDK_SetTimeSyn(LOCALSDK_TIMESYNC_CONFIG *pInfo);

//�������õ��������ȡ(��ץͼ)
int LOCALSDK_GetVideoEncodeV2(int nChannel, LOCALSDK_VIDEOENCODEV2 *pEncode);
int LOCALSDK_SetVideoEncodeV2(int nChannel, LOCALSDK_VIDEOENCODEV2 *pEncode);

//�����������
int LOCALSDK_GetOSDDOTcfg(int nChannel, LOCALSDK_OSD_DOT_CFG *pcfg);
int LOCALSDK_SetOSDDOTcfg(int nChannel, LOCALSDK_OSD_DOT_CFG *pcfg);
//����ָ�
int LOCALSDK_GetSplitModel(LOCALSDK_SPLIT_MODEL *pcfg);
int LOCALSDK_SetSplitModel(LOCALSDK_SPLIT_MODEL *pcfg);

//FTP�й�������Ϣ��ȡ/���ýӿ�
int LOCALSDK_GetFtpCfg(LOCALSDK_FTP_CFG *pInfo);
int LOCALSDK_SetFtpCfg(LOCALSDK_FTP_CFG *pInfo);

//�쳣�����������
int LOCALSDK_GetIPConflictCfg(LOCALSDK_GENERAL_CFG *pcfg);
int LOCALSDK_SetIPConflictCfg(LOCALSDK_GENERAL_CFG *pcfg);

int LOCALSDK_GetNetAbortCfg(LOCALSDK_GENERAL_CFG *pcfg);
int LOCALSDK_SetNetAbortCfg(LOCALSDK_GENERAL_CFG *pcfg);

int LOCALSDK_GetStorageFailureCfg(LOCALSDK_STORAGE_FAIL_CFG *pcfg);
int LOCALSDK_SetStorageFailureCfg(LOCALSDK_STORAGE_FAIL_CFG *pcfg);

int LOCALSDK_GetStorageNotExistCfg(LOCALSDK_GENERAL_CFG *pcfg);
int LOCALSDK_SetStorageNotExistCfg(LOCALSDK_GENERAL_CFG *pcfg);
	
int LOCALSDK_GetStorageLowSpaceCfg(LOCALSDK_STORAGE_LOW_SPACE_CFG *pcfg);
int LOCALSDK_SetStorageLowSpaceCfg(LOCALSDK_STORAGE_LOW_SPACE_CFG *pcfg);

int LOCALSDK_GetStorageTypeCfg(LOCALSDK_STORAGE_TYPE *pInfo);
int LOCALSDK_SetStorageTypeCfg(LOCALSDK_STORAGE_TYPE *pInfo);

int LOCALSDK_GetVideoWidgetCfg(int ch, LOCALSDK_VIDEOWIDGET_CFG *pInfo);
int LOCALSDK_SetVideoWidgetCfg(int ch, LOCALSDK_VIDEOWIDGET_CFG *pInfo);

int LOCALSDK_GetExOSDCfg(int ch, LOCALSDK_OSD_CFG_V2 *pInfo);
int LOCALSDK_SetExOSDCfg(int ch, LOCALSDK_OSD_CFG_V2 *pInfo);
//���ط��Ͷ���Ϣ����绰�ӿ�
int LOCALSDK_SendSMS(LOCALSDK_SMS *pInfo);
int LOCALSDK_GetSIMNum(char *pNum);//char[32]
int LOCALSDK_GetWirelessRSSI(LOCALSDK_WIRELESS_RSSI *pWirelessRSSI);
int LOCALSDK_PhoneCallUp(char *pNum);
int LOCALSDK_PhoneCallDown();
//��ȡrtsp��uir
int LOCALSDK_GetRTSPuir(int ch, int stream, char* pUir, int uirlen);
//iSave=1ʱ,ץͼ�浽Ӳ����
int LOCALSDK_TrigerSnap(int ch, int iSave=0);
int LOCALSDK_rtsp_start();
int LOCALSDK_rtsp_stop();
//��ȡyuv����
int LOCALSDK_StartYUV(int nChannel, LOCALSDK_YUV *yuv);
int LOCALSDK_GetYUVdata(int nChannel, LOCALSDK_YUV *yuv);
int LOCALSDK_StopYUV(int nChannel, LOCALSDK_YUV *yuv);

int LOCALSDK_GetOEMvetion(LOCALSDK_OEM_VERSION *cfg);
int LOCALSDK_SetOEMvetion(LOCALSDK_OEM_VERSION *cfg);

#ifdef _OEM_BaoDingBeiEr
int LOCALSDK_GetSDStateForBaoDingBeiEr(int *state);

/// �ú���������ȡU8300Cģ�鵱ǰ������ʽ( 4G����״̬�µ�������Ӫ����ʽ��)
//����ֵΪö��LOCALSDK_WirelessType
int LOCALSDK_GetWirelessPSART(int *WirelessType);
#endif

//���ܷ�����PEA�㷨ģ�������
int LOCALSDK_GetVideoAnalyzePeaRuleConfig(int ch, LOCALSDK_PEA_RULE_Config_V2* pInfo);
int LOCALSDK_SetVideoAnalyzePeaRuleConfig(int ch, LOCALSDK_PEA_RULE_Config_V2* pInfo);

//��������ģʽ����
int LOCALSDK_GetFishEyeConfig(LOCALSDK_FishEye_Config *pInfo);
int LOCALSDK_SetFishEyeConfig(LOCALSDK_FishEye_Config *pInfo);

#ifdef __cplusplus
}
#endif

#endif
