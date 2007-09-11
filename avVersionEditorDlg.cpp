#include "avVersionEditorDlg.h"

//(*InternalHeaders(avVersionEditorDlg)
#include <wx/bitmap.h>
#include <wx/font.h>
#include <wx/fontenum.h>
#include <wx/fontmap.h>
#include <wx/image.h>
#include <wx/intl.h>
#include <wx/settings.h>
#include <wx/string.h>
//*)

#include <wx/dirdlg.h>

//{ID's

//(*IdInit(avVersionEditorDlg)
const long avVersionEditorDlg::ID_AV_NOTEBOOK = wxNewId();
const long avVersionEditorDlg::ID_VALUES_PANEL = wxNewId();
const long avVersionEditorDlg::ID_MAJOR_LABEL = wxNewId();
const long avVersionEditorDlg::ID_MAJOR_TEXT = wxNewId();
const long avVersionEditorDlg::ID_MINOR_LABEL = wxNewId();
const long avVersionEditorDlg::ID_MINOR_TEXT = wxNewId();
const long avVersionEditorDlg::ID_BUILD_LABEL = wxNewId();
const long avVersionEditorDlg::ID_BUILD_TEXT = wxNewId();
const long avVersionEditorDlg::ID_REVISION_LABEL = wxNewId();
const long avVersionEditorDlg::ID_REVISION_TEXT = wxNewId();
const long avVersionEditorDlg::ID_STATICLINE2 = wxNewId();
const long avVersionEditorDlg::ID_COUNT_LABEL = wxNewId();
const long avVersionEditorDlg::ID_COUNT_TEXT = wxNewId();
const long avVersionEditorDlg::ID_STATUS_PANEL = wxNewId();
const long avVersionEditorDlg::ID_SATUS_LABEL = wxNewId();
const long avVersionEditorDlg::ID_STATUS_COMBOBOX = wxNewId();
const long avVersionEditorDlg::ID_STATICLINE4 = wxNewId();
const long avVersionEditorDlg::ID_STATICTEXT1 = wxNewId();
const long avVersionEditorDlg::ID_ABBREVIATION_COMBOBOX = wxNewId();
const long avVersionEditorDlg::ID_SCHEME_PANEL = wxNewId();
const long avVersionEditorDlg::ID_MINORMAXIMUN_LABEL = wxNewId();
const long avVersionEditorDlg::ID_MINORMAXIMUN_TEXT = wxNewId();
const long avVersionEditorDlg::ID_BUILDNUMBERMAX_LABEL = wxNewId();
const long avVersionEditorDlg::ID_BUILDNUMBERMAX_TEXT = wxNewId();
const long avVersionEditorDlg::ID_REVISIONMAX_LABEL = wxNewId();
const long avVersionEditorDlg::ID_REVISIONMAX_TEXT = wxNewId();
const long avVersionEditorDlg::ID_REVISIONRANDOM_LABEL = wxNewId();
const long avVersionEditorDlg::ID_REVISIONRANDOM_TEXT = wxNewId();
const long avVersionEditorDlg::ID_BUILDTIMES_LABEL = wxNewId();
const long avVersionEditorDlg::ID_BUILDTIMES_TEXT = wxNewId();
const long avVersionEditorDlg::ID_SETTINGS_PANEL = wxNewId();
const long avVersionEditorDlg::ID_AUTO_CHECK = wxNewId();
const long avVersionEditorDlg::ID_DATES_CHECK = wxNewId();
const long avVersionEditorDlg::ID_STATICLINE3 = wxNewId();
const long avVersionEditorDlg::ID_COMMIT_CHECK = wxNewId();
const long avVersionEditorDlg::ID_ASKCOMMIT_CHECK = wxNewId();
const long avVersionEditorDlg::ID_STATICLINE1 = wxNewId();
const long avVersionEditorDlg::ID_SVN_CHECK = wxNewId();
const long avVersionEditorDlg::ID_SVNDIR_TEXT = wxNewId();
const long avVersionEditorDlg::ID_SVNDIR_BUTTON = wxNewId();
const long avVersionEditorDlg::ID_CHANGES_PANEL = wxNewId();
const long avVersionEditorDlg::ID_GENERATECHANGES_CHECKBOX = wxNewId();
const long avVersionEditorDlg::ID_FORMAT_STATICTEXT = wxNewId();
const long avVersionEditorDlg::ID_CHANGESTITLE_TEXTCTRL = wxNewId();
const long avVersionEditorDlg::ID_FORMATS_STATICTEXT = wxNewId();
const long avVersionEditorDlg::ID_ACCEPT = wxNewId();
const long avVersionEditorDlg::ID_CANCEL = wxNewId();
//*)

//}

//{Events
BEGIN_EVENT_TABLE(avVersionEditorDlg,wxDialog)
	//(*EventTable(avVersionEditorDlg)
	//*)
END_EVENT_TABLE()
//}

//{Constructor and Destructor
avVersionEditorDlg::avVersionEditorDlg(wxWindow* parent,wxWindowID id)
{
	//(*Initialize(avVersionEditorDlg)
	Create(parent, wxID_ANY, _("Auto Versioning Editor"), wxDefaultPosition, wxDefaultSize, wxSTAY_ON_TOP|wxCAPTION, _T("wxID_ANY"));
	SetClientSize(wxSize(394,330));
	wxFont thisFont(10,wxDEFAULT,wxFONTSTYLE_NORMAL,wxNORMAL,false,wxEmptyString,wxFONTENCODING_DEFAULT);
	SetFont(thisFont);
	mainSizer = new wxBoxSizer(wxVERTICAL);
	nbAutoVersioning = new wxNotebook(this, ID_AV_NOTEBOOK, wxDefaultPosition, wxSize(396,274), 0, _T("ID_AV_NOTEBOOK"));
	pnlVersionValues = new wxPanel(nbAutoVersioning, ID_VALUES_PANEL, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_VALUES_PANEL"));
	valuesSizer = new wxBoxSizer(wxVERTICAL);
	BoxSizer3 = new wxBoxSizer(wxHORIZONTAL);
	lblMajor = new wxStaticText(pnlVersionValues, ID_MAJOR_LABEL, _("Major Version"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_MAJOR_LABEL"));
	BoxSizer3->Add(lblMajor, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	txtMajorVersion = new wxTextCtrl(pnlVersionValues, ID_MAJOR_TEXT, _("1"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_MAJOR_TEXT"));
	txtMajorVersion->SetToolTip(_("Increments by 1 when the \nminor version reaches its\nmaximun value."));
	BoxSizer3->Add(txtMajorVersion, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	valuesSizer->Add(BoxSizer3, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
	BoxSizer6 = new wxBoxSizer(wxHORIZONTAL);
	lblMinor = new wxStaticText(pnlVersionValues, ID_MINOR_LABEL, _("Minor Version"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_MINOR_LABEL"));
	BoxSizer6->Add(lblMinor, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	txtMinorVersion = new wxTextCtrl(pnlVersionValues, ID_MINOR_TEXT, _("0"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_MINOR_TEXT"));
	txtMinorVersion->SetToolTip(_("Increments by one everytime \nthat the build number pass the\nbarrier of build times. The value \nis reset to 0 when it reaches its\nmaximun value."));
	BoxSizer6->Add(txtMinorVersion, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	valuesSizer->Add(BoxSizer6, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
	BoxSizer9 = new wxBoxSizer(wxHORIZONTAL);
	lblBuild = new wxStaticText(pnlVersionValues, ID_BUILD_LABEL, _("Build Number"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_BUILD_LABEL"));
	BoxSizer9->Add(lblBuild, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	txtBuildNumber = new wxTextCtrl(pnlVersionValues, ID_BUILD_TEXT, _("0"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUILD_TEXT"));
	txtBuildNumber->SetToolTip(_("Increments by 1 everytime \nthat the revision number is\nincremented.\n\nEquivalent to \"Release\" on\nunix systems."));
	BoxSizer9->Add(txtBuildNumber, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	valuesSizer->Add(BoxSizer9, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
	BoxSizer12 = new wxBoxSizer(wxHORIZONTAL);
	lblRevision = new wxStaticText(pnlVersionValues, ID_REVISION_LABEL, _("Revision"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_REVISION_LABEL"));
	BoxSizer12->Add(lblRevision, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	txtRevisionNumber = new wxTextCtrl(pnlVersionValues, ID_REVISION_TEXT, _("0"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_REVISION_TEXT"));
	txtRevisionNumber->SetToolTip(_("Increments randomly when\nsome file is modified."));
	BoxSizer12->Add(txtRevisionNumber, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	valuesSizer->Add(BoxSizer12, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
	StaticLine2 = new wxStaticLine(pnlVersionValues, ID_STATICLINE2, wxDefaultPosition, wxSize(10,-1), wxLI_HORIZONTAL, _T("ID_STATICLINE2"));
	valuesSizer->Add(StaticLine2, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer19 = new wxBoxSizer(wxHORIZONTAL);
	lblCount = new wxStaticText(pnlVersionValues, ID_COUNT_LABEL, _("Build Count"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_COUNT_LABEL"));
	BoxSizer19->Add(lblCount, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	txtBuildCount = new wxTextCtrl(pnlVersionValues, ID_COUNT_TEXT, _("0"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_COUNT_TEXT"));
	txtBuildCount->SetToolTip(_("Increments every time the\nprogram is compiled. Also if \nno changes has been made."));
	BoxSizer19->Add(txtBuildCount, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	valuesSizer->Add(BoxSizer19, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
	pnlVersionValues->SetSizer(valuesSizer);
	valuesSizer->Fit(pnlVersionValues);
	valuesSizer->SetSizeHints(pnlVersionValues);
	pnlStatus = new wxPanel(nbAutoVersioning, ID_STATUS_PANEL, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_STATUS_PANEL"));
	statusSizer = new wxBoxSizer(wxVERTICAL);
	statusSizer->Add(-1,-1,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	lblStatus = new wxStaticText(pnlStatus, ID_SATUS_LABEL, _("Software Status:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_SATUS_LABEL"));
	statusSizer->Add(lblStatus, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	cmbStatus = new wxComboBox(pnlStatus, ID_STATUS_COMBOBOX, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_STATUS_COMBOBOX"));
	cmbStatus->SetSelection( cmbStatus->Append(_("Alpha")) );
	cmbStatus->Append(_("Beta"));
	cmbStatus->Append(_("Release"));
	cmbStatus->Append(_("Release Candidate"));
	cmbStatus->Append(_("Custom"));
	cmbStatus->SetToolTip(_("Example: 1.0 Alpha"));
	statusSizer->Add(cmbStatus, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticLine4 = new wxStaticLine(pnlStatus, ID_STATICLINE4, wxDefaultPosition, wxSize(10,-1), wxLI_HORIZONTAL, _T("ID_STATICLINE4"));
	statusSizer->Add(StaticLine4, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText1 = new wxStaticText(pnlStatus, ID_STATICTEXT1, _("Abbreviation:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
	statusSizer->Add(StaticText1, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	cmbAbbreviation = new wxComboBox(pnlStatus, ID_ABBREVIATION_COMBOBOX, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_ABBREVIATION_COMBOBOX"));
	cmbAbbreviation->SetSelection( cmbAbbreviation->Append(_("a")) );
	cmbAbbreviation->Append(_("b"));
	cmbAbbreviation->Append(_("r"));
	cmbAbbreviation->Append(_("rc"));
	cmbAbbreviation->SetToolTip(_("Example 1.0a"));
	statusSizer->Add(cmbAbbreviation, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	statusSizer->Add(-1,-1,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	pnlStatus->SetSizer(statusSizer);
	statusSizer->Fit(pnlStatus);
	statusSizer->SetSizeHints(pnlStatus);
	pnlScheme = new wxPanel(nbAutoVersioning, ID_SCHEME_PANEL, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_SCHEME_PANEL"));
	schemeSizer = new wxBoxSizer(wxVERTICAL);
	minorMaxSizer = new wxBoxSizer(wxHORIZONTAL);
	lblMinorMaximum = new wxStaticText(pnlScheme, ID_MINORMAXIMUN_LABEL, _("Minor maximun:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_MINORMAXIMUN_LABEL"));
	minorMaxSizer->Add(lblMinorMaximum, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	txtMinorMaximun = new wxTextCtrl(pnlScheme, ID_MINORMAXIMUN_TEXT, _("10"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_MINORMAXIMUN_TEXT"));
	txtMinorMaximun->SetToolTip(_("Resets the minor to\nzero when the specified\nvalue is reached."));
	minorMaxSizer->Add(txtMinorMaximun, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	schemeSizer->Add(minorMaxSizer, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	buildNumberMaxSizer = new wxBoxSizer(wxHORIZONTAL);
	lblBuildNumberMaximun = new wxStaticText(pnlScheme, ID_BUILDNUMBERMAX_LABEL, _("Build Number maximun:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_BUILDNUMBERMAX_LABEL"));
	buildNumberMaxSizer->Add(lblBuildNumberMaximun, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	txtBuildNumberMaximun = new wxTextCtrl(pnlScheme, ID_BUILDNUMBERMAX_TEXT, _("0"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUILDNUMBERMAX_TEXT"));
	txtBuildNumberMaximun->SetToolTip(_("Reset the build number\nto zero when the specified\nvalue is reached.\n\n0 equals to unlimited."));
	buildNumberMaxSizer->Add(txtBuildNumberMaximun, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	schemeSizer->Add(buildNumberMaxSizer, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	BoxSizer1 = new wxBoxSizer(wxHORIZONTAL);
	lblRevisionMax = new wxStaticText(pnlScheme, ID_REVISIONMAX_LABEL, _("Revision maximun:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_REVISIONMAX_LABEL"));
	BoxSizer1->Add(lblRevisionMax, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	txtRevisionMax = new wxTextCtrl(pnlScheme, ID_REVISIONMAX_TEXT, _("0"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_REVISIONMAX_TEXT"));
	txtRevisionMax->SetToolTip(_("Reset the revision to zero\nwhen the specified value \nis reached.\n\n0 equals to unlimited."));
	BoxSizer1->Add(txtRevisionMax, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	schemeSizer->Add(BoxSizer1, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	BoxSizer2 = new wxBoxSizer(wxHORIZONTAL);
	lblRevisionRandom = new wxStaticText(pnlScheme, ID_REVISIONRANDOM_LABEL, _("Revision random maximun:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_REVISIONRANDOM_LABEL"));
	BoxSizer2->Add(lblRevisionRandom, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	txtRevisionRandom = new wxTextCtrl(pnlScheme, ID_REVISIONRANDOM_TEXT, _("10"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_REVISIONRANDOM_TEXT"));
	txtRevisionRandom->SetToolTip(_("Maximun number value\nused for the random\nincrementation of the\nrevision."));
	BoxSizer2->Add(txtRevisionRandom, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	schemeSizer->Add(BoxSizer2, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	lblBuildTimes = new wxStaticText(pnlScheme, ID_BUILDTIMES_LABEL, _("Build times before incrementing Minor:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_BUILDTIMES_LABEL"));
	schemeSizer->Add(lblBuildTimes, 0, wxTOP|wxLEFT|wxRIGHT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	txtBuildTimes = new wxTextCtrl(pnlScheme, ID_BUILDTIMES_TEXT, _("100"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUILDTIMES_TEXT"));
	txtBuildTimes->SetToolTip(_("Indicates the times\nthat the project have\nto be build before\nincrementing the minor."));
	schemeSizer->Add(txtBuildTimes, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	pnlScheme->SetSizer(schemeSizer);
	schemeSizer->Fit(pnlScheme);
	schemeSizer->SetSizeHints(pnlScheme);
	pnlSettings = new wxPanel(nbAutoVersioning, ID_SETTINGS_PANEL, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_SETTINGS_PANEL"));
	settingsSizer = new wxBoxSizer(wxVERTICAL);
	settingsSizer->Add(-1,-1,0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	chkAutoIncrement = new wxCheckBox(pnlSettings, ID_AUTO_CHECK, _("Autoincrement Major and Minor"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_AUTO_CHECK"));
	chkAutoIncrement->SetValue(true);
	chkAutoIncrement->SetToolTip(_("Use the default scheme for \nautoincrementing the major \nand minor versions."));
	settingsSizer->Add(chkAutoIncrement, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	chkDates = new wxCheckBox(pnlSettings, ID_DATES_CHECK, _("Create date declarations"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_DATES_CHECK"));
	chkDates->SetValue(true);
	chkDates->SetToolTip(_("Create variable declarations\nfor date, month and year. And \nalso an ubuntu version style."));
	settingsSizer->Add(chkDates, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticLine3 = new wxStaticLine(pnlSettings, ID_STATICLINE3, wxDefaultPosition, wxSize(10,-1), wxLI_HORIZONTAL, _T("ID_STATICLINE3"));
	settingsSizer->Add(StaticLine3, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 1);
	chkCommit = new wxCheckBox(pnlSettings, ID_COMMIT_CHECK, _("Commit changes"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_COMMIT_CHECK"));
	chkCommit->SetValue(false);
	chkCommit->SetToolTip(_("If you check this you have to\ncommit changes and then the\nversion would increment."));
	settingsSizer->Add(chkCommit, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	chkAskCommit = new wxCheckBox(pnlSettings, ID_ASKCOMMIT_CHECK, _("Ask to commit changes"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_ASKCOMMIT_CHECK"));
	chkAskCommit->SetValue(false);
	chkAskCommit->Disable();
	chkAskCommit->SetToolTip(_("Ask you to commit every time\na change has been made to the \nsource code, before the compilation\ntakes effect."));
	settingsSizer->Add(chkAskCommit, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticLine1 = new wxStaticLine(pnlSettings, ID_STATICLINE1, wxDefaultPosition, wxSize(10,-1), wxLI_HORIZONTAL, _T("ID_STATICLINE1"));
	settingsSizer->Add(StaticLine1, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	chkSvn = new wxCheckBox(pnlSettings, ID_SVN_CHECK, _("svn enabled"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_SVN_CHECK"));
	chkSvn->SetValue(false);
	chkSvn->SetToolTip(_("Check this if your project is controlled by svn\nto generate an SVN_REVISION declaration."));
	settingsSizer->Add(chkSvn, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
	svnSizer = new wxBoxSizer(wxHORIZONTAL);
	txtSvnDir = new wxTextCtrl(pnlSettings, ID_SVNDIR_TEXT, wxEmptyString, wxDefaultPosition, wxSize(236,26), 0, wxDefaultValidator, _T("ID_SVNDIR_TEXT"));
	txtSvnDir->Disable();
	txtSvnDir->SetToolTip(_("Current SVN directory."));
	svnSizer->Add(txtSvnDir, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
	btnSvnDir = new wxButton(pnlSettings, ID_SVNDIR_BUTTON, _("..."), wxDefaultPosition, wxSize(23,26), 0, wxDefaultValidator, _T("ID_SVNDIR_BUTTON"));
	btnSvnDir->Disable();
	btnSvnDir->SetToolTip(_("Choose current svn directory project\nif diffrent from the project default."));
	svnSizer->Add(btnSvnDir, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
	settingsSizer->Add(svnSizer, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
	pnlSettings->SetSizer(settingsSizer);
	settingsSizer->Fit(pnlSettings);
	settingsSizer->SetSizeHints(pnlSettings);
	pnlChanges = new wxPanel(nbAutoVersioning, ID_CHANGES_PANEL, wxPoint(231,17), wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_CHANGES_PANEL"));
	changesSizer = new wxBoxSizer(wxVERTICAL);
	chkChanges = new wxCheckBox(pnlChanges, ID_GENERATECHANGES_CHECKBOX, _("Generate changes log"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_GENERATECHANGES_CHECKBOX"));
	chkChanges->SetValue(false);
	chkChanges->SetToolTip(_("This will open a window\neverytime you commit or\nthe project version increments.\n\nThen you can enter the\nchanges made to the project."));
	changesSizer->Add(chkChanges, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer4 = new wxBoxSizer(wxHORIZONTAL);
	lblChangesTitle = new wxStaticText(pnlChanges, ID_FORMAT_STATICTEXT, _("Title Format:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_FORMAT_STATICTEXT"));
	BoxSizer4->Add(lblChangesTitle, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	txtChangesTitle = new wxTextCtrl(pnlChanges, ID_CHANGESTITLE_TEXTCTRL, _("released version %M.%m.%b of %p"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHANGESTITLE_TEXTCTRL"));
	txtChangesTitle->Disable();
	BoxSizer4->Add(txtChangesTitle, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	changesSizer->Add(BoxSizer4, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	lblChangesFormats = new wxStaticText(pnlChanges, ID_FORMATS_STATICTEXT, _("Major: %M, Minor: %m, Build: %b, Revision: %r, SVN Revision: %s, Date: %d, Month: %o, Year: %y, Ubuntu Style Version: %u, Status: %T, Status Short: %t, Project title: %p"), wxDefaultPosition, wxSize(375,74), 0, _T("ID_FORMATS_STATICTEXT"));
	changesSizer->Add(lblChangesFormats, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	pnlChanges->SetSizer(changesSizer);
	changesSizer->Fit(pnlChanges);
	changesSizer->SetSizeHints(pnlChanges);
	nbAutoVersioning->AddPage(pnlVersionValues, _("Version Values"), true);
	nbAutoVersioning->AddPage(pnlStatus, _("Status"), false);
	nbAutoVersioning->AddPage(pnlScheme, _("Scheme"), false);
	nbAutoVersioning->AddPage(pnlSettings, _("Settings"), false);
	nbAutoVersioning->AddPage(pnlChanges, _("Changes Log"), false);
	mainSizer->Add(nbAutoVersioning, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	buttonsSizer = new wxBoxSizer(wxHORIZONTAL);
	btnAccept = new wxButton(this, ID_ACCEPT, _("&Accept"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_ACCEPT"));
	btnAccept->SetDefault();
	btnAccept->SetToolTip(_("Accept changes made."));
	buttonsSizer->Add(btnAccept, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	buttonsSizer->Add(-1,-1,0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
	btnCancel = new wxButton(this, ID_CANCEL, _("&Cancel"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CANCEL"));
	btnCancel->SetToolTip(_("Cancel changes made\nto the values in the editor."));
	buttonsSizer->Add(btnCancel, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	mainSizer->Add(buttonsSizer, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 1);
	SetSizer(mainSizer);
	mainSizer->SetSizeHints(this);
	Center();
	Connect(ID_STATUS_COMBOBOX,wxEVT_COMMAND_COMBOBOX_SELECTED,(wxObjectEventFunction)&avVersionEditorDlg::OnCmbStatusSelect);
	Connect(ID_COMMIT_CHECK,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&avVersionEditorDlg::OnChkCommitClick);
	Connect(ID_SVN_CHECK,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&avVersionEditorDlg::OnSvnCheck);
	Connect(ID_SVNDIR_BUTTON,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&avVersionEditorDlg::OnSvnDirectoryClick);
	Connect(ID_GENERATECHANGES_CHECKBOX,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&avVersionEditorDlg::OnChkChangesClick);
	Connect(ID_ACCEPT,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&avVersionEditorDlg::OnAcceptClick);
	Connect(ID_CANCEL,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&avVersionEditorDlg::OnCancelClick);
	//*)
}

avVersionEditorDlg::~avVersionEditorDlg()
{
	//(*Destroy(avVersionEditorDlg)
	//*)
}
//}


//{Version Values
long avVersionEditorDlg::Major(long value){
    if(value != -1){
        m_major = value;
        wxString strValue;
        strValue.Printf(_("%d"),value);
        txtMajorVersion->SetValue(strValue);
    }

    return m_major;
}

long avVersionEditorDlg::Minor(long value){
    if(value != -1){
        m_minor = value;
        wxString strValue;
        strValue.Printf(_("%d"),value);
        txtMinorVersion->SetValue(strValue);
    }

    return m_minor;
}

long avVersionEditorDlg::Build(long value){
    if(value != -1){
        m_build = value;
        wxString strValue;
        strValue.Printf(_("%d"),value);
        txtBuildNumber->SetValue(strValue);
    }

    return m_build;
}

long avVersionEditorDlg::Revision(long value){
    if(value != -1){
        m_revision = value;
        wxString strValue;
        strValue.Printf(_("%d"),value);
        txtRevisionNumber->SetValue(strValue);
    }

    return m_revision;
}

long avVersionEditorDlg::Count(long value){
    if(value != -1){
        m_count = value;
        wxString strValue;
        strValue.Printf(_("%d"),value);
        txtBuildCount->SetValue(strValue);
    }

    return m_count;
}
//}

//{Settings
long avVersionEditorDlg::Auto(long value){
    if(value < 1){
        m_autoMajorMinor = value;
        chkAutoIncrement->SetValue(false);
    }
    else if(value == 1){
        m_autoMajorMinor = value;
        chkAutoIncrement->SetValue(true);
    }

    return m_autoMajorMinor;
}

long avVersionEditorDlg::Dates(long value){
    if(value < 1){
        m_dates = value;
        chkDates->SetValue(false);
    }
    else if(value == 1){
        m_dates = value;
        chkDates->SetValue(true);
    }

    return m_dates;
}

long avVersionEditorDlg::Svn(long value){
    if(value < 1){
        m_svn = value;
        chkSvn->SetValue(false);
        txtSvnDir->Disable();
        btnSvnDir->Disable();
    }
    else if(value == 1){
        m_svn = value;
        chkSvn->SetValue(true);
        txtSvnDir->Enable();
        btnSvnDir->Enable();
    }

    return m_svn;
}

wxString avVersionEditorDlg::SvnDirectory(wxString value){
    if(!value.IsEmpty()){
        m_svnDirectory = value;
        txtSvnDir->SetValue(m_svnDirectory);
    }

    return m_svnDirectory;
}

long avVersionEditorDlg::Commit(long value){
    if(value < 1){
        m_commit = value;
        chkCommit->SetValue(false);
        chkAskCommit->Disable();
    }
    else if(value == 1){
        m_commit = value;
        chkCommit->SetValue(true);
        chkAskCommit->Enable();
    }

    return m_commit;
}

long avVersionEditorDlg::CommitAsk(long value){
    if(value < 1){
        m_askCommit = value;
        chkAskCommit->SetValue(false);
    }
    else if(value == 1){
        m_askCommit = value;
        chkAskCommit->SetValue(true);
    }

    return m_askCommit;
}
//}

//{Software Status
wxString avVersionEditorDlg::Status(wxString value){
    if(!value.IsEmpty()){
        m_status = value;
        cmbStatus->SetValue(value);
    }

    return m_status;
}

wxString avVersionEditorDlg::StatusAbbreviation(wxString value){
    if(!value.IsEmpty()){
        m_statusAbbreviation = value;
        cmbAbbreviation->SetValue(value);
    }

    return m_statusAbbreviation;
}
//}

//{Scheme
long avVersionEditorDlg::MinorMaximun(long value){
    if(value != -1){
        m_minorMaximun = value;
        wxString strValue;
        strValue.Printf(_("%d"),value);
        txtMinorMaximun->SetValue(strValue);
    }

    return m_minorMaximun;
}

long avVersionEditorDlg::BuildMaximun(long value){
    if(value != -1){
        m_buildMaximun = value;
        wxString strValue;
        strValue.Printf(_("%d"),value);
        txtBuildNumberMaximun->SetValue(strValue);
    }

    return m_buildMaximun;
}

long avVersionEditorDlg::RevisionMaximun(long value){
    if(value != -1){
        m_revisionMaximun = value;
        wxString strValue;
        strValue.Printf(_("%d"),value);
        txtRevisionMax->SetValue(strValue);
    }

    return m_revisionMaximun;
}

long avVersionEditorDlg::RevisionRandomMaximun(long value){
    if(value != -1){
        m_revisionRandomMaximun = value;
        wxString strValue;
        strValue.Printf(_("%d"),value);
        txtRevisionRandom->SetValue(strValue);
    }

    return m_revisionRandomMaximun;
}

long avVersionEditorDlg::BuildTimesToMinorIncrement(long value){
    if(value != -1){
        m_buildTimesToMinorIncrement = value;
        wxString strValue;
        strValue.Printf(_("%d"),value);
        txtBuildTimes->SetValue(strValue);
    }

    return m_buildTimesToMinorIncrement;
}
//}

//{Changes Log
long avVersionEditorDlg::Changes(long value){
    if(value < 1){
        m_changes = 0;
        chkChanges->SetValue(false);
        txtChangesTitle->Disable();
    }
    else if(value == 1){
        m_changes = value;
        chkChanges->SetValue(true);
        txtChangesTitle->Enable();
    }

    return m_changes;
}

wxString avVersionEditorDlg::ChangesTitle(wxString value){
    if(!value.IsEmpty()){
        m_changesTitle = value;
        txtChangesTitle->SetValue(value);
    }

    return m_changesTitle;
}
//}

//{Events
void avVersionEditorDlg::OnAcceptClick(wxCommandEvent& event)
{
    txtMajorVersion->GetValue().ToLong(&m_major);
    txtMinorVersion->GetValue().ToLong(&m_minor);
    txtBuildNumber->GetValue().ToLong(&m_build);
    txtRevisionNumber->GetValue().ToLong(&m_revision);
    txtBuildCount->GetValue().ToLong(&m_count);

    m_autoMajorMinor = chkAutoIncrement->IsChecked()?1:0;
    m_dates = chkDates->IsChecked()?1:0;
    m_svn = chkSvn->IsChecked()?1:0;
    m_svnDirectory = txtSvnDir->GetValue();
    m_commit = chkCommit->IsChecked()?1:0;
    m_askCommit = chkAskCommit->IsChecked()?1:0;

    m_status = cmbStatus->GetValue();
    m_statusAbbreviation = cmbAbbreviation->GetValue();

    txtMinorMaximun->GetValue().ToLong(&m_minorMaximun);
    txtBuildNumberMaximun->GetValue().ToLong(&m_buildMaximun);
    txtRevisionMax->GetValue().ToLong(&m_revisionMaximun);
    txtRevisionRandom->GetValue().ToLong(&m_revisionRandomMaximun);
    txtBuildTimes->GetValue().ToLong(&m_buildTimesToMinorIncrement);

    m_changes = chkChanges->IsChecked()?1:0;
    m_changesTitle = txtChangesTitle->GetValue();

    EndModal(0);
}

void avVersionEditorDlg::OnCancelClick(wxCommandEvent& event)
{
    EndModal(0);
}

void avVersionEditorDlg::OnSvnCheck(wxCommandEvent& event)
{
        if(chkSvn->IsChecked()){
            txtSvnDir->Enable();
            txtSvnDir->SetValue(m_svnDirectory);
            btnSvnDir->Enable();
        }
        else{
            txtSvnDir->Disable();
            btnSvnDir->Disable();
        }
}

void avVersionEditorDlg::OnSvnDirectoryClick(wxCommandEvent& event)
{
    wxString dir = wxDirSelector(wxDirSelectorPromptStr,m_svnDirectory,0,wxDefaultPosition,this);
    if(!dir.IsEmpty()){
        txtSvnDir->SetValue(dir);
        m_svnDirectory = txtSvnDir->GetValue();
    }
}

void avVersionEditorDlg::OnChkCommitClick(wxCommandEvent& event)
{
    if(chkCommit->IsChecked())
        chkAskCommit->Enable();
    else
        chkAskCommit->Disable();
}

void avVersionEditorDlg::OnCmbStatusSelect(wxCommandEvent& event)
{
    int status = cmbStatus->GetCurrentSelection();
    if(status != 4){
        cmbAbbreviation->SetSelection(status);
    }
    else{
        cmbAbbreviation->SetValue(_(""));
        cmbStatus->SetValue(_(""));
    }
}

void avVersionEditorDlg::OnChkChangesClick(wxCommandEvent& event)
{
    if(chkChanges->IsChecked()){
        txtChangesTitle->Enable();
    }
    else{
        txtChangesTitle->Disable();
    }
}
//}
