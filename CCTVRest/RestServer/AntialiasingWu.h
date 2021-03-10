#pragma once
class CAntialiasingWu
{
public:
	CAntialiasingWu();
	~CAntialiasingWu();
	static void DrawWuCirlce(CDC *pDC, int x, int y, int r, COLORREF clrLine);
	static void DrawPixel(CDC *pDC, short x, short y, short color);
	static void DrawWuLine(CDC * pDC, short X0, short Y0, short X1, short Y1, short BaseColor, 
		short NumLevels, unsigned short IntensityBits);
	static void DrawWuLine(CDC * pDC, int X0, int Y0, int X1, int Y1, COLORREF clrLine);
};

