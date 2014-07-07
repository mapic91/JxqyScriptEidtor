#include "FindDialog.h"
#include "JxqyScriptEditor.h"
#include "JxqyStc.h"
#include "wx/msgdlg.h"
//(*InternalHeaders(FindDialog)
#include <wx/string.h>
//*)

//(*IdInit(FindDialog)
const long FindDialog::ID_STATICTEXT1 = wxNewId();
const long FindDialog::ID_TEXTCTRL1 = wxNewId();
const long FindDialog::ID_BUTTON1 = wxNewId();
const long FindDialog::ID_PANEL1 = wxNewId();
const long FindDialog::ID_STATICTEXT2 = wxNewId();
const long FindDialog::ID_STATICTEXT3 = wxNewId();
const long FindDialog::ID_TEXTCTRL2 = wxNewId();
const long FindDialog::ID_TEXTCTRL3 = wxNewId();
const long FindDialog::ID_BUTTON3 = wxNewId();
const long FindDialog::ID_BUTTON4 = wxNewId();
const long FindDialog::ID_BUTTON5 = wxNewId();
const long FindDialog::ID_PANEL2 = wxNewId();
const long FindDialog::ID_NOTEBOOK1 = wxNewId();
const long FindDialog::ID_CHECKBOX1 = wxNewId();
const long FindDialog::ID_CHECKBOX2 = wxNewId();
const long FindDialog::ID_STATICBOX1 = wxNewId();
const long FindDialog::ID_RADIOBUTTON1 = wxNewId();
const long FindDialog::ID_RADIOBUTTON2 = wxNewId();
const long FindDialog::ID_BUTTON2 = wxNewId();
//*)

BEGIN_EVENT_TABLE(FindDialog,wxDialog)
    //(*EventTable(FindDialog)
    //*)
END_EVENT_TABLE()

FindDialog::FindDialog(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
    //(*Initialize(FindDialog)
    Create(parent, wxID_ANY, _T("查找"), wxDefaultPosition, wxDefaultSize, wxSTAY_ON_TOP|wxDEFAULT_DIALOG_STYLE, _T("wxID_ANY"));
    SetClientSize(wxSize(371,262));
    m_noteBook = new wxNotebook(this, ID_NOTEBOOK1, wxPoint(5,10), wxSize(363,174), 0, _T("ID_NOTEBOOK1"));
    m_panelFind = new wxPanel(m_noteBook, ID_PANEL1, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL1"));
    StaticText1 = new wxStaticText(m_panelFind, ID_STATICTEXT1, _T("查找目标："), wxPoint(16,16), wxDefaultSize, 0, _T("ID_STATICTEXT1"));
    m_textCtrl_Target = new wxTextCtrl(m_panelFind, ID_TEXTCTRL1, wxEmptyString, wxPoint(16,48), wxSize(238,21), 0, wxDefaultValidator, _T("ID_TEXTCTRL1"));
    m_button_Next = new wxButton(m_panelFind, ID_BUTTON1, _T("查找下一个"), wxPoint(264,48), wxSize(82,23), 0, wxDefaultValidator, _T("ID_BUTTON1"));
    m_panel_Replace = new wxPanel(m_noteBook, ID_PANEL2, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL2"));
    StaticText2 = new wxStaticText(m_panel_Replace, ID_STATICTEXT2, _T("查找目标："), wxPoint(16,16), wxDefaultSize, 0, _T("ID_STATICTEXT2"));
    StaticText3 = new wxStaticText(m_panel_Replace, ID_STATICTEXT3, _T("替换为："), wxPoint(16,80), wxDefaultSize, 0, _T("ID_STATICTEXT3"));
    m_textCtrl_Replace_Target = new wxTextCtrl(m_panel_Replace, ID_TEXTCTRL2, wxEmptyString, wxPoint(16,48), wxSize(238,21), 0, wxDefaultValidator, _T("ID_TEXTCTRL2"));
    m_textCtrl_Replace_Replace = new wxTextCtrl(m_panel_Replace, ID_TEXTCTRL3, wxEmptyString, wxPoint(16,112), wxSize(238,21), 0, wxDefaultValidator, _T("ID_TEXTCTRL3"));
    m_button_Replace_Next = new wxButton(m_panel_Replace, ID_BUTTON3, _T("查找下一个"), wxPoint(264,48), wxSize(82,23), 0, wxDefaultValidator, _T("ID_BUTTON3"));
    m_button_Replace_Replace = new wxButton(m_panel_Replace, ID_BUTTON4, _T("替换"), wxPoint(264,80), wxSize(82,23), 0, wxDefaultValidator, _T("ID_BUTTON4"));
    m_button_Replace_All = new wxButton(m_panel_Replace, ID_BUTTON5, _T("替换所有"), wxPoint(264,112), wxSize(82,23), 0, wxDefaultValidator, _T("ID_BUTTON5"));
    m_noteBook->AddPage(m_panelFind, _T("查找"), false);
    m_noteBook->AddPage(m_panel_Replace, _T("替换"), false);
    m_checkBox_MatchCase = new wxCheckBox(this, ID_CHECKBOX1, _T("匹配大小写"), wxPoint(10,200), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX1"));
    m_checkBox_MatchCase->SetValue(false);
    m_checkBox_Wraparound = new wxCheckBox(this, ID_CHECKBOX2, _T("循环查找"), wxPoint(10,230), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX2"));
    m_checkBox_Wraparound->SetValue(true);
    StaticBox1 = new wxStaticBox(this, ID_STATICBOX1, _T("方向"), wxPoint(110,200), wxSize(152,56), 0, _T("ID_STATICBOX1"));
    m_radioButton_Up = new wxRadioButton(this, ID_RADIOBUTTON1, _T("向上"), wxPoint(128,224), wxDefaultSize, 0, wxDefaultValidator, _T("ID_RADIOBUTTON1"));
    m_radioButton_Down = new wxRadioButton(this, ID_RADIOBUTTON2, _T("向下"), wxPoint(200,224), wxDefaultSize, 0, wxDefaultValidator, _T("ID_RADIOBUTTON2"));
    m_radioButton_Down->SetValue(true);
    m_button_Cancle = new wxButton(this, ID_BUTTON2, _T("关闭"), wxPoint(274,230), wxSize(82,23), 0, wxDefaultValidator, _T("ID_BUTTON2"));

    Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&FindDialog::Onm_button_NextClick);
    Connect(ID_BUTTON3,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&FindDialog::Onm_button_Replace_NextClick);
    Connect(ID_BUTTON4,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&FindDialog::Onm_button_Replace_ReplaceClick);
    Connect(ID_BUTTON5,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&FindDialog::Onm_button_Replace_AllClick);
    Connect(ID_NOTEBOOK1,wxEVT_COMMAND_NOTEBOOK_PAGE_CHANGED,(wxObjectEventFunction)&FindDialog::Onm_noteBookPageChanged);
    Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&FindDialog::Onm_button_CancleClick);
    //*)

    m_edit = (JxqyScriptEditor*) parent;
    m_replaceBegin = true;

    this->Bind(wxEVT_ACTIVATE, &FindDialog::OnActivate, this);
}

FindDialog::~FindDialog()
{
    this->Unbind(wxEVT_ACTIVATE, &FindDialog::OnActivate, this);
    //(*Destroy(FindDialog)
    //*)
}


void FindDialog::Onm_button_NextClick(wxCommandEvent& event)
{
    wxString findText = m_textCtrl_Target->GetValue();

    if(findText.IsEmpty()) return;
    bool finded = DoFind(findText, true);

    if(!finded) wxMessageBox(wxT("未找到"));
}
void FindDialog::Onm_button_Replace_NextClick(wxCommandEvent& event)
{
	wxString findText = m_textCtrl_Replace_Target->GetValue();

    if(findText.IsEmpty()) return;
    bool finded = DoFind(findText, true);

    if(!finded) wxMessageBox(wxT("未找到"));
}
void FindDialog::Onm_button_Replace_ReplaceClick(wxCommandEvent& event)
{
    wxString findText = m_textCtrl_Replace_Target->GetValue();
    if(findText.IsEmpty()) return;

	bool finded = DoReplace(findText, true);

    if(!finded) wxMessageBox(wxT("未找到"));
}
bool FindDialog::DoReplace(const wxString& findVal, bool toPos)
{
	if(findVal.IsEmpty()) return false;

	wxString findText = findVal;
	bool isNoCase = !(m_checkBox_MatchCase->GetValue());
    bool finded = false;
    bool isDown = m_radioButton_Down->GetValue();
    if(m_stc)
    {
        if(!m_replaceBegin)
        {
            wxString selectText = m_stc->GetSelectedText();
            if(isNoCase)
            {
                findText.MakeLower();
                selectText.MakeLower();
            }

            if(findText.Cmp(selectText) == 0)
            {
                int selStart = m_stc->GetSelectionStart();
                int lineNum = m_stc->LineFromPosition(selStart);
                int lineStartPos = m_stc->PositionFromLine(lineNum);
                wxString replaceText = m_textCtrl_Replace_Replace->GetValue();

                m_lineNumber = lineNum;
                if(isDown)
				{
					m_lineFindBegin = selStart - lineStartPos + replaceText.Length();
				}
                else
				{
					m_lineFindBegin = (selStart - lineStartPos) ? (selStart - lineStartPos - 1) : 0;
				}
                m_stc->ReplaceSelection(replaceText);
            }
        }
        finded = DoFind(m_textCtrl_Replace_Target->GetValue(), toPos);
        m_replaceBegin = false;
    }
    return finded;
}

void FindDialog::Onm_button_Replace_AllClick(wxCommandEvent& event)
{
	wxString findText = m_textCtrl_Replace_Target->GetValue();
    if(findText.IsEmpty()) return;
    if(m_stc)
	{
		m_stc->BeginUndoAction();
        int counts = 0;
        while(DoReplace(findText, false))
            counts++;
		m_stc->EndUndoAction();
        wxMessageBox(wxString::Format(wxT("%d 个被替换"), counts));
	}

}
void FindDialog::Onm_button_CancleClick(wxCommandEvent& event)
{
    this->Show(false);
}

void FindDialog::OnActivate(wxActivateEvent &event)
{
    if(event.GetActive())
    {
        if(m_edit)
        {
            m_stc = m_edit->GetCurrentStc();
            if(m_stc)
            {
                m_lineNumber = m_stc->GetCurrentLine();
                m_lineFindBegin = m_stc->GetCurrentPos() - m_stc->PositionFromLine(m_lineNumber);
                if(m_radioButton_Up->GetValue() && m_lineFindBegin > 0) m_lineFindBegin--;
            }
        }
    }
    m_replaceBegin = true;
}
bool FindDialog::BeginFind(const wxString& findVal, bool toPos)
{
    if(findVal.IsEmpty() || !m_stc) return false;

    bool isDown = m_radioButton_Down->GetValue();
    bool isNoCase = !(m_checkBox_MatchCase->GetValue());
    bool finded = false;
    size_t pos;
    int lineCount = m_stc->GetLineCount();
    wxString line;
    wxString findText = findVal;
    if(isNoCase) findText.MakeLower();
    for(;
            isDown ? m_lineNumber <= lineCount : m_lineNumber >= 0;
            isDown ? m_lineNumber++ : m_lineNumber--)
    {
        line = m_stc->GetLine(m_lineNumber);
        if(line.IsEmpty()) continue;
        if(isNoCase) line.MakeLower();

        if(isDown) pos = line.find(findText, m_lineFindBegin);
        else pos = line.rfind(findText, m_lineFindBegin);

        if(pos != wxString::npos)
        {
            finded = true;
            int lineBegPos = m_stc->PositionFromLine(m_lineNumber);
            //if(toPos)m_stc->GotoPos(lineBegPos + pos);
            m_stc->SetSelection(lineBegPos + pos, lineBegPos + pos + findText.Length());

            if(isDown)
            {
                if( (pos + findText.Length()) == line.Length() )
                {
                    m_lineNumber = m_lineNumber + 1;
                    m_lineFindBegin = 0;
                }
                else
                {
                    m_lineNumber = m_lineNumber;
                    m_lineFindBegin = pos + findText.Length();
                }
            }
            else
            {
                if(pos == 0)
                {
                    m_lineNumber = m_lineNumber - 1;
                    m_lineFindBegin = wxString::npos;
                }
                else
                {
                    m_lineNumber = m_lineNumber;
                    m_lineFindBegin = pos - 1;
                }
            }
            break;
        }
        else
        {
            if(isDown)
            {
                m_lineFindBegin = 0;
            }
            else
            {
                m_lineFindBegin = wxString::npos;
            }
        }
    }

    return finded;
}
bool FindDialog::DoFind(const wxString& findVal, bool toPos)
{
    bool finded = false;
    if(m_stc)
    {
        finded = BeginFind(findVal, toPos);
        if(!finded && m_checkBox_Wraparound->GetValue())
        {
            if(m_radioButton_Down->GetValue())
            {
                m_lineNumber = 0;
                m_lineFindBegin = 0;
            }
            else
            {
                m_lineNumber = m_stc->GetLineCount();
                m_lineFindBegin = wxString::npos;
            }
            finded = BeginFind(findVal, toPos);
        }
    }
    return finded;
}

void FindDialog::Onm_noteBookPageChanged(wxNotebookEvent& event)
{
    switch(event.GetSelection())
    {
    case 0:
        this->SetTitle(wxT("查找"));
        break;
    case 1:
        this->SetTitle(wxT("替换"));
        m_replaceBegin = true;
        break;
    default:
        break;
    }
}
