#include "cCanvas.h"

#include "wx/dcclient.h"
#include "wx/dcmemory.h"
#include "wx/dcbuffer.h"

wxBEGIN_EVENT_TABLE(cCanvas, wxHVScrolledWindow)
EVT_PAINT(cCanvas::OnPaint)
EVT_LEFT_DOWN(cCanvas::OnMouseLefDown)
EVT_MOTION(cCanvas::OnMouseMotion)
wxEND_EVENT_TABLE()

cCanvas::cCanvas(wxWindow* parent) : wxHVScrolledWindow(parent, wxID_ANY)
{
	SetRowColumnCount(40, 40);
	SetBackgroundStyle(wxBG_STYLE_PAINT);
	pallete[0] = wxColor(0, 0, 0);
	pallete[1] = wxColor(0, 0, 128);
	pallete[2] = wxColor(0, 128, 0);
	pallete[3] = wxColor(0, 128, 128);
	pallete[4] = wxColor(128, 0, 0);
	pallete[5] = wxColor(128, 0, 128);
	pallete[6] = wxColor(128, 128, 0);
	pallete[7] = wxColor(192, 192, 192);
	pallete[8] = wxColor(128, 128, 128);
	pallete[9] = wxColor(0, 0, 255);
	pallete[10] = wxColor(0, 255, 0);
	pallete[11] = wxColor(0, 255, 255);
	pallete[12] = wxColor(255, 0, 0);
	pallete[13] = wxColor(255, 0, 255);
	pallete[14] = wxColor(255, 255, 0);
	pallete[15] = wxColor(255, 255, 255);
}

cCanvas::~cCanvas()
{

}

void cCanvas::SetPixelSize(int n)
{
	m_nPixelSize = n;
	wxVarHScrollHelper::RefreshAll();
	wxVarVScrollHelper::RefreshAll();

	Refresh();
}

void cCanvas::SetSpriteData(int rows, int columns, unsigned char* pSprite)
{
	m_pSprite = pSprite;
	this->SetRowColumnCount(rows, columns);
}

void cCanvas::SetColour(int c)
{
	m_nColour = c;
}

wxCoord cCanvas::OnGetRowHeight(size_t row) const
{
	return wxCoord(m_nPixelSize);
}

wxCoord cCanvas::OnGetColumnWidth(size_t row) const
{
	return wxCoord(m_nPixelSize);
}

void cCanvas::OnDraw(wxDC& dc)
{
	dc.Clear();
	wxBrush brush = dc.GetBrush();
	wxPen pen = dc.GetPen();

	wxPosition s = GetVisibleBegin();
	wxPosition e = GetVisibleEnd();

	pen.SetStyle(wxPENSTYLE_DOT_DASH);
	pen.SetColour(wxColor(200, 200, 200));
	dc.SetPen(pen);
	if (m_nPixelSize <= 4) dc.SetPen(*wxTRANSPARENT_PEN);
	
	for (int y = 0; y < e.GetRow(); y++)
		for (int x = 0; x < e.GetColumn(); x++)
		{
			int color = m_pSprite[y * this->GetColumnCount() + x];
			if (color < 16)
			{
				brush.SetColour(pallete[color]);
				brush.SetStyle(wxBRUSHSTYLE_SOLID);

			}
			else
			{
				brush.SetStyle(wxBrushStyle::wxBRUSHSTYLE_CROSSDIAG_HATCH);
				brush.SetColour(wxColor(0, 0, 0));

			}
			dc.SetBrush(brush);
			dc.DrawRectangle(x * m_nPixelSize, y * m_nPixelSize, m_nPixelSize, m_nPixelSize);
		}

}

void cCanvas::OnPaint(wxPaintEvent& evt)
{
	wxBufferedPaintDC dc(this);
	this->PrepareDC(dc);
	this->OnDraw(dc);
}

void cCanvas::OnMouseLefDown(wxMouseEvent& evt)
{
	wxPosition s = GetVisibleBegin();
	m_pSprite[(evt.GetY() / m_nPixelSize + s.GetRow()) * this->GetColumnCount() + (evt.GetX() / m_nPixelSize + s.GetColumn())] = m_nColour;
	this->Refresh(false);
	evt.Skip();
}

void cCanvas::OnMouseMotion(wxMouseEvent& evt)
{
	
	evt.Skip();
}
