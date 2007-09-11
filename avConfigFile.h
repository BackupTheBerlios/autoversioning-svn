//{Info
/*
 ** Purpose:   Code::Blocks - Auto Versioning Plugin
 ** Author:    JGM
 ** Created:   06/29/07 08:31:29 a.m.
 ** Copyright: (c) JGM
 ** License:   GPL
 */
//}

#ifndef AVCONFIGFILE_H
#define AVCONFIGFILE_H

#include <wx/string.h>

class wxFileConfig;

class avConfigFile{
    wxFileConfig* m_configFile;
    bool m_isOpen;

    public:
        avConfigFile():m_isOpen(false){}
        avConfigFile(const wxString& filename);
        ~avConfigFile();

        void Open(const wxString& filename);
        void Close();
        long ReadValue(const wxString& property) const;
        wxString ReadString(const wxString& property) const ;
        void WriteValue(const wxString& property, const wxString& value);
        void WriteValue(const wxString& property, long value);
};

#endif //AVCONFIGFILE_H
