#pragma once

// El equipo generó clases contenedoras IDispatch con Microsoft Visual C++

// NOTA: no modificar el contenido de este archivo.  Si se utiliza Microsoft Visual C++ para generar
//  esta clase, se reemplazarán las modificaciones.

/////////////////////////////////////////////////////////////////////////////
// Clase contenedora de CIvs_ocxplayerctrlmain

class CIvs_ocxplayerctrlmain : public CWnd
{
protected:
	DECLARE_DYNCREATE(CIvs_ocxplayerctrlmain)
public:
	CLSID const& GetClsid()
	{
		static CLSID const clsid
			= { 0x3556A474, 0x8B23, 0x496F, { 0x9E, 0x5D, 0x38, 0xF7, 0xB7, 0x46, 0x54, 0xF4 } };
		return clsid;
	}
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle,
						const RECT& rect, CWnd* pParentWnd, UINT nID, 
						CCreateContext* pContext = NULL)
	{ 
		return CreateControl(GetClsid(), lpszWindowName, dwStyle, rect, pParentWnd, nID); 
	}

    BOOL Create(LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, 
				UINT nID, CFile* pPersist = NULL, BOOL bStorage = FALSE,
				BSTR bstrLicKey = NULL)
	{ 
		return CreateControl(GetClsid(), lpszWindowName, dwStyle, rect, pParentWnd, nID,
		pPersist, bStorage, bstrLicKey); 
	}

// Atributos
public:


// Operaciones
public:

// _DIVS_OCXPlayer

// Functions
//

	long IVS_OCX_NormalScreenDisplay()
	{
		long result;
		InvokeHelper(0x22, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	long IVS_OCX_FullScreenDisplay()
	{
		long result;
		InvokeHelper(0x23, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	long IVS_OCX_SetDeviceName(unsigned long ulWndID, LPCTSTR pDevName)
	{
		long result;
		static BYTE parms[] = VTS_UI4 VTS_BSTR ;
		InvokeHelper(0x24, DISPATCH_METHOD, VT_I4, (void*)&result, parms, ulWndID, pDevName);
		return result;
	}
	unsigned long IVS_OCX_PlaySound(long lWndID)
	{
		unsigned long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x25, DISPATCH_METHOD, VT_UI4, (void*)&result, parms, lWndID);
		return result;
	}
	unsigned long IVS_OCX_StopSound(long lWndID)
	{
		unsigned long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x26, DISPATCH_METHOD, VT_UI4, (void*)&result, parms, lWndID);
		return result;
	}
	long IVS_OCX_SetVolume(long lWndID, unsigned long ulVolumeValue)
	{
		long result;
		static BYTE parms[] = VTS_I4 VTS_UI4 ;
		InvokeHelper(0x27, DISPATCH_METHOD, VT_I4, (void*)&result, parms, lWndID, ulVolumeValue);
		return result;
	}
	unsigned long IVS_OCX_GetVolume(long lWndID)
	{
		unsigned long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x28, DISPATCH_METHOD, VT_UI4, (void*)&result, parms, lWndID);
		return result;
	}
	long IVS_OCX_SetTitlebar(long lShowStatus)
	{
		long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x29, DISPATCH_METHOD, VT_I4, (void*)&result, parms, lShowStatus);
		return result;
	}
	unsigned long IVS_OCX_SetActiveWnd(unsigned long ulWndID)
	{
		unsigned long result;
		static BYTE parms[] = VTS_UI4 ;
		InvokeHelper(0x2a, DISPATCH_METHOD, VT_UI4, (void*)&result, parms, ulWndID);
		return result;
	}
	unsigned long IVS_OCX_GetSelectWnd()
	{
		unsigned long result;
		InvokeHelper(0x2b, DISPATCH_METHOD, VT_UI4, (void*)&result, NULL);
		return result;
	}
	CString IVS_OCX_GetCameraByWnd(unsigned long ulWndID)
	{
		CString result;
		static BYTE parms[] = VTS_UI4 ;
		InvokeHelper(0x2c, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, ulWndID);
		return result;
	}
	long IVS_OCX_SetToolbarButtonStatus(long lWndID, unsigned long ulToolbarBtn, unsigned long ulButtonStatus)
	{
		long result;
		static BYTE parms[] = VTS_I4 VTS_UI4 VTS_UI4 ;
		InvokeHelper(0x2d, DISPATCH_METHOD, VT_I4, (void*)&result, parms, lWndID, ulToolbarBtn, ulButtonStatus);
		return result;
	}
	long IVS_OCX_ShowTitlebar(BOOL bShow)
	{
		long result;
		static BYTE parms[] = VTS_BOOL ;
		InvokeHelper(0x2e, DISPATCH_METHOD, VT_I4, (void*)&result, parms, bShow);
		return result;
	}
	long IVS_OCX_ShowToolbar(BOOL bShow)
	{
		long result;
		static BYTE parms[] = VTS_BOOL ;
		InvokeHelper(0x2f, DISPATCH_METHOD, VT_I4, (void*)&result, parms, bShow);
		return result;
	}
	unsigned long IVS_OCX_Set3DPTZ(unsigned long ulWndID, unsigned long ulIsStart3D)
	{
		unsigned long result;
		static BYTE parms[] = VTS_UI4 VTS_UI4 ;
		InvokeHelper(0x30, DISPATCH_METHOD, VT_UI4, (void*)&result, parms, ulWndID, ulIsStart3D);
		return result;
	}
	CString IVS_OCX_StartVoiceTalkback(LPCTSTR pTalkParam, LPCTSTR pCameraCode)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR ;
		InvokeHelper(0x31, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, pTalkParam, pCameraCode);
		return result;
	}
	long IVS_OCX_StopVoiceTalkback(unsigned long ulTalkbackHandle)
	{
		long result;
		static BYTE parms[] = VTS_UI4 ;
		InvokeHelper(0x32, DISPATCH_METHOD, VT_I4, (void*)&result, parms, ulTalkbackHandle);
		return result;
	}
	long IVS_OCX_SetTalkbackVolume(unsigned long ulVolumeValue)
	{
		long result;
		static BYTE parms[] = VTS_UI4 ;
		InvokeHelper(0x33, DISPATCH_METHOD, VT_I4, (void*)&result, parms, ulVolumeValue);
		return result;
	}
	unsigned long IVS_OCX_GetTalkbackVolume()
	{
		unsigned long result;
		InvokeHelper(0x34, DISPATCH_METHOD, VT_UI4, (void*)&result, NULL);
		return result;
	}
	unsigned long IVS_OCX_SetCameraAlias(LPCTSTR pCameraCode, LPCTSTR pAlias)
	{
		unsigned long result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR ;
		InvokeHelper(0x35, DISPATCH_METHOD, VT_UI4, (void*)&result, parms, pCameraCode, pAlias);
		return result;
	}
	CString IVS_OCX_GetCameraAlias(LPCTSTR pCameraCode)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x36, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, pCameraCode);
		return result;
	}
	CString IVS_OCX_GetAllCameraAlias()
	{
		CString result;
		InvokeHelper(0x37, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	long IVS_OCX_StartRealPlay(LPCTSTR pMediaPara, LPCTSTR pCameraCode, long lWndID)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_I4 ;
		InvokeHelper(0x3f, DISPATCH_METHOD, VT_I4, (void*)&result, parms, pMediaPara, pCameraCode, lWndID);
		return result;
	}
	long IVS_OCX_StopRealPlay(long lWndID)
	{
		long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x40, DISPATCH_METHOD, VT_I4, (void*)&result, parms, lWndID);
		return result;
	}
	long IVS_OCX_GetMouseWnd()
	{
		long result;
		InvokeHelper(0x49, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	long IVS_OCX_GetFreeWnd()
	{
		long result;
		InvokeHelper(0x4a, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	long IVS_OCX_Init()
	{
		long result;
		InvokeHelper(0x50, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	long IVS_OCX_Cleanup()
	{
		long result;
		InvokeHelper(0x51, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	long IVS_OCX_GetVersion()
	{
		long result;
		InvokeHelper(0x52, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	unsigned long IVS_OCX_StopAllRealPlay()
	{
		unsigned long result;
		InvokeHelper(0x53, DISPATCH_METHOD, VT_UI4, (void*)&result, NULL);
		return result;
	}
	long IVS_OCX_SetWndLayout(unsigned long lWindowsNum)
	{
		long result;
		static BYTE parms[] = VTS_UI4 ;
		InvokeHelper(0x55, DISPATCH_METHOD, VT_I4, (void*)&result, parms, lWindowsNum);
		return result;
	}
	unsigned long IVS_OCX_SetColor(unsigned long ulColor)
	{
		unsigned long result;
		static BYTE parms[] = VTS_UI4 ;
		InvokeHelper(0x56, DISPATCH_METHOD, VT_UI4, (void*)&result, parms, ulColor);
		return result;
	}
	long IVS_OCX_Login(LPCTSTR pUserName, LPCTSTR pPWD, LPCTSTR pServerIP, LPCTSTR pPort, unsigned long ulClientType)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_UI4 ;
		InvokeHelper(0x57, DISPATCH_METHOD, VT_I4, (void*)&result, parms, pUserName, pPWD, pServerIP, pPort, ulClientType);
		return result;
	}
	long IVS_OCX_SetToolbar(unsigned long ulToolbarFlag)
	{
		long result;
		static BYTE parms[] = VTS_UI4 ;
		InvokeHelper(0x58, DISPATCH_METHOD, VT_I4, (void*)&result, parms, ulToolbarFlag);
		return result;
	}
	CString IVS_OCX_AddUser(LPCTSTR pReqXml)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x59, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, pReqXml);
		return result;
	}
	long IVS_OCX_DeleteUser(LPCTSTR pDomainCode, unsigned long ulUserID)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_UI4 ;
		InvokeHelper(0x5a, DISPATCH_METHOD, VT_I4, (void*)&result, parms, pDomainCode, ulUserID);
		return result;
	}
	CString IVS_OCX_GetUserList(LPCTSTR pUnifiedQuery)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x5b, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, pUnifiedQuery);
		return result;
	}
	long IVS_OCX_Logout()
	{
		long result;
		InvokeHelper(0x5c, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	unsigned long IVS_OCX_SetLocalAlarmConfig(LPCTSTR pAlarmParm)
	{
		unsigned long result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x5d, DISPATCH_METHOD, VT_UI4, (void*)&result, parms, pAlarmParm);
		return result;
	}
	CString IVS_OCX_GetLocalAlarmConfig()
	{
		CString result;
		InvokeHelper(0x5e, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	unsigned long IVS_OCX_SetLocalRecordConfig(LPCTSTR pRecordParm)
	{
		unsigned long result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x5f, DISPATCH_METHOD, VT_UI4, (void*)&result, parms, pRecordParm);
		return result;
	}
	CString IVS_OCX_GetLocalRecordConfig()
	{
		CString result;
		InvokeHelper(0x60, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	unsigned long IVS_OCX_SetLocalCaptureConfig(LPCTSTR pCaptureParm)
	{
		unsigned long result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x61, DISPATCH_METHOD, VT_UI4, (void*)&result, parms, pCaptureParm);
		return result;
	}
	CString IVS_OCX_GetLocalCaptureConfig()
	{
		CString result;
		InvokeHelper(0x62, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	unsigned long IVS_OCX_SetLocalNetWorkConfig(LPCTSTR pNetWorkParm)
	{
		unsigned long result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x63, DISPATCH_METHOD, VT_UI4, (void*)&result, parms, pNetWorkParm);
		return result;
	}
	CString IVS_OCX_GetLocalNetWorkConfig()
	{
		CString result;
		InvokeHelper(0x64, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	unsigned long IVS_OCX_SetLocalPTZConfig(LPCTSTR pPTZParm)
	{
		unsigned long result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x65, DISPATCH_METHOD, VT_UI4, (void*)&result, parms, pPTZParm);
		return result;
	}
	CString IVS_OCX_GetLocalPTZConfig()
	{
		CString result;
		InvokeHelper(0x66, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	unsigned long IVS_OCX_SetLocalCameraLinkConfig(LPCTSTR pCameraCode, unsigned long ulLinkMode)
	{
		unsigned long result;
		static BYTE parms[] = VTS_BSTR VTS_UI4 ;
		InvokeHelper(0x67, DISPATCH_METHOD, VT_UI4, (void*)&result, parms, pCameraCode, ulLinkMode);
		return result;
	}
	unsigned long IVS_OCX_GetLocalCameraLinkConfig(LPCTSTR pCameraCode)
	{
		unsigned long result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x68, DISPATCH_METHOD, VT_UI4, (void*)&result, parms, pCameraCode);
		return result;
	}
	unsigned long IVS_OCX_DelLocalCameraLinkConfig(LPCTSTR pCameraCode)
	{
		unsigned long result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x69, DISPATCH_METHOD, VT_UI4, (void*)&result, parms, pCameraCode);
		return result;
	}
	CString IVS_OCX_GetUserInfo(LPCTSTR pDomainCode, unsigned long ulUserID)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR VTS_UI4 ;
		InvokeHelper(0x6a, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, pDomainCode, ulUserID);
		return result;
	}
	long IVS_OCX_ChangePWD(LPCTSTR pOldPWD, LPCTSTR pNewPWD)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR ;
		InvokeHelper(0x6b, DISPATCH_METHOD, VT_I4, (void*)&result, parms, pOldPWD, pNewPWD);
		return result;
	}
	long IVS_OCX_ResetPWD(LPCTSTR pDomainCode, unsigned long ulUserID, LPCTSTR pNewPWD)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_UI4 VTS_BSTR ;
		InvokeHelper(0x6c, DISPATCH_METHOD, VT_I4, (void*)&result, parms, pDomainCode, ulUserID, pNewPWD);
		return result;
	}
	CString IVS_OCX_GetUserGroupList(LPCTSTR pReqXml)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x6d, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, pReqXml);
		return result;
	}
	CString IVS_OCX_ModifyRecordPlan(LPCTSTR pRecordPlan)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x72, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, pRecordPlan);
		return result;
	}
	CString IVS_OCX_DeleteRecordPlan(LPCTSTR pDelRecPlanXML)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x73, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, pDelRecPlanXML);
		return result;
	}
	CString IVS_OCX_GetRecordPlan(LPCTSTR pRecordPlanListReq)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x74, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, pRecordPlanListReq);
		return result;
	}
	CString IVS_OCX_AddDevice(LPCTSTR pReqDev)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x75, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, pReqDev);
		return result;
	}
	CString IVS_OCX_QueryDeviceList(unsigned long ulDeviceType, LPCTSTR pQueryXml)
	{
		CString result;
		static BYTE parms[] = VTS_UI4 VTS_BSTR ;
		InvokeHelper(0x77, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, ulDeviceType, pQueryXml);
		return result;
	}
	long IVS_OCX_ModifyUser(LPCTSTR pReqXml)
	{
		long result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x78, DISPATCH_METHOD, VT_I4, (void*)&result, parms, pReqXml);
		return result;
	}
	unsigned long IVS_OCX_AddKeyword(LPCTSTR pCameraCode, LPCTSTR pDeviceKeyWord)
	{
		unsigned long result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR ;
		InvokeHelper(0x7a, DISPATCH_METHOD, VT_UI4, (void*)&result, parms, pCameraCode, pDeviceKeyWord);
		return result;
	}
	unsigned long IVS_OCX_DelKeyword(LPCTSTR pCameraCode)
	{
		unsigned long result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x7b, DISPATCH_METHOD, VT_UI4, (void*)&result, parms, pCameraCode);
		return result;
	}
	CString IVS_OCX_GetKeyword()
	{
		CString result;
		InvokeHelper(0x7c, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	CString IVS_OCX_AddUserGroup(LPCTSTR pUserGroup)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x7d, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, pUserGroup);
		return result;
	}
	long IVS_OCX_DeleteUserGroup(LPCTSTR pDomainCode, unsigned long ulUserGroupID)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_UI4 ;
		InvokeHelper(0x7e, DISPATCH_METHOD, VT_I4, (void*)&result, parms, pDomainCode, ulUserGroupID);
		return result;
	}
	long IVS_OCX_ModifyUserGroup(LPCTSTR pUserGroup)
	{
		long result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x7f, DISPATCH_METHOD, VT_I4, (void*)&result, parms, pUserGroup);
		return result;
	}
	long IVS_OCX_MoveUserGroup(LPCTSTR pUserGroup)
	{
		long result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x80, DISPATCH_METHOD, VT_I4, (void*)&result, parms, pUserGroup);
		return result;
	}
	CString IVS_OCX_AddRole(LPCTSTR pRoleInfo)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x81, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, pRoleInfo);
		return result;
	}
	long IVS_OCX_DeleteRole(LPCTSTR pDomainCode, unsigned long ulRoleID)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_UI4 ;
		InvokeHelper(0x82, DISPATCH_METHOD, VT_I4, (void*)&result, parms, pDomainCode, ulRoleID);
		return result;
	}
	long IVS_OCX_ModifyRole(LPCTSTR pRoleInfo)
	{
		long result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x83, DISPATCH_METHOD, VT_I4, (void*)&result, parms, pRoleInfo);
		return result;
	}
	CString IVS_OCX_GetRoleList(LPCTSTR pDomainCode)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x84, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, pDomainCode);
		return result;
	}
	CString IVS_OCX_GetOnlineUser(LPCTSTR pUnifiedQuery)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x85, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, pUnifiedQuery);
		return result;
	}
	CString IVS_OCX_AddAlarmLevel(LPCTSTR pAlarmLevel)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x86, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, pAlarmLevel);
		return result;
	}
	long IVS_OCX_ModifyAlarmLevel(LPCTSTR pAlarmLevel)
	{
		long result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x87, DISPATCH_METHOD, VT_I4, (void*)&result, parms, pAlarmLevel);
		return result;
	}
	long IVS_OCX_DeleteAlarmLevel(unsigned long ulAlarmLevelID)
	{
		long result;
		static BYTE parms[] = VTS_UI4 ;
		InvokeHelper(0x88, DISPATCH_METHOD, VT_I4, (void*)&result, parms, ulAlarmLevelID);
		return result;
	}
	long IVS_OCX_SetRecordSpace(LPCTSTR pRecordSpace)
	{
		long result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x89, DISPATCH_METHOD, VT_I4, (void*)&result, parms, pRecordSpace);
		return result;
	}
	long IVS_OCX_DeleteRecordSpace(LPCTSTR pRecordSpace)
	{
		long result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x8a, DISPATCH_METHOD, VT_I4, (void*)&result, parms, pRecordSpace);
		return result;
	}
	long IVS_OCX_ModifyRecordSpace(LPCTSTR pRecordSpace)
	{
		long result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x8b, DISPATCH_METHOD, VT_I4, (void*)&result, parms, pRecordSpace);
		return result;
	}
	long IVS_OCX_GetRecordSpace(LPCTSTR pRecordSpace)
	{
		long result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x8c, DISPATCH_METHOD, VT_I4, (void*)&result, parms, pRecordSpace);
		return result;
	}
	long IVS_OCX_AddHelpInfo(LPCTSTR helpInfo)
	{
		long result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x8d, DISPATCH_METHOD, VT_I4, (void*)&result, parms, helpInfo);
		return result;
	}
	long IVS_OCX_ModifyHelpInfo(LPCTSTR helpInfo)
	{
		long result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x8e, DISPATCH_METHOD, VT_I4, (void*)&result, parms, helpInfo);
		return result;
	}
	CString IVS_OCX_GetOperationLog(LPCTSTR pUnifiedQuery)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x90, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, pUnifiedQuery);
		return result;
	}
	long IVS_OCX_SetUserDeviceList(LPCTSTR pReqXml)
	{
		long result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x91, DISPATCH_METHOD, VT_I4, (void*)&result, parms, pReqXml);
		return result;
	}
	CString IVS_OCX_GetUserDeviceList(LPCTSTR pUnifiedQuery)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x92, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, pUnifiedQuery);
		return result;
	}
	long IVS_OCX_SignOutOnlineUser(LPCTSTR pDomainCode, unsigned long ulUserOnlineID)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_UI4 ;
		InvokeHelper(0x93, DISPATCH_METHOD, VT_I4, (void*)&result, parms, pDomainCode, ulUserOnlineID);
		return result;
	}
	long IVS_OCX_SetCustomWndLayout(unsigned long ulLayoutID, LPCTSTR pLayoutXml)
	{
		long result;
		static BYTE parms[] = VTS_UI4 VTS_BSTR ;
		InvokeHelper(0x95, DISPATCH_METHOD, VT_I4, (void*)&result, parms, ulLayoutID, pLayoutXml);
		return result;
	}
	CString IVS_OCX_GetCustomWndLayout(unsigned long ulLayoutID)
	{
		CString result;
		static BYTE parms[] = VTS_UI4 ;
		InvokeHelper(0x96, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, ulLayoutID);
		return result;
	}
	CString IVS_OCX_GetRecordList(LPCTSTR pCameraCode, unsigned long lRecordMethod, LPCTSTR pStartTime, LPCTSTR pEndTime, unsigned long lFromIndex, unsigned long lToIndex)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR VTS_UI4 VTS_BSTR VTS_BSTR VTS_UI4 VTS_UI4 ;
		InvokeHelper(0x98, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, pCameraCode, lRecordMethod, pStartTime, pEndTime, lFromIndex, lToIndex);
		return result;
	}
	long IVS_OCX_GetGPUDecodeAbility()
	{
		long result;
		InvokeHelper(0x99, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	CString IVS_OCX_GetNVRList(LPCTSTR pUnifiedQuery)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x9a, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, pUnifiedQuery);
		return result;
	}
	CString IVS_OCX_GetDeviceGroup(LPCTSTR pReqXml)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x9b, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, pReqXml);
		return result;
	}
	CString IVS_OCX_GetDeviceInfo(LPCTSTR pReqXml)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x9c, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, pReqXml);
		return result;
	}
	CString IVS_OCX_DeleteDevice(LPCTSTR pReqXml)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x9d, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, pReqXml);
		return result;
	}
	CString IVS_OCX_AddRecordPlan(LPCTSTR pRecordPlan)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x9e, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, pRecordPlan);
		return result;
	}
	long IVS_OCX_ModifyDeviceGroupName(LPCTSTR pReqXml)
	{
		long result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x9f, DISPATCH_METHOD, VT_I4, (void*)&result, parms, pReqXml);
		return result;
	}
	long IVS_OCX_MoveDeviceGroup(LPCTSTR pReqXml)
	{
		long result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0xa0, DISPATCH_METHOD, VT_I4, (void*)&result, parms, pReqXml);
		return result;
	}
	CString IVS_OCX_AddDeviceGroup(LPCTSTR pReqXml)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0xa1, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, pReqXml);
		return result;
	}
	long IVS_OCX_DeleteDeviceGroup(LPCTSTR pReqXml)
	{
		long result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0xa2, DISPATCH_METHOD, VT_I4, (void*)&result, parms, pReqXml);
		return result;
	}
	long IVS_OCX_DeleteDeviceFromGroup(LPCTSTR pReqXml)
	{
		long result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0xa4, DISPATCH_METHOD, VT_I4, (void*)&result, parms, pReqXml);
		return result;
	}
	CString IVS_OCX_GetAlarmLevelList()
	{
		CString result;
		InvokeHelper(0xa5, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	long IVS_OCX_SetDeviceConfig(long iConfigType, LPCTSTR pDevCode, LPCTSTR pReqXml)
	{
		long result;
		static BYTE parms[] = VTS_I4 VTS_BSTR VTS_BSTR ;
		InvokeHelper(0xa6, DISPATCH_METHOD, VT_I4, (void*)&result, parms, iConfigType, pDevCode, pReqXml);
		return result;
	}
	CString IVS_OCX_GetDeviceConfig(long iConfigType, LPCTSTR pReqXml)
	{
		CString result;
		static BYTE parms[] = VTS_I4 VTS_BSTR ;
		InvokeHelper(0xa7, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, iConfigType, pReqXml);
		return result;
	}
	CString IVS_OCX_GetAlarmTypeList(LPCTSTR pReqXml)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0xa8, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, pReqXml);
		return result;
	}
	CString IVS_OCX_Aes256CbcEncode(LPCTSTR pszPlain)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0xa9, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, pszPlain);
		return result;
	}
	CString IVS_OCX_Aes256CbcDecode(LPCTSTR pszCipher)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0xaa, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, pszCipher);
		return result;
	}
	CString IVS_OCX_GetAlarmLevel(long uiAlarmLevelID)
	{
		CString result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0xac, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, uiAlarmLevelID);
		return result;
	}
	long IVS_OCX_DeleteHelpInfo(LPCTSTR helpInfo)
	{
		long result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0xad, DISPATCH_METHOD, VT_I4, (void*)&result, parms, helpInfo);
		return result;
	}
	CString IVS_OCX_QueryHelpInfo(LPCTSTR helpInfo)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0xae, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, helpInfo);
		return result;
	}
	CString IVS_OCX_GetMediaInfo(unsigned long ulWndID)
	{
		CString result;
		static BYTE parms[] = VTS_UI4 ;
		InvokeHelper(0xaf, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, ulWndID);
		return result;
	}
	long IVS_OCX_SetAlarmTypeLevel(LPCTSTR pReqXml)
	{
		long result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0xb0, DISPATCH_METHOD, VT_I4, (void*)&result, parms, pReqXml);
		return result;
	}
	long IVS_OCX_SetDisplayScale(long lDisplayScale)
	{
		long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0xb1, DISPATCH_METHOD, VT_I4, (void*)&result, parms, lDisplayScale);
		return result;
	}
	CString IVS_OCX_AddFavoriteDevice(LPCTSTR pReqXml)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0xb2, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, pReqXml);
		return result;
	}
	long IVS_OCX_DelFavoriteDevice(LPCTSTR pReqXml)
	{
		long result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0xb3, DISPATCH_METHOD, VT_I4, (void*)&result, parms, pReqXml);
		return result;
	}
	long IVS_OCX_MoveFavoriteDevice(LPCTSTR pReqXml)
	{
		long result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0xb4, DISPATCH_METHOD, VT_I4, (void*)&result, parms, pReqXml);
		return result;
	}
	CString IVS_OCX_AddFavoriteFolder(LPCTSTR pReqXml)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0xb5, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, pReqXml);
		return result;
	}
	long IVS_OCX_DelFavoriteFolder(LPCTSTR pReqXml)
	{
		long result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0xb6, DISPATCH_METHOD, VT_I4, (void*)&result, parms, pReqXml);
		return result;
	}
	long IVS_OCX_ModFavoriteFolder(LPCTSTR pReqXml)
	{
		long result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0xb7, DISPATCH_METHOD, VT_I4, (void*)&result, parms, pReqXml);
		return result;
	}
	long IVS_OCX_MoveFavoriteFolder(LPCTSTR pReqXml)
	{
		long result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0xb8, DISPATCH_METHOD, VT_I4, (void*)&result, parms, pReqXml);
		return result;
	}
	CString IVS_OCX_GetFavoriteDevice()
	{
		CString result;
		InvokeHelper(0xb9, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	long IVS_OCX_AllocAreaGuardPlan(LPWSTR pReqXml)
	{
		long result;
		static BYTE parms[] = VTS_UNKNOWN ;
		InvokeHelper(0xbd, DISPATCH_METHOD, VT_I4, (void*)&result, parms, pReqXml);
		return result;
	}
	long IVS_OCX_SubscribeAlarm(LPCTSTR pReqXml)
	{
		long result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0xba, DISPATCH_METHOD, VT_I4, (void*)&result, parms, pReqXml);
		return result;
	}
	CString IVS_OCX_SubscribeAlarmQuery(LPCTSTR pReqXml)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0xbb, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, pReqXml);
		return result;
	}
	CString IVS_OCX_GetDomainRoute()
	{
		CString result;
		InvokeHelper(0xbe, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	long IVS_OCX_ModifyAlarmArea(LPCTSTR pReqXml)
	{
		long result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0xbf, DISPATCH_METHOD, VT_I4, (void*)&result, parms, pReqXml);
		return result;
	}
	long IVS_OCX_DeleteAlarmArea(LPWSTR pDomainCode, unsigned long ulAlarmAreaID)
	{
		long result;
		static BYTE parms[] = VTS_UNKNOWN VTS_UI4 ;
		InvokeHelper(0xc0, DISPATCH_METHOD, VT_I4, (void*)&result, parms, pDomainCode, ulAlarmAreaID);
		return result;
	}
	CString IVS_OCX_GetAlarmAreaList(LPCTSTR pReqXml)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0xc1, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, pReqXml);
		return result;
	}
	long IVS_OCX_ModifyAreaGuardPlan(long pReqXml)
	{
		long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0xc3, DISPATCH_METHOD, VT_I4, (void*)&result, parms, pReqXml);
		return result;
	}
	long IVS_OCX_DeleteAreaGuardPlan(LPWSTR pDomainCode, unsigned long ulAlarmAreaID)
	{
		long result;
		static BYTE parms[] = VTS_UNKNOWN VTS_UI4 ;
		InvokeHelper(0xc4, DISPATCH_METHOD, VT_I4, (void*)&result, parms, pDomainCode, ulAlarmAreaID);
		return result;
	}
	CString IVS_OCX_GetAreaGuardPlan(LPWSTR pDomainCode, unsigned long ulAlarmAreaID)
	{
		CString result;
		static BYTE parms[] = VTS_UNKNOWN VTS_UI4 ;
		InvokeHelper(0xc5, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, pDomainCode, ulAlarmAreaID);
		return result;
	}
	CString IVS_OCX_AddAlarmArea(LPCTSTR pReqXml)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0xc6, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, pReqXml);
		return result;
	}
	CString IVS_OCX_GetAlarmAreaInfo(LPWSTR pDomainCode, unsigned long ulAlarmAreaID)
	{
		CString result;
		static BYTE parms[] = VTS_UNKNOWN VTS_UI4 ;
		InvokeHelper(0xc7, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, pDomainCode, ulAlarmAreaID);
		return result;
	}
	long IVS_OCX_UserAuthentication(LPCTSTR pPWD)
	{
		long result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0xc2, DISPATCH_METHOD, VT_I4, (void*)&result, parms, pPWD);
		return result;
	}
	CString IVS_OCX_AddAlarmLinkage(LPCTSTR pReqXml)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0xc8, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, pReqXml);
		return result;
	}
	long IVS_OCX_ModifyAlarmLinkage(LPCTSTR pReqXml)
	{
		long result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0xcb, DISPATCH_METHOD, VT_I4, (void*)&result, parms, pReqXml);
		return result;
	}
	long IVS_OCX_DeleteAlarmLinkage(LPCTSTR pReqXml)
	{
		long result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0xcc, DISPATCH_METHOD, VT_I4, (void*)&result, parms, pReqXml);
		return result;
	}
	CString IVS_OCX_GetAlarmLinkage(LPCTSTR pReqXml)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0xc9, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, pReqXml);
		return result;
	}
	CString IVS_OCX_GetAlarmLinkageList(LPCTSTR pReqXml)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0xca, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, pReqXml);
		return result;
	}
	long IVS_OCX_AddDeviceToGroup(LPCTSTR pReqXml)
	{
		long result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0xd4, DISPATCH_METHOD, VT_I4, (void*)&result, parms, pReqXml);
		return result;
	}
	CString IVS_OCX_GetAlarmEventList(LPCTSTR pReqXml)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0xd5, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, pReqXml);
		return result;
	}
	long IVS_OCX_StartAlarmAreaGuard(LPWSTR pDomainCode, unsigned long ulAlarmAreaID)
	{
		long result;
		static BYTE parms[] = VTS_UNKNOWN VTS_UI4 ;
		InvokeHelper(0xd6, DISPATCH_METHOD, VT_I4, (void*)&result, parms, pDomainCode, ulAlarmAreaID);
		return result;
	}
	long IVS_OCX_StopAlarmAreaGuard(LPWSTR pDomainCode, unsigned long ulAlarmAreaID)
	{
		long result;
		static BYTE parms[] = VTS_UNKNOWN VTS_UI4 ;
		InvokeHelper(0xd7, DISPATCH_METHOD, VT_I4, (void*)&result, parms, pDomainCode, ulAlarmAreaID);
		return result;
	}
	long IVS_OCX_AlarmCommission(LPCTSTR pReqXml)
	{
		long result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0xde, DISPATCH_METHOD, VT_I4, (void*)&result, parms, pReqXml);
		return result;
	}
	CString IVS_OCX_GetAlarmEventInfo(long uiAlarmEventId, LPCTSTR pAlarmInCode)
	{
		CString result;
		static BYTE parms[] = VTS_I4 VTS_BSTR ;
		InvokeHelper(0xd9, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, uiAlarmEventId, pAlarmInCode);
		return result;
	}
	CString IVS_OCX_QueryRecordList(LPCTSTR pUnifiedQuery)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0xda, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, pUnifiedQuery);
		return result;
	}
	CString IVS_OCX_IA(unsigned long ulInterfaceType, LPCTSTR pReqXml)
	{
		CString result;
		static BYTE parms[] = VTS_UI4 VTS_BSTR ;
		InvokeHelper(0xdb, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, ulInterfaceType, pReqXml);
		return result;
	}
	void IVS_OCX_SetPlayQualityMode(unsigned long ulWndID, long lpalyQualityMode)
	{
		static BYTE parms[] = VTS_UI4 VTS_I4 ;
		InvokeHelper(0xdc, DISPATCH_METHOD, VT_EMPTY, NULL, parms, ulWndID, lpalyQualityMode);
	}
	CString IVS_OCX_GetChannelList(LPCTSTR pDevCode)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0xe0, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, pDevCode);
		return result;
	}
	CString IVS_OCX_GetRecordPolicyByTime(LPCTSTR pCameraCode)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0xdf, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, pCameraCode);
		return result;
	}
	long IVS_OCX_AlarmReport(LPCTSTR pAlarmReport)
	{
		long result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0xe5, DISPATCH_METHOD, VT_I4, (void*)&result, parms, pAlarmReport);
		return result;
	}
	long IVS_OCX_AlarmConfirm(LPCTSTR pReqXml)
	{
		long result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0xe1, DISPATCH_METHOD, VT_I4, (void*)&result, parms, pReqXml);
		return result;
	}
	long IVS_OCX_AlarmCancel(LPCTSTR pReqXml)
	{
		long result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0xe2, DISPATCH_METHOD, VT_I4, (void*)&result, parms, pReqXml);
		return result;
	}
	CString IVS_OCX_PtzControl(LPCTSTR pCameraCode, long lOperateCode, LPCTSTR pControlPara1, LPCTSTR pControlPara2)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR VTS_I4 VTS_BSTR VTS_BSTR ;
		InvokeHelper(0xe3, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, pCameraCode, lOperateCode, pControlPara1, pControlPara2);
		return result;
	}
	CString IVS_OCX_GetRecordStatus(LPCTSTR pCameraCode, unsigned long ulRecordMethod)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR VTS_UI4 ;
		InvokeHelper(0xe4, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, pCameraCode, ulRecordMethod);
		return result;
	}
	long IVS_OCX_EnableGPU(long bEnable)
	{
		long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0xe6, DISPATCH_METHOD, VT_I4, (void*)&result, parms, bEnable);
		return result;
	}
	long IVS_OCX_SetRecordPolicyByTime(LPCTSTR pRecordPolicyXml)
	{
		long result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0xe7, DISPATCH_METHOD, VT_I4, (void*)&result, parms, pRecordPolicyXml);
		return result;
	}
	CString IVS_OCX_GetUserID()
	{
		CString result;
		InvokeHelper(0xe8, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	long IVS_OCX_BackupUserData()
	{
		long result;
		InvokeHelper(0xe9, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	long IVS_OCX_RestoreUserData()
	{
		long result;
		InvokeHelper(0xea, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	CString IVS_OCX_GetRoleInfoByRoleID(LPCTSTR pDomainCode, unsigned long ulRoleID)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR VTS_UI4 ;
		InvokeHelper(0xeb, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, pDomainCode, ulRoleID);
		return result;
	}
	CString IVS_OCX_GetRoleInfoByUserID(LPCTSTR pDomainCode, unsigned long ulUserID)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR VTS_UI4 ;
		InvokeHelper(0xec, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, pDomainCode, ulUserID);
		return result;
	}
	CString IVS_OCX_GetDefaultRoleAccountRule(LPCTSTR pDomainCode)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0xed, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, pDomainCode);
		return result;
	}
	CString IVS_OCX_GetOperationRightGroup(LPCTSTR pDomainCode)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0xee, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, pDomainCode);
		return result;
	}
	long IVS_OCX_CheckPWDByRole(LPCTSTR pDomainCode, unsigned long ulRoleID, LPCTSTR pLoginName, LPCTSTR pPWD)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_UI4 VTS_BSTR VTS_BSTR ;
		InvokeHelper(0xef, DISPATCH_METHOD, VT_I4, (void*)&result, parms, pDomainCode, ulRoleID, pLoginName, pPWD);
		return result;
	}
	CString IVS_OCX_GetAutoCreatePWD(LPCTSTR pDomainCode, unsigned long ulRoleID, LPCTSTR pLoginName)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR VTS_UI4 VTS_BSTR ;
		InvokeHelper(0xf0, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, pDomainCode, ulRoleID, pLoginName);
		return result;
	}
	long IVS_OCX_StartPlatformPlayBack(LPCTSTR pCameraCode, LPCTSTR pPlaybackParam, long lWndID)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_I4 ;
		InvokeHelper(0xf1, DISPATCH_METHOD, VT_I4, (void*)&result, parms, pCameraCode, pPlaybackParam, lWndID);
		return result;
	}
	long IVS_OCX_StopPlatformPlayBack(long lWndID)
	{
		long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0xf2, DISPATCH_METHOD, VT_I4, (void*)&result, parms, lWndID);
		return result;
	}
	long IVS_OCX_PlayBackPause(long lWndID)
	{
		long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0xf3, DISPATCH_METHOD, VT_I4, (void*)&result, parms, lWndID);
		return result;
	}
	long IVS_OCX_PlayBackResume(long lWndID)
	{
		long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0xf4, DISPATCH_METHOD, VT_I4, (void*)&result, parms, lWndID);
		return result;
	}
	long IVS_OCX_PlaybackFrameStepForward(long lWndID)
	{
		long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0xf5, DISPATCH_METHOD, VT_I4, (void*)&result, parms, lWndID);
		return result;
	}
	long IVS_OCX_SetPlayBackSpeed(long lWndID, float fSpeed)
	{
		long result;
		static BYTE parms[] = VTS_I4 VTS_R4 ;
		InvokeHelper(0xf6, DISPATCH_METHOD, VT_I4, (void*)&result, parms, lWndID, fSpeed);
		return result;
	}
	CString IVS_OCX_GetPlayBackSpeed(long lWndID)
	{
		CString result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0xf7, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, lWndID);
		return result;
	}
	CString IVS_OCX_GetPlayBackTime(long lWndID)
	{
		CString result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0xf8, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, lWndID);
		return result;
	}
	CString IVS_OCX_GetPlayBackStatus(long lWndID)
	{
		CString result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0xf9, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, lWndID);
		return result;
	}
	long IVS_OCX_SetIAToolbar(unsigned long ulToolbarFlag)
	{
		long result;
		static BYTE parms[] = VTS_UI4 ;
		InvokeHelper(0xfa, DISPATCH_METHOD, VT_I4, (void*)&result, parms, ulToolbarFlag);
		return result;
	}
	long IVS_OCX_InitTVWall()
	{
		long result;
		InvokeHelper(0xfb, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	long IVS_OCX_CleanupTVWall()
	{
		long result;
		InvokeHelper(0xfc, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	long IVS_OCX_WinUserLogin(LPCTSTR pUserName, LPCTSTR pPWD, LPCTSTR pServerIP, LPCTSTR pServerPort, LPCTSTR pDomainName, unsigned long ulLoginType, unsigned long ulClientType)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_UI4 VTS_UI4 ;
		InvokeHelper(0xfe, DISPATCH_METHOD, VT_I4, (void*)&result, parms, pUserName, pPWD, pServerIP, pServerPort, pDomainName, ulLoginType, ulClientType);
		return result;
	}
	long IVS_OCX_SetPlayBackTime(long lWndID, unsigned long ulTime)
	{
		long result;
		static BYTE parms[] = VTS_I4 VTS_UI4 ;
		InvokeHelper(0x101, DISPATCH_METHOD, VT_I4, (void*)&result, parms, lWndID, ulTime);
		return result;
	}
	long IVS_OCX_SetGraphics(unsigned long ulWindowID, LPCTSTR pGraphicsXml)
	{
		long result;
		static BYTE parms[] = VTS_UI4 VTS_BSTR ;
		InvokeHelper(0x102, DISPATCH_METHOD, VT_I4, (void*)&result, parms, ulWindowID, pGraphicsXml);
		return result;
	}
	long IVS_OCX_DeleteGraphicsSelected(unsigned long ulWindowID)
	{
		long result;
		static BYTE parms[] = VTS_UI4 ;
		InvokeHelper(0x103, DISPATCH_METHOD, VT_I4, (void*)&result, parms, ulWindowID);
		return result;
	}
	long IVS_OCX_DeleteGraphics(unsigned long ulWindowID)
	{
		long result;
		static BYTE parms[] = VTS_UI4 ;
		InvokeHelper(0x104, DISPATCH_METHOD, VT_I4, (void*)&result, parms, ulWindowID);
		return result;
	}
	unsigned long IVS_OCX_StartLocalRecord(LPCTSTR pRecordPara, long lWndID)
	{
		unsigned long result;
		static BYTE parms[] = VTS_BSTR VTS_I4 ;
		InvokeHelper(0x105, DISPATCH_METHOD, VT_UI4, (void*)&result, parms, pRecordPara, lWndID);
		return result;
	}
	long IVS_OCX_StopLocalRecord(long lWndID)
	{
		long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x106, DISPATCH_METHOD, VT_I4, (void*)&result, parms, lWndID);
		return result;
	}
	long IVS_OCX_EnableDraw(unsigned long ulWindowID)
	{
		long result;
		static BYTE parms[] = VTS_UI4 ;
		InvokeHelper(0x107, DISPATCH_METHOD, VT_I4, (void*)&result, parms, ulWindowID);
		return result;
	}
	long IVS_OCX_DisableDraw(unsigned long ulWindowID)
	{
		long result;
		static BYTE parms[] = VTS_UI4 ;
		InvokeHelper(0x108, DISPATCH_METHOD, VT_I4, (void*)&result, parms, ulWindowID);
		return result;
	}
	CString IVS_OCX_GetGraphics(unsigned long ulWindowID)
	{
		CString result;
		static BYTE parms[] = VTS_UI4 ;
		InvokeHelper(0x109, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, ulWindowID);
		return result;
	}
	CString IVS_OCX_GetTVWallList()
	{
		CString result;
		InvokeHelper(0x10a, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	CString IVS_OCX_AddTVWall(LPCTSTR pTVWall)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x10b, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, pTVWall);
		return result;
	}
	long IVS_OCX_ModifyTVWallInfo(LPCTSTR pTVWall)
	{
		long result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x10c, DISPATCH_METHOD, VT_I4, (void*)&result, parms, pTVWall);
		return result;
	}
	long IVS_OCX_ModifyTVWallLayout(LPCTSTR pTVWall)
	{
		long result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x10d, DISPATCH_METHOD, VT_I4, (void*)&result, parms, pTVWall);
		return result;
	}
	long IVS_OCX_DeleteTVWall(unsigned long ulTVWallID)
	{
		long result;
		static BYTE parms[] = VTS_UI4 ;
		InvokeHelper(0x10e, DISPATCH_METHOD, VT_I4, (void*)&result, parms, ulTVWallID);
		return result;
	}
	CString IVS_OCX_PopupFloderDialog()
	{
		CString result;
		InvokeHelper(0x10f, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	long IVS_OCX_StartRealPlayTVWall(unsigned long ulTVWallID, LPCTSTR pCameraCode, LPCTSTR pRealplayParam, unsigned long ulWndID)
	{
		long result;
		static BYTE parms[] = VTS_UI4 VTS_BSTR VTS_BSTR VTS_UI4 ;
		InvokeHelper(0x110, DISPATCH_METHOD, VT_I4, (void*)&result, parms, ulTVWallID, pCameraCode, pRealplayParam, ulWndID);
		return result;
	}
	long IVS_OCX_StopRealPlayTVWall(unsigned long ulTVWallID, unsigned long ulWndID)
	{
		long result;
		static BYTE parms[] = VTS_UI4 VTS_UI4 ;
		InvokeHelper(0x111, DISPATCH_METHOD, VT_I4, (void*)&result, parms, ulTVWallID, ulWndID);
		return result;
	}
	long IVS_OCX_StartPlatformPlayBackTVWall(unsigned long ulTVWallID, LPCTSTR pCameraCode, LPCTSTR pPlaybackParam, unsigned long ulWndID)
	{
		long result;
		static BYTE parms[] = VTS_UI4 VTS_BSTR VTS_BSTR VTS_UI4 ;
		InvokeHelper(0x112, DISPATCH_METHOD, VT_I4, (void*)&result, parms, ulTVWallID, pCameraCode, pPlaybackParam, ulWndID);
		return result;
	}
	long IVS_OCX_StopPlatformPlayBackTVWall(unsigned long ulTVWallID, unsigned long ulWndID)
	{
		long result;
		static BYTE parms[] = VTS_UI4 VTS_UI4 ;
		InvokeHelper(0x113, DISPATCH_METHOD, VT_I4, (void*)&result, parms, ulTVWallID, ulWndID);
		return result;
	}
	CString IVS_OCX_GetDeviceList(unsigned long ulDeviceType, unsigned long ulFromIndex, unsigned long ulToIndex)
	{
		CString result;
		static BYTE parms[] = VTS_UI4 VTS_UI4 VTS_UI4 ;
		InvokeHelper(0x114, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, ulDeviceType, ulFromIndex, ulToIndex);
		return result;
	}
	CString IVS_OCX_GetDeviceUserList(LPCTSTR pDomainCode, LPCTSTR pDevCode, unsigned long ulIsUserOnline, unsigned long ulFromIndex, unsigned long ulToIndex)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_UI4 VTS_UI4 VTS_UI4 ;
		InvokeHelper(0x115, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, pDomainCode, pDevCode, ulIsUserOnline, ulFromIndex, ulToIndex);
		return result;
	}
	long IVS_OCX_SetTVWallTempScenario(LPCTSTR pScenarioXml)
	{
		long result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x116, DISPATCH_METHOD, VT_I4, (void*)&result, parms, pScenarioXml);
		return result;
	}
	CString IVS_OCX_GetTVWallTempScenario(unsigned long pScenarioID)
	{
		CString result;
		static BYTE parms[] = VTS_UI4 ;
		InvokeHelper(0x117, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, pScenarioID);
		return result;
	}
	CString IVS_OCX_GetTVWallByID(unsigned long ulTVWallID)
	{
		CString result;
		static BYTE parms[] = VTS_UI4 ;
		InvokeHelper(0x118, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, ulTVWallID);
		return result;
	}
	long IVS_OCX_StopDrawGraphics(unsigned long ulWindowID, unsigned long ulGraphicGroup)
	{
		long result;
		static BYTE parms[] = VTS_UI4 VTS_UI4 ;
		InvokeHelper(0x119, DISPATCH_METHOD, VT_I4, (void*)&result, parms, ulWindowID, ulGraphicGroup);
		return result;
	}
	long IVS_OCX_SelectGraphicByGroup(unsigned long ulWindowID, unsigned long ulGraphicGroup)
	{
		long result;
		static BYTE parms[] = VTS_UI4 VTS_UI4 ;
		InvokeHelper(0x11a, DISPATCH_METHOD, VT_I4, (void*)&result, parms, ulWindowID, ulGraphicGroup);
		return result;
	}
	long IVS_OCX_SelectCancel(unsigned long ulWindowID)
	{
		long result;
		static BYTE parms[] = VTS_UI4 ;
		InvokeHelper(0x11b, DISPATCH_METHOD, VT_I4, (void*)&result, parms, ulWindowID);
		return result;
	}
	CString IVS_OCX_GetGraphicsByGroup(unsigned long ulWindowID, unsigned long ulGraphicGroup)
	{
		CString result;
		static BYTE parms[] = VTS_UI4 VTS_UI4 ;
		InvokeHelper(0x11c, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, ulWindowID, ulGraphicGroup);
		return result;
	}
	long IVS_OCX_DeleteGraphicsByGroup(unsigned long ulWindowID, unsigned long ulGraphicGroup)
	{
		long result;
		static BYTE parms[] = VTS_UI4 VTS_UI4 ;
		InvokeHelper(0x11d, DISPATCH_METHOD, VT_I4, (void*)&result, parms, ulWindowID, ulGraphicGroup);
		return result;
	}
	long IVS_OCX_SetRelationShip(unsigned long ulWindowID, unsigned long ulGraphicGroupA, unsigned long ulGraphicGroupB, unsigned long ulRelationShipType)
	{
		long result;
		static BYTE parms[] = VTS_UI4 VTS_UI4 VTS_UI4 VTS_UI4 ;
		InvokeHelper(0x11e, DISPATCH_METHOD, VT_I4, (void*)&result, parms, ulWindowID, ulGraphicGroupA, ulGraphicGroupB, ulRelationShipType);
		return result;
	}
	long IVS_OCX_SetRecordSearchInfo(LPCTSTR pSearchInfo)
	{
		long result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x11f, DISPATCH_METHOD, VT_I4, (void*)&result, parms, pSearchInfo);
		return result;
	}
	CString IVS_OCX_GetRecordSearchInfo()
	{
		CString result;
		InvokeHelper(0x120, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	long IVS_OCX_SetTempScenario(LPCTSTR pScenarioXml)
	{
		long result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x121, DISPATCH_METHOD, VT_I4, (void*)&result, parms, pScenarioXml);
		return result;
	}
	CString IVS_OCX_GetTempScenario()
	{
		CString result;
		InvokeHelper(0x122, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	CString IVS_OCX_AddScenarioFavorite(LPCTSTR pScenarioXml)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x123, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, pScenarioXml);
		return result;
	}
	long IVS_OCX_ModScenarioFavorite(LPCTSTR pScenarioXml)
	{
		long result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x124, DISPATCH_METHOD, VT_I4, (void*)&result, parms, pScenarioXml);
		return result;
	}
	long IVS_OCX_DelScenarioFavorite(LPCTSTR pScenarioID)
	{
		long result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x125, DISPATCH_METHOD, VT_I4, (void*)&result, parms, pScenarioID);
		return result;
	}
	CString IVS_OCX_GetScenarioFavoriteList()
	{
		CString result;
		InvokeHelper(0x126, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	CString IVS_OCX_GetScenarioFavorite(LPCTSTR pScenarioID)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x127, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, pScenarioID);
		return result;
	}
	long IVS_OCX_DrawGraphics(unsigned long ulWindowID, LPCTSTR pGraphicsXml)
	{
		long result;
		static BYTE parms[] = VTS_UI4 VTS_BSTR ;
		InvokeHelper(0x128, DISPATCH_METHOD, VT_I4, (void*)&result, parms, ulWindowID, pGraphicsXml);
		return result;
	}
	long IVS_OCX_SetMainDeviceName(LPCTSTR pDevCode, LPCTSTR pNewDevName)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR ;
		InvokeHelper(0x129, DISPATCH_METHOD, VT_I4, (void*)&result, parms, pDevCode, pNewDevName);
		return result;
	}
	long IVS_OCX_SetCameraName(LPCTSTR pCameraCode, LPCTSTR pNewCameraName)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR ;
		InvokeHelper(0x12a, DISPATCH_METHOD, VT_I4, (void*)&result, parms, pCameraCode, pNewCameraName);
		return result;
	}
	CString IVS_OCX_GetTVWallGroupTurnInspect(unsigned long ulTVWallID)
	{
		CString result;
		static BYTE parms[] = VTS_UI4 ;
		InvokeHelper(0x134, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, ulTVWallID);
		return result;
	}
	CString IVS_OCX_AddTVWallGroupTurnInspect(LPCTSTR pTVWall)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x135, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, pTVWall);
		return result;
	}
	long IVS_OCX_ModifyTVWallGroupTurnInspect(LPCTSTR pTVWall)
	{
		long result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x136, DISPATCH_METHOD, VT_I4, (void*)&result, parms, pTVWall);
		return result;
	}
	long IVS_OCX_DeleteTVWallGroupTurnInspect(unsigned long ulTVWallID)
	{
		long result;
		static BYTE parms[] = VTS_UI4 ;
		InvokeHelper(0x137, DISPATCH_METHOD, VT_I4, (void*)&result, parms, ulTVWallID);
		return result;
	}
	CString IVS_OCX_GetTVWallTurnInspect(unsigned long ulTVWallID)
	{
		CString result;
		static BYTE parms[] = VTS_UI4 ;
		InvokeHelper(0x138, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, ulTVWallID);
		return result;
	}
	long IVS_OCX_AddTVWallTurnInspect(LPCTSTR pTVWall)
	{
		long result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x139, DISPATCH_METHOD, VT_I4, (void*)&result, parms, pTVWall);
		return result;
	}
	long IVS_OCX_ModifyTVWallTurnInspect(LPCTSTR pTVWall)
	{
		long result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x13a, DISPATCH_METHOD, VT_I4, (void*)&result, parms, pTVWall);
		return result;
	}
	long IVS_OCX_DeleteTVWallTurnInspect(unsigned long ulTVWallID)
	{
		long result;
		static BYTE parms[] = VTS_UI4 ;
		InvokeHelper(0x13b, DISPATCH_METHOD, VT_I4, (void*)&result, parms, ulTVWallID);
		return result;
	}
	long IVS_OCX_SetTurnInspectPlan(LPCTSTR pTurnInspectPlanInfo)
	{
		long result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x13c, DISPATCH_METHOD, VT_I4, (void*)&result, parms, pTurnInspectPlanInfo);
		return result;
	}
	long IVS_OCX_ModifyTurnInspectPlan(LPCTSTR pTurnInspectPlanInfo)
	{
		long result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x13d, DISPATCH_METHOD, VT_I4, (void*)&result, parms, pTurnInspectPlanInfo);
		return result;
	}
	long IVS_OCX_RebootDevice(LPCTSTR pDeviceCode, unsigned long ulRebootType)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_UI4 ;
		InvokeHelper(0x13e, DISPATCH_METHOD, VT_I4, (void*)&result, parms, pDeviceCode, ulRebootType);
		return result;
	}
	CString IVS_OCX_GetConfigInfo(LPCTSTR pReqXml)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x13f, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, pReqXml);
		return result;
	}
	CString IVS_OCX_GetGraphicsByPercent(unsigned long ulWindowID)
	{
		CString result;
		static BYTE parms[] = VTS_UI4 ;
		InvokeHelper(0x140, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, ulWindowID);
		return result;
	}
	long IVS_OCX_SetGraphicsByPercent(unsigned long ulWindowID, LPCTSTR pGraphicsXml)
	{
		long result;
		static BYTE parms[] = VTS_UI4 VTS_BSTR ;
		InvokeHelper(0x141, DISPATCH_METHOD, VT_I4, (void*)&result, parms, ulWindowID, pGraphicsXml);
		return result;
	}
	CString IVS_OCX_AddBookmark(LPCTSTR pNVRCode, LPCTSTR pCameraCode, LPCTSTR pBookmarkName, LPCTSTR pBookmarkTime)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR ;
		InvokeHelper(0x142, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, pNVRCode, pCameraCode, pBookmarkName, pBookmarkTime);
		return result;
	}
	CString IVS_OCX_GetBookmarkList(LPCTSTR pQueryXml)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x143, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, pQueryXml);
		return result;
	}
	long IVS_OCX_ModifyBookmark(LPCTSTR pNVRCode, LPCTSTR pCameraCode, unsigned long ulBookmarkID, LPCTSTR pNewBookmarkName)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_UI4 VTS_BSTR ;
		InvokeHelper(0x144, DISPATCH_METHOD, VT_I4, (void*)&result, parms, pNVRCode, pCameraCode, ulBookmarkID, pNewBookmarkName);
		return result;
	}
	long IVS_OCX_DeleteBookmark(LPCTSTR pNVRCode, LPCTSTR pCameraCode, unsigned long ulBookmarkID)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_UI4 ;
		InvokeHelper(0x145, DISPATCH_METHOD, VT_I4, (void*)&result, parms, pNVRCode, pCameraCode, ulBookmarkID);
		return result;
	}
	CString IVS_OCX_AddPTZPreset(LPCTSTR pCameraCode, LPCTSTR pPresetName)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR ;
		InvokeHelper(0x146, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, pCameraCode, pPresetName);
		return result;
	}
	long IVS_OCX_DelPTZPreset(LPCTSTR pCameraCode, unsigned long ulPresetIndex)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_UI4 ;
		InvokeHelper(0x147, DISPATCH_METHOD, VT_I4, (void*)&result, parms, pCameraCode, ulPresetIndex);
		return result;
	}
	long IVS_OCX_ModPTZPreset(LPCTSTR pCameraCode, unsigned long ulPresetIndex, LPCTSTR pPresetName)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_UI4 VTS_BSTR ;
		InvokeHelper(0x148, DISPATCH_METHOD, VT_I4, (void*)&result, parms, pCameraCode, ulPresetIndex, pPresetName);
		return result;
	}
	CString IVS_OCX_GetPTZPresetList(LPCTSTR pCameraCode)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x149, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, pCameraCode);
		return result;
	}
	long IVS_OCX_SetGuardPos(LPCTSTR pGuardPosInfo)
	{
		long result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x14a, DISPATCH_METHOD, VT_I4, (void*)&result, parms, pGuardPosInfo);
		return result;
	}
	CString IVS_OCX_GetGuardPos(LPCTSTR pCameraCode)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x14b, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, pCameraCode);
		return result;
	}
	CString IVS_OCX_AddCruiseTrack(LPCTSTR pCuriseTrackInfo)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x14c, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, pCuriseTrackInfo);
		return result;
	}
	long IVS_OCX_DelCruiseTrack(LPCTSTR pCameraCode, unsigned long ulTrackIndex, unsigned long ulCruiseType)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_UI4 VTS_UI4 ;
		InvokeHelper(0x14d, DISPATCH_METHOD, VT_I4, (void*)&result, parms, pCameraCode, ulTrackIndex, ulCruiseType);
		return result;
	}
	long IVS_OCX_ModCruiseTrack(LPCTSTR pCuriseTrackInfo)
	{
		long result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x14e, DISPATCH_METHOD, VT_I4, (void*)&result, parms, pCuriseTrackInfo);
		return result;
	}
	CString IVS_OCX_GetCruiseTrackList(LPCTSTR pCameraCode)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x14f, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, pCameraCode);
		return result;
	}
	CString IVS_OCX_GetCruiseTrack(LPCTSTR pCameraCode, unsigned long ulTrackIndex)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR VTS_UI4 ;
		InvokeHelper(0x150, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, pCameraCode, ulTrackIndex);
		return result;
	}
	long IVS_OCX_SetCruisePlan(LPCTSTR pCruisePlan)
	{
		long result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x151, DISPATCH_METHOD, VT_I4, (void*)&result, parms, pCruisePlan);
		return result;
	}
	CString IVS_OCX_GetCruisePlan(LPCTSTR pCameraCode)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x152, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, pCameraCode);
		return result;
	}
	CString IVS_OCX_AddCameraSwitch(LPCTSTR pSwitchInfo)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x153, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, pSwitchInfo);
		return result;
	}
	long IVS_OCX_DelCameraSwitch(LPCTSTR pCameraSwitchID)
	{
		long result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x154, DISPATCH_METHOD, VT_I4, (void*)&result, parms, pCameraSwitchID);
		return result;
	}
	CString IVS_OCX_GetCameraSwitchList()
	{
		CString result;
		InvokeHelper(0x155, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	CString IVS_OCX_GetCameraSwitchInfo(LPCTSTR pCameraSwitchID)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x156, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, pCameraSwitchID);
		return result;
	}
	long IVS_OCX_LockUser(LPCTSTR pDomainCode, unsigned long ulUserID, unsigned long ulLock)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_UI4 VTS_UI4 ;
		InvokeHelper(0x157, DISPATCH_METHOD, VT_I4, (void*)&result, parms, pDomainCode, ulUserID, ulLock);
		return result;
	}
	long IVS_OCX_LocalSnapshot(long lWndID)
	{
		long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x158, DISPATCH_METHOD, VT_I4, (void*)&result, parms, lWndID);
		return result;
	}
	long IVS_OCX_PlatformSnapshot(LPCTSTR pCameraCode)
	{
		long result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x159, DISPATCH_METHOD, VT_I4, (void*)&result, parms, pCameraCode);
		return result;
	}
	CString IVS_OCX_GetSnapshotList(LPCTSTR pQueryParam)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x15a, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, pQueryParam);
		return result;
	}
	long IVS_OCX_DownloadSnapshot(unsigned long ulPictureID, LPCTSTR pFileName)
	{
		long result;
		static BYTE parms[] = VTS_UI4 VTS_BSTR ;
		InvokeHelper(0x15b, DISPATCH_METHOD, VT_I4, (void*)&result, parms, ulPictureID, pFileName);
		return result;
	}
	long IVS_OCX_DeleteSnapshot(LPCTSTR pCameraCode, unsigned long ulPictureID)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_UI4 ;
		InvokeHelper(0x15c, DISPATCH_METHOD, VT_I4, (void*)&result, parms, pCameraCode, ulPictureID);
		return result;
	}
	long IVS_OCX_SetSnapshotPlan(LPCTSTR pSnapshotPlan)
	{
		long result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x15d, DISPATCH_METHOD, VT_I4, (void*)&result, parms, pSnapshotPlan);
		return result;
	}
	CString IVS_OCX_GetSnapshotPlan(LPCTSTR pCameraCode)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x15e, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, pCameraCode);
		return result;
	}
	long IVS_OCX_GetLogo(unsigned long ulLogoType, LPCTSTR pLogoFile)
	{
		long result;
		static BYTE parms[] = VTS_UI4 VTS_BSTR ;
		InvokeHelper(0x15f, DISPATCH_METHOD, VT_I4, (void*)&result, parms, ulLogoType, pLogoFile);
		return result;
	}
	long IVS_OCX_UploadLogo(unsigned long ulLogoType, LPCTSTR pLogoFile)
	{
		long result;
		static BYTE parms[] = VTS_UI4 VTS_BSTR ;
		InvokeHelper(0x160, DISPATCH_METHOD, VT_I4, (void*)&result, parms, ulLogoType, pLogoFile);
		return result;
	}
	CString IVS_OCX_GetStatement(LPCTSTR pLanguageType)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x161, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, pLanguageType);
		return result;
	}
	long IVS_OCX_UploadStatement(LPCTSTR pLanguageType, LPCTSTR pStatementFile)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR ;
		InvokeHelper(0x162, DISPATCH_METHOD, VT_I4, (void*)&result, parms, pLanguageType, pStatementFile);
		return result;
	}
	long IVS_OCX_SetWarnState(unsigned long ulWndID, unsigned long ulWarnState, unsigned long ulWarnSeconds)
	{
		long result;
		static BYTE parms[] = VTS_UI4 VTS_UI4 VTS_UI4 ;
		InvokeHelper(0x163, DISPATCH_METHOD, VT_I4, (void*)&result, parms, ulWndID, ulWarnState, ulWarnSeconds);
		return result;
	}
	long IVS_OCX_StartPlatformRecord(LPCTSTR pCameraCode, unsigned long ulRecordTime)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_UI4 ;
		InvokeHelper(0x164, DISPATCH_METHOD, VT_I4, (void*)&result, parms, pCameraCode, ulRecordTime);
		return result;
	}
	long IVS_OCX_StopPlatformRecord(LPCTSTR pCameraCode)
	{
		long result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x165, DISPATCH_METHOD, VT_I4, (void*)&result, parms, pCameraCode);
		return result;
	}
	long IVS_OCX_StartPURecord(LPCTSTR pCameraCode, unsigned long ulRecordTime)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_UI4 ;
		InvokeHelper(0x166, DISPATCH_METHOD, VT_I4, (void*)&result, parms, pCameraCode, ulRecordTime);
		return result;
	}
	long IVS_OCX_StopPURecord(LPCTSTR pCameraCode)
	{
		long result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x167, DISPATCH_METHOD, VT_I4, (void*)&result, parms, pCameraCode);
		return result;
	}
	long IVS_OCX_StartAlarmOut(LPCTSTR pAlarmOutCode)
	{
		long result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x168, DISPATCH_METHOD, VT_I4, (void*)&result, parms, pAlarmOutCode);
		return result;
	}
	long IVS_OCX_StopAlarmOut(LPCTSTR pAlarmOutCode)
	{
		long result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x169, DISPATCH_METHOD, VT_I4, (void*)&result, parms, pAlarmOutCode);
		return result;
	}
	long IVS_OCX_SetCameraBackupConfig(LPCTSTR pBackupXml)
	{
		long result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x16a, DISPATCH_METHOD, VT_I4, (void*)&result, parms, pBackupXml);
		return result;
	}
	CString IVS_OCX_GetCameraBackupConfig(LPCTSTR pCameraCode)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x16b, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, pCameraCode);
		return result;
	}
	long IVS_OCX_SetWndType(unsigned long ulWindID, unsigned long ulTyle)
	{
		long result;
		static BYTE parms[] = VTS_UI4 VTS_UI4 ;
		InvokeHelper(0x16c, DISPATCH_METHOD, VT_I4, (void*)&result, parms, ulWindID, ulTyle);
		return result;
	}
	long IVS_OCX_DeleteAlarmWnd(unsigned long ulWindID)
	{
		long result;
		static BYTE parms[] = VTS_UI4 ;
		InvokeHelper(0x16d, DISPATCH_METHOD, VT_I4, (void*)&result, parms, ulWindID);
		return result;
	}
	long IVS_OCX_SetTVWallWndLayout(unsigned long ulTVWallID)
	{
		long result;
		static BYTE parms[] = VTS_UI4 ;
		InvokeHelper(0x16e, DISPATCH_METHOD, VT_I4, (void*)&result, parms, ulTVWallID);
		return result;
	}
	long IVS_OCX_SetTVWallPaneStatus(unsigned long ulTVWallID, unsigned long ulPaneID, unsigned long ulPaneStatus)
	{
		long result;
		static BYTE parms[] = VTS_UI4 VTS_UI4 VTS_UI4 ;
		InvokeHelper(0x16f, DISPATCH_METHOD, VT_I4, (void*)&result, parms, ulTVWallID, ulPaneID, ulPaneStatus);
		return result;
	}
	CString IVS_OCX_GetHelpInfoText(LPCTSTR pAlarmInCode, LPCTSTR pAlarmType)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR ;
		InvokeHelper(0x170, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, pAlarmInCode, pAlarmType);
		return result;
	}
	long IVS_OCX_SetLanguage(LPCTSTR pLanguage)
	{
		long result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x171, DISPATCH_METHOD, VT_I4, (void*)&result, parms, pLanguage);
		return result;
	}
	long IVS_OCX_StartSearchDevice(LPCTSTR pDomainCode, LPCTSTR pSearchInfo)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR ;
		InvokeHelper(0x172, DISPATCH_METHOD, VT_I4, (void*)&result, parms, pDomainCode, pSearchInfo);
		return result;
	}
	long IVS_OCX_StopSearchDevice(LPCTSTR pDomainCode, LPCTSTR pSearchInfo)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR ;
		InvokeHelper(0x173, DISPATCH_METHOD, VT_I4, (void*)&result, parms, pDomainCode, pSearchInfo);
		return result;
	}
	CString IVS_OCX_VerifyDevice(LPCTSTR pDomainCode, LPCTSTR pVerifyInfo)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR ;
		InvokeHelper(0x174, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, pDomainCode, pVerifyInfo);
		return result;
	}
	CString IVS_OCX_GetDevLog(LPCTSTR pQueryXml)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x175, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, pQueryXml);
		return result;
	}
	CString IVS_OCX_GetDecoderList()
	{
		CString result;
		InvokeHelper(0x176, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	CString IVS_OCX_GetDeviceAlarmList(LPCTSTR pReqXml)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x177, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, pReqXml);
		return result;
	}
	CString IVS_OCX_GetCPUMemory(LPCTSTR pNodeCode)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x178, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, pNodeCode);
		return result;
	}
	long IVS_OCX_AddRecordBackupPlan(LPCTSTR pBackupPlan)
	{
		long result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x179, DISPATCH_METHOD, VT_I4, (void*)&result, parms, pBackupPlan);
		return result;
	}
	long IVS_OCX_ModifyRecordBackupPlan(LPCTSTR pBackupPlan)
	{
		long result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x17a, DISPATCH_METHOD, VT_I4, (void*)&result, parms, pBackupPlan);
		return result;
	}
	long IVS_OCX_DeleteRecordBackupPlan(LPCTSTR pBackupPlan)
	{
		long result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x17b, DISPATCH_METHOD, VT_I4, (void*)&result, parms, pBackupPlan);
		return result;
	}
	CString IVS_OCX_GetRecordBackupPlan(LPCTSTR pQueryInfo)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x17c, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, pQueryInfo);
		return result;
	}
	long IVS_OCX_DelSnapshotPlan(LPCTSTR pCameraCode)
	{
		long result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x17d, DISPATCH_METHOD, VT_I4, (void*)&result, parms, pCameraCode);
		return result;
	}
	CString IVS_OCX_GetDomainList()
	{
		CString result;
		InvokeHelper(0x17e, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	long IVS_OCX_StartRealBroadcast()
	{
		long result;
		InvokeHelper(0x17f, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	long IVS_OCX_StopRealBroadcast()
	{
		long result;
		InvokeHelper(0x180, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	long IVS_OCX_StartFileBroadcast(LPCTSTR pFileName, unsigned long ulCycle)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_UI4 ;
		InvokeHelper(0x181, DISPATCH_METHOD, VT_I4, (void*)&result, parms, pFileName, ulCycle);
		return result;
	}
	long IVS_OCX_StopFileBroadcast()
	{
		long result;
		InvokeHelper(0x182, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	long IVS_OCX_AddBroadcastDevice(LPCTSTR pCameraCode)
	{
		long result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x183, DISPATCH_METHOD, VT_I4, (void*)&result, parms, pCameraCode);
		return result;
	}
	long IVS_OCX_DeleteBroadcastDevice(LPCTSTR pCameraCode)
	{
		long result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x184, DISPATCH_METHOD, VT_I4, (void*)&result, parms, pCameraCode);
		return result;
	}
	long IVS_OCX_SetCameraSwitchWnd(unsigned long ulWndID, unsigned long ulStyle)
	{
		long result;
		static BYTE parms[] = VTS_UI4 VTS_UI4 ;
		InvokeHelper(0x185, DISPATCH_METHOD, VT_I4, (void*)&result, parms, ulWndID, ulStyle);
		return result;
	}
	long IVS_OCX_GetWndType(unsigned long ulWndID)
	{
		long result;
		static BYTE parms[] = VTS_UI4 ;
		InvokeHelper(0x186, DISPATCH_METHOD, VT_I4, (void*)&result, parms, ulWndID);
		return result;
	}
	CString IVS_OCX_GetExDomainList(LPCTSTR pQueryInfo)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x188, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, pQueryInfo);
		return result;
	}
	CString IVS_OCX_ShareCatalog(LPCTSTR pShareInfo)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x189, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, pShareInfo);
		return result;
	}
	CString IVS_OCX_GetShareCatalogList(LPCTSTR pQueryInfo)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x18a, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, pQueryInfo);
		return result;
	}
	CString IVS_OCX_GetIACPUMemory(LPCTSTR pNodeCode)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x18b, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, pNodeCode);
		return result;
	}
	long IVS_OCX_PlaybackFrameStepBackward(long lWndID)
	{
		long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x18c, DISPATCH_METHOD, VT_I4, (void*)&result, parms, lWndID);
		return result;
	}
	long IVS_OCX_StartSyncPlay(LPCTSTR pSyncPlayInfo)
	{
		long result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x18d, DISPATCH_METHOD, VT_I4, (void*)&result, parms, pSyncPlayInfo);
		return result;
	}
	long IVS_OCX_StopSyncPlay()
	{
		long result;
		InvokeHelper(0x18e, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	CString IVS_OCX_GetRecordTask()
	{
		CString result;
		InvokeHelper(0x18f, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	CString IVS_OCX_QueryPerformance(LPCTSTR pNodeCode)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x190, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, pNodeCode);
		return result;
	}
	long IVS_OCX_SignOutUser(LPCTSTR pDomainCode, unsigned long ulUserID)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_UI4 ;
		InvokeHelper(0x191, DISPATCH_METHOD, VT_I4, (void*)&result, parms, pDomainCode, ulUserID);
		return result;
	}
	CString IVS_OCX_StartPlatformDownload(LPCTSTR pCameraCode, LPCTSTR pStartTime, LPCTSTR pEndTime, LPCTSTR pDownloadParamXml)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR ;
		InvokeHelper(0x192, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, pCameraCode, pStartTime, pEndTime, pDownloadParamXml);
		return result;
	}
	long IVS_OCX_StopPlatformDownload(unsigned long ulDownloadHandle)
	{
		long result;
		static BYTE parms[] = VTS_UI4 ;
		InvokeHelper(0x193, DISPATCH_METHOD, VT_I4, (void*)&result, parms, ulDownloadHandle);
		return result;
	}
	CString IVS_OCX_StartPUDownload(LPCTSTR pCameraCode, LPCTSTR pStartTime, LPCTSTR pEndTime, LPCTSTR pDownloadParamXml)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR ;
		InvokeHelper(0x194, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, pCameraCode, pStartTime, pEndTime, pDownloadParamXml);
		return result;
	}
	long IVS_OCX_StopPUDownload(unsigned long ulDownloadHandle)
	{
		long result;
		static BYTE parms[] = VTS_UI4 ;
		InvokeHelper(0x195, DISPATCH_METHOD, VT_I4, (void*)&result, parms, ulDownloadHandle);
		return result;
	}
	long IVS_OCX_DownloadPause(unsigned long ulDownloadHandle)
	{
		long result;
		static BYTE parms[] = VTS_UI4 ;
		InvokeHelper(0x196, DISPATCH_METHOD, VT_I4, (void*)&result, parms, ulDownloadHandle);
		return result;
	}
	long IVS_OCX_DownloadResume(unsigned long ulDownloadHandle)
	{
		long result;
		static BYTE parms[] = VTS_UI4 ;
		InvokeHelper(0x197, DISPATCH_METHOD, VT_I4, (void*)&result, parms, ulDownloadHandle);
		return result;
	}
	CString IVS_OCX_GetDownloadInfo(unsigned long ulDownloadHandle)
	{
		CString result;
		static BYTE parms[] = VTS_UI4 ;
		InvokeHelper(0x198, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, ulDownloadHandle);
		return result;
	}
	long IVS_OCX_StartPUPlayBack(LPCTSTR pCameraCode, LPCTSTR pPlaybackParam, long lWndID)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_I4 ;
		InvokeHelper(0x199, DISPATCH_METHOD, VT_I4, (void*)&result, parms, pCameraCode, pPlaybackParam, lWndID);
		return result;
	}
	long IVS_OCX_StopPUPlayBack(long lWndID)
	{
		long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x19a, DISPATCH_METHOD, VT_I4, (void*)&result, parms, lWndID);
		return result;
	}
	CString IVS_OCX_GetRecordBackupTaskList(LPCTSTR pQueryInfo)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x19b, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, pQueryInfo);
		return result;
	}
	long IVS_OCX_StartRecordBackupTask(LPCTSTR pQueryInfo)
	{
		long result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x19c, DISPATCH_METHOD, VT_I4, (void*)&result, parms, pQueryInfo);
		return result;
	}
	long IVS_OCX_StopRecordBackupTask(LPCTSTR pQueryInfo)
	{
		long result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x19d, DISPATCH_METHOD, VT_I4, (void*)&result, parms, pQueryInfo);
		return result;
	}
	CString IVS_OCX_GetDriverList(LPCTSTR pReqXml)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x19e, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, pReqXml);
		return result;
	}
	CString IVS_OCX_GetTemplateList(LPCTSTR pReqXml)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x19f, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, pReqXml);
		return result;
	}
	long IVS_OCX_DelRecordBackupTask(LPCTSTR pQueryInfo)
	{
		long result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x1a0, DISPATCH_METHOD, VT_I4, (void*)&result, parms, pQueryInfo);
		return result;
	}
	long IVS_OCX_AddRecordBackupTask(LPCTSTR pBackupTask)
	{
		long result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x1a1, DISPATCH_METHOD, VT_I4, (void*)&result, parms, pBackupTask);
		return result;
	}
	void IVS_OCX_SetEventReceiver()
	{
		InvokeHelper(0x1a2, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	long IVS_OCX_SetWndDrag(unsigned long ulWndID, unsigned long ulEnable)
	{
		long result;
		static BYTE parms[] = VTS_UI4 VTS_UI4 ;
		InvokeHelper(0x1a3, DISPATCH_METHOD, VT_I4, (void*)&result, parms, ulWndID, ulEnable);
		return result;
	}
	void IVS_OCX_RefreshWnd(unsigned long ulRefreshType)
	{
		static BYTE parms[] = VTS_UI4 ;
		InvokeHelper(0x1a4, DISPATCH_METHOD, VT_EMPTY, NULL, parms, ulRefreshType);
	}
	CString IVS_OCX_GetAlarmLinkageAction(LPCTSTR pReqXml)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x1a5, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, pReqXml);
		return result;
	}
	CString IVS_OCX_GetPWDStrength(LPCTSTR pPWD)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x1a6, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, pPWD);
		return result;
	}
	long IVS_OCX_AddCameraSwitchPlan(LPCTSTR pSwitchPlanInfo)
	{
		long result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x1a7, DISPATCH_METHOD, VT_I4, (void*)&result, parms, pSwitchPlanInfo);
		return result;
	}
	long IVS_OCX_DelCameraSwitchPlan(LPCTSTR pCameraSwitchID)
	{
		long result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x1a8, DISPATCH_METHOD, VT_I4, (void*)&result, parms, pCameraSwitchID);
		return result;
	}
	CString IVS_OCX_GetCameraSwitchPlanList()
	{
		CString result;
		InvokeHelper(0x1a9, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	CString IVS_OCX_GetCameraSwitchPlan(LPCTSTR pCameraSwitchID)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x1aa, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, pCameraSwitchID);
		return result;
	}
	long IVS_OCX_UnlockRecord(LPCTSTR pUnlockXml)
	{
		long result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x1ab, DISPATCH_METHOD, VT_I4, (void*)&result, parms, pUnlockXml);
		return result;
	}
	long IVS_OCX_LockRecord(LPCTSTR pLockXml)
	{
		long result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x1ac, DISPATCH_METHOD, VT_I4, (void*)&result, parms, pLockXml);
		return result;
	}
	CString IVS_OCX_GetVideoNumAndResource(LPCTSTR pCameraCode)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x1ad, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, pCameraCode);
		return result;
	}
	long IVS_OCX_UnlockBackupRecord(LPCTSTR pUnlockXml)
	{
		long result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x1ae, DISPATCH_METHOD, VT_I4, (void*)&result, parms, pUnlockXml);
		return result;
	}
	long IVS_OCX_LockBackupRecord(LPCTSTR pLockXml)
	{
		long result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x1af, DISPATCH_METHOD, VT_I4, (void*)&result, parms, pLockXml);
		return result;
	}
	CString IVS_OCX_GetMotionRangeDataPlatform(LPCTSTR pCameraCode, LPCTSTR pStartTime, LPCTSTR pEndTime, long lFromIndex, long lToIndex)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_BSTR VTS_I4 VTS_I4 ;
		InvokeHelper(0x1b0, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, pCameraCode, pStartTime, pEndTime, lFromIndex, lToIndex);
		return result;
	}
	long IVS_OCX_AddBookmarkForBackup(LPCTSTR pDomainCode, LPCTSTR pNVRCode, LPCTSTR pCameraCode, LPCTSTR pBookmarkName, LPCTSTR pBookmarkTime)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR ;
		InvokeHelper(0x1b1, DISPATCH_METHOD, VT_I4, (void*)&result, parms, pDomainCode, pNVRCode, pCameraCode, pBookmarkName, pBookmarkTime);
		return result;
	}
	CString IVS_OCX_GetBookmarkListForBackup(LPCTSTR pQueryXml)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x1b2, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, pQueryXml);
		return result;
	}
	long IVS_OCX_ModifyBookmarkForBackup(LPCTSTR pDomainCode, LPCTSTR pNVRCode, LPCTSTR pCameraCode, unsigned long ulBookmarkID, LPCTSTR pNewBookmarkName)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_BSTR VTS_UI4 VTS_BSTR ;
		InvokeHelper(0x1b3, DISPATCH_METHOD, VT_I4, (void*)&result, parms, pDomainCode, pNVRCode, pCameraCode, ulBookmarkID, pNewBookmarkName);
		return result;
	}
	long IVS_OCX_DeleteBookmarkForBackup(LPCTSTR pDomainCode, LPCTSTR pNVRCode, LPCTSTR pCameraCode, unsigned long ulBookmarkID)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_BSTR VTS_UI4 ;
		InvokeHelper(0x1b4, DISPATCH_METHOD, VT_I4, (void*)&result, parms, pDomainCode, pNVRCode, pCameraCode, ulBookmarkID);
		return result;
	}
	CString IVS_OCX_OMUQueryDevReport(LPCTSTR pReqXml)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x1b5, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, pReqXml);
		return result;
	}
	CString IVS_OCX_OMUQueryDevReportDetail(LPCTSTR pReqXml)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x1b6, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, pReqXml);
		return result;
	}
	CString IVS_OCX_OMUQueryRealtimeReport(LPCTSTR pReqXml)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x1b7, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, pReqXml);
		return result;
	}
	CString IVS_OCX_OMUQueryRealtimeReportDetail(LPCTSTR pReqXml)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x1b8, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, pReqXml);
		return result;
	}
	CString IVS_OCX_OMUQueryQDReport(LPCTSTR pReqXml)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x1b9, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, pReqXml);
		return result;
	}
	CString IVS_OCX_OMUQueryQDReportDetail(LPCTSTR pReqXml)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x1ba, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, pReqXml);
		return result;
	}
	CString IVS_OCX_OMUQueryRecordPlanReport(LPCTSTR pReqXml)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x1bb, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, pReqXml);
		return result;
	}
	CString IVS_OCX_OMUQueryRecordPlanReportDetail(LPCTSTR pReqXml)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x1bc, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, pReqXml);
		return result;
	}
	CString IVS_OCX_OMUQueryRecordIntegralityReport(LPCTSTR pReqXml)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x1bd, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, pReqXml);
		return result;
	}
	CString IVS_OCX_OMUQueryRecordIntegralityReportDetail(LPCTSTR pReqXml)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x1be, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, pReqXml);
		return result;
	}
	CString IVS_OCX_OMUQueryPacketLossRateReport(LPCTSTR pReqXml)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x1bf, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, pReqXml);
		return result;
	}
	CString IVS_OCX_OMUQueryPacketLossRateReportDetail(LPCTSTR pReqXml)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x1c0, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, pReqXml);
		return result;
	}
	CString IVS_OCX_OMUQueryDiskUsageRateReport(LPCTSTR pReqXml)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x1c1, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, pReqXml);
		return result;
	}
	long IVS_OCX_SetDevGroupRemark(LPCTSTR pReqXml)
	{
		long result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x1c2, DISPATCH_METHOD, VT_I4, (void*)&result, parms, pReqXml);
		return result;
	}
	CString IVS_OCX_GetDevGroupRemark(LPCTSTR pReqXml)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x1c3, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, pReqXml);
		return result;
	}
	CString IVS_OCX_OMUAddAlarmLinkageRule(LPCTSTR pReqXml)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x1c4, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, pReqXml);
		return result;
	}
	long IVS_OCX_OMUModAlarmLinkageRule(LPCTSTR pReqXml)
	{
		long result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x1c5, DISPATCH_METHOD, VT_I4, (void*)&result, parms, pReqXml);
		return result;
	}
	long IVS_OCX_OMUDelAlarmLinkageRule(LPCTSTR pReqXml)
	{
		long result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x1c6, DISPATCH_METHOD, VT_I4, (void*)&result, parms, pReqXml);
		return result;
	}
	CString IVS_OCX_OMUGetAlarmLinkageRuleList(LPCTSTR pReqXml)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x1c7, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, pReqXml);
		return result;
	}
	CString IVS_OCX_OMUGetAlarmLinkageRuleDetail(LPCTSTR pReqXml)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x1c8, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, pReqXml);
		return result;
	}
	CString IVS_OCX_OMUGetDevTypeByNodeCode(LPCTSTR pReqXml)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x1c9, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, pReqXml);
		return result;
	}
	CString IVS_OCX_GetPrerecordCameraList()
	{
		CString result;
		InvokeHelper(0x1ca, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	long IVS_OCX_VerifyWatermark(long lWndID, unsigned long ulVerifyWatermark)
	{
		long result;
		static BYTE parms[] = VTS_I4 VTS_UI4 ;
		InvokeHelper(0x1cc, DISPATCH_METHOD, VT_I4, (void*)&result, parms, lWndID, ulVerifyWatermark);
		return result;
	}
	long IVS_OCX_WatermarkAlarmConfirm(LPCTSTR pConfirmInfo)
	{
		long result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x1cd, DISPATCH_METHOD, VT_I4, (void*)&result, parms, pConfirmInfo);
		return result;
	}
	long IVS_OCX_WatermarkAlarmCancel(LPCTSTR pCancelInfo)
	{
		long result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x1ce, DISPATCH_METHOD, VT_I4, (void*)&result, parms, pCancelInfo);
		return result;
	}
	CString IVS_OCX_QueryWatermarkAlarmList(LPCTSTR pQueryXml)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x1cf, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, pQueryXml);
		return result;
	}
	CString IVS_OCX_GetPaneWndID(unsigned long ulTVWallID, unsigned long ulPaneID)
	{
		CString result;
		static BYTE parms[] = VTS_UI4 VTS_UI4 ;
		InvokeHelper(0x1d0, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, ulTVWallID, ulPaneID);
		return result;
	}
	long IVS_OCX_StartLocalPlayBack(long lWndID, LPCTSTR pFileName, LPCTSTR pPlaybackParam)
	{
		long result;
		static BYTE parms[] = VTS_I4 VTS_BSTR VTS_BSTR ;
		InvokeHelper(0x1d1, DISPATCH_METHOD, VT_I4, (void*)&result, parms, lWndID, pFileName, pPlaybackParam);
		return result;
	}
	long IVS_OCX_StopLocalPlayBack(long lWndID)
	{
		long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x1d2, DISPATCH_METHOD, VT_I4, (void*)&result, parms, lWndID);
		return result;
	}
	CString IVS_OCX_GetDeviceCapability(long lCapabilityType, LPCTSTR pDevCode)
	{
		CString result;
		static BYTE parms[] = VTS_I4 VTS_BSTR ;
		InvokeHelper(0x1d3, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, lCapabilityType, pDevCode);
		return result;
	}
	long IVS_OCX_StartNetKeyBoard(unsigned long ulNetKeyBoardVendor, unsigned long ulPort)
	{
		long result;
		static BYTE parms[] = VTS_UI4 VTS_UI4 ;
		InvokeHelper(0x1d4, DISPATCH_METHOD, VT_I4, (void*)&result, parms, ulNetKeyBoardVendor, ulPort);
		return result;
	}
	long IVS_OCX_StopNetKeyBoard()
	{
		long result;
		InvokeHelper(0x1d5, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	long IVS_OCX_SetNetKeyBoardPort(unsigned long ulPort)
	{
		long result;
		static BYTE parms[] = VTS_UI4 ;
		InvokeHelper(0x1d6, DISPATCH_METHOD, VT_I4, (void*)&result, parms, ulPort);
		return result;
	}
	CString IVS_OCX_GetCameraPlanInfo(LPCTSTR pReqXml)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x1d7, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, pReqXml);
		return result;
	}
	long IVS_OCX_SetExDomainRecordPolicy(LPCTSTR pReqXml)
	{
		long result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x1d8, DISPATCH_METHOD, VT_I4, (void*)&result, parms, pReqXml);
		return result;
	}
	CString IVS_OCX_GetExDomainRecordPolicy(LPCTSTR pReqXml)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x1d9, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, pReqXml);
		return result;
	}
	CString IVS_OCX_AddExDomainRecordPlan(LPCTSTR pRecordPlanXml)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x1da, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, pRecordPlanXml);
		return result;
	}
	CString IVS_OCX_ModExDomainRecordPlan(LPCTSTR pRecordPlan)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x1db, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, pRecordPlan);
		return result;
	}
	CString IVS_OCX_DelExDomainRecordPlan(LPCTSTR pDelRecPlanXML)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x1dc, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, pDelRecPlanXML);
		return result;
	}
	CString IVS_OCX_GetExDomainRecordPlan(LPCTSTR pRecordPlanListReq)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x1dd, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, pRecordPlanListReq);
		return result;
	}
	CString IVS_OCX_CheckNewVersion(LPCTSTR pReqXml)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x1de, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, pReqXml);
		return result;
	}
	long IVS_OCX_SetDeviceGuard(LPCTSTR pReqXml)
	{
		long result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x1df, DISPATCH_METHOD, VT_I4, (void*)&result, parms, pReqXml);
		return result;
	}
	long IVS_OCX_SetLogPath(LPCTSTR pLogPath)
	{
		long result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x1e0, DISPATCH_METHOD, VT_I4, (void*)&result, parms, pLogPath);
		return result;
	}
	long IVS_OCX_SignOutUserByRole(LPCTSTR pDomainCode, unsigned long ulRoleID)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_UI4 ;
		InvokeHelper(0x1e1, DISPATCH_METHOD, VT_I4, (void*)&result, parms, pDomainCode, ulRoleID);
		return result;
	}
	long IVS_OCX_StartBackupPlayBack(LPCTSTR pDomainCode, LPCTSTR pNVRCode, LPCTSTR pCameraCode, LPCTSTR pPlaybackParam, long lWndID)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_I4 ;
		InvokeHelper(0x1e2, DISPATCH_METHOD, VT_I4, (void*)&result, parms, pDomainCode, pNVRCode, pCameraCode, pPlaybackParam, lWndID);
		return result;
	}
	long IVS_OCX_StopBackupPlayBack(long lWndID)
	{
		long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x1e3, DISPATCH_METHOD, VT_I4, (void*)&result, parms, lWndID);
		return result;
	}
	long IVS_OCX_ShowInstantReplayBar(unsigned long ulWndID, unsigned long ulStyle)
	{
		long result;
		static BYTE parms[] = VTS_UI4 VTS_UI4 ;
		InvokeHelper(0x1e4, DISPATCH_METHOD, VT_I4, (void*)&result, parms, ulWndID, ulStyle);
		return result;
	}
	CString IVS_OCX_GetCameraThumbnail(LPCTSTR pCameraCode)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x1e5, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, pCameraCode);
		return result;
	}
	CString IVS_OCX_GetAlarmSnapshotList(LPCTSTR pQueryParam)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x1e6, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, pQueryParam);
		return result;
	}
	long IVS_OCX_ModLockRecord(LPCTSTR pLockXml)
	{
		long result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x1e7, DISPATCH_METHOD, VT_I4, (void*)&result, parms, pLockXml);
		return result;
	}
	long IVS_OCX_ShowPaneBar(unsigned long ulWndID, unsigned long ulStyle)
	{
		long result;
		static BYTE parms[] = VTS_UI4 VTS_UI4 ;
		InvokeHelper(0x1e8, DISPATCH_METHOD, VT_I4, (void*)&result, parms, ulWndID, ulStyle);
		return result;
	}
	long IVS_OCX_StopDisasterRecoveryDownload(unsigned long ulDownloadHandle)
	{
		long result;
		static BYTE parms[] = VTS_UI4 ;
		InvokeHelper(0x1e9, DISPATCH_METHOD, VT_I4, (void*)&result, parms, ulDownloadHandle);
		return result;
	}
	CString IVS_OCX_StartDisasterRecoveryDownload(LPCTSTR pCameraCode, LPCTSTR pStartTime, LPCTSTR pEndTime, LPCTSTR pDownloadParamXml)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR ;
		InvokeHelper(0x1ea, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, pCameraCode, pStartTime, pEndTime, pDownloadParamXml);
		return result;
	}
	CString IVS_OCX_StartBackupDownload(LPCTSTR pDomainCode, LPCTSTR pNVRCode, LPCTSTR pCameraCode, LPCTSTR pStartTime, LPCTSTR pEndTime, LPCTSTR pDownloadParamXml)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR ;
		InvokeHelper(0x1eb, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, pDomainCode, pNVRCode, pCameraCode, pStartTime, pEndTime, pDownloadParamXml);
		return result;
	}
	long IVS_OCX_StopBackupDownload(unsigned long ulDownloadHandle)
	{
		long result;
		static BYTE parms[] = VTS_UI4 ;
		InvokeHelper(0x1ec, DISPATCH_METHOD, VT_I4, (void*)&result, parms, ulDownloadHandle);
		return result;
	}
	CString IVS_OCX_AddRealPlayBookmark(LPCTSTR pCameraCode, LPCTSTR pBookmarkName, LPCTSTR pBookmarkTime)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_BSTR ;
		InvokeHelper(0x1ed, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, pCameraCode, pBookmarkName, pBookmarkTime);
		return result;
	}
	long IVS_OCX_ModifyRealPlayBookmark(LPCTSTR pCameraCode, unsigned long ulBookmarkID, LPCTSTR pNewBookmarkName)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_UI4 VTS_BSTR ;
		InvokeHelper(0x1ee, DISPATCH_METHOD, VT_I4, (void*)&result, parms, pCameraCode, ulBookmarkID, pNewBookmarkName);
		return result;
	}
	long IVS_OCX_DeleteRealPlayBookmark(LPCTSTR pCameraCode, unsigned long ulBookmarkID)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_UI4 ;
		InvokeHelper(0x1ef, DISPATCH_METHOD, VT_I4, (void*)&result, parms, pCameraCode, ulBookmarkID);
		return result;
	}
	long IVS_OCX_StartSyncPlayTVWall(unsigned long ulTVWallID, LPCTSTR pSyncPlayInfo)
	{
		long result;
		static BYTE parms[] = VTS_UI4 VTS_BSTR ;
		InvokeHelper(0x1f0, DISPATCH_METHOD, VT_I4, (void*)&result, parms, ulTVWallID, pSyncPlayInfo);
		return result;
	}
	long IVS_OCX_StopSyncPlayTVWall(unsigned long ulTVWallID)
	{
		long result;
		static BYTE parms[] = VTS_UI4 ;
		InvokeHelper(0x1f1, DISPATCH_METHOD, VT_I4, (void*)&result, parms, ulTVWallID);
		return result;
	}
	CString IVS_OCX_SetPaneEMap(unsigned long ulWndID)
	{
		CString result;
		static BYTE parms[] = VTS_UI4 ;
		InvokeHelper(0x1f2, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, ulWndID);
		return result;
	}
	CString IVS_OCX_GetPWDExpireInfo()
	{
		CString result;
		InvokeHelper(0x1f3, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	CString IVS_OCX_GetNetkeyboardList()
	{
		CString result;
		InvokeHelper(0x1f4, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	long IVS_OCX_SaveNetkeyboardCamera(LPCTSTR pNetboardCameraList)
	{
		long result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x1f5, DISPATCH_METHOD, VT_I4, (void*)&result, parms, pNetboardCameraList);
		return result;
	}
	long IVS_OCX_ModNetkeyboardCamera(LPCTSTR pNetboardCamera)
	{
		long result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x1f6, DISPATCH_METHOD, VT_I4, (void*)&result, parms, pNetboardCamera);
		return result;
	}
	long IVS_OCX_StartDisasterRecoveryPlayBack(LPCTSTR pCameraCode, LPCTSTR pPlaybackParam, long lWndID)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_I4 ;
		InvokeHelper(0x1f7, DISPATCH_METHOD, VT_I4, (void*)&result, parms, pCameraCode, pPlaybackParam, lWndID);
		return result;
	}
	long IVS_OCX_StopDisasterRecoveryPlayBack(long lWndID)
	{
		long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x1f8, DISPATCH_METHOD, VT_I4, (void*)&result, parms, lWndID);
		return result;
	}
	long IVS_OCX_ImportDevCfgFile(LPCTSTR pDevCode, LPCTSTR pCFGFile)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR ;
		InvokeHelper(0x1f9, DISPATCH_METHOD, VT_I4, (void*)&result, parms, pDevCode, pCFGFile);
		return result;
	}
	long IVS_OCX_ExportDevCfgFile(LPCTSTR pDevCode, LPCTSTR pCFGFilePath)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR ;
		InvokeHelper(0x1fa, DISPATCH_METHOD, VT_I4, (void*)&result, parms, pDevCode, pCFGFilePath);
		return result;
	}
	long IVS_OCX_PlaybackFrameStepForwardTVWall(unsigned long ulTVWallID, long lWndID)
	{
		long result;
		static BYTE parms[] = VTS_UI4 VTS_I4 ;
		InvokeHelper(0x1fb, DISPATCH_METHOD, VT_I4, (void*)&result, parms, ulTVWallID, lWndID);
		return result;
	}
	long IVS_OCX_DelGuardPos(LPCTSTR pGuardPosInfo)
	{
		long result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x1fc, DISPATCH_METHOD, VT_I4, (void*)&result, parms, pGuardPosInfo);
		return result;
	}
	long IVS_OCX_AddCameraSwitchPlanTVWall(LPCTSTR pSwitchPlanInfo)
	{
		long result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x1fd, DISPATCH_METHOD, VT_I4, (void*)&result, parms, pSwitchPlanInfo);
		return result;
	}
	long IVS_OCX_DelCameraSwitchPlanTVWall(unsigned long ulTVWallID, LPCTSTR pCameraSwitchID)
	{
		long result;
		static BYTE parms[] = VTS_UI4 VTS_BSTR ;
		InvokeHelper(0x1fe, DISPATCH_METHOD, VT_I4, (void*)&result, parms, ulTVWallID, pCameraSwitchID);
		return result;
	}
	CString IVS_OCX_GetCameraSwitchPlanListTVWall()
	{
		CString result;
		InvokeHelper(0x1ff, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	CString IVS_OCX_GetCameraSwitchPlanTVWall(unsigned long ulTVWallID, LPCTSTR pCameraSwitchID)
	{
		CString result;
		static BYTE parms[] = VTS_UI4 VTS_BSTR ;
		InvokeHelper(0x200, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, ulTVWallID, pCameraSwitchID);
		return result;
	}
	long IVS_OCX_ModLockBackupRecord(LPCTSTR pLockXml)
	{
		long result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x201, DISPATCH_METHOD, VT_I4, (void*)&result, parms, pLockXml);
		return result;
	}
	long IVS_OCX_PlayBackPauseTVWall(unsigned long ulTVWallID, long lWndID)
	{
		long result;
		static BYTE parms[] = VTS_UI4 VTS_I4 ;
		InvokeHelper(0x202, DISPATCH_METHOD, VT_I4, (void*)&result, parms, ulTVWallID, lWndID);
		return result;
	}
	long IVS_OCX_PlayBackResumeTVWall(unsigned long ulTVWallID, long lWndID)
	{
		long result;
		static BYTE parms[] = VTS_UI4 VTS_I4 ;
		InvokeHelper(0x203, DISPATCH_METHOD, VT_I4, (void*)&result, parms, ulTVWallID, lWndID);
		return result;
	}
	long IVS_OCX_StartPUPlayBackTVWall(unsigned long ulTVWallID, LPCTSTR pCameraCode, LPCTSTR pPlaybackParam, long lWndID)
	{
		long result;
		static BYTE parms[] = VTS_UI4 VTS_BSTR VTS_BSTR VTS_I4 ;
		InvokeHelper(0x204, DISPATCH_METHOD, VT_I4, (void*)&result, parms, ulTVWallID, pCameraCode, pPlaybackParam, lWndID);
		return result;
	}
	long IVS_OCX_StopPUPlayBackTVWall(unsigned long ulTVWallID, long lWndID)
	{
		long result;
		static BYTE parms[] = VTS_UI4 VTS_I4 ;
		InvokeHelper(0x205, DISPATCH_METHOD, VT_I4, (void*)&result, parms, ulTVWallID, lWndID);
		return result;
	}
	CString IVS_OCX_GetRecordThumbnail(LPCTSTR pThumbnailQuery)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x206, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, pThumbnailQuery);
		return result;
	}
	unsigned long IVS_OCX_GetPaneWnd(unsigned long ulWndID)
	{
		unsigned long result;
		static BYTE parms[] = VTS_UI4 ;
		InvokeHelper(0x207, DISPATCH_METHOD, VT_UI4, (void*)&result, parms, ulWndID);
		return result;
	}
	long IVS_OCX_SetDevPWD(LPCTSTR pReqXml)
	{
		long result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x208, DISPATCH_METHOD, VT_I4, (void*)&result, parms, pReqXml);
		return result;
	}
	long IVS_OCX_SetSkin(unsigned long ulSkinType)
	{
		long result;
		static BYTE parms[] = VTS_UI4 ;
		InvokeHelper(0x209, DISPATCH_METHOD, VT_I4, (void*)&result, parms, ulSkinType);
		return result;
	}
	long IVS_OCX_ResetAlarm(LPCTSTR pReqXml)
	{
		long result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x20a, DISPATCH_METHOD, VT_I4, (void*)&result, parms, pReqXml);
		return result;
	}
	long IVS_OCX_ExEventSubscribe(LPCTSTR pReqXml)
	{
		long result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x20b, DISPATCH_METHOD, VT_I4, (void*)&result, parms, pReqXml);
		return result;
	}
	CString IVS_OCX_GetExEventSubscribe(LPCTSTR pReqXml)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x20c, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, pReqXml);
		return result;
	}
	long IVS_OCX_ExCatalogSubscribe(LPCTSTR pReqXml)
	{
		long result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x20d, DISPATCH_METHOD, VT_I4, (void*)&result, parms, pReqXml);
		return result;
	}
	CString IVS_OCX_GetExCatalogSubscribeList(LPCTSTR pReqXml)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x20e, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, pReqXml);
		return result;
	}
	long IVS_OCX_StartBackupPlayBackTVWall(unsigned long ulTVWallID, LPCTSTR pDomainCode, LPCTSTR pNVRCode, LPCTSTR pCameraCode, LPCTSTR pPlaybackParam, long lWndID)
	{
		long result;
		static BYTE parms[] = VTS_UI4 VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_I4 ;
		InvokeHelper(0x20f, DISPATCH_METHOD, VT_I4, (void*)&result, parms, ulTVWallID, pDomainCode, pNVRCode, pCameraCode, pPlaybackParam, lWndID);
		return result;
	}
	long IVS_OCX_StopBackuplayBackTVWall(unsigned long ulTVWallID, long lWndID)
	{
		long result;
		static BYTE parms[] = VTS_UI4 VTS_I4 ;
		InvokeHelper(0x210, DISPATCH_METHOD, VT_I4, (void*)&result, parms, ulTVWallID, lWndID);
		return result;
	}
	unsigned long IVS_OCX_GetAbilityInfo()
	{
		unsigned long result;
		InvokeHelper(0x211, DISPATCH_METHOD, VT_UI4, (void*)&result, NULL);
		return result;
	}
	long IVS_OCX_SetScenarioRecovery(long lRecovery)
	{
		long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x212, DISPATCH_METHOD, VT_I4, (void*)&result, parms, lRecovery);
		return result;
	}
	long IVS_OCX_GetScenarioRecovery()
	{
		long result;
		InvokeHelper(0x213, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	CString IVS_OCX_GetGraphicSelected(unsigned long ulWindowID)
	{
		CString result;
		static BYTE parms[] = VTS_UI4 ;
		InvokeHelper(0x214, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, ulWindowID);
		return result;
	}
	void IVS_OCX_EnableExchangePane(unsigned long ulStatus)
	{
		static BYTE parms[] = VTS_UI4 ;
		InvokeHelper(0x215, DISPATCH_METHOD, VT_EMPTY, NULL, parms, ulStatus);
	}
	long IVS_OCX_SetRealTimeTempScenario(LPCTSTR pRealTimeScenarioXml, LPCTSTR pScenarioID)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR ;
		InvokeHelper(0x216, DISPATCH_METHOD, VT_I4, (void*)&result, parms, pRealTimeScenarioXml, pScenarioID);
		return result;
	}
	long IVS_OCX_SetRecordTempScenario(LPCTSTR pRecordScenarioXml, LPCTSTR pScenarioID)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR ;
		InvokeHelper(0x217, DISPATCH_METHOD, VT_I4, (void*)&result, parms, pRecordScenarioXml, pScenarioID);
		return result;
	}
	long IVS_OCX_SetEmapTempScenario(LPCTSTR pEmapScenarionXml, LPCTSTR pScenarioID)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR ;
		InvokeHelper(0x218, DISPATCH_METHOD, VT_I4, (void*)&result, parms, pEmapScenarionXml, pScenarioID);
		return result;
	}
	CString IVS_OCX_GetRealTimeTempScenario(LPCTSTR pScenarioID)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x219, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, pScenarioID);
		return result;
	}
	CString IVS_OCX_GetRecordTempScenario(LPCTSTR pScenarioID)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x21a, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, pScenarioID);
		return result;
	}
	CString IVS_OCX_GetEmapTempScenario(LPCTSTR pScenarioID)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x21b, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, pScenarioID);
		return result;
	}
	void IVS_OCX_KeyEventNotice(unsigned long ulCtrlKey, unsigned long ulKey)
	{
		static BYTE parms[] = VTS_UI4 VTS_UI4 ;
		InvokeHelper(0x21c, DISPATCH_METHOD, VT_EMPTY, NULL, parms, ulCtrlKey, ulKey);
	}
	unsigned long IVS_OCX_SetTitleBarStatus(unsigned long ulWndID, unsigned long ulStatusType, unsigned long ulShow)
	{
		unsigned long result;
		static BYTE parms[] = VTS_UI4 VTS_UI4 VTS_UI4 ;
		InvokeHelper(0x21d, DISPATCH_METHOD, VT_UI4, (void*)&result, parms, ulWndID, ulStatusType, ulShow);
		return result;
	}
	long IVS_OCX_ModCameraSwitch(LPCTSTR pSwitchInfo)
	{
		long result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x21e, DISPATCH_METHOD, VT_I4, (void*)&result, parms, pSwitchInfo);
		return result;
	}
	long IVS_OCX_DeleteBroadcastFile(LPCTSTR pFileName)
	{
		long result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x21f, DISPATCH_METHOD, VT_I4, (void*)&result, parms, pFileName);
		return result;
	}
	CString IVS_OCX_GetBroadcastCameraList()
	{
		CString result;
		InvokeHelper(0x220, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	long IVS_OCX_AddBroadcastFile(LPCTSTR pFileName)
	{
		long result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x221, DISPATCH_METHOD, VT_I4, (void*)&result, parms, pFileName);
		return result;
	}
	CString IVS_OCX_GetBroadcastFileList()
	{
		CString result;
		InvokeHelper(0x222, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	CString IVS_OCX_ExGetDeviceStatus(LPCTSTR pReqXml)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x223, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, pReqXml);
		return result;
	}
	long IVS_OCX_ExGetDeviceInfo(LPCTSTR pReqXml)
	{
		long result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x224, DISPATCH_METHOD, VT_I4, (void*)&result, parms, pReqXml);
		return result;
	}
	long IVS_OCX_RefreshCameraList()
	{
		long result;
		InvokeHelper(0x225, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	CString IVS_OCX_GetDeviceEncodeCapabilities(LPCTSTR pDevCode)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x226, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, pDevCode);
		return result;
	}
	CString IVS_OCX_GetCUVersion(LPCTSTR pReqXml)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x227, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, pReqXml);
		return result;
	}
	long IVS_OCX_StartRealPlayTVWall_Async(unsigned long ulTVWallID, LPCTSTR pCameraCode, LPCTSTR pRealplayParam, unsigned long ulWndID, unsigned long ulTransID)
	{
		long result;
		static BYTE parms[] = VTS_UI4 VTS_BSTR VTS_BSTR VTS_UI4 VTS_UI4 ;
		InvokeHelper(0x228, DISPATCH_METHOD, VT_I4, (void*)&result, parms, ulTVWallID, pCameraCode, pRealplayParam, ulWndID, ulTransID);
		return result;
	}
	long IVS_OCX_StopRealPlayTVWall_Async(unsigned long ulTVWallID, unsigned long ulWndID)
	{
		long result;
		static BYTE parms[] = VTS_UI4 VTS_UI4 ;
		InvokeHelper(0x229, DISPATCH_METHOD, VT_I4, (void*)&result, parms, ulTVWallID, ulWndID);
		return result;
	}
	long IVS_OCX_StartRealPlay_Async(LPCTSTR pMediaPara, LPCTSTR pCameraCode, long lWndID, unsigned long lTransID)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_I4 VTS_UI4 ;
		InvokeHelper(0x22a, DISPATCH_METHOD, VT_I4, (void*)&result, parms, pMediaPara, pCameraCode, lWndID, lTransID);
		return result;
	}
	long IVS_OCX_StopRealPlay_Async(long lWndID)
	{
		long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x22b, DISPATCH_METHOD, VT_I4, (void*)&result, parms, lWndID);
		return result;
	}
	void IVS_OCX_SetLogLevel(unsigned long ulLogLevel)
	{
		static BYTE parms[] = VTS_UI4 ;
		InvokeHelper(0x22c, DISPATCH_METHOD, VT_EMPTY, NULL, parms, ulLogLevel);
	}
	long IVS_OCX_LoginByTicket(LPCTSTR pTicketID, LPCTSTR pServerIP, LPCTSTR pPort, unsigned long ulClientType)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_BSTR VTS_UI4 ;
		InvokeHelper(0x22d, DISPATCH_METHOD, VT_I4, (void*)&result, parms, pTicketID, pServerIP, pPort, ulClientType);
		return result;
	}
	long IVS_OCX_SetReceiveOMUAlarm(long bReceive)
	{
		long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x22e, DISPATCH_METHOD, VT_I4, (void*)&result, parms, bReceive);
		return result;
	}
	CString IVS_OCX_GetVideoDiagnose(LPCTSTR pDomainCode, LPCTSTR pCameraCode)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR ;
		InvokeHelper(0x22f, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, pDomainCode, pCameraCode);
		return result;
	}
	long IVS_OCX_SetVideoDiagnose(LPCTSTR pReqXml)
	{
		long result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x230, DISPATCH_METHOD, VT_I4, (void*)&result, parms, pReqXml);
		return result;
	}
	CString IVS_OCX_GetStreamListByCam(LPCTSTR pDomainCode, LPCTSTR pCameraCode)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR ;
		InvokeHelper(0x231, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, pDomainCode, pCameraCode);
		return result;
	}
	long IVS_OCX_ShutdownStreamByUser(LPCTSTR pDomainCode, unsigned long ulUserID, LPCTSTR pCameraCode, long lStreamType, long lDuration)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_UI4 VTS_BSTR VTS_I4 VTS_I4 ;
		InvokeHelper(0x232, DISPATCH_METHOD, VT_I4, (void*)&result, parms, pDomainCode, ulUserID, pCameraCode, lStreamType, lDuration);
		return result;
	}
	CString IVS_OCX_GetStreamListByUser(LPCTSTR pDomainCode, unsigned long ulUserID)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR VTS_UI4 ;
		InvokeHelper(0x233, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, pDomainCode, ulUserID);
		return result;
	}
	long IVS_OCX_SetMicVolume(unsigned long ulVolumeValue)
	{
		long result;
		static BYTE parms[] = VTS_UI4 ;
		InvokeHelper(0x234, DISPATCH_METHOD, VT_I4, (void*)&result, parms, ulVolumeValue);
		return result;
	}
	unsigned long IVS_OCX_GetMicVolume()
	{
		unsigned long result;
		InvokeHelper(0x235, DISPATCH_METHOD, VT_UI4, (void*)&result, NULL);
		return result;
	}
	long IVS_OCX_LocalSnapshotToDir(long lWndID, unsigned long ulPictureFormat, LPCTSTR pFileName)
	{
		long result;
		static BYTE parms[] = VTS_I4 VTS_UI4 VTS_BSTR ;
		InvokeHelper(0x236, DISPATCH_METHOD, VT_I4, (void*)&result, parms, lWndID, ulPictureFormat, pFileName);
		return result;
	}
	long IVS_OCX_SetVideoEffect(long lWndID, long lBrightValue, long lContrastValue, long lSaturationValue, long lHueValue)
	{
		long result;
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 ;
		InvokeHelper(0x237, DISPATCH_METHOD, VT_I4, (void*)&result, parms, lWndID, lBrightValue, lContrastValue, lSaturationValue, lHueValue);
		return result;
	}
	CString IVS_OCX_GetDomainDeviceList(LPCTSTR pDomainCode, unsigned long ulDeviceType, unsigned long ulFromIndex, unsigned long ulToIndex)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR VTS_UI4 VTS_UI4 VTS_UI4 ;
		InvokeHelper(0x238, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, pDomainCode, ulDeviceType, ulFromIndex, ulToIndex);
		return result;
	}

// Properties
//



};
