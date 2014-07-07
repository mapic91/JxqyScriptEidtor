#include "JxqyStc.h"
#include "wx/textfile.h"
#include "wx/file.h"
#include "wx/msgdlg.h"
#include "wx/filename.h"
#include "JxqyScriptEditor.h"

JxqyStc::JxqyStc(JxqyScriptEditor *parent,
                 wxWindowID id,
                 const wxPoint &pos,
                 const wxSize &size,
                 long style,
                 const wxString &name)
    :wxStyledTextCtrl(parent, id, pos, size, style, name)
{
    SetLexer(wxSTC_LEX_JXQY);
//    wxFont font(12, wxMODERN, wxNORMAL, wxNORMAL);
//    SetDefaultFont(font);
//    SetDefaultBackgroundColour(wxColour(192, 255, 185));
//    StyleSetBackground(wxSTC_STYLE_DEFAULT, wxColour(192, 255, 185));
//    StyleSetForeground(wxSTC_JXQY_COMMENT, wxColour(160, 160, 160));
//    //StyleSetForeground(wxSTC_JXQY_KEYWORD, wxColour(0, 255, 0));
//    StyleSetForeground(wxSTC_JXQY_FUNCTION, wxColour(255, 128, 0));
//    StyleSetForeground(wxSTC_JXQY_OPERATOR, wxColour(255, 0, 0));
//    StyleSetForeground(wxSTC_JXQY_STRING, wxColour(0, 0, 255));
//    StyleSetForeground(wxSTC_JXQY_GOTOPOS, wxColour(201,84,218));
//    StyleSetForeground(wxSTC_JXQY_VARIABLE, wxColour(50,167,120));
//    StyleSetForeground(wxSTC_JXQY_NUMBER, wxColour(255,128,255));
//    SetTabWidth(4);
//    SetIndent(4);
//    SetUseTabs(true);
//    SetTabIndents (false);
//    SetBackSpaceUnIndents(false);
//    SetIndentationGuides(true);
//SetCodePage(65001);
    //Settings
    m_showCallTip = true;
    m_autoCompSelected = false;
    this->Bind(wxEVT_STC_CHARADDED, &JxqyStc::OnCharAdded, this);
    this->Bind(wxEVT_MOTION, &JxqyStc::OnMouseMove, this);
    this->Bind(wxEVT_STC_AUTOCOMP_SELECTION, &JxqyStc::OnAutocompSelection, this);
    this->Bind(wxEVT_STC_CHANGE, &JxqyStc::OnStcChange, this);
    this->Bind(wxEVT_STC_UPDATEUI, &JxqyScriptEditor::OnStcChange, (JxqyScriptEditor*)GetParent());
}

JxqyStc::~JxqyStc()
{
    this->Unbind(wxEVT_STC_CHARADDED, &JxqyStc::OnCharAdded, this);
    this->Unbind(wxEVT_MOTION, &JxqyStc::OnMouseMove, this);
    this->Unbind(wxEVT_STC_AUTOCOMP_SELECTION, &JxqyStc::OnAutocompSelection, this);
   // this->Unbind(wxEVT_STC_CHANGE, &JxqyStc::OnStcChange, this);
    this->Unbind(wxEVT_STC_UPDATEUI, &JxqyScriptEditor::OnStcChange, (JxqyScriptEditor*)GetParent());
    //wxMessageBox(wxT("JxqyStc destructed"));
}

void JxqyStc::OnCharAdded(wxStyledTextEvent &event)
{
    //Auto indent
    char chr = (char)event.GetKey();
    int currentLine = GetCurrentLine();
    if (chr == '\n' || chr == '\r')
    {
        int lineInd = 0;
        if (currentLine > 0)
        {
            lineInd = GetLineIndentation(currentLine - 1);
        }
        if (lineInd != 0)
        {
            SetLineIndentation (currentLine, lineInd);
            GotoPos(PositionFromLine (currentLine) + lineInd);
        }
    }

    //Auto complete
    int curline =  GetCurrentLine();
    int startPos = PositionFromLine(curline);
    int curPos = GetCurrentPos();
    int lineLenBefCaret = curPos - startPos;
    wxString lineStr = GetCurLine();
    lineStr = lineStr.Mid(0, lineLenBefCaret);
    lineStr.Trim(false);

    int lineLen = lineStr.length(), hintLen = 0;
    while(hintLen < lineLen)
        if(wxIsalpha(lineStr[lineLen - hintLen - 1]))
            hintLen++;
        else
            break;
    if(hintLen > 0)
    {
    	m_autoCompSearchLength = hintLen;

        wxString compList, tmpStr;
        wxString findStr = lineStr.Mid(lineLen - hintLen);
        size_t len = m_functionKeyword.Length();
        size_t findEnd;
        for(size_t findBeg = 0; findBeg < len;)
        {
            findEnd = m_functionKeyword.find(wxChar(' '), findBeg);
            tmpStr = m_functionKeyword.Mid(findBeg, findEnd - findBeg);
            if(tmpStr.Length() >= findStr.Length() &&
                    !findStr.CmpNoCase(tmpStr.Mid(0, findStr.Length())))
            {
                compList += (tmpStr + wxT(" "));
            }
            findBeg = findEnd + 1;
        }

        if(!AutoCompActive() && !compList.IsEmpty())
            AutoCompShow(hintLen, compList);
    }
}
void JxqyStc::OnStcChange(wxStyledTextEvent& event)
{
	if(m_showCallTip && m_autoCompSelected)
	{
		m_autoCompSelected = false;
		wxString descrip = FindFunctionCallTip(m_lastCallTipWord);
		if(!descrip.IsEmpty())
		{
			ShowFunctionCallTip(GetCurrentPos(),descrip);
		}
	}
}

void JxqyStc::SetFunctionKeywordFromFile(const wxString &filename)
{
    ClearFunctionKeyword();

    wxTextFile file;
    if(!file.Open(filename, wxConvLibc)) return;

    wxArrayString words;
    wxString line,trimLine, word, descrip;

    bool blockBegin = true;
    for(line = file.GetFirstLine(); !file.Eof(); line = file.GetNextLine())
    {
        trimLine = line;
        trimLine.Trim(true);
        trimLine.Trim(false);
        if(blockBegin)
        {
            if(!trimLine.IsEmpty())
            {
                word = line;
                word = StripBraceContensAndNonalpha(word);
                words.Add(word);
                descrip += (line + wxT("\n"));
                blockBegin = false;
            }
        }
        else
        {
            if(trimLine.IsEmpty())
            {
                descrip = descrip.Mid(0, descrip.Length() - 1);//remove end newline
                m_functionDescribeMap[word] += //+= for overloaded function
                    ( m_functionDescribeMap[word].IsEmpty() ?
                      descrip :
                      (wxT("\n\n") + descrip) //add newline to seperate with old contents
                    );
                word.Clear();
                descrip.Clear();
                blockBegin = true;
            }
            else
            {
                descrip += (line + wxT("\n"));
            }
        }
    }
    //handle last line
    trimLine = line;
    trimLine.Trim(true);
    trimLine.Trim(false);
    if(blockBegin)
    {
        if(!trimLine.IsEmpty())
        {
            word = line;
            word = StripBraceContensAndNonalpha(word);
            words.Add(word);
            m_functionDescribeMap[word];
        }
    }
    else
    {
        if(!trimLine.IsEmpty())descrip += line;
        m_functionDescribeMap[word] += //+= for overloaded function
            ( m_functionDescribeMap[word].IsEmpty() ?
              descrip :
              (wxT("\n\n") + descrip) //add newline to seperate with old contents
            );
    }
    file.Close();

    SetFunctionKeyword(&words);
}

void JxqyStc::OnMouseMove(wxMouseEvent &event)
{
    event.Skip();

    if(m_showCallTip)
    {
        wxPoint pt = event.GetPosition();
        int pos = PositionFromPointClose(pt.x, pt.y);
        //get alphabet word at pos
        int style = GetStyleAt(pos);
        wxString word = GetWordAtPos(pos);
        if(style == wxSTC_JXQY_FUNCTION &&
                !word.IsEmpty()
          )
        {
            if(word != m_lastCallTipWord || !CallTipActive())
            {
            	m_lastCallTipWord = word;
                wxString descip = FindFunctionCallTip(word);
                if(!descip.IsEmpty())
                {
                    ShowFunctionCallTip(pos, descip);
                }
            }
        }
        else
            CallTipCancel();
    }
}
void JxqyStc::OnAutocompSelection(wxStyledTextEvent& event)
{
    m_lastCallTipWord = event.GetText();
    m_autoCompSelected = true;
    m_autoCompBeginPos = event.GetPosition();
}

wxString JxqyStc::StripBraceContensAndNonalpha(const wxString& word)
{
    bool begBrace = false;
    bool endBrace = true;
    size_t len = word.Length();
    wxString stripedWord;
    //strip (xxx)
    for(size_t j = 0; j < len; j++)
    {
        if(begBrace && word[j] == wxChar(')'))
        {
            endBrace = true;
            begBrace = false;
        }
        if(endBrace)
            stripedWord += word[j];
        if(endBrace && word[j] == wxChar('('))
        {
            begBrace = true;
            endBrace = false;
        }
    }
    wxString strip;
    len = stripedWord.Length();
    //strip nonalpha
    for(size_t i = 0; i < len; i++)
    {
        if(wxIsalpha(stripedWord[i]))
            strip += stripedWord[i];
    }
    return strip;
}
void JxqyStc::StripBraceContensAndNonalpha(wxArrayString *words)
{
    size_t count = words->Count();
    for(size_t i = 0; i < count; i++)
    {
        words->Item(i) = StripBraceContensAndNonalpha(words->Item(i));
    }
}

wxString JxqyStc::GetWordAtPos(int pos)
{
    wxString word;
    if(pos != wxSTC_INVALID_POSITION)
    {
        int start,end;
        start = end = pos;
        //get alphabet word at pos
        if(wxIsalpha(GetCharAt(pos)))
        {
            start--;
            end++;
            while(wxIsalpha(GetCharAt(start)))
                start--;
            while(wxIsalpha(GetCharAt(end)))
                end++;
            start++;
            word = GetTextRange(start, end);
        }
    }
    return word;
}
wxString JxqyStc::FindFunctionCallTip(const wxString& keyword)
{
    FunctionMapIterator it = m_functionDescribeMap.find(keyword);
    if(it != m_functionDescribeMap.end())
    {
        return it->second;
    }
    else
        return wxEmptyString;
}
void JxqyStc::ShowFunctionCallTip(int pos, const wxString& word)
{
    CallTipCancel();//Cancel calltip otherwise calltip window won't work properly
    CallTipShow(pos, word);
}
void JxqyStc::ShowLineNumber(bool show)
{
    if(show)
    {
        SetMarginWidth( 2, 0 );
        SetMarginWidth( 1, 5 );
        SetMarginType( 0, wxSTC_MARGIN_NUMBER );
        SetMarginWidth( 0, TextWidth( wxSTC_STYLE_LINENUMBER, wxT("99999") ) );
    }
    else
    {
        SetMarginWidth(0, 0);
        SetMarginWidth(1, 0);
        SetMarginWidth(2, 0);
    }
}
bool JxqyStc::OpenFromFile(const wxString& filePath)
{
	wxFile file(filePath);
    if(file.IsOpened())
    {
    	size_t length = (size_t) file.Length();
    	char *buf = new char[length + 1];
    	file.Read((void*)buf, length);
    	buf[length] = 0;
    	wxString text(buf);
    	SetText(text);
    	EmptyUndoBuffer();
        m_filePath = filePath;
        return true;
    }
    else
        return false;
}

bool JxqyStc::Save()
{
    if(m_filePath.IsEmpty()) return false;
    return SaveFile(m_filePath);
}

bool JxqyStc::SaveToFile(const wxString& filePath)
{
    if(SaveFile(filePath))
    {
        m_filePath = filePath;
        return true;
    }
    else
        return false;
}

wxString JxqyStc::GetFileName()
{
    wxFileName fn(m_filePath);
    return fn.GetFullName();
}
