#include "cEditorFrame.h"

wxBEGIN_EVENT_TABLE(cEditorFrame, wxMDIChildFrame)
EVT_SLIDER(20001, cEditorFrame::OnZoomChange)
wxEND_EVENT_TABLE()
cEditorFrame::cEditorFrame(wxMDIParentFrame* parent, wxString sName) :wxMDIChildFrame(parent, wxID_ANY, sName)
{
	m_Canvas = new cCanvas(this);
	m_StatusBar = this->CreateStatusBar(3, wxSTB_DEFAULT_STYLE, wxID_ANY);
	m_ZoomSlider = new wxSlider(m_StatusBar, 20001, 8, 1, 32);
}

cEditorFrame::~cEditorFrame()
{
}

void cEditorFrame::SetColour(int c)
{
	m_Canvas->SetColour(c);
}

bool cEditorFrame::Save(wxString sFileName)
{
	for (int i = 0; i < sprBase.nWidth; i++)
		for (int j = 0; j < sprBase.nHeight; j++)
		{
			short color = m_pSprite[j * sprBase.nWidth + i];
			if (color == 16)
			{
				sprBase.SetColour(i, j, 0);
				sprBase.SetGlyph(i, j, L' ');
			}
			else {
				sprBase.SetColour(i, j, color);
				sprBase.SetGlyph(i, j, 0x2588);
			}
		}
	return sprBase.Save(sFileName.wc_str());
}

bool cEditorFrame::Open(wxString sFileName)
{
	if (!sprBase.Load(sFileName.wc_str()))

		return false;
	else
	{
		delete[] m_pSprite;
		m_pSprite = new unsigned char[sprBase.nWidth * sprBase.nHeight]{ 0 };
		for (int i = 0; i < sprBase.nWidth; i++)
			for (int j = 0; j < sprBase.nHeight; j++)
			{
				wchar_t glyph = sprBase.GetGlyph(i, j);
				short color = sprBase.GetColour(i, j);
				if (glyph == L' ')
				{
					m_pSprite[j * sprBase.nWidth + i] = 16;
				}
				else
				{
					m_pSprite[j * sprBase.nWidth + i] = color & 0x000F;
				}
			}

		m_Canvas->SetSpriteData(sprBase.nHeight, sprBase.nWidth, m_pSprite);
		m_StatusBar->SetStatusText(wxString("Size: ") << sprBase.nWidth << " x " << sprBase.nHeight, 2);
		return true;
	}
	
}

bool cEditorFrame::New(int r, int c)
{
	delete[] m_pSprite;
	m_pSprite = new unsigned char[r * c]{ 0 };
	for (int i = 0; i < r * c; i++) {
		m_pSprite[i] = ' ';
	}
		m_Canvas->SetSpriteData(r, c, m_pSprite);

	sprBase = olcSprite(c, r);
	m_StatusBar->SetStatusText(wxString("Size: ") << sprBase.nWidth << " x " << sprBase.nHeight, 2);
	return false;
}

void cEditorFrame::OnZoomChange(wxCommandEvent& evt)
{
	m_StatusBar->SetStatusText(wxString("Zoom: ") << m_ZoomSlider->GetValue(), 1);
	m_Canvas->SetPixelSize(m_ZoomSlider->GetValue());
	evt.Skip();
}