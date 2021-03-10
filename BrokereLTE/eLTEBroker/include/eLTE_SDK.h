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
filename		: 	eLTE_SDK.h
author			:	zWX229156
created		    :	2015/1/5
description		:	���� DLL Ӧ�ó���ĵ�������
copyright		:	Copyright (C) 2015-2017
history			:	2015/1/5 ��ʼ�汾
*********************************************************************/

#ifndef __ELTE_SDK_H__
#define __ELTE_SDK_H__

#include "eLTE_Types.h"

// �����ṩDLL�����ӿ�
#ifdef WIN32
#ifdef  ELTE_SDK_EXPORTS
#define ELTE_SDK_API __declspec(dllexport)
#else
#define ELTE_SDK_API __declspec(dllimport)
#endif
#else
#define ELTE_SDK_API __attribute__((visibility("default")))
#endif

#ifdef __cplusplus
extern "C"
{
#endif

	/**************************************************************************
	* name			: ELTE_SDK_SetLogPath
	* description   : ������־·������ʹ�þ���·������鿴��־�ļ�
	* input			: pLogFilePath ��־����·��
	* output		: N/A
	* return		: �ɹ�����0��ʧ�ܷ��ش�����
	**************************************************************************/
	ELTE_SDK_API ELTE_INT32 __SDK_CALL ELTE_SDK_SetLogPath(const ELTE_CHAR* pLogFilePath);

	/**************************************************************************
	* name			: ELTE_SDK_SetLogLevel	
	* description   : ������־����
	* input			: iLogLevel ��־����
	* output		: N/A
	* return		: �ɹ�����0��ʧ�ܷ��ش�����
	**************************************************************************/
	ELTE_SDK_API ELTE_INT32 __SDK_CALL ELTE_SDK_SetLogLevel(ELTE_UINT32 iLogLevel);

	/**************************************************************************
	* name			: ELTE_SDK_ReleaseBuffer
	* description   : �ͷ�SDK�ڲ�������ڴ�
	* input			: pBuffer �ڴ�ָ��
	* output		: N/A
	* return		: �ɹ�����0��ʧ�ܷ��ش�����
	**************************************************************************/
	ELTE_SDK_API ELTE_INT32 __SDK_CALL  ELTE_SDK_ReleaseBuffer(ELTE_CHAR* pBuffer);

	/**************************************************************************
	* name			: ELTE_SDK_GetVersion
	* description   : ��ȡSDK�汾��
	* input			: pVersion ��ȡSDK�汾��
	* output		: N/A
	* return		: �ɹ�����0��ʧ�ܷ��ش�����
	**************************************************************************/
	ELTE_SDK_API ELTE_INT32 __SDK_CALL ELTE_SDK_GetVersion(ELTE_CHAR** pVersion);

	/**************************************************************************
	* name			: ELTE_SDK_Init
	* description   : ��ʼ��SDK
	* input			: N/A
	* output		: N/A
	* return		: �ɹ�����0��ʧ�ܷ��ش�����
	**************************************************************************/
	ELTE_SDK_API ELTE_INT32 __SDK_CALL ELTE_SDK_Init(ELTE_INT32 iMediaBypass);

	/**************************************************************************
	* name			: ELTE_SDK_Cleanup
	* description   : �ͷ�SDK
	* input			: N/A
	* output		: N/A
	* return		: �ɹ�����0��ʧ�ܷ��ش�����
	**************************************************************************/
	ELTE_SDK_API ELTE_INT32 __SDK_CALL ELTE_SDK_Cleanup();

	/**************************************************************************
	* name			: ELTE_SDK_SetEventCallBack
	* description   : ������Ϣ�ص�����
	* input			: fEventCallBack �û����õ��¼��ص�������Ϊ�ձ�ʾȡ�����õĻص�����
	                  pUserData      �û�����
	* output		: N/A
	* return		: �ɹ�����0��ʧ�ܷ��ش�����
	**************************************************************************/
	ELTE_SDK_API ELTE_INT32 __SDK_CALL ELTE_SDK_SetEventCallBack(EventCallBack fEventCallBack, ELTE_VOID* pUserData);

	/**************************************************************************
	* name			: ELTE_SDK_SetYUVFrameCallBack
	* description   : ������Ƶ���ݻص�����
	* input			: fYUVFrameCallBack �û����õ���Ƶ���ݻص�������Ϊ�ձ�ʾȡ�����õĻص�����
	                  pUserData      �û�����
	* output		: N/A
	* return		: �ɹ�����0��ʧ�ܷ��ش�����
	**************************************************************************/
	ELTE_SDK_API ELTE_INT32 __SDK_CALL ELTE_SDK_SetYUVFrameCallBack(YUVFrameCallBack fYUVFrameCallBack, ELTE_VOID* pUserData);

	/**************************************************************************
	* name			: ELTE_SDK_Login
	* description   : ��¼
	* input			: pUserID         ����Ա�˺�
					  pPWD            ����Ա����
					  pServerIP       ���Ȼ�IP��ַ
	                  pLocalIP        ��������IP��ַ
					  uiServerSIPPort ���Ȼ�SIP����˿�
	* output		: N/A
	* return		: �ɹ�����0��ʧ�ܷ��ش�����
	**************************************************************************/
	ELTE_SDK_API ELTE_INT32 __SDK_CALL ELTE_SDK_Login(const ELTE_CHAR* pUserID, const ELTE_CHAR* pPWD, const ELTE_CHAR* pServerIP, const ELTE_CHAR* pLocalIP, ELTE_UINT32 uiServerSIPPort);

	/**************************************************************************
	* name			: ELTE_SDK_Logout
	* description   : ע��
	* input			: pUserID ����Ա�˺�
	* output		: N/A
	* return		: �ɹ�����0��ʧ�ܷ��ش�����
	**************************************************************************/
	ELTE_SDK_API ELTE_INT32 __SDK_CALL ELTE_SDK_Logout(const ELTE_CHAR* pUserID);

	/**************************************************************************
	* name			: ELTE_SDK_TriggerStatusReport
	* description   : ����״̬�ϱ�
	* input			: iEnableStatusReport �Ƿ���״̬�ϱ�
	* output		: N/A
	* return		: �ɹ�����0��ʧ�ܷ��ش�����
	**************************************************************************/
	ELTE_SDK_API ELTE_INT32 __SDK_CALL ELTE_SDK_TriggerStatusReport(ELTE_INT32 iEnableStatusReport);

	/**************************************************************************
	* name			: ELTE_SDK_ProvisionManagerInitMRS
	* description   : ý���������ʼ��
	* input			: pServerIP ý�������IP��ַ
	* output		: N/A
	* return		: �ɹ�����0��ʧ�ܷ��ش�����
	**************************************************************************/
	ELTE_SDK_API ELTE_INT32 __SDK_CALL ELTE_SDK_ProvisionManagerInitMRS(const ELTE_CHAR* pServerIP);

	/**************************************************************************
	* name			: ELTE_SDK_GetDcGroups
	* description   : ��ȡ����̨Ⱥ���б�
	* input			: pUserID ����̨���û���
	* output		: pDcGroups �õ���̨����������Ⱥ���б�
	* return		: �ɹ�����0��ʧ�ܷ��ش�����
	**************************************************************************/
	ELTE_SDK_API ELTE_INT32 __SDK_CALL ELTE_SDK_GetDcGroups(const ELTE_CHAR* pUserID, ELTE_CHAR** pDcGroups);

	/**************************************************************************
	* name			: ELTE_SDK_GetDcUsers
	* description   : ��ȡ����̨�û��б�
	* input			: pUserID ����̨���û���
	* output		: pDcUsers �õ���̨������������û��б�
	* return		: �ɹ�����0��ʧ�ܷ��ش�����
	**************************************************************************/
	ELTE_SDK_API ELTE_INT32 __SDK_CALL ELTE_SDK_GetDcUsers(const ELTE_CHAR* pUserID, ELTE_CHAR** pDcUsers);

	/**************************************************************************
	* name			: ELTE_SDK_GetGroupUsers
	* description   : ��ȡһ��Ⱥ���Ա�б�
	* input			: pGroupID Ⱥ���
	* output		: pGroupUsers ��Ⱥ������г�Ա�б�
	* return		: �ɹ�����0��ʧ�ܷ��ش�����
	**************************************************************************/
	ELTE_SDK_API ELTE_INT32 __SDK_CALL ELTE_SDK_GetGroupUsers(const ELTE_CHAR* pGroupID, ELTE_CHAR** pGroupUsers);

	/**************************************************************************
	* name			: ELTE_SDK_GetGroupInfo
	* description   : ��ȡһ��Ⱥ����ϸ��Ϣ
	* input			: pGroupID Ⱥ���
	* output		: pGroupInfo ��Ⱥ�����ϸ��Ϣ
	* return		: �ɹ�����0��ʧ�ܷ��ش�����
	**************************************************************************/
	ELTE_SDK_API ELTE_INT32 __SDK_CALL ELTE_SDK_GetGroupInfo(const ELTE_CHAR* pGroupID, ELTE_CHAR** pGroupInfo);

	/**************************************************************************
	* name			: ELTE_SDK_GetUserInfo
	* description   : ��ȡһ���û���ϸ��Ϣ
	* input			: pUserID ����Ա�˺�
	* output		: pUserInfo ���û�����ϸ��Ϣ
	* return		: �ɹ�����0��ʧ�ܷ��ش�����
	**************************************************************************/
	ELTE_SDK_API ELTE_INT32 __SDK_CALL ELTE_SDK_GetUserInfo(const ELTE_CHAR* pUserID, ELTE_CHAR** pUserInfo);

	/**************************************************************************
	* name			: ELTE_SDK_GetDcInfo
	* description   : ��ȡһ���û���ϸ��Ϣ
	* input			: pUserID ����̨���û���
	* output		: pDcInfo �õ���̨��ϸ��Ϣ
	* return		: �ɹ�����0��ʧ�ܷ��ش�����
	**************************************************************************/
	ELTE_SDK_API ELTE_INT32 __SDK_CALL ELTE_SDK_GetDcInfo(const ELTE_CHAR* pUserID, ELTE_CHAR** pDcInfo);

	/**************************************************************************
	* name			: ELTE_SDK_UnSubscribeGroup
	* description   : ȡ������Ⱥ��
	* input			: pGroupID              Ⱥ���
	* output		: N/A
	* return		: �ɹ�����0��ʧ�ܷ��ش�����
	**************************************************************************/
	ELTE_SDK_API ELTE_INT32 __SDK_CALL ELTE_SDK_UnSubscribeGroup(const ELTE_CHAR* pGroupID);

	/**************************************************************************
	* name			: ELTE_SDK_SubJoinGroup
	* description   : ���Ĳ��Զ�����Ⱥ��
	* input			: pGroupID  Ⱥ���
	* output		: N/A
	* return		: �ɹ�����0��ʧ�ܷ��ش�����
	**************************************************************************/
	ELTE_SDK_API ELTE_INT32 __SDK_CALL ELTE_SDK_SubJoinGroup(const ELTE_CHAR* pGroupID);

	/**************************************************************************
	* name			: ELTE_SDK_CreateDynamicGroup
	* description   : ������̬Ⱥ��
	* input			: pDGNAParam ��̬�������Ϣ
	* output		: N/A
	* return		: �ɹ�����0��ʧ�ܷ��ش�����
	**************************************************************************/
	ELTE_SDK_API ELTE_INT32 __SDK_CALL ELTE_SDK_CreateDynamicGroup(const ELTE_CHAR* pDGNAParam);

	/**************************************************************************
	* name			: ELTE_SDK_CancelDynamicGroup
	* description   : ɾ����̬Ⱥ��
	* input			: pResourceID ��̬�����
	* output		: N/A
	* return		: �ɹ�����0��ʧ�ܷ��ش�����
	**************************************************************************/
	ELTE_SDK_API ELTE_INT32 __SDK_CALL ELTE_SDK_CancelDynamicGroup(const ELTE_CHAR* pResourceID);

	/**************************************************************************
	* name			: ELTE_SDK_GetTempGroupID
	* description   : ��ȡ��ʱ���
	* input			: N/A
	* output		: iGroupID ��ʱ�����
	* return		: �ɹ�����0��ʧ�ܷ��ش�����
	**************************************************************************/
	ELTE_SDK_API ELTE_INT32 __SDK_CALL ELTE_SDK_GetTempGroupID(ELTE_INT32* iGroupID);

	/**************************************************************************
	* name			: ELTE_SDK_CreateTempGroup
	* description   : ������ʱ��
	* input			: pTEMPGParam ��ʱ�������Ϣ
	* output		: N/A
	* return		: �ɹ�����0��ʧ�ܷ��ش�����
	**************************************************************************/
	ELTE_SDK_API ELTE_INT32 __SDK_CALL ELTE_SDK_CreateTempGroup(const ELTE_CHAR* pTEMPGParam);

	/**************************************************************************
	* name			: ELTE_SDK_GetUserRECFileInfoList
	* description   : ��ȡ¼���ļ��б�
	* input			: pQueryXml ��ѯ¼������Xml
	* output		: pRspXml   ��ѯ¼���ļ�����б�
	* return		: �ɹ�����0��ʧ�ܷ��ش�����
	**************************************************************************/
	ELTE_SDK_API ELTE_INT32 __SDK_CALL ELTE_SDK_GetUserRECFileInfoList(const ELTE_CHAR* pQueryXml, ELTE_CHAR** pRspXml);

	/**************************************************************************
	* name			: ELTE_SDK_StartRealPlay
	* description   : ��ʼ����ʵʱ��Ƶ
	* input			: pResourceID ��ԴID
	                  pVideoParam ý�����
	* output		: N/A
	* return		: �ɹ�����0��ʧ�ܷ��ش�����
	**************************************************************************/
	ELTE_SDK_API ELTE_INT32 __SDK_CALL ELTE_SDK_StartRealPlay(const ELTE_CHAR* pResourceID, const ELTE_CHAR* pVideoParam);

	/**************************************************************************
	* name			: ELTE_SDK_SetPlayWindow
	* description   : ���ò���ʵʱ��Ƶ����
	* input			: pResourceID ��ԴID
	                  pVideoParam ���ھ��
	* output		: N/A
	* return		: �ɹ�����0��ʧ�ܷ��ش�����
	**************************************************************************/
	ELTE_SDK_API ELTE_INT32 __SDK_CALL ELTE_SDK_SetPlayWindow(const ELTE_CHAR* pResourceID, ELTE_VOID* hWnd);

	/**************************************************************************
	* name			: ELTE_SDK_LocalSnapshot
	* description   : ץ����Ƶ����
	* input			: pResourceID ��ԴID
	                  pSnapshotPath ͼƬ����·��+�ļ���
					  ulSnapshotFormat ץͼ��ʽ��1 JPG��2 BMP
	* output		: N/A
	* return		: �ɹ�����0��ʧ�ܷ��ش�����
	**************************************************************************/
	ELTE_SDK_API ELTE_INT32 __SDK_CALL ELTE_SDK_LocalSnapshot(const ELTE_CHAR* pResourceID, const ELTE_CHAR* pSnapshotPath, ELTE_ULONG ulSnapshotFormat);

	/**************************************************************************
	* name			: ELTE_SDK_SetPlayWindowSize
	* description   : ���ò���ʵʱ��Ƶ���ڵĴ�С
	* input			: pResourceID ��ԴID
	                  ulWidth			���
					  ulHeight		    �߶�
	* output		: N/A
	* return		: �ɹ�����0��ʧ�ܷ��ش�����
	**************************************************************************/
	ELTE_SDK_API ELTE_INT32 __SDK_CALL ELTE_SDK_SetPlayWindowSize(const ELTE_CHAR* pResourceID, ELTE_ULONG ulWidth, ELTE_ULONG ulHeight);

	/**************************************************************************
	* name			: ELTE_SDK_PTZControl
	* description   : ��ʼ��̨����
	* input			: pResourceID      ����̨���������ԴID
	                  iPTZControlCode  ��̨��������
					  iPTZControlValue ��̨���������Ӧ�Ĳ���
	* output		: N/A
	* return		: �ɹ�����0��ʧ�ܷ��ش�����
	**************************************************************************/
	ELTE_SDK_API ELTE_INT32 __SDK_CALL ELTE_SDK_PTZControl(const ELTE_CHAR* pResourceID, ELTE_UINT32 iPTZControlCode, ELTE_UINT32 iPTZControlValue);

	/**************************************************************************
	* name			: ELTE_SDK_StopRealPlay
	* description   : ֹͣ����ʵʱ��Ƶ
	* input			: pResourceID      ����̨���������ԴID
	* output		: N/A
	* return		: �ɹ�����0��ʧ�ܷ��ش�����
	**************************************************************************/
	ELTE_SDK_API ELTE_INT32 __SDK_CALL ELTE_SDK_StopRealPlay(const ELTE_CHAR* pResourceID);

	/**************************************************************************
	* name			: ELTE_SDK_P2PDial
	* description   : �����������
	* input			: pResourceID  ��ԴID
	* output		: N/A
	* return		: �ɹ�����0��ʧ�ܷ��ش�����
	**************************************************************************/
	ELTE_SDK_API ELTE_INT32 __SDK_CALL ELTE_SDK_P2PDial(const ELTE_CHAR* pResourceID);

	/**************************************************************************
	* name			: ELTE_SDK_P2PHalfDpxDial
	* description   : �ͷŰ�˫�����
	* input			: pResourceID  ����ĶԶ���ԴID
	* output		: N/A
	* return		: �ɹ�����0��ʧ�ܷ��ش�����
	**************************************************************************/
	ELTE_SDK_API ELTE_INT32 __SDK_CALL ELTE_SDK_P2PHalfDpxRelease(const ELTE_CHAR* pResourceID);

	/**************************************************************************
	* name			: ELTE_SDK_P2PHalfDpxDial
	* description   : �����˫�����
	* input			: pResourceID  ����ĶԶ���ԴID
	* output		: N/A
	* return		: �ɹ�����0��ʧ�ܷ��ش�����
	**************************************************************************/
	ELTE_SDK_API ELTE_INT32 __SDK_CALL ELTE_SDK_P2PHalfDpxDial(const ELTE_CHAR* pResourceID);

	/**************************************************************************
	* name			: ELTE_SDK_P2PRecv
	* description   : �����������
	* input			: pResourceID  ��ԴID
	* output		: N/A
	* return		: �ɹ�����0��ʧ�ܷ��ش�����
	**************************************************************************/
	ELTE_SDK_API ELTE_INT32 __SDK_CALL ELTE_SDK_P2PRecv(const ELTE_CHAR* pResourceID);

	/**************************************************************************
	* name			: ELTE_SDK_P2PReject
	* description   : �ܽ��������
	* input			: pResourceID  ��ԴID
	* output		: N/A
	* return		: �ɹ�����0��ʧ�ܷ��ش�����
	**************************************************************************/
	ELTE_SDK_API ELTE_INT32 __SDK_CALL ELTE_SDK_P2PReject(const ELTE_CHAR* pResourceID);

	/**************************************************************************
	* name			: ELTE_SDK_P2PHangup
	* description   : �Ҷ��������
	* input			: pResourceID  ��ԴID
	* output		: N/A
	* return		: �ɹ�����0��ʧ�ܷ��ش�����
	**************************************************************************/
	ELTE_SDK_API ELTE_INT32 __SDK_CALL ELTE_SDK_P2PHangup(const ELTE_CHAR* pResourceID);

	/**************************************************************************
	* name			: ELTE_SDK_P2PBreakoff
	* description   : ����̨ǿ����
	* input			: pResourceID  ��ԴID
	* output		: N/A
	* return		: �ɹ�����0��ʧ�ܷ��ش�����
	**************************************************************************/
	ELTE_SDK_API ELTE_INT32 __SDK_CALL ELTE_SDK_P2PBreakoff(const ELTE_CHAR* pResourceID);

	/**************************************************************************
	* name			: ELTE_SDK_P2PBreakin
	* description   : ������ǿ����+�����µ����
	* input			: pResourceID  ��ԴID
	* output		: N/A
	* return		: �ɹ�����0��ʧ�ܷ��ش�����
	**************************************************************************/
	ELTE_SDK_API ELTE_INT32 __SDK_CALL ELTE_SDK_P2PBreakin(const ELTE_CHAR* pResourceID);

	/**************************************************************************
	* name			: ELTE_SDK_PTTDial
	* description   : ����������̶�����ʱ���������Ȩ
	* input			: pGroupID  Ⱥ���
	* output		: N/A
	* return		: �ɹ�����0��ʧ�ܷ��ش�����
	**************************************************************************/
	ELTE_SDK_API ELTE_INT32 __SDK_CALL ELTE_SDK_PTTDial(const ELTE_CHAR* pGroupID);

	/**************************************************************************
	* name			: ELTE_SDK_PTTRelease
	* description   : �ͷŻ�Ȩ
	* input			: pGroupID  Ⱥ���
	* output		: N/A
	* return		: �ɹ�����0��ʧ�ܷ��ش�����
	**************************************************************************/
	ELTE_SDK_API ELTE_INT32 __SDK_CALL ELTE_SDK_PTTRelease(const ELTE_CHAR* pGroupID);

	/**************************************************************************
	* name			: ELTE_SDK_PTTHangup
	* description   : �˳����
	* input			: pGroupID  Ⱥ���
	* output		: N/A
	* return		: �ɹ�����0��ʧ�ܷ��ش�����
	**************************************************************************/
	ELTE_SDK_API ELTE_INT32 __SDK_CALL ELTE_SDK_PTTHangup(const ELTE_CHAR* pGroupID);

	/**************************************************************************
	* name			: ELTE_SDK_PTTEmergency
	* description   : ����������
	* input			: pGroupID  Ⱥ���
	* output		: N/A
	* return		: �ɹ�����0��ʧ�ܷ��ش�����
	**************************************************************************/
	ELTE_SDK_API ELTE_INT32 __SDK_CALL ELTE_SDK_PTTEmergency(const ELTE_CHAR* pGroupID);

	/**************************************************************************
	* name			: ELTE_SDK_GroupBreakoff
	* description   : ����̨ǿ�����
	* input			: pGroupID  Ⱥ���
	* output		: N/A
	* return		: �ɹ�����0��ʧ�ܷ��ش�����
	**************************************************************************/
	ELTE_SDK_API ELTE_INT32 __SDK_CALL ELTE_SDK_GroupBreakoff(const ELTE_CHAR* pGroupID);

	/**************************************************************************
	* name			: ELTE_SDK_VolMute
	* description   : ����ִ̨�о���
	* input			: pResourceID ��ԴID
	                  pMuteParam ��������
	* output		: N/A
	* return		: �ɹ�����0��ʧ�ܷ��ش�����
	**************************************************************************/
	ELTE_SDK_API ELTE_INT32 __SDK_CALL ELTE_SDK_VolMute(const ELTE_CHAR* pResourceID, const ELTE_CHAR* pMuteParam);

	/**************************************************************************
	* name			: ELTE_SDK_VolUnMute
	* description   : ����̨ȡ������
	* input			: pResourceID ��ԴID
						pUnMuteParam ȡ����������
	* output		: N/A
	* return		: �ɹ�����0��ʧ�ܷ��ش�����
	**************************************************************************/
	ELTE_SDK_API ELTE_INT32 __SDK_CALL ELTE_SDK_VolUnMute(const ELTE_CHAR* pResourceID, const ELTE_CHAR* pUnMuteParam);

	/**************************************************************************
	* name			: ELTE_SDK_GISSubscribe
	* description   : ����/ȥ����GIS�ն�
	* input			: pResourceID ��ԴID
	                  pGISParam GIS����
	* output		: N/A
	* return		: �ɹ�����0��ʧ�ܷ��ش�����
	**************************************************************************/
	ELTE_SDK_API ELTE_INT32 __SDK_CALL ELTE_SDK_GISSubscribe(const ELTE_CHAR* pResourceID, const ELTE_CHAR* pGISParam);

	/**************************************************************************
	* name			: ELTE_SDK_SDSSendMessage
	* description   : ���Ͷ�/����
	* input			: pResourceID ��ԴID
	                  pSDSParam ��/���Ų���
	* output		: N/A
	* return		: �ɹ�����0��ʧ�ܷ��ش�����
	**************************************************************************/
	ELTE_SDK_API ELTE_INT32 __SDK_CALL ELTE_SDK_SDSSendMessage(const ELTE_CHAR* pResourceID, const ELTE_CHAR* pSDSParam);

	/**************************************************************************
	* name			: ELTE_SDK_StartVideoDispatch
	* description   : ��ʼ��Ƶ�ַ�
	* input			: pResourceID ��ԴID
	                  pVideoDispatchParam ��Ƶ�ַ�����
	* output		: N/A
	* return		: �ɹ�����0��ʧ�ܷ��ش�����
	**************************************************************************/
	ELTE_SDK_API ELTE_INT32 __SDK_CALL ELTE_SDK_StartVideoDispatch(const ELTE_CHAR* pResourceID, const ELTE_CHAR* pVideoDispatchParam);

	/**************************************************************************
	* name			: ELTE_SDK_StopVideoDispatch
	* description   : ֹͣ��Ƶ�ַ�
	* input			: pResourceID ��ԴID
	                  pVideoDispatchParam ��Ƶ�ַ�����
	* output		: N/A
	* return		: �ɹ�����0��ʧ�ܷ��ش�����
	**************************************************************************/
	ELTE_SDK_API ELTE_INT32 __SDK_CALL ELTE_SDK_StopVideoDispatch(const ELTE_CHAR* pResourceID, const ELTE_CHAR* pVideoDispatchParam);

	/**************************************************************************
	* name			: ELTE_SDK_RecvVideoPlay
	* description   : ����̨������Ƶ�ش�
	* input			: pResourceID ��ԴID
	* output		: N/A
	* return		: �ɹ�����0��ʧ�ܷ��ش�����
	**************************************************************************/
	ELTE_SDK_API ELTE_INT32 __SDK_CALL ELTE_SDK_RecvVideoPlay(const ELTE_CHAR* pResourceID);

	/**************************************************************************
	* name			: ELTE_SDK_StartVWall
	* description   : ������Ƶ��ǽ
	* input			: pResVWallID ��ԴID
	                  pVWallStartParam ��Ƶ��ǽ����
	* output		: N/A
	* return		: �ɹ�����0��ʧ�ܷ��ش�����
	**************************************************************************/
	ELTE_SDK_API ELTE_INT32 __SDK_CALL ELTE_SDK_VWallStart(const ELTE_CHAR* pResVWallID, const ELTE_CHAR* pVWallStartParam);

	/**************************************************************************
	* name			: ELTE_SDK_GetDcVWallIDList
	* description   : ��ȡ��Ƶ��ǽID�б�
	* input			: DstObjId ��Ƶ��ǽ��Ŀ�ĵأ�Ϊһ����Ƶͨ��
					  pVWallIDList ��Ƶ��ǽĿ��ID�б�
	* output		: N/A
	* return		: �ɹ�����0��ʧ�ܷ��ش�����
	**************************************************************************/
	ELTE_SDK_API ELTE_INT32 __SDK_CALL ELTE_SDK_GetDcVWallIDList(ELTE_CHAR** pVWallIDList);

	/**************************************************************************
	* name			: ELTE_SDK_VWallStop
	* description   : ��ֹ��Ƶ��ǽ
	* input			: pResVWallID ��Ƶ��ǽ��Դ��Ϊһ������ͷ
	                  pVWallStopParam ��Ƶ��ǽ����
	* output		: N/A
	* return		: �ɹ�����0��ʧ�ܷ��ش�����
	**************************************************************************/
	ELTE_SDK_API ELTE_INT32 __SDK_CALL ELTE_SDK_VWallStop(const ELTE_CHAR* pResVWallID, const ELTE_CHAR* pVWallStopParam);

	/**************************************************************************
	* name			: ELTE_SDK_StartDiscreetListen
	* description   : �������ܼ���
	* input			: pResourceID ��Դ���󣬿�����Ⱥ����û�
	* output		: N/A
	* return		: �ɹ�����0��ʧ�ܷ��ش�����
	**************************************************************************/
	ELTE_SDK_API ELTE_INT32 __SDK_CALL ELTE_SDK_StartDiscreetListen(const ELTE_CHAR* pResourceID);

	/**************************************************************************
	* name			: ELTE_SDK_StopDiscreetListen
	* description   : ֹͣ���ܼ���
	* input			: pResourceID ��Դ���󣬿�����Ⱥ����û�
	* output		: N/A
	* return		: �ɹ�����0��ʧ�ܷ��ش�����
	**************************************************************************/
	ELTE_SDK_API ELTE_INT32 __SDK_CALL ELTE_SDK_StopDiscreetListen(const ELTE_CHAR* pResourceID);

	/**************************************************************************
	* name			: ELTE_SDK_StartEnvironmentListen
	* description   : ���𻷾�����
	* input			: pResourceID ��Դ���󣬿�����Ⱥ����û�
	* output		: N/A
	* return		: �ɹ�����0��ʧ�ܷ��ش�����
	**************************************************************************/
	ELTE_SDK_API ELTE_INT32 __SDK_CALL ELTE_SDK_StartEnvironmentListen(const ELTE_CHAR* pResourceID);

	/**************************************************************************
	* name			: ELTE_SDK_P2PTransfer
	* description   : �����˹�ת��
	* input			: pResourceID ��Դ����һ���Ƿ����˹�ת�ӵĵ���Ա
					  pP2PTransferParam �˹�ת�Ӳ���
	* output		: N/A
	* return		: �ɹ�����0��ʧ�ܷ��ش�����
	**************************************************************************/
	ELTE_SDK_API ELTE_INT32 __SDK_CALL ELTE_SDK_P2PTransfer(const ELTE_CHAR* pResourceID,const ELTE_CHAR* pP2PTransferParam);

	/**************************************************************************
	* name			: ELTE_SDK_CreatePatchGroup
	* description   : �����ɽ���
	* input			: pP2PTransferParam �ɽ������
	* output		: N/A
	* return		: �ɹ�����0��ʧ�ܷ��ش�����
	**************************************************************************/
	ELTE_SDK_API ELTE_INT32 __SDK_CALL ELTE_SDK_CreatePatchGroup(const ELTE_CHAR* pPatchGroupParam);

	/**************************************************************************
	* name			: ELTE_SDK_CancelPatchGroup
	* description   : ȡ���Ѵ����ɽ���
	* input			: pPatchGroupID ��Դ����һ���Ǵ����ɽ������š�
									ͨ��notifyResourceStatus���������
	* output		: N/A
	* return		: �ɹ�����0��ʧ�ܷ��ش�����
	**************************************************************************/
	ELTE_SDK_API ELTE_INT32 __SDK_CALL ELTE_SDK_CancelPatchGroup(const ELTE_CHAR* pPatchGroupID);

	/**************************************************************************
	* name			: ELTE_SDK_AddPatchGroupMember
	* description   : �����ɽ����Ա
	* input			: pPatchGroupParam �ɽ������
	* output		: N/A
	* return		: �ɹ�����0��ʧ�ܷ��ش�����
	**************************************************************************/
	ELTE_SDK_API ELTE_INT32 __SDK_CALL ELTE_SDK_AddPatchGroupMember(const ELTE_CHAR* pPatchGroupParam);

	/**************************************************************************
	* name			: ELTE_SDK_DeletePatchGroupMember
	* description   : ɾ���ɽ����Ա
	* input			: pPatchGroupParam �ɽ������
	* output		: N/A
	* return		: �ɹ�����0��ʧ�ܷ��ش�����
	**************************************************************************/
	ELTE_SDK_API ELTE_INT32 __SDK_CALL ELTE_SDK_DeletePatchGroupMember(const ELTE_CHAR* pPatchGroupParam);

	/**************************************************************************
	* name			: ELTE_SDK_GetPatchGroups
	* description   : ��ȡָ������̨�������ɽ����б�
	* input			: pDcUser ����̨�û�
					  pPatchGroups �õ���̨������ɽ�����Ϣ		
	* output		: N/A
	* return		: �ɹ�����0��ʧ�ܷ��ش�����
	**************************************************************************/
	ELTE_SDK_API ELTE_INT32 __SDK_CALL ELTE_SDK_GetPatchGroups(const ELTE_CHAR* pDcUser, ELTE_CHAR** pPatchGroups);

	/**************************************************************************
	* name			: ELTE_SDK_GetGroupMemberByPatchId
	* description   : ��ȡָ���ɽ������ĳ�Ա�б�
	* input			: pPatchGroupId �ɽ����
					  pPatchGroupMembers ���ɽ����Ա��Ϣ		
	* output		: N/A
	* return		: �ɹ�����0��ʧ�ܷ��ش�����
	**************************************************************************/
	ELTE_SDK_API ELTE_INT32 __SDK_CALL ELTE_SDK_GetGroupMemberByPatchId(const ELTE_CHAR* pPatchGroupId, ELTE_CHAR** pPatchGroupMembers);

	/**************************************************************************
	* name			: ELTE_SDK_GetPatchGroupInfo
	* description   : ��ȡָ���ɽ���������Ϣ
	* input			: pPatchGroupId �ɽ����
					  pPatchGroupInfo ���ɽӵ�������Ϣ		
	* output		: N/A
	* return		: �ɹ�����0��ʧ�ܷ��ش�����
	**************************************************************************/
	ELTE_SDK_API ELTE_INT32 __SDK_CALL ELTE_SDK_GetPatchGroupInfo(const ELTE_CHAR* pPatchGroupId, ELTE_CHAR** pPatchGroupInfo);

	/**************************************************************************
	* name			: ELTE_SDK_GetGisSubscription
	* description   : ��ȡ����̨����GIS�ϱ����ն��б�
	* input			: pResourceID ����̨ID	
	* output		: pGisQuerySubList ����GIS�ϱ����ն��б�
	* return		: �ɹ�����0��ʧ�ܷ��ش�����
	**************************************************************************/
	ELTE_SDK_API ELTE_INT32 __SDK_CALL ELTE_SDK_GetGisSubscription(const ELTE_CHAR* pResourceID, ELTE_CHAR** pGisQuerySubList);

	/**************************************************************************
	* name			: ELTE_SDK_ModifyDynamicGroup
	* description   : �޸Ķ�̬Ⱥ��
	* input			: pResourceID ������̬��ĵ���̨ ID
	                  pDynamicGroupInfo ��̬���޸���Ϣ
	* output		: N/A
	* return		: �ɹ�����0��ʧ�ܷ��ش�����
	**************************************************************************/
	ELTE_SDK_API ELTE_INT32 __SDK_CALL ELTE_SDK_ModifyDynamicGroup(const ELTE_CHAR* pResourceID, const ELTE_CHAR* pDynamicGroupInfo);


#ifdef __cplusplus
}
#endif //__cplusplus

#endif
