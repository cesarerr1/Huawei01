#pragma once
#include "afxwin.h"

#define MOUSE_LEFT_BUTTON_DOWN	0x0001
#define MOUSE_LEFT_BUTTON_UP	0x0002
#define MOUSE_RIGHT_BUTTON_DOWN	0x0010
#define MOUSE_RIGHT_BUTTON_UP	0x0020
#define MOUSE_MOVE				0x0100

#define PTZ_BUTTON_TOP			0x1000
#define PTZ_BUTTON_BOTTOM		0x2000
#define PTZ_BUTTON_CENTER		0x3000
#define PTZ_BUTTON_LEFT			0x4000
#define PTZ_BUTTON_

#define WM_MOUSE_LEFTBUTTON_DOWN	WM_APP + 0x0100
#define WM_MOUSE_LEFTBUTTON_UP		WM_APP + 0x0200
#define WM_MOUSE_RIGHTBUTTON_DOWN	WM_APP + 0x0300
#define WM_MOUSE_RIGHTBUTTON_UP		WM_APP + 0x0400
#define WM_MOUSE_MOVE				WM_APP + 0x0500

#define BUTTON_MODE_NORMAL	0x0000
#define BUTTON_MODE_PTZ		0x0001

class CMyButton :
	public CWnd
{
public:
	CMyButton();
	~CMyButton();
	void SetButtonID(UINT buttonID, UINT buttonMode);
	void SetButtonIcon(UINT iconoID, BYTE width, BYTE height, SHORT deep);
	DECLARE_MESSAGE_MAP()
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnPaint();		
	
public:
	void RegistrarEventosActivos(UINT16 evt);

protected:	
	HICON LoadResourceIcon(UINT nResID, BYTE nWidth, BYTE nHeight, SHORT nBitDepth);
	BOOL RegisterWindowClass();
	UINT buttonID;
	UINT iconoID;
	BYTE iconoWidth;
	BYTE iconoHeight;
	SHORT iconoDepth;
	UINT buttonMode;
	UINT mouseStatus;
	UINT mouseEvt;
	HRGN **regiones;
};

