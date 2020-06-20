#pragma once
#include "wx/wx.h"

class cMain :public wxMDIParentFrame
{
public:
	cMain();
	~cMain();
private:
	wxToolBar *m_ToolBar = nullptr;
	wxMenuBar* m_MenuBar = nullptr;
	wxDECLARE_EVENT_TABLE();
};

