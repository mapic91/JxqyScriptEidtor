#include "ColourSettingDialog.h"

//(*InternalHeaders(ColourSettingDialog)
#include <wx/string.h>
//*)

//(*IdInit(ColourSettingDialog)
const long ColourSettingDialog::ID_LISTBOX1 = wxNewId();
const long ColourSettingDialog::ID_STATICTEXT1 = wxNewId();
const long ColourSettingDialog::ID_STATICTEXT2 = wxNewId();
const long ColourSettingDialog::ID_COLOURPICKERCTRL1 = wxNewId();
const long ColourSettingDialog::ID_COLOURPICKERCTRL2 = wxNewId();
const long ColourSettingDialog::ID_BUTTON1 = wxNewId();
const long ColourSettingDialog::ID_BUTTON2 = wxNewId();
const long ColourSettingDialog::ID_BUTTON3 = wxNewId();
const long ColourSettingDialog::ID_BUTTON4 = wxNewId();
//*)

BEGIN_EVENT_TABLE(ColourSettingDialog,wxDialog)
	//(*EventTable(ColourSettingDialog)
	//*)
END_EVENT_TABLE()

ColourSettingDialog::ColourSettingDialog(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(ColourSettingDialog)
	Create(parent, wxID_ANY, _T("颜色设置"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("wxID_ANY"));
	SetClientSize(wxSize(399,228));
	m_listBox_Style = new wxListBox(this, ID_LISTBOX1, wxPoint(16,24), wxSize(184,144), 0, 0, 0, wxDefaultValidator, _T("ID_LISTBOX1"));
	m_listBox_Style->SetSelection( m_listBox_Style->Append(_T("默认")) );
	m_listBox_Style->Append(_T("注释"));
	m_listBox_Style->Append(_T("跳转"));
	m_listBox_Style->Append(_T("函数"));
	m_listBox_Style->Append(_T("字符串"));
	m_listBox_Style->Append(_T("操作符"));
	m_listBox_Style->Append(_T("变量"));
	m_listBox_Style->Append(_T("数字"));
	m_listBox_Style->Append(_T("行数侧边栏"));
	StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _T("字体颜色："), wxPoint(220,40), wxDefaultSize, 0, _T("ID_STATICTEXT1"));
	StaticText2 = new wxStaticText(this, ID_STATICTEXT2, _T("背景颜色："), wxPoint(220,100), wxDefaultSize, 0, _T("ID_STATICTEXT2"));
	m_colourPickerCtrl_Forground = new wxColourPickerCtrl(this, ID_COLOURPICKERCTRL1, wxColour(0,0,0), wxPoint(220,65), wxSize(70,20), 0, wxDefaultValidator, _T("ID_COLOURPICKERCTRL1"));
	m_colourPickerCtrl_BackGround = new wxColourPickerCtrl(this, ID_COLOURPICKERCTRL2, wxColour(0,0,0), wxPoint(220,125), wxSize(70,20), 0, wxDefaultValidator, _T("ID_COLOURPICKERCTRL2"));
	m_button_Forground = new wxButton(this, ID_BUTTON1, _T("D"), wxPoint(300,65), wxSize(20,20), 0, wxDefaultValidator, _T("ID_BUTTON1"));
	m_button_Forground->Disable();
	m_button_Forground->SetToolTip(_T("默认颜色"));
	m_button_Background = new wxButton(this, ID_BUTTON2, _T("D"), wxPoint(300,125), wxSize(20,20), 0, wxDefaultValidator, _T("ID_BUTTON2"));
	m_button_Background->Disable();
	m_button_Background->SetToolTip(_T("默认颜色"));
	m_button_OK = new wxButton(this, ID_BUTTON3, _T("确认"), wxPoint(88,192), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON3"));
	m_button_Cancle = new wxButton(this, ID_BUTTON4, _T("取消"), wxPoint(216,192), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON4"));
	Center();

	Connect(ID_LISTBOX1,wxEVT_COMMAND_LISTBOX_SELECTED,(wxObjectEventFunction)&ColourSettingDialog::Onm_listBox_StyleSelect);
	Connect(ID_COLOURPICKERCTRL1,wxEVT_COMMAND_COLOURPICKER_CHANGED,(wxObjectEventFunction)&ColourSettingDialog::Onm_colourPickerCtrl_ForgroundColourChanged);
	Connect(ID_COLOURPICKERCTRL2,wxEVT_COMMAND_COLOURPICKER_CHANGED,(wxObjectEventFunction)&ColourSettingDialog::Onm_colourPickerCtrl_BackGroundColourChanged);
	Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&ColourSettingDialog::Onm_button_ForgroundClick);
	Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&ColourSettingDialog::Onm_button_BackgroundClick);
	Connect(ID_BUTTON3,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&ColourSettingDialog::Onm_button_OKClick);
	Connect(ID_BUTTON4,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&ColourSettingDialog::Onm_button_CancleClick);
	//*)
	m_colourPickerCtrl_Forground->SetColour(m_cfg.GetStyleForegroundColour(0));
	m_colourPickerCtrl_BackGround->SetColour(m_cfg.GetStyleBackgroundColour(0));
}

ColourSettingDialog::~ColourSettingDialog()
{
	//(*Destroy(ColourSettingDialog)
	//*)
}


void ColourSettingDialog::Onm_colourPickerCtrl_ForgroundColourChanged(wxColourPickerEvent& event)
{
	wxColour col = event.GetColour();
	int sel = GetCorrectedListSelection();
	if(sel != wxNOT_FOUND)
	{
		m_cfg.SetStyleForegroundColour(sel, col);
		m_button_Forground->Enable(true);
	}

}

void ColourSettingDialog::Onm_colourPickerCtrl_BackGroundColourChanged(wxColourPickerEvent& event)
{
	wxColour col = event.GetColour();
	int sel = GetCorrectedListSelection();
	if(sel != wxNOT_FOUND)
	{
		m_cfg.SetStyleBackgroundColour(sel, col);
		m_button_Background->Enable(true);
	}

}

void ColourSettingDialog::Onm_button_ForgroundClick(wxCommandEvent& event)
{
	int sel = GetCorrectedListSelection();
	if(sel != wxNOT_FOUND)
	{
		m_cfg.UnsetForgroundColour(sel);
		m_colourPickerCtrl_Forground->SetColour(m_cfg.GetStyleForegroundColour(0));
		m_button_Forground->Enable(false);
	}
}

void ColourSettingDialog::Onm_button_BackgroundClick(wxCommandEvent& event)
{
	int sel = GetCorrectedListSelection();
	if(sel != wxNOT_FOUND)
	{
		m_cfg.UnsetBackgroundColour(sel);
		m_colourPickerCtrl_BackGround->SetColour(m_cfg.GetStyleBackgroundColour(0));
		m_button_Background->Enable(false);
	}
}

void ColourSettingDialog::Onm_button_OKClick(wxCommandEvent& event)
{
	m_cfg.WriteConfig();
	EndModal(wxID_OK);
}

void ColourSettingDialog::Onm_button_CancleClick(wxCommandEvent& event)
{
	EndModal(wxID_CANCEL);
}

void ColourSettingDialog::Onm_listBox_StyleSelect(wxCommandEvent& event)
{
	int sel = GetCorrectedListSelection();
	if(sel != wxNOT_FOUND)
	{
		wxColour forcol, backcol;
		if(m_cfg.IsForgroundColourSetted(sel))
		{
			forcol = m_cfg.GetStyleForegroundColour(sel);
			m_button_Forground->Enable(true);
		}
		else
		{
			forcol = m_cfg.GetStyleForegroundColour(0);
			m_button_Forground->Enable(false);
		}
		if(m_cfg.IsBackgroundColourSetted(sel))
		{
			backcol = m_cfg.GetStyleBackgroundColour(sel);
			m_button_Background->Enable(true);
		}
		else
		{
			backcol = m_cfg.GetStyleBackgroundColour(0);
			m_button_Background->Enable(false);
		}
		m_colourPickerCtrl_Forground->SetColour(forcol);
		m_colourPickerCtrl_BackGround->SetColour(backcol);
	}
}
int ColourSettingDialog::GetCorrectedListSelection()
{
	if(!m_listBox_Style) return wxNOT_FOUND;
	int sel = m_listBox_Style->GetSelection();
	switch(sel)
	{
	case 8: //行数侧边栏
		sel = wxSTC_STYLE_LINENUMBER;
		break;
	}
	return sel;
}
