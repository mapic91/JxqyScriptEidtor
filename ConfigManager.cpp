#include "ConfigManager.h"
#include "helperFun.h"

#include "wx/config.h"

const wxString ConfigManager::LEX_JXQY2_FILEPATH = wxT("Function\\剑侠情缘2.txt");
const wxString ConfigManager::LEX_YYCS_FILEPATH = wxT("Function\\月影传说.txt");
const wxString ConfigManager::LEX_XJXQY_FILEPATH = wxT("Function\\新剑侠情缘.txt");
const wxString ConfigManager::CONFIGNAME = wxT("JxqyScriptEditor");

#define LEX_TYPE "LexType"

ConfigManager::ConfigManager()
{
	m_lexer = LEX_JXQY2;

	wxConfig cfg(CONFIGNAME);
	long lexType;
	if(cfg.Read(LEX_TYPE, &lexType))
	{
		if(lexType > LEX_BEGIN && lexType < LEX_END)
		m_lexer = (LexerType)lexType;
	}

	cfg.Write(LEX_TYPE, (long)m_lexer);
}

ConfigManager::~ConfigManager()
{
	//dtor
}

wxString ConfigManager::GetLexerFilePath()
{
	wxString path = GetExecutableDirWithoutEndPathSeprator() + wxT("\\");
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
