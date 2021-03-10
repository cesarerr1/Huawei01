/*Copyright 2015 Huawei Technologies Co., Ltd. All rights reserved.
eSDK is licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at
		http://www.apache.org/licenses/LICENSE-2.0
Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.*/

/********************************************************************
filename	: 	IVS_SDKTVWall.h
author		:	g00209332
created		:	2012/12/21	
description	:	SDK�����ṩ����ǽ��ؽӿڶ���
                ��Ϊ����ǽ�ӿڲ����⿪�ţ�ֻ��OCXʹ�ã����Բ�����IVS_SDK.h��
copyright	:	Copyright (C) 2011-2015
history		:	2012/12/21 ��ʼ�汾;
*********************************************************************/
#ifndef __IVS_SDK_TVWALL_H__
#define __IVS_SDK_TVWALL_H__

#include "hwsdk.h"

#ifdef WIN32
#ifdef  IVS_SDK_EXPORTS
#define IVS_SDK_API __declspec(dllexport)
#else
#define IVS_SDK_API __declspec(dllimport)
#endif
#else
//#define IVS_SDK_API __attribute__((visibility))
#define IVS_SDK_API __attribute__((visibility("default")))
#endif

#define CUMW_SESSION_ID_LEN          512  //�ỰID����󳤶�
#define CUMW_SESSION_URL_LEN         512  //�ỰUrl����󳤶�
#define CUMW_ERROR_DESCRIPTION_LEN   512  //�������Ӧ������������󳤶�
#define CUMW_DECODER_ID_LEN          20   //������ID�ĳ���
#define CUMW_DECODER_NAME_LEN        32   //������ͨ�����Ƴ���
#define CUMW_DECODER_ENCODING_LEN    16   //�����������ʽ��󳤶�
#define CUMW_DECODER_CHANNEL_MAX_NUM 36   //������ͨ���������ֵ
#define CUMW_CHANNEL_NAME_LEN        32   //������ͨ�����Ƴ���
#define CUMW_PAY_LOAD_TYPE_NUM       16   //PayLoadType��������
//#define CUMW_DECODER_CHANNEL_MAX_NUM 64   //������ͨ���������ֵ
#define CUMW_MAX_PORT_ONE_TYPE_NUM   8    //һ��������֧�ֵ�ĳ�����Ͷ˿�������Ŀ
#define DECODER_MAX_CHANNEL_NUM      32

//TVWall���ش����� (���������λ��ţ�OCX 000��199 SDK 200��399 MP 400��599 TVWALL 600~799)
typedef enum
{
	IVS_TVWALL_MEMORY_NULL = 999115600,			      //ָ��Ϊ��
	IVS_TVWALL_CREATE_THREAD_FAIL = 999115601,        //�����߳�ʧ��
	IVS_TVWALL_BUSINESS_ID_NO_EXIST = 999115602,      //ҵ��ID������
	IVS_TVWALL_SEND_FAIL = 999115603,                 //������Ϣʧ��

	IVS_TVWALL_INIT_NO = 999115607,                   //��δ��ʼ��
	IVS_TVWALL_INIT_ALREADY = 999115608,              //�Ѿ���ʼ��
	IVS_TVWALL_TV_WALL_SRC_RUNING = 999115609,        //����ǽ�����Ѿ�����
	IVS_TVWALL_TV_WALL_SRC_STOPED = 999115610,	      //����ǽ������δ����
	IVS_TVWALL_DECODER_OFFLINE = 999115611,           //������������
	IVS_TVWALL_DECODER_NO_CHANNEL = 999115612,        //������û�и�ͨ��
	IVS_TVWALL_DECODER_INIT_CHANNEL_FAIL = 999115613, //��ʼ��������ͨ��ʧ��
	IVS_TVWALL_STOP_FLAG = 999115614,                  //����������ǽ�Ĺ����У��յ�ֹͣ������ڲ�ʹ�ã�
	IVS_TVWALL_DECODER_NO_CAPABILITY = 999115615,                  //���������߱��޷��л�����

	IVS_TVWALL_FIND_PACKET_FAIL = 999115616, //���Ұ�ʧ��
	IVS_TVWALL_NET_FAIL = 999115617, //��������ԭ��������æ, ��¼ʧ��!
	IVS_TVWALL_HAS_SAME_NAME_DEC = 999115618, //�Ѿ�����ͬ�Ľ�����������ϵͳ��
} IVS_TVWALL_ERR_CODE;


//��Ƶ������Э��
enum RDA_PROTOCOL
{
	RDA_PROTOCOL_NONE = 0x00,
	RDA_PROTOCOL_NSS_OVER_UDP = 0x02, //NSS Over UDP
	RDA_PROTOCOL_NSS_OVER_TCP = 0x03, //NSS Over TCP
	RDA_PROTOCOL_RTP_OVER_UDP = 0x04, //RTP Over UDP
	RDA_PROTOCOL_RTP_OVER_TCP = 0x05, //RTP Over TCP
	RDA_PROTOCOL_MAX  = 0x06 //���ֵ
};

//ý���������Ϣ
typedef struct
{
	unsigned short usTcpInterleavedPort;       //TCP��֯�˿�
	unsigned short usUdpVideoRtpPort;          //UDP��ƵRTP�˿�
	unsigned short usUdpVideoRtcpPort;         //UDP��ƵRTCP�˿�
	unsigned short usUdpAudioRtpPort;          //UDP��ƵRTP�˿�
	unsigned short usUdpAudioRtcpPort;         //UDP��ƵRTCP�˿�

	char          szMediaIP[IVS_IP_LEN];//��������ý��ͨ��IP
	unsigned char ucTransportProtocol;         //��Ƶ����Э��
} CUMW_MEDIA_NET_INFO;

//�����ʼ����Ϣ
typedef struct
{
	unsigned long  ulAsyncSeq;                          //�첽�������
	unsigned short usChannelNo;                         //ͨ�����
	char           szDecoderID[CUMW_DECODER_ID_LEN + 1];//������ID��20λ��������\0��
	unsigned char  ucTransportProtocol;                 //��Ƶ����Э��
} IPI_INIT_BUSINESS_REQ;


//����Զ�̽�������Ϣ
typedef struct
{
	unsigned long  ulAsyncSeq;                          //�첽�������
	unsigned long  ulBusinessID;
	unsigned short usChannelNo;                         //ͨ�����

	char           szSessionId[CUMW_SESSION_ID_LEN];    //�ỰID
	char           szSessionUrl[CUMW_SESSION_URL_LEN];  //�ỰURL
	char           szDecoderID[CUMW_DECODER_ID_LEN + 1];//������ID��20λ��������\0��

	unsigned char  ucVideoPayloadType;                  //��ƵPayload����
	unsigned char  ucAudioPayloadType;                  //��ƵPayload����

	CUMW_MEDIA_NET_INFO stMediaNetInfo;                 //ý���������Ϣ
} IPI_START_BUSINESS_REQ;

//ֹͣ����Ƶ������Ϣ
typedef struct
{
	unsigned long  ulAsyncSeq;                          //�첽�������
	unsigned long  ulBusinessID;
	unsigned short usChannelNo;                         //ͨ�����
	char           szDecoderID[CUMW_DECODER_ID_LEN + 1];//������ID��20λ��������\0��
} IPI_STOP_BUSINESS_REQ;

//����/ֹͣ������Ƶ��Ϣ
typedef struct
{
	unsigned long  ulAsyncSeq;                          //�첽�������
	unsigned long  ulBusinessID;
	unsigned short usChannelNo;                         //ͨ�����
	char           szDecoderID[CUMW_DECODER_ID_LEN + 1];//������ID��20λ��������\0��
	unsigned char  cAudioCmd;                           //0x00 ֹͣ���� ��0x01��ʼ����
} IPI_AUDIO_CONTROL_REQ;

//����������Ϣ
typedef struct
{
	unsigned long  ulAsyncSeq;                          //�첽�������
	unsigned long  ulBusinessID;
	unsigned short usChannelNo;                         //ͨ�����
	char           szDecoderID[CUMW_DECODER_ID_LEN + 1];//������ID��20λ��������\0��
	unsigned char  cVolume;                             //������С��0~100��
} IPI_TUNEUP_VOLUME_REQ;

/*********************֪ͨ�ص���ض���***********************************/
//֪ͨ���Ͷ���
typedef enum
{
	CUMW_NOTIFY_TYPE_EVENT = 0x0001,                     //�¼�֪ͨ
	//��ӦpNotifyInfo�ṹ��Ϊ: CUMW_NOTIFY_EVENT
	CUMW_NOTIFY_TYPE_ASYNC_RET = 0x0002,                 //�첽����֪ͨ
	//��ӦpNotifyInfo�ṹ��Ϊ: CUMW_NOTIFY_ASYNC_RET
	CUMW_NOTIFY_TYPE_REMOTE_DECODER_REGISTER = 0x0003,   //Զ�̽�����ע��֪ͨ
	//��ӦpNotifyInfo�ṹ��Ϊ: CUMW_NOTIFY_REMOTE_DECODER_STATUS
	CUMW_NOTIFY_TYPE_REMOTE_DECODER_UNRIGISTER = 0x0004, //Զ�̽�����ע��
	//��ӦpNotifyInfo�ṹ��Ϊ: CUMW_NOTIFY_REMOTE_DECODER_OFF_LINE_INFO
	CUMW_NOTIFY_TYPE_REMOTE_DECODER_DISCONNECT = 0x0005, //Զ�̽���������
	//��ӦpNotifyInfo�ṹ��Ϊ: CUMW_NOTIFY_REMOTE_DECODER_OFF_LINE_INFO
	CUMW_NOTIFY_TYPE_INIT_DECODER = 0x0006,              //��ʼ��������
	//��ӦpNotifyInfo�ṹ��Ϊ: CUMW_NOTIFY_INIT_DECODER_INFO
	CUMW_NOTIFY_TYPE_START_DECODER = 0x0007,             //����Զ�̽�����
	//��ӦpNotifyInfo�ṹ��Ϊ: CUMW_NOTIFY_START_STOP_DECODER_INFO
	CUMW_NOTIFY_TYPE_DECODER_ERROR = 0x0008,             //������֪ͨ����
	//��ӦpNotifyInfo�ṹ��Ϊ: CUMW_NOTIFY_TYPE_DECODER_ERROR_INFO
	CUMW_NOTIFY_TYPE_AUDIO_CONTROL = 0x0009,             //����/ֹͣ������Ƶ��Ϣ֪ͨ
	//��ӦpNotifyInfo�ṹ��Ϊ: CUMW_NOTIFY_COM_RES_INFO
	CUMW_NOTIFY_TYPE_SET_VOLUME = 0x000A,                //����������Ϣ֪ͨ
	//��ӦpNotifyInfo�ṹ��Ϊ: CUMW_NOTIFY_COM_RES_INFO
	CUMW_NOTIFY_TYPE_STOP_DECODER = 0x000B,              //ֹͣ����
	//��ӦpNotifyInfo�ṹ��Ϊ: CUMW_NOTIFY_START_STOP_DECODER_INFO
	CUMW_NOTIFY_TYPE_START_AUTO_RESUME_INFO = 0x000C,              

	CUMW_NOTIFY_TYPE_AUTO_RESUME_RES = 0x000D,            
	//��ӦpNotifyInfo�ṹ��Ϊ: CUMW_NOTIFY_TYPE_DECODER_ERROR_INFO
	CUMW_NOTIFY_TYPE_RTSP_EXCEPTION = 0x000E,					//RTSP�쳣��
	//��ӦpNotifyInfo�ṹ��Ϊ: CUMW_NOTIFY_TYPE_DECODER_CAPABILITY_INFO
	CUMW_NOTIFY_TYPE_REMOTE_DECODER_CAPABILITY = 0x000F,//������������
	//��ӦpNotifyInfo�ṹ��Ϊ: 
	CUMW_NOTIFY_TYPE_SET_PORT_CONFIG_RET = 0x0010,       //���ý���������˿�����
	//��ӦpNotifyInfo�ṹ��Ϊ: 
	CUMW_NOTIFY_TYPE_GET_DEV_ABILITY_RET = 0x0011,       //��ȡ�豸����
	//��ӦpNotifyInfo�ṹ��Ϊ: 
	CUMW_NOTIFY_TYPE_SDK_LOGIN_DEC_SUC = 0x0012,         //sdk��ʽ���ӵĽ�������¼�ɹ�
	//��ӦpNotifyInfo�ṹ��Ϊ: 
	CUMW_NOTIFY_TYPE_REMOTE_DECODER_RESUMECONNECT =0x0013,
	
	CUMW_NOTIFY_TYPE_INTERFACE_MAX = 0x8000              //�ӿ����ֵ
} CUMW_NOTIFY_TYPE;

//����������
typedef enum
{
	CUMW_DECODER_TYPE_RDA = 0,			//RDA������
	CUMW_DECODER_TYPE_SDK = 1			//SDK������
} CUMW_DECODER_TYPE;

//�¼�֪ͨ
//��Ӧ��CUMW_NOTIFY_TYPEΪ: CUMW_NOTIFY_TYPE_EVENT
typedef struct
{
	unsigned long ulEventType;    //�¼����ͣ�ȡֵ��CUMW_NOTIFY_EVENT_TYPE
	unsigned long ulEventPara;    //�¼�����
} CUMW_NOTIFY_EVENT;

//�첽����֪ͨ
//��Ӧ��CUMW_NOTIFY_TYPEΪ: CUMW_NOTIFY_TYPE_ASYNC_RET
//TVWall->SDK
typedef struct
{
	unsigned long   ulAsyncType;        //�첽�ӿ����ͣ�ȡֵ��CUMW_ASYNC_TYPE
	unsigned long   ulAsyncSeq;         //�첽�������
	unsigned long   ulAsyncRetCode;     //�첽�����룬ȡֵ��CUMW_RET_CODE
	unsigned long   ulAsyncRetReason;   //������ϸԭ��û����ϸԭ�����0.������ο������ĵ�
	unsigned long   ulBusinessID;       //ҵ��ID���첽�ӿ�����Ϊ��ʼý��ҵ����첽�ӿ�ʱ����Ч
	void*           pAsyncRetInfo;      //�첽������Ϣ�������������ulAsyncType��ȡֵ��CUMW_ASYNC_TYPE
	unsigned long   ulAsyncRetInfoLen;  //pAsyncRetInfo���ݵ�ʵ�ʳ���
} CUMW_NOTIFY_ASYNC_RET;
//��Ӧ��CUMW_NOTIFY_TYPEΪ: CUMW_NOTIFY_TYPE_ASYNC_RET
//SDK->OCX
typedef enum
{
	CUMW_BREAKDOWN_REASON_UNKNOWN = 0,				//δ֪ԭ��
	CUMW_BREAKDOWN_REASON_DECODER_OFFLINE = 1,		//����������
	CUMW_BREAKDOWN_REASON_NO_VIDEO = 2				//��Ƶ�ж�
}CUMW_BREAKDOWN_REASON;

typedef struct
{
	IVS_INT32 iRetCode;                                 //�첽����������
	IVS_CHAR szCameraCode[IVS_DEV_CODE_LEN+1];          //����ͷ����
	IVS_CHAR szDecoderID[IVS_TVWALL_DECODER_CODE_LEN+1];//������ID
	IVS_UINT32 uiChannel;                               //������ͨ����
	CUMW_BREAKDOWN_REASON iReason;						//�쳣ԭ��
} CUMW_NOTIFY_ASYNC_RET_EX;

//������ͨ����Ϣ
typedef struct
{
	IVS_CHAR szDecoderID[IVS_TVWALL_DECODER_CODE_LEN + 1]; //������ID
	unsigned long ulChannelID;                             //������ͨ����
	char          szChannelName[CUMW_CHANNEL_NAME_LEN + 1];//������ͨ������
	unsigned char ucPortMode;							   //ͨ����Ӧ�˿�ģʽ��SDK�������иù��ܣ� 1-1���� 2-2���� 4-4���� 9-9���� 16-16����
	unsigned char ucChannelType;						   //ͨ������ 0-���� 1-���
	bool          bDecording;                              //true-���ڽ��� false-δ����
} CUMW_DECODER_CHANNEL_INFO;

//Զ�̽�����״̬֪ͨ
//��Ӧ��CUMW_NOTIFY_TYPEΪ: CUMW_NOTIFY_TYPE_REMOTE_DECODER_STATUS
typedef struct
{
	unsigned char			  ucDecoderType;								   //���������� 0-RDA������ 1-SDK������
	unsigned long             ulDecoderStatus;                                 //������״̬������μ�CUMW_DECODER_STATUS
	unsigned long             ulVideoPayloadTypeNum;                           //֧�ֵ���ƵPayloadType���������ֵ������16
	unsigned long             ulAudioPayloadTypeNum;                           //֧�ֵ���ƵPayloadType���������ֵ������16
	unsigned long             ulChannelNum;                                    //��������Чͨ����������󲻳���CUMW_DECODER_CHANNEL_MAX_NUM
	char                      szDecoderID[CUMW_DECODER_ID_LEN + 1];            //������ID
	char                      szDecoderName[CUMW_DECODER_NAME_LEN + 1];        //����������
	char				      szDecoderEncoding[CUMW_DECODER_ENCODING_LEN + 1];//�����������ʽ 
	char                      szDecoderIP[IVS_IP_LEN];                        //������IP
	unsigned char             ucVideoPayloadTypeArray[CUMW_PAY_LOAD_TYPE_NUM]; //֧�ֵ���ƵPayloadType�̶����顣Ԫ�ظ���Ϊ16��ʵ��Ԫ�ظ���ΪulVideoPayloadTypeNum
	unsigned char             ucAudioPayloadTypeArray[CUMW_PAY_LOAD_TYPE_NUM]; //֧�ֵ���ƵPayloadType�̶����顣Ԫ�ظ���Ϊ16��ʵ��Ԫ�ظ���ΪulAudioPayloadTypeNum
	CUMW_DECODER_CHANNEL_INFO stChannelInfoArray[CUMW_DECODER_CHANNEL_MAX_NUM];//������ͨ����Ϣ������Ԫ�ظ���ΪulChannelNum
} CUMW_NOTIFY_REMOTE_DECODER_STATUS;

typedef struct
{
    IVS_UINT32   uiTotal;                                   // �ܼ�¼��
    IVS_INDEX_RANGE stIndexRange;                           // ��ҳ��Ϣ  
    CUMW_NOTIFY_REMOTE_DECODER_STATUS stDecoderList[1];     // �������б�
} CUMW_NOTIFY_REMOTE_DECODER_STATUS_LIST;

//Զ�̽�����������ע��֪ͨ�ṹ��
//��Ӧ��CUMW_NOTIFY_TYPEΪ: CUMW_NOTIFY_TYPE_REMOTE_DECODER_DISCONNECT��CUMW_NOTIFY_TYPE_REMOTE_DECODER_UNRIGISTER
typedef struct
{
	char   szDecoderID[CUMW_DECODER_ID_LEN + 1]; //������ID
} CUMW_NOTIFY_REMOTE_DECODER_OFF_LINE_INFO;


//Զ�̽��������صĲ����������Ϣ
typedef struct
{
	unsigned long ulErrorCode;                                   //�����룬0����ɹ�
	char          szErrorDescription[CUMW_ERROR_DESCRIPTION_LEN];//�������Ӧ��������
}CUMW_ERROR_CODE_INFO;

//��������ʼ��֪ͨ��Ϣ�ṹ��
//��Ӧ��CUMW_NOTIFY_TYPEΪ: CUMW_NOTIFY_TYPE_INIT_DECODER
typedef struct
{
	unsigned long ulAsyncSeq;                          //�첽�������
	unsigned long ulBusinessID;                         
	char          szDecoderID[CUMW_DECODER_ID_LEN + 1];//������ID��20λ��������\0��

	CUMW_MEDIA_NET_INFO  stMediaNetInfo;               //ý���������Ϣ
	CUMW_ERROR_CODE_INFO stErrorCode;                  //������Ϣ
} CUMW_NOTIFY_INIT_DECODER_INFO;


//����Զ�̽�������ֹͣԶ�̽�����֪ͨ��Ϣ�ṹ��
//��Ӧ��CUMW_NOTIFY_TYPEΪ: CUMW_NOTIFY_TYPE_START_DECODER��CUMW_NOTIFY_TYPE_STOP_DECODER
typedef struct
{
	unsigned long ulAsyncSeq;                          //�첽�������
	unsigned long ulBusinessID;
	char          szDecoderID[CUMW_DECODER_ID_LEN + 1];//������ID��20λ��������\0��

	CUMW_ERROR_CODE_INFO stErrorCode;                  //������Ϣ
}CUMW_NOTIFY_START_STOP_DECODER_INFO;

//������֪ͨ�������Ϣ�ṹ
//��Ӧ��CUMW_NOTIFY_TYPEΪ: CUMW_NOTIFY_TYPE_DECODER_ERROR
typedef struct
{
	unsigned short usChannelNo;                         //ͨ�����
	char           szDecoderID[CUMW_DECODER_ID_LEN + 1];//������ID��20λ��������\0��

	CUMW_ERROR_CODE_INFO stErrorCode;                   //������Ϣ
} CUMW_NOTIFY_TYPE_DECODER_ERROR_INFO;


//ͨ��֪ͨ��Ϣ�ṹ��
//��Ӧ��CUMW_NOTIFY_TYPEΪ: CUMW_NOTIFY_TYPE_SET_VOLUME��CUMW_NOTIFY_TYPE_AUDIO_CONTROL
typedef struct
{
	unsigned long ulAsyncSeq;                          //�첽�������
	unsigned long ulBusinessID;
	char          szDecoderID[CUMW_DECODER_ID_LEN + 1];//������ID��20λ��������\0��

	CUMW_ERROR_CODE_INFO stErrorCode;                  //������Ϣ
}CUMW_NOTIFY_COM_RES_INFO;


//֪ͨ�ص�������֪ͨ��Ϣ�ṹ��
typedef struct
{
	unsigned long   ulNotifyType;       //֪ͨ���ͣ�ȡֵ��CUMW_NOTIFY_TYPE
	void*           pNotifyInfo;        //֪ͨ��Ϣ�������������ulNotifyType��ȡֵ��CUMW_NOTIFY_TYPE
	unsigned long   ulNotifyInfoLen;    //pNotifyInfo���ݵ�ʵ�ʳ��ȣ�������ȷ
} CUMW_NOTIFY_INFO;

//����������֪ͨ��Ϣ�ṹ��
//��Ӧ��CUMW_NOTIFY_TYPEΪ: CUMW_NOTIFY_TYPE_REMOTE_DECODER_CAPABILITY
typedef struct
{
	char szDecoderID[CUMW_DECODER_ID_LEN + 1];		//������ID
	unsigned long ulSupportSwitch;											//֧���޷��л���1��ʾ֧�֣�0��ʾ��֧��
	unsigned long ulReserve1;													//�����ֶ�1
	unsigned long ulReserve2;													//�����ֶ�2
}CUMW_NOTIFY_TYPE_DECODER_CAPABILITY_INFO;


//��������������
typedef enum
{
	CUMW_DECODER_CONNECT_NONE = 0,
	CUMW_DECODER_CONNECT_HIK,		//����������
	CUMW_DECODER_CONNECT_HW,		//��Ϊ������
	CUMW_DECODER_CONNECT_MAX
} CUMW_DECODER_CONNECT_TYPE;

// SDK��ʽ���Ӻ����������ṹ��
typedef struct
{
	IVS_CHAR cDecoderID[CUMW_DECODER_ID_LEN+1];					//������ID��SDK����
	IVS_CHAR cDecoderName[CUMW_DECODER_NAME_LEN+1];	//��������
	IVS_CHAR cDevIP[IVS_IP_LEN + 1];			//������IP
	IVS_INT32 iPort;			//��������¼�˿�
	IVS_CHAR cUser[IVS_NAME_LEN+1];		//�û���
	IVS_CHAR cPassword[IVS_PWD_LEN + 1];		//����
	IVS_BOOL bLoginSuc;                   // 0-δ��¼��1-�ѵ�¼  
	IVS_INT32 iChannelNum;			//������ͨ����Ŀ
	CUMW_DECODER_CHANNEL_INFO stChannels[DECODER_MAX_CHANNEL_NUM];		//������ͨ����Ϣ
}DECODER_DEV;


//ͨ������Ϣ�ṹ�����Ͷ���
typedef struct
{
	unsigned short usChannelNo;				//ͨ����
	char szChannelName[CUMW_DECODER_NAME_LEN + 1];		//ͨ��������
} CHANNEL_INFO;


typedef struct
{
	unsigned short usChannelNum;			//ͨ������Ŀ
	CHANNEL_INFO stChannelInfo[CUMW_DECODER_CHANNEL_MAX_NUM];			//ͨ������Ϣ
} CHANNELS_INFO;

//һ������˿ڵ�������Ϣ
typedef struct
{
	unsigned short         usPortEnable;     //�˿��Ƿ�ʹ��
	unsigned short         usResolution;     //�˿�����ֱ��� 
	unsigned short         usFrameRate;      //�˿�ˢ���� 
	unsigned short         usChannelMode;    //ͨ��ģʽ1��4��9��16 
	CHANNELS_INFO stChannelsInfo;   //�˿ڰ󶨵�ͨ����Ϣ
} PORT_CONFIG;


//�������˿ڵ�������Ϣ
typedef struct
{
	unsigned short   usPortNum;		//�˿ں�
	PORT_CONFIG  stPortConfig[CUMW_MAX_PORT_ONE_TYPE_NUM];		//�˿�������Ϣ
} PORTS_CONFIG;

typedef struct
{
	unsigned long ulVideoPayloadTypeNum;                           //֧�ֵ���ƵPayloadType���������ֵ������16
	unsigned long ulAudioPayloadTypeNum;								 //֧�ֵ���ƵPayloadType���������ֵ������16

	unsigned char ucVideoPayloadTypeArray[CUMW_PAY_LOAD_TYPE_NUM]; //֧�ֵ���ƵPayloadType�̶����顣Ԫ�ظ���Ϊ16��ʵ��Ԫ�ظ���ΪulVideoPayloadTypeNum
	unsigned char ucAudioPayloadTypeArray[CUMW_PAY_LOAD_TYPE_NUM]; //֧�ֵ���ƵPayloadType�̶����顣Ԫ�ظ���Ϊ16��ʵ��Ԫ�ظ���ΪulAudioPayloadTypeNum

	PORTS_CONFIG  stBNCPortCfgs;  //������BNC�˿ڵ����� 
	PORTS_CONFIG  stVGAPortCfgs;  //������VGA�˿ڵ�����
	PORTS_CONFIG  stHDMIPortCfgs; //������HDMI�˿ڵ�����
	PORTS_CONFIG  stDVIPortCfgs;  //������DVI�˿ڵ�����
} PORTS_INFO;

//���ö˿�����
typedef struct
{
	unsigned long  ulAsyncSeq;                          //�첽�������
	unsigned long  ulBusinessID;
	char           szDecoderID[CUMW_DECODER_ID_LEN + 1];//������ID��20λ��������\0��
	PORTS_INFO    stPortsInfo;		//�˿�������Ϣ
} IPI_SET_PORTS_CONFIG_REQ;

typedef struct
{
	unsigned long  usChannelNo;                         //ͨ�����
	char           szDecoderID[CUMW_DECODER_ID_LEN + 1];//������ID��20λ��������\0��
	CUMW_ERROR_CODE_INFO stErrorCode;                   //������Ϣ
} CUMW_NOTIFY_TYPE_DECODER_ERROR_INFO_EX;


// ��½SDK��������Ϣ
typedef struct
{
	IVS_CHAR cUserName[IVS_NAME_LEN]; // �û���
	IVS_CHAR pPWD[IVS_PWD_LEN]; // ����
	IVS_IP stIP; // ��¼������IP
	IVS_UINT32 uiPort; // ��¼�������˿�		//�����������˿�8000
	IVS_CHAR cDecoderName[CUMW_DECODER_NAME_LEN];		//��������
	IVS_CHAR cReserve[256]; //�����ֶ�
}SDK_DECODER_LOGIN_INFO;



//֪ͨ�ص���������
typedef IVS_INT32 (__SDK_CALL * PCUMW_CALLBACK_NOTIFY)(CUMW_NOTIFY_INFO* pstNotifyInfo,void* pUserData);

#ifdef __cplusplus
extern "C"
{
#endif
	/*************************************************************************
	* name				: IVS_SDK_InitTVWall
	* description	: ��ʼ������ǽ
	* input				: iSessionID   ��¼�ɹ���ĻỰID
	*								pFunNotifyCallBack �ص�������ַ, 
	*								pUserData �ص��������ݣ�����ΪNULL
	*								enDecoderType ��ʼ���Ľ���������
	* output     : NA
	* return     : �ɹ�����0��ʧ�ܷ��ش�����
	* author     ��gaoshuming g00209332
	* remark     : NA
	* history    : 2012-12-20 17.28[add]
	*************************************************************************/
	IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_InitTVWall(IVS_INT32 iSessionID, PCUMW_CALLBACK_NOTIFY pFunNotifyCallBack, 
														void* pUserData);

	/*************************************************************************
	* name       : IVS_SDK_CleanupTVWall
	* description: �ͷŵ���ǽ
	* input      : iSessionID   ��¼�ɹ���ĻỰID
	* output     : NA
	* return     : �ɹ�����0��ʧ�ܷ��ش�����
	* author     ��gaoshuming g00209332
	* remark     : NA
	* history    : 2012-12-20 17.28[add]
	*************************************************************************/
	IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_CleanupTVWall(IVS_INT32 iSessionID);

	/**********************************************************************
	* name			: IVS_SDK_GetDecoderList 
	* description	: ��ȡ�������б�
	* input			: iSessionID   ��¼�ɹ���ĻỰID
	*				  pTVWallParam ����ǽ����������
	* output     	: NA
	* return     	: �ɹ�-0 ʧ��-������ 
	* remark     	: NA   
	*********************************************************************/
	IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_GetDecoderList(IVS_INT32 iSessionID,
															const IVS_INDEX_RANGE* pIndexRange,
															CUMW_NOTIFY_REMOTE_DECODER_STATUS_LIST* pDecoderList,
															IVS_UINT32 uiBufferSize);
	/**********************************************************************
	* name			: IVS_SDK_StartRealPlayTVWall
	* description	: ��������ǽʵʱ���
	* input			: iSessionID   ��¼�ɹ���ĻỰID
	*				  pCameraCode ���������
	*				  pRealplayParam ʵʱ�������XML
	*				  pTVWallParam ����ǽ����������
	* output     	: NA
	* return     	: �ɹ�-0 ʧ��-������ 
	* remark     	: NA   
	*********************************************************************/
	IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_StartRealPlayTVWall(IVS_INT32 iSessionID,
																const IVS_CHAR* pCameraCode,
																const IVS_REALPLAY_PARAM* pRealplayParam,
																const IVS_TVWALL_PARAM* pTVWallParam);

	/**********************************************************************
	* name			: IVS_SDK_StopRealPlayTVWall
	* description	: ֹͣ����ǽʵʱ���
	* input			: pTVWallParam ����ǽ����������
	* output     	: NA
	* return     	: �ɹ�-0 ʧ��-������ 
	* remark     	: NA   
	*********************************************************************/
	IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_StopRealPlayTVWall(IVS_INT32 iSessionID,
																const IVS_TVWALL_PARAM* pTVWallParam);
	/**********************************************************************
	* name			: IVS_SDK_StartPlatformPlayBackTVWall
	* description	: ��ʼ����ǽƽ̨¼��ط�
    * input			: iSessionID   ��¼�ɹ���ĻỰID
	*				  pCameraCode ���������
    *				  pPlaybackParam ¼��طŲ���XML
    *				  pTVWallParam ����ǽ����������
	* output     	: NA
	* return     	: �ɹ�-0 ʧ��-������ 
	* remark     	: NA   
	*********************************************************************/
    IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_StartPlatformPlayBackTVWall (IVS_INT32 iSessionID,
                                                                            const IVS_CHAR* pCameraCode,
                                                                            const IVS_PLAYBACK_PARAM* pPlaybackParam,
                                                                            const IVS_TVWALL_PARAM* pTVWallParam);
	/**********************************************************************
	* name			: IVS_SDK_StopPlatformPlayBackTVWall
	* description	: ֹͣ����ǽƽ̨¼��ط�
	* input			: iSessionID   ��¼�ɹ���ĻỰID
	*				  pTVWallParam ����ǽ����������
	* output     	: NA
	* return     	: �ɹ�-0 ʧ��-������ 
	* remark     	: NA   
	*********************************************************************/
	IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_StopPlatformPlayBackTVWall(IVS_INT32 iSessionID,
                                                                        const IVS_TVWALL_PARAM* pTVWallParam);
	/**********************************************************************
	* name			: IVS_SDK_StartPUPlayBackTVWall
	* description	: ��ʼ����ǽǰ��¼��ط�
    * input			: iSessionID   ��¼�ɹ���ĻỰID
	*				  pCameraCode ���������
    *				  pPlaybackParam ¼��طŲ���XML
    *				  pTVWallParam ����ǽ����������
	* output     	: NA
	* return     	: �ɹ�-0 ʧ��-������ 
	* remark     	: NA   
	*********************************************************************/
    IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_StartPUPlayBackTVWall (IVS_INT32 iSessionID,
                                                                            const IVS_CHAR* pCameraCode,
                                                                            const IVS_PLAYBACK_PARAM* pPlaybackParam,
                                                                            const IVS_TVWALL_PARAM* pTVWallParam);
	/**********************************************************************
	* name			: IVS_SDK_StopPUPlayBackTVWall
	* description	: ֹͣ����ǽǰ��¼��ط�
	* input			: iSessionID   ��¼�ɹ���ĻỰID
	*				  pTVWallParam ����ǽ����������
	* output     	: NA
	* return     	: �ɹ�-0 ʧ��-������ 
	* remark     	: NA   
	*********************************************************************/
	IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_StopPUPlayBackTVWall(IVS_INT32 iSessionID,
                                                                        const IVS_TVWALL_PARAM* pTVWallParam);
	/**********************************************************************
	* name			: IVS_SDK_StartBackupPlayBackTVWall
	* description	: ��ʼ����ǽ����¼��ط�
    * input			: iSessionID   ��¼�ɹ���ĻỰID
	*				  pDomainCode �����
	*				  pNVRCode    NVR����
	*				  pCameraCode ���������
    *				  pPlaybackParam ¼��طŲ���XML
    *				  pTVWallParam ����ǽ����������
	* output     	: NA
	* return     	: �ɹ�-0 ʧ��-������ 
	* remark     	: NA   
	*********************************************************************/
    IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_StartBackupPlayBackTVWall (IVS_INT32 iSessionID,
																			const IVS_CHAR* pDomainCode,
																			const IVS_CHAR* pNVRCode,
                                                                            const IVS_CHAR* pCameraCode,
                                                                            const IVS_PLAYBACK_PARAM* pPlaybackParam,
                                                                            const IVS_TVWALL_PARAM* pTVWallParam);
	/**********************************************************************
	* name			: IVS_SDK_StopBackupPlayBackTVWall
	* description	: ֹͣ����ǽ����¼��ط�
	* input			: iSessionID   ��¼�ɹ���ĻỰID
	*				  pTVWallParam ����ǽ����������
	* output     	: NA
	* return     	: �ɹ�-0 ʧ��-������ 
	* remark     	: NA   
	*********************************************************************/
	IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_StopBackupPlayBackTVWall(IVS_INT32 iSessionID,
                                                                        const IVS_TVWALL_PARAM* pTVWallParam);
	/**********************************************************************
	* name			: IVS_SDK_PlayBackPauseTVWall
	* description	: ��ͣ����ǽ¼��ط�
	* input			: iSessionID   ��¼�ɹ���ĻỰID
	*				  pTVWallParam ����ǽ����������
	* output     	: NA
	* return     	: �ɹ�-0 ʧ��-������ 
	* remark     	: NA   
	*********************************************************************/
	IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_PlayBackPauseTVWall(IVS_INT32 iSessionID,
                                                                        const IVS_TVWALL_PARAM* pTVWallParam);
	/**********************************************************************
	* name			: IVS_SDK_PlayBackResumeTVWall
	* description	: �ָ�����ǽǰ��¼��ط�
	* input			: iSessionID   ��¼�ɹ���ĻỰID
	*				  pTVWallParam ����ǽ����������
	* output     	: NA
	* return     	: �ɹ�-0 ʧ��-������ 
	* remark     	: NA   
	*********************************************************************/
	IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_PlayBackResumeTVWall(IVS_INT32 iSessionID,
                                                                        const IVS_TVWALL_PARAM* pTVWallParam);
	/**********************************************************************
	* name			: IVS_SDK_PlaybackFrameStepForwardTVWall
	* description	: �ط�ʱ��֡���
	* input			: iSessionID   ��¼�ɹ���ĻỰID
	*				  pTVWallParam ����ǽ����������
	* output     	: NA
	* return     	: �ɹ�-0 ʧ��-������ 
	* remark     	: NA   
	*********************************************************************/
	IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_PlaybackFrameStepForwardTVWall(IVS_INT32 iSessionID,
                                                                        const IVS_TVWALL_PARAM* pTVWallParam);

	/*************************************************************************
	* name			:	IVS_SDK_SwitchRealPlayTVWall
	* description	:	����ǽ�޷�����
	* input			:	iSessionID	��¼�ɹ���ĻỰID
	* input			:	pCameraCode	���������
	* input			:	pRealplayParam	ʵʱ�������
	* input			:	pTVWallParam	����ǽ����������
	* output			:	NA
	* return			:	�ɹ�����0��ʧ�ܷ��ش�����
	* remark		:	NA
	*************************************************************************/
	IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_SwitchRealPlayTVWall(IVS_INT32 iSessionID, 
		const IVS_CHAR* pCameraCode,  
		const IVS_REALPLAY_PARAM* pRealplayParam,  
		const IVS_TVWALL_PARAM* pTVWallParam);


	/*************************************************************************
	* name				: IVS_SDK_AddDecoder
	* description	: ��¼������
	* input				: iSessionID     ��¼�ɹ���ĻỰID
									emConnectType ����������
	*								pSDKDecoderLoginInfo ��������¼��Ϣ
	* output			: NA
	* return			: �ɹ�����0��ʧ�ܷ��ش�����
	* remark			: NA
	*************************************************************************/
	IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_AddDecoder(IVS_INT32 iSessionID, CUMW_DECODER_CONNECT_TYPE emConnectType, const SDK_DECODER_LOGIN_INFO *pSDKDecoderLoginInfo);

	/*************************************************************************
	* name				: IVS_SDK_DelDecoder
	* description	: �ǳ�������
	* input				: iSessionID     ��¼�ɹ���ĻỰID
									emConnectType ����������
									pDecoderID ������ID
	* output			: NA
	* return			: �ɹ�����0��ʧ�ܷ��ش�����
	* remark			: NA
	*************************************************************************/
	IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_DelDecoder(IVS_INT32 iSessionID, CUMW_DECODER_CONNECT_TYPE emConnectType, const IVS_CHAR* pDecoderID);

#ifdef __cplusplus
}
#endif //__cplusplus

#endif //__IVS_SDK_TVWALL_H__
