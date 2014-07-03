#ifndef CONFIGMANAGER_H
#define CONFIGMANAGER_H
#include "wx/string.h"

class ConfigManager
{
	public:
		ConfigManager();
		virtual ~ConfigManager();

		wxString GetLexerFilePath();

		enum LexerType
		{
			LEX_BEGIN,
			LEX_JXQY2,
			LEX_YYCS,
			LEX_XJXQY,
			LEX_END
		};
		static const wxString CONFIGNAME;
		static const wxString LEX_JXQY2_FILEPATH;
		static const wxString LEX_YYCS_FILEPATH;
		static const wxString LEX_XJXQY_FILEPATH;

	protected:
	private:

		LexerType m_lexer;
};

#endif // CONFIGMANAGER_H
