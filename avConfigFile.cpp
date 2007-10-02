#include <wx/fileconf.h>
#include "avConfigFile.h"

avConfigFile::avConfigFile(const wxString& filename){
    m_configFile = new wxFileConfig(_T("AutoVersioning"), _T("Code::Blocks"), filename);
    m_isOpen = true;
}

avConfigFile::~avConfigFile(){
    if(m_isOpen){
    	Close();
    }
}

void avConfigFile::Open(const wxString& filename){
    if(m_isOpen == true)
        Close();

    m_configFile = new wxFileConfig(_T("AutoVersioning"), _T("Code::Blocks"), filename);
    m_isOpen = true;
}

void avConfigFile::Close(){
    delete m_configFile;
    m_configFile = 0;
    m_isOpen = false;
}

long avConfigFile::ReadValue(const wxString& property) const {
    long value = 0;
    m_configFile->Read(property, &value);
    return value;
}

wxString avConfigFile::ReadString(const wxString& property) const {
    wxString value;
    m_configFile->Read(property, &value);
    return value;
}

void avConfigFile::WriteValue(const wxString& property, const wxString& value){
    m_configFile->Write(property, value);
}

void avConfigFile::WriteValue(const wxString& property, long value){
    m_configFile->Write(property, value);
}

