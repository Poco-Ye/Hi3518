#ifndef _DATA_ASSIST_H_
#define _DATA_ASSIST_H_

//const define
#define MAX_PACKET_LEN 168
#define AUDIO_PACKET_HEAD_LEN 8
#define MAX_CHANNEL_NUM 32
#define MAX_FILE_NAME_LEN 128
#define LOCAL_N_WEEKS 7		///< days of week
#define LOCAL_N_TSECT	6		///< time sect num
#define LOCAL_MD_REGION_ROW 32

#define  NAME_PASSWORD_LEN  64
#define  DECODER_NAME_LEN	64
#define  EMAIL_ADDR_LEN  32
#define  N_MIN_TSECT 2
#define  N_ALARMSERVERKEY 5
#define  MAX_FILTERIP_NUM 64
#define  MAX_MAC_LEN 32
#define  MAX_PROTOCOL_LENGTH 32
#define  LOCAL_N_ALM_OUT  32
#define  LOCALSDK_MAX_DRIVER_PER_DISK 4
#define  LOCALSDK_MAX_DISK_PER_MACHINE 8
#define  LOCALSDK_MAX_CHANNEL_WIDTH 320
#define MAX_ENCODER_NUM  32
#define COM_TYPES 2 
#define LOCAL_MAX_ARSP_TYPE 5
#define MAX_DIRPATH_LENGTH 260
#define MAX_MSK_SIZE 16 //��������Ĵ�С

enum Versions
{
	V_32DEV,
	V_64DEV,
};
typedef unsigned int						uint;			///< sizeof(uint) == sizeof(int) == 4
typedef unsigned char						uchar;	

//error code
enum LOCALSDK_RETURN_CODE	//
{
	LOCALSDK_SUCCESS	= 0,
	LOCALSDK_NOT_SUPPORT_STREAM = -1000,
	LOCALSDK_NOT_SUPPORT_CHANNEL = -1001,
	LOCALSDK_CAPTURE_FAIL = -1002,
	LOCALSDK_NO_INIT = -1003,
	LOCALSDK_ILLEGAL_PARAM = -1004,
	LOCALSDK_TIMEOUT = -1005,
	LOCALSDK_INVALID_HANDLE = -1006,
	LOCALSDK_IN_PLAYING = -1007,
	LOCALSDK_NOT_FOUND_FILE = -1008,
	LOCALSDK_GET_DATA_FAIL = -1009,
	LOCALSDK_NOT_IN_PLAYING = -1010,
	LOCALSDK_CREATE_FILE_FAIL = -1011,
	LOCALSDK_SET_DATA_FAIL = -1012,
	LOCALSDK_VERSION_DISMATCH = -1013,
	LOCALSDK_NOT_SUPPORT_FUNCTION = -1014,
	LOCALSDK_OVER_SIZE = -1015,
	LOCALSDK_NEED_REBOOT = -1016
};

/// ����ģʽ
enum AlarmTypes
{
	ALARM_CFG,			// ���� 
	ALARM_HAND,		    // �ֶ� 
	ALARM_CLOSE,		// �ر� 
};

/// capture channel type
enum SDK_CaptureChannelTypes 
{
	SDK_CAPTURE_CHN_MAIN = 0,		///< main stream 1
	SDK_CAPTURE_CHN_2END = 1,		///< extra stream 2
	SDK_CAPTURE_CHN_3IRD = 2,		///< extra stream 3
	SDK_CAPTURE_CHN_4RTH = 3,		///< extra stream 4
	SDK_CAPTURE_CHN_JPEG = 4,		///< JPEG stream
	SDK_CAPTURE_CHN_NR
};

enum SDK_video_standard_t {
	VIDEO_STANDARD_PAL = 0,	///< PAL��ʽ��
	VIDEO_STANDARD_NTSC,	///< NTSC��ʽ��
};

//////////////////////struct define
typedef struct LocalSDK_DeviceInfo_t
{
	unsigned int	uiIP; 				//device IP  
	unsigned short	usPort;				//HTTP port
	char    szDeviceName[32];			//device name
	char	szDeviceType[32];			//device type
	unsigned char	nVideoNum;			//video channels
	unsigned char	nAudioNum;			//audio channels
	unsigned char	nSubstreamNum;		//0:not support sub-stream
	unsigned char	nPlaybackNum;		//playback channels
	unsigned char	nAlarmInNum;		//alarm-in channels
	unsigned char	nAlarmOutNum;		//alarm-out channels
	unsigned char	nHddNum;			//hdd num
	char szVersion[32];                 //Version of Sofia
	char szSerialNo[17];                //SerualNum of Sofia
	uchar maxchnum;			//���ͨ����
	uchar videostandard;			//��Ƶ��ʽ: SDK_video_standard_t
	unsigned char	reserved[12];		//reserve
}LOCALSDK_DEVICE_INFO;

typedef struct LocalSDK_DeviceInfo_t_V2
{
	unsigned int	uiIP; 				//device IP  
	unsigned short	usPort;				//HTTP port
	char    szDeviceName[32];			//device name
	char	szDeviceType[32];			//device type
	unsigned char	nVideoNum;			//video channels
	unsigned char	nAudioNum;			//audio channels
	unsigned char	nSubstreamNum;		//0:not support sub-stream
	unsigned char	nPlaybackNum;		//playback channels
	unsigned char	nAlarmInNum;		//alarm-in channels
	unsigned char	nAlarmOutNum;		//alarm-out channels
	unsigned char	nHddNum;			//hdd num
	char szVersion[64];                 //Version of Sofia
	char szSerialNo[17];                //SerualNum of Sofia
	uchar maxchnum;			//���ͨ����
	uchar videostandard;			//��Ƶ��ʽ: 0��ʾP��; 1��ʾNTSC��
	unsigned char	reserved[12];		//reserve
}LOCALSDK_DEVICE_INFO_V2;

/// FrameType
enum FRAME_TYPE
{
	FRAME_VIDEO = 1,
	FRAME_AUDIO = 2,
	FRAME_DATA = 3
};


/// FrameSubType
enum FRAME_SUB_TYPE
{
	I_FRAME = 0,
	P_FRAME = 1,
	B_FRAME = 2,
	S_FRAME = 3,
	DATA_TEXT = 5,
	DATA_TNTL = 6
};

enum NET_ISP
{
	ISP_AUTO, //�Զ�ѡ��
	ISP_TELCOM, //����
	ISP_UNIONCOM, //��ͨ
	ISP_CNC,//��ͨ
	ISP_MOBILE,//�ƶ�����ͨ
	ISP_USER //�Զ���
};

/// ��������
enum ENCODE_TYPE
{
	StreamTypeEmpty = 0,
	StreamTypeH264 = 2,
	StreamTypeJpeg = 3,
	StreamTypeGeneral = 4,
	StreamTypePCM8 = 7,
	StreamTypeStd = 8
};

typedef struct 
{
	unsigned char *pHeader;				///< buffer header address
	unsigned char *pContent;            ///< frame data address
	unsigned long nLength;              ///< packet len
	unsigned long nFrameLength;         ///< frame len

	unsigned int FrameType;            ///< refer to FRAME_TYPE
	unsigned int nSubType;             ///< refer to FRAME_SUB_TYPE

	unsigned int nEncodeType;		///ENCODE_TYPE

	unsigned long nYear;				///< timestamp
	unsigned long nMonth;
	unsigned long nDay;
	unsigned long nHour;
	unsigned long nMinute;
	unsigned long nSecond;
	unsigned long nTimeStamp;	

	unsigned int  nFrameRate;			///< frame rate
	int nWidth;							///< video resolution��width and height
	int nHeight;
	unsigned long nRequence;

	unsigned int nChannels;
	unsigned int nBitsPerSample;		///< audio sample bit depth
	unsigned int nSamplesPerSecond;		///< audio sample rate

	unsigned long nParam1;		// 
	unsigned long nParam2;		// 
} SDK_H264_FRAME_INFO;

typedef struct
{
	int  year;		///< year  
	int  month;		///< month��January = 1, February = 2, and so on.   
	int  day;		///< day   
	int  wday;		///< weekday, Sunday = 0, Monday = 1, and so on   
	int  hour;		///< hour   
	int  minute;	///< min   
	int  second;	///< sec   
	int  isdst;		///< 1: using daylight saving time
}LOCALSDK_TIME,*LPLOCALSDK_TIME;

/// ¼������
enum RecordTypes
{
	RECORD_TYPE_COMMON = 0x00,		///< ��ͨ¼��
	RECORD_TYPE_ALARM = 0x01,		///< ����¼��
	RECORD_TYPE_MOTION = 0x02,		///< ����¼��
	RECORD_TYPE_HAND = 0x03,		///< �ֶ�¼��
	RECORD_TYPE_SNAP = 0x04,		///
	RECORD_TYPE_NR
};

enum LINK_FILE_TYPE //��Ϊ����ԭ������������¼���ͼƬ
{
	LINK_ALL,        //����ԭ��,����
	LINK_LOCALALARM, //���ر�������
	LINK_VIDEOALARM, //��Ƶ��ʧ���ƶ���������Ƶ��صı���
	LINK_ALLALARM,   //�������ֱ�������һ�ַ���
	LINK_HANDLE,     //�ֶ�¼���ץͼ
	LINK_NORMAL     //����¼���е���ͨ����µ�¼��
};
//search condtion
typedef struct 
{
	int nChannel;			//channel id
	int nFileType;			//file type, refer to LINK_FILE_TYPE
	LOCALSDK_TIME stBeginTime;	//begin time
	LOCALSDK_TIME stEndTime;	//end time
}LOCALSDK_FINDINFO;

/// ����������
enum FileSystemDriverTypes
{
	DRIVER_TYPE_BASE	= 0,	///< ������������ʼֵ
	DRIVER_READ_WRITE	= 0,	///< ��д������
	DRIVER_READ_ONLY	= 1,	///< ֻ��������
	DRIVER_EVENTS		= 2,	///< �¼�������
	DRIVER_REDUNDANT	= 3,	///< ����������
	DRIVER_SNAPSHOT		= 4,	///< ����������
	DRIVER_TYPE_NR		= 5,	///< ���������͸���
	DRIVER_UNUSED		= 0xff	///< û��ʹ�õ��������ṹ
};

typedef struct 
{
	int nChannel;			//ͨ����
	unsigned int 		nFileType;		//�ļ�����(����), ��RecordTypes
	unsigned int 		nDriverTypes;		//¼��Ϊ3��ץͼΪ1 << DRIVER_SNAPSHOT�������ݲ�֧�֣��Ժ���ܻ���չ
	LOCALSDK_TIME stBeginTime;	//��ʼʱ��
	LOCALSDK_TIME stEndTime;	//����ʱ��
	int StreamType;				//��������
	int MaxFileNum;
	uint resu[2];
}LOCALSDK_FINDINFOV2;

//record file info
typedef struct 
{
	int nChannel;				//channel id
	unsigned int nSize;			//file size
	char sFileName[128];		///< file name
	LOCALSDK_TIME stBeginTime;	///< begin time
	LOCALSDK_TIME stEndTime;	///< end time
}LOCALSDK_FILE_DATA;

typedef struct 
{
	LOCALSDK_FILE_DATA *pFileData;  //buffer for search return
	int nMaxSize;                   //max item num
	int nRetSize;                   //actually return item num
}LOCALSDK_FIND_FILE_RET;

typedef struct 
{
	int nFrameType : 4;             //fram type, refer to FRAME_TYPE
	int nFrameSubType : 4;          //fram sub type,refer to FRAME_SUB_TYPE
	int nFrameLen : 24;             //fram len
}FRAME_INDEX;

typedef struct 
{
	int nEnable;
	unsigned int	uiServerIP; 		//server IP 
	unsigned short	usPort;				//port 
	unsigned short	usDownlodPort;		//download port
	int nSyncTime;                      //is sync time from server
	int nStreamType;                    //0: main stream 1: extra stream
	char szPassword[16];
	char szSID[32]; 
}LOCALSDK_XINGWAN_INFO;

typedef struct 
{
	int nEnable;
	char szServerIP[64]; 		//server IP 
	unsigned int 	uiPort;		//port 
	unsigned int    uiDevID;    //device id
	unsigned int    uiDisplayID;
	int nGPSHeartBeat;          //gps hearbeat
	int nSysHeartBeat;          //svr hearbeat
	char szNoUsed[64]; 
}LOCALSDK_WELLSUN_INFO;

typedef struct 
{
	int	nBrightness;		///< Brightness	0-100
	int	nContrast;			///< Contrast	0-100
	int	nSaturation;		///< Saturation	0-100
	int	nHue;				///< Hue	0-100
	int	mGain;				///< Gain	0-100 
	int	mWhitebalance;		///< Whitebalance��bit7: 1-enable 0-disable. bit0~bit6:0x0-high 0x1-mid 0x2-low
}LOCALSDK_VIDEOCOLOR;

enum CaptureBitrateControlType 
{
	CAPTURE_BITRATE_CBR,			///< fixed bitrate
	CAPTURE_BITRATE_VBR,			///< Variable bitrate
	CAPTURE_BITRATE_MBR,			///< mix bitrate��
	CAPTURE_BITRATE_NR				///< 
};

enum CaptureCompressType 
{
	CAPTURE_COMPRESS_DIVX_MPEG4,	///< DIVX MPEG4��
	CAPTURE_COMPRESS_MS_MPEG4,		///< MS MPEG4��
	CAPTURE_COMPRESS_MPEG2,			///< MPEG2��
	CAPTURE_COMPRESS_MPEG1,			///< MPEG1��
	CAPTURE_COMPRESS_H263,			///< H.263
	CAPTURE_COMPRESS_MJPG,			///< MJPG
	CAPTURE_COMPRESS_FCC_MPEG4,		///< FCC MPEG4
	CAPTURE_COMPRESS_H264,			///< H.264
	CAPTURE_COMPRESS_NR				///< 
};


/// iamge quality
enum CaptureImageQuality
{
	CAPTURE_IMG_QUALITY_WOREST = 1,		///< worest
	CAPTURE_IMG_QUALITY_WORSE = 2,		///< worse
	CAPTURE_IMG_QUALITY_GENERAL = 3,	///< general
	CAPTURE_IMG_QUALITY_GOOD = 4,		///< good
	CAPTURE_IMG_QUALITY_BETTER = 5,		///< better
	CAPTURE_IMG_QUALITY_BEST = 6,		///< best
	CAPTURE_IMG_QUALITY_NR = 7
};

typedef struct 
{
	int		iCompression;			//  refer to CaptureCompressType
	int		iResolution;			//  refer to capture_size_t	
	int		iBitRateControl;		//  refer to capture_brc_t
	int		iQuality;				//  refer to CaptureImageQuality
	int		nFPS;					//  frame per second 2~12
	int		nBitRate;				//  0-4096k
	int		iGOP;					//  GOP
}LOCALSDK_VIDEO_FORMAT;

typedef struct 
{
	int nMainAudio;                // Main stream audio flag: 0 - disable 1 - enable
	int nExtraVideo;               // Extra stream video flag: 0 - disable 1 - enable
	int nExtraAudio;               // Extra stream audio flag: 0 - disable 1 - enable
	LOCALSDK_VIDEO_FORMAT stMain;  // Main stream
	LOCALSDK_VIDEO_FORMAT stExtra; // Extra stream
}LOCALSDK_VIDEOENCODE;

typedef struct 
{
	int nMainAudio;                // Main stream audio flag: 0 - disable 1 - enable
	int nExtraVideo;               // Extra stream video flag: 0 - disable 1 - enable
	int nExtraAudio;               // Extra stream audio flag: 0 - disable 1 - enable
	LOCALSDK_VIDEO_FORMAT stMain;  // Main stream
	LOCALSDK_VIDEO_FORMAT stExtra; // Extra stream
	LOCALSDK_VIDEO_FORMAT stSnap;  // Snap stream
}LOCALSDK_VIDEOENCODEV2;
/*��������������*/
enum DecorderConnType
{
	CONN_SINGLE = 0, 	/*������*/
	CONN_MULTI = 1,		/*��������Ѳ*/
	CONN_TYPE_NR,
};
enum DevType
{
	DEV_TYPE_IPC,
	DEV_TYPE_DVR,
	DEV_TYPE_HVR,
	DEV_TYPE_POEIPC,
	DEV_TYPE_NR
};

enum TransferProtocol_V2
{
	TRANSFER_PROTOCOL_NETIP,
	TRANSFER_PROTOCOL_ONVIF,
	TRANSFER_PROTOCOL_MAC,
	TRANSFER_PROTOCOL_NAT,
	TRANSFER_PROTOCOL_DAHUA,
	TRANSFER_PROTOCOL_NR_V2,
	TRANSFER_PROTOCOL_ONVIF_DEFAULT = 128,
	TRANSFER_PROTOCOL_ONVIF_NR_V2,
};
typedef struct 
{
	bool Enable;						///< �Ƿ���
	char UserName[NAME_PASSWORD_LEN];	///< DDNS��������, Ŀǰ��: JUFENG
	char PassWord[NAME_PASSWORD_LEN];	///< ������
	char Address[MAX_FILE_NAME_LEN];
	int Protocol;
	int Port;							///< ���������Ӷ˿�
	int Channel;						///< ����������ͨ����
	int Interval;                       ///< ��Ѳ�ļ��ʱ��(s),0:��ʾ����
	char ConfName[DECODER_NAME_LEN];	///<��������
	int DevType;						///<�豸����
	int StreamType;						///<���ӵ���������SDK_CaptureChannelTypes
	char MainRtspUrl[MAX_FILE_NAME_LEN];		///<rtspЭ��ʱ��ʾǰ���豸����������ַ
	char SubRtspUrl[MAX_FILE_NAME_LEN];		///<rtspЭ��ʱ��ʾǰ���豸�ĸ�������ַ
}NetDecorderConfigV3;

typedef struct 
{
	bool Enable;		/*����ͨ���Ƿ���*/		
	int ConnType;		/*�������ͣ�ȡDecoderConnectType��ֵ*/
	int TourIntv;		/*������ʱ��Ѳ���*/
	unsigned int SingleConnId;	/*������ʱ����������ID, ��1��ʼ��0��ʾ��Ч*/
	bool EnCheckTime;	/*������ʱ*/
	NetDecorderConfigV3 vDecorderConfigAll[MAX_ENCODER_NUM];
}LOCALSDK_NETDIGITCHNCONFIG;

enum PTZ_LINK_TYPES
{
	PTZ_LINK_NONE,			// none 
	PTZ_LINK_PRESET,		// goto preset
	PTZ_LINK_TOUR,			// start tour
	PTZ_LINK_PATTERN		// start pattern
};

//  PTZ link action
typedef struct 
{
	int iType;		// refer to PTZ_LINK_TYPES
	int iValue;		// value according to PTZ_LINK_TYPES
}PTZ_LINK;

typedef struct
{
	int enable;
	int startHour;
	int	startMinute;
	int	startSecond;
	int	endHour;
	int	endMinute;
	int	endSecond;
}TIME_SECTION;

/// worksheet
typedef struct
{	
	TIME_SECTION	tsSchedule[LOCAL_N_WEEKS][LOCAL_N_TSECT];
}WORK_SHEET;

/// event handler
typedef struct
{
	unsigned int	dwRecord;		// channel mask of record
	int		iRecordLatch;			// latch time��10��300 sec  	
	unsigned int	dwTour;					// channel mask of tour
	unsigned int	dwSnapShot;				// channel mask of snapshot 
	unsigned int	dwAlarmOut;				// channel mask of alarm-out 
	unsigned int	dwMatrix;				// channel mask of matrix
	int		iEventLatch;			// interval of alarm
	int		iAOLatch;				// alarm-out latch time: 10��300 sec  
	PTZ_LINK PtzLink[MAX_CHANNEL_NUM];		// ptz link action
	WORK_SHEET schedule;		// worksheet

	bool	bRecordEn;				// record enable flag
	bool	bTourEn;				// tour enable flag
	bool	bSnapEn;				// snapshot enable flag
	bool	bAlarmOutEn;			// alarm-out enable flag
	bool	bPtzEn;					// ptz link action enable flag
	bool	bTip;					// screen tip enable flag
	bool	bMail;					// send email enable flag
	bool	bMessage;				// send message enable flag
	bool	bBeep;					// beep enable flag
	bool	bVoice;					// voice enable flag
	bool	bFTP;					// ftp enable flag
	bool	bMatrixEn;				// matrix enable flag
	bool	bLog;					// log enable flag
	bool	bMessagetoNet;			// send message to net enable flag

	bool	bShowInfo;              // �Ƿ���GUI�Ϻͱ�������ʾ������Ϣ
	unsigned int	dwShowInfoMask;         // Ҫ������ʾ������Ϣ��ͨ������
	char	pAlarmInfo[NAME_PASSWORD_LEN];//Ҫ��ʾ�ı�����Ϣ

	bool    bShortMsg;              //���Ͷ���
	bool    bMultimediaMsg;         //���Ͳ���
}EVENT_HANDLER;

typedef struct 
{
	bool bEnable;							// enable flag 
	int nLevel;								// Sensitivity: 1-6
	unsigned int mRegion[LOCAL_MD_REGION_ROW]; // Region of motion�� bitmask for each line
	EVENT_HANDLER hEvent;					// motion detect handler 
}LOCALSDK_MOTION_DETECT;

///< �ڵ��������
typedef struct 
{
	bool	bEnable;		///< �ڵ���⿪��
	int		iLevel;			///< �����ȣ�1��6
	EVENT_HANDLER hEvent;	///< �ڵ������������
}LOCALSDK_BLIND_DETECT;

///< �����¼��ṹ
typedef struct 
{
	bool bEnable;			///< ʹ��
	EVENT_HANDLER hEvent;	///< �������
}LOCALSDK_GENERAL_CFG;

///< ���ر�������
typedef struct 
{
	bool	bEnable;		///< �������뿪��
	int		iSensorType;	///< ���������ͳ��� or ����
	EVENT_HANDLER hEvent;	///< ��������
}LOCALSDK_ALARM_CFG;

/// �¼��������
typedef struct
{
	uchar	dwRecord[MAX_MSK_SIZE];				// ¼������ 
	int		iRecordLatch;			// ¼����ʱ��10��300 sec  	 
	uchar	dwTour[MAX_MSK_SIZE];	// ��Ѳ���� 	 
	uchar	dwSnapShot[MAX_MSK_SIZE];			// ץͼ����  
	uchar	dwAlarmOut[MAX_MSK_SIZE];			// �������ͨ������  
	uchar	dwMatrix[MAX_MSK_SIZE];				// ��������  
	int		iEventLatch;			// ������ʼ��ʱʱ�䣬sΪ��λ 
	int		iAOLatch;				// ���������ʱ��10��300 sec  
	PTZ_LINK PtzLink[64];		// ��̨������
	WORK_SHEET schedule;		// ¼��ʱ���

	bool	bRecordEn;				// ¼��ʹ�� 
	bool	bTourEn;				// ��Ѳʹ�� 
	bool	bSnapEn;				// ץͼʹ�� 	
	bool	bAlarmOutEn;			// ����ʹ�� 
	bool	bPtzEn;					// ��̨����ʹ�� 
	bool	bTip;					// ��Ļ��ʾʹ�� 	
	bool	bMail;					// �����ʼ� 	
	bool	bMessage;				// ������Ϣ���������� 	
	bool	bBeep;					// ���� 	
	bool	bVoice;					// ������ʾ 		
	bool	bFTP;					// ����FTP���� 
	bool	bMatrixEn;				// ����ʹ�� 
	bool	bLog;					// ��־ʹ��
	bool	bMessagetoNet;			// ��Ϣ�ϴ�������ʹ�� 

	bool	bShowInfo;              // �Ƿ���GUI�Ϻͱ�������ʾ������Ϣ
	//uint	dwShowInfoMask;         // Ҫ������ʾ������Ϣ��ͨ������ 
	uchar	dwShowInfoMask[MAX_MSK_SIZE];         // Ҫ������ʾ������Ϣ��ͨ������
	char	pAlarmInfo[NAME_PASSWORD_LEN];//Ҫ��ʾ�ı�����Ϣ

	bool    bShortMsg;              //���Ͷ���
	bool    bMultimediaMsg;         //���Ͳ���
}EventHandler_V2;

typedef struct 
{
	bool bEnable;							// enable flag 
	int nLevel;								// Sensitivity: 1-6
	unsigned int mRegion[LOCAL_MD_REGION_ROW]; // Region of motion�� bitmask for each line
	EventHandler_V2 hEvent;					// motion detect handler 
}LOCALSDK_MOTION_DETECT_V2;

///< �ڵ��������
typedef struct 
{
	bool	bEnable;		///< �ڵ���⿪��
	int		iLevel;			///< �����ȣ�1��6
	EventHandler_V2 hEvent;	///< �ڵ������������
}LOCALSDK_BLIND_DETECT_V2;

///< �����¼��ṹ
typedef struct 
{
	bool bEnable;			///< ʹ��
	EventHandler_V2 hEvent;	///< �������
}LOCALSDK_GENERAL_CFG_V2;

///< ���ر�������
typedef struct 
{
	bool	bEnable;		///< �������뿪��
	int		iSensorType;	///< ���������ͳ��� or ����
	EventHandler_V2 hEvent;	///< ��������
}LOCALSDK_ALARM_CFG_V2;

///< ���ر����������
typedef struct
{
	int nAlarmOutType;		///< �����������: ����,�ֶ�,�ر�,��AlarmTypes
	int nAlarmOutStatus;		///< ����״̬: 0:�� 1;�պ�
}LOCALSDK_ALARMOUT_CFG;


///< ����ͨ���ı����������
typedef struct
{
	LOCALSDK_ALARMOUT_CFG vAlarmOutConfigAll[LOCAL_N_ALM_OUT];
}LOCALSDK_ALARMOUT_CFG_ALL;

typedef struct
{
	LOCALSDK_ALARMOUT_CFG* vAlarmOutConfigAll;
	int maxChannelNum;
	int retChannelNum;
}LOCALSDK_ALARMOUT_CFG_ALL_V2;

typedef union {	//IP addr
	unsigned char	c[4];
	unsigned short	s[2];
	unsigned int	l;
} LOCALSDK_IPADDR;

///< ��ͨ��������
typedef struct
{
	char HostName[NAME_PASSWORD_LEN];	///< ������
	LOCALSDK_IPADDR HostIP;		///< ����IP
	LOCALSDK_IPADDR Submask;		///< ��������
	LOCALSDK_IPADDR Gateway;		///< ����IP
	int HttpPort;			///< HTTP����˿�
	int TCPPort;			///< TCP�����˿�
	int SSLPort;			///< SSL�����˿�
	int UDPPort;			///< UDP�����˿�
	int MaxConn;			///< ���������
	int MonMode;			///< ����Э�� {"TCP","UDP","MCAST",��}
	int MaxBps;				///< �޶�����ֵ
	int TransferPlan;		///< ������� ��TransferPolicy
	bool bUseHSDownLoad;	///< �Ƿ����ø���¼�����ز���	
	char sMac[MAX_MAC_LEN]; ///< MAC��ַ
}LOCALSDK_NETCOMMON;

///< �������ṹ����
typedef struct
{
	char ServerName[NAME_PASSWORD_LEN];	///< ������
	LOCALSDK_IPADDR ip;						///< IP��ַ
	int Port;							///< �˿ں�
	char UserName[NAME_PASSWORD_LEN];		///< �û���
	char Password[NAME_PASSWORD_LEN];		///< ����	
	bool Anonymity;							///< �Ƿ�������¼
}LOCALSDK_REMOTE_CFG;

///< pppoe����
typedef struct
{
	bool Enable;		///< �Ƿ���
	LOCALSDK_REMOTE_CFG Server;		///< PPPOE������
	LOCALSDK_IPADDR addr;		///< ���ź��õ�IP��ַ
}LOCALSDK_PPPOE_CFG;

typedef struct
{
	int	iDataBits;	// ����λȡֵΪ5,6,7,8 
	int	iStopBits;	// ֹͣλ
	int	iParity;	// У��λ
	int	iBaudRate;	// ʵ�ʲ�����
}LOCALSDK_COMM_ATTRI;

// ��̨����
typedef struct
{
	char sProtocolName[MAX_PROTOCOL_LENGTH];	// Э������ 	
	int	ideviceNo;				// ��̨�豸��ַ��� 	
	int	iNumberInMatrixs;		// �ھ����е�ͳһ���	
	int iPortNo;				// ���ڶ˿ں�	[1, 4] 	
	LOCALSDK_COMM_ATTRI dstComm;			// �������� 	
}LOCALSDK_PTZ_CFG;

// ��������
typedef struct 
{
	char sProtocolName[MAX_PROTOCOL_LENGTH];	// ����Э��:��Console�� 
	int iPortNo;		// �˿ں� 
	LOCALSDK_COMM_ATTRI aCommAttri;		// �������� 
}LOCALSDK_CONFIG_COMM_X;

typedef struct
{
	LOCALSDK_CONFIG_COMM_X vCommConfig[COM_TYPES];
} LOCALSDK_COMM_CFG;


/// ¼��ģʽ����
enum RecordModeTypes
{
	RECORD_MODE_CLOSED,		///< �ر�¼��
	RECORD_MODE_MANUAL,		///< �ֶ�¼��
	RECORD_MODE_CONFIG,		///< ������¼��
	RECORD_MODE_NR
};

///< ¼������
typedef struct 
{
	int iPreRecord;			///< Ԥ¼ʱ�䣬Ϊ��ʱ��ʾ�ر�	
	bool bRedundancy;		///< ���࿪��
	int iPacketLength;		///< ¼�������ȣ����ӣ�[1, 255]
	int iRecordMode;		///< ¼��ģʽ����RecordModeTypes
	WORK_SHEET wcWorkSheet;				///< ¼��ʱ���	
	unsigned int typeMask[LOCAL_N_WEEKS][LOCAL_N_TSECT];	///< ¼���������룬��enum RecordTypes
}LOCALSDK_RECORD_CFG;


/// ͼƬģʽ����
enum SnapModeTypes
{
	SNAP_MODE_CLOSED,		///< �ر�ץͼ
	SNAP_MODE_MANUAL,		///< �ֹ�ץͼ
	SNAP_MODE_CONFIG,		///< ������ץͼ
	SNAP_MODE_NR	
};

///< ͼƬ����
typedef struct 
{
	int iPreSnap;			///< ԤץͼƬ��
	bool bRedundancy;		///< ���࿪��
	int iSnapMode;		///< ¼��ģʽ����SnapModeTypes
	WORK_SHEET wcWorkSheet;				///< ¼��ʱ���	
	unsigned int typeMask[LOCAL_N_WEEKS][LOCAL_N_TSECT];	///< ¼���������룬��enum RecordTypes
}LOCALSDK_SNAPSHOT_CFG;


///< ��������Ϣ�ṹ
typedef struct 
{
	int		iDriverType;		///< ����������
	bool	bIsCurrent;			///< �Ƿ�Ϊ��ǰ������
	unsigned int	uiTotalSpace;		///< ��������MBΪ��λ
	unsigned int	uiRemainSpace;		///< ʣ��������MBΪ��λ
	int		iStatus;			///< �����־���ļ�ϵͳ��ʼ��ʱ������
	int		iLogicSerialNo;				///< �߼����
	LOCALSDK_TIME  tmStartTimeNew;		///< ��¼��ʱ��εĿ�ʼʱ��
	LOCALSDK_TIME	 tmEndTimeNew;			///< ��¼��ʱ��εĽ���ʱ��
	LOCALSDK_TIME	 tmStartTimeOld;		///< ��¼��ʱ��εĿ�ʼʱ��
	LOCALSDK_TIME	 tmEndTimeOld;			///< ��¼��ʱ��εĽ���ʱ��
}LOCALSDK_DRIVER_INFO;

/// ������Ϣ�ṹ
typedef struct 
{
	int		iPhysicalNo;		// Ӳ��������ţ���0��ʼ
	int		iPartNumber;		// ������
	LOCALSDK_DRIVER_INFO diPartitions[LOCALSDK_MAX_DRIVER_PER_DISK];
}LOCALSDK_STORAGE_INFO;

typedef struct 
{
	int iDiskNumber;
	LOCALSDK_STORAGE_INFO vStorageDeviceInfoAll[LOCALSDK_MAX_DISK_PER_MACHINE];
}LOCALSDK_STORAGE_INFO_ALL;

/// ��Ƶ��������
enum AudioEncodeTypes
{
	AUDIO_ENCODE_NONE = 0,
	AUDIO_ENCODE_G729_8KBIT,
	AUDIO_ENCODE_G726_16KBIT,
	AUDIO_ENCODE_G726_24KBIT,
	AUDIO_ENCODE_G726_32KBIT,
	AUDIO_ENCODE_G726_40KBIT,
	AUDIO_ENCODE_PCM_8TO16BIT,
	AUDIO_ENCODE_PCM_ALAW,
	AUDIO_ENCODE_PCM_ULAW,
	AUDIO_ENCODE_ADPCM8K16BIT,
	AUDIO_ENCODE_ADPCM16K16BIT,
	AUDIO_ENCODE_G711_ALAW,
	AUDIO_ENCODE_MPEG2_LAYER1,
	AUDIO_ENCODE_AMR8K16BIT,
	AUDIO_ENCODE_G711_ULAW,
	AUDIO_ENCODE_IMA_ADPCM_8K16BIT,
	AUDIO_ENCODE_TYPES_NR
};

/// ��Ƶ�����ʽ�������Խ���
typedef struct 
{
	int iBitRate;	   ///< ������С��kbpsΪ��λ������192kbps��128kbps
	int iSampleRate;   ///< �����ʣ�HzΪ��λ������44100Hz
	int iSampleBit;    ///< ������λ��
	int iEncodeType;   ///< ���뷽ʽ������AudioEncodeTypes����
}LOCALSDK_AUDIOIN_FORMAT;

enum LOACLSDK_PTZ_OPT_ACT
{
	PTZ_OPT_NONE = 0,
	PTZ_OPT_LEFTUP = 1,
	PTZ_OPT_UP,
	PTZ_OPT_RIGHTUP,
	PTZ_OPT_LEFT,
	PTZ_OPT_RIGHT,

	//6
	PTZ_OPT_LEFTDOWN,
	PTZ_OPT_DOWN,
	PTZ_OPT_RIGHTDOWN,
	PTZ_OPT_ZOOM_WIDE,
	PTZ_OPT_ZOOM_TELE,

	//11
	PTZ_OPT_FOCUS_FAR,
	PTZ_OPT_FOCUS_NEAR,
	PTZ_OPT_IRIS_LARGE,
	PTZ_OPT_IRIS_SMALL,
	PTZ_OPT_ALARM_SEARCH,

	//16
	PTZ_OPT_LIGHT_ON,
	PTZ_OPT_LIGHT_OFF,
	PTZ_OPT_SETPRESET,
	PTZ_OPT_CLEARPRESET,
	PTZ_OPT_GOTOPRESET,

	//21
	PTZ_OPT_AUTOPANON,
	PTZ_OPT_AUTOPANOFF,
	PTZ_OPT_SETLEFTLIMIT,
	PTZ_OPT_SETRIGHTLIMIT,
	PTZ_OPT_AUTOSCANON,

	//26
	PTZ_OPT_AUTOSCANOFF,
	PTZ_OPT_ADDTOUR,
	PTZ_OPT_DELTOUR,
	PTZ_OPT_STARTTOUR,
	PTZ_OPT_STOPTOUR,

	//31
	PTZ_OPT_CLEARTOUR,
	PTZ_OPT_SETPATTERNBEGIN,
	PTZ_OPT_SETPATTERNEND,
	PTZ_OPT_STARTPATTERN,
	PTZ_OPT_STOPPATTERN,

	//36
	PTZ_OPT_CLEARPATTERN,
	PTZ_OPT_POSITION,
	PTZ_OPT_AUXON,
	PTZ_OPT_AUXOFF,
	PTZ_OPT_MENU,

	//41
	PTZ_OPT_EXIT,
	PTZ_OPT_ENTER,
	PTZ_OPT_ESC,
	PTZ_OPT_MENUUP,
	PTZ_OPT_MENUDOWN,

	//46
	PTZ_OPT_MENULEFT,
	PTZ_OPT_MENURIGHT,
	PTZ_OPT_SWITCH,
	//47
	PTZ_OPT_FLIP,
	PTZ_OPT_RESET,
	PTZ_MATRIX_SWITCH,
	PTZ_LIGHT_CONTROLLER,

	//51
	PTZ_OPT_SETPRESETNAME,
	PTZ_OPT_ALARMPTZ,

	PTZ_OPT_STANDARD
};

typedef struct 
{
	int nCmd;						///< refer to LOACLSDK_PTZ_OPT_ACT
	int nArg1;						///< step(1~8), preset num, tour num and so on according to LOACLSDK_PTZ_OPT_ACT
	int nArg2;						///< add and del tour means to preset num, and PTZ_OPT_LEFTUP,PTZ_OPT_RIGHTUP,PTZ_OPT_LEFTDOWN,PTZ_OPT_RIGHTDOWN means horizontal step
	int nArg3;						///< no used
	int nArg4;						///< 0��start 1��stop
}LOCALSDK_PTZ_OPT;

/// �澯״̬
typedef struct
{
	int iVideoMotion; ///< motion detect state,bit0 means channel 1 and so on, 1 - alarm 0 - normal
	int iVideoBlind; ///< blind state,bit0 means channel 1 and so on, 1 - alarm 0 - normal
	int iVideoLoss;	///< loss state,bit0 means channel 1 and so on, 1 - alarm 0 - normal
	int iAlarmIn;	///< alarm-in state,bit0 means channel 1 and so on, 1 - alarm 0 - normal
	int iAlarmOut;	///< alarm-out state,bit0 means channel 1 and so on, 1 - alarm 0 - normal
}ALARM_STATE;

typedef struct
{
	bool bRecord; ///< 1: in recording 0: no record
	int iBitrate;	///< bitrate
}CHANNEL_STATE;

typedef struct
{
	CHANNEL_STATE vChnState[MAX_CHANNEL_NUM];
	ALARM_STATE vAlarmState;
}LOCALSDK_WORKSTATE;

typedef struct
{
	uchar iVideoMotion[MAX_MSK_SIZE]; ///< �ƶ����״̬,�������ʾͨ����,bit0����ͨ��һ,�Դ����� 1: �и澯 0: �޸澯
	uchar iVideoBlind[MAX_MSK_SIZE]; ///< ��Ƶ�ڵ�״̬,�������ʾͨ����,bit0����ͨ��һ,�Դ����� 1: �и澯 0: �޸澯
	uchar iVideoLoss[MAX_MSK_SIZE];	///< ��Ƶ��ʧ״̬,�������ʾͨ����,bit0����ͨ��һ,�Դ����� 1: �и澯 0: �޸澯
	uchar iAlarmIn[MAX_MSK_SIZE];	///< �澯����״̬,�������ʾͨ����,bit0����ͨ��һ,�Դ����� 1: �и澯 0: �޸澯
	uint iAlarmOut;	///< �澯���״̬,�������ʾͨ����,bit0����ͨ��һ,�Դ����� 1: �и澯 0: �޸澯
}ALARM_STATE_V2;

typedef struct
{
	CHANNEL_STATE* vChnState;
	ALARM_STATE_V2 vAlarmState;
	int maxChannelNum;
	int retChannelNum;
}LOCALSDK_WORKSTATE_V2;

typedef struct 
{
	char szFileName[MAX_FILE_NAME_LEN];
	char szResv[128];
}LOCALSDK_FILE_INFO;

typedef struct 
{
	/// �ж�̬��ⷢ�����������ݵ�ÿһλ��Ӧһ����������飬��1��ʾ�ڸ������
	/// ��̬���ɹ�����0��ʾ������鶯̬���ʧ�ܡ�ÿһ����һ��unsigned int��ʾ�������
	/// �Ŀ������λ�����ϵ��µ��ж�Ӧ���±��0��17��֧�ֵ�������֮���Ӧ������
	/// λ��Ч��
	unsigned int	win[18];
}MOTION_DETECT_RESULT;

enum OSD_PLACE
{
	OSD_LEFTUP,
	OSD_UP,
	OSD_RIGHTUP,
	OSD_LEFT,
	OSD_CENTER,
	OSD_RIGHT,
	OSD_LEFTDOWN,
	OSD_DOWN,
	OSD_DOWNRIGHT,
	OSD_NUM
};

enum OSD_PARAM
{
	OSD_OFF,	//�ر��ֶ����Ź��ܣ�ʹ���Զ����ţ���Ϊȱʡֵ��
	OSD_SMAL,	//����֮һ
	OSD_NOMAL,	//ԭʼ��С
	OSD_BIG2,	//������С
	OSD_NR,
};

typedef struct 
{
	int nPlace;    //refer to OSD_PLACE
	char szOSDTitle[MAX_FILE_NAME_LEN - 4];  //end with '\0'
	int iParam;		//enum OSD_PARAM
}LOCALSDK_OSD_INFO;

typedef struct 
{
	int nX;    //����ǧ�ֱ�
	int nY;
	char szOSDTitle[MAX_FILE_NAME_LEN - 4];  //end with '\0'
	int iParam;		//enum OSD_PARAM
}LOCALSDK_OSD_INFO_V2;




typedef struct
{
 	int nTimePlace;    //refer to OSD_PLACE  //ʱ������
	int nEnableTime;    
	
 	int nCamNamePlace;    //refer to OSD_PLACE  //ʱ������
	int nEnableCamName;    //�Ƿ�������ʾ
  
}LOCALSDK_OSD_CHANNELINFO;

// alarm type
enum ALARM_MSG_TYPE
{
	ALARM_IO,
	ALARM_MOTION,
	ALARM_LOSS,
	ALARM_BLIND,
	ALARM_NET_ALARM,
	ALARM_STORAGE_ERROR,
	ALARM_STORAGE_LOW_SPACE,
	ALARM_NET_ABORT,
	ALARM_IP_CONFLICT,
	ALARM_VIDEO_ANALYZE,
	ALARM_SYS_UPGRADE,
	ALARM_NUM
};

// alarm msg info
typedef struct 
{
	int nChannel;           ///< channel
	int nType;              ///< msg type see refer to ALARM_MSG_TYPE
	int nStatus;            ///< status 1: start 0: stop
	LOCALSDK_TIME Time;     ///< happen time
}LOCAL_ALARM_MSG;



enum MediaEventTypes
{
	F_COMMON	= 0x00,		///< (R)
	F_ALERT		= 0x01,		///< (A)
	F_DYNAMIC	= 0x02,		///< (M)
	F_CARD		= 0x03,		///< (C)
	F_HAND		= 0x04		///< (H)
};

enum MediaFileTypes
{
	F_JPEG = 0,				///< JPEG FILE
	F_AUDIO = 1,			///< audio file
	F_VIDEO = 2,			///< video file
	F_AUDIO_VIDEO = 3		///< audio and video file
};

typedef struct  
{
	unsigned char	chan;		//channel
	unsigned char	av;			//see refer to MediaFileTypes
	unsigned char	image;		//frame rate
	unsigned char	alarm;		//see refer to MediaEventTypes
	LOCALSDK_TIME	stime;		//record begin time
	LOCALSDK_TIME	etime;		//record end time
	unsigned int	len;		//file size, KB unit
	unsigned int	csize;		//cluter size, KB Unit
}LOCAL_FILE_ATTR;

typedef struct 
{
	int nEnable;
	char strSSID[32];            //SSID Number
	int nChannel;                   //channel
	char strNetType[32];         //Infra, Adhoc
	char strEncrypType[32];      //NONE, WEP, TKIP, AES
	char strAuth[32];            //OPEN, SHARED, WEPAUTO, WPAPSK, WPA2PSK, WPANONE, WPA, WPA2
	int  nKeyType;                  //0:Hex 1:ASCII
	char strKeys[32];
	LOCALSDK_IPADDR HostIP;		///< host ip
	LOCALSDK_IPADDR Submask;		///< netmask
	LOCALSDK_IPADDR Gateway;		///< gateway
}LOCALSDK_WIFI_CONFIG;


// RTSP
typedef  struct 
{
	bool bServer;
	bool bClient;
	LOCALSDK_REMOTE_CFG Server;		///< ������ģʽ
	LOCALSDK_REMOTE_CFG Client;		///< �ͻ���ģʽ
}LOCALSDK_RTSP_CONFIG;

///< NTP����

typedef struct 
{
	///< �Ƿ���
	bool Enable;
	///< PPPOE������
	LOCALSDK_REMOTE_CFG Server;
	///< ��������
	int UpdatePeriod;
	///< ʱ��
	int TimeZone;
}LOCALSDK_NTP_CONFIG;


//DHCP
typedef struct 
{
	bool bEnable;
	char ifName[32];
}LOCALSDK_DHCP_CONFIG;

/// ����������DHCP����
typedef struct 
{
	LOCALSDK_DHCP_CONFIG vNetDHCPConfig[4];      //0����, 2Wifi
}LOCALSDK_DHCP_CONFIGALL;

///< NTP����
typedef struct 
{
	LOCALSDK_IPADDR PrimaryDNS;
	LOCALSDK_IPADDR SecondaryDNS;
}LOCALSDK_DNS_CONFIG;

typedef struct
{
 	int Enable;
	int nISP;
	char sServerName[32];
	char ID[32];
	char sUserName[32];
	char sPassword[32];
	LOCALSDK_IPADDR HostIP;		///< host ip
	int port;
}LOCALSDK_NET_PLATFORM_CONFIG;
enum OSD_DOT_PARAM
{
	OSD_DOT_CH_TITLE,		//ͨ�����⣬���ڼ��ݣ����԰�ͨ���������ǰ��
	OSD_DOT_OTHERS,		//����OSD����
	OSD_DOT_NR,
};
typedef struct
{
	int nLen;
	unsigned char vBuf[2996];
	int Param;		//enum OSD_DOT_PARAM
}LOCALSDK_OSD_DOT_MATRIX;

typedef struct
{
	int nLen;
	int Param;
	unsigned char *vBuf;
}LOCALSDK_OSD_DOT_MATRIX_V2;

enum manual_action
{
	ACT_STOP = 0,
	ACT_START
};
enum manual_kind
{
	MANUAL_RECORD=0,
	MANUAL_SNAP
};

typedef struct
{
	int nKind;    //���� manual_kind
	int nAction;  //����,��manual_action
}LOCALSDK_MANUAL_ACTION;

typedef struct
{
	int nPort; //�ڲ��˿�
	int nExPort; //�ⲿ�˿�
	int nAct;   //0:���  1ɾ��  2��ȡ
}LOCALSDK_UPNP;

typedef struct 
{
	LOCALSDK_VIDEO_FORMAT stMain;  // ������
	LOCALSDK_VIDEO_FORMAT stExtra; // ������
}LOCALSDK_MANUAL_VIDEOENCODE;


///< ARSP(����ע�������)���ð�������̩DNS
struct NetARSPConfig
{
	bool bEnable;	///< �Ƿ���
	char sARSPKey[NAME_PASSWORD_LEN];	///< DNS��������
	int iInterval;	///< ������ʱ��
	char sURL[NAME_PASSWORD_LEN];    ///< ��������
	LOCALSDK_REMOTE_CFG Server;		///< DDNS������
	int nHttpPort;                  ///< ������HTTP�˿�
};

typedef struct  
{
	NetARSPConfig vNetARSPConfigAll[LOCAL_MAX_ARSP_TYPE];
}LOCALSDK_ARSP_CONFIG;

///< �Զ�ά������
typedef struct 
{
	int iAutoRebootDay;				///< �Զ�������������
	int iAutoRebootHour;			///< ��������ʱ��	[0, 23]	
	int iAutoDeleteFilesDays;		///< �Զ�ɾ���ļ�ʱ��[0, 30] ָ����ǰ���ļ� 0��ɾ��
}LOCALSDK_AUTO_MAINTAIN_CONFIG;


/* �������� */
enum LOCALSDK_WirelessType
{
	LOCALSDK_WIRELESS_TYPE_AUTOSEL=0,		/* �Զ�ѡ��*/
	LOCALSDK_WIRELESS_TYPE_TD_SCDMA=1,	/* TD-SCDMA���� */
	LOCALSDK_WIRELESS_TYPE_WCDMA=2,		/* WCDMA���� */
	LOCALSDK_WIRELESS_TYPE_CDMA_1x=3,		/* CDMA 1.x���� */
	LOCALSDK_WIRELESS_TYPE_EDGE=4,		/* GPRS���� */
	LOCALSDK_WIRELESS_TYPE_EVDO=5,		/*EVDO����*/
	LOCALSDK_WIRELESS_TYPE_4G=6,		/*EVDO����*/
	LOCALSDK_WIRELESS_TYPE_MAX
};

// �����豸
typedef struct //tagWIRELESS_DEVICE
{
	unsigned int	typeMask; ///< ֧�ֵ������������룬��λ��ʾ��ÿһλ��ӦWirelessType����
	char	info[32]; ///< ������Ϣ
	int reserved[23];
}LOCALSDK_WIRELESS_DEVICE;


typedef struct //tagWIRELESS_CONFIG
{
	int iEnable;					/* ����ģ��ʹ�ܱ�־ */
	LOCALSDK_WirelessType iNetType;			/* ������������*/
	char szAPN[32];		         	/* ��������ƣ��ַ���, ����'\0'��������32bytes */
	char szDialNum[32];  			/* ���ź��룬�ַ���, ����'\0'��������32bytes */
	char  szUserName[128];  		/* �����û������ַ���, ����'\0'��������16bytes */
	char szPWD[128];  				/* �������룬�ַ���, ����'\0'��������16bytes */
	char Reserved[8]; 				/* Ԥ��8�ֽڣ�����չ */
}LOCALSDK_WIRELESS_CONFIG;


// ��������״̬
typedef struct //tagWIRELESS_STATUS
{
	int iAccessStat; /* ��������ע��״̬*/
	char szDevIP[16];   /* ǰ���豸����IP���ַ���, ����'\0'��������16byte*/
	char szSubNetMask [16];   /* ǰ���豸�����������룬�ַ���, ����'\0'��������16byte */
	char szGateWay[16];  /* ǰ���豸�������أ��ַ���, ����'\0'��������16byte */
	LOCALSDK_WirelessType iNetType : 8; /* ������������*/
	char Reserved1[3];   /* �����ֽڣ�������չ*/
	char Reserved[4];   /* �����ֽڣ�������չ*/
}LOCALSDK_WIRELESS_STATE;

typedef struct 
{
	bool bEnable;			  ///< ʹ�ܱ�־
	bool bState;              ///< ״̬
	int iHTTPPort;			  ///< HTTP�˿�
	int iMediaPort;			  ///< ý��˿�
	int iMobliePort;		  ///< �ֻ���ض˿�
}LOCALSDK_NETUPNP_CONFIG;

//��������̬����
typedef struct  
{
//	char reserved[2];
	int profile;
	int level;
	int reserved1[4];
}LOCALSDK_ENCODESTATIC_CFG;

//��������ͷ����
//�ع�����
struct ExposureParam
{
	int  level;    //�ع�ȼ�
	uint leastTime;//�Զ��ع�ʱ�����޻��ֶ��ع�ʱ�䣬��λ΢��
	uint mostTime; //�Զ��ع�ʱ�����ޣ���λ΢��
};

//��������
struct GainParam
{
	int gain;    //�Զ���������(�Զ���������)��̶�����ֵ
	int autoGain;//�Զ������Ƿ����ã�0:������  1:����
};

//��������ͷ����
typedef struct CameraParam
{
	uint whiteBalance;          //��ƽ��
	uint dayNightColor;         //��ҹģʽ��ȡֵ�в�ɫ���Զ��л��ͺڰ�
	int  elecLevel;             //�ο���ƽֵ
	uint apertureMode;          //�Զ���Ȧģʽ
	uint BLCMode;               //���ⲹ��ģʽ
	ExposureParam exposureParam;//�ع�����
	GainParam     gainParam;    //��������
	uint PictureFlip;		//ͼƬ���·�ת
	uint PictureMirror;	//ͼƬ���ҷ�ת
	uint RejectFlicker;	//�չ�Ʒ�������
	uint EsShutter;		//���������Ź���
	int ircut_mode;		//IR-CUT�л� 0 = �����ͬ���л� 1 = �Զ��л�
	int dnc_thr;			//��ҹת����ֵ
	int ae_sensitivity;	//ae����������
	int Day_nfLevel;		//noise filter �ȼ���0-5,0���˲���1-5 ֵԽ���˲�Ч��Խ����
	int Night_nfLevel;
	int Ircut_swap;		//ircut ������= 0        ����= 1
}LOCALSDK_CAMERAPARA_CONFIG;

//��˼IPCͼ���񣬲�ͬ���֮�仭�汥�Ͷ�֮�������ͬ�������ɵײ����
enum IMG_TYPE
{
	IMG_TYPE_DEFAULT,
	IMG_TYPE_1,
	IMG_TYPE_2,
	IMG_TYPE_NR,
};

//��������ͷ��չ����
typedef struct CameraParamEx
{
	GainParam broadTrends;	//��̬
	int style;	//enum IMG_TYPE
	uint exposureTime;//ʵ����Ч���ع�ʱ��
	int res[62];	//����
}LOCALSDK_CAMERAPARA_EX_CONFIG;

//�ָ�Ĭ������
// Ĭ����������
typedef enum 
{
	DEFAULT_CFG_GENERAL,			// ��ͨ����
	DEFAULT_CFG_ENCODE,				// ��������
	DEFAULT_CFG_RECORD,				// ¼������
	DEFAULT_CFG_NET_SERVICE,		// �������
	DEFAULT_CFG_NET_COMMON,			// ͨ������
	DEFAULT_CFG_ALARM,				// ����
	DEFAULT_CFG_PTZCOMM,			// ��̨������
	DEFAULT_CFG_USERMANAGER,		// �û�����
	DEFAULT_CFG_PREVIEW,			// Ԥ������
	DEFAULT_CFG_CAMERA_PARAM,		// ��������ͷ����
	DEFAULT_CFG_END
}DefaultConfigKinds;

//����Ӧ�ý������λ��ʾ�������õĹ۲������ã����õ��ύ�߼��
typedef enum 
{
	CONFIG_APPLY_OK = 0,						/// �ɹ�
	CONFIG_APPLY_REBOOT = 0x00000002,			/// ��Ҫ����ϵͳ
	CONFIG_APPLY_FILE_ERROR = 0x00000004,		/// д�ļ�����
	CONFIG_APPLY_CAPS_ERROR = 0x00000008,		/// ���Բ�֧��
	CONFIG_APPLY_GATEWAY_ERROR = 0x00000010,	///��������ʧ��,��Ȼ����Ϊ�ɹ�
	CONFIG_APPLY_VALIT_ERROR = 0x00000020,		/// ��֤ʧ�� 
	CONFIG_APPLY_NOT_EXSIST = 0x00000040,		/// ���ò����� 
	CONFIG_APPLY_NOT_SAVE = 0x00000080,			/// ��Ҫ���浽�ļ�
	CONFIG_APPLY_DELAY_SAVE = 0x00000100,		///��ʱ����..��λռ��ȡֵΪ0x180��ԭ���������ñ����ʱ����Ҫ����
}CONFIG_APPLY_RET;

typedef struct DefaultConfig
{
	DefaultConfigKinds enkind;//��Ҫ�ָ���Ĭ����������
	CONFIG_APPLY_RET  enResult;//�ָ�Ĭ�ϲ������
}LOCALSDK_DEFAULT_CONFIG;

/***��ͨ����***/
/// ����ʱ����
enum DST_RULE_TYPES
{
	DST_RULE_OFF = 0,	///< �ر�����ʱ����
	DST_RULE_ON,		///< ��������ʱ����
	DST_RULE_NR
};

///< ����ʱ�ṹ
struct GeneralDSTPoint
{
	int	iYear;
	int	iMonth;
	int	iWeek;		///<��1:first  to2 3 4 -1:last one   0:��ʾʹ�ð��ռ���ķ���[-1,4]
	int	iWeekDay;	///<weekday from sunday=0	[0, 6]
	int Hour;
	int Minute;
};

///<��������
typedef struct LocationConfig
{
	int iVideoFormat;		///< ��Ƶ��ʽ
	int iLanguage;			///< ����ѡ��
	int iDateFormat;		///< ���ڸ�ʽ
	int iDateSeparator;		///< ���ڷָ��:��.��, ��-��, ��/�� 
	int iTimeFormat;		///< ʱ���ʽ:��12��, ��24�� 
	int iDSTRule;			///< ����ʱ���� 
	int iWorkDay;			///< ������
	GeneralDSTPoint dDSTStart;
	GeneralDSTPoint dDSTEnd;
}LOCALSDK_LOCATION_CONFIG;

typedef struct BeepConfig
{
	int Frequence;      
	int Duration;       //from 0 to 3000;other value is invalid.unit is millisecond
}LOCALSDK_BEEP_CONFIG;

//�ֻ��������
typedef struct NetMobileConfig
{
	bool bEnable;	///< �Ƿ���
	LOCALSDK_REMOTE_CFG Server;		///< ������
}LOCALSDK_MOBILE_CONFIG;

//��ȡ�û�Ȩ���б�
#define MAX_USER_LENGTH 32
#define MAX_RIGTH_NUM 128
#define MAX_GROUP_NUM 32
#define PASS_WORD_LENGTH 32
#define MAX_USER_NUM 32

typedef struct _USER_INFO
{
	int			rigthNum;        //�û�ӵ�е�Ȩ�޸���
	char		rights[MAX_RIGTH_NUM][MAX_USER_LENGTH];  
	char		Groupname[MAX_USER_LENGTH];
	char		memo[MAX_USER_LENGTH];
	char		name[MAX_USER_LENGTH];
	char		passWord[MAX_USER_LENGTH];
	bool		reserved;		 //�Ƿ���
	bool		shareable;		 //���û��Ƿ������� 1-���ã�0-������
}LOCALSDK_USER_INFO;

//�û�����������飬
typedef struct _ATHORITY_INFO
{
	int         AthorityNum;
	char        GroupName[MAX_USER_LENGTH];
	char        Athority[MAX_RIGTH_NUM][MAX_USER_LENGTH];  
}LOCALSDK_ATHORITY_INFO;

//���б�
typedef struct _GROUP_LIST
{
	char        GroupList[MAX_GROUP_NUM][MAX_USER_LENGTH];
}LOCALSDK_GROUP_LIST;

/// �޸��û���������
typedef struct ModifyPassword
{
	char  UserName[MAX_USER_LENGTH];
	char  Password[PASS_WORD_LENGTH];
	char  NewPassword[PASS_WORD_LENGTH];
}LOCALSDK_MODIFY_PASSWORD;

//��ȡ�û��б�
typedef struct UserList
{
	char UserList[MAX_USER_NUM][MAX_USER_LENGTH];
}LOCALSDK_USER_LIST;

//ǿ��I֡
// ����ͨ������
typedef enum {
	SDK_CHL_MAIN_T = 0,		///< ��ͨ��	��	������1 
	SDK_CHL_2END_T = 1,		///< ��ͨ��	��	��������2 
	SDK_CHL_3IRD_T = 2,		///< ��ͨ��	��	��������3 
	SDK_CHL_4RTH_T = 3,		///< ��ͨ��	��	��������4 
	SDK_CHL_JPEG_T = 4,		///< ��ͨ��	��	��JPEGץͼ 
	SDK_CHL_FUNCTION_NUM
}CHANNELTYPE;

typedef struct 
{
	int Channel;
	CHANNELTYPE dwStreamType;
}LOCALSDK_FORCE_I_FRAME;

typedef struct
{
	int Length;
	char DataBuffer[4 * 1024 * 10];
}LOCALSDK_UPGRADE_DATA;

typedef struct DASSerInfo
{
	bool enable;
 	char serAddr[NAME_PASSWORD_LEN];
	int  port;
	char userName[NAME_PASSWORD_LEN];
	char passwd[NAME_PASSWORD_LEN];
	char devID[NAME_PASSWORD_LEN];
}LOCALSDK_DAS_SER_INFO;

typedef struct VPNState
{
	int state;
	char sIPaddr[32];
	char mask[32];
}LOCALSDK_VPN_STATE;

typedef struct GUIInfo
{
	int Isshow;         //1.�������ݣ�0.ɾ������
	int iChannel;       //��Ӧͨ��
	int index;          //��Ӧͨ��
	int nX;    			//����ǧ�ֱ�
	int nY;
	char szGuiContent[MAX_FILE_NAME_LEN]; //OSD��ӵ�����
}LOCALSDK_ADD_GUI_INFO;

//���ݿ���ƽ̨
/***�û���Ϣ***/ 
typedef union {	//IP addr
	unsigned char	c[4];
	unsigned short	s[2];
	uint	l;
}LOCALSDK_IPAddress;

struct CONFIG_KAINENG_USERINFO
{
	char szUserName[16];           //�û�������5�����ֻ�ʮ����ĸ;
	char szUserAddr[128];           //�û���ַ��30�����ֻ�60����ĸ;
	char szUserAttr[16];           //�û����ʣ�5�����ֻ�ʮ����ĸ��
	
	char szBelongUnit[64];         //��ܵ�λ��15�����ֻ�30����ĸ;
	char szBelongUnitPhone[16];    //��ܵ�λ�绰��14λ���֣��ֻ���"-" �����;
	
	char szPoliceUnit[64];         //������λ��15�����ֻ�30����ĸ;
	char szPoliceUnitAddr[128];     //������λ��ַ��30�����ֻ�60����ĸ;
	char szPoliceUnitPhone[16];    //������λ�绰��14λ���֣��ֻ���"-"�����;
	
	char szPolicePhone[4][16];
	char szPolOrCenPhone[2][16];   //����/���ĵ绰1��2��14λ���֣��ֻ���"-" �����;

	char szFTP[64];                //FTP��50���ַ���
	char szEMail[64];              //E-Mail: 50���ַ���
	LOCALSDK_IPAddress PoliceIP;            //�Ӿ�����IP��ַ
	int nHttpPort;                 //�Ӿ�����IP�˿�
};

/***�豸��Ϣ***/
//���ò�������ö��
typedef enum GuardType
{
	FORBID = 0,      //��ֹ
	TEN_MIN,         //ʮ����
	THIRTY_MIN,      //��ʮ����
	SIXTY_MIN,       //��ʮ����
	MAX,
}GUARDTYEP;

struct CONFIG_KAINENG_DEVINFO
{
	char ProbeNum1;                //��������������������ÿ��������� 1�ŵ�10��̽����ѡ�� ��Ĭ������Ϊ <1��̽����>
	char ProbeNum2;                //��������������������ÿ��������� 1�ŵ�10��̽����ѡ�� ��Ĭ������Ϊ <1��̽����>	
	char nProbeType;			   //������������ ��ѡ��3��Ϊ <��ֹ>  <AND>  <OR>  Ĭ��Ϊ <��ֹ>
	char nGuardType;               //���ò���, ����GUARDTYEP

	int AlarmTime;                //���ѿ���ʱ�䣺��λ���ִ�000-999  Ĭ��Ϊ��180
	int nGuardArea;               //���߷������ͣ���λ���֣�ÿλ��С0���3����00000000 ��33333333;  Ĭ�ϣ�00000000��
	
	char szRemConAddr[4][4];       //ң����1-4�ŵ�ַ ����λ16�����ַ�����գ���0-9  A-F����Ĭ��Ϊ�գ�
	char szLinDevAddr[6][4];       //�����豸��1-6��ַ����λ16�����ַ�����գ���0-9  A-F����Ĭ��Ϊ�գ�
	char szProbeAddr[10][4];       //̽����1-10�ŵ�ַ����λ16�����ַ�����գ���0-9  A-F����Ĭ��Ϊ�գ�
	
	//��ʱ������
	char szGuardTime[3][9];        //��ʱ������,ÿ�鶼Ϊchar [8] ���� ��00 00 00 00������ɿ�ʼʱ�ֵ�����ʱ�֣�����Ҫ��������
};



/***��������***/
//��������ö��
typedef enum KNAlarmLink
{
	LINK_EMPTY = 0,
	LINK_SWITH,
	LINK_10S,
	LINK_30S,
	LINK_60S,
	LINK_200S,
	LINK_600S,
	LINK_METHOD_1,
	LINK_METHOD_2,
	LINK_MAX
}KNALARMLINK;

struct CONFIG_KAINENG_LINKINFO
{
	char eLink[10][7];        //��������,ȡֵΪ��������ö��
};

//���ܶ��ƣ�3��������Ϣȫ�����
typedef struct CONFIG_KAINENG_INFO
{
	CONFIG_KAINENG_USERINFO UserInfo;
	CONFIG_KAINENG_DEVINFO DevInfo;
	CONFIG_KAINENG_LINKINFO LinkInfo;
}LOCALSDK_CONFIG_KAINENG_INFO;

//���ܻص��ṹ��
typedef struct 
{	CONFIG_KAINENG_DEVINFO DevInfo;
	CONFIG_KAINENG_LINKINFO LinkInfo;
}LOCALSDK_CBCONFIG_KAINENG_INFO;

// VPN���ýṹ
typedef struct
{
	int		enable;			///< �Ƿ�����VPN��0-��������1-����
	char	serverip[32];	///< VPN������IP��ַ����0���������ַ����������ʽ����192.168.0.6��
	char	username[64];	///< VPN�����û�������0���������ַ�����
	char	password[64];	///< VPN�������룬��0���������ַ�����
}LOCALSDK_NET_VPN_CONFIG;

//����ƽ̨���󣬻�ȡԤ¼����
typedef struct PRERecord
{
	int iChannel;
	int iSecond;
}LOCALSDK_PRERECORD_INFO;

//������һ���ͻ���Ҫ����һЩ�Զ�����Ϣ���úͶ�ȡ�Ľӿ�
typedef struct
{
	int iIndex;        //��Χ0��9���洢10����Ϣ
	char szContent[64];
}LOCALSDK_CUSTOMINFO;

typedef struct
{
	int iChannel;
	
}LOCALSDK_DIGCHANNELINFO;


//�û������Ƿ���Ч
typedef struct
{
	char	Username[64];   //�û���
	char	Password[64];	//����
	char    IsValid;        //0��Ч��1��Ч��
}LOCALSDK_USERPW_ISVALID;

//���մ���C7ƽ̨����
typedef struct
{
	char pServerAddr[64];//ƽ̨��ַ��IP��ַ������
	int  servPort;       //ƽ̨�˿�
	char pPUID[32];      //PUID
	char pPassword[32];  //����
}LOCALSDK_CHUANGSHI_INFO;

// ������̩��ƽ̨����
typedef struct
{
	bool bEnable;
	char ServerUrl[64]; //��������ַ
	char DevID[16];     //�豸id
	char Password[16];  //�豸��֤��
	char DevModel[16];     //�豸�ͺ�
	char SerialNo[20]; //�豸���к�	
}LOCALSDK_BJHONGTAIHENG_INFO;

typedef struct 
{
	char ChannelNum;
	char ChannelTypes[32];     //ChannelTypes[0] = 1;,��ʾ��һͨ����ģ��ͨ����ChannelTypes[1] = 2����ʾ�ڶ�ͨ��������ͨ��
}LOCALSDK_CHANNEL_INFO;
/// ����ͨ������
enum capture_channel_t {
	CHL_MAIN_T = 0,		///< ��ͨ��	��	������1 
	CHL_2END_T = 1,		///< ��ͨ��	��	��������2 
	CHL_3IRD_T = 2,		///< ��ͨ��	��	��������3 
	CHL_4RTH_T = 3,		///< ��ͨ��	��	��������4 
	CHL_JPEG_T = 4,		///< ��ͨ��	��	��JPEGץͼ 
	CHL_FUNCTION_NUM
};


typedef struct 
{
	char ChannelNum;
	char ChannelTypes[64];     //ChannelTypes[0] = 1;,��ʾ��һͨ����ģ��ͨ����ChannelTypes[1] = 2����ʾ�ڶ�ͨ��������ͨ��
}LOCALSDK_CHANNEL_INFO_V2;

/*
typedef struct 
{
	char* ChannelTypes;     //ChannelTypes[0] = 1;,��ʾ��һͨ����ģ��ͨ����ChannelTypes[1] = 2����ʾ�ڶ�ͨ��������ͨ��
	int maxChannelNum;
	int retChannelNum;
}LOCALSDK_CHANNEL_INFO_V2;*/
/// ����ʼ����
enum capture_start_t {
	CAPTURE_START_VIDEO = 1,	///< ��Ƶ���뿪��
	CAPTURE_START_AUDIO = 2		///< ��Ƶ���뿪��
};

/// ����ѹ����ʽ����
enum capture_comp_t {
	CAPTURE_COMP_DIVX_MPEG4,	///< DIVX MPEG4��
	CAPTURE_COMP_MS_MPEG4,		///< MS MPEG4��
	CAPTURE_COMP_MPEG2,			///< MPEG2��
	CAPTURE_COMP_MPEG1,			///< MPEG1��
	CAPTURE_COMP_H263,			///< H.263
	CAPTURE_COMP_MJPG,			///< MJPG
	CAPTURE_COMP_FCC_MPEG4,		///< FCC MPEG4
	CAPTURE_COMP_H264,			///< H.264
	CAPTURE_COMP_NR				///< ö�ٵ�ѹ����׼��Ŀ��
};

/// ������������ģʽ����
enum capture_brc_t {
	CAPTURE_BRC_CBR,			///< �̶�������
	CAPTURE_BRC_VBR,			///< �ɱ�������
	CAPTURE_BRC_MBR,			///< ���������
	CAPTURE_BRC_NR				///< ö�ٵ���������ģʽ��Ŀ��
};

/// ����ֱ�������
/// \note������������ṹʱ��Ҫͬ������Record.cpp����֤��������
enum capture_size_t {
	LOCALSDK_CAPTURE_SIZE_D1,		///< 704*576(PAL)	704*480(NTSC)
	LOCALSDK_CAPTURE_SIZE_HD1,		///< 704*288(PAL)	704*240(NTSC)
	LOCALSDK_CAPTURE_SIZE_BCIF,		///< 352*576(PAL)	352*480(NTSC)
	LOCALSDK_CAPTURE_SIZE_CIF,		///< 352*288(PAL)	352*240(NTSC)
	LOCALSDK_CAPTURE_SIZE_QCIF,		///< 176*144(PAL)	176*120(NTSC)
	LOCALSDK_CAPTURE_SIZE_VGA,		///< 640*480(PAL)	640*480(NTSC)
	LOCALSDK_CAPTURE_SIZE_QVGA,		///< 320*240(PAL)	320*240(NTSC)
	LOCALSDK_CAPTURE_SIZE_SVCD,		///< 480*480(PAL)	480*480(NTSC)
	LOCALSDK_CAPTURE_SIZE_QQVGA,		///< 160*128(PAL)	160*128(NTSC)
	LOCALSDK_CAPTURE_SIZE_NR = 9,	///< ����ʱ����ȵײ�һ���޸�
	LOCALSDK_CAPTURE_SIZE_ND1 = 9,   ///< 240*192
	LOCALSDK_CAPTURE_SIZE_650TVL,    ///< 960*576
	LOCALSDK_CAPTURE_SIZE_720P,      ///< 1280*720
	LOCALSDK_CAPTURE_SIZE_1_3M,      ///< 1280*960
	LOCALSDK_CAPTURE_SIZE_UXGA ,     ///< 1600*1200
	LOCALSDK_CAPTURE_SIZE_1080P,     ///< 1920*1080
	LOCALSDK_CAPTURE_SIZE_WUXGA,     ///< 1920*1200
	LOCALSDK_CAPTURE_SIZE_2_5M,      ///< 1872*1408
	LOCALSDK_CAPTURE_SIZE_3M,        ///< 2048*1536
	LOCALSDK_CAPTURE_SIZE_5M,        ///< 3744*1408
	LOCALSDK_CAPTURE_SIZE_EXT_NR = 19,    ///< ö�ٵ�ͼ�δ�С�������Ŀ��
	LOCALSDK_CAPTURE_SIZE_1080N = 19,     ///< 960*1080
	LOCALSDK_CAPTURE_SIZE_4M,        ///< 2560��1440
	LOCALSDK_CAPTURE_SIZE_6M,		///< 3072��2048
	LOCALSDK_CAPTURE_SIZE_8M,		///< 3264��2448
	LOCALSDK_CAPTURE_SIZE_12M,		///< 4000*3000
	LOCALSDK_CAPTURE_SIZE_4K,		///< 4096 * 2160/3840*2160
	LOCALSDK_CAPTURE_SIZE_EXT_V2_NR = 25,    ///< ö�ٵ�ͼ�δ�С�������Ŀ��
	LOCALSDK_CAPTURE_SIZE_720N=25,     ///< 640*720
	LOCALSDK_CAPTURE_SIZE_RES1,		///< 0*0����
	LOCALSDK_CAPTURE_SIZE_RES2,		///< 0*0
	LOCALSDK_CAPTURE_SIZE_RES3,		///< 0*0
	LOCALSDK_CAPTURE_SIZE_RES4,		///< 0*0
	LOCALSDK_CAPTURE_SIZE_RES5,		///< 0*0
	LOCALSDK_CAPTURE_SIZE_RES6,		///< 0*0
	LOCALSDK_CAPTURE_SIZE_EXT_V3_NR
};

typedef struct 
{
	unsigned int uiImageSize;  ///< ÿ��ͨ��֧�ֵ�ͼ��ֱ���
	unsigned int uiExImageSize;  ///< ÿ��ͨ��֧�ֵĸ�����ͼ��ֱ���
	unsigned int uiExImageSizeEx[LOCALSDK_CAPTURE_SIZE_EXT_NR]; ///< ָ���������ֱ�����ÿ��ͨ���ĸ�����֧�ֵ�ͼ��ֱ���
	unsigned int uiMaxPower;///<ÿ��ͨ��֧�ֵ��ܱ�������
	unsigned int uiExImageSizeEx2[LOCALSDK_CAPTURE_SIZE_EXT_V2_NR - LOCALSDK_CAPTURE_SIZE_EXT_NR]; ///< ָ���������ֱ�����ÿ��ͨ���ĸ�����֧�ֵ�ͼ��ֱ���	
	unsigned int res[11 - LOCALSDK_CAPTURE_SIZE_EXT_V2_NR + LOCALSDK_CAPTURE_SIZE_EXT_NR];
}LOCALSDK_CHANNEL_ABILITY;

typedef struct 
{
	unsigned int uiImageSize;  ///< ÿ��ͨ��֧�ֵ�ͼ��ֱ���
	unsigned int uiExImageSize;  ///< ÿ��ͨ��֧�ֵĸ�����ͼ��ֱ���
	unsigned int uiExImageSizeEx[LOCALSDK_CAPTURE_SIZE_EXT_V3_NR]; ///< ָ���������ֱ�����ÿ��ͨ���ĸ�����֧�ֵ�ͼ��ֱ���
	unsigned int uiMaxPower;///<ÿ��ͨ��֧�ֵ��ܱ�������
	unsigned int res[8];
}LOCALSDK_CHANNEL_ABILITY_V2;

typedef struct LOCALSDK_CAPTURE_CAPS
{
	/// ֧�ֵ�ѹ����׼�����룬λ��Ŷ�Ӧö������capture_comp_t��ÿһ��ֵ��
	/// ��1��ʾ֧�ָ�ö��ֵ��Ӧ�����ԣ���0��ʾ��֧�֡�
	unsigned int Compression;

	/// ֧�ֵ���������ģʽ�����룬λ��Ŷ�Ӧö������capture_brc_t��ÿһ��ֵ��
	/// ��1��ʾ֧�ָ�ö��ֵ��Ӧ�����ԣ���0��ʾ��֧�֡�
	unsigned int BitRateControl;

	/// ֧�ֵ�ͼ���С���͵����룬λ��Ŷ�Ӧö������capture_size_t��ÿһ��ֵ��
	/// ��1��ʾ֧�ָ�ö��ֵ��Ӧ�����ԣ���0��ʾ��֧�֡�
	/// ��V2�汾�ӿ����Ѿ�����ʹ��
	unsigned int ImageSize;

	/// ֧�ֵ�ý�����͵����룬��ö������capture_start_t��ÿһ��ֵ���룬�õ���Ӧ
	/// �����ԡ���1��ʾ֧�ָ�ö��ֵ��Ӧ�����ԣ���0��ʾ��֧�֡�
	unsigned int Media;

	/// ���򸲸ǵ�֧�ֵĿ�����
	int CoverBlocks;

	/// ������
	int Reserved;

	/// ֧�����ı�����ӵĸ�����
	int	TitleCount;

	/// �Ƿ�֧�����򸲸� 0-��֧�֣�1-֧��ʵʱ�����򸲸ǣ� ����������ʱ
	/// �ٶȽϿ죬����ʵʱ���ã� 2-֧�ַ�ʵʱ�����򸲸ǣ�����������ʱ�ٶȽ�����
	/// ֻ�����û�ȷ���������á�  
	int	RegionCover;
} LOCALSDK_CAPTURE_CAPS;
enum EncStaticParam
{
	ENC_STATICPARAM_BASELINE = 0,	//֧��baseline
	ENC_STATICPARAM_MAINPRO,	//֧��main profile
	ENC_STATICPARAM_HIGHPRO,	//֧��high profile
	ENC_STATICPARAM_NR
};
typedef struct
{
	LOCALSDK_CHANNEL_ABILITY DspAbility[32];
	LOCALSDK_CAPTURE_CAPS CapsAbility;	///<��������
	unsigned int uiMaxEncodePower;      ///< ֧�ֵ��ܱ�������
	unsigned int uiMaxBps;              ///< ֧�ֵ������ʴ�СKbps	
	unsigned int uEncStaticParam;	///��̬��������
	unsigned int uiResverd[13];
}LOCALSDK_CAPTURE_DSPINFO;

typedef struct
{
	LOCALSDK_CHANNEL_ABILITY_V2 DspAbility[32];
	LOCALSDK_CAPTURE_CAPS CapsAbility;	///<��������
	unsigned int uiMaxEncodePower;      ///< ֧�ֵ��ܱ�������
	unsigned int uiMaxBps;              ///< ֧�ֵ������ʴ�СKbps
	unsigned int uEncStaticParam;	///��̬��������
	unsigned int uiResverd[13];
}LOCALSDK_CAPTURE_DSPINFO_V2;

typedef struct
{
	LOCALSDK_CHANNEL_ABILITY* DspAbility;
	int maxsize;
	int retsize;
	unsigned int uiResverd[24];
}LOCALSDK_CAPTURE_DSPINFO_V3;

typedef struct
{
	char	ModuleName[64];		//ģ����
	char	pInfo[256];			//��Ϣ
}LOCALSDK_INFO_FRAME;


#define  MAX_EMAIL_TITLE_LEN 64
#define  MAX_EMAIL_RECIEVERS  5
typedef struct
{
	///< �Ƿ���
	bool Enable;
	///< smtp ��������ַʹ���ַ�����ʽ���
	///< ������ip,Ҳ����������
	LOCALSDK_REMOTE_CFG Server;
	bool bUseSSL;
	///< ���͵�ַ
	char SendAddr[EMAIL_ADDR_LEN];
	///< �����˵�ַ
	char Recievers[MAX_EMAIL_RECIEVERS][EMAIL_ADDR_LEN];
	///< �ʼ�����
	char Title[MAX_EMAIL_TITLE_LEN];
	///< email��Чʱ��
	TIME_SECTION Schedule[N_MIN_TSECT];
}LOCALSDK_EMAIL_CFG;

enum DecChnState
{
	DecStaNone, 			//����
	DecStaNoConfig,		//δ����
	DecStaNoLogin,		//δ��½
	DecStaNoConnect,		//δ����
	DecStaConnected,		//������
	decStaLoginFailed,	//��½ʧ��
};
	
typedef struct
{
	int chnstate; //enum DecChnState
	int res[8];
}LOCALSDK_DIGIT_CHN_STATE;

typedef struct LOCALSDK_ASB_NET_VSP_CFG
{
	bool		bCsEnable;				//ʹ�ܱ��
	char		szCsIP[64];				//��������ַ	(IP)
	short	sCsPort;					//�������˿�
	short	sUdpPort;				//���ط�����udp�˿�
	char		szServerNo[64];			//���������
	char 		szServerDn[64];			//����������(����Ϊ28181���)
	char		szDeviceNO[64];			//�豸���
	char 		szConnPass[64];			//�豸ע������
	int		iHsIntervalTime;			//�������ʱ��,��λ����
	int		iRsAgedTime;			//ע����Ч�ڣ���λΪ��
	char		Camreaid[MAX_CHANNEL_NUM][64];	//ͨ�����
	int		CamreaLevel[MAX_CHANNEL_NUM];	//��������
	char		Alarmid[MAX_CHANNEL_NUM][64];	//�������
	int		AlarmLevel[MAX_CHANNEL_NUM];	//��������
	uint		uiAlarmStateGpinEnable;	//�ⲿ����ʹ��
	uint		uiAlarmStateLoseEnable;	//��Ƶ��ʧ�澯ʹ��
	uint		uiAlarmStateMotionEnable;//��Ƶ��̬���澯ʹ��
	uint		uiAlarmStateBlindEnable;	//��Ļ�ڵ��澯ʹ��
	uint		uiAlarmStatePerformanceEnable;	//ϵͳ�쳣�澯ʹ��
	uint		uiAlarmStateConnectEnable;	//�û����Ӹ澯ʹ��
}ASB_NET_VSP_CONFIG;

enum RSSI_SINGNAL
{
	RSSI_NO_SIGNAL,   //<= -90db
	RSSI_VERY_LOW,     //<= -81db
	RSSI_LOW,          //<= -71db
	RSSI_GOOD,         //<= -67db
	RSSI_VERY_GOOD,    //<= -57db
	RSSI_EXCELLENT     //>-57db
};
typedef struct 
{
	char SSID[36];
	int nRSSI;                          //SEE RSSI_SINGNAL
	int nChannel;
	char  NetType[32];	 //Infra, Adhoc
	char  Encode[32];   // NONE, WEP, TKIP, AES
	char  Auth[32];      // OPEN, SHARED, WEPAUTO, WPAPSK, WPA2PSK, WPANONE, WPA, WPA2
}LOCALSDK_WLAN_DEVICE;

typedef struct 
{
	LOCALSDK_WLAN_DEVICE *pWlanDev;
	int MaxDevNum;
	int RetDevNum;
}LOCALSDK_WLAN_DEVICE_LIST;

enum DiskFullPolicy
{	
	DISK_FULL_POLICY_STOP_RECORD,	///< ֹͣ¼��
	DISK_FULL_POLICY_OVERWRITE,		///< ����
	DISK_FULL_POLICY_NR
};

///< ��ͨ����
typedef struct
{	
	int iLocalNo;				///< �������:[0, 998] 	
	int iOverWrite;				///< Ӳ����ʱ�Ĵ������DiskFullPolicy
	int iAutoLogout;			///< ���ز˵��Զ�ע��(����)	[0, 120]
}LOCALSDK_GENERAL_CONFIG;

enum TimeSynTypes
{
	TST_OFF = 0,
	TST_TIME_UTC,
	TST_TIME_LOCAL,
	TST_TIME_ALL,
	TST_NR
};

typedef struct
{
	int *pDigitTimeSync;
	int NumDigit;
}LOCALSDK_TIMESYNC_CONFIG;
typedef struct 
{
	int left;
	int top;
	int right;
	int bottom;
}TRect;
typedef uint 			RGBA32;		//0x00bbggrr

/// ��Ƶ����ṹ
struct  VIDEO_WIDGET
{
	RGBA32 rgbaFrontground;		///< �����ǰ��MakeRGB����͸����	
	RGBA32 rgbaBackground;		///< ����ĺ�MakeRGB����͸����	
	TRect	rcRelativePos;		///< ����߾��������ı���*8191
	bool	bShowInPreview;		///< Ԥ������	
	bool	bShowInEncode;		///< �������
};

//��Ļ��ʾ��Ϣ
typedef struct
{
	VIDEO_WIDGET OSDInfoWidget;
	char ppInfo[12][64];
}LOCALSDK_OSD_DOT_CFG;

enum WindowStyle
{
	split1,
	split2,	
	split4,	
	split8,
	split9,	
	split16,
	splitPIP,
	split6,
	split12,
	split25,
	split36,
	split5,
	split10,
	split20,
	splitNR,
};

typedef struct
{
	int spt;		//�ָ��enum WindowStyle
	int sub;		//�ָ����ģʽ
}LOCALSDK_SPLIT_MODEL;


///< ftp����
typedef struct NetFtpServerConfig{
	bool bEnable;        ///< ������ʹ��     
	LOCALSDK_REMOTE_CFG Server;	///< FTP������
	char cRemoteDir[MAX_DIRPATH_LENGTH];	///< Զ��Ŀ¼
	int iMaxFileLen;	///< �ļ���󳤶�
}LOCALSDK_FTP_CFG;

/// ¼��洢�豸���ͣ��������͵�һ�ֻ��߶���
typedef struct
{
	bool SATA_as;
	bool USB_as;
	bool SD_as;
	bool DVD_as;
}LOCALSDK_STORAGE_TYPE;

///<Ӳ�̳����¼��ṹ
typedef struct
{
	bool 	bEnable;
	EVENT_HANDLER hEvent;	///< �������
	bool	bRebootEnable;		//ϵͳ����ʹ��
}LOCALSDK_STORAGE_FAIL_CFG;

///< Ӳ�����������¼��ṹ
typedef struct StorageLowSpaceConfig
{
	bool bEnable;
	int iLowerLimit;		///< Ӳ��ʣ����������
	EVENT_HANDLER hEvent;	///< �������
	bool bRecordTimeEnable;
	int iRecordTime;		///<¼������
	int Limittype;			///<ʣ��������λ
}LOCALSDK_STORAGE_LOW_SPACE_CFG;

/// ��Ƶ�������
typedef struct 
{
	VIDEO_WIDGET	dstCovers[8];
	VIDEO_WIDGET	ChannelTitle;
	VIDEO_WIDGET	TimeTitle;
	struct 
	{
		char strName[64];
		unsigned long long iSerialNo;	
	} ChannelName;					/// ͨ������
	int				iCoverNum;		/// ��ǰ��ͨ���м������ӵ�����
}LOCALSDK_VIDEOWIDGET_CFG;

typedef struct
{
	int index;
	bool bFlagSave;
	LOCALSDK_OSD_DOT_CFG OsdCfg;
}LOCALSDK_OSD_CFG_V2;
typedef struct
{
	int MsgLen;
	char pNum[32][32];//���32�����룬ÿ���������32λ
	char* pMsg;
}LOCALSDK_SMS;

typedef struct
{
	int EnStop;		//�Ƿ�ֹͣ������
	int YH;			//y���ݵĸ�,uv���ݸ�Ϊy���ݵ�1/2
	int yuvW;		//yuv���ݵĿ��
	char pFileName[256];//���·��
}LOCALSDK_YUV;

enum WIRELESS_TYPE_AUTOSEL
{
	WIRELESS_TYPE_wcdma,			//��ͨ
	WIRELESS_TYPE_td_scdma,		//�ƶ�
	WIRELESS_TYPE_evdo, 			//����	
	WIRELESS_TYPE_cdma_1x,  
	WIRELESS_TYPE_edge, 
	WIRELESS_TYPE_net4g, ///4g�ź�ǿ��
	WIRELESS_TYPE_NR
};
typedef struct  
{
	int type;			//��Ӫ��WIRELESS_TYPE_AUTOSEL
	int value;		//ǿ��
	int reserved[4]; /*�����ֽڣ�������չ*/
}LOCALSDK_WIRELESS_RSSI;


typedef struct 
{
	char ProductType[128];
}LOCALSDK_OEM_VERSION;

// ------------------------------ ���ܷ���������� ----------------------------------------
// from IMP header: �������ݽṹ
/** URP������������� */
#define IMP_URP_MAX_TRIPWIRE_CNT 8

/** ���߽���� */
#define IMP_MAX_BOUNDARY_POINT_NUM 8

typedef short IMP_S16;
typedef int IMP_S32;

/** ����� */
typedef struct
{
	IMP_S16 s16X;					/**< x */
	IMP_S16 s16Y;					/**< y */
}URP_IMP_POINT_S;

/** �߽ṹ */
typedef struct
{
	URP_IMP_POINT_S stStartPt;			/**< �߶���� */
	URP_IMP_POINT_S stEndPt;			/**< �߶��յ� */
}URP_LINE_S;

/** URP�����߽ṹ */
typedef struct
{
	IMP_S32     s32Valid;						/**< �Ƿ���Ч */
	IMP_S32     s32IsDoubleDirection;				/**< ��ʾ�ð����Ƿ�Ϊ˫�����(0: ��, 1: ��) */
	IMP_S32     s32ForbiddenDirection;				/**< �����߽�ֹ����Ƕ�(��λ: ��) */
	URP_LINE_S	stLine;						/**< ������λ�� */
}URP_TRIPWIRE_S;

/** URP���������Ʋ��� */
typedef struct
{
	IMP_S32 s32MinDist;						/**< ��С���ؾ��� */
	IMP_S32 s32MinTime;						/**< ���ʱ�� */
}URP_TRIPWIRE_LIMIT_PARA_S;

/** URP�����߹������ */
typedef struct
{
	IMP_S32 s32TypeLimit;						/**< Ŀ���������� */
	IMP_S32 s32TypeHuman;						/**< Ŀ�������(�޶�����ʱʹ��) */
	IMP_S32 s32TypeVehicle;						/**< Ŀ����𣺳� */
	URP_TRIPWIRE_S astLines[IMP_URP_MAX_TRIPWIRE_CNT];		/**< ������ */
	URP_TRIPWIRE_LIMIT_PARA_S stLimitPara;				/**< ���������Ʋ��� */
} URP_TRIPWIRE_RULE_PARA_S;

/** URP�ܽ���߽�� */
typedef struct
{
	IMP_S32       s32BoundaryPtNum;					/**< �߽����Ŀ */
	URP_IMP_POINT_S   astBoundaryPts[IMP_MAX_BOUNDARY_POINT_NUM];	/**< �߽�㼯�� */
}URP_PERIMETER_LIMIT_BOUNDARY_S;

/** URP�ܽ������Ʋ��� */
typedef struct
{
	IMP_S32 s32MinDist;						/**< ��С���ؾ��� */
	IMP_S32 s32MinTime;						/**< ���ʱ�� */
	IMP_S32	 s32DirectionLimit;					/**< �Ƿ����������� */
	IMP_S32 s32ForbiddenDirection;					/**< ��ֹ����Ƕ�(��λ: �Ƕ�) */
	URP_PERIMETER_LIMIT_BOUNDARY_S stBoundary;			/**< �ܽ�߽����� */
}URP_PERIMETER_LIMIT_PARA_S;

/** URP�ܽ��������� */
typedef struct
{
	IMP_S32 s32TypeLimit;						/**< Ŀ���������� */
	IMP_S32 s32TypeHuman;						/**< Ŀ�������(�޶�����ʱʹ��) */
	IMP_S32 s32TypeVehicle;						/**< Ŀ����𣺳� */
	IMP_S32 s32Mode;						/**< �ܽ�ģʽ */
	URP_PERIMETER_LIMIT_PARA_S stLimitPara;				/**< �ܽ����Ʋ��� */
} URP_PERIMETER_RULE_PARA_S;

typedef struct
{
	int iShowTrack;						/// �Ƿ���ʾ�켣
	int iShowRule;						/// �Ƿ���ʾ����
	int iLevel;						   /// ���伶��2���ͼ���1���м���0: �߼�
	int iPerimeterEnable;					/// �ܽ����ʹ��
	//PERIMETER_RULE_S  stPerimeter;			/// �ܽ����
	URP_PERIMETER_RULE_PARA_S	stPerimeterRulePara;	/**< �ܽ��� */
	int iTripWireEnable;					/// �����߹���ʹ��
	//TRIPWIRE_RULE_PARA_S  stTripWire;			/// �����߹���
	URP_TRIPWIRE_RULE_PARA_S	stTripwireRulePara;	/**< �����߼�� */
}PEA_RULE_S;

//һ��ͨ�������ܷ�������
typedef struct
{
	bool         bEnable;      //�Ƿ�������Ƶ��������
	EVENT_HANDLER hEvent;  //�����¼�
	PEA_RULE_S stRulePea;   //�ܽ������������
}LOCALSDK_PEA_RULE_Config;

//һ��ͨ�������ܷ�������
typedef struct
{
	bool         bEnable;      //�Ƿ�������Ƶ��������
	EventHandler_V2 hEvent;  //�����¼�
	PEA_RULE_S stRulePea;   //�ܽ������������
}LOCALSDK_PEA_RULE_Config_V2;

//---------------------------------------------------------------------------------------------------

//------------- ����ģʽ���� --------------------
typedef enum{
	FEC_APP_CEIL = 0, 
	FEC_APP_TABL = 1,
	FEC_APP_WALL = 2
}FEC_APP_TYPE_E;

typedef enum{
	FEC_SECENE_ORIG	= 0,
	FEC_SECENE_R = 1,
	FEC_SECENE_P180_ALL = 2,
	FEC_SECENE_P180_ONE = 3,
	FEC_SECENE_P180_TWO = 4,
	FEC_SECENE_P360_FULL = 5,
	FEC_SECENE_P360_SEPE = 6,
	FEC_SECENE_P360_HALF = 7,
	FEC_SECENE_ROP_R = 8,
	FEC_SECENE_RORR_R = 9,
	FEC_SECENE_RRRR_R = 10,
	FEC_SECENE_RRP_R = 11
}FEC_SECENE_E;

typedef struct{
	unsigned int appType;//FEC_APP_TYPE_E
	unsigned int secene;//FEC_SECENE_E
	unsigned int reserv[8];
}LOCALSDK_FishEye_Config;
//----------------------------------------------


#endif

