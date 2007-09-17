//{Info
/*
 ** Purpose:   Code::Blocks - Auto Versioning Plugin
 ** Author:    JGM
 ** Created:   06/29/07 02:48:59 p.m.
 ** Copyright: (c) JGM
 ** License:   GPL
 */
//}

#ifndef DLGVERSIONINTIALIZER_H
#define DLGVERSIONINTIALIZER_H

//(*Headers(avVersionEditorDlg)
#include <wx/button.h>
#include <wx/checkbox.h>
#include <wx/combobox.h>
#include <wx/dialog.h>
#include <wx/notebook.h>
#include <wx/panel.h>
#include <wx/radiobox.h>
#include <wx/sizer.h>
#include <wx/statline.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
//*)

class avVersionEditorDlg: public wxDialog
{
    long m_major;
    long m_minor;
    long m_build;
    long m_count;
    long m_revision;
    long m_autoMajorMinor;
    long m_dates;
    long m_svn;
    long m_commit;
    long m_askCommit;
    long m_minorMaximun;
    long m_buildMaximun;
    long m_revisionMaximun;
    long m_revisionRandomMaximun;
    long m_buildTimesToMinorIncrement;
    long m_changes;
    wxString m_svnDirectory;
    wxString m_status;
    wxString m_statusAbbreviation;
    wxString m_changesTitle;
    wxString m_language;

    public:
		avVersionEditorDlg(wxWindow* parent,wxWindowID id = -1);
		virtual ~avVersionEditorDlg();

		//(*Identifiers(avVersionEditorDlg)
		static const long ID_AV_NOTEBOOK;
		static const long ID_VALUES_PANEL;
		static const long ID_MAJOR_LABEL;
		static const long ID_MAJOR_TEXT;
		static const long ID_MINOR_LABEL;
		static const long ID_MINOR_TEXT;
		static const long ID_BUILD_LABEL;
		static const long ID_BUILD_TEXT;
		static const long ID_REVISION_LABEL;
		static const long ID_REVISION_TEXT;
		static const long ID_STATICLINE2;
		static const long ID_COUNT_LABEL;
		static const long ID_COUNT_TEXT;
		static const long ID_STATUS_PANEL;
		static const long ID_SATUS_LABEL;
		static const long ID_STATUS_COMBOBOX;
		static const long ID_STATICLINE4;
		static const long ID_STATICTEXT1;
		static const long ID_ABBREVIATION_COMBOBOX;
		static const long ID_SCHEME_PANEL;
		static const long ID_MINORMAXIMUN_LABEL;
		static const long ID_MINORMAXIMUN_TEXT;
		static const long ID_BUILDNUMBERMAX_LABEL;
		static const long ID_BUILDNUMBERMAX_TEXT;
		static const long ID_REVISIONMAX_LABEL;
		static const long ID_REVISIONMAX_TEXT;
		static const long ID_REVISIONRANDOM_LABEL;
		static const long ID_REVISIONRANDOM_TEXT;
		static const long ID_BUILDTIMES_LABEL;
		static const long ID_BUILDTIMES_TEXT;
		static const long ID_SETTINGS_PANEL;
		static const long ID_AUTO_CHECK;
		static const long ID_DATES_CHECK;
		static const long ID_STATICLINE3;
		static const long ID_COMMIT_CHECK;
		static const long ID_ASKCOMMIT_CHECK;
		static const long ID_HEADERLANGUAGE_RADIOBOX;
		static const long ID_STATICLINE1;
		static const long ID_SVN_CHECK;
		static const long ID_SVNDIR_TEXT;
		static const long ID_SVNDIR_BUTTON;
		static const long ID_CHANGES_PANEL;
		static const long ID_GENERATECHANGES_CHECKBOX;
		static const long ID_FORMAT_STATICTEXT;
		static const long ID_CHANGESTITLE_TEXTCTRL;
		static const long ID_FORMATS_STATICTEXT;
		static const long ID_ACCEPT;
		static const long ID_CANCEL;
		//*)

	protected:

		//(*Handlers(avVersionEditorDlg)
		void OnAcceptClick(wxCommandEvent& event);
		void OnCancelClick(wxCommandEvent& event);
		void OnSvnCheck(wxCommandEvent& event);
		void OnSvnDirectoryClick(wxCommandEvent& event);
		void OnChkCommitClick(wxCommandEvent& event);
		void OnChoStatusSelect(wxCommandEvent& event);
		void OnChoAbbreviationSelect(wxCommandEvent& event);
		void OnCmbStatusSelect(wxCommandEvent& event);
		void OnCmbAbbreviationSelect(wxCommandEvent& event);
		void OnChkChangesClick(wxCommandEvent& event);
		void OnnbAutoVersioningPageChanged(wxNotebookEvent& event);
		//*)

		//(*Declarations(avVersionEditorDlg)
		wxBoxSizer* mainSizer;
		wxNotebook* nbAutoVersioning;
		wxPanel* pnlVersionValues;
		wxBoxSizer* valuesSizer;
		wxBoxSizer* BoxSizer3;
		wxStaticText* lblMajor;
		wxTextCtrl* txtMajorVersion;
		wxBoxSizer* BoxSizer6;
		wxStaticText* lblMinor;
		wxTextCtrl* txtMinorVersion;
		wxBoxSizer* BoxSizer9;
		wxStaticText* lblBuild;
		wxTextCtrl* txtBuildNumber;
		wxBoxSizer* BoxSizer12;
		wxStaticText* lblRevision;
		wxTextCtrl* txtRevisionNumber;
		wxStaticLine* StaticLine2;
		wxBoxSizer* BoxSizer19;
		wxStaticText* lblCount;
		wxTextCtrl* txtBuildCount;
		wxPanel* pnlStatus;
		wxBoxSizer* statusSizer;
		wxStaticText* lblStatus;
		wxComboBox* cmbStatus;
		wxStaticLine* StaticLine4;
		wxStaticText* StaticText1;
		wxComboBox* cmbAbbreviation;
		wxPanel* pnlScheme;
		wxBoxSizer* schemeSizer;
		wxBoxSizer* minorMaxSizer;
		wxStaticText* lblMinorMaximum;
		wxTextCtrl* txtMinorMaximun;
		wxBoxSizer* buildNumberMaxSizer;
		wxStaticText* lblBuildNumberMaximun;
		wxTextCtrl* txtBuildNumberMaximun;
		wxBoxSizer* BoxSizer1;
		wxStaticText* lblRevisionMax;
		wxTextCtrl* txtRevisionMax;
		wxBoxSizer* BoxSizer2;
		wxStaticText* lblRevisionRandom;
		wxTextCtrl* txtRevisionRandom;
		wxStaticText* lblBuildTimes;
		wxTextCtrl* txtBuildTimes;
		wxPanel* pnlSettings;
		wxBoxSizer* settingsSizer;
		wxCheckBox* chkAutoIncrement;
		wxCheckBox* chkDates;
		wxStaticLine* StaticLine3;
		wxBoxSizer* BoxSizer5;
		wxBoxSizer* BoxSizer7;
		wxCheckBox* chkCommit;
		wxCheckBox* chkAskCommit;
		wxBoxSizer* BoxSizer8;
		wxRadioBox* rbHeaderLanguage;
		wxStaticLine* StaticLine1;
		wxCheckBox* chkSvn;
		wxBoxSizer* svnSizer;
		wxTextCtrl* txtSvnDir;
		wxButton* btnSvnDir;
		wxPanel* pnlChanges;
		wxBoxSizer* changesSizer;
		wxCheckBox* chkChanges;
		wxBoxSizer* BoxSizer4;
		wxStaticText* lblChangesTitle;
		wxTextCtrl* txtChangesTitle;
		wxStaticText* lblChangesFormats;
		wxBoxSizer* buttonsSizer;
		wxButton* btnAccept;
		wxButton* btnCancel;
		//*)

    public:
        long Major(long value = -1);
        long Minor(long value = -1);
        long Build(long value = -1);
        long Revision(long value = -1);
        long Count(long value = -1);

        long Svn(long value = 5);
        wxString SvnDirectory(wxString value = _(""));
        long Auto(long value = 5);
        long Dates(long value = 5);
        long Commit(long value = 5);
        long CommitAsk(long value = 5);
        wxString Language(wxString value = _(""));

        long MinorMaximun(long value = -1);
        long BuildMaximun(long value = -1);
        long RevisionMaximun(long value = -1);
        long RevisionRandomMaximun(long value = -1);
        long BuildTimesToMinorIncrement(long value = -1);

        wxString Status(wxString value = _(""));
        wxString StatusAbbreviation(wxString value = _(""));

        long Changes(long value = 5);
        wxString ChangesTitle(wxString value = _(""));

		DECLARE_EVENT_TABLE()
};

#endif
