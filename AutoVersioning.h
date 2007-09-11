//{Info
/*
 ** Purpose:   Code::Blocks - Auto Versioning Plugin
 ** Author:    JGM
 ** Created:   06/27/07 11:19:56 a.m.
 ** Copyright: (c) JGM
 ** License:   GPL
 */
//}

#ifndef AUTOVERSIONING_H
#define AUTOVERSIONING_H

#include <cbplugin.h>
#include "avConfigFile.h"

class avVersionEditorDlg;
class wxTimer;
class wxTimerEvent;

class AutoVersioning : public cbPlugin
{
    //Private members
    avConfigFile m_versionConfig;
    avVersionEditorDlg* m_versionEditorDialog;
    wxString m_versionConfigPath;
    wxString m_versionHeaderPath;
    wxTimer* m_timerStatus;

	public: //Constructor and Destructor
        AutoVersioning();
		~AutoVersioning();

	//Functions
        int Configure(){ return -1; }
        void BuildMenu(wxMenuBar* menuBar);
        void BuildModuleMenu(const ModuleType type, wxMenu* menu, const FileTreeData* data = 0){}
		bool BuildToolBar(wxToolBar* toolBar){return false;}
        void CreateVersionFile(bool update = false);
        void UpdateVersionFileFromDialog(); //For visibility purposes
        void UpdateVersionHeader();
        void UpdateEditorDialog();
        void CommitChanges();
        void GenerateChanges();

	//Events
		void OnAttach();
		void OnRelease(bool appShutDown);
		void OnMenuAutoVersioning(wxCommandEvent& event);
		void OnMenuCommitChanges(wxCommandEvent& event);
		void OnUpdateUI(wxUpdateUIEvent& event);
		void OnCompilerStarted(CodeBlocksEvent& event);
		void OnCompilerFinished(CodeBlocksEvent& event);
		void OnTimerVerify(wxTimerEvent& event);

        DECLARE_EVENT_TABLE()
};

#endif // AUTOVERSIONING_H

