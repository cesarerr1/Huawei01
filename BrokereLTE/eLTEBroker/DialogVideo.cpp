// DialogVideo.cpp : implementation file
//

#include "stdafx.h"
#include "eLTEBroker.h"
#include "DialogVideo.h"
#include "afxdialogex.h"
#include "plog\Log.h"

// CDialogVideo dialog

IMPLEMENT_DYNAMIC(CDialogVideo, CDialogEx)

CDialogVideo::CDialogVideo(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_VIDEO, pParent)
{
	b_inicializado = false;
	p_Sesion = NULL;
	m_brush.CreateSolidBrush(RGB(0, 0, 0));
}

CDialogVideo::~CDialogVideo()
{
	if (s_Video.GetSafeHwnd() != NULL)
		s_Video.DestroyWindow();
}

void CDialogVideo::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDialogVideo, CDialogEx)
	ON_WM_SIZE()
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()

void CDialogVideo::CreateVideoStatic(const CRect& rect)
{
	CRect rtVideo(rect);
	s_Video.Create(NULL, WS_CHILD | WS_VISIBLE, rtVideo, this);
	s_Video.SetParent(this);
	s_Video.Invalidate(TRUE);
}

void CDialogVideo::SetResourceID(string resource) {
	LOGD << "Se solicita asignar el ID del recurso a la ventana de video: " << resource;
	this->s_resource = resource;
}

void CDialogVideo::OnOK()
{
	LOGD << "Se solicita aceptar la operación.";

	CDialogEx::OnOK();
}


void CDialogVideo::OnCancel()
{
	LOGD << "Se solicita cancelar la operación.";

	CDialogEx::OnCancel();
}

BOOL CDialogVideo::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_ESCAPE)
		return FALSE;
	else
		return CDialogEx::PreTranslateMessage(pMsg);
}


void CDialogVideo::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	if (NULL != s_Video.GetSafeHwnd())
	{
		s_Video.SetWindowPos(NULL, 0, 0, cx, cy, SWP_NOMOVE);
		ELTE_SDK_SetPlayWindowSize(s_resource.c_str(), cx, cy);
	}
}


void CDialogVideo::PostNcDestroy()
{
	// TODO: Add your specialized code here and/or call the base class

	CDialogEx::PostNcDestroy();
	delete this;
}


void CDialogVideo::OnPaint()
{
	CPaintDC dc(this); // device context for painting
}


HBRUSH CDialogVideo::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	if (s_Video.GetSafeHwnd() && pWnd == CWnd::FromHandle(s_Video.GetSafeHwnd()))
		return m_brush;

	return hbr;
}
