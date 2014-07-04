#include "JxqyScriptEditor.h"
#include "helperFun.h"
#include "ColourSettingDialog.h"

#include "wx/msgdlg.h"
#include "wx/filedlg.h"
#include "wx/fontdlg.h"

//(*InternalHeaders(JxqyScriptEditor)
#include <wx/string.h>
//*)

//(*IdInit(JxqyScriptEditor)
const long JxqyScriptEditor::ID_AUINOTEBOOK1 = wxNewId();
const long JxqyScriptEditor::MYID_SAVEALL = wxNewId();
const long JxqyScriptEditor::MYID_CLOSE = wxNewId();
const long JxqyScriptEditor::MYID_CLOSEALL = wxNewId();
const long JxqyScriptEditor::MYID_FONTSETTING = wxNewId();
const long JxqyScriptEditor::MYID_COLOURSETTING = wxNewId();
//*)



BEGIN_EVENT_TABLE(JxqyScriptEditor,wxFrame)
    //(*EventTable(JxqyScriptEditor)
    //*)
    EVT_MENU(wxID_NEW, JxqyScriptEditor::OnNewFile)
    EVT_MENU(wxID_OPEN, JxqyScriptEditor::OnOpenFile)
    EVT_MENU(wxID_SAVE, JxqyScriptEditor::OnSave)
    EVT_MENU(wxID_SAVEAS, JxqyScriptEditor::OnSaveAs)
    EVT_MENU(MYID_SAVEALL, JxqyScriptEditor::OnSaveAll)
    EVT_MENU(MYID_CLOSE, JxqyScriptEditor::OnClose)
    EVT_MENU(MYID_CLOSEALL, JxqyScriptEditor::OnCloseAll)
    EVT_MENU(wxID_EXIT, JxqyScriptEditor::OnExit)
    EVT_MENU(MYID_FONTSETTING, JxqyScriptEditor::OnFontSetting)
    EVT_MENU(MYID_COLOURSETTING, JxqyScriptEditor::OnColourSetting)
END_EVENT_TABLE()

JxqyScriptEditor::JxqyScriptEditor(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
    //(*Initialize(JxqyScriptEditor)
    wxBoxSizer* BoxSizer1;

    Create(parent, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("wxID_ANY"));
    SetClientSize(wxSize(800,600));
    BoxSizer1 = new wxBoxSizer(wxHORIZONTAL);
    m_AuiBook = new wxAuiNotebook(this, ID_AUINOTEBOOK1, wxDefaultPosition, wxDefaultSize, wxAUI_NB_CLOSE_ON_ALL_TABS|wxAUI_NB_DEFAULT_STYLE);
    BoxSizer1->Add(m_AuiBook, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    SetSizer(BoxSizer1);
    MenuBar1 = new wxMenuBar();
    Menu1 = new wxMenu();
    MenuItem2 = new wxMenuItem(Menu1, wxID_NEW, _T("新建文档\tCtrl+N"), wxEmptyString, wxITEM_NORMAL);
    Menu1->Append(MenuItem2);
    MenuItem1 = new wxMenuItem(Menu1, wxID_OPEN, _T("打开...\tCtrl+O"), wxEmptyString, wxITEM_NORMAL);
    Menu1->Append(MenuItem1);
    MenuItem3 = new wxMenuItem(Menu1, wxID_SAVE, _T("保存\tCtrl+S"), wxEmptyString, wxITEM_NORMAL);
    Menu1->Append(MenuItem3);
    MenuItem4 = new wxMenuItem(Menu1, wxID_SAVEAS, _T("另存为...\tCtrl+Alt+S"), wxEmptyString, wxITEM_NORMAL);
    Menu1->Append(MenuItem4);
    MenuItem5 = new wxMenuItem(Menu1, MYID_SAVEALL, _T("保存所有\tCtrl+Shift+S"), _T("保存所有打开的文件"), wxITEM_NORMAL);
    Menu1->Append(MenuItem5);
    MenuItem6 = new wxMenuItem(Menu1, MYID_CLOSE, _T("关闭\tCtrl+W"), wxEmptyString, wxITEM_NORMAL);
    Menu1->Append(MenuItem6);
    MenuItem7 = new wxMenuItem(Menu1, MYID_CLOSEALL, _T("关闭所有\tShift+Esc"), _T("关闭所有打开的文档"), wxITEM_NORMAL);
    Menu1->Append(MenuItem7);
    MenuItem8 = new wxMenuItem(Menu1, wxID_EXIT, _T("退出\tAlt+F4"), wxEmptyString, wxITEM_NORMAL);
    Menu1->Append(MenuItem8);
    MenuBar1->Append(Menu1, _T("文件"));
    Menu2 = new wxMenu();
    MenuItem9 = new wxMenuItem(Menu2, MYID_FONTSETTING, _T("字体设置..."), wxEmptyString, wxITEM_NORMAL);
    Menu2->Append(MenuItem9);
    MenuItem10 = new wxMenuItem(Menu2, MYID_COLOURSETTING, _T("颜色设置..."), wxEmptyString, wxITEM_NORMAL);
    Menu2->Append(MenuItem10);
    MenuBar1->Append(Menu2, _T("设置"));
    SetMenuBar(MenuBar1);
    SetSizer(BoxSizer1);
    Layout();
    Center();
    //*)
    Init();
	AddNewFile();
}

JxqyScriptEditor::~JxqyScriptEditor()
{
    //(*Destroy(JxqyScriptEditor)
    //*)
    Uninit();
}
void JxqyScriptEditor::Init()
{

    m_AuiBook->Bind(wxEVT_AUINOTEBOOK_PAGE_CLOSE, &JxqyScriptEditor::OnPageClose, this);
}

void JxqyScriptEditor::Uninit()
{

	m_AuiBook->Unbind(wxEVT_AUINOTEBOOK_PAGE_CLOSE, &JxqyScriptEditor::OnPageClose, this);
}


void JxqyScriptEditor::OnNewFile(wxCommandEvent& event)
{
	AddNewFile();
}

void JxqyScriptEditor::OnOpenFile(wxCommandEvent& event)
{

}

void JxqyScriptEditor::OnSave(wxCommandEvent& event)
{

}

void JxqyScriptEditor::OnSaveAs(wxCommandEvent& event)
{

}

void JxqyScriptEditor::OnSaveAll(wxCommandEvent& event)
{

}

void JxqyScriptEditor::OnClose(wxCommandEvent& event)
{

}

void JxqyScriptEditor::OnCloseAll(wxCommandEvent& event)
{

}

void JxqyScriptEditor::OnExit(wxCommandEvent& event)
{

}

void JxqyScriptEditor::OnFontSetting(wxCommandEvent& event)
{
	wxFontData data;
	data.SetInitialFont(m_cfg.GetDefaultFont());
	wxFontDialog fontdlg(this, data);
	if(fontdlg.ShowModal() == wxID_OK)
	{
		m_cfg.SetDefaultFont(fontdlg.GetFontData().GetChosenFont());
		m_cfg.WriteConfig();
	}
	ResetOpenedPageStyle();
}

void JxqyScriptEditor::OnColourSetting(wxCommandEvent& event)
{
	ColourSettingDialog dlg(this);
	if(dlg.ShowModal() == wxID_OK)
	{
		m_cfg.ReadConfig();
		ResetOpenedPageStyle();
	}
}


void JxqyScriptEditor::OnPageClose(wxAuiNotebookEvent& event)
{
    int pageIdx = event.GetSelection();
    JxqyStc *stc = (JxqyStc*)m_AuiBook->GetPage(pageIdx);
    if(stc)
    {
        if(stc->GetModify())
        {
            wxString title = m_AuiBook->GetPageText(pageIdx);
            wxString msg = wxT("保存文件 \"") + title + wxT("\" ?");
            int ret = wxMessageBox(msg, wxT("保存"), wxCANCEL | wxYES_NO | wxICON_QUESTION |wxCENTER);
            if(ret == wxYES)
            {
                if(stc->FilePathEmpty())
                {
                    wxFileDialog fileDlg(this,
                                         wxT("保存文件"),
                                         wxEmptyString,
                                         title,
                                         wxT("txt(*.txt)|*.txt|所有文件(*.*)|*.*"),
                                         wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
                    if(fileDlg.ShowModal() == wxID_OK)
                    {
                        if(!stc->SaveToFile(fileDlg.GetPath()))
                        {
                            wxMessageBox(wxT("保存失败！"), wxT("错误"), wxOK | wxCENTER | wxICON_ERROR);
                            event.Veto();
                        }
                    }
                }
                else
                {
                    if(!stc->Save())
                    {
                        wxMessageBox(wxT("保存失败！"), wxT("错误"), wxOK | wxCENTER | wxICON_ERROR);
                        event.Veto();
                    }
                }
            }
            else if(ret == wxCANCEL)
				event.Veto();
        }
    }
}

void JxqyScriptEditor::AddNewFile()
{
	JxqyStc *stc = GetInitlizedJxqyStc();
    m_AuiBook->AddPage(stc, wxT("未命名"));
}


JxqyStc* JxqyScriptEditor::GetInitlizedJxqyStc()
{
	JxqyStc *stc = new JxqyStc(m_AuiBook);
	SetJxqyStcStyleFromSetting(stc);
	return stc;
}
void JxqyScriptEditor::SetJxqyStcStyleFromSetting(JxqyStc* stc)
{
//	stc->SetLexer(wxSTC_LEX_JXQY);
	stc->SetFunctionKeywordFromFile(m_cfg.GetLexerFilePath());

	//Default style
	wxFont defFont = m_cfg.GetDefaultFont();
    stc->StyleSetFont(wxSTC_STYLE_DEFAULT, defFont);
    stc->StyleSetForeground(wxSTC_STYLE_DEFAULT, m_cfg.GetStyleForegroundColour(0));
    stc->StyleSetBackground(wxSTC_STYLE_DEFAULT, m_cfg.GetStyleBackgroundColour(0));
    stc->StyleClearAll();

	//Text style
    stc->StyleSetForeground(wxSTC_JXQY_COMMENT, m_cfg.GetStyleForegroundColour(wxSTC_JXQY_COMMENT));
    stc->StyleSetForeground(wxSTC_JXQY_FUNCTION, m_cfg.GetStyleForegroundColour(wxSTC_JXQY_FUNCTION));
    stc->StyleSetForeground(wxSTC_JXQY_OPERATOR, m_cfg.GetStyleForegroundColour(wxSTC_JXQY_OPERATOR));
    stc->StyleSetForeground(wxSTC_JXQY_STRING, m_cfg.GetStyleForegroundColour(wxSTC_JXQY_STRING));
    stc->StyleSetForeground(wxSTC_JXQY_GOTOPOS, m_cfg.GetStyleForegroundColour(wxSTC_JXQY_GOTOPOS));
    stc->StyleSetForeground(wxSTC_JXQY_VARIABLE, m_cfg.GetStyleForegroundColour(wxSTC_JXQY_VARIABLE));
    stc->StyleSetForeground(wxSTC_JXQY_NUMBER, m_cfg.GetStyleForegroundColour(wxSTC_JXQY_NUMBER));

	stc->StyleSetBackground(wxSTC_JXQY_COMMENT, m_cfg.GetStyleBackgroundColour(wxSTC_JXQY_COMMENT));
    stc->StyleSetBackground(wxSTC_JXQY_FUNCTION, m_cfg.GetStyleBackgroundColour(wxSTC_JXQY_FUNCTION));
    stc->StyleSetBackground(wxSTC_JXQY_OPERATOR, m_cfg.GetStyleBackgroundColour(wxSTC_JXQY_OPERATOR));
    stc->StyleSetBackground(wxSTC_JXQY_STRING, m_cfg.GetStyleBackgroundColour(wxSTC_JXQY_STRING));
    stc->StyleSetBackground(wxSTC_JXQY_GOTOPOS, m_cfg.GetStyleBackgroundColour(wxSTC_JXQY_GOTOPOS));
    stc->StyleSetBackground(wxSTC_JXQY_VARIABLE, m_cfg.GetStyleBackgroundColour(wxSTC_JXQY_VARIABLE));
    stc->StyleSetBackground(wxSTC_JXQY_NUMBER, m_cfg.GetStyleBackgroundColour(wxSTC_JXQY_NUMBER));

	//Indentation
    stc->SetTabWidth(4);
    stc->SetIndent(4);
    stc->SetUseTabs(true);
    stc->SetTabIndents (false);
    stc->SetBackSpaceUnIndents(false);
    stc->SetIndentationGuides(true);

	//Autocompletaion
    stc->AutoCompSetIgnoreCase(true);
    stc->AutoCompSetMaxWidth(50);

	//Line number
	stc->StyleSetForeground(wxSTC_STYLE_LINENUMBER, m_cfg.GetStyleForegroundColour(wxSTC_STYLE_LINENUMBER));
    stc->StyleSetBackground(wxSTC_STYLE_LINENUMBER, m_cfg.GetStyleBackgroundColour(wxSTC_STYLE_LINENUMBER));
    stc->ShowLineNumber(true);
	stc->SetMarginWidth( 2, 0 );
	stc->SetMarginWidth( 1, 5 );
	stc->SetMarginType( 0, wxSTC_MARGIN_NUMBER );
	stc->SetMarginWidth( 0, stc->TextWidth( wxSTC_STYLE_LINENUMBER, wxT("_99999") ) );
}

void JxqyScriptEditor::ResetOpenedPageStyle()
{
	size_t count = m_AuiBook->GetPageCount();
	JxqyStc *stc;
	for(size_t i = 0; i < count; i++)
	{
		stc = (JxqyStc*)m_AuiBook->GetPage(i);
		if(stc)
		{
			SetJxqyStcStyleFromSetting(stc);
		}
	}
}


