
// BrokerCCTV.h: archivo de encabezado principal para la aplicaci�n PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "incluir 'stdafx.h' antes de incluir este archivo para PCH"
#endif

#include "resource.h"		// S�mbolos principales


// CBrokerCCTVApp:
// Consulte la secci�n BrokerCCTV.cpp para obtener informaci�n sobre la implementaci�n de esta clase
//

class CBrokerCCTVApp : public CWinApp
{
public:
	CBrokerCCTVApp();

// Reemplazos
public:
	virtual BOOL InitInstance();

// Implementaci�n

	DECLARE_MESSAGE_MAP()
};

extern CBrokerCCTVApp theApp;