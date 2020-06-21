#include "cMain.h"
#include "cEditorFrame.h"
#include <wx/numdlg.h>

wxBEGIN_EVENT_TABLE(cMain, wxMDIParentFrame)
EVT_MENU(10001, cMain::OnMenuNew)
EVT_MENU(10002, cMain::OnMenuOpen)
EVT_MENU(10003, cMain::OnMenuSave)
EVT_MENU(10004, cMain::OnMenuExit)
wxEND_EVENT_TABLE()

cMain::cMain() : wxMDIParentFrame(nullptr, wxID_ANY, "Sprite editor")
{
	m_MenuBar = new wxMenuBar();
	this->SetMenuBar(m_MenuBar);
	wxMenu* menuFile = new wxMenu();

	menuFile->Append(10001, "New");
	menuFile->Append(10002, "Open");
	menuFile->Append(10003, "Save");
	menuFile->Append(10004, "Exit");

	//Add File Menu to Menu Bar
	m_MenuBar->Append(menuFile, "File");

	//Add a toolbar for pallete
	m_ToolBar = this->CreateToolBar(wxTB_HORIZONTAL, wxID_ANY);

	wxColor pallete[16];
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

	for (int i = 0; i < 16; i++)
	{
		wxButton* b = new wxButton(m_ToolBar, 10100 + i, "", wxDefaultPosition, wxSize(40, 24), 0);
		b->SetBackgroundColour(pallete[i]);
		b->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(cMain::OnSelectColour), nullptr, this);
		m_ToolBar->AddControl(b);
	}
	wxButton* b = new wxButton(m_ToolBar, 10100 + 16, "ALPHA", wxDefaultPosition, wxSize(60, 24), 0);
	m_ToolBar->AddControl(b);
	b->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(cMain::OnSelectColour), nullptr, this);
	m_ToolBar->Realize();
}

cMain::~cMain()
{
}

void cMain::OnMenuNew(wxCommandEvent& evt)
{
	cEditorFrame* f = new cEditorFrame(this, "Test");


	
	int width;
	int height;
	wxNumberEntryDialog  dlgW(this, "Enter width", "width", "width", 16, 5, 40);
	if (dlgW.ShowModal() == wxID_OK)
	{	
		width = dlgW.GetValue();
	}
	wxNumberEntryDialog  dlgH(this, "Enter height", "height", "height", 16, 5, 40);
	
	if (dlgH.ShowModal() == wxID_OK)
	{
		height = dlgH.GetValue();
	
	}
	
	f->New(height, width);
	f->Show();
	evt.Skip();
}

void cMain::OnMenuOpen(wxCommandEvent& evt)
{
	wxFileDialog dlg(this, "Open olcSprite file", "", "", ".spr Files (*.spr)|*.spr", wxFD_OPEN | wxFD_FILE_MUST_EXIST);
	if (dlg.ShowModal() == wxID_OK)
	{
		cEditorFrame* f = new cEditorFrame(this, dlg.GetPath());
		f->Open(dlg.GetPath());
		f->Show();
	}
}

void cMain::OnMenuSave(wxCommandEvent& evt)
{
	if (GetActiveChild() != nullptr)
	{
		wxFileDialog dlg(this, "Save olcSprite file", "", "", ".spr Files (*.spr)|*.spr", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
		if (dlg.ShowModal() == wxID_OK)
		{
			((cEditorFrame*)GetActiveChild())->Save(dlg.GetPath());
		}
	}
}

void cMain::OnMenuExit(wxCommandEvent& evt)
{
	Close();
	evt.Skip();
}

void cMain::OnSelectColour(wxCommandEvent& evt)
{
	int color = evt.GetId() - 10100;
	if (GetActiveChild() != nullptr)
	{
		((cEditorFrame*)GetActiveChild())->SetColour(color);
	}
	evt.Skip();
}