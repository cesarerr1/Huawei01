#include "stdafx.h"
#include "MyButton.h"
#include "AntialiasingWu.h"
#include "resource.h"
#define NOMBRE_CONTROL _T("CMyButton")  // Window class name

CMyButton::CMyButton()
{
	mouseStatus = 0;
	mouseEvt = 0;
	RegisterWindowClass();
	regiones = NULL;
}


CMyButton::~CMyButton()
{
}

BEGIN_MESSAGE_MAP(CMyButton, CWnd)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_PAINT()
END_MESSAGE_MAP()

BOOL CMyButton::RegisterWindowClass()
{
	WNDCLASS wndcls;
	HINSTANCE hInst = AfxGetInstanceHandle();

	if (!(::GetClassInfo(hInst, NOMBRE_CONTROL, &wndcls)))
	{
		// otherwise we need to register a new class
		wndcls.style = CS_DBLCLKS;// | CS_HREDRAW | CS_VREDRAW;
		wndcls.lpfnWndProc = ::DefWindowProc;
		wndcls.cbClsExtra = wndcls.cbWndExtra = 0;
		wndcls.hInstance = hInst;
		wndcls.hIcon = NULL;
		wndcls.hCursor = AfxGetApp()->LoadStandardCursor(IDC_ARROW);
		wndcls.hbrBackground = ::GetSysColorBrush(COLOR_3DFACE);
		wndcls.lpszMenuName = NULL;
		wndcls.lpszClassName = NOMBRE_CONTROL;

		if (!AfxRegisterClass(&wndcls))
		{
			AfxThrowResourceException();
			return FALSE;
		}
	}

	return TRUE;
}

void CMyButton::SetButtonID(UINT buttonID, UINT buttonMode) {
	char buffer[1024];
	sprintf_s(buffer, 1024, "Carga de ID para el control: %d\n", buttonID);
	OutputDebugStringA(buffer);
	this->buttonID = buttonID;
	this->buttonMode = buttonMode;
}

void CMyButton::SetButtonIcon(UINT iconoID, BYTE width, BYTE height, SHORT depth) {
	this->iconoID = iconoID;
	this->iconoWidth = width;
	this->iconoHeight = height;
	this->iconoDepth = depth;
}

void CMyButton::OnLButtonDown(UINT nFlags, CPoint point)
{
	// Se evalua si se debe atender el evento
	if ((mouseEvt & MOUSE_LEFT_BUTTON_DOWN) == 0)
		return CWnd::OnLButtonDown(nFlags, point);

	// Se atiende y marca el evento
	char buffer[1024];
	sprintf_s(buffer, 1024, "MyButton - Boton izquierdo down[%d].\n", buttonID);
	OutputDebugStringA(buffer);

	// Se valida el modo de operación del botón
	if (buttonMode == BUTTON_MODE_NORMAL) {
		sprintf_s(buffer, 1024, "MyButton - Envio de evento boton izquierdo normal.[%d].\n", buttonID);
		OutputDebugStringA(buffer);
		mouseStatus = mouseStatus | MOUSE_LEFT_BUTTON_DOWN;
		GetParent()->PostMessageW(buttonID, WM_MOUSE_LEFTBUTTON_DOWN, (LPARAM)&point);
	}
	else if (buttonMode == BUTTON_MODE_PTZ) {

		sprintf_s(buffer, 1024, "MyButton - Barrido de las zonas asociadas con el botón PTZ.[%d].\n", buttonID);
		OutputDebugStringA(buffer);

		// Se valida e inicializa la busqueda de regiones
		HRGN **item = regiones;
		if (item == NULL) {
			sprintf_s(buffer, 1024, "MyButton - ERROR: No se cuenta con regiones para validar[%d].\n", buttonID);
			OutputDebugStringA(buffer);
			return;
		}

		// Se hace el barrido de las regiones
		item++;
		for (int c = 0; c < 5; c++) {
			if (PtInRegion(**item, point.x, point.y)) {				
				sprintf_s(buffer, 1024, "MyButton - Se encontro el click en la zona [%d] - [%d].\n", 
					c, buttonID);
				OutputDebugStringA(buffer);
				mouseStatus = mouseStatus | MOUSE_LEFT_BUTTON_DOWN;
				GetParent()->PostMessageW(buttonID, WM_MOUSE_LEFTBUTTON_DOWN | (c * 0x10), (LPARAM)&point);
			}
			item++;
		}
	}
	
	CWnd::OnLButtonDown(nFlags, point);
}


void CMyButton::OnLButtonUp(UINT nFlags, CPoint point)
{
	// Se evalua si se debe atender el evento
	if ((mouseEvt & MOUSE_LEFT_BUTTON_UP) == 0)
		return CWnd::OnLButtonUp(nFlags, point);

	// Se atiende el evento
	char buffer[1024];
	sprintf_s(buffer, 1024, "MyButton - Boton izquierdo up[%d].\n", buttonID);
	OutputDebugStringA(buffer);

	// Se valida el modo de operación del botón
	if (buttonMode == BUTTON_MODE_NORMAL) {
		sprintf_s(buffer, 1024, "MyButton - Envio de evento boton izquierdo normal.[%d].\n", buttonID);
		OutputDebugStringA(buffer);
		mouseStatus = mouseStatus & !(MOUSE_LEFT_BUTTON_DOWN);
		GetParent()->PostMessageW(buttonID, WM_MOUSE_LEFTBUTTON_UP, (LPARAM)&point);
	}
	else if (buttonMode == BUTTON_MODE_PTZ) {

		sprintf_s(buffer, 1024, "MyButton - MyButton - Barrido de las zonas asociadas con el botón PTZ.[%d].\n", buttonID);
		OutputDebugStringA(buffer);

		// Se valida e inicializa la busqueda de regiones
		HRGN **item = regiones;
		if (item == NULL) {
			sprintf_s(buffer, 1024, "MyButton - ERROR: No se cuenta con regiones para validar[%d].\n", buttonID);
			OutputDebugStringA(buffer);
			return;
		}

		// Se hace el barrido de las regiones
		item++;
		for (int c = 0; c < 5; c++) {
			if (PtInRegion(**item, point.x, point.y)) {
				sprintf_s(buffer, 1024, "MyButton - Se encontro el click en la zona [%d] - [%d].\n",
					c, buttonID);
				OutputDebugStringA(buffer);
				mouseStatus = mouseStatus & !(MOUSE_LEFT_BUTTON_DOWN);
				GetParent()->PostMessageW(buttonID, WM_MOUSE_LEFTBUTTON_UP | (c * 0x10), (LPARAM)&point);
			}
			item++;
		}
	}
	
	CWnd::OnLButtonUp(nFlags, point);
}


void CMyButton::OnRButtonDown(UINT nFlags, CPoint point)
{
	// Se evalua si se debe atender el evento
	if ((mouseEvt & MOUSE_RIGHT_BUTTON_DOWN) == 0)
		return CWnd::OnRButtonDown(nFlags, point);

	// Se atiende el evento
	char buffer[1024];
	sprintf_s(buffer, 1024, "MyButton - Boton derecho down[%d].\n", buttonID);
	OutputDebugStringA(buffer);

	// Se valida el modo de operación del botón
	if (buttonMode == BUTTON_MODE_NORMAL) {
		sprintf_s(buffer, 1024, "MyButton - Envio de evento boton izquierdo normal.[%d].\n", buttonID);
		OutputDebugStringA(buffer);
		mouseStatus = mouseStatus | MOUSE_RIGHT_BUTTON_DOWN;
		GetParent()->PostMessageW(buttonID, WM_MOUSE_RIGHTBUTTON_DOWN, (LPARAM)&point);
	}
	else if (buttonMode == BUTTON_MODE_PTZ) {

		sprintf_s(buffer, 1024, "MyButton - Barrido de las zonas asociadas con el botón PTZ.[%d].\n", buttonID);
		OutputDebugStringA(buffer);

		// Se valida e inicializa la busqueda de regiones
		HRGN **item = regiones;
		if (item == NULL) {
			sprintf_s(buffer, 1024, "MyButton - ERROR: No se cuenta con regiones para validar[%d].\n", buttonID);
			OutputDebugStringA(buffer);
			return;
		}

		// Se hace el barrido de las regiones
		item++;
		for (int c = 0; c < 5; c++) {
			if (PtInRegion(**item, point.x, point.y)) {
				sprintf_s(buffer, 1024, "MyButton - Se encontro el click en la zona [%d] - [%d].\n",
					c, buttonID);
				OutputDebugStringA(buffer);
				mouseStatus = mouseStatus | MOUSE_RIGHT_BUTTON_DOWN;
				GetParent()->PostMessageW(buttonID, WM_MOUSE_RIGHTBUTTON_DOWN | (c * 0x10), (LPARAM)&point);
			}
			item++;
		}
	}

	CWnd::OnRButtonDown(nFlags, point);
}


void CMyButton::OnRButtonUp(UINT nFlags, CPoint point)
{
	// Se evalua si se debe atender el evento
	if ((mouseEvt & MOUSE_RIGHT_BUTTON_UP) == 0)
		return CWnd::OnRButtonUp(nFlags, point);

	// Se atiende el evento
	char buffer[1024];
	sprintf_s(buffer, 1024, "MyButton - Boton derecho up[%d].\n", buttonID);
	OutputDebugStringA(buffer);
	mouseStatus = mouseStatus & !(MOUSE_RIGHT_BUTTON_DOWN);
	GetParent()->PostMessageW(buttonID, WM_MOUSE_RIGHTBUTTON_UP, (LPARAM)&point);
	CWnd::OnRButtonUp(nFlags, point);
}


void CMyButton::OnMouseMove(UINT nFlags, CPoint point)
{
	// Se evalua si se debe atender el evento
	if ((mouseEvt & MOUSE_MOVE) == 0)
		return;

	// Se atiende el evento
	char buffer[1024];
	sprintf_s(buffer, 1024, "MyButton - Mouse moviendose[%d][%d-%d].\n", buttonID,
		point.x, point.y);
	//OutputDebugStringA(buffer);
	//GetParent()->PostMessageW(buttonID, WM_MOUSE_MOVE, (LPARAM)&point);
	CWnd::OnMouseMove(nFlags, point);
}

void CMyButton::OnPaint()
{
	CPaintDC dc(this); 
	RECT rect;
	this->GetClientRect(&rect);

	// Se dibuja el fondo del control	
	dc.FillSolidRect(&rect, RGB(64, 64, 64));

	// Se valida el tipo de control a dibujar
	HRGN **item = NULL, dona;
	if (this->buttonMode == BUTTON_MODE_NORMAL) {

		// Se calculan las regiones del control
		HRGN **item = NULL;
		if (regiones == NULL) {

			// Circulo central
			regiones = (HRGN**)malloc(sizeof(HRGN*) * 1);
			item = regiones;
			*regiones = (HRGN*)malloc(sizeof(HRGN));
			**regiones = ::CreateRoundRectRgn(
				rect.left, rect.top, rect.right, rect.bottom,
				5, 5);
		}
	}

	else if (this->buttonMode == BUTTON_MODE_PTZ) {

		// Se calculan las regiones del control
		if (regiones == NULL) {

			// Circulo central
			regiones = (HRGN**)malloc(sizeof(HRGN*) * 6);
			item = regiones;
			*regiones = (HRGN*)malloc(sizeof(HRGN));
			**regiones = ::CreateRoundRectRgn(
				rect.left, rect.top, rect.right, rect.bottom,
				20, 20);
			//**regiones = ::CreateEllipticRgnIndirect(&rect);

			// Circulo interior
			item++;
			int ancho = rect.right / 3, alto = rect.bottom / 3;
			*item = (HRGN*)malloc(sizeof(HRGN));
			**item = ::CreateEllipticRgn(ancho, alto, ancho * 2, alto * 2);
			dona = ::CreateRectRgn(0, 0, 0, 0);
			CombineRgn(dona, **regiones, **item, RGN_DIFF);

			// Triangulo superior
			item++;
			ancho = rect.right;
			alto = rect.bottom / 2;
			*item = (HRGN*)malloc(sizeof(HRGN));
			**item = ::CreateRectRgn(0, 0, 0, 0);
			POINT puntos[3];
			puntos[0].x = 0;
			puntos[0].y = 0;
			puntos[1].x = rect.right;
			puntos[1].y = 0;
			puntos[2].x = rect.right / 2;
			puntos[2].y = rect.bottom / 2;
			HRGN triangulo = ::CreatePolygonRgn(puntos, 3, ALTERNATE);
			CombineRgn(**item, dona, triangulo, RGN_AND);

			// Triangulo inferior
			item++;
			*item = (HRGN*)malloc(sizeof(HRGN));
			**item = ::CreateRectRgn(0, 0, 0, 0);
			puntos[0].x = 0;
			puntos[0].y = rect.right;
			puntos[1].x = rect.right;
			puntos[1].y = rect.bottom;
			puntos[2].x = rect.right / 2;
			puntos[2].y = rect.bottom / 2;
			triangulo = ::CreatePolygonRgn(puntos, 3, ALTERNATE);
			CombineRgn(**item, dona, triangulo, RGN_AND);

			// Triangulo izquierdo
			item++;
			*item = (HRGN*)malloc(sizeof(HRGN));
			**item = ::CreateRectRgn(0, 0, 0, 0);
			puntos[0].x = 0;
			puntos[0].y = 0;
			puntos[1].x = 0;
			puntos[1].y = rect.bottom;
			puntos[2].x = rect.right / 2;
			puntos[2].y = rect.bottom / 2;
			triangulo = ::CreatePolygonRgn(puntos, 3, ALTERNATE);
			CombineRgn(**item, dona, triangulo, RGN_AND);

			// Trinagulo derecho
			item++;
			*item = (HRGN*)malloc(sizeof(HRGN));
			**item = ::CreateRectRgn(0, 0, 0, 0);
			puntos[0].x = rect.right;
			puntos[0].y = 0;
			puntos[1].x = rect.right;
			puntos[1].y = rect.bottom;
			puntos[2].x = rect.right / 2;
			puntos[2].y = rect.bottom / 2;
			triangulo = ::CreatePolygonRgn(puntos, 3, ALTERNATE);
			CombineRgn(**item, dona, triangulo, RGN_AND);
		}
	}

	// Se hace el barrido de las regiones
	int nRegiones = 0;
	switch (buttonMode)
	{
		default:
		case BUTTON_MODE_NORMAL:
			nRegiones = 1;
			break;

		case BUTTON_MODE_PTZ:
			nRegiones = 6;
			break;
	}

	// Se hace el barrido de las regiones
	item = regiones;
	for (int c = 0; c < nRegiones; c++) {
						
		// Se obtiene el box de la región
		RECT box;
		GetRgnBox(**item, &box);
			
		// Se intenta obtener el icono a pintar
		HICON icono = NULL;
		BYTE width, height;
		if (buttonMode == BUTTON_MODE_NORMAL) {
			icono = LoadResourceIcon(iconoID, iconoWidth, iconoHeight, iconoDepth);
			width = iconoWidth;
			height = iconoHeight;
		}			
			
		else if (buttonMode == BUTTON_MODE_PTZ) {

			if (c == 1)
				icono = LoadResourceIcon(IDI_ICON_CENTRO, 32, 32, 24);

			else if (c == 2)
				icono = LoadResourceIcon(IDI_ICON_ARRIBA, 32, 32, 24);

			else if (c == 3)
				icono = LoadResourceIcon(IDI_ICON_ABAJO, 32, 32, 24);

			else if (c == 4)
				icono = LoadResourceIcon(IDI_ICON_IZQUIERDA, 32, 32, 24);

			else if (c == 5)
				icono = LoadResourceIcon(IDI_ICON_DERECHA, 32, 32, 24);

			width = height = 32;
		}

		if (icono != NULL) {		
			CBrush brush(RGB(195, 195, 195));
			void *itemB = dc.SelectObject(brush);				
			PaintRgn(dc.GetSafeHdc(), **item);
			FrameRgn(dc.GetSafeHdc(), **item, 
				CreateSolidBrush(RGB(165, 165, 165)), 1, 1);
			DrawIcon(dc.GetSafeHdc(),
				box.left + ((box.right - box.left - width) / 2),
				box.top + ((box.bottom - box.top - height) / 2),
				icono);				
			dc.SelectObject(itemB);				
		}

		if (c + 1 < nRegiones)
			item++;
	}

}

void CMyButton::RegistrarEventosActivos(UINT16 evt) {
	char buffer[1024];
	sprintf_s(buffer, 1024, "MyButton - Carga de los eventos para el control: %d-%d\n", buttonID, evt);
	OutputDebugStringA(buffer);
	mouseEvt = evt;
}

HICON CMyButton::LoadResourceIcon(UINT nResID, BYTE nWidth, BYTE nHeight, SHORT nBitDepth)
{
	HICON hIconRet = NULL;

#pragma pack(2)
	struct IcoMemEntry          // This is what an icon resource looks like in memory
	{
		byte Width;             // Width, in pixels, of the image
		byte Height;            // Height, in pixels, of the image
		byte ColorCount;        // Number of colors in image(0 if >=8bpp)
		byte Reserved;          // Reserved (must be 0)
		short Planes;           // Color Planes
		short BitCount;         // Bits per pixel
		int BytesInRes;         // How many bytes in this resource?
		short ID;               // Where in the file is this image?
	};

	struct IcoHeader
	{
		short Reserved;         // Reserved (must be 0)
		short Type;             // 1 = Icon, 0 = Bitmap
		short Count;            // number of icons
		IcoMemEntry Entries;    // address place holder
	};
#pragma pack()

	// Find the start of the icon resource in memory
	HMODULE hModule = AfxGetInstanceHandle();
	HRSRC hRes = ::FindResource(hModule, MAKEINTRESOURCE(nResID), RT_GROUP_ICON);
	HGLOBAL hGlobal = ::LoadResource(hModule, hRes);
	IcoHeader* pHead = (IcoHeader*)::LockResource(hGlobal);
	if (pHead == NULL) {
		char buffer[1024];
		sprintf_s(buffer, "MyButton - ERROR: En la obtención del icono: %d", nResID);
		OutputDebugStringA(buffer);
		return NULL;
	}

	if (pHead->Count != 0)
	{
		// Get the hicon headers so we can examine them
		IcoMemEntry* pEntries = NULL;
		pEntries = new IcoMemEntry[pHead->Count];

		IcoMemEntry* pEntry = &(pHead->Entries);
		CopyMemory(pEntries, pEntry, sizeof(IcoMemEntry) * pHead->Count);

		for (int i = 0; i < pHead->Count; i++)
		{
			// If an icon matches our criteria, extract it
			if (pEntries[i].Width == nWidth && pEntries[i].Height == nHeight &&
				pEntries[i].BitCount == nBitDepth)
			{
				HRSRC hIconInfo = ::FindResource(hModule, MAKEINTRESOURCE(pEntry[i].ID),
					MAKEINTRESOURCE(RT_ICON));
				HGLOBAL hIconRes = ::LoadResource(hModule, hIconInfo);
				BYTE* dibBits = (BYTE*)::LockResource(hIconRes);
				long szLength = ::SizeofResource(hModule, hIconInfo);

				hIconRet = CreateIconFromResourceEx((PBYTE)dibBits, szLength, TRUE, 0x00030000,
					nWidth, nHeight, LR_DEFAULTCOLOR);
				::DestroyIcon((HICON)dibBits);
				break;
			}
		}

		// Clean up
		if (pEntries != NULL)
		{
			delete[] pEntries;
		}
	}

	::DestroyIcon((HICON)pHead);

	return hIconRet;
}