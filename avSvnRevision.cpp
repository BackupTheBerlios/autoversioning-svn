#include "avSvnRevision.h"
#include <wx/intl.h>
#include <wx/utils.h>
#include <wx/string.h>
#include <wx/arrstr.h>
#include <tinyxml/tinyxml.h>

#include "avStrCon.h"

bool QuerySvn(const wxString& workingDir, wxString& revision, wxString& date)
{
    revision = _("0");
    date = _("unknown date");
    wxString svncmd = _("svn info --xml --non-interactive ");
    svncmd.Append(_("\"") + workingDir + _("\""));
    wxArrayString xmlOutput;

    if (wxExecute(svncmd, xmlOutput) != -1)
    {

        wxString buf = _("");

        for(unsigned int i=0; i<xmlOutput.GetCount(); ++i){
            buf << xmlOutput[i];
        }

        TiXmlDocument doc;
        doc.Parse(ws2s(buf).c_str());

        if (doc.Error())
            return 0;

        TiXmlHandle hCommit(&doc);
        hCommit = hCommit.FirstChildElement("info").FirstChildElement("entry").FirstChildElement("commit");
		if(const TiXmlElement* e = hCommit.ToElement())
        {
            revision = e->Attribute("revision") ? s2ws(e->Attribute("revision")) : wxT("");
            const TiXmlElement* d = e->FirstChildElement("date");
            if(d && d->GetText())
                date = s2ws(d->GetText());

            return 1;
        }
    }
    return 0;
}
