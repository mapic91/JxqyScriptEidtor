#include "ConfigManager.h"
#include "helperFun.h"
#include "wx/font.h"

//#define BYTE unsigned char
//#define WORD unsigned int
//#define DWORD_PTR unsigned long
//#define LOBYTE(w) ((BYTE) (((DWORD_PTR) (w)) & 0xff))
//#define RGB(r,g,b) ((WORD)(((BYTE)(r)|((WORD)((BYTE)(g))<<8))|(((DWORD)(BYTE)(b))<<16)))
//#define GetRValue(rgb) (LOBYTE(rgb))
//#define GetGValue(rgb) (LOBYTE(((WORD)(rgb)) >> 8))
//#define GetBValue(rgb) (LOBYTE((rgb)>>16))

const wxString ConfigManager::LEX_JXQY2_FILEPATH = wxT("Function\\剑侠情缘二.txt");
const wxString ConfigManager::LEX_YYCS_FILEPATH = wxT("Function\\月影传说.txt");
const wxString ConfigManager::LEX_XJXQY_FILEPATH = wxT("Function\\新剑侠情缘.txt");
//const wxString ConfigManager::CONFIGNAME = wxT("JxqyScriptEditor");
//static const unsigned int ConfigManager::FORGROUND_INIT[wxSTC_STYLE_DEFAULT + 1] =
//{
//	0x000000, 0x000000, 0x000000, 0x000000, 0x000000,    0x000000, 0x000000, 0x000000, 0x000000, 0x000000,
//	0x000000, 0x000000, 0x000000, 0x000000, 0x000000,    0x000000, 0x000000, 0x000000, 0x000000, 0x000000,
//	0x000000, 0x000000, 0x000000, 0x000000, 0x000000,    0x000000, 0x000000, 0x000000, 0x000000, 0x000000,
//	0x000000, 0x000000, 0x000000
//}
//static const unsigned int ConfigManager::BACKGROUND_INIT[wxSTC_STYLE_DEFAULT + 1] =
//{
//	0xFFFFFF, 0xFFFFFF, 0xFFFFFF, 0xFFFFFF, 0xFFFFFF,    0xFFFFFF, 0xFFFFFF, 0xFFFFFF, 0xFFFFFF, 0xFFFFFF,
//	0xFFFFFF, 0xFFFFFF, 0xFFFFFF, 0xFFFFFF, 0xFFFFFF,    0xFFFFFF, 0xFFFFFF, 0xFFFFFF, 0xFFFFFF, 0xFFFFFF,
//	0xFFFFFF, 0xFFFFFF, 0xFFFFFF, 0xFFFFFF, 0xFFFFFF,    0xFFFFFF, 0xFFFFFF, 0xFFFFFF, 0xFFFFFF, 0xFFFFFF,
//	0xFFFFFF, 0xFFFFFF, 0xFFFFFF
//}
const wxFont ConfigManager::FONT_INIT = wxFont(12, wxMODERN, wxNORMAL, wxNORMAL);
const ConfigManager::LexerType ConfigManager::LEXER_INIT = ConfigManager::LEX_JXQY2;

#define LEX_TYPE "LEX_TYPE"
#define DEFAULT_FONT_FACENAME "DEFAULT_FONT_FACENAME"
#define DEFAULT_FONT_WEIGHT "DEFAULT_FONT_WEIGHT"
#define DEFAULT_FONT_SIZE "DEFAULT_FONT_SIZE"
#define DEFAULT_FONT_STYLE "DEFAULT_FONT_STYLE"
#define DEFAULT_FONT_UNDERLINED "DEFAULT_FONT_UNDERLINED"
#define DEFAULT_FONT_STRIKETHROUGH "DEFAULT_FONT_STRIKETHROUGH"
#define STYLE_FOREGROUNDCOLOUR "STYLE_FOREGROUNDCOLOUR"
#define STYLE_BACKGROUNDCOLOUR "STYLE_BACKGROUNDCOLOUR"
#define IS_WORD_WRAP "IS_WORD_WRAP"
#define IS_FUNCTION_HELP_SHOW "IS_FUNCTION_HELP_SHOW"

ConfigManager::ConfigManager()
{
    m_lexer = LEXER_INIT;
    m_defaultFont =  FONT_INIT;
    m_isWordWrap = true;
    m_isFunctionHelpShow = true;

    for(int i = 0 ; i < wxSTC_STYLE_MAX; i++)
    {
        m_foregroundColour[i] = 0;
        m_backgroundColour[i] = 0xFFFFFF;
    }

    ReadConfig();
}

ConfigManager::~ConfigManager()
{

}

wxString ConfigManager::GetLexerFilePath()
{
    wxString path = GetExecutableDirWithoutEndPathSeprator() + wxFileName::GetPathSeparator();
    switch(m_lexer)
    {
    case LEX_JXQY2:
        path += LEX_JXQY2_FILEPATH;
        break;
    case LEX_YYCS:
        path += LEX_YYCS_FILEPATH;
        break;
    case LEX_XJXQY:
        path += LEX_XJXQY_FILEPATH;
        break;
    default:
        path.Clear();
    }
    return path;
}
void ConfigManager::ReadConfig()
{
    wxFileConfig *cfg = GetNewFileConfig();

    wxString str_var;
    long long_var;

    cfg->Read(LEX_TYPE, (long*)&m_lexer);
    if(cfg->Read(DEFAULT_FONT_FACENAME, &str_var))
		m_defaultFont.SetFaceName(str_var);
    if(cfg->Read(DEFAULT_FONT_WEIGHT, &long_var))
		m_defaultFont.SetWeight((int)long_var);
    if(cfg->Read(DEFAULT_FONT_SIZE, &long_var))
		m_defaultFont.SetPointSize((int)long_var);
    if(cfg->Read(DEFAULT_FONT_STYLE, &long_var))
		m_defaultFont.SetStyle((int)long_var);
    if(cfg->Read(DEFAULT_FONT_UNDERLINED, &long_var))
		m_defaultFont.SetUnderlined((bool)long_var);
	if(cfg->Read(DEFAULT_FONT_STRIKETHROUGH, &long_var))
		m_defaultFont.SetStrikethrough((bool)long_var);
    //Colour
    wxString col_key;
    for(int j = 0 ; j < wxSTC_STYLE_MAX; j++)
    {
        col_key = wxString::Format(wxT("%s_%d"), STYLE_FOREGROUNDCOLOUR, j);
		m_isForegroundColourSetted[j] = cfg->Read(col_key, (int*)&m_foregroundColour[j]);
        col_key = wxString::Format(wxT("%s_%d"), STYLE_BACKGROUNDCOLOUR, j);
		m_isBackgroundColourSetted[j] = cfg->Read(col_key, (int*)&m_backgroundColour[j]);
    }

	if(cfg->Read(IS_WORD_WRAP, &long_var))
		m_isWordWrap = (bool) long_var;
	if(cfg->Read(IS_FUNCTION_HELP_SHOW, &long_var))
		m_isFunctionHelpShow = (bool) long_var;

    delete cfg;
}

void ConfigManager::WriteConfig()
{
	wxFileConfig *cfg = GetNewFileConfig();

    cfg->DeleteAll();
    //LEX_TYPE
    cfg->Write(LEX_TYPE, (long)m_lexer);
    //DEFAULT_FONT_FACENAME
    cfg->Write(DEFAULT_FONT_FACENAME, m_defaultFont.GetFaceName());
    //DEFAULT_FONT_WEIGHT
    cfg->Write(DEFAULT_FONT_WEIGHT, (long)m_defaultFont.GetWeight());
    //DEFAULT_FONT_SIZE
    cfg->Write(DEFAULT_FONT_SIZE, (long)m_defaultFont.GetPointSize());
    //DEFAULT_FONT_STYLE
    cfg->Write(DEFAULT_FONT_STYLE, (long)m_defaultFont.GetStyle());
    //DEFAULT_FONT_UNDERLINED
    cfg->Write(DEFAULT_FONT_UNDERLINED, (long)m_defaultFont.GetUnderlined());
    //DEFAULT_FONT_STRIKETHROUGH
	cfg->Write(DEFAULT_FONT_STRIKETHROUGH, (long)m_defaultFont.GetStrikethrough());
    //Colour
    wxString col_key;
    for(int j = 0 ; j < wxSTC_STYLE_MAX; j++)
    {
        col_key = wxString::Format(wxT("%s_%d"), STYLE_FOREGROUNDCOLOUR, j);
        if(m_isForegroundColourSetted[j])
			cfg->Write(col_key, (long)m_foregroundColour[j]);
        col_key = wxString::Format(wxT("%s_%d"), STYLE_BACKGROUNDCOLOUR, j);
        if(m_isBackgroundColourSetted[j])
			cfg->Write(col_key, (long)m_backgroundColour[j]);
    }

    cfg->Write(IS_WORD_WRAP, (long)m_isWordWrap);
    cfg->Write(IS_FUNCTION_HELP_SHOW, (long)m_isFunctionHelpShow);

    delete cfg;
}

wxFileConfig *ConfigManager::GetNewFileConfig()
{
	return new wxFileConfig(wxT("JxqyScriptEditor"),
                             wxT("小试刀剑"),
                             GetExecutableDirWithoutEndPathSeprator() +
                             wxFileName::GetPathSeparator() +
                             wxT("JxqyScriptEditor.ini"),
                             wxT(""),
                             wxCONFIG_USE_LOCAL_FILE);
}
