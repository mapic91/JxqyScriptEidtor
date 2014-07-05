#ifndef CONFIGMANAGER_H
#define CONFIGMANAGER_H
#include "wx/string.h"
#include "wx/stc/stc.h"
#include "wx/fileconf.h"
/**
* Add config:
* 1.Add class member
* 2.Add setter,getter
* 3.Add default value in constructor
* 4.Add to ReadConfig()
* 5.Add to WriteConfig()
**/
class ConfigManager
{
	public:
		ConfigManager();
		virtual ~ConfigManager();

		enum LexerType
		{
			LEX_JXQY2,
			LEX_YYCS,
			LEX_XJXQY,
			LEX_MAX
		};
		//static const wxString CONFIGNAME;
		static const wxString LEX_JXQY2_FILEPATH;
		static const wxString LEX_YYCS_FILEPATH;
		static const wxString LEX_XJXQY_FILEPATH;
//		static const unsigned int FORGROUND_INIT[wxSTC_STYLE_DEFAULT + 1];
//		static const unsigned int BACKGROUND_INIT[wxSTC_STYLE_DEFAULT + 1];
		static const wxFont FONT_INIT;
		static const LexerType LEXER_INIT;

		void ReadConfig();
		void WriteConfig();

		wxString GetLexerFilePath();
		wxFont GetDefaultFont() { return m_defaultFont; }
		void SetDefaultFont(const wxFont &font) { m_defaultFont = font; }
		wxColour GetStyleForegroundColour(unsigned int style)
		{
			wxColour col;
			if(style < wxSTC_STYLE_MAX)
			{
				if(m_isForegroundColourSetted[style])
					col.SetRGB(m_foregroundColour[style]);
				else
					col.SetRGB(m_foregroundColour[0]);
			}
			return col;
		}
		void SetStyleForegroundColour(unsigned int style, const wxColour &col)
		{
			if(style < wxSTC_STYLE_MAX)
			{
				m_foregroundColour[style] = col.GetRGB();
				m_isForegroundColourSetted[style] = true;
			}
		}
		wxColour GetStyleBackgroundColour(unsigned int style)
		{
			wxColour col;
			if(style < wxSTC_STYLE_MAX)
			{
				if(m_isBackgroundColourSetted[style])
					col.SetRGB(m_backgroundColour[style]);
				else
					col.SetRGB(m_backgroundColour[0]);
			}
			return col;
		}
		void SetStyleBackgroundColour(unsigned int style, const wxColour &col)
		{
			if(style < wxSTC_STYLE_MAX)
			{
				m_backgroundColour[style] = col.GetRGB();
				m_isBackgroundColourSetted[style] = true;
			}
		}
		void UnsetForgroundColour(unsigned int style)
		{
			if(style < wxSTC_STYLE_MAX)
			{
				m_isForegroundColourSetted[style] = false;
			}
		}
		bool IsForgroundColourSetted(unsigned int style)
		{
			if(style < wxSTC_STYLE_MAX)
			{
				return m_isForegroundColourSetted[style];
			}
			else
				return false;
		}
		void UnsetBackgroundColour(unsigned int style)
		{
			if(style < wxSTC_STYLE_MAX)
			{
				m_isBackgroundColourSetted[style] = false;
			}
		}
		bool IsBackgroundColourSetted(unsigned int style)
		{
			if(style < wxSTC_STYLE_MAX)
			{
				return m_isBackgroundColourSetted[style];
			}
			else
				return false;
		}
		void SetWordWrap(bool wrap) { m_isWordWrap = wrap; }
		bool IsWordWrap() { return m_isWordWrap; }
		void SetFunctionHelpShow(bool show) { m_isFunctionHelpShow = show; }
		bool IsFunctionHelpShow() { return m_isFunctionHelpShow; }
		void SetLexerType(LexerType type) { m_lexer = type; };
		LexerType GetLexerType() { return m_lexer; }
		void SetShowLineNumber(bool show) { m_showLineNumber = show; }
		bool IsShowLineNumber() { return m_showLineNumber; }
	protected:
	private:

		wxFileConfig *GetNewFileConfig();

		LexerType m_lexer;
		wxFont m_defaultFont;
		unsigned int m_foregroundColour[wxSTC_STYLE_MAX];
		unsigned int m_backgroundColour[wxSTC_STYLE_MAX];
		bool m_isForegroundColourSetted[wxSTC_STYLE_MAX];
		bool m_isBackgroundColourSetted[wxSTC_STYLE_MAX];

		bool m_isWordWrap;
		bool m_isFunctionHelpShow;
		bool m_showLineNumber;
};

#endif // CONFIGMANAGER_H
