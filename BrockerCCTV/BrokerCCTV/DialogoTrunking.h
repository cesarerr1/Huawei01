#pragma once
#include "elte_playerctrl.h"


// Cuadro de di�logo de DialogoTrunking

class CDialogoTrunking : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogoTrunking)

public:
	CDialogoTrunking(CWnd* pParent = NULL);   // Constructor est�ndar
	virtual ~CDialogoTrunking();

// Datos del cuadro de di�logo
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TRUNKING_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // Compatibilidad con DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
};
