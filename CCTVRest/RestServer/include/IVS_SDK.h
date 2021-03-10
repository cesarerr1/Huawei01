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
filename	: 	IVSSDK.cpp
author		:	z00201790
created		:	2012/10/23	
description	:	���� DLL Ӧ�ó���ĵ�������;
copyright	:	Copyright (C) 2011-2015
history		:	2012/10/23 ��ʼ�汾;
*********************************************************************/

#ifndef IVS_SDK_H
#define IVS_SDK_H

#include "hwsdk.h"
#include "ivs_error.h"

#ifdef WIN32
#ifdef  IVS_SDK_EXPORTS
#define IVS_SDK_API __declspec(dllexport)
#else
#define IVS_SDK_API __declspec(dllimport)
#endif
#else
#define IVS_SDK_API __attribute__((visibility("default")))
#endif

#ifdef WIN32
#define __SDK_CALL __stdcall
#else
#define __SDK_CALL
#endif

#ifndef VOID
#define VOID void
#endif
#ifdef __cplusplus
extern "C"
{
#endif

	/**************************************************************************
	* name			: IVS_SDK_Init
	* description	: ��ʼ��SDK
	* input			: NA
	* output		: NA
	* return		: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
	* remark		: NA
	**************************************************************************/
	IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_Init();

	/**************************************************************************
	* name			: IVS_SDK_Cleanup()
	* description	: �ͷ�SDK
	* input			: NA
	* output		: NA
	* return		: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
	* remark		: NA
	**************************************************************************/
	IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_Cleanup();

	/**************************************************************************
	* name			: IVS_SDK_GetVersion()
	* description	: ��ȡSDK�汾�ţ���ǰ�汾��Ϊ2.2.0.1
	* input			: NA
	* output		: NA
	* return		: �ɹ�����SDK�汾�ţ���16λ��25λ~32λ��ʾ���汾�ţ�17~24λ��ʾ�Ӱ汾�š���16λ��9λ~16λ��ʾ�����汾�ţ�1~8λ��ʾԤ���汾��;
	* remark		: ����SDK�汾����16���Ʊ�ʾ������2.2.0.1����ֵΪ0x02020001
	**************************************************************************/
	IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_GetVersion();

	/**************************************************************************
	* name			: IVS_SDK_SetEventCallBack()
	* description	: �����¼��ص�����
	* input			: iSessionID        ��¼�ɹ���ĻỰID
	*					  fEventCallBack    �û����õ��¼��ص�������Ϊ�ձ�ʾȡ�����õĻص�����;
	*					  pUserData		 �û����ݣ��Զ��壬��Ӧ�ص�����������ʱ���ظò���
	* output		: NA
	* return		: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
	* remark		: NA
	**************************************************************************/
	IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_SetEventCallBack(IVS_INT32 iSessionID, EventCallBack fEventCallBack = NULL, void *pUserData = NULL);

	/**************************************************************************
	* name			: IVS_SDK_Login
	* description	: �û���¼
	* input			: pLoginReqInfo ��¼��Ϣ
    * output		: iSessionID �ỰID��SessionID��SDK�ڲ�������0-127����������Ϊ�����ӿڵ���Σ�������ʶ�û���һ�ε�¼�����֧�ֵĵ�¼��Ϊ128	
	* return		: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
	* remark		: NA
	**************************************************************************/
    IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_Login(IVS_LOGIN_INFO* pLoginReqInfo, IVS_INT32* iSessionID);
	
	/**************************************************************************
	* name       : IVS_SDK_LoginByTicket
	* description: �û������¼;
	* input      : IVS_LOGIN_INFO_EX ��½��νṹ��;
					(cTicketID		�û���Ʊ�ݣ����û�Ψһ��Ӧ;
					stIP			������IP��ַ;
					uiPort			�������˿�;
					uiLoginType		��½����: 0 �C���������֤;
					cDomainName		��¼������Ϣ;
					cMachineName	�ͻ��˵�¼�Ļ�����;
					uiClientType	�ͻ������ͣ��ο� IVS_CLIENT_TYPE 0-PC�ͻ���, 1-web�����, 
						2-�ƶ��ͻ���, 3-PC�ͻ����ӽ��̣�4-����ǽ����;);
    * output     : pSessionId  ����sessionId SessionID��SDK�ڲ�����������0��������
                        ��Ϊ�����ӿڵ���Σ��������ַ��ʵķ�����������¼128��������;
	* return     : �ɹ�����0��ʧ�ܷ��ش�����;
	* remark     : NA
	**************************************************************************/
    IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_LoginByTicket(IVS_LOGIN_INFO_EX* pLoginReqInfoEx, IVS_INT32* pSessionId);
	
    /**************************************************************************
	* name			: IVS_SDK_WinUserLogin
	* description	: �û���¼
	* input			: pLoginReqInfo ��¼��Ϣ
    * output		: iSessionID �ỰID��SessionID��SDK�ڲ�������0-127����������Ϊ�����ӿڵ���Σ�������ʶ�û���һ�ε�¼�����֧�ֵĵ�¼��Ϊ128
	* return		: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
	* remark		: NA
	**************************************************************************/
    IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_WinUserLogin(IVS_LOGIN_INFO* pLoginReqInfo, IVS_INT32* iSessionID);

	/**************************************************************************
	* name			: IVS_SDK_Logout
	* description	: �û�ע��
	* input			: iSessionID ��¼�ɹ���ĻỰID
	* output		: NA
	* return		: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
	* remark		: NA
	**************************************************************************/
	IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_Logout(IVS_INT32 iSessionID);

	/**************************************************************************
	* name			: IVS_SDK_ChangePWD
	* description	: �޸�����
	* input			: iSessionID ��¼�ɹ���ĻỰID
						  pOldPWD    ������
						  pNewPWD    ������
	* output		: NA
	* return		: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
	* remark		: NA
	**************************************************************************/
    IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_ChangePWD(IVS_INT32 iSessionID, const IVS_CHAR* pOldPWD, const IVS_CHAR* pNewPWD);

	/******************************************************************
    function		: IVS_SDK_ResetPWD
    description	: ��������
    input			: iSessionID      ��¼�ɹ���ĻỰID
					  pDomainCode    �����
					  iUserID     �û�ID
					  pNewPWD      �û�������
    return		: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
    *******************************************************************/
    IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_ResetPWD(IVS_INT32 iSessionID, const IVS_CHAR* pDomainCode, const IVS_UINT32 uiUserID, const IVS_CHAR* pNewPWD);

    /******************************************************************
    function		: IVS_SDK_CheckPWDByRole
    description	: У�������Ƿ������˺Ź���
    input			: iSessionID     ��¼�ɹ���ĻỰID
					  pDomainCode    �����
					  uiRoleID   ��ɫID
					  pLoginName  �û���¼��
					  pPWD     �û����õ�����
    return		: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
    *******************************************************************/
    IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_CheckPWDByRole(IVS_INT32 iSessionID, const IVS_CHAR* pDomainCode, const IVS_UINT32 uiRoleID, const IVS_CHAR* pLoginName, const IVS_CHAR* pPWD);

    /******************************************************************
    function		: IVS_SDK_GetAutoCreatePWD
    description	: ���ݽ�ɫ��ȡ�����˺Ź��������
    input			: iSessionID    ��¼�ɹ���ĻỰID
					  pDomainCode   �����
					  uiRoleID    ��ɫID
					  pLoginName    �û���¼��
					  uiPWDLen     ���볤��
    output		: pNewPWD     �����ַ���
    return		: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
    *******************************************************************/
    IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_GetAutoCreatePWD(IVS_INT32 iSessionID, const IVS_CHAR* pDomainCode, IVS_UINT32 uiRoleID, const IVS_CHAR* pLoginName, IVS_CHAR* pNewPWD, IVS_UINT32 uiPWDLen);

    /******************************************************************
    function		: IVS_SDK_GetPWDStrength
    description	: ��ȡ����ǿ��
    input			: pPWD  ����
    output		: uiPWDStrength  ����ǿ��
    return		: ��������ǿ�ȣ�ֵ�ο� IVS_KEY_RELIABILITY��
    *******************************************************************/
    IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_GetPWDStrength(const IVS_CHAR* pPWD, IVS_UINT32* uiPWDStrength);

	/******************************************************************
    function		: IVS_SDK_GetPWDExpireInfo
    description	: ��ȡ���������Ϣ
	input			: iSessionID    ��¼�ɹ���ĻỰID
    output		: pPWDExpireInfo    ���������Ϣ
    return		: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
    *******************************************************************/
    IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_GetPWDExpireInfo(IVS_INT32 iSessionID, IVS_PWD_EXPIRE_INFO* pPWDExpireInfo);

	/**************************************************************************
	* name			: IVS_SDK_GetUserID
	* description	: ��ȡ��½�û����û�ID
	* input			: iSessionID  ��¼�ɹ���ĻỰID
	* output		: puiUserID  �û�ID
	* return		: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
	* remark		: NA
	**************************************************************************/
    IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_GetUserID(IVS_INT32 iSessionID, IVS_UINT32* puiUserID);

	/*************************************************************************
	* name			: IVS_SDK_AddRecordPlan
	* description	: ����ƽ̨/ǰ��¼��ƻ�
	* input			: iSessionID         ��¼�ɹ���ĻỰID
						  uiDeviceNum        ���������
						  pDeviceList        ����������б�
						  pRecordPlan        ¼��ƻ�
						  uiResultBufferSize �����С
	* output		: pResultList        ¼��ƻ��������
	* return		: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
	* remark		: NA
	*************************************************************************/
	IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_AddRecordPlan(IVS_INT32 iSessionID,IVS_UINT32 uiDeviceNum,
		const IVS_DEVICE_CODE* pDeviceList,const IVS_RECORD_PLAN* pRecordPlan,IVS_RESULT_LIST* pResultList,IVS_UINT32 uiResultBufferSize);

	/*************************************************************************
	* name			: IVS_SDK_ModifyRecordPlan
	* description	: �޸�ƽ̨/ǰ��¼��ƻ�
	* input			: iSessionID         ��¼�ɹ���ĻỰID
						  uiDeviceNum        ���������
						  pDeviceList        ����������б�
						  pRecordPlan        ¼��ƻ�
						  uiResultBufferSize �����С
	* output		: pResultList        ¼��ƻ��޸Ľ��
	* return		: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
	* remark		: NA
	*************************************************************************/
	IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_ModifyRecordPlan(IVS_INT32 iSessionID,IVS_UINT32 uiDeviceNum,const IVS_DEVICE_CODE* pDeviceList,
		const IVS_RECORD_PLAN* pRecordPlan,IVS_RESULT_LIST* pResultList,IVS_UINT32 uiResultBufferSize);

	/*************************************************************************
	* name			: IVS_SDK_DeleteRecordPlan
	* description	: ɾ��ƽ̨/ǰ��¼��ƻ�
	* input			: iSessionID         ��¼�ɹ���ĻỰID
						  uiDeviceNum        ���������
						  pDeviceList        ����������б�
						  uiRecordMethod     ¼��ʽ��0-ƽ̨¼�� 1-ǰ��¼��
						  uiResultBufferSize �����С
	* output		: pResultList        ¼��ƻ�ɾ�����
	* return		: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
	* remark		: NA
	*************************************************************************/
	IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_DeleteRecordPlan(IVS_INT32 iSessionID,IVS_UINT32 uiDeviceNum,const IVS_DEVICE_CODE* pDeviceList,
		IVS_UINT32 uiRecordMethod,IVS_RESULT_LIST* pResultList,IVS_UINT32 uiResultBufferSize);

	/*************************************************************************
	* name			: IVS_SDK_GetRecordPlan
	* description	: ��ѯƽ̨/ǰ��¼��ƻ�
	* input			: iSessionID         ��¼�ɹ���ĻỰID
						  pCameraCode        ���������
						  uiRecordMethod     ¼��ʽ��0-ƽ̨¼�� 1-ǰ��¼��
	* output		: pRecordPlan        ¼��ƻ�
	* return		: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
	* remark		: NA
	*************************************************************************/
	IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_GetRecordPlan(IVS_INT32 iSessionID,const char* pCameraCode,IVS_UINT32 uiRecordMethod,IVS_RECORD_PLAN *pRecordPlan);

	/*************************************************************************
	* name			: IVS_SDK_AddBookmark
	* description	: ����¼����ǩ
	* input			: iSessionID    ��¼�ɹ���ĻỰID
						  pCameraCode   ���������
						  pNVRCode      NVR����
						  pBookmarkName ��ǩ����
						  pBookmarkTime ��ǩʱ��
	* output		: uiBookmarkID  ��ǩID
	* return		: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
	* remark		: NA
	*************************************************************************/
	IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_AddBookmark(IVS_INT32 iSessionID,const IVS_CHAR* pCameraCode,const IVS_CHAR* pNVRCode,
		const IVS_CHAR* pBookmarkName,const IVS_CHAR* pBookmarkTime,IVS_UINT32* uiBookmarkID);

	/*************************************************************************
	* name			: IVS_SDK_ModifyBookmark
	* description	: �޸�¼����ǩ
	* input			: iSessionID    ��¼�ɹ���ĻỰID
						  pNVRCode      NVR����
						  pCameraCode   ���������
						  uiBookmarkID  ��ǩID
						  pBookmarkName ����ǩ����
	* output		: NA
	* return		: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
	* remark		: NA
	*************************************************************************/
	IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_ModifyBookmark(IVS_INT32 iSessionID,const IVS_CHAR* pNVRCode,const IVS_CHAR* pCameraCode,IVS_UINT32 uiBookmarkID,const IVS_CHAR* pNewBookmarkName);
	/*************************************************************************
	* name			: IVS_SDK_DeleteBookmark
	* description	: ɾ��¼����ǩ
	* input			: iSessionID    ��¼�ɹ���ĻỰID
						  pNVRCode      NVR����
						  pCameraCode   ���������
						  uiBookmarkID  ��ǩID
	* output		: NA
	* return		: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
	* remark		: NA
	*************************************************************************/
	IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_DeleteBookmark(IVS_INT32 iSessionID,const IVS_CHAR* pNVRCode,const IVS_CHAR* pCameraCode,IVS_UINT32 uiBookmarkID);

	/*************************************************************************
	* name			: IVS_SDK_GetBookmarkList
	* description	: ��ѯ¼����ǩ�б�
	* input			: iSessionID    ��¼�ɹ���ĻỰID
						  pUnifiedQuery ��ѯ����
						  uiBufSize     �����С
	* output		: pBookmarkList ��ǩ��ѯ����б�
	* return		: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
	* remark		: NA
	*************************************************************************/
	IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_GetBookmarkList(IVS_INT32 iSessionID, const IVS_QUERY_UNIFIED_FORMAT* pUnifiedQuery, 
		IVS_RECORD_BOOKMARK_INFO_LIST* pBookmarkList,IVS_UINT32 uiBufSize);

	/*************************************************************************
	* name			: IVS_SDK_QueryRecordList
	* description	: ��ѯ¼���б�
	* input			: iSessionID      ��¼�ɹ���ĻỰID
						  pUnifiedQuery   ��ѯ����
						  uiBufferSize    �����С
	* output		: pRecordInfoList ¼���ѯ����б�
	* return		: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
	* remark		: NA
	*************************************************************************/
	IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_QueryRecordList(IVS_INT32 iSessionID, const IVS_QUERY_UNIFIED_FORMAT* pUnifiedQuery, 
		IVS_RECORD_INFO_LIST* pRecordInfoList,IVS_UINT32 uiBufferSize);

	/*************************************************************************
	* name			: IVS_SDK_GetRecordPolicyByTime
	* description	: ��ѯ¼��ʱ�����
	* input			: iSessionID    ��¼�ɹ���ĻỰID
						  pCameraCode   ���������
	* output		: pRecordPolicy ¼�����
	* return		: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
	* remark		: NA
	*************************************************************************/
	IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_GetRecordPolicyByTime(IVS_INT32 iSessionID,const IVS_CHAR* pCameraCode,IVS_RECORD_POLICY_TIME* pRecordPolicy);

	/*************************************************************************
	* name         : IVS_SDK_SetRecordPolicyByTime
	* description : ����¼��ʱ�����
	* input			: iSessionID    ��¼�ɹ���ĻỰID
						  pCameraCode   ���������
						  pRecordPolicy ¼�����
	* output		: NA
	* return		: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
	* remark		: NA
	*************************************************************************/
	IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_SetRecordPolicyByTime(IVS_INT32 iSessionID,const IVS_CHAR* pCameraCode,const IVS_RECORD_POLICY_TIME* pRecordPolicy);

	/*************************************************************************
	* name			: IVS_SDK_GetRecordList
	* description	: ��ѯ¼���б�
	* input			: iSessionID    ��¼�ɹ���ĻỰID
						  pCameraCode   �����ID
						  iRecordMethod ¼��ʽ��0-ƽ̨¼�� 1-ǰ��¼�� 2-���ݷ�����
						  pTimeSpan     ��ѯʱ���
						  pIndexRange   ��ҳ��Ϣ
						  iBufSize      �����С
	* output		: pRecordList   ����¼���б�
	* return		: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
	* remark		: NA
	*************************************************************************/
	IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_GetRecordList(IVS_INT32 iSessionID,const IVS_CHAR* pCameraCode,IVS_INT32 iRecordMethod,const IVS_TIME_SPAN* pTimeSpan,
		const IVS_INDEX_RANGE* pIndexRange,IVS_RECORD_INFO_LIST* pRecordList,IVS_UINT32 uiBufSize);


	/*************************************************************************
	* name			: IVS_SDK_SubscribeAlarmQuery
	* description	: �澯���Ĳ�ѯ
	* input			: iSessionID ��¼�ɹ���ĻỰID
						  pReqXml    �澯���Ĳ�ѯ����xml
	* output		: pRspXml    �澯���Ĳ�ѯ��Ӧxml
	* return		: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
	* remark		: NA
	*************************************************************************/
	IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_SubscribeAlarmQuery(IVS_INT32 iSessionID, const IVS_CHAR* pReqXml, IVS_CHAR** pRspXml);

	/******************************************************************
	* name			: IVS_SDK_ReleaseBuffer
	* description	: �ͷ�SDK�ڲ�������ڴ�
	* input			: pBuffer ָ��SDK�ڲ������ڴ��ָ��
	* output		: NA
	* return		: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
	* remark		: NA
	  *******************************************************************/  
	  IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_ReleaseBuffer(IVS_CHAR *pBuffer);

	/*************************************************************************
	* name			: IVS_SDK_SubscribeAlarm
	* description	: �����澯����
	* input			: iSessionID ��¼�ɹ���ĻỰID
						  pReqXml    �澯��������xml
	* output		: NA
	* return		: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
	* remark		: NA
	*************************************************************************/
	IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_SubscribeAlarm(IVS_INT32 iSessionID, const IVS_CHAR* pReqXml);

	/*************************************************************************
	* name			: IVS_SDK_AddAlarmLinkage
	* description	: �����澯��������
	* input			: iSessionID ��¼�ɹ���ĻỰID
						  pReqXml    ������Ϣ
	* output		: pRspXml    ��Ӧ��Ϣ����������������ID
	* return		: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
	* remark		: pRspXmlʹ������ڴ���Ҫ����IVS_SDK_ReleaseBuffer�ӿڻ���
	*************************************************************************/
	IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_AddAlarmLinkage(IVS_INT32 iSessionID,	const IVS_CHAR* pReqXml, IVS_CHAR** pRspXml);

	/*************************************************************************
	* name       : IVS_SDK_AddAlarmLinkage_S
	* description: �����澯�������ԣ���ȫ������
	* input      : iSessionID ��¼�ɹ���ĻỰID
	* input      : pReqXml��������Ϣ
	* output     : pRspXml,��Ӧ��Ϣ����������������ID
	* return     : �ɹ�����0��ʧ�ܷ��ش�����
	* remark     : pRspXmlʹ������ڴ���Ҫ����IVS_SDK_ReleaseBuffer�ӿڻ���
	*************************************************************************/
	IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_AddAlarmLinkage_S(IVS_INT32 iSessionID, const IVS_CHAR* pReqXml, IVS_CHAR** pRspXml);
	
	/*************************************************************************
	* name			: IVS_SDK_ModifyAlarmLinkage
	* description	: �޸ĸ澯��������
	* input			: iSessionID ��¼�ɹ���ĻỰID
						  pReqXml    ������Ϣ
	* output		: NA
	* return		: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
	* remark		: NA
	*************************************************************************/
	IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_ModifyAlarmLinkage(IVS_INT32 iSessionID, const IVS_CHAR* pReqXml);

	/*************************************************************************
	* name       : IVS_SDK_ModifyAlarmLinkage_S
	* description: �޸ĸ澯�������ԣ���ȫ������
	* input      : iSessionID ��¼�ɹ���ĻỰID
	* input      : pReqXml��������Ϣ
	* output     : NA
	* return     : �ɹ�����0��ʧ�ܷ��ش�����
	* remark     : NA
	*************************************************************************/
	IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_ModifyAlarmLinkage_S(IVS_INT32 iSessionID, const IVS_CHAR* pReqXml);
	
	/*************************************************************************
	* name			: IVS_SDK_DeleteAlarmLinkage
	* description	: ɾ���澯��������
	* input			: iSessionID ��¼�ɹ���ĻỰID
						  pReqXml    ������Ϣ
	* output		: NA
	* return		: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
	* remark		: NA
	*************************************************************************/
	IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_DeleteAlarmLinkage(IVS_INT32 iSessionID, const IVS_CHAR* pReqXml);

	/*************************************************************************
	* name			: IVS_SDK_GetAlarmlinkageList
	* description	: �鿴�澯���������б�
	* input			: iSessionID ��¼�ɹ���ĻỰID
						  pReqXml    ������Ϣ
	* output		: pRspXml    ��Ӧ��Ϣ
	* return		: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
	* remark		: pRspXmlʹ������ڴ���Ҫ����IVS_SDK_ReleaseBuffer�ӿڻ���
	*************************************************************************/
	IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_GetAlarmlinkageList(IVS_INT32 iSessionID, const IVS_CHAR* pReqXml, IVS_CHAR** pRspXml);

	/*************************************************************************
	* name			: IVS_SDK_GetAlarmLinkage
	* description	: ��ѯ�澯��������
	* input			: iSessionID ��¼�ɹ���ĻỰID
						  pReqXml    ������Ϣ
	* output		: pRspXml    ��Ӧ��Ϣ
	* return		: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
	* remark		: pRspXmlʹ������ڴ���Ҫ����IVS_SDK_ReleaseBuffer�ӿڻ���
	*************************************************************************/
	IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_GetAlarmLinkage (IVS_INT32 iSessionID, const IVS_CHAR* pReqXml, IVS_CHAR** pRspXml);

	/*************************************************************************
	* name       : IVS_SDK_GetAlarmLinkage_S
	* description: ��ѯ�澯�������ԣ���ȫ������
	* input      : iSessionID ��¼�ɹ���ĻỰID
	* input      : pReqXml ��ѯ����
	* output     : pRspXml ��ѯ���ĸ澯��������
	* return     : �ɹ�����0��ʧ�ܷ��ش�����
	* remark     : pRspXmlʹ������ڴ���Ҫ����IVS_SDK_ReleaseBuffer�ӿڻ���
	*************************************************************************/
	IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_GetAlarmLinkage_S(IVS_INT32 iSessionID, const IVS_CHAR* pReqXml, IVS_CHAR** pRspXml);
	
	/*************************************************************************
	* name			: IVS_SDK_StartAlarmOut
	* description	: ��������������澯
	* input			: iSessionID    ��¼�ɹ���ĻỰID
						  pAlarmOutCode ����������豸����
	* output		: NA
	* return		: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
	* remark		: NA
	*************************************************************************/
	IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_StartAlarmOut(IVS_INT32 iSessionID, const IVS_CHAR* pAlarmOutCode);

	/*************************************************************************
	* name			: IVS_SDK_StopAlarmOut
	* description	: ֹͣ����������澯
	* input			: iSessionID    ��¼�ɹ���ĻỰID
						  pAlarmOutCode ����������豸����
	* output		: NA
	* return		: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
	* remark		: NA
	*************************************************************************/
	IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_StopAlarmOut(IVS_INT32 iSessionID, const IVS_CHAR* pAlarmOutCode);

	/*************************************************************************
	* name			: IVS_SDK_GetAlarmEventInfo
	* description	: ��ѯ�澯��Ϣ
	* input			: iSessionID      ��¼�ɹ���ĻỰID
						  ullAlarmEventID �澯�¼�ID
						  pAlarmInCode    �澯Դ����
	* output		: pAlarmEvent     �¼�����
	* return		: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
	* remark		: NA
	*************************************************************************/
	IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_GetAlarmEventInfo(IVS_INT32 iSessionID, IVS_UINT64 ullAlarmEventID, const IVS_CHAR* pAlarmInCode, IVS_ALARM_EVENT* pAlarmEvent);

	/*************************************************************************
	* name			: IVS_SDK_GetAlarmEventList
	* description	: ��ѯ��ʷ�澯��Ϣ�б�
	* input			: iSessionID      ��¼�ɹ���ĻỰID
						  pUnifiedQuery   ��ѯ����
						  uiBufferSize    �����С
	* output		: pAlarmEventList �澯��Ϣ�б�
	* return		: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
	* remark		: NA
	*************************************************************************/
	IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_GetAlarmEventList(IVS_INT32 iSessionID, const IVS_QUERY_UNIFIED_FORMAT* pUnifiedQuery, IVS_ALARM_EVENT_LIST* pAlarmEventList, IVS_UINT32 uiBufferSize);

	/*************************************************************************
	* name			: IVS_SDK_GetAlarmTypeList
	* description	: ��ѯ�澯�����б�
	* input			: iSessionID ��¼�ɹ���ĻỰID
						  pUnifiedQuery ��ѯ����
						  uiBufferSize �����С
	* output			: pAlarmTypeList �澯�����б�
	* return			: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
	* remark			: NA
	*************************************************************************/
    IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_GetAlarmTypeList (IVS_INT32 iSessionID, const IVS_QUERY_UNIFIED_FORMAT* pUnifiedQuery, IVS_ALARM_TYPE_LIST* pAlarmTypeList, IVS_UINT32 uiBufferSize);

	/*************************************************************************
	* name			: IVS_SDK_SetAlarmTypeLevel
	* description	: ���ø澯���ͼ���
	* input			: iSessionID ��¼�ɹ���ĻỰID
						  pAlarmTypeList �澯�����б�
	* output			: NA
	* return			: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
	* remark			: NA
	*************************************************************************/
	IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_SetAlarmTypeLevel(IVS_INT32 iSessionID, const IVS_ALARM_TYPE_LIST* pAlarmTypeList);

	/*************************************************************************
	* name			: IVS_SDK_GetAlarmLevelList
	* description	: ��ѯ�澯�����б�
	* input			: iSessionID ��¼�ɹ���ĻỰID
						  uiMaxAlarmLevelNum ϵͳ���澯�������IVS_MAX_ALARM_LEVEL_NUM
						  uiBufferSize  �澯���������ڴ�ռ��С
	* output			: puiAlarmLevelNum ��ѯ���ص�ϵͳ�澯�������
						  pAlarmLevel �澯�����б�
	* return			: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
	* remark			: NA
	*************************************************************************/
	IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_GetAlarmLevelList(IVS_INT32 iSessionID,
		IVS_UINT32 uiMaxAlarmLevelNum,IVS_UINT32* puiAlarmLevelNum,IVS_ALARM_LEVEL* pAlarmLevel,IVS_UINT32 uiBufferSize);

	/**************************************************************************
    * name			: IVS_SDK_GetAlarmLevel
    * description	: ��ѯ�澯��������
    * input			: iSessionID     ��¼�ɹ���ĻỰID
						  uiAlarmLevelID    �澯����ID
    * output			: pAlarmLevel    �澯�������� 
    * return			: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
    * remark			: NA
    **************************************************************************/
	IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_GetAlarmLevel(IVS_INT32 iSessionID,IVS_UINT32 uiAlarmLevelID,IVS_ALARM_LEVEL* pAlarmLevel);

	/*************************************************************************
	* name			: IVS_SDK_AddAlarmArea
	* description	: ��������
	* input			: iSessionID ��¼�ɹ���ĻỰID
						  pReq ����XML
	* output			: pRsp ��ӦXML
	* return			: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
	* remark			: NA
	*************************************************************************/
	IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_AddAlarmArea(IVS_INT32 iSessionID, const IVS_CHAR* pReq, IVS_CHAR** pRsp);

	/*************************************************************************
	* name			: IVS_SDK_ModifyAlarmArea
	* description	: �޸ķ���
	* input			: iSessionID ��¼�ɹ���ĻỰID
						  pReqXml ����XML
	* output			: NA
	* return			: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
	* remark			: NA
	*************************************************************************/
	IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_ModifyAlarmArea(IVS_INT32 iSessionID, const IVS_CHAR* pReqXml);

	/*************************************************************************
	* name			: IVS_SDK_DeleteAlarmArea
	* description	: ɾ������
	* input			: iSessionID ��¼�ɹ���ĻỰID
						  pDomainCode Ŀ�������
						  uiAlarmAreaId ����ID
	* output			: NA
	* return			: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
	* remark			: NA
	*************************************************************************/
	IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_DeleteAlarmArea(IVS_INT32 iSessionID, const IVS_CHAR* pDomainCode, IVS_UINT32 uiAlarmAreaId);

	/*************************************************************************
	* name			: IVS_SDK_GetAlarmAreaList
	* description	: �鿴�����б�
	* input			: iSessionID ��¼�ɹ���ĻỰID
						  pReqXml ����XML
	* output			: pRspXml ��ӦXML
	* return			: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
	* remark			: NA
	*************************************************************************/
	IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_GetAlarmAreaList(IVS_INT32 iSessionID, const IVS_CHAR* pReqXml, IVS_CHAR** pRspXml);

	/*************************************************************************
	* name			: IVS_SDK_GetAlarmAreaInfo
	* description	: �鿴��������
	* input			: iSessionID ��¼�ɹ���ĻỰID
						  pDomainCode �����
						  uiAlarmAreaId ����ID
	* output			: pAlarmArea ��������
	* return			: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
	* remark			: NA
	*************************************************************************/
	IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_GetAlarmAreaInfo(IVS_INT32 iSessionID,const IVS_CHAR* pDomainCode,IVS_UINT32 uiAlarmAreaId,IVS_CHAR** pAlarmArea);

	/*************************************************************************
	* name			: IVS_SDK_StartAlarmAreaGuard
	* description	: �ֶ�����
	* input			: iSessionID ��¼�ɹ���ĻỰID
						  pDomainCode �����
						  uiAlarmAreaId  ����ID
	* output			: NA
	* return			: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
	* remark			: NA
	*************************************************************************/
	IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_StartAlarmAreaGuard(IVS_INT32 iSessionID, const IVS_CHAR* pDomainCode,IVS_UINT32 uiAlarmAreaId);

	/*************************************************************************
	* name			: IVS_SDK_SubscribeAlarmQuery
	* description	: �ֶ�����
	* input			: iSessionID ��¼�ɹ���ĻỰID
						  pDomainCode �����
						  uiAlarmAreaId  ����ID
	* output			: NA
	* return			: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
	* remark			: NA
	*************************************************************************/
	IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_StopAlarmAreaGuard(IVS_INT32 iSessionID, const IVS_CHAR* pDomainCode,IVS_UINT32 uiAlarmAreaId);

	/*************************************************************************
	* name			: IVS_SDK_AllocAreaGuardPlan
	* description	: ���������ƻ�
	* input			: iSessionID ��¼�ɹ���ĻỰID
						  pReqXml ����XML
	* output			: NA
	* return			: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
	* remark			: NA
	*************************************************************************/
	IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_AllocAreaGuardPlan(IVS_INT32 iSessionID,const IVS_CHAR* pReqXml);

	/*************************************************************************
	* name			: IVS_SDK_GetAreaGuardPlan
	* description	: �鿴�����ƻ�
	* input			: iSessionID ��¼�ɹ���ĻỰID
						  pDomainCode �����
						  uiAlarmAreaId ����ID
	* output			: pRspXml ��ӦXML
	* return			: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
	* remark			: NA
	*************************************************************************/
	IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_GetAreaGuardPlan(IVS_INT32 iSessionID, const IVS_CHAR* pDomainCode,IVS_UINT32 uiAlarmAreaId, IVS_CHAR** pRspXml);

	/*************************************************************************
	* name			: IVS_SDK_QueryDeviceList
	* description	: ��ѯ�豸�б�
	* input			: iSessionID ��¼�ɹ���ĻỰID
						  pDomainCode �����
						  uiDeviceType �豸���ͣ�ȡֵ�ο�IVS_DEVICE_TYPE��Ŀǰ֧�ָ���������ѯ���豸�����ǣ�
                                1-���豸
						  pQueryFormat ͨ�ò�ѯ�ṹ��
						  uiBufferSize �����С
	* output		: pBuffer  ������ڴ棬��uiDeviceType��Ӧ
                                1-���豸��IVS_DEVICE_BRIEF_INFO_LIST
	* return		: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
	* remark		: NA
	*************************************************************************/
    IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_QueryDeviceList(IVS_INT32 iSessionID,
		const IVS_CHAR* pDomainCode,
		IVS_UINT32 uiDeviceType, 
		const IVS_QUERY_UNIFIED_FORMAT *pQueryFormat, 
		IVS_VOID* pBuffer, 
		IVS_UINT32 uiBufferSize);

	/******************************************************************
	* name			: IVS_SDK_GetDeviceList
	* description	: ��ȡ�豸�б�
	* input			: iSessionID   ��¼�ɹ���ĻỰID
						  uiDeviceType �豸���ͣ�ȡֵ�ο�IVS_DEVICE_TYPE��Ŀǰ֧�ֻ�ȡ����3���豸�б�
								2-����ͷ�豸
                                4-�澯�豸
								9-����澯�豸
								30-Ӱ������ͷ
								32-����ͷ�豸��Ӱ������ͷ
								33-����ͷ�豸�����и߶Ⱥ;�γ����Ϣ
						  pIndexRange  ��ҳ��Ϣ
						  uiBufferSize �����С
	* output		: pDeviceList  �豸�б�ָ�룬����˵�����£�
                                ����ͷ�豸��IVS_CAMERA_BRIEF_INFO_LIST
								�澯�豸��IVS_ALARM_BRIEF_INFO_LIST
                                ����澯�豸��IVS_ALARM_BRIEF_INFO_LIST
                                Ӱ������ͷ��IVS_SHADOW_CAMERA_BRIEF_INFO_LIST
								����ͷ�豸��Ӱ������ͷ��IVS_SHADOW_CAMERA_BRIEF_INFO_LIST
								����ͷ�豸�����и߶Ⱥ;�γ����Ϣ��IVS_CAMERA_BRIEF_INFO_LIST_EX
	* return		: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
	* remark		: NA
	*******************************************************************/
	IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_GetDeviceList(
		IVS_INT32 iSessionID,
		IVS_UINT32 uiDeviceType,
		const IVS_INDEX_RANGE* pIndexRange,
		IVS_VOID* pDeviceList,
		IVS_UINT32 uiBufferSize);

	/*************************************************************************
	* name			: IVS_SDK_AddDeviceGroup
	* description	: �����豸��
	* input			: iSessionID ��¼�ɹ���ĻỰID
						  pDevGroup �豸����Ϣ
	* output			: puiDevGroupID �豸��ID
	* return			: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
	* remark			: NA
	*************************************************************************/
	IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_AddDeviceGroup (IVS_INT32 iSessionID, const IVS_DEV_GROUP* pDevGroup,IVS_UINT32* puiDevGroupID);

	/*************************************************************************
    * name			: IVS_SDK_DeleteDeviceGroup
    * description	: ɾ���豸��
    * input			: iSessionID ��¼�ɹ���ĻỰID
						  pDomainCode ɾ���豸�������������
						  uiDevGroupID ɾ�����豸��ID
    * output			: NA
    * return			: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
    * remark			: NA
    *************************************************************************/
    IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_DeleteDeviceGroup( IVS_INT32 iSessionID, const IVS_CHAR* pDomainCode, IVS_UINT32 uiDevGroupID);

	/**************************************************************************
    * name			: IVS_SDK_ModifyDeviceGroupName
    * description	: �޸��豸������
    * input			: iSessionID  ��¼�ɹ���ĻỰID
						  pDomainCode  �豸�����������
						  uiDevGroupID  �豸��ID
						  pNewDevGroupName  �豸��������
    * return			: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
    * remark			: NA
    **************************************************************************/
    IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_ModifyDeviceGroupName(IVS_INT32 iSessionID,  const IVS_CHAR* pDomainCode, IVS_UINT32 uiDevGroupID, const IVS_CHAR* pNewDevGroupName);

	/*************************************************************************
	* name			: IVS_SDK_MoveDeviceGroup
	* description	: �ƶ��豸��
	* input			: iSessionID ��¼�ɹ���ĻỰID
						  pDomainCode  �豸�����������
						  uiNewParentDevGroupID  �豸����¸���ID
						  uiDevGroupID  �豸��ID
	* output			: NA
	* return			: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
	* remark			: NA
	*************************************************************************/
    IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_MoveDeviceGroup(IVS_INT32 iSessionID,  const IVS_CHAR* pDomainCode, IVS_UINT32 uiNewParentDevGroupID, IVS_UINT32 uiDevGroupID);

	/*************************************************************************
	* name			: IVS_SDK_GetDeviceGroup
	* description	: ��ѯ�豸���б�
	* input			: iSessionID    ��¼�ɹ���ĻỰID
						  pDomainCode   �豸�����������
						  pDevGroupCode �豸��ID
						  uiBufferSize  �����С
	* output		: pDeviceGroupList �豸���б�
	* return		: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
	* remark		: NA
	*************************************************************************/		
    IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_GetDeviceGroup(IVS_INT32 iSessionID,
                                                            const IVS_CHAR* pDomainCode,
                                                            const IVS_CHAR* pDevGroupCode,
                                                            IVS_DEVICE_GROUP_LIST* pDeviceGroupList,
                                                            IVS_UINT32 uiBufferSize);

	/******************************************************************
    function		: IVS_SDK_AddDeviceToGroup
    description	: �����豸�����豸
    input			: iSessionID  ��¼�ɹ���ĻỰID
					  pTargetDomainCode  Ŀ���豸�������
					  uiTargetDevGroupID  Ŀ���豸��ID
					  uiDeviceNum  �����豸����
					  pGroupCameraList  �����豸��Ϣ����ָ��
    output		: NA
    return		: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
    *******************************************************************/
    IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_AddDeviceToGroup( IVS_INT32 iSessionID, 
                                        const IVS_CHAR* pTargetDomainCode,
                                        IVS_UINT32 uiTargetDevGroupID,
                                        IVS_UINT32 uiDeviceNum,
                                        const IVS_DEV_GROUP_CAMERA* pGroupCameraList);

	/******************************************************************
    function		: IVS_SDK_DeleteDeviceFromGroup
    description	: ɾ���豸�����豸
    input			: iSessionID  ��¼�ɹ���ĻỰID
					  pTargetDomainCode  Ŀ���豸�������
					  uiDeviceNum  ɾ���豸����
					  pGroupCameraList  ɾ���豸��Ϣ����ָ��
    output		: NA
    return		: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
    *******************************************************************/
    IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_DeleteDeviceFromGroup( IVS_INT32 iSessionID, 
                                                                    const IVS_CHAR* pTargetDomainCode,
                                                                    IVS_UINT32 uiDeviceNum,
                                                                    const IVS_DEV_GROUP_CAMERA* pGroupCameraList);

    /**************************************************************************
    * name			: IVS_SDK_StartRealPlay
    * description	: ��ʼʵʱ���
    * input			: iSessionID    ��¼�ɹ���ĻỰID
						  pRealplayPara ʵ�����������ʵ�������ṹ��
						  pCamerCode    ����ͷ����
						  hWnd          ���ھ��
    * output		: pHandle       ���ž��
    * return		: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
	* remark		: NA
    **************************************************************************/
    IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_StartRealPlay(IVS_INT32 iSessionID, IVS_REALPLAY_PARAM* pRealplayPara, const IVS_CHAR* pCameraCode, HWND hWnd, IVS_ULONG* pHandle);

	/**************************************************************************
    * name			: IVS_SDK_StartRealPlayCBRaw
    * description	: ��ʼʵʱ������Իص���ʽ���ƴ֡���������
    * input			: iSessionID           ��¼�ɹ���ĻỰID
						  pRealplayPara        ʵ�����������ʵ�������ṹ��
						  pCamerCode           ����ͷ����
						  fRealPlayCallBackRaw ʵʱ����ص�����
						  pUserData            �û����ݣ��Զ��壬��Ӧ�ص�����������ʱ���ظò���
    * output		: pHandle              ���ž��
    * return		: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
	* remark		: NA
    **************************************************************************/
	IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_StartRealPlayCBRaw(IVS_INT32 iSessionID, IVS_REALPLAY_PARAM* pRealplayPara, const IVS_CHAR* pCameraCode, 
                                                                RealPlayCallBackRaw fRealPlayCallBackRaw, void* pUserData, IVS_ULONG* pHandle );

	/**************************************************************************
    * name			: IVS_SDK_StartRealPlayCBFrame
    * description	: ��ʼʵʱ������Իص���ʽ���YUV��
    * input			: iSessionID               ��¼�ɹ���ĻỰID
						  pRealplayPara            ʵ�����������ʵ�������ṹ��
						  pCamerCode               ����ͷ����
						  fRealPlayCallBackFrame   ʵʱ����ص�����
						  pUserData                �û����ݣ��Զ��壬��Ӧ�ص�����������ʱ���ظò���
    * output		: pHandle                  ���ž��
    * return		: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
	* remark		: NA
    **************************************************************************/
	IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_StartRealPlayCBFrame(IVS_INT32 iSessionID, IVS_REALPLAY_PARAM* pRealplayPara, const IVS_CHAR* pCameraCode, 
                                                                  RealPlayCallBackFrame fRealPlayCallBackFrame, void* pUserData, IVS_ULONG* pHandle);

	/**************************************************************************
    * name			: IVS_SDK_StopRealPlay
    * description	: ֹͣʵʱ���
    * input			: iSessionID ��¼�ɹ���ĻỰID
						  ulHandle   ���ž��
    * output		: NA
    * return		: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
	* remark		: NA
    **************************************************************************/
	IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_StopRealPlay( IVS_INT32 iSessionID, IVS_ULONG ulHandle);

	/**************************************************************************
    * name			: IVS_SDK_AddPlayWindowPartial
    * description	: ��Ӿֲ��Ŵ󴰿�
    * input			: iSessionID   ��¼�ɹ���ĻỰID
						  ulPlayHandle ���ž��
						  hWnd         ���ھ��
						  pPartial     �ֲ��Ŵ��������Σ���ʾԭͼλ�ðٷֱȣ�����˵�����£�
								��Ҫ�Ŵ��������top��bottom��left��right
								ͼ��ߴ�width��height
								pPartial->top = top*100/height
								pPartial->bottom = bottom*100/height
								pPartial->left = left*100/width
								pPartial->right = right*100/width

    * output		: NA
    * return		: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
	* remark		: NA
    **************************************************************************/
	IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_AddPlayWindowPartial(IVS_INT32 iSessionID, IVS_ULONG ulPlayHandle, HWND hWnd, void *pPartial);

	/**************************************************************************
    * name			: IVS_SDK_UpdateWindowPartial
    * description	: ˢ�¾ֲ��Ŵ󴰿ڣ���Ŵ�����λ���ƶ���
    * input			: iSessionID   ��¼�ɹ���ĻỰID
						  ulPlayHandle ���ž��
						  hWnd         ���ھ��
						  pPartial     �ֲ��Ŵ��������Σ���ʾԭͼλ�ðٷֱȣ�����˵�����£�
								��Ҫ�Ŵ��������top��bottom��left��right
								ͼ��ߴ�width��height
								pPartial->top = top*100/height
								pPartial->bottom = bottom*100/height
								pPartial->left = left*100/width
								pPartial->right = right*100/width
    * output		: NA
    * return		: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
	* remark		: NA
    **************************************************************************/
	IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_UpdateWindowPartial(IVS_INT32 iSessionID, IVS_ULONG ulPlayHandle, HWND hWnd, void *pPartial);

	/**************************************************************************
    * name			: IVS_SDK_StartPlatformPlayBack
    * description	: ��ʼƽ̨¼��ط�
    * input			: iSessionID      ��¼�ɹ���ĻỰID
						  pCameraCode     ���������
						  pPlaybackParam  �طŲ���
						  hWnd            ���ھ��
    * output		: pHandle         ���ž��
    * return		: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
    * remark		: NA
    **************************************************************************/
    IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_StartPlatformPlayBack(IVS_INT32 iSessionID,
                                                                   const IVS_CHAR* pCameraCode,
                                                                   const IVS_PLAYBACK_PARAM* pPlaybackParam,
                                                                   HWND hWnd,
                                                                   IVS_ULONG* pHandle);

   /**************************************************************************
    * name			: IVS_SDK_StopPlatformPlayBack
    * description	: ֹͣƽ̨¼��ط�
    * input			: iSessionID      �ỰID
						  ulPlayHandle    ���ž��
    * output		: NA
    * return		: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
    * remark		: NA
    **************************************************************************/
	IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_StopPlatformPlayBack(IVS_INT32 iSessionID,IVS_ULONG ulPlayHandle);

	/**************************************************************************
    * name			: IVS_SDK_StartPlatformPlayBackByIP
    * description	: ��ʼ�ͻ���ƽ̨¼��ط�
    * input			: iSessionID      �ỰID
						  pCameraCode     ���������
						  pPlaybackParam  �طŲ���
						  pMediaAddrDst  ý����Ŀ���ַ
	* output			: pMediaAddrSrc ý����Դ��ַ
						  pHandle ���ž��
    * return			: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
    * remark			: NA
    **************************************************************************/
    IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_StartPlatformPlayBackByIP(IVS_INT32 iSessionID,
																	const IVS_CHAR* pCameraCode,
																	const IVS_PLAYBACK_PARAM* pPlaybackParam,
																	const IVS_MEDIA_ADDR* pMediaAddrDst,
																	IVS_MEDIA_ADDR* pMediaAddrSrc,
																	IVS_ULONG* pHandle);

   /**************************************************************************
    * name			: IVS_SDK_StopPlatformPlayBackByIP
    * description	: ֹͣ�ͻ���ƽ̨¼��ط�
    * input			: iSessionID      �ỰID
						  ulPlayHandle    ���ž��
    * output			: NA
    * return			: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
    * remark			: NA
    **************************************************************************/
	IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_StopPlatformPlayBackByIP(IVS_INT32 iSessionID,IVS_ULONG ulPlayHandle);
	
	/**************************************************************************
    * name			: IVS_SDK_PlatformPlayBackPauseByIP
    * description: ��ͣƽ̨¼��ط�
    * input			: iSessionID	�ỰID
							: ulPlayHandle	���ž��
    * output			: NA
    * return			: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
    * remark		: NA
    **************************************************************************/
    IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_PlatformPlayBackPauseByIP(IVS_INT32 iSessionID,
																	IVS_ULONG ulPlayHandle);

	/**************************************************************************
    * name			: IVS_SDK_PlatformPlayBackResumeByIP
    * description: �ָ�ƽ̨¼��ط�
    * input			: iSessionID	�ỰID
							: ulPlayHandle	���ž��
    * output			: NA
    * return			: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
    * remark		: NA
    **************************************************************************/
    IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_PlatformPlayBackResumeByIP(IVS_INT32 iSessionID,
																	IVS_ULONG ulPlayHandle);

	/**************************************************************************
    * name			: IVS_SDK_SetPlayBackSpeedByIP
    * description: ����ƽ̨¼�������ط��ٶ�
    * input			: iSessionID	�ỰID
							: ulPlayHandle	���ž��
							: fSpeed	�����ٶ�
    * output			: NA
    * return			: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
    * remark		: NA
    **************************************************************************/
    IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_SetPlayBackSpeedByIP(IVS_INT32 iSessionID, 
		IVS_ULONG ulPlayHandle, 
		IVS_FLOAT fSpeed);
	
	/**************************************************************************
    * name			: IVS_SDK_SetPlayBackSpeedByIPnTime
    * description	: ����ƽ̨¼�������ط��ٶ�
    * input			: iSessionID	�ỰID
					: ulPlayHandle	���ž��
					: fSpeed	�����ٶ�
					: uiOffsetTime	��ǰ����ʱ�䣬��λ����
    * output		: NA
    * return		: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
    * remark		: NA
    **************************************************************************/
    IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_SetPlayBackSpeedByIPnTime(IVS_INT32 iSessionID, 
		IVS_ULONG ulPlayHandle, 
		IVS_FLOAT fSpeed, IVS_UINT64 uiOffsetTime);

	 /**************************************************************************
    * name			: IVS_SDK_SetPlayBackTimeByIP
    * description: ����ƽ̨¼�������ط�ʱ��
    * input			: iSessionID	�ỰID
							: ulPlayHandle	���ž��
							: uiTime	�϶��߶ȣ���λ�룬������������ʱ��
    * output			: NA
    * return			: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
    * remark		: NA
    **************************************************************************/
    IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_SetPlayBackTimeByIP(IVS_INT32 iSessionID, 
		IVS_ULONG ulPlayHandle, 
		IVS_UINT32 uiTime);

	/**************************************************************************
    * name			: IVS_SDK_StartLocalPlayBack
    * description	: ��ʼ����¼��ط�
    * input			: iSessionID      ��¼�ɹ���ĻỰID
						  pFileName       ����¼���ļ�
						  pPlaybackParam  �طŲ���
						  hWnd            ���ھ��
    * output		: pHandle         ���ž��
    * return		: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
    * remark		: NA
    **************************************************************************/
	IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_StartLocalPlayBack(IVS_INT32 iSessionID,
		                       const IVS_CHAR* pFileName,
		                       const IVS_LOCAL_PLAYBACK_PARAM* pPlaybackParam,
		                       HWND hWnd, 
							   IVS_ULONG* pHandle);
	
	/**************************************************************************
    * name			: IVS_SDK_StartPlatformPlayBack
    * description	: ֹͣ����¼��ط�
    * input			: iSessionID      ��¼�ɹ���ĻỰID
						  ulPlayHandle    �طž��
    * output		: NA
    * return		: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
    * remark		: NA
    **************************************************************************/
	IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_StopLocalPlayBack(IVS_INT32 iSessionID, IVS_ULONG ulPlayHandle);

    /**************************************************************************
    * name			: IVS_SDK_StartPlatformPlayBackCBRaw
    * description	: ��ʼƽ̨¼��ط�(�������ص�)
    * input			: iSessionID           ��¼�ɹ���ĻỰID
						  pCameraCode          ���������
						  pPlaybackParam       �طŲ���
						  fPlayBackCallBackRaw ¼��ط��������ص�����
						  pUserData            �û����ݣ��Զ��壬��Ӧ�ص�����������ʱ���ظò���
    * output		: pHandle              ���ž��
    * return		: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
    * remark		: NA
    **************************************************************************/
	IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_StartPlatformPlayBackCBRaw(IVS_INT32 iSessionID,
																		const IVS_CHAR* pCameraCode,
																		const IVS_PLAYBACK_PARAM* pPlaybackParam,
																		PlayBackCallBackRaw fPlayBackCallBackRaw, 
																		void* pUserData,
																		IVS_ULONG* pHandle);


	/**************************************************************************
    * name			: IVS_SDK_StartPlatformPlayBackCBFrame
    * description	: ��ʼƽ̨¼��ط�(֡�����ص�)
    * input			: iSessionID             ��¼�ɹ���ĻỰID
						  pCameraCode            ���������
						  pPlaybackParam         �طŲ���
						  fPlayBackCallBackFrame ¼��طŽ����֡�����ص�����
						  pUserData              �û����ݣ��Զ��壬��Ӧ�ص�����������ʱ���ظò���
    * output		: pHandle                ���ž��
    * return		: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
    * remark		: NA
    **************************************************************************/
	IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_StartPlatformPlayBackCBFrame(IVS_INT32 iSessionID,
		   																  const IVS_CHAR* pCameraCode,
																		  const IVS_PLAYBACK_PARAM* pPlaybackParam,
																		  PlayBackCallBackFrame fPlayBackCallBackFrame, 
																		  void* pUserData,
																		  IVS_ULONG* pHandle);
	/**************************************************************************
    * name       : IVS_SDK_StartPlatformPlayBackCBFrameEx
    * description: ��ʼƽ̨¼��ط�(֡�����ص�)
    * input      : iSessionID			��¼�ɹ���ĻỰID
                   pPlaybackParam		¼��طŲ���
                   fDisplayCallBack		¼��طŽ����֡�����ص�����
                   pUserData			�û�����
    * output     : pHandle				���ž��
    * return     : �ɹ�����IVS_SUCCESSED��ʧ�ܷ��ش�����
    * remark     : �ص��ٶ����û��ٶ�һ��
    **************************************************************************/
	IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_StartPlatformPlayBackCBFrameEx(IVS_INT32 iSessionID,
		const IVS_CHAR* pCameraCode,
		const IVS_PLAYBACK_PARAM* pPlaybackParam,
		DisplayCallBackFrame fDisplayCallBack, 
		void* pUserData,
		IVS_ULONG* pHandle);


    /******************************************************************
     function		: IVS_SDK_PlayBackPause
     description	: ��ͣ�ط�
     input			: iSessionID   ��¼�ɹ���ĻỰID
						  ulPlayHandle ���ž��
     output			: NA
     return			: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
    *******************************************************************/
    IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_PlayBackPause(IVS_INT32 iSessionID, IVS_ULONG ulPlayHandle);

    /******************************************************************
     function		: IVS_SDK_PlayBackResume
     description	: �ָ��ط�
     input			: iSessionID   ��¼�ɹ���ĻỰID
						  ulPlayHandle ���ž��
     output			: NA
     return			: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
    *******************************************************************/
    IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_PlayBackResume(IVS_INT32 iSessionID, IVS_ULONG ulPlayHandle);

	/******************************************************************
	 function		: IVS_SDK_GetPlayBackStatus
	 description	: ��ȡ�ط�״̬
     input			: iSessionID   ��¼�ɹ���ĻỰID
						  ulPlayHandle ���ž��
     output			: pbPause      ����״̬��0-��ͣ��1-����
     return			: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
	*******************************************************************/
	IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_GetPlayBackStatus(IVS_INT32 iSessionID, IVS_ULONG ulPlayHandle, IVS_BOOL* pbPause);

    /******************************************************************
     function		: IVS_SDK_PlayBackFrameStepForward
     description	: ��֡����
     input			: iSessionID   ��¼�ɹ���ĻỰID
						  ulPlayHandle ���ž��
     output			: NA
     return			: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
    *******************************************************************/
    IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_PlayBackFrameStepForward(IVS_INT32 iSessionID, IVS_ULONG ulPlayHandle);

    /******************************************************************
     function		: IVS_SDK_PlayBackFrameStepBackward
     description	: ��֡����
     input			: iSessionID   ��¼�ɹ���ĻỰID
						  ulPlayHandle ���ž��
     output			: NA
     return			: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
    *******************************************************************/
	IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_PlayBackFrameStepBackward(IVS_INT32 iSessionID, IVS_ULONG ulPlayHandle);

    /******************************************************************
     function		: IVS_SDK_SetPlayBackSpeed
     description	: ���ûط��ٶ�
     input			: iSessionID   ��¼�ɹ���ĻỰID
						  ulPlayHandle ���ž��
						  fSpeed       �����ٶ�
     output			: NA
     return			: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
    *******************************************************************/
    IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_SetPlayBackSpeed(IVS_INT32 iSessionID, IVS_ULONG ulPlayHandle, IVS_FLOAT fSpeed);

	/******************************************************************
	 function		: IVS_SDK_GetPlayBackSpeed
	 description	: ��ȡ�ط��ٶ�
     input			: iSessionID   ��¼�ɹ���ĻỰID
						  ulPlayHandle ���ž��
     output			: fSpeed       �����ٶ�
     return			: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
	*******************************************************************/
	IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_GetPlayBackSpeed(IVS_INT32 iSessionID, IVS_ULONG ulPlayHandle, IVS_FLOAT* pfSpeed);

    /******************************************************************
     function		: IVS_SDK_SetPlayBackTime
     description	: �ط��϶�
     input			: iSessionID   ��¼�ɹ���ĻỰID
						  ulPlayHandle ���ž��
						  uiTime       �϶��߶ȣ���λ�룬������������ʱ��
     output			: NA
     return			: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
    *******************************************************************/
    IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_SetPlayBackTime(IVS_INT32 iSessionID, IVS_ULONG ulPlayHandle, IVS_UINT32 uiTime);

    /******************************************************************
     function		: IVS_SDK_GetPlayBackTime
     description	: ��ȡ��ǰ�ط�ʱ��
     input			: iSessionID    ��¼�ɹ���ĻỰID
						  ulPlayHandle  ���ž��
     output			: pPlayBackTime �ط�ʱ��
     return			: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
    *******************************************************************/
    IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_GetPlayBackTime(IVS_INT32 iSessionID, IVS_ULONG ulPlayHandle, IVS_PLAYBACK_TIME* pPlayBackTime);

	/******************************************************************
     function		: IVS_SDK_StartPlatformDownload
     description	: ��ʼƽ̨¼������
     input			: iSessionID      ��¼�ɹ���ĻỰID
						  pCameraCode     ���������
						  pDownloadParam  ¼�����ز���
     output			: pulHandle       ¼�����ؾ��
     return			: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
    *******************************************************************/
	IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_StartPlatformDownload(IVS_INT32 iSessionID, const IVS_CHAR* pCameraCode,
		const IVS_DOWNLOAD_PARAM* pDownloadParam, IVS_ULONG* pulHandle);

	/******************************************************************
     function		: IVS_SDK_StopPlatformDownload
     description	: ֹͣƽ̨¼������
     input			: iSessionID ��¼�ɹ���ĻỰID
						  ulHandle   ¼�����ؾ��
	 output			: NA
     return			: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
    *******************************************************************/
    IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_StopPlatformDownload(IVS_INT32 iSessionID, IVS_ULONG ulHandle);

	/******************************************************************
     function		: IVS_SDK_StartPUDownload
     description	: ��ʼǰ��¼������
     input			: iSessionID      ��¼�ɹ���ĻỰID
						  pCameraCode     ���������
						  pDownloadParam  ¼�����ز���
     output			: pulHandle       ¼�����ؾ��
     return			: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
    *******************************************************************/
	IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_StartPUDownload(IVS_INT32 iSessionID, const IVS_CHAR* pCameraCode,
					const IVS_DOWNLOAD_PARAM* pDownloadParam, IVS_ULONG* pulHandle);

	/******************************************************************
     function		: IVS_SDK_StopPUDownload
     description	: ֹͣǰ��¼������
     input			: iSessionID ��¼�ɹ���ĻỰID
						  ulHandle   ¼�����ؾ��
	 output			: NA
     return			: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
    *******************************************************************/
	IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_StopPUDownload(IVS_INT32 iSessionID, IVS_ULONG ulHandle);

	/******************************************************************
     function		: IVS_SDK_DownloadPause
     description	: ��ͣ¼������
     input			: iSessionID ��¼�ɹ���ĻỰID
						  ulHandle   ¼�����ؾ��
	 output			: NA
     return			: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
    *******************************************************************/
    IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_DownloadPause(IVS_INT32 iSessionID, IVS_ULONG ulHandle);

	/******************************************************************
     function		: IVS_SDK_DownloadResume
     description	: �ָ�¼������
     input			: iSessionID ��¼�ɹ���ĻỰID
						  ulHandle   ¼�����ؾ��
	 output			: NA
     return			: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
    *******************************************************************/
	IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_DownloadResume(IVS_INT32 iSessionID,IVS_ULONG ulHandle);

	/******************************************************************
     function		: IVS_SDK_GetDownloadInfo
     description	: ��ȡ������Ϣ
     input			: iSessionID    ��¼�ɹ���ĻỰID
						  ulHandle      ¼�����ؾ��
	 output			: pDownloadInfo ¼��������Ϣ
     return			: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
    *******************************************************************/
	IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_GetDownloadInfo(IVS_INT32 iSessionID, 
		              IVS_ULONG ulHandle, IVS_DOWNLOAD_INFO* pDownloadInfo);

	/**************************************************************************
    * name			: IVS_SDK_StartPUPlayBack
    * description	: ��ʼǰ��¼��ط�
    * input			: iSessionID      ��¼�ɹ���ĻỰID
						  pCameraCode     ���������
						  pPlaybackParam  �طŲ���
						  hWnd            ���ھ��
    * output		: pHandle         �طž��
    * return		: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
    * remark		: NA
    **************************************************************************/
#ifdef WIN32
    IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_StartPUPlayBack(
                                    IVS_INT32 iSessionID,
                                    const IVS_CHAR* pCameraCode,
                                    const IVS_PLAYBACK_PARAM* pPlaybackParam,
                                    HWND hWnd,
                                    IVS_ULONG* pHandle);
#endif

	/**************************************************************************
    * name       : 
    * description: ��ʼ�ͻ���ǰ��¼��ط��������ص�
    * input      : iSessionID      �ỰID
				   pCameraCode     ���������
                   pPlaybackParam  �طŲ���
				   fPlayBackCallBackRaw �������ص�����
				   pUserData	   �û�����
                   pHandle         �طž��
    * output     : NA
    * return     : �ɹ����ز��ž����ʧ�ܷ��ظ���������
    * remark     : NA
    **************************************************************************/
    IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_StartPUPlayBackCBRaw(
                                    IVS_INT32 iSessionID,
                                    const IVS_CHAR* pCameraCode,
                                    const IVS_PLAYBACK_PARAM* pPlaybackParam,
									PlayBackCallBackRaw fPlayBackCallBackRaw, 
									void* pUserData,
                                    IVS_ULONG* pHandle);

   /**************************************************************************
    * name			: IVS_SDK_StopPUPlayBack
    * description	: ֹͣǰ��¼��ط�
    * input			: iSessionID      ��¼�ɹ���ĻỰID
						  ulPlayHandle    ���ž��
    * output		: NA
    * return		: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
    * remark		: NA
    **************************************************************************/
	IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_StopPUPlayBack(IVS_INT32 iSessionID,
                                                       IVS_ULONG ulPlayHandle);

	/**************************************************************************
    * name			: IVS_SDK_GetMediaInfo
    * description	: ��ȡý����Ϣ
    * input			: iSessionID     ��¼�ɹ���ĻỰID
						  ulHandle       ҵ����������ʵ�����ط�
    * output		: pMediaInfo     ý����Ϣ
    * return		: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
    * remark		: NA
    **************************************************************************/
    IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_GetMediaInfo(IVS_INT32 iSessionID, IVS_ULONG ulHandle, IVS_MEDIA_INFO* pMediaInfo);

	/**************************************************************************
	* name			: IVS_SDK_SetDisplayScale
	* description	: ���ò�����ʾ����
	* input			: iSessionID        ��¼�ɹ���ĻỰID
						  ulHandle          ҵ����������ʵ�����ط�
						  iDisplayScale     ��ʾ����ֵ��1-ԭʼ������ʾ 2-�������� 
	* output		: NA
	* return		: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
	* remark		: NA
	**************************************************************************/
	IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_SetDisplayScale(IVS_INT32 iSessionID, IVS_ULONG ulHandle,IVS_INT32 iDisplayScale);

	/**************************************************************************
    * name			: IVS_SDK_GetNVRList
    * description	: ��ѯNVR�豸�б�
    * input			: iSessionID     ��¼�ɹ���ĻỰID
						  pDomainCode    �����
						  uiServerType   NVR���ͣ������������£�
                                  0 ȫ��
                                  1 NVR
                                  2 TAS
                                  3 MBS
						  pIndexRange    ��ҳ����
						  uiBufferSize   �����С
    * output		: pNvrList       Nvr�б�      
    * return		: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
    * remark		: NA
    **************************************************************************/
	IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_GetNVRList(IVS_INT32 iSessionID, 
		                                                const IVS_CHAR* pDomainCode,
		                                                IVS_UINT32 uiServerType,
		                                                const IVS_INDEX_RANGE* pIndexRange,
		                                                IVS_DEVICE_BRIEF_INFO_LIST* pNvrList,
		                                                IVS_UINT32 uiBufferSize);

	/**************************************************************************
    * name			: IVS_SDK_SetDeviceConfig
    * description	: �����豸����
    * input			: iSessionID        ��¼�ɹ���ĻỰID
						  pDevCode          �豸����
						  uiConfigType      �������ͣ�ֵ�ο�IVS_CONFIG_TYPE
						  pBuffer           ���ݻ��棬ʹ�õ����ݽṹ��ο�IVS_CONFIG_TYPE��˵��
						  uiBufferSize      �����С
    * output		: NA        
    * return		: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
    * remark		: NA
    **************************************************************************/
    IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_SetDeviceConfig(IVS_INT32 iSessionID,
                                                             const IVS_CHAR* pDevCode, 
                                                             IVS_UINT32 uiConfigType,
                                                             IVS_VOID* pBuffer,
                                                             IVS_UINT32 uiBufSize);

	/**************************************************************************
    * name			: IVS_SDK_GetDeviceConfig
    * description	: ��ȡ�豸����
    * input			: iSessionID        ��¼�ɹ���ĻỰID
						  pDevCode          �豸����
						  uiConfigType      �������ͣ�ֵ�ο�IVS_CONFIG_TYPE
						  uiBufferSize      �����С
    * output		: pBuffer           ���ݻ��棬ʹ�õ����ݽṹ��ο�IVS_CONFIG_TYPE��˵��       
    * return		: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
    * remark		: NA
    **************************************************************************/
    IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_GetDeviceConfig(IVS_INT32 iSessionID,
                                                             const IVS_CHAR* pDevCode,
                                                             IVS_UINT32 uiConfigType,
                                                             IVS_VOID* pBuffer,
                                                             IVS_UINT32 uiBufSize);

  /**************************************************************************
    * name			: IVS_SDK_StartPlatformRecord
    * description	: ��ʼƽ̨¼��
    * input			: iSessionID      ��¼�ɹ���ĻỰID
						  pCameraCode     ��ʼƽ̨¼������������
						  iRecordTime     ¼��ʱ������λ�룬������300 ~ 43200��12Сʱ��
    * return		: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
    * remark		: NA
	**************************************************************************/
  IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_StartPlatformRecord(IVS_INT32 iSessionID,const IVS_CHAR* pCameraCode,IVS_INT32 iRecordTime);

  /**************************************************************************
    * name			: IVS_SDK_StopPlatformRecord
    * description	: ֹͣƽ̨¼��
    * input			: iSessionID      ��¼�ɹ���ĻỰID
						  pCameraCode     ֹͣƽ̨¼������������
    * return		: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
    * remark		: NA
  **************************************************************************/
  IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_StopPlatformRecord(IVS_INT32 iSessionID,const IVS_CHAR* pCameraCode);

  /**************************************************************************
  * name			: IVS_SDK_StartPURecord(
  * description	: ��ʼǰ��¼��
  * input			: iSessionID      ��¼�ɹ���ĻỰID
						  pCameraCode     ��ʼǰ��¼������������
						  iRecordTime     ¼��ʱ��
  * return			: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
  * remark			: NA
  **************************************************************************/
  IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_StartPURecord(IVS_INT32 iSessionID,const IVS_CHAR* pCameraCode,IVS_INT32 iRecordTime);

  /**************************************************************************
    * name			: IVS_SDK_StopPURecord
    * description	: ֹͣǰ��¼��
    * input			: iSessionID      ��¼�ɹ���ĻỰID
						  pCameraCode     ֹͣƽ̨¼������������
    * return		: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
    * remark		: NA
  **************************************************************************/
  IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_StopPURecord(IVS_INT32 iSessionID,const IVS_CHAR* pCameraCode);

  /**************************************************************************
   * name			: IVS_SDK_StartLocalRecord
   * description	: ��ʼ����¼��
   * input			: iSessionID     ��¼�ɹ���ĻỰID
						  pRecordParam   ����¼�����
						  ulPlayHandle   ���ž��
						  pSaveFileName  �����ļ���
   * return			: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
   * remark		: NA
   **************************************************************************/
   IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_StartLocalRecord(IVS_INT32 iSessionID,
	                                                         const IVS_LOCAL_RECORD_PARAM* pRecordParam, 
                                                             IVS_ULONG ulPlayHandle, 
                                                             const IVS_CHAR* pSaveFileName);

  /**************************************************************************
   * name			: IVS_SDK_StopLocalRecord
   * description	: ֹͣ����¼��
   * input			: iSessionID      ��¼�ɹ���ĻỰID
						  ulPlayHandle    ���ž��
   * return			: �ɹ�����0��IVS_SUCCEED���� ʧ�ܷ��ش�����
   * remark		: NA
   **************************************************************************/
   IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_StopLocalRecord(IVS_INT32 iSessionID, IVS_ULONG ulPlayHandle);

  /******************************************************************
  function		: IVS_SDK_GetDomainRoute
  description	: ��ѯ��·����Ϣ
  input			: iSessionID       ��¼�ɹ���ĻỰID
					  uiBufferSize     �����С
  output			: pDomainRouteList ·����Ϣ�б�
  return			: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
  *******************************************************************/  
  IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_GetDomainRoute( IVS_INT32 iSessionID, 
                          IVS_DOMAIN_ROUTE_LIST* pDomainRouteList,
                          IVS_UINT32 uiBufferSize);
						  
  /******************************************************************
  function   : IVS_SDK_GetPTZAbsPosition
  description: ��ȡ��̨��ǰλ��
  input      : iSessionID ��¼�ɹ��󷵻صĻỰID
			   pDomainCode �����
               pCameraCode ���������
  output     : pPTZPosInfo ��̨λ����Ϣ
  return     : �ɹ�����0��ʧ�ܷ��ش�����
  *******************************************************************/
  IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_GetPTZAbsPosition(IVS_INT32 iSessionID,
	  const IVS_CHAR* pDomainCode, const IVS_CHAR* pCameraCode, IVS_PTZ_ABSPOSITION *pPtzAbsPosition);

  /******************************************************************
  function		: IVS_SDK_PtzControl
  description	: �ƾ�����
  input			: iSessionID    ��¼�ɹ���ĻỰID
					  pCameraCode   ���������
					  iControlCode  ��̨�����룬ֵ�ο�IVS_PTZ_CODE
					  pControlPara1 ����1
					  pControlPara2 ����2
  output			: pLockStatus   ��̨����״̬��0-������1-����
  return			: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
  *******************************************************************/
  IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_PtzControl(IVS_INT32 iSessionID,const IVS_CHAR* pCameraCode, IVS_INT32 iControlCode,const IVS_CHAR* pControlPara1,const IVS_CHAR* pControlPara2, IVS_UINT32* pLockStatus);

  /******************************************************************
	function		: IVS_SDK_PtzControlWithLockerInfo
	description: �ƾ�����
	input			: iSessionID ��¼�ɹ��󷵻صĻỰID
					  pCameraCode ���������
					  iControlCode ��̨������
					  pControlPara1 ����1
					  pControlPara2 ����2
	output		: pPtzControlInfo ��̨������Ϣ
	return		: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
	*******************************************************************/
	IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_PtzControlWithLockerInfo(IVS_INT32 iSessionID,
															  const IVS_CHAR* pCameraCode, 
															  IVS_INT32 iControlCode,
															  const IVS_CHAR* pControlPara1,
															  const IVS_CHAR* pControlPara2, 
															  IVS_PTZ_CONTROL_INFO* pPtzControlInfo);

    /*************************************************************************
	* name			: IVS_SDK_PlaySound
	* description	: ������·����
	* input			: iSessionID   ��¼�ɹ���ĻỰID, 
						  uiPlayHandle ���ž��
	* output		: NA
	* return		: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
	* remark		: NA
	*************************************************************************/
    IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_PlaySound(IVS_INT32 iSessionID, IVS_UINT32 uiPlayHandle);

    /*************************************************************************
	* name			: IVS_SDK_StopSound
	* description	: ֹͣ������·����
	* input			: iSessionID   ��¼�ɹ���ĻỰID, 
						  uiPlayHandle ���ž��
	* output		: NA
	* return		: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
	* remark		: NA
	*************************************************************************/
    IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_StopSound(IVS_INT32 iSessionID, IVS_UINT32 uiPlayHandle);


    /*************************************************************************
	* name			: IVS_SDK_SetVolume
	* description	: ��������
	* input			: iSessionID    ��¼�ɹ���ĻỰID, 
						  uiPlayHandle  ���ž��
						  uiVolumeValue ������ȡֵ��Χ0~100
	* output		: NA
	* return		: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
	* remark		: NA
	*************************************************************************/
    IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_SetVolume(IVS_INT32 iSessionID,
                                                       IVS_UINT32 uiPlayHandle, 
                                                       IVS_UINT32 uiVolumeValue);


    /*************************************************************************
	* name			: IVS_SDK_GetVolume
	* description	: ��ȡ����
	* input			: iSessionID    ��¼�ɹ���ĻỰID, 
						  uiPlayHandle  ���ž��
	* output		: puiVolumeValue ������ȡֵ��Χ0~100
	* return		: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
	* remark		: NA
	*************************************************************************/
    IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_GetVolume(IVS_INT32 iSessionID,
                                                       IVS_UINT32 uiPlayHandle, 
                                                       IVS_UINT32* puiVolumeValue);

	/**************************************************************************
    * name			: IVS_SDK_LocalSnapshot
    * description	: ����ץ�ĵ���ͼƬ
    * input			: iSessionID      ��¼�ɹ���ĻỰID
						  ulPlayHandle    ���ž��
						  uiPictureFormat ͼƬ��ʽ��1-JPG��2-BMP
						  pFileName	   ץ��ͼƬ����·������󳤶�Ϊ256�ֽڣ�������׺�ͽ����������ļ���׺����ͼƬ��ʽ����һ�£�.jpg��.bmp��
	* output		: NA
    * return		: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
	* remark		: NA
    **************************************************************************/
	IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_LocalSnapshot(IVS_INT32 iSessionID, IVS_ULONG ulPlayHandle, IVS_UINT32 uiPictureFormat, const IVS_CHAR* pFileName);
	
	/**************************************************************************
    * name			: IVS_SDK_AddPTZPreset
    * description	: ����Ԥ��λ
    * input			: iSessionID    ��¼�ɹ���ĻỰID
						  pCameraCode   ���������
						  pPTZPreset    Ԥ��λ����
	* output		: uiPresetIndex Ԥ��λ������
    * return		: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
	* remark		: NA
    **************************************************************************/
	IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_AddPTZPreset (IVS_INT32 iSessionID, const IVS_CHAR* pCameraCode, const IVS_CHAR* pPresetName, IVS_UINT32* uiPresetIndex);

	/**************************************************************************
    * name			: IVS_SDK_DelPTZPreset
    * description	: ɾ��Ԥ��λ
    * input			: iSessionID    ��¼�ɹ���ĻỰID
						  pCameraCode   ���������
						  uiPresetIndex Ԥ��λ����
	* output		: NA
    * return		: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
	* remark		: NA
    **************************************************************************/
	IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_DelPTZPreset (IVS_INT32 iSessionID, const IVS_CHAR* pCameraCode, IVS_UINT32 uiPresetIndex);

	/**************************************************************************
    * name			: IVS_SDK_ModPTZPreset
    * description	: �޸�Ԥ��λ
    * input			: iSessionID  ��¼�ɹ���ĻỰID
						  pCameraCode ���������
						  pPTZPreset  Ԥ��λ��Ϣ
	* output		: NA
    * return		: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
	* remark		: NA
    **************************************************************************/
	IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_ModPTZPreset (IVS_INT32 iSessionID, const IVS_CHAR* pCameraCode, const IVS_PTZ_PRESET* pPTZPreset);

	/**************************************************************************
    * name			: IVS_SDK_GetPTZPresetList
    * description	: ��ѯԤ��λ�б�
    * input			: iSessionID     ��¼�ɹ���ĻỰID
						  pCameraCode    ���������
						  pPTZPresetList Ԥ��λ��Ϣ�б����128������Ԥ�ȷ���128�����ڴ�ռ䣩
						  uiBufferSize   �����С
	* output		: uiPTZPresetNum ʵ��Ԥ��λ����
    * return		: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
	* remark		: NA
    **************************************************************************/
	IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_GetPTZPresetList (IVS_INT32 iSessionID, const IVS_CHAR* pCameraCode, IVS_PTZ_PRESET* pPTZPresetList, IVS_UINT32 uiBufferSize, IVS_UINT32* uiPTZPresetNum);

	/**************************************************************************
    * name			: IVS_SDK_SetGuardPos
    * description	: ���ÿ���λ
    * input			: iSessionID    ��¼�ɹ���ĻỰID
						  pCameraCode   ���������
						  pGuardPosInfo ����λ��Ϣ
	* output		: NA
    * return		: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
	* remark		: NA
    **************************************************************************/
	IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_SetGuardPos (IVS_INT32 iSessionID, const IVS_CHAR* pCameraCode, const IVS_GUARD_POS_INFO* pGuardPosInfo);

	/**************************************************************************
    * name			: IVS_SDK_DelGuardPos
    * description	: ɾ������λ
    * input			: iSessionID    ��¼�ɹ���ĻỰID
						  pCameraCode   ���������
						  uiPresetIndex Ԥ��λ����
	* output		: NA
    * return		: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
	* remark		: NA
    **************************************************************************/
	IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_DelGuardPos (IVS_INT32 iSessionID, const IVS_CHAR* pCameraCode, IVS_UINT32 uiPresetIndex);

	/**************************************************************************
    * name			: IVS_SDK_GetGuardPos
    * description	: ��ȡ����λ
    * input			: iSessionID    ��¼�ɹ���ĻỰID
						  pCameraCode   ���������
	* output		: pGuardPosInfo ����λ��Ϣ
    * return		: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
	* remark		: NA
    **************************************************************************/
	IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_GetGuardPos (IVS_INT32 iSessionID, const IVS_CHAR* pCameraCode, IVS_GUARD_POS_INFO* pGuardPosInfo);

	/**************************************************************************
    * name			: IVS_SDK_AddCruiseTrack
    * description	: ����Ѳ���켣
    * input			: iSessionID       ��¼�ɹ���ĻỰID
						  pCameraCode      ���������
						  pCuriseTrackInfo Ѳ���켣��Ϣ
	* output		: uiTrackIndex �켣����
    * return		: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
	* remark		: NA
    **************************************************************************/
	IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_AddCruiseTrack (IVS_INT32 iSessionID, const IVS_CHAR* pCameraCode, const IVS_CRUISE_TRACK* pCuriseTrackInfo, IVS_UINT32* uiTrackIndex);

	/**************************************************************************
    * name			: IVS_SDK_DelCruiseTrack
    * description	: ɾ��Ѳ���켣
    * input			: iSessionID   ��¼�ɹ���ĻỰID
						  pCameraCode  ���������
						  uiTrackIndex �켣����
						  uiCruiseType �켣���ͣ�1-�켣Ѳ�� 2-ģʽѲ��
	* output		: NA
    * return		: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
	* remark		: NA
    **************************************************************************/
	IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_DelCruiseTrack (IVS_INT32 iSessionID, const IVS_CHAR* pCameraCode, IVS_UINT32 uiTrackIndex, IVS_UINT32 uiCruiseType);

	/**************************************************************************
    * name			: IVS_SDK_ModCruiseTrack 
    * description	: �޸�Ѳ���켣
    * input			: iSessionID       ��¼�ɹ���ĻỰID
						  pCameraCode      ���������
						  pCuriseTrackInfo Ѳ���켣��Ϣ
	* output		: NA
    * return		: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
	* remark		: NA
    **************************************************************************/
	IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_ModCruiseTrack (IVS_INT32 iSessionID, const IVS_CHAR* pCameraCode, const IVS_CRUISE_TRACK* pCuriseTrackInfo);

	/**************************************************************************
    * name			: IVS_SDK_GetCruiseTrackList
    * description	: ��ѯѲ���켣�б�
    * input			: iSessionID           ��¼�ɹ���ĻỰID
						  pCameraCode          ���������
						  pCruiseTrackInfoList Ѳ���켣�б�ע����ʱ�����ع켣����Ϣ�������16�������ⲿ���÷����㹻�ռ�
						  uiBufferSize         �����С
	* output		: uiCruiseTrackNum     ʵ�ʲ�ѯ����Ѳ���켣����
    * return		: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
	* remark		: NA
    **************************************************************************/
	IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_GetCruiseTrackList (IVS_INT32 iSessionID, const IVS_CHAR* pCameraCode, IVS_CRUISE_TRACK* pCruiseTrackList, IVS_UINT32 uiBufferSize, IVS_UINT32* uiCruiseTrackNum);

	/**************************************************************************
    * name			: IVS_SDK_GetCruiseTrack
    * description	: ��ѯѲ���켣��Ϣ
    * input			: iSessionID   ��¼�ɹ���ĻỰID
						  pCameraCode  ���������
						  uiTrackIndex �켣����
	* output		: pCruiseTrackInfo Ѳ���켣��Ϣ
    * return		: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
	* remark		: NA
    **************************************************************************/
	IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_GetCruiseTrack (IVS_INT32 iSessionID, const IVS_CHAR* pCameraCode, IVS_INT32 uiTrackIndex, IVS_CRUISE_TRACK* pCruiseTrackInfo);

	/**************************************************************************
    * name			: IVS_SDK_SetCruisePlan
    * description	: ����Ѳ���ƻ�
    * input			: iSessionID   ��¼�ɹ���ĻỰID
						  pCameraCode  ���������
						  pCruisePlan  Ѳ���ƻ�
	* output		: NA
    * return		: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
	* remark		: NA
    **************************************************************************/
	IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_SetCruisePlan (IVS_INT32 iSessionID, const IVS_CHAR* pCameraCode, const IVS_CRUISE_PLAN* pCruisePlan);

	/**************************************************************************
    * name			: IVS_SDK_GetCruisePlan
    * description	: ��ѯѲ���ƻ�
    * input			: iSessionID   ��¼�ɹ���ĻỰID
						  pCameraCode  ���������
	* output		: pCruisePlan  Ѳ���ƻ�
    * return		: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
	* remark		: NA
    **************************************************************************/
	IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_GetCruisePlan (IVS_INT32 iSessionID, const IVS_CHAR* pCameraCode, IVS_CRUISE_PLAN* pCruisePlan);

	/**************************************************************************
    * name			: IVS_SDK_PlatformSnapshot
    * description	: ƽ̨ץ�� 
    * input			: iSessionID  ��¼�ɹ���ĻỰID
						  pCameraCode ���������
	* output		: NA
    * return		: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
	* remark		: NA
    **************************************************************************/
	IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_PlatformSnapshot(IVS_INT32 iSessionID,const IVS_CHAR* pCameraCode);

	/*****************************************************************
    * name			: IVS_SDK_GetSnapshotList 
    * description	: �ӷ�������ȡͼƬ�б� 
    * input			: iSessionID    ��¼�ɹ���ĻỰID
						  pCameraCode   ���������
						  pQueryParam   ץ��ͼƬ��ѯ����
						  uiBufSize     �����С
	* output		: pSnapshotList ץ��ͼƬ�б���Ϣ
    * return		: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
	* remark		: NA
	*****************************************************************/
	IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_GetSnapshotList(IVS_INT32 iSessionID,
															 const IVS_CHAR* pCameraCode,
															 const IVS_QUERY_SNAPSHOT_PARAM* pQueryParam,
															 IVS_SNAPSHOT_INFO_LIST* pSnapshotList,
															 IVS_UINT32 uiBufSize);

    /*************************************************************************
	* name			: IVS_SDK_StartVoiceTalkback
	* description	: ��ʼ�����Խ�
	* input			: iSessionID     ��¼�ɹ���ĻỰID
						  pTalkbackParam �����Խ�������ע��Ŀǰֻ֧��UDP��ʽ��
						  pCameraCode    ���������
	* output		: pHandle        �Խ����
	* return		: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
	* remark		: NA
	*************************************************************************/
    IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_StartVoiceTalkback(
                                IVS_INT32 iSessionID,
                                const IVS_VOICE_TALKBACK_PARAM* pTalkbackParam,
                                const IVS_CHAR* pCameraCode,
                                IVS_ULONG* pHandle);

    /*************************************************************************
	* name			: IVS_SDK_StopVoiceTalkback
	* description	: ֹͣ�����Խ�
	* input			: iSessionID   ��¼�ɹ���ĻỰID
						  ulHandle     �Խ����
	* output		: NA
	* return		: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
	* remark		: NA
	*************************************************************************/
    IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_StopVoiceTalkback(
                                                          IVS_INT32 iSessionID,
                                                          IVS_ULONG ulHandle);

    /**************************************************************************
    * name			: IVS_SDK_SetMicVolume
    * description	: ������˷�����
    * input			: uiVolumeValue ����ֵ����Χ0~100
    * output		: NA
    * return		: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
    * remark		: NA
    **************************************************************************/
    IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_SetMicVolume(IVS_UINT32 uiVolumeValue);

    /**************************************************************************
    * name			: IVS_SDK_GetMicVolume
    * description	: ��ȡ��˷�����
    * input			: NA
    * output		: NA
    * return		: ����ֵ����Χ0~100
    * remark		: NA
    **************************************************************************/
    IVS_SDK_API IVS_UINT32 __SDK_CALL IVS_SDK_GetMicVolume();

    /*************************************************************************
	* name			: IVS_SDK_StartRealBroadcast
	* description	: ��ʼʵʱ�����㲥
	* input			: iSessionID   ��¼�ɹ���ĻỰID
	* output		: NA
	* return		: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
	* remark		: NA
	*************************************************************************/
    IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_StartRealBroadcast(IVS_INT32 iSessionID);

    /*************************************************************************
	* name			: IVS_SDK_StopRealBroadcast
	* description	: ֹͣʵʱ�����㲥
	* input			: iSessionID   ��¼�ɹ���ĻỰID
	* output		: NA
	* return		: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
	* remark		: NA
	*************************************************************************/
    IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_StopRealBroadcast(IVS_INT32 iSessionID);

    /*************************************************************************
	* name			: IVS_SDK_StartFileBroadcast
	* description	: ��ʼ�ļ������㲥
	* input			: iSessionID ��¼�ɹ���ĻỰID, 
						  pFileName  ��Ƶ�ļ���,
						  bCycle     �Ƿ�ѭ�����ţ�0-��ѭ����1-ѭ��
	* output		: NA
	* return		: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
	* remark		: NA
	*************************************************************************/
    IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_StartFileBroadcast(
                                                    IVS_INT32 iSessionID,
                                                    const IVS_CHAR* pFileName,
                                                    IVS_BOOL bCycle);

    /*************************************************************************
	* name			: IVS_SDK_StopFileBroadcast
	* description	: ֹͣ�ļ������㲥
	* input			: iSessionID   ��¼�ɹ���ĻỰID, 
	* output		: NA
	* return		: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
	* remark		: NA
	*************************************************************************/
    IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_StopFileBroadcast(IVS_INT32 iSessionID);

    /*************************************************************************
	* name			: IVS_SDK_AddBroadcastDevice
	* description	: ��ӹ㲥�豸
	* input			: iSessionID  ��¼�ɹ���ĻỰID, 
						  pCameraCode ���������
	* output		: NA
	* return		: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
	* remark		: NA
	*************************************************************************/
    IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_AddBroadcastDevice(
                                                   IVS_INT32 iSessionID,
                                                   const IVS_CHAR* pCameraCode);

    /*************************************************************************
	* name			: IVS_SDK_DeleteBroadcastDevice
	* description	: ɾ���㲥�豸
	* input			: iSessionID  ��¼�ɹ���ĻỰID, 
						  pCameraCode ���������
	* output		: NA
	* return		: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
	* remark		: NA
	*************************************************************************/
    IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_DeleteBroadcastDevice (
                                                   IVS_INT32 iSessionID,
                                                   const IVS_CHAR* pCameraCode);
												   
	/*****************************************************************
	* name       : IVS_SDK_AddRecordBackupPlan
	* description: ���¼�񱸷ݼƻ�
	* input      : iSessionID ��¼�ɹ���ĻỰID, 
				   pBackupPlan ¼�񱸷ݼƻ�XML
	* output     : NA
	* return     : �ɹ�����0��ʧ�ܷ��ش�����
	* author     ��zhouqiming z90003203
	* remark     : NA
	* history    : 2013-1-29[add]
	*****************************************************************/
	IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_AddRecordBackupPlan(IVS_INT32 iSessionID, 
		const IVS_CHAR* pBackupPlan);

	/*****************************************************************
	* name       : IVS_SDK_ModifyRecordBackupPlan
	* description: �޸�¼�񱸷ݼƻ�
	* input      : iSessionID ��¼�ɹ���ĻỰID, 
				   pBackupPlan ¼�񱸷ݼƻ�XML
	* output     : NA
	* return     : �ɹ�����0��ʧ�ܷ��ش�����
	* author     ��zhouqiming z90003203
	* remark     : NA
	* history    : 2013-1-29[add]
	*****************************************************************/
	IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_ModifyRecordBackupPlan(IVS_INT32 iSessionID, 
		const IVS_CHAR* pBackupPlan);

	/*****************************************************************
	* name       : IVS_SDK_DeleteRecordBackupPlan
	* description: ɾ��¼�񱸷ݼƻ�
	* input      : iSessionID ��¼�ɹ���ĻỰID, 
				   pBackupPlan ¼�񱸷ݼƻ�XML
	* output     : NA
	* return     : �ɹ�����0��ʧ�ܷ��ش�����
	* author     ��zhouqiming z90003203
	* remark     : NA
	* history    : 2013-1-29[add]
	*****************************************************************/
	IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_DeleteRecordBackupPlan(IVS_INT32 iSessionID, 
		const IVS_CHAR* pBackupPlan);

	/*****************************************************************
	* name       : IVS_SDK_GetRecordBackupPlan
	* description: ��ѯ¼�񱸷ݼƻ�
	* input      : iSessionID ��¼�ɹ���ĻỰID, 
				   pQueryInfo ��ѯ����XML
	* output     : pBackupPlan ¼�񱸷ݼƻ�������ϢXML
	* return     : �ɹ�����0��ʧ�ܷ��ش�����
	* author     ��zhouqiming z90003203
	* remark     : NA
	* history    : 2013-1-29[add]
	*****************************************************************/
	IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_GetRecordBackupPlan(IVS_INT32 iSessionID, 
		const IVS_CHAR* pQueryInfo, 
		IVS_CHAR** pBackupPlan);

	/*****************************************************************
    * name			: IVS_SDK_GetAlarmLinkageAction
    * description	: ��ѯ�澯������������
	* input			: iSessionID ��¼�ɹ���ĻỰID
						  pReqXml    ������Ϣ
	* output		: pRspXml    ��Ӧ��Ϣ
    * return		: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
	* remark		: pRspXmlʹ������ڴ���Ҫ����IVS_SDK_ReleaseBuffer�ӿڻ���
	*****************************************************************/	
	IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_GetAlarmLinkageAction(IVS_INT32 iSessionID, const IVS_CHAR* pReqXml, IVS_CHAR** pRsqXml);

	/**************************************************************************
    * name			: IVS_SDK_GetAlarmLinkageAction_S
    * description	: ��ѯ�澯�����������飨��ȫ������
    * input			: iSessionID ��¼�ɹ���ĻỰID
	* input			: pReqXml ��ѯ����
	* output		: pRsqXml ��ѯ���ĸ澯������������
    * return		: �ɹ�����IVS_SUCCESSED��ʧ�ܷ��ش�����
	* remark		: pRspXmlʹ������ڴ���Ҫ����IVS_SDK_ReleaseBuffer�ӿڻ���
	* history		: 2017-1-9
    **************************************************************************/
	IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_GetAlarmLinkageAction_S(IVS_INT32 iSessionID, const IVS_CHAR* pReqXml, IVS_CHAR** pRsqXml);
	
	/*****************************************************************
	* name			: IVS_SDK_DeleteSnapshot
	* description	: ɾ��ƽ̨ץ��ͼƬ
	* input			: iSessionID  ��¼�ɹ���ĻỰID
						  pCameraCode ���������
						  uiPictureID ͼƬID
	* output		: NA
	* return		: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
	* remark		: NA
	*****************************************************************/
	IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_DeleteSnapshot(IVS_INT32 iSessionID, const IVS_CHAR* pCameraCode, IVS_UINT32 uiPictureID);

	/******************************************************************
    function		: IVS_SDK_SetLogPath
    description: ������־��Ŀ¼
    input			: pLogPath ��־��Ŀ¼
    return		: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
    *******************************************************************/
    IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_SetLogPath(const IVS_CHAR* pLogPath);

	/*****************************************************************
	function		: IVS_SDK_StartSearchDevice
	description	: ��������ǰ���豸
	input			: iSessionID   ��¼�ɹ���ĻỰID
					  pDomainCode  Ŀ�������
					  pSearchInfo �豸������ϢXML
	output		: NA
	return		: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
	*****************************************************************/
	IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_StartSearchDevice(IVS_INT32 iSessionID, const IVS_CHAR* pDomainCode, const IVS_CHAR* pSearchInfo);

	/*****************************************************************
	function		: IVS_SDK_StopSearchDevice
	description	: ֹͣ����ǰ���豸
	input			: iSessionID   ��¼�ɹ���ĻỰID
					  pDomainCode  Ŀ�������
					  pSearchInfo �豸������ϢXML
	output		: NA
	return		: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
	*****************************************************************/
	IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_StopSearchDevice(IVS_INT32 iSessionID, const IVS_CHAR* pDomainCode, const IVS_CHAR* pSearchInfo);

	/*****************************************************************
	function		: IVS_SDK_VerifyDevice
	description	: ��֤ǰ���豸
	input			: iSessionID   ��¼�ɹ���ĻỰID
					  pDomainCode  Ŀ�������
					  pVerifyInfo �豸��֤��ϢXML
	output		: pRspXml   ��֤���XML 
	return		: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
	*****************************************************************/
	IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_VerifyDevice(IVS_INT32 iSessionID, const IVS_CHAR* pDomainCode, const IVS_CHAR* pVerifyInfo, IVS_CHAR** pRspXml);

	/*************************************************************************
	* name			: IVS_SDK_AddDevice
	* description	: �����豸
	* input			: iSessionID ��¼�ɹ���ĻỰID
						  pDomainCode �����
						  uiDeviceNum �豸����
						  pDevList �豸�б�
						  uiResultBufferSize ����б����С
	* output		: pResultList ����б�
	* return		: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
	*************************************************************************/
    IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_AddDevice(IVS_INT32 iSessionID, const IVS_CHAR* pDomainCode,  IVS_UINT32 uiDeviceNum, 
		const IVS_DEVICE_OPER_INFO* pDevList, IVS_DEVICE_OPER_RESULT_LIST* pResultList, IVS_UINT32 uiResultBufferSize);

	/*************************************************************************
	* name			: IVS_SDK_DeleteDevice
	* description	: ɾ���豸
	* input			: iSessionID ��¼�ɹ���ĻỰID
						  pDomainCode �����
						  uiDeviceNum �豸����
						  pDevList �豸�б�
						  uiResultBufferSize ����б����С
	* output		: pResultList ����б�
	* return		: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
	*************************************************************************/
	IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_DeleteDevice(IVS_INT32 iSessionID,const IVS_CHAR* pDomainCode,IVS_UINT32 uiDeviceNum,
		const IVS_DEVICE_CODE* pDevCodeList, IVS_RESULT_LIST* pResultList,IVS_UINT32 uiResultBufferSize);

	/**************************************************************************
    * name			: IVS_SDK_RebootDevice
    * description	: ����ǰ���豸
    * input			: iSessionID ��¼�ɹ���ĻỰID
						  pDeviceCode  ���豸����
						  uiRebootType �������ͣ�0-���� 1-�ָ�Ĭ�����ò�����
	* output		: NA
    * return		: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
    **************************************************************************/
	IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_RebootDevice (IVS_INT32 iSessionID, const IVS_CHAR* pDeviceCode, IVS_UINT32 uiRebootType);

	/*************************************************************************
	* name			: IVS_SDK_SetMainDeviceName
	* description	: �޸����豸����
	* input			: iSessionID ��¼�ɹ���ĻỰID
						  pDevCode ���豸����
						  pNewDevName ���豸�µ�����
	* output		: NA
	* return		: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
	*************************************************************************/
	IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_SetMainDeviceName(	IVS_INT32 iSessionID, const IVS_CHAR* pDevCode, const IVS_CHAR* pNewDevName);

	/*************************************************************************
	* name			: IVS_SDK_SetCameraName
	* description	: �޸����������
	* input			: iSessionID ��¼�ɹ���ĻỰID, 
						  pCameraCode ���������
						  pNewCameraName ������µ�����
	* output		: NA
	* return		: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
	*************************************************************************/
	IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_SetCameraName(	IVS_INT32 iSessionID, const IVS_CHAR* pCameraCode, const IVS_CHAR* pNewCameraName);

	/******************************************************************
	function		: IVS_SDK_SetDevPWD
	description: ����ǰ���豸����
	input			: iSessionID  ��¼�ɹ��󷵻صĻỰID
					  pDevCode  �豸���룻
					  pDevUserName    �豸��¼�û���
					  pDevPWD  �豸��¼����
					  pDevRegPWD  �豸��ƽ̨ע������
	output		: NA
	return		: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
	*******************************************************************/
  IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_SetDevPWD(IVS_INT32 iSessionID, const IVS_CHAR* pDevCode, const IVS_CHAR* pDevUserName, const IVS_CHAR* pDevPWD, const IVS_CHAR* pDevRegPWD);

	/******************************************************************
    function		: IVS_SDK_GetChannelList
    description: �������豸��ѯ���豸�б�
    input			: iSessionID  ��¼�ɹ��󷵻صĻỰID
					  pDevCode   ���豸����
					  uiBufferSize �����С
    output		: pChannelList  ���豸�����豸�б�
    return		: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
    *******************************************************************/
    IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_GetChannelList(IVS_INT32 iSessionID, const IVS_CHAR* pDevCode, IVS_DEV_CHANNEL_BRIEF_INFO_LIST* pChannelList, IVS_UINT32 uiBufferSize);

	/**************************************************************************
    * name			: IVS_SDK_SetPlayQualityMode
    * description	: ����ʵ������ģʽ������������
    * input			: iSessionID   ��¼�ɹ���ĻỰID
						  ulHandle   ҵ����������ʵ�����ط�
						  iPlayQualityMode  ����ģʽ �ο���IVS_PLAY_QUALITY_MODE
    * output		: NA
    * return		: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
    * remark		: NA
    **************************************************************************/
	IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_SetPlayQualityMode(IVS_INT32 iSessionID, IVS_ULONG ulHandle,IVS_INT32 iPlayQualityMode);

	/*****************************************************************
	* name       : IVS_SDK_GetRecordBackupTaskList
	* description: ��ѯ¼�񱸷������б�
	* input      : iSessionID ��¼�ɹ���ĻỰID
				   pQueryInfo ��ѯ����xml
	* output     : pRspXml ��ѯ¼�񱸷������б�����ϢXML
	* return     : �ɹ�����IVS_SUCCESSED��ʧ�ܷ��ش�����
	* author     ��
	* remark     : NA
	* history    : 2013-3-5
	*****************************************************************/
	IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_GetRecordBackupTaskList(IVS_INT32 iSessionID, 
		const IVS_CHAR* pQueryInfo, 
		IVS_CHAR** pRspXml);

	/*****************************************************************
	* name       : IVS_SDK_StartRecordBackupTask
	* description: ����/����¼�񱸷�����
	* input      : iSessionID ��¼�ɹ���ĻỰID
				   pTaskInfo ������Ϣxml
	* output     : NA
	* return     : �ɹ�����IVS_SUCCESSED��ʧ�ܷ��ش�����
	* author     ��
	* remark     : NA
	* history    : 2013-3-5
	*****************************************************************/
	IVS_SDK_API IVS_INT32 __SDK_CALL  IVS_SDK_StartRecordBackupTask (IVS_INT32 iSessionID, 
		const IVS_CHAR* pTaskInfo);

	/*****************************************************************
	* name       : IVS_SDK_StopRecordBackupTask
	* description: ��ͣ/ֹͣ¼�񱸷�����
	* input      : iSessionID ��¼�ɹ���ĻỰID
				   pTaskInfo ������Ϣxml
	* output     : NA
	* return     : �ɹ�����IVS_SUCCESSED��ʧ�ܷ��ش�����
	* author     ��
	* remark     : NA
	* history    : 2013-3-5
	*****************************************************************/
	IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_StopRecordBackupTask (IVS_INT32 iSessionID, 
		const IVS_CHAR* pTaskInfo);

	/*****************************************************************
	* name       : IVS_SDK_DeleteRecordBackupTask
	* description: ɾ��¼�񱸷�����
	* input      : iSessionID ��¼�ɹ���ĻỰID
				   pTaskInfo ������Ϣxml
	* output     : NA
	* return     : �ɹ�����IVS_SUCCESSED��ʧ�ܷ��ش�����
	* author     ��
	* remark     : NA
	* history    : 2013-3-5
	*****************************************************************/
	IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_DeleteRecordBackupTask (IVS_INT32 iSessionID, 
		const IVS_CHAR* pTaskInfo);

	/*****************************************************************
	* name       : IVS_SDK_AddRecordBackupTask
	* description: ����¼�񱸷�����
	* input      : iSessionID ��¼�ɹ���ĻỰID
				   pBackupTask  ����¼�񱸷�����xml
	* output     : NA
	* return     : �ɹ�����IVS_SUCCESSED��ʧ�ܷ��ش�����
	* author     ��
	* remark     : NA
	* history    : 2013-3-5
	*****************************************************************/	
	IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_AddRecordBackupTask(IVS_INT32 iSessionID, 
		const IVS_CHAR* pBackupTask);

	/**************************************************************************
    * name			: IVS_SDK_StartRealPlayByIP
    * description	: ��ʼʵʱ���
    * input			: iSessionID ��¼�ɹ���ĻỰID
						  pCameraCode  ���������
						  pMediaAddrDst  ý����Ŀ���ַ
	* output		: pMediaAddrSrc ý����Դ��ַ
						  pHandle ���ž����Ψһָ���˲���ͨ����
    * return		: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
    **************************************************************************/
	IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_StartRealPlayByIP(IVS_INT32 iSessionID, 
		const IVS_CHAR* pCameraCode, const IVS_MEDIA_ADDR* pMediaAddrDst, IVS_MEDIA_ADDR* pMediaAddrSrc, IVS_ULONG* pHandle);

	/**************************************************************************
    * name			: IVS_SDK_StopRealPlayByIP
    * description	: ֹͣʵʱ���
    * input			: iSessionID ��¼�ɹ���ĻỰID
						  ulHandle ���ž����Ψһָ���˲���ͨ����
	* output		: NA
    * return		: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
    **************************************************************************/
	IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_StopRealPlayByIP(IVS_INT32 iSessionID, IVS_ULONG ulHandle);

	/**************************************************************************
    * name			: IVS_SDK_StartRealPlayByIPEx
    * description	: ��ʼʵʱ���
    * input			: iSessionID ��¼�ɹ���ĻỰID
						  pRealplayParam  ���Ų���
						  pCameraCode  ���������
						  pMediaAddrDst  ý����Ŀ���ַ
	* output			: pMediaAddrSrc ý����Դ��ַ
						  pHandle ���ž����Ψһָ���˲���ͨ����
    * return			: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
    **************************************************************************/
	IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_StartRealPlayByIPEx(IVS_INT32 iSessionID, 
															const IVS_REALPLAY_PARAM  *pRealplayParam,
															const IVS_CHAR* pCameraCode,
															const IVS_MEDIA_ADDR* pMediaAddrDst,
															IVS_MEDIA_ADDR* pMediaAddrSrc,
															IVS_ULONG* pHandle);

	/**************************************************************************
    * name			: IVS_SDK_StopRealPlayByIPEx
    * description	: ֹͣʵʱ���
    * input			: iSessionID ��¼�ɹ���ĻỰID
						  ulHandle ���ž����Ψһָ���˲���ͨ����
	* output			: NA
    * return			: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
    **************************************************************************/
	IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_StopRealPlayByIPEx(IVS_INT32 iSessionID, IVS_ULONG ulHandle);

	/******************************************************************
	function		: IVS_SDK_GetRecordStatus
	description: ��ѯ¼��״̬
	input			: iSessionID ��¼�ɹ��󷵻صĻỰID
					  pCameraCode ���������
					  uiRecordMethod ¼��ʽ
	output		: pRecordState ¼��״̬
	return		: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
	*******************************************************************/
  IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_GetRecordStatus(IVS_INT32 iSessionID,const IVS_CHAR* pCameraCode,IVS_UINT32 uiRecordMethod,IVS_UINT32* pRecordState);

	/*****************************************************************
	function		: IVS_SDK_GetRecordTask
	description: ��ѯ��ǰ�û����ֶ�¼������
	input			: iSessionID   ��¼�ɹ���ĻỰID
	output		: pRspXml   ��ѯ��ǰ�û����ֶ�¼�����񷵻���ϢXML
	return		: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
	*****************************************************************/
	IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_GetRecordTask(IVS_INT32 iSessionID, IVS_CHAR** pRspXml);

	/*************************************************************************
	* name			: IVS_SDK_AddRealPlayBookmark
	* description	: ����ʵ����ǩ
	* input			: iSessionID ��¼�ɹ���ĻỰID
						  pCameraCode ���������
						  pBookmarkName ��ǩ��
						  pBookmarkTime ��ǩʱ��
	* output		: uiBookmarkID ��ǩID
	* return		: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
	* remark		: NA
	*************************************************************************/
	IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_AddRealPlayBookmark(IVS_INT32 iSessionID,const IVS_CHAR* pCameraCode,
		const IVS_CHAR* pBookmarkName,const IVS_CHAR* pBookmarkTime,IVS_UINT32* uiBookmarkID);

	/*************************************************************************
	* name			: IVS_SDK_ModifyRealPlayBookmark
	* description	: �޸�ʵ����ǩ
	* input			: iSessionID ��¼�ɹ���ĻỰID
						  pCameraCode ���������
						  uiBookmarkID ��ǩID
						  pNewBookmarkName ����ǩ��
	* output		: NA
	* return		: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
	* remark		: NA
	*************************************************************************/
	IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_ModifyRealPlayBookmark(IVS_INT32 iSessionID, 
		const IVS_CHAR* pCameraCode,IVS_UINT32 uiBookmarkID,const IVS_CHAR* pNewBookmarkName);

	/*************************************************************************
	* name			: IVS_SDK_DeleteRealPlayBookmark
	* description	: ɾ��ʵ����ǩ
	* input			: iSessionID ��¼�ɹ���ĻỰID
						  pCameraCode ���������
						  uiBookmarkID ��ǩID
	* output		: NA
	* return		: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
	* remark		: NA
	*************************************************************************/
	IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_DeleteRealPlayBookmark(IVS_INT32 iSessionID,const IVS_CHAR* pCameraCode,IVS_UINT32 uiBookmarkID);

	/*************************************************************************
	* name			: IVS_SDK_GetCurrentFrameTick
	* description	: ��ȡ�ط�ʱ�䣨��ȷ�����룩
	* input			: iSessionID ��¼�ɹ���ĻỰID
						  ulPlayHandle ���ž��
	* output		: pTick �ط�ʱ�䣬��ȷ������
	* return		: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
	* remark		: NA
	*************************************************************************/
	IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_GetCurrentFrameTick(IVS_INT32 iSessionID, IVS_ULONG ulPlayHandle, IVS_UINT64* pTick);

	/*************************************************************************
	* name			: IVS_SDK_AlarmConfirm
	* description	: �澯ȷ��
	* input			: iSessionID ��¼�ɹ���ĻỰID
						  ullAlarmEventID �澯�¼�ID
						  pAlarmInCode �澯Դ����
						  pAlarmOperateInfo �澯������Ϣ�������û�ID��������Ϣ������ʱ��
	* output		: NA
	* return		: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
	* remark		: NA
	*************************************************************************/
	IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_AlarmConfirm(IVS_INT32 iSessionID, IVS_UINT64 ullAlarmEventID, 
		const IVS_CHAR* pAlarmInCode, const IVS_ALARM_OPERATE_INFO* pAlarmOperateInfo);

	/*************************************************************************
	* name			: IVS_SDK_AlarmCancel
	* description	: �澯����
	* input			: iSessionID ��¼�ɹ���ĻỰID
						  ullAlarmEventID �澯�¼�ID
						  pAlarmInCode �澯Դ����
						  pAlarmOperateInfo �澯������Ϣ�������û�ID��������Ϣ������ʱ��
	* output		: NA
	* return		: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
	* remark		: NA
	*************************************************************************/
	IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_AlarmCancel(IVS_INT32 iSessionID, IVS_UINT64 ullAlarmEventID, 
		const IVS_CHAR* pAlarmInCode, const IVS_ALARM_OPERATE_INFO* pAlarmOperateInfo);

	/*************************************************************************
	* name			: IVS_SDK_AlarmCommission
	* description	: �澯��Ȩ
	* input			: iSessionID ��¼�ɹ���ĻỰID
						  pAlarmInCode �澯Դ����
						  pAlarmCommission �澯��Ȩ��Ϣ
	* output		: NA
	* return		: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
	* remark		: NA
	*************************************************************************/
	IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_AlarmCommission (IVS_INT32 iSessionID, 
		const IVS_CHAR* pAlarmInCode, const IVS_ALARM_COMMISSION* pAlarmCommission);

	/*************************************************************************
	* name			: IVS_SDK_UserAlarmAuthorization
	* description	: ��Ȩ�澯�û���֤
	* input			: iSessionID ��¼�ɹ���ĻỰID
						  pPWD �û�����
	* output		: NA
	* return		: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
	* remark		: NA
	*************************************************************************/
	IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_UserAuthentication(IVS_INT32 iSessionID, const IVS_CHAR *pPWD);

	/*************************************************************************
	* name			: IVS_SDK_AlarmReport
	* description	: �澯��Ϣ�ϱ����澯���ͣ�
	* input			: iSessionID  ��¼�ɹ���ĻỰID
						  pAlarmReport  ��Ϣ�ϱ��ṹ��
	* output		: NA
	* return		: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
	* remark		: NA
	*************************************************************************/
	IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_AlarmReport(IVS_INT32 iSessionID, const IVS_ALARM_REPORT* pAlarmReport);

	/******************************************************************
    function		: IVS_SDK_AddUser
    description: ����û�
    input			: iSessionID  ��¼�ɹ���ĻỰID
					  pUserInfo   �û���Ϣ�ṹ��
    output		: puiUserID     ��ӳɹ��󷵻��û�ID
    return		: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
    *******************************************************************/
    IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_AddUser(IVS_INT32 iSessionID, const IVS_USER_INFO* pUserInfo, IVS_UINT32* puiUserID);

    /******************************************************************
    function		: IVS_SDK_ModifyUser
    description: �޸��û�
    input			: iSessionID   ��¼�ɹ���ĻỰID
					  pUserInfo    �û���Ϣ�ṹ��
    return		: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
    *******************************************************************/
    IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_ModifyUser(IVS_INT32 iSessionID, const IVS_USER_INFO* pUserInfo);

    /******************************************************************
    function		: IVS_SDK_DeleteUser
    description: ɾ���û�
    input			: iSessionID   ��¼�ɹ���ĻỰID
					  pDomainCode    �����
					  uiUserID     �û�ID
    return		: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
    *******************************************************************/
    IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_DeleteUser(IVS_INT32 iSessionID, const IVS_CHAR* pDomainCode, IVS_UINT32 uiUserID);

    /******************************************************************
    function		: IVS_SDK_GetUserList
    description: ��ѯ�û��б�
    input			: iSessionID  ��¼�ɹ���ĻỰID
					  pDomainCode �����
					  pUnifiedQuery  ͨ�ò�ѯ����
					  uiBufferSize   �����С
	output		: pUserList   �û���Ϣ�б�
    return		: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
    *******************************************************************/
	IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_GetUserList(IVS_INT32 iSessionID, 
		const IVS_CHAR* pDomainCode, const IVS_QUERY_UNIFIED_FORMAT* pUnifiedQuery, IVS_USER_INFO_LIST* pUserList, IVS_UINT32 uiBufferSize);

    /******************************************************************
    function		: IVS_SDK_GetOnlineUser
    description: ��ѯ�����û��б�
	input			: iSessionID   ��¼�ɹ���ĻỰID
					  pDomainCode �����
					  pUnifiedQuery  ͨ�ò�ѯ����
					  uiBufferSize   �����С
    output		: pOnlineUserList   �����û���Ϣ�б�
    return		: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
    *******************************************************************/
    IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_GetOnlineUser(IVS_INT32 iSessionID, 
		const IVS_CHAR* pDomainCode, const IVS_QUERY_UNIFIED_FORMAT* pUnifiedQuery, IVS_ONLINE_USER_LIST* pOnlineUserList, IVS_UINT32 uiBufferSize);

    /******************************************************************
    function		: IVS_SDK_GetUserInfo
    description: ��ѯ�û���Ϣ
    input			: iSessionID   ��¼�ɹ���ĻỰID
					  pDomainCode    �����
					  uiUserID   �û�ID
    output		: pUserInfo  �û���Ϣ
    return		: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
    *******************************************************************/
    IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_GetUserInfo(IVS_INT32 iSessionID, const IVS_CHAR* pDomainCode, IVS_UINT32 uiUserID, IVS_USER_INFO* pUserInfo);

    /******************************************************************
    function		: IVS_SDK_LockUser
    description: ����/�����û�
    input			: iSessionID   ��¼�ɹ���ĻỰID
					  pDomainCode    �����
					  uiUserID   �û�ID
					  bLock   �Ƿ������û���0-������1-����
    return		: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
    *******************************************************************/
    IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_LockUser(IVS_INT32 iSessionID, const IVS_CHAR* pDomainCode, IVS_UINT32 uiUserID, IVS_BOOL bLock);

	/******************************************************************
    function		: IVS_SDK_SignOutUser
    description: �����û�IDǩ���û������лỰ
    input			: iSessionID  ��¼�ɹ���ĻỰID
					  pDomainCode    �����
					  uiUserID   �û�ID
    return		: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
    *******************************************************************/
    IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_SignOutUser(IVS_INT32 iSessionID, const IVS_CHAR* pDomainCode, IVS_UINT32 uiUserID);

    /******************************************************************
    function		: IVS_SDK_SignOutUserByRole
    description: ���ݽ�ɫIDǩ���û������лỰ
    input			: iSessionID  ��¼�ɹ���ĻỰID
					  pDomainCode    �����
					  uiRoleID  ��ɫID
    return		: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
    *******************************************************************/
    IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_SignOutUserByRole(IVS_INT32 iSessionID, const IVS_CHAR* pDomainCode, IVS_UINT32 uiRoleID);

    /******************************************************************
    function		: IVS_SDK_SignOutOnlineUser
    description: ǩ�������û�
    input			: iSessionID  ��¼�ɹ���ĻỰID
					  pDomainCode    �����
					  uiUserOnlineID      �����û��ĻỰID
    return		: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
    *******************************************************************/
    IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_SignOutOnlineUser(IVS_INT32 iSessionID, const IVS_CHAR* pDomainCode, IVS_UINT32 uiUserOnlineID);

	/******************************************************************
    function		: IVS_SDK_SetUserDeviceList
    description: �����û��豸�б�
    input			: iSessionID   ��¼�ɹ���ĻỰID
					  pDomainCode     �����
					  uiUserID    �û�ID
				      pUserDevList  �û��豸�б�
					  uiBufferSize   �����С
    return		: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
    *******************************************************************/
    IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_SetUserDeviceList(IVS_INT32 iSessionID, 
		const IVS_CHAR* pDomainCode, IVS_UINT32 uiUserID, const IVS_USER_DEVICE_INFO_LIST* pUserDevList, IVS_UINT32 uiBufferSize);

    /******************************************************************
    function		: IVS_SDK_GetUserDeviceList
    description: ��ȡ�û��豸�б�
    input			: iSessionID    ��¼�ɹ���ĻỰID
					  pDomainCode    �����
					  uiUserID  �û�ID
					  pIndexRange   ��ҳ��Ϣ
					  uiBufferSize     �����С
    output		: pUserDevList       �û��豸�б�
    return		: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
    *******************************************************************/
    IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_GetUserDeviceList(IVS_INT32 iSessionID, const IVS_CHAR* pDomainCode, 
		IVS_UINT32 uiUserID, const IVS_INDEX_RANGE* pIndexRange, IVS_USER_DEVICE_INFO_LIST* pUserDevList, IVS_UINT32 uiBufferSize);

	/**************************************************************************
    * name			: IVS_SDK_GetDeviceUserList
    * description	: ��ȡӵ��ָ���豸Ȩ�޵��û��б�
    * input			: iSessionID ��¼�ɹ���ĻỰID
						  pDomainCode �����
						  pDevCode   �豸����
						  uiIsUserOnline �û��Ƿ����ߣ�0-���� 1-���� 2-����
						  pIndexRange ��ҳ��Ϣ
						  uiBufferSize �����С
	* output		: pUserDevList �û��豸�б�
    * return		: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
    **************************************************************************/
	IVS_SDK_API IVS_INT32 __SDK_CALL  IVS_SDK_GetDeviceUserList(IVS_INT32 iSessionID, const IVS_CHAR* pDomainCode, const IVS_CHAR* pDevCode, 
		IVS_UINT32 uiIsUserOnline, const IVS_INDEX_RANGE* pIndexRange, IVS_DEVICE_USER_INFO_LIST* pDevUserList, IVS_UINT32 uiBufferSize);

	/******************************************************************
    function		: IVS_SDK_AddUserGroup
    description	: �����û���
    input			: iSessionID    ��¼�ɹ���ĻỰID
					  pUserGroup   �û�����Ϣ
    output		: puiUserGroupID    �û���ID
    return		: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
    *******************************************************************/
    IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_AddUserGroup(IVS_INT32 iSessionID, const IVS_USER_GROUP* pUserGroup, IVS_UINT32* puiUserGroupID);

    /******************************************************************
    function		: IVS_SDK_ModifyUserGroup
    description	: �޸��û���
    input			: iSessionID   ��¼�ɹ���ĻỰID
					  pUserGroup   �û�����Ϣ
    return		: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
    *******************************************************************/
    IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_ModifyUserGroup(IVS_INT32 iSessionID, const IVS_USER_GROUP* pUserGroup);

    /******************************************************************
    function		: IVS_SDK_DeleteUserGroup
    description	: ɾ���û���
    input			: iSessionID    ��¼�ɹ���ĻỰID
					  pDomainCode    �����
					  uiUserGroupID    �û���ID
    return		: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
    *******************************************************************/
    IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_DeleteUserGroup(IVS_INT32 iSessionID, const IVS_CHAR* pDomainCode, IVS_UINT32 uiUserGroupID);

    /******************************************************************
    function		: IVS_SDK_MoveUserGroup
    description	: �ƶ��û���
    input			: iSessionID   ��¼�ɹ���ĻỰID
					  pDomainCode   �����
					  uiTargetGroupID   Ŀ���û���ID
					  pUserGroupList  �û����б�
    return		: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
    *******************************************************************/
    IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_MoveUserGroup(IVS_INT32 iSessionID, const IVS_CHAR* pDomainCode, IVS_UINT32 uiTargetGroupID, const IVS_USER_GROUP_LIST* pUserGroupList);

	/******************************************************************
    function		: IVS_SDK_GetUserGroupList
    description: ��ѯ�û����б�
    input			: iSessionID   ��¼�ɹ���ĻỰID
					  pDomainCode    �����
					  pIndexRange     ��ҳ��Ϣ
					  uiBufferSize    �����С
    output		: pUserGroupList   �û����б�
    return		: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
    *******************************************************************/
    IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_GetUserGroupList(IVS_INT32 iSessionID, const IVS_CHAR* pDomainCode, 
		const IVS_INDEX_RANGE* pIndexRange, IVS_USER_GROUP_LIST* pUserGroupList, IVS_UINT32 uiBufferSize);

	/******************************************************************
    function		: IVS_SDK_AddRole
    description	: ���ӽ�ɫ
    input			: iSessionID    ��¼�ɹ���ĻỰID
					  pRoleInfo     ��ɫ��Ϣ
    output		: puiRoleID     ��ɫID
    return		: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
    *******************************************************************/
    IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_AddRole(IVS_INT32 iSessionID, const IVS_ROLE_INFO* pRoleInfo, IVS_UINT32* puiRoleID);

    /******************************************************************
    function		: IVS_SDK_ModifyRole
    description	: �޸Ľ�ɫ
    input			: iSessionID   ��¼�ɹ���ĻỰID
					  pRoleInfo    ��ɫ��Ϣ�ṹ��
    return		: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
    *******************************************************************/
    IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_ModifyRole(IVS_INT32 iSessionID, const IVS_ROLE_INFO* pRoleInfo);

    /******************************************************************
    function		: IVS_SDK_DeleteRole
    description	: ɾ����ɫ
    input			: iSessionID    ��¼�ɹ���ĻỰID
					  pDomainCode    �����
					  uiRoleID     ��ɫID
    return		: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
    *******************************************************************/
    IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_DeleteRole(IVS_INT32 iSessionID, const IVS_CHAR* pDomainCode, IVS_UINT32 uiRoleID);

	/******************************************************************
    function		: IVS_SDK_GetRoleList
    description: ��ѯ��ɫ�б�
    input			: iSessionID   ��¼�ɹ���ĻỰID
					  pDomainCode     �����
					  pIndexRange     ��ҳ��Ϣ
					  uiBufferSize    �����С
    output		: pRoleInfoList     ��ɫ�б�
    return		: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
    *******************************************************************/
    IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_GetRoleList(IVS_INT32 iSessionID, const IVS_CHAR* pDomainCode, 
		const IVS_INDEX_RANGE* pIndexRange, IVS_ROLE_INFO_LIST* pRoleInfoList, IVS_UINT32 uiBufferSize);

	/******************************************************************
    function		: IVS_SDK_GetRoleInfoByRoleID
    description: ���ݽ�ɫID��ȡ��ɫ��ϸ��Ϣ
    input			: iSessionID   ��¼�ɹ���ĻỰID
					  pDomainCode    �����
					  uiRoleID    ��ɫID
    output		: pRoleInfo      ��ɫ��Ϣ
    return		: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
    *******************************************************************/
    IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_GetRoleInfoByRoleID(IVS_INT32 iSessionID, const IVS_CHAR* pDomainCode, IVS_UINT32 uiRoleID, IVS_ROLE_INFO* pRoleInfo);

    /******************************************************************
    function		: IVS_SDK_GetRoleInfoByUserID
    description: �����û�ID��ȡ��ɫ��ϸ��Ϣ
    input			: iSessionID    ��¼�ɹ���ĻỰID
					  pDomainCode    �����
					  uiUserID    ��ɫID
    output		: pRoleInfo    ��ɫ��Ϣ
    return		: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
    *******************************************************************/
    IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_GetRoleInfoByUserID(IVS_INT32 iSessionID, const IVS_CHAR* pDomainCode, IVS_UINT32 uiUserID, IVS_ROLE_INFO* pRoleInfo);

	/******************************************************************
    function		: IVS_SDK_GetDefaultRoleAccountRule
    description	: ��ȡĬ���˻�����
    input			: iSessionID    ��¼�ɹ���ĻỰID
					  pDomainCode     �����
    output		: pRoleAccountRule   �˻�����
    return		: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
    *******************************************************************/
    IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_GetDefaultRoleAccountRule(IVS_INT32 iSessionID, const IVS_CHAR* pDomainCode, IVS_ROLE_ACCOUNT_RULE* pRoleAccountRule);

	/******************************************************************
    function		: IVS_SDK_GetOperationRightGroup
    description: ��ȡ�û�Ȩ����Ϣ
    input			: iSessionID   ��¼�ɹ���ĻỰID
					  pDomainCode    �����
					  uiBufferSize    �����С
    output		: pRightGroupList   Ȩ�����б�
    return		: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
    *******************************************************************/
    IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_GetOperationRightGroup(IVS_INT32 iSessionID, const IVS_CHAR* pDomainCode, IVS_OPERATION_RIGHT_GROUP_LIST* pRightGroupList, IVS_UINT32 uiBufferSize);

	/******************************************************************
    function		: IVS_SDK_OMUQueryDiskUsageRateReport
    description: ���̴洢ռ���ʱ����ѯ
    input			: iSessionID   ��¼�ɹ���ĻỰID
					  pReqXml    ��ѯ����
    output		: pRspXml    ��ѯ���
    return		: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
    *******************************************************************/
    IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_OMUQueryDiskUsageRateReport(IVS_INT32 iSessionID, const IVS_CHAR* pReqXml, IVS_CHAR** pRspXml);

	/**************************************************************************
    * name			: IVS_SDK_OMUQueryRaidGroup
    * description	: ��������Ϣ��ѯ
    * input			: iSessionID ��¼�ɹ���ĻỰID
	* output		: pRspXml  ��ӦXML
    * return		: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
    **************************************************************************/
	IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_OMUQueryRaidGroup(IVS_INT32 iSessionID, IVS_CHAR** pRspXml);

	/**************************************************************************
    * name			: IVS_SDK_OMUQueryRaidGroupDisk
    * description	: ������Ϣ��ѯ
    * input			: iSessionID ��¼�ɹ���ĻỰID
						  pReqXml ����XML
	* output		: pRspXml  ��ӦXML
    * return		: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
    **************************************************************************/
	IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_OMUQueryRaidGroupDisk(IVS_INT32 iSessionID, const IVS_CHAR* pReqXml, IVS_CHAR** pRspXml);

	/**************************************************************************
    * name			: IVS_SDK_GetOperationLog
    * description	: ��ѯ������־
    * input			: iSessionID ��¼�ɹ���ĻỰID
						  pUnifiedQuery ͨ�ò�ѯ�ṹ��
						  uiBufSize �����С
    * output			: pResOperLogList ������־
    * return			: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
	* remark			: NA
    **************************************************************************/
	IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_GetOperationLog(IVS_INT32 iSessionID,
		const IVS_QUERY_UNIFIED_FORMAT* pUnifiedQuery,IVS_OPERATION_LOG_LIST* pResOperLogList, IVS_UINT32 uiBufSize);


	/**************************************************************************
    * name			: IVS_SDK_GetOperationLogEx
    * description: ��չ��ѯ������־
    * input			: iSessionID ��¼�ɹ���ĻỰID
	* input			: pUnifiedQuery ͳһͨ�ò�ѯ����
	* input			: pOptLogQueryEx ��չ��ѯ������־����
	* input			: uiBufSize �¼����ݴ�С
    * output			: pResOperLogList ������־��ѯ��ѯ���
    * return			: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
	* remark		: NA
    **************************************************************************/

	IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_GetOperationLogEx(IVS_INT32 iSessionID,
		const IVS_QUERY_UNIFIED_FORMAT* pUnifiedQuery,
		const IVS_QUERY_OPTLOG_EX *pOptLogQueryEx,
		IVS_OPERATION_LOG_LIST* pResOperLogList,
		const IVS_UINT32 uiBufSize);
		
	/*****************************************************************
	     function   : IVS_SDK_GetCPUMemory
	     description: CPU/�ڴ����ܲ�ѯ
	     output     : IVS_INT32 iSessionID         ��¼�ɹ���ĻỰID
					  const IVS_CHAR * pQueryXml   ��ѯXML
		 output     : IVS_CHAR** pRspXml           ��ӦXML 
	     return     : �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
	*****************************************************************/
	IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_GetCPUMemory(IVS_INT32 iSessionID, const IVS_CHAR* pNodeCode, IVS_CHAR** pPerformance);
	
	/******************************************************************
    function : IVS_SDK_OMUQueryDiskUsageRateReport
    description: ���̴洢ռ���ʱ����ѯ
    input : IVS_INT32 iSessionID        ��¼�ɹ���ĻỰID
    input : const IVS_CHAR * pReqXml    ��ѯ����
    input : IVS_CHAR * * pRspXml        ��ѯ���
    output : NA
    return : �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
    *******************************************************************/
    IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_OMUQueryDiskUsageRateReport(IVS_INT32 iSessionID, const IVS_CHAR* pReqXml, IVS_CHAR** pRspXml);
	
  	/******************************************************************
  	function   : IVS_SDK_GetRecordStatus
 	description: ��ѯ¼��״̬
  	input      : iSessionID ��¼�ɹ��󷵻صĻỰID
               pCameraCode ���������
			   uiRecordMethod ¼��ʽ
  	output     : NA
  	return     : �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
  	*******************************************************************/
  	IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_GetRecordStatus(IVS_INT32 iSessionID,const IVS_CHAR* pCameraCode,IVS_UINT32 uiRecordMethod,IVS_UINT32* pRecordState);
  
  	/******************************************************************
    function : IVS_SDK_OMUQueryRecordIntegralityReport
    description: ¼�������Ա����ѯ
    input : IVS_INT32 iSessionID        ��¼�ɹ���ĻỰID
    input : const IVS_CHAR * pReqXml    ��ѯ����
    input : IVS_CHAR * * pRspXml        ��ѯ���
    output : NA
    return : �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
    *******************************************************************/
    IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_OMUQueryRecordIntegralityReport(IVS_INT32 iSessionID, const IVS_CHAR* pReqXml, IVS_CHAR** pRspXml);
		
	/******************************************************************
    function			: IVS_SDK_OMUQueryDiskProperty
    description	: ��ѯ������Ϣ�ӿ�
    input				: iSessionID ��¼�ɹ���ĻỰID
    output			: pRspXml ���XML
	return				: �ɹ�����0��ʧ�ܷ��ش�����
    remark			: pRspXml��SDK�ڲ������ڴ棬ʹ����Ӧ�ͷš�
    return				: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
    *******************************************************************/
	IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_OMUQueryDiskProperty(IVS_INT32 iSessionID, 
		IVS_CHAR** pRspXml);
		
	/**************************************************************************
    * name			: IVS_SDK_GetVideoDiagnose
    * description: ��ѯ��̨VCN����Ƶ������ϼƻ�
    * input			: iSessionID ��¼�ɹ���ĻỰID
	* input			: pDomainCode �����
	* input			: pCameraCode ���������
	* output			: pRspXml ��̨VCN����Ƶ������ϼƻ�xml
    * return			: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
	* remark		: pRspXml��SDK�ڲ������ڴ棬ʹ����Ӧ����IVS_SDK_ReleaseBuffer�ͷš�
	* history			: 2014-6-9
    **************************************************************************/
	IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_GetVideoDiagnose(IVS_INT32 iSessionID,
		const IVS_CHAR* pDomainCode,
		const IVS_CHAR* pCameraCode,
		IVS_CHAR** pRspXml);

	/**************************************************************************
    * name			: IVS_SDK_SetVideoDiagnose
    * description: ���õ�̨VCN����Ƶ������ϼƻ�
    * input			: iSessionID ��¼�ɹ���ĻỰID
	* input			: pReqXml ��̨VCN����Ƶ������ϼƻ�xml
	* output			: NA
    * return			: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
	* remark		: NA
	* history			: 2014-6-9
    **************************************************************************/
	IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_SetVideoDiagnose(IVS_INT32 iSessionID, 
		const IVS_CHAR* pReqXml);

	/**************************************************************************
    * name			: IVS_SDK_GetStreamListByCam
    * description: ���������Code����ѯ����������ڸ���Щ�û��ṩ��Ƶҵ��
    * input			: iSessionID ��¼�ɹ���ĻỰID
	* input			: pDomainCode ����ѯ����������������
	* input			: pCameraCode ���������
	* input			: uiBufSize �����ڴ��С
	* output			: pStreamListByCam �����������ý��ҵ���б�
    * return			: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
	* remark		: C/C++��uiBufSize�̶�Ϊsizeof(IVS_STREAM_LIST_BY_CAM) + 
								(IVS_MAX_STREAM_USER_INFO_NUM -1) * sizeof(IVS_STREAM_USER_INFO)
	* history			: 2014-6-10
    **************************************************************************/
	IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_GetStreamListByCam(IVS_INT32 iSessionID, 
		const IVS_CHAR* pDomainCode,
		const IVS_CHAR* pCameraCode,
		IVS_UINT32 uiBufSize,
		IVS_STREAM_LIST_BY_CAM* pStreamListByCam);

	/**************************************************************************
    * name			: IVS_SDK_GetStreamListByUser
    * description: �����û����룬��ѯ���û����ڸ�������Щ���������Ƶҵ��
    * input			: iSessionID ��¼�ɹ���ĻỰID
	* input			: pDomainCode ����ѯ���û����������
	* input			: uiUserID ����ѯ���û�ID
	* input			: uiBufSize �����ڴ��С
	* output			: pStreamListByUser �û����ڵ��õ�ý��ҵ���б�
    * return			: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
	* remark		: C/C++��uiBufSize�̶�Ϊsizeof(IVS_STREAM_LIST_BY_USER) + 
								(IVS_MAX_STREAM_CAM_INFO_NUM -1) * sizeof(IVS_STREAM_CAM_INFO)
	* history			: 2014-6-24
    **************************************************************************/
	IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_GetStreamListByUser(IVS_INT32 iSessionID, 
		const IVS_CHAR* pDomainCode,
		IVS_UINT32 uiUserID,
		IVS_UINT32 uiBufSize,
		IVS_STREAM_LIST_BY_USER* pStreamListByUser);

	/**************************************************************************
    * name			: IVS_SDK_ShutdownStreamByUser
    * description: ���������Code���û�ID���رո��û�����ʹ�õ���Ƶҵ��
    * input			: iSessionID ��¼�ɹ���ĻỰID
	* input			: pDomainCode �û����������
	* input			: uiUserID �û�ID
	* input			: pCameraCode ���������
	* input			: iStreamType ��Ƶҵ������ 1-ʵ����2-�ط�
	* input			: iDuration �ر�ʱ�����ڴ�ʱ��֮�ڸ��û������ٴε㲥����λΪ�룬0Ϊ�����ƹر�ʱ��
	* output			: NA
    * return			: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
	* remark		: NA
	* history			: 2014-6-10
    **************************************************************************/
	IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_ShutdownStreamByUser(IVS_INT32 iSessionID,
		const IVS_CHAR* pDomainCode,
		IVS_UINT32 uiUserID,
		const IVS_CHAR* pCameraCode,
		IVS_INT32 iStreamType,
		IVS_INT32 iDuration);

	/**************************************************************************
    * name			: IVS_SDK_PasswdValidation
    * description: �û�����������֤
    * input			: iSessionID ��¼�ɹ���ĻỰID
	* input			: pLoginName ��¼�û���
	* input			: pPasswd ����
	* output			: NA
    * return			: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
	* remark		: NA
	* history			: 2014-6-27
    **************************************************************************/
	IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_PasswdValidation(IVS_INT32 iSessionID,
		const IVS_CHAR* pLoginName,
		const IVS_CHAR *pPasswd);

	/**************************************************************************
    * name			: IVS_SDK_SetVideoEffect
    * description: ¼����Ƶ��������
	* input			: iSessionID ��¼�ɹ���ĻỰID
    * input			: ulHandle ���ž��
	* input			: lBrightValue ����
	* input			: lContrastValue �Աȶ�
	* input			: lSaturationValue ���Ͷ�
	* input			: lHueValue ɫ��
	* output			: NA
    * return			: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
	* remark		: NA
	* history			: 2014-9-2
    **************************************************************************/
	IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_SetVideoEffect(IVS_INT32 iSessionID,
		IVS_ULONG ulPlayHandle, IVS_LONG lBrightValue,
		IVS_LONG lContrastValue, IVS_LONG lSaturationValue,
		IVS_LONG lHueValue);

	/**************************************************************************
    * name			: IVS_SDK_GetDomainDeviceList
    * description: ��ȡָ�������������豸�б�
	* input			: iSessionID ��¼�ɹ���ĻỰID
    * input			: pDomainCode ����룬Ϊ��Ҫ��ѯ�豸����ı���
	* input			: uiDeviceType �豸���ͣ�ֵ�ο�IVS_DEVICE_TYPE��֧�ֳ����豸������澯�豸��������豸
	* input			: pIndexRange ��ҳ��Ϣ
	* output			: pDeviceList �豸�б�ָ��
	* input			: uiBufferSize �����С
    * return			: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
	* remark		: NA
	* history			: 2014-9-9
    **************************************************************************/
	IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_GetDomainDeviceList(IVS_INT32 iSessionID,
		const IVS_CHAR* pDomainCode,
		IVS_UINT32 uiDeviceType,
		const IVS_INDEX_RANGE* pIndexRange,
		IVS_VOID* pDeviceList,
		IVS_UINT32 uiBufferSize);
		
  /**************************************************************************
    * name			: IVS_SDK_EnablePURealplayIAOverLay
    * description: ���������ʵ�������ܷ����켣����
	* input			: iSessionID ��¼�ɹ���ĻỰID
	* input			: ulRealPlayHandle ʵ�����ž��
    * input			: pDomainCode ����ͷID
	* input			: pNVRCode NVR����
	* input			: hWnd ý�崰�ھ��
    * return			: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
	* remark		: ��Ҫ����ͷ�߱����ܷ�����
	* history			: 2015-1-13
    **************************************************************************/
	IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_EnablePURealplayIAOverLay(IVS_INT32 iSessionID,
		IVS_ULONG ulRealPlayHandle,
		const IVS_CHAR* pCameraCode,
		const IVS_CHAR* pNVRCode,
		HWND hWnd);

	/**************************************************************************
    * name			: IVS_SDK_DisablePURealplayIAOverLay
    * description: ֹͣ�����ʵ�������ܷ����켣����
	* input			: iSessionID ��¼�ɹ���ĻỰID
	* input			: ulRealPlayHandle ʵ�����ž��
    * return			: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
	* remark		: ��Ҫ����ͷ�߱����ܷ�����
	* history			: 2015-1-13
    **************************************************************************/
	IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_DisablePURealplayIAOverLay(IVS_INT32 iSessionID,
		IVS_ULONG ulRealPlayHandle);

	/*********************************************************************************************
    * name       : IVS_SDK_GetAlarmSnapshotList
    * description: ��ȡ�澯ץ��ͼƬ�б�
    * input      : iSessionID, �ỰID��
							pReqXml�� ����xml
    * output     : pRsqXml, ��Ӧxml
    * return     : �ɹ�����0�� ʧ�ܷ��ش�����
    * remark     : NA
    *********************************************************************************************/
   IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_GetAlarmSnapshotList(IVS_INT32 iSessionID, const IVS_CHAR* pReqXml, IVS_CHAR** pRsqXml);
		
	/**************************************************************************
    * name			: IVS_SDK_GetDeviceListEx
    * description: ��ȡ�豸�б�������豸�����豸��γ����Ϣ
	* input			: iSessionID ��¼�ɹ���ĻỰID
	* input			: uiDeviceType �豸���ͣ�ֵ�ο�IVS_DEVICE_TYPE
	* input			: pIndexRange ��ҳ��Ϣ
	* input			: uiBufferSize �����С
	* output			: pDeviceList �豸�б�ָ��
    * return			: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
    * author			: zhuohaofan zwx211831
	* history			: 2015-3-20
    **************************************************************************/
	IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_GetDeviceListEx(IVS_INT32 iSessionID,
		IVS_UINT32	uiDeviceType,
		const IVS_INDEX_RANGE*	pIndexRange,
		IVS_VOID*	pDeviceList,
		IVS_UINT32	uiBufferSize);

	/**************************************************************************
    * name			: IVS_SDK_GetDomainDeviceListEx
    * description: ��ȡָ�������������豸�б�������豸�����豸��γ����Ϣ
	* input			: iSessionID ��¼�ɹ���ĻỰID
    * input			: pDomainCode ����룬Ϊ��Ҫ��ѯ�豸����ı���
	* input			: uiDeviceType �豸���ͣ�ֵ�ο�IVS_DEVICE_TYPE
	* input			: pIndexRange ��ҳ��Ϣ
	* output			: pDeviceList �豸�б�ָ��
	* input			: uiBufferSize �����С
    * return			: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
    * author			: zhuohaofan zwx211831
	* remark		: NA
	* history			: 2014-3-26
    **************************************************************************/
	IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_GetDomainDeviceListEx(IVS_INT32 iSessionID,
		const IVS_CHAR* pDomainCode,
		IVS_UINT32 uiDeviceType,
		const IVS_INDEX_RANGE* pIndexRange,
		IVS_VOID* pDeviceList,
		IVS_UINT32 uiBufferSize);

	/**************************************************************************
    * name			: IVS_SDK_EnablePUPlaybackIAOverLay
    * description: ���������¼������ܷ����켣����
	* input			: iSessionID ��¼�ɹ���ĻỰID
	* input			: ulPlaybackHandle �طŲ��ž��
    * input			: pDomainCode ����ͷID
	* input			: pNVRCode NVR����
	* input			: hWnd ý�崰�ھ��
    * return			: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
    * author			: zhuohaofan zwx211831
	* remark		: ֻ֧��һ��������
	* history			: 2015-7-13
    **************************************************************************/
	IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_EnablePUPlaybackIAOverLay(IVS_INT32 iSessionID,
		IVS_ULONG ulPlaybackHandle,
		const IVS_CHAR* pCameraCode,
		const IVS_CHAR* pNVRCode,
		HWND hWnd);

	/**************************************************************************
    * name			: IVS_SDK_DisablePURealplayIAOverLay
    * description: ֹͣ�����¼������ܷ����켣����
	* input			: iSessionID ��¼�ɹ���ĻỰID
	* input			: ulPlaybackHandle �طŲ��ž��
    * return			: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
    * author			: zhuohaofan zwx211831
	* remark		: 
	* history			: 2015-7-13
    **************************************************************************/
	IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_DisablePUPlaybackIAOverLay(IVS_INT32 iSessionID,
		IVS_ULONG ulPlaybackHandle);
		
	/**************************************************************************
    * name			: IVS_SDK_GetRtspURL
    * description	: ��ȡRtspURL
	* input			: iSessionID ��¼�ɹ���ĻỰID
	* input			: pCameraCode ʵ����¼������������
	* input		: pURLMediaParam  RTSP URL�����ṹ��
	* output		: pRtspURL  ���ص�RTSP URL��ַ
	* input			: uiBufferSize ���URL���ڴ��С
    * return		: �ɹ�����0��IVS_SUCCEED����ʧ�ܷ��ش�����
    * author		: zhuohaofan zwx211831
	* remark		: 
	* history		: 2015-12-26
    **************************************************************************/
	IVS_SDK_API IVS_INT32 __SDK_CALL  IVS_SDK_GetRtspURL(IVS_INT32 iSessionID, 
		const IVS_CHAR* pCameraCode, 
		const IVS_URL_MEDIA_PARAM *pURLMediaParam, 
		IVS_CHAR *pRtspURL, 
		IVS_UINT32 uiBufferSize);

	/*************************************************************************
	* name       : IVS_SDK_AddShadowIPC
	* description: ����Ӱ���豸
	* input      : iSessionID	��¼�ɹ���ĻỰID
				   pDomainCode	Ӱ��IPC�������
                   pShadowIPCInfo	Ӱ��IPC����Ϣ
	* output     : NA
	* return     : �ɹ�����0��ʧ�ܷ��ش�����
	* remark     : NA
	*************************************************************************/
	IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_AddShadowIPC(IVS_INT32 iSessionID,
		const IVS_CHAR* pDomainCode,
		const IVS_SHADOW_IPC_INFO* pShadowIPCInfo);

	/*************************************************************************
	* name       : IVS_SDK_ShadowDevSyncNotify
	* description: Ӱ���豸�ֶ�ͬ��
	* input      : uiDeviceNum Ӱ���豸����
                   pDevList    Ӱ��IPC��Ϣ
	* output     : NA
	* return     : �ɹ�����0��ʧ�ܷ��ش�����
	* remark     : NA
	*************************************************************************/
    IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_SYNC_ShadowIPC(IVS_INT32 iSessionID, 
        const IVS_SHADOW_IPC_LIST* pShadowIPCList);

	/**************************************************************************
    * name       : IVS_SDK_DelPlayWnd
    * description: 
    * input      : iSessionID ��¼�ɹ���ĻỰID
	               ulPlayHandle   ���ž��
                   hWnd       ���ھ��
    * output     : NA
    * return     : �ɹ�����IVS_SUCCESSED��ʧ�ܷ��ش�����
    * author     ��
	* remark     : NA
    **************************************************************************/
	IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_DelPlayWnd(IVS_INT32 iSessionID, IVS_ULONG ulPlayHandle, HWND hWnd);

	/******************************************************************
	name : IVS_SDK_SetDrawCallBackEx
	description: ���û�ͼ��ʾ�Ļص��ӿ�
	input : IVS_INT32			iSessionID		��¼�ɹ��󷵻صĻỰID��
			IVS_ULONG			ulPlayHandle	���ž����
			DRAW_PROC 		callback		��ͼ�ص�����ָ�룻
			void*��			pUserData		�û�����ָ��
	output : NA
	return : �ɹ�����0��ʧ�ܷ��ش�����
	*******************************************************************/
	IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_SetDrawCallBackEx(IVS_INT32 iSessionID, 
	IVS_ULONG ulPlayHandle, 
	HWND hWnd, 
	DRAW_PROC callback, 
	void *pUserData);
	
	/*************************************************************************
	* name       : IVS_SDK_SetProgressionTransmit
	* description: ������ת��
	* input      : bSupportProgressionTransmit �Ƿ�֧����ת��
                   pProgressionDomainCode      ת�������
	* output     : NA
	* return     : �ɹ�����0��ʧ�ܷ��ش�����
	* remark     : NA
	*************************************************************************/
    IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_SetProgressionTransmit(IVS_INT32 iSessionID, 
        IVS_BOOL  bSupportProgressionTransmit, const IVS_CHAR* pProgressionDomainCode);
		
  /******************************************************************
  * name : IVS_SDK_GetDomainRouteEx
  * description: ��ѯ��·����Ϣ
  * input : IVS_INT32 iSessionID
          IVS_UINT32 uiBufferSize
  * output : IVS_DOMAIN_ROUTE_LIST_EX * pDomainRouteList
  * return : NA
  *******************************************************************/  
  IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_GetDomainRouteEx( IVS_INT32 iSessionID, 
                          IVS_DOMAIN_ROUTE_LIST_EX* pDomainRouteList,
                          IVS_UINT32 uiBufferSize);
						  
	/**************************************************************************
    * name       : IVS_SDK_GetDeviceAlarmList
    * description: ��ѯOMU�澯�¼��б�
    * input      : iSessionID ��¼�ɹ���ĻỰID
				   pUnifiedQuery  ������Ϣ�ṹ��
	* output     : pAlarmEventList  ��Ӧ��Ϣ�ṹ��
    * return     : �ɹ�����IVS_SUCCESSED��ʧ�ܷ��ش�����
    **************************************************************************/
	IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_GetDeviceAlarmList(IVS_INT32 iSessionID, 
																const IVS_QUERY_UNIFIED_FORMAT* pUnifiedQuery,
																IVS_DEVICE_ALARM_EVENT_LIST* pAlarmEventList,
																IVS_UINT32 uiBufferSize);
	/**************************************************************************
    * name				:	IVS_SDK_StartRealPlayByChannel
    * description	:	��ʼʵʱ���������������ʱ�ɶ�ε���, 
									�ڿ���һ��ʵ����ʱ���ϵڶ�����������ô��ڣ�
									������ֹͣ��һ��ʵ�����ٲ��ŵڶ�������ͷ��ʵ����
									�ӿ���Ҫʵ����Ƶ�ؼ�֡���롣
    * input				:	 iSessionID ��¼�ɹ���ĻỰID
									pRealplayPara ʵ�����������ý������ṹ��
									uiChannel ͨ����
									hWnd       ���ھ��
    * output			:	pHandle    ���ž��
    * return			:	�ɹ�����IVS_SUCCESSED��ʧ�ܷ��ش�����
    * author			:	ywx313149
	* remark			:	NA
	* history			:	2016-07-19
    **************************************************************************/
    IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_StartRealPlayByChannel(IVS_INT32 iSessionID, 
																	IVS_REALPLAY_PARAM* pRealplayPara, 
																	IVS_UINT32 uiChannel, 
																	HWND hWnd, 
																	IVS_ULONG* pHandle);


	/**************************************************************************
    * name				:	 IVS_SDK_StartRealPlayCBRawByChannel
    * description	:	��ʼʵʱ������Իص���ʽ���ƴ֡���������, ����������ʱ�ɶ�ε���, 
									�ڿ���һ��ʵ����ʱ���ϵڶ�����������ô��ڣ�
									������ֹͣ��һ��ʵ�����ٲ��ŵڶ�������ͷ��ʵ����
									�ӿ���Ҫʵ����Ƶ�ؼ�֡���롣
    * input				:	iSessionID           ��¼�ɹ���ĻỰID
									pRealplayPara        ʵ�����������ʵ�������ṹ��
									uiChannel           ͨ����
									fRealPlayCallBackRaw ʵʱ����ص�����
									pUserData            �û�����
    * output			:	pHandle              ���ž��
    * return			:	�ɹ�����IVS_SUCCESSED��ʧ�ܷ��ش�����
    * author			:	ywx313149
	* remark			:	NA
	* history			:	2016-07-19
    **************************************************************************/
	IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_StartRealPlayCBRawByChannel(IVS_INT32 iSessionID, 
																	IVS_REALPLAY_PARAM* pRealplayPara, 
																	IVS_UINT32 uiChannel, 
																	RealPlayCallBackRaw fRealPlayCallBackRaw, 
																	void* pUserData, 
																	IVS_ULONG* pHandle );


	/**************************************************************************
    * name				:	IVS_SDK_StartRealPlayCBFrameByChannel
    * description	:	��ʼʵʱ������Իص���ʽ���YUV��, ����������ʱ�ɶ�ε���, 
									�ڿ���һ��ʵ����ʱ���ϵڶ�����������ô��ڣ�
									������ֹͣ��һ��ʵ�����ٲ��ŵڶ�������ͷ��ʵ����
									�ӿ���Ҫʵ����Ƶ�ؼ�֡���롣
    * input				:	iSessionID               ��¼�ɹ���ĻỰID
									pRealplayPara            ʵ�����������ʵ�������ṹ��
									uiChannel               ͨ����
									fRealPlayCallBackFrame   ʵʱ����ص�����
									pUserData                �û�����
    * output			:	pHandle                  ���ž��
    * return			:	 �ɹ�����IVS_SUCCESSED��ʧ�ܷ��ش�����
    * author			:	ywx313149
	* remark			:	 NA
	* history			:	2016-07-19
    **************************************************************************/
	IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_StartRealPlayCBFrameByChannel(IVS_INT32 iSessionID, 
																	IVS_REALPLAY_PARAM* pRealplayPara, 
																	IVS_UINT32 uiChannel, 
																	RealPlayCallBackFrame fRealPlayCallBackFrame, 
																	void* pUserData, 
																	IVS_ULONG* pHandle);

	/**************************************************************************
    * name				:	IVS_SDK_StartPlatformRecordByChannel
    * description	:	��ʼƽ̨¼��
    * input				:	 iSessionID      ��¼�ɹ���ĻỰID
									uiChannel     ͨ����
									iRecordTime     ¼��ʱ��
    * return			:	�ɹ�����IVS_SUCCESSED��ʧ�ܷ��ش�����
	* author			:	ywx313149
	* remark			:	 NA
	* history			:	2016-07-19
	**************************************************************************/
	IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_StartPlatformRecordByChannel(IVS_INT32 iSessionID, IVS_UINT32 uiChannel, IVS_INT32 iRecordTime);


	  /**************************************************************************
	  * name				:	IVS_SDK_StopPlatformRecordByChannel
	  * description	:	ֹͣƽ̨¼��
	  * input				:	 iSessionID      ��¼�ɹ���ĻỰID
										uiChannel     ͨ����
	  * return			:	�ɹ�����IVS_SUCCESSED��ʧ�ܷ��ش�����
	  * author			:	ywx313149
	  * remark			:	 NA
	  * history			:	2016-07-19
	  **************************************************************************/
	  IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_StopPlatformRecordByChannel(IVS_INT32 iSessionID, IVS_UINT32 uiChannel);


	   /**************************************************************************
	  * name				:	IVS_SDK_StartPURecordByChannel
	  * description	:	��ʼǰ��¼��
	  * input				:	 iSessionID      ��¼�ɹ���ĻỰID
										 uiChannel     ͨ����
										 iRecordTime     ¼��ʱ��
		* return			:	�ɹ�����IVS_SUCCESSED��ʧ�ܷ��ش�����
		* author			:	ywx313149
		* remark			:	 NA
		* history			:	2016-07-19
	  **************************************************************************/
	  IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_StartPURecordByChannel(IVS_INT32 iSessionID, IVS_UINT32 uiChannel, IVS_INT32 iRecordTime);


   /**************************************************************************
   * name				:	IVS_SDK_StopPURecordByChannel
   * description	:	ֹͣǰ��¼��
   * input				:	 iSessionID      ��¼�ɹ���ĻỰID
									uiChannel     ͨ����
   * return			:	�ɹ�����IVS_SUCCESSED��ʧ�ܷ��ش�����
   * author			:	ywx313149
   * remark			:	 NA
   * history			:	2016-07-19
  **************************************************************************/
  IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_StopPURecordByChannel(IVS_INT32 iSessionID, IVS_UINT32 uiChannel);

  /******************************************************************
   * name				:	IVS_SDK_GetRecordStatusByChannel
  * description	:	��ѯ¼��״̬
  * input				:	iSessionID ��¼�ɹ��󷵻صĻỰID
									uiChannel     ͨ����
									uiRecordMethod ¼��ʽ,0-ƽ̨¼�� 1-ǰ��¼��
	* output			:	pRecordState ¼��״̬
	* return			:	�ɹ�����IVS_SUCCESSED��ʧ�ܷ��ش�����
	* author			:	ywx313149
	* remark			:	 NA
	* history			:	2016-07-19
  *******************************************************************/
  IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_GetRecordStatusByChannel(IVS_INT32 iSessionID, 
																	IVS_UINT32 uiChannel, 
																	IVS_UINT32 uiRecordMethod, 
																	IVS_UINT32* pRecordState);


  /*************************************************************************
	 * name				:	IVS_SDK_GetRecordListByChannel
	* description		:	 ��ѯ¼���б�
	* input					:	iSessionID ��¼�ɹ���ĻỰID
										uiChannel ͨ����
										iRecordMethod ¼��洢λ��
										pTimeSpan ʱ�����Ϣ
										pIndexRange ��ҳ��Ϣ
										pRecordList ����¼���б�
										iBufSize �ڴ����ռ��С
	* output				:	pRecordList ¼���б�
	* return				:	�ɹ�����IVS_SUCCESSED��ʧ�ܷ��ش�����
	* author				:	ywx313149
	* remark				:	 NA
	* history				:	2016-07-19
	*************************************************************************/
	IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_GetRecordListByChannel(IVS_INT32 iSessionID, 
																	IVS_UINT32 uiChannel, 
																	IVS_INT32 iRecordMethod,
																	const IVS_TIME_SPAN* pTimeSpan,
																	const IVS_INDEX_RANGE* pIndexRange, 
																	IVS_RECORD_INFO_LIST* pRecordList, 
																	IVS_UINT32 uiBufSize);


	/*************************************************************************
	* name				:	IVS_SDK_QueryRecordListByChannel
	* description		:	��ѯ¼���б�
	* input					:	iSessionID ��¼�ɹ���ĻỰID
										uiChannel ͨ����
										pUnifiedQuery ͨ�ò�ѯ�ṹ
										pRecordInfoList ����¼���ѯ�ṹ�б�
										uiBufferSize �����ڴ��С
	* output				:	pRecordInfoList ��ѯ¼�����б�ṹ��
	* return				:	�ɹ�����IVS_SUCCESSED��ʧ�ܷ��ش�����
	* author				:	ywx313149
	* remark				:	 NA
	* history				:	2016-07-19
	*************************************************************************/
	IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_QueryRecordListByChannel(IVS_INT32 iSessionID, 
																	IVS_UINT32 uiChannel,
																	IVS_QUERY_UNIFIED_FORMAT* pUnifiedQuery, 
																	IVS_RECORD_INFO_LIST* pRecordInfoList,
																	IVS_UINT32 uiBufferSize);

	/*****************************************************************
	* name				:	IVS_SDK_GetRecordTaskByChannel
	* description		:	��ѯ��ǰ�û����ֶ�¼������
	* input					:	iSessionID ��¼�ɹ���ĻỰID
	* output				:	pRspXml ��ѯ��ǰ�û����ֶ�¼�����񷵻���ϢXML
	* return				:	�ɹ�����IVS_SUCCESSED��ʧ�ܷ��ش�����
	* author				:	ywx313149
	* remark				:	 NA
	* history				:	2016-07-19
	*****************************************************************/
	IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_GetRecordTaskByChannel(IVS_INT32 iSessionID, IVS_CHAR** pRspXml);

	/******************************************************************
     * name				:	IVS_SDK_StartPlatformDownloadByChannel
     * description		:	��ʼƽ̨¼������
     * input					:	iSessionID	��¼�ɹ���ĻỰID
										uiChannel	NVRͨ����
										pDownloadParam	¼�����ز�����ʱ�����ΪUTC��ʽʱ��
																				ʱ���Ȳ��ܴ���30��
     * output				:	pulHandle ¼�����ؾ��
     * return				:	�ɹ�����IVS_SUCCESSED��ʧ�ܷ��ش�����
	 * author				:	ywx313149
	 * remark				:	 NA
	 * history				:	2016-07-19
    *******************************************************************/
	IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_StartPlatformDownloadByChannel(IVS_INT32 iSessionID, 
																	IVS_UINT32 uiChannel,
																	const IVS_DOWNLOAD_PARAM* pDownloadParam, 
																	IVS_ULONG* pulHandle);

	/******************************************************************
     * name				:	IVS_SDK_StartPUDownloadByChannel
     * description		:	��ʼǰ��¼������
     * input					:	iSessionID	��¼�ɹ���ĻỰID
										uiChannel	NVRͨ����
										pDownloadParam	¼�����ز�����ʱ�����ΪUTC��ʽʱ��
																					ʱ���Ȳ��ܴ���30��
	 * output				:	pulHandle ¼�����ؾ��
	 * return				:	�ɹ�����IVS_SUCCESSED��ʧ�ܷ��ش�����
	 * author				:	ywx313149
	 * remark				:	 NA
	 * history				:	2016-07-19
    *******************************************************************/
	IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_StartPUDownloadByChannel(IVS_INT32 iSessionID, 
																	IVS_UINT32 uiChannel,
																	const IVS_DOWNLOAD_PARAM* pDownloadParam, 
																	IVS_ULONG* pulHandle);

	/**************************************************************************
	* name				:	IVS_SDK_StartPlatformPlayBackByChannel
	* description		:	��ʼƽ̨¼��ط�
	* input					:	iSessionID	��¼�ɹ���ĻỰID
										uiChannel	NVRͨ����
										pPlaybackParam	¼��طŲ���
										hWnd	���ھ��
	* output				:	pulHandle ¼��طž��
	* return				:	�ɹ�����IVS_SUCCESSED��ʧ�ܷ��ش�����
	* author				:	ywx313149
	* remark				:	 NA
	* history				:	2016-07-19
    **************************************************************************/
    IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_StartPlatformPlayBackByChannel(IVS_INT32 iSessionID,
																	IVS_UINT32 uiChannel,
																	const IVS_PLAYBACK_PARAM* pPlaybackParam,
																	HWND hWnd,
																	IVS_ULONG* pHandle);

	/**************************************************************************
    * name				:	IVS_SDK_StartPlatformPlayBackCBRawByChannel
    * description		:	��ʼƽ̨¼��ط�(�������ص�)
    * input					:	iSessionID           ��¼�ɹ���ĻỰID
										uiChannel          ͨ����
										fPlayBackCallBackRaw ¼��ط��������ص�����
										pUserData            �û�����
    * output				:	pHandle              ���ž��
	* return				:	�ɹ�����IVS_SUCCESSED��ʧ�ܷ��ش�����
	* author				:	ywx313149
	* remark				:	 NA
	* history				:	2016-07-19
    **************************************************************************/
	IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_StartPlatformPlayBackCBRawByChannel(IVS_INT32 iSessionID,
																		IVS_UINT32 uiChannel,
																		const IVS_PLAYBACK_PARAM* pPlaybackParam,
																		PlayBackCallBackRaw fPlayBackCallBackRaw, 
																		void* pUserData,
																		IVS_ULONG* pHandle);

	/**************************************************************************
    * name				:	IVS_SDK_StartPlatformPlayBackCBFrameByChannel
	* description		:	��ʼƽ̨¼��ط�(֡�����ص�)
	* input					:	iSessionID		��¼�ɹ���ĻỰID
										uiChannel		ͨ����
										pPlaybackParam		¼��طŲ���
										fPlayBackCallBackFrame		¼��طŽ����֡�����ص�����
										pUserData		�û�����
	* output				:	pHandle              ���ž��
	* return				:	�ɹ�����IVS_SUCCESSED��ʧ�ܷ��ش�����
	* author				:	ywx313149
	* remark				:	 NA
	* history				:	2016-07-19
    **************************************************************************/
	IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_StartPlatformPlayBackCBFrameByChannel(IVS_INT32 iSessionID,
		   																  IVS_UINT32 uiChannel,
																		  const IVS_PLAYBACK_PARAM* pPlaybackParam,
																		  PlayBackCallBackFrame fPlayBackCallBackFrame, 
																		  void* pUserData,
																		  IVS_ULONG* pHandle);
	/**************************************************************************
	* name				:	IVS_SDK_StartPUPlayBackByChannel
	* description		:	��ʼǰ��¼��ط�
	* input					:	iSessionID	��¼�ɹ���ĻỰID
										uiChannel	NVRͨ����
										pPlaybackParam	¼��طŲ���
										hWnd ���ھ��
	* output				:	pulHandle ¼��طž��
	* return				:	�ɹ�����IVS_SUCCESSED��ʧ�ܷ��ش�����
	* author				:	ywx313149
	* remark				:	 NA
	* history				:	2016-07-19
    **************************************************************************/
#ifdef WIN32
    IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_StartPUPlayBackByChannel(
                                    IVS_INT32 iSessionID,
                                    IVS_UINT32 uiChannel,
                                    const IVS_PLAYBACK_PARAM* pPlaybackParam,
                                    HWND hWnd,
                                    IVS_ULONG* pHandle);
#endif

	/**************************************************************************
	* name				:	IVS_SDK_AddRecordPlanByChannel
	* description		:	����ƽ̨��ǰ��¼��ƻ���֧�ֵ������Ӻ���������
	* input					:	iSessionID	��¼�ɹ���ĻỰID
										uiDeviceNum	���������
										pChannelList	NVRͨ�����б�
										pRecordPlan	¼��ƻ�
										uiResultBufferSize �����С
	* output				:	pResultList ¼��ƻ���������б�ṹ��
	* return				:	�ɹ�����IVS_SUCCESSED��ʧ�ܷ��ش�����
	* author				:	ywx313149
	* remark				:	 NA
	* history				:	2016-07-19
    **************************************************************************/
	IVS_SDK_API IVS_INT32 __SDK_CALL  IVS_SDK_AddRecordPlanByChannel(IVS_INT32  iSessionID, 
																	IVS_UINT32  uiDeviceNum, 
																	const IVS_CHANNEL  *pChannelList, 
																	const IVS_RECORD_PLAN  *pRecordPlan, 
																	IVS_RESULT_LIST  *pResultList, 
																	IVS_UINT32  uiResultBufferSize);

	/*************************************************************************
	* name				:	IVS_SDK_ModifyRecordPlanByChannel
	* description		:	�޸�ƽ̨��ǰ��¼��ƻ���֧�ֵ������Ӻ������޸�
	* input					:	iSessionID	��¼�ɹ���ĻỰID
										uiDeviceNum	���������
										pChannelList	NVRͨ�����б�
										pRecordPlan	¼��ƻ�
										uiResultBufferSize �����С
	* output				:	pResultList ¼��ƻ���������б�ṹ��
	* return				:	�ɹ�����IVS_SUCCESSED��ʧ�ܷ��ش�����
	* author				:	ywx313149
	* remark				:	 NA
	* history				:	2016-07-19
	*************************************************************************/
	IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_ModifyRecordPlanByChannel(IVS_INT32 iSessionID, 
																	IVS_UINT32 uiDeviceNum, 
																	const IVS_CHANNEL  *pChannelList, 
																	const IVS_RECORD_PLAN  *pRecordPlan, 
																	IVS_RESULT_LIST  *pResultList, 
																	IVS_UINT32 uiResultBufferSize );

	/*************************************************************************
	* name				:	IVS_SDK_DeleteRecordPlanByChannel
	* description		:	ɾ��ƽ̨��ǰ��¼��ƻ�
	* input					:	iSessionID	��¼�ɹ���ĻỰID
										uiDeviceNum	���������
										pChannelList	NVRͨ�����б�
										uiRecordMethod	¼��ʽ
										uiResultBufferSize �����С
	* output				:	pResultList ¼��ƻ���������б�ṹ��
	* return				:	�ɹ�����IVS_SUCCESSED��ʧ�ܷ��ش�����
	* author				:	ywx313149
	* remark				:	 NA
	* history				:	2016-07-19
	*************************************************************************/
	IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_DeleteRecordPlanByChannel(IVS_INT32 iSessionID, 
																	IVS_UINT32 uiDeviceNum, 
																	const IVS_CHANNEL   *pChannelList, 
																	IVS_UINT32  uiRecordMethod, 
																	IVS_RESULT_LIST *pResultList, 
																	IVS_UINT32  uiResultBufferSize);

	/*************************************************************************
	* name				:	IVS_SDK_GetRecordPlanByChannel
	* description		:	��ѯƽ̨��ǰ��¼��ƻ�
	* input					:	iSessionID	��¼�ɹ���ĻỰID
										uiChannel	NVRͨ����
										uiRecordMethod	¼��ʽ
	* output				:	NA
	* return				:	�ɹ�����IVS_SUCCESSED��ʧ�ܷ��ش�����
	* author				:	ywx313149
	* remark				:	 NA
	* history				:	2016-07-19
	*************************************************************************/
	IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_GetRecordPlanByChannel(IVS_INT32 iSessionID, 
																	IVS_UINT32  uiChannel, 
																	IVS_UINT32   uiRecordMethod, 
																	IVS_RECORD_PLAN *pRecordPlan);

	/*************************************************************************
	* name				:	IVS_SDK_SetRecordPolicyByTimeByChannel
	* description		:	����¼��ʱ�����
	* input					:	iSessionID	��¼�ɹ���ĻỰID
										uiChannel	NVRͨ����
										pRecordPolicy	¼�����
	* output				:	NA
	* return				:	�ɹ�����IVS_SUCCESSED��ʧ�ܷ��ش�����
	* author				:	ywx313149
	* remark				:	 NA
	* history				:	2016-07-19
	*************************************************************************/
	IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_SetRecordPolicyByTimeByChannel(IVS_INT32  iSessionID, 
																	IVS_UINT32  uiChannel, 
																	const IVS_RECORD_POLICY_TIME  *pRecordPolicy);

	/*************************************************************************
	* name				:	IVS_SDK_GetRecordPolicyByTimeByChannel
	* description		:	��ѯ¼��ʱ�����
	* input					:	iSessionID	��¼�ɹ���ĻỰID
										uiChannel	NVRͨ����
	* output				:	pRecordPolicy	¼�����
	* return				:	�ɹ�����IVS_SUCCESSED��ʧ�ܷ��ش�����
	* author				:	ywx313149
	* remark				:	 NA
	* history				:	2016-07-19
	*************************************************************************/
	IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_GetRecordPolicyByTimeByChannel(IVS_INT32  iSessionID, 
																	IVS_UINT32  uiChannel, 
																	IVS_RECORD_POLICY_TIME  *pRecordPolicy);
																	
  /*************************************************************************
   * name		: IVS_SDK_GetVehicleList
   * description: ��ѯ����ͼƬ�б�
   * input		: iSessionID ��¼�ɹ���ĻỰID
   * input		: pUnifiedQuery ��ѯ��Ϣ
   * input		: uiBufferSize ��Ų�ѯ����ͼƬ�ڴ��С
   * output 	: pVehicleList ��Ų�ѯ����ͼƬ�ڴ�ָ��
   * return 	: �ɹ�����0��ʧ�ܷ��ش�����
   * remark 	: NA
   *************************************************************************/
   IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_GetVehicleList(IVS_INT32 iSessionID, const IVS_QUERY_UNIFIED_FORMAT* pUnifiedQuery, IVS_ITS_VEHICLE_LIST* pVehicleList, IVS_UINT32 uiBufferSize);

   /*************************************************************************
   * name			: IVS_SDK_StartUploadVehicleImg
   * description	: ��ʼ�ϴ�ͼƬ,��ȡ�ϴ����
   * input			: iSessionID ��¼�ɹ���ĻỰID
   * input/output	: pStoreNvrInfo ͼƬƽ̨�洢��Ϣ
						[in]pStoreNvrInfo->cDomainCode �����
						[in]pStoreNvrInfo->cClusterCode ��Ⱥ���루��Ⱥģʽ�±���ѵ�ģʽ��Ϊ�գ�
						[in/out]pStoreNvrInfo->cNVRCode NVR����;���ѵ�ģʽ�£�cNVRCodeΪ��Σ���Ⱥģʽ�£�cNVRCodeΪ���Σ�
   * output 		: pHandle �ϴ����
   * return 		: �ɹ�����0��ʧ�ܷ��ش�����
   * remark 		: Ŀǰδ���Ż�ȡ��Ⱥ����Ľӿڣ���Ҫ�Ӽ�Ⱥ����ҳ���ϻ�ȡ��
   *************************************************************************/
   IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_StartUploadVehicleImg(IVS_INT32 iSessionID, const IVS_IMG_STORE_NVR_INFO* pStoreNvrInfo, void* &pHandle);

   /*************************************************************************
   * name			: IVS_SDK_UploadVehicleImg
   * description	: ͨ������ϴ�ͼƬ
   * input			: iSessionID ��¼�ɹ���ĻỰID; 
   * input			: pHandle �ϴ�ͼƬ�ľ��;
   * input/output	: pImgInfo[] �ϴ�ͼƬ�Ľṹ��ָ������;
   * input			: uiPicNum �ϴ���ͼƬ����
   * output 		: NA
   * return 		: �ɹ�����0��ʧ�ܷ��ش�����
   * remark 		: NA
   *************************************************************************/
   IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_UploadVehicleImg(IVS_INT32 iSessionID, const void* pHandle, IVS_IMG_STORE_INFO* pImgInfo[], const IVS_UINT32 uiPicNum);

   /*************************************************************************
   * name		: IVS_SDK_StopUploadVehicleImg
   * description: ֹͣ�ϴ�ͼƬ
   * input		: iSessionID ��¼�ɹ���ĻỰID
   * input		: pHandle �ϴ�ͼƬ�ľ��
   * output 	: NA
   * return 	: �ɹ�����0��ʧ�ܷ��ش�����
   * remark 	: NA
   *************************************************************************/
   IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_StopUploadVehicleImg(IVS_INT32 iSessionID, const void* pHandle);

   /*************************************************************************
   * name			: IVS_SDK_DownloadImg
   * description	: ����ͼƬ
   * input			: iSessionID ��¼�ɹ���ĻỰID
   * input			: pStoreNvrInfo ͼƬƽ̨�洢��Ϣ
   * input/output	: pImgInfo[] ��Ҫ���ص�ͼƬ��Ϣ�����غ��ͼƬ����
   * input			: uiPicNum ����ͼƬ����
   * output 		: NA
   * return 		: �ɹ�����0��ʧ�ܷ��ش�����
   * remark 		: pStoreNvrInfoֻ�����cDomainCode��cNVRCode����Ⱥģʽ����ε�cNVRCodeΪ��ʼ�ϴ�ʱ�ĳ��Ρ�
   *************************************************************************/
   IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_DownloadImg(IVS_INT32 iSessionID, const IVS_IMG_STORE_NVR_INFO* pStoreNvrInfo, IVS_IMG_STORE_INFO* pImgInfo[], const IVS_UINT32 uiPicNum);

   /*************************************************************************
   * name			: IVS_SDK_GetTicket
   * description	: ��ȡ�����¼��ticket
   * input			: iSessionID ��¼�ɹ���ĻỰID
   * input			: uiBufferSize �洢Ticket���ڴ��ֽڳ��ȣ���С��64�ֽڣ�
   * output			: pTicket һ������֤ƾ��
   * return 		: �ɹ�����0��ʧ�ܷ��ش�����
   * remark 		: TicketΪһ������֤ƾ�ݣ���Чʱ��Ϊ5����
   *************************************************************************/
   IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_GetTicket(IVS_INT32 iSessionID, IVS_CHAR *pTicket, IVS_UINT32 uiBufferSize);

   /**************************************************************************
	* name       : IVS_SDK_Login
	* description: �û���¼
	* input      : IVS_LOGIN_INFO_BYTOKEN ��½��νṹ��
                       �� cTokenID TokenID
                       pUserName �û���
	                    pPassword ����
	                    pIP       ������IP��ַ
	                    iPort     �������˿�
                        stClientIP ��¼�������ͻ���IP
	                    loginType ��½����	��		0 �C���������֤ 	1 �CWindows�������֤����ǰ�û� 	2 �CWindows�������֤�������û�
	                    pDomainName   ��¼������Ϣ
	                    pMachineName �ͻ��˵�¼�Ļ�������
    * output     : pSessionId  ����sessionId SessionID��SDK�ڲ�����������0��������
                        ��Ϊ�����ӿڵ���Σ��������ַ��ʵķ�����������¼128����������
	* return     : �ɹ�����0��ʧ�ܷ��ش�����
	* remark     : NA
	**************************************************************************/
    IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_LoginByToken(IVS_LOGIN_INFO_BYTOKEN* pLoginReqInfo, IVS_INT32* pSessionId);

    /******************************************************************
    function : IVS_SDK_ChangePWDByToken
    description: �޸��û�����
    input : IVS_INT32 iSessionID            ��¼�ɹ���ĻỰID
    input : const IVS_CHANGE_USERPWD_INFO* pUserInfo    ���޸ĵ��û���Ϣ
    return : �ɹ�����0��ʧ�ܷ��ش�����
    *******************************************************************/
    IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_ChangePWDByToken(IVS_INT32 iSessionID, const IVS_CHANGE_USERPWD_INFO* pUserInfo);

    /******************************************************************
    function : IVS_SDK_PasswdValidationByToken
    description: �����û���������
    input : IVS_INT32 iSessionID            ��¼�ɹ���ĻỰID
    input : const IVS_CHANGE_USERPWD_INFO* pUserInfo    ���޸ĵ��û���Ϣ
    return : �ɹ�����0��ʧ�ܷ��ش�����
    *******************************************************************/
    IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_PasswdValidationByToken(IVS_INT32 iSessionID, const IVS_VALIDATE_USER_INFO* pUserInfo);

    /******************************************************************
    function : IVS_SDK_GetValidateToken
    description: ��ȡ�û������������token
    input : IVS_INT32 iSessionID            ��¼�ɹ���ĻỰID
	input			: uiBufferSize �洢Token���ڴ��ֽڳ��ȣ���С��64�ֽڣ�
    output : IVS_CHAR * pTokenID  ���ص�Token����󳤶�ΪIVS_TOKEN_LEN	
    return : �ɹ�����0��ʧ�ܷ��ش�����
    *******************************************************************/
    IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_GetValidateToken(IVS_INT32 iSessionID, IVS_CHAR* pTokenID, IVS_UINT32 uiBufferSize);
	
	IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_SetStorageRedundanceStrategy(IVS_INT32  iSessionID, const IVS_CHAR *pCamcode, IVS_INT32 TimeLen);
	
	IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_GetStorageRedundanceStrategy(IVS_INT32  iSessionID, const IVS_CHAR *pCamcode, IVS_INT32 *pTimeLen);

    /******************************************************************
    function : IVS_SDK_SetPlayBackSpeedType
    description: ���ò����ٶȵ�����
    input : IVS_INT32 iSessionID            ��¼�ɹ���ĻỰID
	input			: 0��ʾ��ʵ�ٶȣ�1��ʾĬ���ٶȡ�
    return : �ɹ�����0��ʧ�ܷ��ش�����
    *******************************************************************/
   IVS_SDK_API IVS_INT32 __SDK_CALL IVS_SDK_SetPlayBackSpeedType(IVS_INT32 iSessionID, IVS_UINT32 uPlayBackSpeedType);
#ifdef __cplusplus
}
#endif //__cplusplus

#endif //_IVS_SDK_H_

