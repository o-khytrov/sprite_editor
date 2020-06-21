#pragma once
#include "wx/wx.h"
#include "wx/vscroll.h"

class cCanvas :wxHVScrolledWindow
{
public:
	cCanvas(wxWindow* parent);
	~cCanvas();
	void SetPixelSize(int n);
	void SetSpriteData(int rows, int columns, unsigned char* pSprite);
	void SetColour(int c);
private:
	int m_nPixelSize = 8;

private:
	unsigned char* m_pSprite = nullptr;
	wxColor pallete[16];
	int m_nColour = 0;
	virtual wxCoord OnGetRowHeight(size_t row) const;
	virtual wxCoord OnGetColumnWidth(size_t row) const;
	void OnDraw(wxDC& dc);
	void OnPaint(wxPaintEvent& evt);
	void OnMouseLefDown(wxMouseEvent& evt);
	void OnMouseMotion(wxMouseEvent& evt);
	wxDECLARE_EVENT_TABLE();
};

