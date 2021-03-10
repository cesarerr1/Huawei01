#pragma once

// El equipo generó clases contenedoras IDispatch con Microsoft Visual C++

// NOTA: no modificar el contenido de este archivo.  Si se utiliza Microsoft Visual C++ para generar
//  esta clase, se reemplazarán las modificaciones.

/////////////////////////////////////////////////////////////////////////////
// Clase contenedora de CElte_playerctrl

class CElte_playerctrl : public CWnd
{
protected:
	DECLARE_DYNCREATE(CElte_playerctrl)
public:
	CLSID const& GetClsid()
	{
		static CLSID const clsid
			= { 0x6AB35B6F, 0xD5D4, 0x4DA3, { 0x95, 0x3, 0x1A, 0xD4, 0xE5, 0xE1, 0xE5, 0x89 } };
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

// _DeLTE_Player

// Functions
//

	void AboutBox()
	{
		InvokeHelper(DISPID_ABOUTBOX, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	CString ELTE_OCX_SetLogPath(LPCTSTR pLogFilePath)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x1, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, pLogFilePath);
		return result;
	}
	CString ELTE_OCX_SetLogLevel(unsigned long ulLogLevel)
	{
		CString result;
		static BYTE parms[] = VTS_UI4 ;
		InvokeHelper(0x2, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, ulLogLevel);
		return result;
	}
	CString ELTE_OCX_UploadLogo(LPCTSTR pLogoFilePath)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x3, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, pLogoFilePath);
		return result;
	}
	CString ELTE_OCX_GetVersion(unsigned long ulVersion)
	{
		CString result;
		static BYTE parms[] = VTS_UI4 ;
		InvokeHelper(0x4, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, ulVersion);
		return result;
	}
	CString ELTE_OCX_SetLanguage(unsigned long ulLanguage)
	{
		CString result;
		static BYTE parms[] = VTS_UI4 ;
		InvokeHelper(0x5, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, ulLanguage);
		return result;
	}
	CString ELTE_OCX_ShowToolbar(long ulToolbar)
	{
		CString result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x6, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, ulToolbar);
		return result;
	}
	CString ELTE_OCX_Load(unsigned long ulType)
	{
		CString result;
		static BYTE parms[] = VTS_UI4 ;
		InvokeHelper(0x7, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, ulType);
		return result;
	}
	CString ELTE_OCX_UnLoad()
	{
		CString result;
		InvokeHelper(0x8, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	CString ELTE_OCX_Login(LPCTSTR pUserID, LPCTSTR pPWD, LPCTSTR pServerIP, LPCTSTR pLocalIP, LPCTSTR pServerSIPPort)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR ;
		InvokeHelper(0xa, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, pUserID, pPWD, pServerIP, pLocalIP, pServerSIPPort);
		return result;
	}
	CString ELTE_OCX_Logout(LPCTSTR pUserID)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0xb, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, pUserID);
		return result;
	}
	CString ELTE_OCX_TriggerStatusReport(unsigned long ulEnableStatusReport)
	{
		CString result;
		static BYTE parms[] = VTS_UI4 ;
		InvokeHelper(0xc, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, ulEnableStatusReport);
		return result;
	}
	CString ELTE_OCX_ProvisionManagerInit(LPCTSTR pServerIP, LPCTSTR pUserID)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR ;
		InvokeHelper(0xd, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, pServerIP, pUserID);
		return result;
	}
	CString ELTE_OCX_ProvisionManagerExit()
	{
		CString result;
		InvokeHelper(0xe, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	CString ELTE_OCX_GetDcGroups(LPCTSTR pUserID)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0xf, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, pUserID);
		return result;
	}
	CString ELTE_OCX_GetDcUsers(LPCTSTR pUserID)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x10, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, pUserID);
		return result;
	}
	CString ELTE_OCX_GetGroupUsers(LPCTSTR pGroupID)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x11, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, pGroupID);
		return result;
	}
	CString ELTE_OCX_GetGroupInfo(LPCTSTR pGroupID)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x12, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, pGroupID);
		return result;
	}
	CString ELTE_OCX_GetUserInfo(LPCTSTR pUserID)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x13, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, pUserID);
		return result;
	}
	CString ELTE_OCX_GetDcInfo(LPCTSTR pUserID)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x14, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, pUserID);
		return result;
	}
	CString ELTE_OCX_SubscribeGroup(LPCTSTR pGroupID, unsigned long ulEnableSubscribeGroup)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR VTS_UI4 ;
		InvokeHelper(0x15, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, pGroupID, ulEnableSubscribeGroup);
		return result;
	}
	CString ELTE_OCX_GetUserRECFileInfoList(LPCTSTR pQueryXml)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x16, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, pQueryXml);
		return result;
	}
	CString ELTE_OCX_StartRealPlay(LPCTSTR pResourceID, LPCTSTR pVideoParam)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR ;
		InvokeHelper(0x17, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, pResourceID, pVideoParam);
		return result;
	}
	CString ELTE_OCX_ReverseRealPlay(LPCTSTR pResourceID, LPCTSTR pVideoParam)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR ;
		InvokeHelper(0x18, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, pResourceID, pVideoParam);
		return result;
	}
	CString ELTE_OCX_StopRealPlay(LPCTSTR pResourceID)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x19, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, pResourceID);
		return result;
	}
	CString ELTE_OCX_ShowRealPlay(LPCTSTR pResourceID, LPCTSTR pLocalMediaAddr, LPCTSTR pRemoteMediaAddr)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_BSTR ;
		InvokeHelper(0x1d, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, pResourceID, pLocalMediaAddr, pRemoteMediaAddr);
		return result;
	}
	CString ELTE_OCX_Snapshot(LPCTSTR pResourceID)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x1e, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, pResourceID);
		return result;
	}
	CString ELTE_OCX_HideRealPlay()
	{
		CString result;
		InvokeHelper(0x1f, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	CString ELTE_OCX_PlaySound()
	{
		CString result;
		InvokeHelper(0x21, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	CString ELTE_OCX_StopSound()
	{
		CString result;
		InvokeHelper(0x22, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	CString ELTE_OCX_SetVideoWindowPos(unsigned long ulLeft, unsigned long ulTop, unsigned long ulWidth, unsigned long ulHeight)
	{
		CString result;
		static BYTE parms[] = VTS_UI4 VTS_UI4 VTS_UI4 VTS_UI4 ;
		InvokeHelper(0x23, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, ulLeft, ulTop, ulWidth, ulHeight);
		return result;
	}
	CString ELTE_OCX_FullScreenDisplay()
	{
		CString result;
		InvokeHelper(0x24, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	CString ELTE_OCX_NormalScreenDisplay()
	{
		CString result;
		InvokeHelper(0x25, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	CString ELTE_OCX_SetTitleText(LPCTSTR pTitleText)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x26, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, pTitleText);
		return result;
	}
	CString ELTE_OCX_CreateDynamicGroup(LPCTSTR pDGNAParam)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x27, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, pDGNAParam);
		return result;
	}
	CString ELTE_OCX_CancelDynamicGroup(LPCTSTR pResourceID)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x28, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, pResourceID);
		return result;
	}
	CString ELTE_OCX_CreateTempGroup(LPCTSTR pTEMPGParam)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x29, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, pTEMPGParam);
		return result;
	}
	CString ELTE_OCX_GetNextTempGroupID()
	{
		CString result;
		InvokeHelper(0x2a, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	CString ELTE_OCX_P2PDial(LPCTSTR pResourceID)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x2b, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, pResourceID);
		return result;
	}
	CString ELTE_OCX_P2PRecv(LPCTSTR pResourceID)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x2c, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, pResourceID);
		return result;
	}
	CString ELTE_OCX_P2PReject(LPCTSTR pResourceID)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x2d, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, pResourceID);
		return result;
	}
	CString ELTE_OCX_P2PHangup(LPCTSTR pResourceID)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x2e, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, pResourceID);
		return result;
	}
	CString ELTE_OCX_JoinGroup(LPCTSTR pGroupID)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x2f, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, pGroupID);
		return result;
	}
	CString ELTE_OCX_SubJoinGroup(LPCTSTR pGroupID)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x30, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, pGroupID);
		return result;
	}
	CString ELTE_OCX_PTTDial(LPCTSTR pGroupID)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x31, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, pGroupID);
		return result;
	}
	CString ELTE_OCX_PTTRelease(LPCTSTR pGroupID)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x32, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, pGroupID);
		return result;
	}
	CString ELTE_OCX_PTTHangup(LPCTSTR pGroupID)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x33, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, pGroupID);
		return result;
	}
	CString ELTE_OCX_PTTEmergency(LPCTSTR pGroupID)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x34, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, pGroupID);
		return result;
	}
	CString ELTE_OCX_GroupBreakoff(LPCTSTR pGroupID)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x35, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, pGroupID);
		return result;
	}
	CString ELTE_OCX_P2PBreakin(LPCTSTR pResourceID)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x36, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, pResourceID);
		return result;
	}
	CString ELTE_OCX_P2PBreakoff(LPCTSTR pResourceID)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x37, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, pResourceID);
		return result;
	}
	CString ELTE_OCX_VolMute(LPCTSTR pResourceID, LPCTSTR pMuteParam)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR ;
		InvokeHelper(0x38, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, pResourceID, pMuteParam);
		return result;
	}
	CString ELTE_OCX_VolUnMute(LPCTSTR pResourceID, LPCTSTR pMuteParam)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR ;
		InvokeHelper(0x39, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, pResourceID, pMuteParam);
		return result;
	}
	CString ELTE_OCX_MuteControl(LPCTSTR pResourceID, LPCTSTR pMuteType)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR ;
		InvokeHelper(0x3a, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, pResourceID, pMuteType);
		return result;
	}
	CString ELTE_OCX_GISSubscribe(LPCTSTR pResourceID, LPCTSTR pGISParam)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR ;
		InvokeHelper(0x3b, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, pResourceID, pGISParam);
		return result;
	}
	CString ELTE_OCX_SetBypassBuildMedia(unsigned long ulBypass)
	{
		CString result;
		static BYTE parms[] = VTS_UI4 ;
		InvokeHelper(0x3c, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, ulBypass);
		return result;
	}
	CString ELTE_OCX_ProvisionManagerInitMRS(LPCTSTR pServerIP)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x3d, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, pServerIP);
		return result;
	}

// Properties
//



};
