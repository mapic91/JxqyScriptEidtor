#ifndef JxqyStc_H
#define JxqyStc_H

#include "wx/stc/stc.h"

#include <map>

class JxqyScriptEditor;
typedef std::map<wxString, wxString>::iterator FunctionMapIterator;


static int CmpStringNoCase(const wxString& first, const wxString& second)
{
	return first.CmpNoCase(second);
}

class JxqyStc: public wxStyledTextCtrl
{
public:
    JxqyStc(JxqyScriptEditor *parent,
            wxWindowID id=wxID_ANY,
            const wxPoint &pos=wxDefaultPosition,
            const wxSize &size=wxDefaultSize,
            long style=0,
            const wxString &name=wxSTCNameStr);
    virtual ~JxqyStc();

//    void SetDefaultFont(wxFont font)
//    {
//        for(int i = 0; i <= wxSTC_STYLE_DEFAULT; i++)
//        {
//            StyleSetFont(i, font);
//        }
//    }
//    void SetDefaultForegroundColour(const wxColour &colour)
//    {
//        for(int i = 0; i <= wxSTC_STYLE_DEFAULT; i++)
//        {
//            StyleSetForeground(i, colour);
//        }
//    }
//    void SetDefaultBackgroundColour(const wxColour &colour)
//    {
//        for(int i = 0; i <= wxSTC_STYLE_DEFAULT; i++)
//        {
//            StyleSetBackground(i, colour);
//        }
//    }
    void SetFunctionKeyword(const wxString &words, bool sortedAndClean = false)
    {
    	if(!sortedAndClean)
		{
			wxArrayString arrStr = wxSplit(words, wxChar(' '), wxChar(NULL));
			SetFunctionKeyword(&arrStr);
		}
		else
		{
			SetKeyWords(1, words);
			m_functionKeyword = words;
		}

    }
    //Set keywors, the space in words is striped
    void SetFunctionKeyword(wxArrayString *words, bool sortedAndClean = false)
    {
    	if(!sortedAndClean)
		{
			StripBraceContensAndNonalpha(words);
			words->Sort(CmpStringNoCase);
		}
        m_functionKeyword.Clear();
        size_t counts = words->Count();
        for(size_t i = 0; i < counts; i++)
        {
            m_functionKeyword += words->Item(i);
			m_functionKeyword += wxT(" ");
        }
        SetKeyWords(1, m_functionKeyword);
    }
    void ClearFunctionKeyword()
    {
		m_functionDescribeMap.clear();
		m_functionKeyword.clear();
		SetKeyWords(1, m_functionKeyword);
    }
    void SetFunctionKeywordFromFile(const wxString &filename);

    bool OpenFromFile(const wxString &filePath);
    //if file path is not set, return false
    bool Save();
    bool SaveToFile(const wxString &filePath);
    bool FilePathEmpty(){return m_filePath.IsEmpty();}
    wxString GetFilePath(){return m_filePath;}
    wxString GetFileName();

    //Settings
    void SetShowCallTip(bool show = true){m_showCallTip = show;}
    void ShowLineNumber(bool show = true);

protected:
	void OnMouseMove(wxMouseEvent &event);
	void OnAutocompSelection(wxStyledTextEvent &event);

private:
	/*
	*  Helper function
	*/
	//( ) and contents in ( ) and nonalpha is removed
    wxString StripBraceContensAndNonalpha(const wxString &word);
    void StripBraceContensAndNonalpha(wxArrayString *words);
	wxString GetWordAtPos(int pos);
	void ShowFunctionCallTip(int pos, const wxString &word);

    void OnCharAdded(wxStyledTextEvent &event);
    wxString m_functionKeyword;
    wxString m_lastCallTipWord;
    std::map<wxString, wxString> m_functionDescribeMap;

    wxString m_filePath;

    //Settings
    bool m_showCallTip;
};

#endif // JxqyStc_H
