#pragma once
#include "elte_playerctrl_video.h"
#include "eLTESession.h"
#include "afxwin.h"

// CDialogVideo dialog

class CDialogVideo : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogVideo)

public:
	CDialogVideo(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDialogVideo();

protected:
	bool b_inicializado;
	eLTESession* p_Sesion;

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_VIDEO };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	void CreateVideoStatic(const CRect& rect);
	void SetResourceID(string resource);
	HWND GetVideoStaticHwnd() { return s_Video.GetSafeHwnd(); }
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual void PostNcDestroy();
	afx_msg void OnPaint();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

private:
	string s_resource;
	CBrush m_brush;
	CStatic s_Video;
};
