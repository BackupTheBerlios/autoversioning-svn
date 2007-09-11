#include "avStrCon.h"

using std::string;

string ws2s(wxString value){
    return string((value).mb_str(wxConvLibc));
}

wxString s2ws(string value){
    return wxString((value).c_str(),wxConvLibc);
}
