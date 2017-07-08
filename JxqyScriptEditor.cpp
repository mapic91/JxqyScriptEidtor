#include "JxqyScriptEditor.h"
#include "helperFun.h"
#include "ColourSettingDialog.h"
#include "AboutDialog.h"
#include "FindDialog.h"
#include "TalkListPanel.h"

#include "wx/msgdlg.h"
#include "wx/fontdlg.h"
#include "wx/log.h"
#include "wx/app.h"

#define SAVE_ERROR_MESSAGEDIALOG wxMessageBox(wxT("保存失败！"), wxT("错误"), wxOK | wxCENTER | wxICON_ERROR)
#define VOTE_SAVE_ERROR_MESSAGEDIALOG wxMessageBox(wxT("保存失败！关闭文件？"), wxT("错误"), wxYES_NO | wxCENTER | wxICON_ERROR)

wxFileDialog* JxqyScriptEditor::GetFileSaveDialog(const wxString& defaultFileName)
{
    wxFileDialog *fileDlg = new wxFileDialog(this,
            wxT("保存文件"),
            wxEmptyString,
            defaultFileName,
            wxT("txt(*.txt)|*.txt|所有文件(*.*)|*.*"),
            wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
    return fileDlg;
}
wxFileDialog* JxqyScriptEditor::GetFileOpenDialog()
{
    wxFileDialog *fileDlg = new wxFileDialog(this,
            wxT("打开文件"),
            wxEmptyString,
            wxEmptyString,
            wxT("txt(*.txt)|*.txt|所有文件(*.*)|*.*"),
            wxFD_OPEN | wxFD_FILE_MUST_EXIST);
    return fileDlg;
}

//(*InternalHeaders(JxqyScriptEditor)
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/string.h>
//*)

//(*IdInit(JxqyScriptEditor)
const long JxqyScriptEditor::ID_AUINOTEBOOK1 = wxNewId();
const long JxqyScriptEditor::MYID_SAVEALL = wxNewId();
const long JxqyScriptEditor::MYID_CLOSE = wxNewId();
const long JxqyScriptEditor::MYID_CLOSEALL = wxNewId();
const long JxqyScriptEditor::MYID_UNDO = wxNewId();
const long JxqyScriptEditor::MYID_REDO = wxNewId();
const long JxqyScriptEditor::MYID_CUT = wxNewId();
const long JxqyScriptEditor::MYID_COPY = wxNewId();
const long JxqyScriptEditor::MYID_PASTE = wxNewId();
const long JxqyScriptEditor::MYID_DELETE = wxNewId();
const long JxqyScriptEditor::MYID_SELECTALL = wxNewId();
const long JxqyScriptEditor::MYID_FONTSETTING = wxNewId();
const long JxqyScriptEditor::MYID_COLOURSETTING = wxNewId();
const long JxqyScriptEditor::MYID_WORDWRAP = wxNewId();
const long JxqyScriptEditor::MYID_FUNHELP = wxNewId();
const long JxqyScriptEditor::MYID_SHOWLINENUMBER = wxNewId();
const long JxqyScriptEditor::MYID_JXQY2 = wxNewId();
const long JxqyScriptEditor::MYID_YYCS = wxNewId();
const long JxqyScriptEditor::MYID_XJXQY = wxNewId();
const long JxqyScriptEditor::MYID_YYCSGQ = wxNewId();
const long JxqyScriptEditor::MYID_SHOWFILEEXPLORER = wxNewId();
const long JxqyScriptEditor::MYID_SHOW_TALKLIST = wxNewId();
const long JxqyScriptEditor::TOOLBAR_MYID_SAVEALL = wxNewId();
const long JxqyScriptEditor::TOOLBAR_MYID_UNDO = wxNewId();
const long JxqyScriptEditor::TOOLBAR_MYID_REDO = wxNewId();
const long JxqyScriptEditor::TOOLBAR_MYID_CUT = wxNewId();
const long JxqyScriptEditor::TOOLBAR_MYID_COPY = wxNewId();
const long JxqyScriptEditor::TOOLBAR_MYID_PASTE = wxNewId();
const long JxqyScriptEditor::ID_TOOLBAR1 = wxNewId();
const long JxqyScriptEditor::MYID_PAGETABCLOSENOTTHIS = wxNewId();
const long JxqyScriptEditor::MYID_PAGETABCLOSEALL = wxNewId();
const long JxqyScriptEditor::MYID_SHOWINFILEEXPLORER = wxNewId();
const long JxqyScriptEditor::MYID_OPENFILEDIR = wxNewId();
//*)



BEGIN_EVENT_TABLE(JxqyScriptEditor,wxFrame)
    //(*EventTable(JxqyScriptEditor)
    //*)
    EVT_MENU(wxID_NEW, JxqyScriptEditor::OnNewFile)
    EVT_MENU(wxID_OPEN, JxqyScriptEditor::OnOpenFile)
    EVT_MENU(wxID_SAVE, JxqyScriptEditor::OnSave)
    EVT_MENU(wxID_SAVEAS, JxqyScriptEditor::OnSaveAs)
    EVT_MENU(MYID_SAVEALL, JxqyScriptEditor::OnSaveAll)
    EVT_MENU(TOOLBAR_MYID_SAVEALL, JxqyScriptEditor::OnSaveAll)
    EVT_MENU(MYID_CLOSE, JxqyScriptEditor::OnClose)
    EVT_MENU(MYID_CLOSEALL, JxqyScriptEditor::OnCloseAll)
    EVT_MENU(wxID_EXIT, JxqyScriptEditor::OnExit)
    EVT_MENU(MYID_UNDO, JxqyScriptEditor::OnEdit)
    EVT_MENU(MYID_REDO, JxqyScriptEditor::OnEdit)
    EVT_MENU(TOOLBAR_MYID_UNDO, JxqyScriptEditor::OnEdit)
    EVT_MENU(TOOLBAR_MYID_REDO, JxqyScriptEditor::OnEdit)
    EVT_MENU(MYID_CUT, JxqyScriptEditor::OnEdit)
    EVT_MENU(MYID_COPY, JxqyScriptEditor::OnEdit)
    EVT_MENU(MYID_PASTE, JxqyScriptEditor::OnEdit)
    EVT_MENU(TOOLBAR_MYID_CUT, JxqyScriptEditor::OnEdit)
    EVT_MENU(TOOLBAR_MYID_COPY, JxqyScriptEditor::OnEdit)
    EVT_MENU(TOOLBAR_MYID_PASTE, JxqyScriptEditor::OnEdit)
    EVT_MENU(MYID_DELETE, JxqyScriptEditor::OnEdit)
    EVT_MENU(MYID_SELECTALL, JxqyScriptEditor::OnEdit)
    EVT_MENU(wxID_FIND, JxqyScriptEditor::OnSearch)
    EVT_MENU(wxID_REPLACE, JxqyScriptEditor::OnSearch)
    EVT_MENU(MYID_FONTSETTING, JxqyScriptEditor::OnFontSetting)
    EVT_MENU(MYID_COLOURSETTING, JxqyScriptEditor::OnColourSetting)
    EVT_MENU(wxID_ABOUT, JxqyScriptEditor::OnAbout)
    EVT_MENU(wxID_HELP, JxqyScriptEditor::OnHelp)
    EVT_MENU(MYID_WORDWRAP, JxqyScriptEditor::OnWordWrap)
    EVT_MENU(MYID_FUNHELP, JxqyScriptEditor::OnFunctionHelpShow)
    EVT_MENU(MYID_SHOWLINENUMBER, JxqyScriptEditor::OnLineNumberShow)
    EVT_MENU(MYID_JXQY2, JxqyScriptEditor::OnFunctionFileChoose)
    EVT_MENU(MYID_YYCS, JxqyScriptEditor::OnFunctionFileChoose)
    EVT_MENU(MYID_XJXQY, JxqyScriptEditor::OnFunctionFileChoose)
    EVT_MENU(MYID_YYCSGQ, JxqyScriptEditor::OnFunctionFileChoose)
    EVT_MENU(MYID_OPENFILEDIR, JxqyScriptEditor::OnPageTabPopup)
    EVT_MENU(MYID_PAGETABCLOSENOTTHIS, JxqyScriptEditor::OnPageTabPopup)
    EVT_MENU(MYID_SHOWINFILEEXPLORER, JxqyScriptEditor::OnPageTabPopup)
    EVT_MENU(MYID_PAGETABCLOSEALL, JxqyScriptEditor::OnCloseAll)
    EVT_MENU(MYID_SHOWFILEEXPLORER, JxqyScriptEditor::OnShowFileExplorer)
    EVT_MENU(MYID_SHOW_TALKLIST, JxqyScriptEditor::OnShowTalkList)
END_EVENT_TABLE()

JxqyScriptEditor::JxqyScriptEditor(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
    //(*Initialize(JxqyScriptEditor)
    wxBoxSizer* BoxSizer1;

    Create(parent, wxID_ANY, _T("剑侠情缘脚本编辑器"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("wxID_ANY"));
    SetClientSize(wxSize(800,600));
    BoxSizer1 = new wxBoxSizer(wxHORIZONTAL);
    m_AuiBook = new wxAuiNotebook(this, ID_AUINOTEBOOK1, wxDefaultPosition, wxDefaultSize, wxAUI_NB_CLOSE_ON_ALL_TABS|wxAUI_NB_DEFAULT_STYLE);
    BoxSizer1->Add(m_AuiBook, 1, wxALL|wxEXPAND, 0);
    SetSizer(BoxSizer1);
    m_menuBar = new wxMenuBar();
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
    m_menuBar->Append(Menu1, _T("文件"));
    Menu3 = new wxMenu();
    MenuItem17 = new wxMenuItem(Menu3, MYID_UNDO, _T("撤销\tCtrl+Z"), wxEmptyString, wxITEM_NORMAL);
    Menu3->Append(MenuItem17);
    MenuItem18 = new wxMenuItem(Menu3, MYID_REDO, _T("恢复\tCtrl+Y"), wxEmptyString, wxITEM_NORMAL);
    Menu3->Append(MenuItem18);
    Menu3->AppendSeparator();
    MenuItem19 = new wxMenuItem(Menu3, MYID_CUT, _T("剪切\tCtrl+X"), wxEmptyString, wxITEM_NORMAL);
    Menu3->Append(MenuItem19);
    MenuItem20 = new wxMenuItem(Menu3, MYID_COPY, _T("复制\tCtrl+C"), wxEmptyString, wxITEM_NORMAL);
    Menu3->Append(MenuItem20);
    MenuItem21 = new wxMenuItem(Menu3, MYID_PASTE, _T("粘贴\tCtrl+V"), wxEmptyString, wxITEM_NORMAL);
    Menu3->Append(MenuItem21);
    MenuItem22 = new wxMenuItem(Menu3, MYID_DELETE, _T("删除\tDEL"), wxEmptyString, wxITEM_NORMAL);
    Menu3->Append(MenuItem22);
    MenuItem23 = new wxMenuItem(Menu3, MYID_SELECTALL, _T("全选\tCtrl+A"), wxEmptyString, wxITEM_NORMAL);
    Menu3->Append(MenuItem23);
    m_menuBar->Append(Menu3, _T("编辑"));
    Menu4 = new wxMenu();
    MenuItem24 = new wxMenuItem(Menu4, wxID_FIND, _T("查找...\tCtrl+F"), wxEmptyString, wxITEM_NORMAL);
    Menu4->Append(MenuItem24);
    MenuItem25 = new wxMenuItem(Menu4, wxID_REPLACE, _T("替换...\tCtrl+R"), wxEmptyString, wxITEM_NORMAL);
    Menu4->Append(MenuItem25);
    m_menuBar->Append(Menu4, _T("搜索"));
    Menu2 = new wxMenu();
    MenuItem9 = new wxMenuItem(Menu2, MYID_FONTSETTING, _T("字体设置..."), wxEmptyString, wxITEM_NORMAL);
    Menu2->Append(MenuItem9);
    MenuItem10 = new wxMenuItem(Menu2, MYID_COLOURSETTING, _T("颜色设置..."), wxEmptyString, wxITEM_NORMAL);
    Menu2->Append(MenuItem10);
    Menu2->AppendSeparator();
    MenuItem11 = new wxMenuItem(Menu2, MYID_WORDWRAP, _T("自动换行\tF2"), wxEmptyString, wxITEM_CHECK);
    Menu2->Append(MenuItem11);
    MenuItem12 = new wxMenuItem(Menu2, MYID_FUNHELP, _T("显示函数帮助\tF3"), wxEmptyString, wxITEM_CHECK);
    Menu2->Append(MenuItem12);
    MenuItem16 = new wxMenuItem(Menu2, MYID_SHOWLINENUMBER, _T("显示行数\tF4"), wxEmptyString, wxITEM_CHECK);
    Menu2->Append(MenuItem16);
    Menu2->AppendSeparator();
    MenuItem13 = new wxMenuItem(Menu2, MYID_JXQY2, _T("剑侠情缘二\tCtrl+1"), wxEmptyString, wxITEM_RADIO);
    Menu2->Append(MenuItem13);
    MenuItem14 = new wxMenuItem(Menu2, MYID_YYCS, _T("月影传说\tCtrl+2"), wxEmptyString, wxITEM_RADIO);
    Menu2->Append(MenuItem14);
    MenuItem15 = new wxMenuItem(Menu2, MYID_XJXQY, _T("新剑侠情缘\tCtrl+3"), wxEmptyString, wxITEM_RADIO);
    Menu2->Append(MenuItem15);
    MenuItem34 = new wxMenuItem(Menu2, MYID_YYCSGQ, _T("月影传说-高清版\tCtrl+4"), wxEmptyString, wxITEM_RADIO);
    Menu2->Append(MenuItem34);
    m_menuBar->Append(Menu2, _T("设置"));
    Menu6 = new wxMenu();
    MenuItem31 = new wxMenuItem(Menu6, MYID_SHOWFILEEXPLORER, _T("文件浏览\tCtrl+E"), wxEmptyString, wxITEM_NORMAL);
    Menu6->Append(MenuItem31);
    MenuItem33 = new wxMenuItem(Menu6, MYID_SHOW_TALKLIST, _T("对话列表\tCtrl+T"), wxEmptyString, wxITEM_NORMAL);
    Menu6->Append(MenuItem33);
    m_menuBar->Append(Menu6, _T("窗口"));
    Menu5 = new wxMenu();
    MenuItem30 = new wxMenuItem(Menu5, wxID_HELP, _T("帮助\tF1"), wxEmptyString, wxITEM_NORMAL);
    Menu5->Append(MenuItem30);
    MenuItem26 = new wxMenuItem(Menu5, wxID_ABOUT, _T("关于"), wxEmptyString, wxITEM_NORMAL);
    Menu5->Append(MenuItem26);
    m_menuBar->Append(Menu5, _T("帮助"));
    SetMenuBar(m_menuBar);
    m_toolBar = new wxToolBar(this, ID_TOOLBAR1, wxDefaultPosition, wxDefaultSize, wxTB_HORIZONTAL|wxNO_BORDER, _T("ID_TOOLBAR1"));
    ToolBarItem1 = m_toolBar->AddTool(wxID_NEW, _T("新建文档"), wxBITMAP_PNG(NEW), wxNullBitmap, wxITEM_NORMAL, _T("新建文档"), wxEmptyString);
    ToolBarItem2 = m_toolBar->AddTool(wxID_OPEN, _T("打开"), wxBITMAP_PNG(OPEN), wxNullBitmap, wxITEM_NORMAL, _T("打开文档"), wxEmptyString);
    ToolBarItem3 = m_toolBar->AddTool(wxID_SAVE, _T("保存"), wxBITMAP_PNG(SAVE), wxNullBitmap, wxITEM_NORMAL, _T("保存"), wxEmptyString);
    ToolBarItem4 = m_toolBar->AddTool(wxID_SAVEAS, _T("另存为"), wxBITMAP_PNG(SAVEAS), wxNullBitmap, wxITEM_NORMAL, _T("另存为"), wxEmptyString);
    ToolBarItem5 = m_toolBar->AddTool(TOOLBAR_MYID_SAVEALL, _T("保存所有"), wxBITMAP_PNG(SAVEALL), wxNullBitmap, wxITEM_NORMAL, _T("保存所有"), wxEmptyString);
    m_toolBar->AddSeparator();
    ToolBarItem7 = m_toolBar->AddTool(TOOLBAR_MYID_UNDO, _T("撤销"), wxBITMAP_PNG(UNDO), wxNullBitmap, wxITEM_NORMAL, _T("撤销"), wxEmptyString);
    ToolBarItem6 = m_toolBar->AddTool(TOOLBAR_MYID_REDO, _T("恢复"), wxBITMAP_PNG(REDO), wxNullBitmap, wxITEM_NORMAL, _T("恢复"), wxEmptyString);
    m_toolBar->AddSeparator();
    ToolBarItem8 = m_toolBar->AddTool(TOOLBAR_MYID_CUT, _T("剪切"), wxBITMAP_PNG(CUT), wxNullBitmap, wxITEM_NORMAL, _T("剪切"), wxEmptyString);
    ToolBarItem9 = m_toolBar->AddTool(TOOLBAR_MYID_COPY, _T("复制"), wxBITMAP_PNG(COPY), wxNullBitmap, wxITEM_NORMAL, _T("复制"), wxEmptyString);
    ToolBarItem10 = m_toolBar->AddTool(TOOLBAR_MYID_PASTE, _T("粘贴"), wxBITMAP_PNG(PASTE), wxNullBitmap, wxITEM_NORMAL, _T("粘贴"), wxEmptyString);
    m_toolBar->AddSeparator();
    ToolBarItem11 = m_toolBar->AddTool(wxID_FIND, _T("查找"), wxBITMAP_PNG(FIND), wxNullBitmap, wxITEM_NORMAL, _T("查找"), wxEmptyString);
    ToolBarItem12 = m_toolBar->AddTool(wxID_REPLACE, _T("替换"), wxBITMAP_PNG(REPLACE), wxNullBitmap, wxITEM_NORMAL, _T("替换"), wxEmptyString);
    m_toolBar->Realize();
    SetToolBar(m_toolBar);
    MenuItem29 = new wxMenuItem((&m_menuPageTabPopup), MYID_PAGETABCLOSENOTTHIS, _T("关闭非当前文件"), wxEmptyString, wxITEM_NORMAL);
    m_menuPageTabPopup.Append(MenuItem29);
    MenuItem28 = new wxMenuItem((&m_menuPageTabPopup), MYID_PAGETABCLOSEALL, _T("关闭所有"), wxEmptyString, wxITEM_NORMAL);
    m_menuPageTabPopup.Append(MenuItem28);
    m_menuPageTabPopup.AppendSeparator();
    MenuItem32 = new wxMenuItem((&m_menuPageTabPopup), MYID_SHOWINFILEEXPLORER, _T("在文件浏览窗口显示"), wxEmptyString, wxITEM_NORMAL);
    m_menuPageTabPopup.Append(MenuItem32);
    MenuItem27 = new wxMenuItem((&m_menuPageTabPopup), MYID_OPENFILEDIR, _T("打开文件所在文件夹"), wxEmptyString, wxITEM_NORMAL);
    m_menuPageTabPopup.Append(MenuItem27);
    SetSizer(BoxSizer1);
    Layout();
    Center();

    Connect(ID_AUINOTEBOOK1,wxEVT_COMMAND_AUINOTEBOOK_PAGE_CLOSED,(wxObjectEventFunction)&JxqyScriptEditor::OnPageClosed);
    Connect(ID_AUINOTEBOOK1,wxEVT_COMMAND_AUINOTEBOOK_PAGE_CHANGED,(wxObjectEventFunction)&JxqyScriptEditor::OnPageChanged);
    Connect(ID_AUINOTEBOOK1,wxEVT_COMMAND_AUINOTEBOOK_PAGE_CHANGING,(wxObjectEventFunction)&JxqyScriptEditor::Onm_AuiBookPageChanging);
    Connect(ID_AUINOTEBOOK1,wxEVT_COMMAND_AUINOTEBOOK_TAB_RIGHT_DOWN,(wxObjectEventFunction)&JxqyScriptEditor::OBookTabRightDown);
    Connect(wxID_ANY,wxEVT_CLOSE_WINDOW,(wxObjectEventFunction)&JxqyScriptEditor::OnFrameClose);
    //*)

    Init();

    MyFileDrop *drop = new MyFileDrop(this);
    SetDropTarget(drop);

    m_find = new FindDialog(this);

    m_menuBar->Check(MYID_WORDWRAP, m_cfg.IsWordWrap());
    m_menuBar->Check(MYID_FUNHELP, m_cfg.IsFunctionHelpShow());
    m_menuBar->Check(MYID_SHOWLINENUMBER, m_cfg.IsShowLineNumber());
    switch(m_cfg.GetLexerType())
    {
    case ConfigManager::LEX_JXQY2:
        m_menuBar->Check(MYID_JXQY2, true);
        break;
    case ConfigManager::LEX_YYCS:
        m_menuBar->Check(MYID_YYCS, true);
        break;
    case ConfigManager::LEX_XJXQY:
        m_menuBar->Check(MYID_XJXQY, true);
        break;
	case ConfigManager::LEX_YYCSGQ:
		m_menuBar->Check(MYID_YYCSGQ, true);
		break;
    default:
        break;
    }

    m_fileExplorer = NULL;
    m_talkList = NULL;

    SetIcon(wxICON(aaaa));
    Center();
    Raise();
}

JxqyScriptEditor::~JxqyScriptEditor()
{
    //(*Destroy(JxqyScriptEditor)
    //*)
    if(m_fileExplorer) delete m_fileExplorer;
    if(m_talkList) delete m_talkList;
    Uninit();
}
void JxqyScriptEditor::Init()
{
    SetMenuAndPageState();

    m_AuiBook->Bind(wxEVT_AUINOTEBOOK_PAGE_CLOSE, &JxqyScriptEditor::OnPageClose, this);
    this->Bind(wxEVT_ACTIVATE, &JxqyScriptEditor::OnActivate, this);
}

void JxqyScriptEditor::Uninit()
{
    m_AuiBook->Unbind(wxEVT_AUINOTEBOOK_PAGE_CLOSE, &JxqyScriptEditor::OnPageClose, this);
    this->Unbind(wxEVT_ACTIVATE, &JxqyScriptEditor::OnActivate, this);
}


void JxqyScriptEditor::OnNewFile(wxCommandEvent& event)
{
    AddNewFile();
}

void JxqyScriptEditor::OnOpenFile(wxCommandEvent& event)
{
    wxFileDialog *fileDlg = GetFileOpenDialog();

    if(fileDlg->ShowModal() == wxID_OK)
    {
        OpenFile(fileDlg->GetPath());
    }
    delete fileDlg;
}

void JxqyScriptEditor::OnSave(wxCommandEvent& event)
{
    SavePageToFile();
}

void JxqyScriptEditor::OnSaveAs(wxCommandEvent& event)
{
    wxFileDialog *fileDlg = GetFileSaveDialog(GetPageTiltleClean());
    if(fileDlg->ShowModal() == wxID_OK)
    {
        SavePageToFile(-1, fileDlg->GetPath());
    }
    delete fileDlg;
}

void JxqyScriptEditor::OnSaveAll(wxCommandEvent& event)
{
    size_t counts = m_AuiBook->GetPageCount();
    int cur_sel = m_AuiBook->GetSelection();
    JxqyStc *stc;
    for(size_t i = 0; i < counts; i++)
    {
        stc = (JxqyStc*) m_AuiBook->GetPage(i);
        if(stc)
        {
            if(stc->GetModify() || stc->FilePathEmpty())
            {
                if(stc->FilePathEmpty())
                    m_AuiBook->SetSelection(i);
                SavePageToFile((int)i);
            }
        }
    }
    m_AuiBook->SetSelection(cur_sel);
}

void JxqyScriptEditor::OnClose(wxCommandEvent& event)
{
    ClosePage();
}

void JxqyScriptEditor::OnCloseAll(wxCommandEvent& event)
{
    CloseAllPage();
}

void JxqyScriptEditor::OnExit(wxCommandEvent& event)
{
    this->Close();
}
void JxqyScriptEditor::OnEdit(wxCommandEvent& event)
{
    int id = event.GetId();
    JxqyStc *stc = GetCurrentStc();
    if(stc)
    {
        if(id == MYID_UNDO || id == TOOLBAR_MYID_UNDO)
            stc->Undo();
        else if(id == MYID_REDO || id == TOOLBAR_MYID_REDO)
            stc->Redo();
        else if(id == MYID_CUT || id == TOOLBAR_MYID_CUT)
            stc->Cut();
        else if(id == MYID_COPY || id == TOOLBAR_MYID_COPY)
            stc->Copy();
        else if(id == MYID_PASTE || id == TOOLBAR_MYID_PASTE)
            stc->Paste();
        else if(id == MYID_DELETE)
            stc->Clear();
        else if(id == MYID_SELECTALL)
            stc->SelectAll();
    }

}
void JxqyScriptEditor::OnSearch(wxCommandEvent& event)
{
    int id = event.GetId();
    JxqyStc *stc = GetCurrentStc();
    if(stc)
    {
        if(stc->HasSelection())
            m_find->SetFindText(stc->GetSelectedText());
    }

    if(id == wxID_FIND)
    {
        m_find->SetPage(0);
    }
    else if(id == wxID_REPLACE)
    {
        m_find->SetPage(1);
    }

    m_find->Show();
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
void JxqyScriptEditor::OnHelp(wxCommandEvent& event)
{
    wxMessageBox(wxT("设置：可以设置字体、颜色、哪个游戏等。\n\n函数提示文件在Function文件夹下，可以自行修改。\n"),
                 wxT("帮助"));
}

void JxqyScriptEditor::OnAbout(wxCommandEvent& event)
{
    AboutDialog dlg(this);
    dlg.ShowModal();
}

void JxqyScriptEditor::OnPageTabPopup(wxCommandEvent& event)
{
    int id = event.GetId();
    JxqyStc *stc = GetCurrentStc();
    wxString filePath = wxT("");
    if(stc)
    {
        filePath = stc->GetFilePath();
    }
    if(id == MYID_OPENFILEDIR)
    {
        if(wxFileName::FileExists(filePath))
        {
            wxString cmd = wxT("explorer /select,\"") + filePath + wxT("\"");
            wxExecute(cmd);
        }
    }
    else if(id == MYID_PAGETABCLOSENOTTHIS)
    {
        CloseAllPage(m_AuiBook->GetSelection());
    }
    else if(id == MYID_SHOWINFILEEXPLORER)
    {
		if(wxFileName::FileExists(filePath))
		{
			GetFileExplorerPanel()->Show();
			GetFileExplorerPanel()->ExpandPath(filePath);
		}
    }
}

void JxqyScriptEditor::TalkToSay()
{
	JxqyStc *stc = GetCurrentStc();
	if(stc)
	{
		wxArrayString lines;
		int count = stc->GetLineCount();

		stc->BeginUndoAction();
        stc->ClearAll();
        for(int i = 0; i < count; i++)
		{
			wxString linetoAdd = stc->GetLine(i);
			std::string line = std::string(stc->GetLine(i).char_str());
			size_t pos = line.find("Talk");
			while(pos != std::string::npos)
			{
				int textPos = stc->PositionFromLine(i);
				textPos += pos;
				if(stc->GetStyleAt(textPos) == wxSTC_JXQY_FUNCTION)
				{
                    linetoAdd = wxString(line.substr(0, pos).c_str());
                    //Go on.......
				}
				pos = line.find("Talk", pos+1);
			}
			lines.Add(linetoAdd);
		}
		stc->EndUndoAction();
	}
}

void JxqyScriptEditor::OnWordWrap(wxCommandEvent& event)
{
    if(m_cfg.IsWordWrap())
    {
        m_cfg.SetWordWrap(false);
    }
    else
    {
        m_cfg.SetWordWrap(true);
    }
    m_cfg.WriteConfig();
    ResetOpenedPageStyle();
}
void JxqyScriptEditor::OnLineNumberShow(wxCommandEvent& event)
{
    if(m_cfg.IsShowLineNumber())
    {
        m_cfg.SetShowLineNumber(false);
    }
    else
    {
        m_cfg.SetShowLineNumber(true);
    }
    m_cfg.WriteConfig();
    ResetOpenedPageStyle();
}
void JxqyScriptEditor::OnFunctionHelpShow(wxCommandEvent& event)
{
    if(m_cfg.IsFunctionHelpShow())
    {
        m_cfg.SetFunctionHelpShow(false);
    }
    else
    {
        m_cfg.SetFunctionHelpShow(true);
    }
    m_cfg.WriteConfig();
    ResetOpenedPageStyle();
}

void JxqyScriptEditor::OnPageClose(wxAuiNotebookEvent& event)
{
    int pageIdx = event.GetSelection();
    JxqyStc *stc = (JxqyStc*)m_AuiBook->GetPage(pageIdx);
    if(stc)
    {
        if(stc->GetModify())
        {
            bool veto = false;
            wxString title = GetPageTiltleClean(pageIdx);
            wxString msg = wxT("保存文件 \"") + title + wxT("\" ?");
            int ret = wxMessageBox(msg, wxT("保存"), wxCANCEL | wxYES_NO | wxICON_QUESTION |wxCENTER);
            if(ret == wxYES)
            {
                SavePageToFile(pageIdx, wxEmptyString, title, &veto);
                if(veto) event.Veto();
            }
            else if(ret == wxCANCEL)
                event.Veto();
        }
    }
}
void JxqyScriptEditor::OnActivate(wxActivateEvent& event)
{
    if(!event.GetActive())
    {
        JxqyStc *stc = GetCurrentStc();
        if(stc)
        {
            stc->AutoCompCancel();
        }
    }
}
void JxqyScriptEditor::AddNewFile()
{
    JxqyStc *stc = GetInitlizedJxqyStc();
    m_AuiBook->AddPage(stc, wxT("未命名"), true);
    m_AuiBook->SetPageToolTip(m_AuiBook->GetPageIndex(stc), wxT("未命名"));
}


JxqyStc* JxqyScriptEditor::GetInitlizedJxqyStc()
{
    JxqyStc *stc = new JxqyStc(this);
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
    if(m_cfg.IsShowLineNumber())
    {
        stc->StyleSetForeground(wxSTC_STYLE_LINENUMBER, m_cfg.GetStyleForegroundColour(wxSTC_STYLE_LINENUMBER));
        stc->StyleSetBackground(wxSTC_STYLE_LINENUMBER, m_cfg.GetStyleBackgroundColour(wxSTC_STYLE_LINENUMBER));
        stc->ShowLineNumber(true);
        stc->SetMarginWidth( 2, 0 );
        stc->SetMarginWidth( 1, 5 );
        stc->SetMarginType( 0, wxSTC_MARGIN_NUMBER );
        stc->SetMarginWidth( 0, stc->TextWidth( wxSTC_STYLE_LINENUMBER, wxT("_9999") ) );
    }
    else
    {
        stc->SetMarginWidth( 0, 0 );
        stc->SetMarginWidth( 1, 0 );
        stc->SetMarginWidth( 2, 0 );
    }

    //Wordwrap
    if(m_cfg.IsWordWrap())
        stc->SetWrapMode(wxSTC_WRAP_WORD);
    else
        stc->SetWrapMode(wxSTC_WRAP_NONE);

    //FunctionHelpShow
    stc->SetShowCallTip(m_cfg.IsFunctionHelpShow());
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
void JxqyScriptEditor::OnFunctionFileChoose(wxCommandEvent& event)
{
    int id = event.GetId();
    if(id == MYID_JXQY2)
        m_cfg.SetLexerType(ConfigManager::LEX_JXQY2);
    else if(id == MYID_YYCS)
        m_cfg.SetLexerType(ConfigManager::LEX_YYCS);
    else if(id == MYID_XJXQY)
        m_cfg.SetLexerType(ConfigManager::LEX_XJXQY);
	else if(id == MYID_YYCSGQ)
		m_cfg.SetLexerType(ConfigManager::LEX_YYCSGQ);
    m_cfg.WriteConfig();
    ResetOpenedPageStyle();
}

void JxqyScriptEditor::OnShowFileExplorer(wxCommandEvent& event)
{
    GetFileExplorerPanel()->Show(true);
}

void JxqyScriptEditor::OnShowTalkList(wxCommandEvent& event)
{
	GetTalkListPanel()->Show(true);
}

int JxqyScriptEditor::GetOpenedFile(const wxString& path)
{
    size_t count = m_AuiBook->GetPageCount();
    JxqyStc *stc;
    for(size_t i = 0; i < count; i++)
    {
        stc = (JxqyStc*)m_AuiBook->GetPage(i);
        if(stc)
        {
            if(stc->GetFilePath() == path)
                return i;
        }
    }
    return -1;
}
void JxqyScriptEditor::SetPageChanged(bool changed, int idx)
{
    if(idx == -1)
        idx = m_AuiBook->GetSelection();
    wxString title = m_AuiBook->GetPageText(idx);
    if(!title.IsEmpty())
    {
        if(changed && title[0] != wxChar('*'))
        {
            title = wxT("*") + title;
            m_AuiBook->SetPageText(idx, title);
        }
        else if(!changed && title[0] == wxChar('*'))
        {
            title = title.Mid(1);
            m_AuiBook->SetPageText(idx, title);
        }
    }
}
bool JxqyScriptEditor::SavePageToFile(int idx, const wxString& path, const wxString &defaultFileName, bool *veto)
{
    wxLogNull lognull;
    if(m_AuiBook->GetPageCount() == 0) return false;

    if(idx == -1)
        idx = m_AuiBook->GetSelection();
    if(idx == -1) return false;

    if(veto) *veto = false;

    int ret;
    bool successed = true, cancled = false;
    wxString filename = defaultFileName.IsEmpty() ?  GetPageTiltleClean(idx) : defaultFileName;
    JxqyStc *stc = (JxqyStc*)m_AuiBook->GetPage(idx);
    if(stc)
    {
        if(stc->FilePathEmpty() && path.IsEmpty())
        {
            wxFileDialog *fileDlg = GetFileSaveDialog(filename);

            if(fileDlg->ShowModal() == wxID_OK)
            {
                if(!stc->SaveToFile(fileDlg->GetPath()))
                {
                    successed = false;
                }
            }
            else
            {
                successed = false;
                cancled = true;
            }
            delete fileDlg;
        }
        else if(!stc->FilePathEmpty() && path.IsEmpty())
        {
            if(!stc->Save())
            {
                successed = false;
            }
        }
        else if(!path.IsEmpty())
        {
            if(!stc->SaveToFile(path))
            {
                successed = false;
            }
        }
    }
    else
        successed = false;

    if(successed == false)
    {
        if(veto)
        {
            if(cancled)
            {
                *veto = true;
            }
            else
            {
                ret = VOTE_SAVE_ERROR_MESSAGEDIALOG;
                if(ret == wxNO) *veto = true;
            }
        }
        else
        {
            if(!cancled)SAVE_ERROR_MESSAGEDIALOG;
        }
    }
    else
    {
        ResetPageTitleTooltip(idx);
    }

    return successed;
}

wxString JxqyScriptEditor::GetPageTiltleClean(int idx)
{
    if(idx == -1) idx = m_AuiBook->GetSelection();
    wxString title = m_AuiBook->GetPageText(idx);
    if(!title.IsEmpty() && title[0] == wxChar('*') )
    {
        title = title.Mid(1);
    }
    return title;
}
void JxqyScriptEditor::ResetPageTitleTooltip(int idx)
{
    if(idx == -1) idx = m_AuiBook->GetSelection();
    JxqyStc *stc = (JxqyStc*)m_AuiBook->GetPage(idx);
    if(stc)
    {
        m_AuiBook->SetPageText(idx, stc->GetFileName());
        m_AuiBook->SetPageToolTip(idx, stc->GetFilePath());
    }
}
bool JxqyScriptEditor::ClosePage(int idx, bool deletePage)
{
    if(idx == -1) idx = m_AuiBook->GetSelection();
    wxAuiNotebookEvent auievent;
    auievent.SetSelection(idx);
    auievent.SetEventType(wxEVT_AUINOTEBOOK_PAGE_CLOSE);
    //auievent.SetEventObject(this);
    m_AuiBook->GetEventHandler()->ProcessEvent(auievent);
    if(auievent.IsAllowed())
    {
        if(deletePage)m_AuiBook->DeletePage(idx);
        return true;
    }
    else
        return false;
}
bool JxqyScriptEditor::CloseAllPage(size_t keep)
{
    size_t count = m_AuiBook->GetPageCount();
    JxqyStc *stc[count];
    for(size_t i = 0; i < count; i++)
    {
        stc[i] = NULL;
        if(i != keep)
        {
            stc[i] = (JxqyStc*)m_AuiBook->GetPage(i);
            if(stc[i])
            {
                m_AuiBook->SetSelection(i);
                if(!ClosePage(i, false)) return false;
            }
        }
    }
    for(size_t i = 0; i < count; i++)
    {
        m_AuiBook->DeletePage(m_AuiBook->GetPageIndex(stc[i]));
    }
    SetMenuAndPageState();
    return true;
}


void JxqyScriptEditor::OnFrameClose(wxCloseEvent& event)
{
    if(CloseAllPage()) this->Destroy();
}
void JxqyScriptEditor::OnStcChange(wxStyledTextEvent& event)
{
    int idx = m_AuiBook->GetPageIndex((wxWindow*)event.GetEventObject());
    JxqyStc *stc = (JxqyStc*)m_AuiBook->GetPage(idx);
    if(stc)
    {
        SetMenuAndPageState(stc);
    }
    event.Skip();
}
JxqyStc *JxqyScriptEditor::GetCurrentStc()
{
    return (JxqyStc*)( m_AuiBook->GetPage(m_AuiBook->GetSelection()) );
}
void JxqyScriptEditor::SetMenuAndPageState(JxqyStc* stc)
{
    if(stc == NULL)stc = (JxqyStc *)m_AuiBook->GetPage(m_AuiBook->GetSelection());
    int idx = m_AuiBook->GetPageIndex(stc);
    if(stc)
    {
        if(stc->IsModified())
            SetPageChanged(true, idx);
        else
            SetPageChanged(false, idx);
    }

    size_t num = m_AuiBook->GetPageCount();
    bool existUnmodifed = false;
    JxqyStc *tmpstc;
    for(size_t i = 0; i < num; i++)
    {
        tmpstc = (JxqyStc *)m_AuiBook->GetPage(i);
        if(tmpstc)
        {
            if(tmpstc->IsModified())
            {
                existUnmodifed = true;
                break;
            }
        }
    }

    m_menuBar->Enable(wxID_SAVE, stc ? stc->IsModified() : false);
    m_menuBar->Enable(wxID_SAVEAS, (bool)stc);
    m_menuBar->Enable(MYID_SAVEALL, existUnmodifed);
    m_menuBar->Enable(MYID_CLOSE, (bool)num);
    m_menuBar->Enable(MYID_CLOSEALL, (bool)num);
    m_toolBar->EnableTool(wxID_SAVE, stc ? stc->IsModified() : false);
    m_toolBar->EnableTool(wxID_SAVEAS, (bool)stc);
    m_toolBar->EnableTool(TOOLBAR_MYID_SAVEALL, existUnmodifed);

    m_menuBar->Enable(MYID_UNDO, stc ? stc->CanUndo() : false);
    m_menuBar->Enable(MYID_REDO, stc ? stc->CanRedo() : false);
    m_menuBar->Enable(MYID_CUT, stc ? stc->HasSelection() : false);
    m_menuBar->Enable(MYID_COPY, stc ? stc->HasSelection() : false);
    m_menuBar->Enable(MYID_PASTE, stc ? stc->CanPaste() : false);
    m_menuBar->Enable(MYID_DELETE, stc ? stc->HasSelection() : false);
    m_menuBar->Enable(MYID_SELECTALL, (bool)stc);
    m_toolBar->EnableTool(TOOLBAR_MYID_UNDO, stc ? stc->CanUndo() : false);
    m_toolBar->EnableTool(TOOLBAR_MYID_REDO, stc ? stc->CanRedo() : false);
    m_toolBar->EnableTool(TOOLBAR_MYID_CUT, stc ? stc->HasSelection() : false);
    m_toolBar->EnableTool(TOOLBAR_MYID_COPY, stc ? stc->HasSelection() : false);
    m_toolBar->EnableTool(TOOLBAR_MYID_PASTE, stc ? stc->CanPaste() : false);
}

void JxqyScriptEditor::OnPageClosed(wxAuiNotebookEvent& event)
{
    SetMenuAndPageState();
}

void JxqyScriptEditor::OnPageChanged(wxAuiNotebookEvent& event)
{
    SetMenuAndPageState();
}

bool JxqyScriptEditor::OpenFile(const wxString& path)
{
    int openedIdx = GetOpenedFile(path);
    if(openedIdx != -1)
    {
        m_AuiBook->SetSelection(openedIdx);
    }
    else
    {
        JxqyStc *stc = GetInitlizedJxqyStc();
        if(!stc->OpenFromFile(path))
        {
            wxMessageBox(wxT("文件打开失败！"), wxT("错误"), wxOK|wxCENTER|wxICON_ERROR);
            delete stc;
            return false;
        }
        m_AuiBook->AddPage(stc, stc->GetFileName(), true);
        m_AuiBook->SetPageToolTip(m_AuiBook->GetPageIndex(stc), stc->GetFilePath());
    }
    return true;
}
bool MyFileDrop::OnDropFiles(wxCoord x, wxCoord y, const wxArrayString& filenames)
{
    if(mainfram == NULL) return false;

    for(size_t i = 0; i < filenames.Count(); i++)
    {
        mainfram->OpenFile(filenames[i]);
    }
    return true;
}

void JxqyScriptEditor::OBookTabRightDown(wxAuiNotebookEvent& event)
{
    m_AuiBook->SetSelection(event.GetSelection());
    PopupMenu(&m_menuPageTabPopup);
}

void JxqyScriptEditor::Onm_AuiBookPageChanging(wxAuiNotebookEvent& event)
{
    JxqyStc *stc = GetCurrentStc();
    if(stc)
    {
        stc->CallTipCancel();
    }
}

void FileExplorerPanel::OnFilterChange(wxCommandEvent& event)
{
    switch(event.GetSelection())
    {
    case -1:
    case 0:
        m_genericDirCtrl1->SetFilterIndex(0);
        break;
    default:
        m_genericDirCtrl1->SetFilterIndex(event.GetSelection());
        break;
    }
    wxString path = m_genericDirCtrl1->GetPath();
    m_genericDirCtrl1->ReCreateTree();
    m_genericDirCtrl1->ExpandPath(path);
}

void FileExplorerPanel::OnTreeItemActivated(wxTreeEvent& event)
{
    event.Skip();
    wxString path = m_genericDirCtrl1->GetPath();
    if(wxFileName::FileExists(path))
    {
        m_parent->OpenFile(path);
    }
}

FileExplorerPanel* JxqyScriptEditor::GetFileExplorerPanel()
{
	if(!m_fileExplorer)
	{
		m_fileExplorer = new FileExplorerPanel(this);
	}
	return m_fileExplorer;
}

TalkListPanel* JxqyScriptEditor::GetTalkListPanel()
{
	if(!m_talkList)
	{
		m_talkList = new TalkListPanel(this);
	}
	return m_talkList;
}
