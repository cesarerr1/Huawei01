#pragma once
#include "elte_playerctrl.h"


// Cuadro de diálogo de DialogoTrunking

class CDialogoTrunking : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogoTrunking)

public:
	CDialogoTrunking(CWnd* pParent = NULL);   // Constructor estándar
	virtual ~CDialogoTrunking();

// Datos del cuadro de diálogo
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TRUNKING_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // Compatibilidad con DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
};
