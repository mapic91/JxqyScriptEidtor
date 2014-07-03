#include "wx/stdpaths.h"
#include "wx/filename.h"
#include "helperFun.h"

wxString GetExecutableDirWithoutEndPathSeprator()
{
	static wxString dir;
	if(dir.IsEmpty())
	{
		wxFileName fileName(wxStandardPaths::Get().GetExecutablePath());
		dir = fileName.GetPath();
		if(dir[dir.Length() - 1] == wxFileName::GetPathSeparator())
			dir = dir.Mid(0, dir.Length() - 1);
	}
	return dir;
}
