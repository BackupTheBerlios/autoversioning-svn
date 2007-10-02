#include <sdk.h>

#ifndef CB_PRECOMP
#include <wx/file.h>
#include <wx/ffile.h>
#include <wx/filename.h>
#include <wx/intl.h>
#include <wx/msgdlg.h>
#include <wx/timer.h>
#include <cbproject.h>
#include <manager.h>
#include <messagemanager.h>
#include <projectbuildtarget.h>
#include <projectmanager.h>
#endif

#include <ctime>
#include <cstdlib> //For random numbers
#include "AutoVersioning.h"
#include "avSvnRevision.h"
#include "avStrCon.h"
#include "avVersionEditorDlg.h"
#include "avChangesDlg.h"

using namespace std;

enum MenuID{idMenuAutoVersioning=5555,idMenuCommitChanges};


//{Ini Settings Names
static const wxString MAJOR = _T("Major");
static const wxString MINOR = _T("Minor");
static const wxString BUILD_NUMBER = _T("Build Number");
static const wxString REVISION = _T("Revision");
static const wxString BUILD_COUNT = _T("Build Count");
static const wxString AUTO_INCREMENT = _T("Auto Increment");
static const wxString DATES = _T("Dates");
static const wxString SVN = _T("Svn");
static const wxString SVN_DIRECTORY = _T("Svn Directory");

static const wxString COMMIT = _T("Commit");
static const wxString COMMIT_ASK = _T("Commit Ask");
static const wxString LANGUAGE = _T("Language");

static const wxString STATUS = _T("Status");
static const wxString STATUS_ABBREVIATION = _T("Status Abbreviation");

static const wxString MINOR_MAX = _T("Minor Max");
static const wxString BUILD_MAX = _T("Build Max");
static const wxString REVISION_MAX = _T("Revision Max");
static const wxString REVISION_RANDOM_MAX = _T("Revision Random Max");
static const wxString BUILD_TIMES_TO_MINOR_INCREMENT = _T("Build Times To Minor Increment");

static const wxString BUILD_HISTORY = _T("Build History");
static const wxString MODIFIED = _T("Modified");

static const wxString CHANGES_LOG = _T("Changes Log");
static const wxString CHANGES_TITLE = _T("Changes Title");
//}


//{Event Table
BEGIN_EVENT_TABLE(AutoVersioning,wxEvtHandler)
    EVT_TIMER(-1, AutoVersioning::OnTimerVerify)

    EVT_UPDATE_UI(idMenuCommitChanges, AutoVersioning::OnUpdateUI)
    EVT_MENU(idMenuAutoVersioning, AutoVersioning::OnMenuAutoVersioning)
    EVT_MENU(idMenuCommitChanges, AutoVersioning::OnMenuCommitChanges)
END_EVENT_TABLE()
//}

namespace
{
    PluginRegistrant<AutoVersioning> reg(_T("AutoVersioning"));
}

//{Constructor and Destructor
AutoVersioning::AutoVersioning()
{}

AutoVersioning::~AutoVersioning()
{}
//}

//{Virtual overrides
void AutoVersioning::OnAttach()
{
    if (!IsAttached())
    {
        wxMessageBox(_("Error loading AutoVersioning Plugin!"),_("Error"),wxICON_ERROR );
    }

    m_versionEditorDialog = new avVersionEditorDlg((wxWindow*) Manager::Get()->GetAppWindow(),0L);
    m_timerStatus = new wxTimer(this,30000);
    m_timerStatus->Start(1000);

    //Register functions to events
    Manager::Get()->RegisterEventSink(cbEVT_COMPILER_STARTED, new cbEventFunctor<AutoVersioning, CodeBlocksEvent>(this, &AutoVersioning::OnCompilerStarted));
    Manager::Get()->RegisterEventSink(cbEVT_COMPILER_FINISHED, new cbEventFunctor<AutoVersioning, CodeBlocksEvent>(this, &AutoVersioning::OnCompilerFinished));
}

void AutoVersioning::OnRelease(bool appShutDown)
{
    m_versionEditorDialog->Destroy();
    m_versionEditorDialog = 0;

    if (m_timerStatus->IsRunning())
        m_timerStatus->Stop();

    delete m_timerStatus;
    m_timerStatus = 0;
}

void AutoVersioning::BuildMenu(wxMenuBar* menuBar)
{
    int idProject = menuBar->FindMenu(_("Project"));
    if (idProject != wxNOT_FOUND)
    {
        wxMenu* project = menuBar->GetMenu(idProject);
        project->AppendSeparator();
        project->Append(idMenuAutoVersioning, _("Auto Versioning"), _("Manage your project version"));
        project->Append(idMenuCommitChanges, _("Commit Changes"), _("Commit the changes made to the project to increment the version"));
    }
}
//}

//{Envent Functions
void AutoVersioning::OnCompilerStarted(CodeBlocksEvent& event)
{

    cbProject* project = Manager::Get()->GetProjectManager()->GetActiveProject();
    if (project && IsAttached())
    {
        const wxString basepath = project->GetBasePath();
        m_versionConfigPath = basepath + _T("version.ini");
        m_versionHeaderPath = basepath + _T("version.h");

        if (wxFileExists(m_versionConfigPath))
        {
            m_versionConfig.Open(m_versionConfigPath);
            if (m_versionConfig.ReadValue( MODIFIED ) == 1)
            {
                long commit = m_versionConfig.ReadValue( COMMIT );
                long askCommit = m_versionConfig.ReadValue( COMMIT_ASK );
                m_versionConfig.Close();

                if (commit && askCommit)
                {
                    if (wxMessageBox(_("Do you want to commit changes?"),_T(""),wxYES_NO) == wxYES)
                    {
                        CommitChanges();
                        m_versionConfig.Open(m_versionConfigPath);
                        m_versionConfig.WriteValue(MODIFIED, 0);
                        m_versionConfig.Close();
                    }
                }
                if (!commit)
                {
                    CommitChanges();
                }
            }
            else
            {
                m_versionConfig.Close();
            }
        }
    }
}

void AutoVersioning::OnCompilerFinished(CodeBlocksEvent& event)
{
    cbProject* project = Manager::Get()->GetProjectManager()->GetActiveProject();
    if (project && IsAttached())
    {
        wxString basepath = project->GetBasePath();
        m_versionConfigPath = basepath + _T("version.ini");
        m_versionHeaderPath = basepath + _T("version.h");

        if (wxFileExists(m_versionConfigPath))
        {
            m_versionConfig.Open(m_versionConfigPath);

            long commit = m_versionConfig.ReadValue( COMMIT );
            long modified = m_versionConfig.ReadValue( MODIFIED );
            long buildCount = m_versionConfig.ReadValue( BUILD_COUNT );
            m_versionConfig.WriteValue(BUILD_COUNT, buildCount+1);

            if (modified == 1 && commit == 0)
            {
                m_versionConfig.WriteValue(MODIFIED, 0);
            }

            m_versionConfig.Close();
        }
    }
}

void AutoVersioning::OnTimerVerify(wxTimerEvent& event)
{
    cbProject* project = Manager::Get()->GetProjectManager()->GetActiveProject();
    if (project && IsAttached())
    {
        const wxString basepath = project->GetBasePath();
        m_versionConfigPath = basepath + _T("version.ini");
        m_versionHeaderPath = basepath + _T("version.h");

        if (wxFileExists(m_versionConfigPath))
        {
            m_versionConfig.Open(m_versionConfigPath);
            if (m_versionConfig.ReadValue( MODIFIED ) != 1)
            {
                m_versionConfig.Close();
                bool modified = false;
                for (int i=0; i<project->GetFilesCount(); ++i)
                {
                    const ProjectFile* file = project->GetFile(i);
                    if (file->GetFileState() == fvsModified)
                    {
                        modified = true;
                        break;
                    }
                }
                if (modified)
                {
                    m_versionConfig.Open(m_versionConfigPath);
                    m_versionConfig.WriteValue(MODIFIED, 1);
                    m_versionConfig.Close();
                }
            }
        }
    }
}

void AutoVersioning::OnMenuAutoVersioning(wxCommandEvent& event)
{
    if (IsAttached())
    {

        cbProject* project = Manager::Get()->GetProjectManager()->GetActiveProject();
        if (!project)
        {
            wxString msg = _("No active project!");
            cbMessageBox(msg, _("Error"), wxICON_ERROR | wxOK);
        }
        else
        {

            const wxString basepath = project->GetBasePath();
            m_versionConfigPath = basepath + _T("version.ini");
            m_versionHeaderPath = basepath + _T("version.h");

            if (wxFileExists(m_versionConfigPath))
            {
                UpdateVersionFileFromDialog();
            }
            else
            {
                if (wxMessageBox(_("Configure the project \"") + project->GetTitle() + _("\" for Auto Versioning?"),_("Auto Versioning"),wxYES_NO) == wxYES)
                {

                    CreateVersionFile();
                    UpdateVersionHeader();

                    for (int i=1; i < project->GetBuildTargetsCount(); ++i)
                    {
                        project->AddFile(i,m_versionHeaderPath,true,true,0);
                    }

                    wxMessageBox(_("Project configured!"));
                }
            }
        }
    }
}

void AutoVersioning::OnMenuCommitChanges(wxCommandEvent& event)
{
    if (IsAttached())
    {

        const cbProject* project = Manager::Get()->GetProjectManager()->GetActiveProject();
        if (project)
        {

            const wxString basepath = project->GetBasePath();
            m_versionConfigPath = basepath + _T("version.ini");
            m_versionHeaderPath = basepath + _T("version.h");

            if (wxFileExists(m_versionConfigPath))
            {
                CommitChanges();
                m_versionConfig.Open(m_versionConfigPath);
                m_versionConfig.WriteValue(MODIFIED,0);
                m_versionConfig.Close();
            }
        }
    }
}

void AutoVersioning::OnUpdateUI(wxUpdateUIEvent& event)
{
    if (IsAttached())
    {

        const cbProject* project = Manager::Get()->GetProjectManager()->GetActiveProject();
        if (project)
        {

            const wxString basepath = project->GetBasePath();
            m_versionConfigPath = basepath + _T("version.ini");
            m_versionHeaderPath = basepath + _T("version.h");

            if (wxFileExists(m_versionConfigPath))
            {
                m_versionConfig.Open(m_versionConfigPath);
                long commit = m_versionConfig.ReadValue(COMMIT);
                long modified = m_versionConfig.ReadValue(MODIFIED);
                m_versionConfig.Close();

                if (modified && commit)
                {
                    event.Enable(true);
                }
                else
                {
                    event.Enable(false);
                }
            }
            else
            {
                event.Enable(false);
            }
        }
    }
}
//}

//{Functions
void AutoVersioning::CreateVersionFile(bool update)
{
    m_timerStatus->Stop();
    m_versionConfig.Open(m_versionConfigPath);

    if (!update)
    {
        m_versionEditorDialog->Major(1);
        m_versionEditorDialog->Minor(0);
        m_versionEditorDialog->Build(0);
        m_versionEditorDialog->Revision(0);
        m_versionEditorDialog->Count(1);
        m_versionEditorDialog->Auto(1);
        m_versionEditorDialog->Dates(1);
        m_versionEditorDialog->Svn(0);
        m_versionEditorDialog->SvnDirectory(m_versionConfigPath.Remove(m_versionConfigPath.Len() - wxStrlen(_T("/version.ini"))));
        m_versionEditorDialog->Commit(0);
        m_versionEditorDialog->CommitAsk(0);
        m_versionEditorDialog->Language(_T("C++"));
        m_versionEditorDialog->Status(_T("Alpha"));
        m_versionEditorDialog->StatusAbbreviation(_T("a"));
        m_versionEditorDialog->MinorMaximun(10);
        m_versionEditorDialog->BuildMaximun(0);
        m_versionEditorDialog->RevisionMaximun(0);
        m_versionEditorDialog->RevisionRandomMaximun(10);
        m_versionEditorDialog->BuildTimesToMinorIncrement(100);
        m_versionEditorDialog->Changes(0);
        m_versionEditorDialog->ChangesTitle(_("released version %M.%m.%b of %p"));

        m_versionEditorDialog->ShowModal();
    }
    else
    {
        UpdateEditorDialog();
        m_versionEditorDialog->ShowModal();
    }

    m_versionConfig.WriteValue(MAJOR, m_versionEditorDialog->Major());
    m_versionConfig.WriteValue(MINOR, m_versionEditorDialog->Minor());
    m_versionConfig.WriteValue(BUILD_NUMBER, m_versionEditorDialog->Build());
    m_versionConfig.WriteValue(REVISION, m_versionEditorDialog->Revision());
    m_versionConfig.WriteValue(BUILD_COUNT, m_versionEditorDialog->Count());
    m_versionConfig.WriteValue(AUTO_INCREMENT, m_versionEditorDialog->Auto());
    m_versionConfig.WriteValue(DATES, m_versionEditorDialog->Dates());
    m_versionConfig.WriteValue(SVN, m_versionEditorDialog->Svn());
    m_versionConfig.WriteValue(SVN_DIRECTORY, m_versionEditorDialog->SvnDirectory());

    m_versionConfig.WriteValue(COMMIT, m_versionEditorDialog->Commit());
    m_versionConfig.WriteValue(COMMIT_ASK, m_versionEditorDialog->CommitAsk());

    m_versionConfig.WriteValue(LANGUAGE, m_versionEditorDialog->Language());

    m_versionConfig.WriteValue(STATUS, m_versionEditorDialog->Status());
    m_versionConfig.WriteValue(STATUS_ABBREVIATION, m_versionEditorDialog->StatusAbbreviation());

    m_versionConfig.WriteValue(MINOR_MAX, m_versionEditorDialog->MinorMaximun());
    m_versionConfig.WriteValue(BUILD_MAX, m_versionEditorDialog->BuildMaximun());
    m_versionConfig.WriteValue(REVISION_MAX, m_versionEditorDialog->RevisionMaximun());
    m_versionConfig.WriteValue(REVISION_RANDOM_MAX, m_versionEditorDialog->RevisionRandomMaximun());
    m_versionConfig.WriteValue(BUILD_TIMES_TO_MINOR_INCREMENT, m_versionEditorDialog->BuildTimesToMinorIncrement());

    m_versionConfig.WriteValue(CHANGES_LOG, m_versionEditorDialog->Changes());
    m_versionConfig.WriteValue(CHANGES_TITLE, m_versionEditorDialog->ChangesTitle());

    if (!update)
    {
        m_versionConfig.WriteValue(BUILD_HISTORY,0);
        m_versionConfig.WriteValue(MODIFIED,0);
    }
    m_versionConfig.Close();
    m_timerStatus->Start(1000);
}

void AutoVersioning::UpdateVersionFileFromDialog()
{
    CreateVersionFile(true);
    UpdateVersionHeader();
}

void AutoVersioning::UpdateVersionHeader()
{
    m_timerStatus->Stop();

    cbProject* project = Manager::Get()->GetProjectManager()->GetActiveProject();

    const wxString basepath = project->GetBasePath();
    m_versionConfigPath = basepath + _T("version.ini");
    m_versionHeaderPath = basepath + _T("version.h");

    wxString headerOutput = _T("");

    m_versionConfig.Open(m_versionConfigPath);

    long date = m_versionConfig.ReadValue( DATES );
    long major = m_versionConfig.ReadValue( MAJOR );
    long minor = m_versionConfig.ReadValue( MINOR );
    long build = m_versionConfig.ReadValue( BUILD_NUMBER );
    long revision = m_versionConfig.ReadValue( REVISION );
    long count = m_versionConfig.ReadValue( BUILD_COUNT );
    long svn = m_versionConfig.ReadValue( SVN );
    wxString status = m_versionConfig.ReadString( STATUS );
    wxString statusAbbreviation = m_versionConfig.ReadString( STATUS_ABBREVIATION );
    wxString language  = m_versionConfig.ReadString( LANGUAGE );
    wxString svnDirectory = m_versionConfig.ReadString( SVN_DIRECTORY );

    m_versionConfig.Close();

    headerOutput << _T("#ifndef VERSION_H") << _T("\n");
    headerOutput << _T("#define VERSION_H") << _T("\n");
    headerOutput << _T("\n");

    if(language == _T("C++")){
        headerOutput << _T("namespace AutoVersion{") << _T("\n");
        headerOutput << _T("\t") << _T("\n");
    }

    if (date == 1)
    {
        wxDateTime actualDate = wxDateTime::Now();
        headerOutput << _T("\t") << _T("//Date Version Types") << _T("\n");
        headerOutput << _T("\t") << _T("static char DATE[] = ") << actualDate.Format(_T("\"%d\"")) << _T(";\n");
        headerOutput << _T("\t") << _T("static char MONTH[] = ") << actualDate.Format(_T("\"%m\"")) << _T(";\n");
        headerOutput << _T("\t") << _T("static char YEAR[] = ") << actualDate.Format(_T("\"%Y\"")) << _T(";\n");
        long ubuntuYearNumber = 0;
        actualDate.Format(_T("%y")).ToLong(&ubuntuYearNumber);
        wxString ubuntuYear;
        ubuntuYear.Printf(_T("%d"),ubuntuYearNumber);
        headerOutput << _T("\t") << _T("static double UBUNTU_VERSION_STYLE = ") << ubuntuYear << actualDate.Format(_T(".%m")) << _T(";\n");
        headerOutput << _T("\t") << _T("\n");
    }

    headerOutput << _T("\t") << _T("//Software Status") << _T("\n");
    headerOutput << _T("\t") << _T("static char STATUS[] = \"") << status << _T("\";\n");
    headerOutput << _T("\t") << _T("static char STATUS_SHORT[] = \"") << statusAbbreviation << _T("\";\n");
    headerOutput << _T("\t") << _T("\n");

    wxString myPrintf;
    headerOutput << _T("\t") << _T("//Standard Version Type") << _T("\n");
    myPrintf.Printf(_T("%d"),major);
    headerOutput << _T("\t") << _T("static long MAJOR = ") << myPrintf << _T(";\n");
    myPrintf.Printf(_T("%d"),minor);
    headerOutput << _T("\t") << _T("static long MINOR = ") << myPrintf << _T(";\n");
    myPrintf.Printf(_T("%d"),build);
    headerOutput << _T("\t") << _T("static long BUILD = ") << myPrintf << _T(";\n");
    myPrintf.Printf(_T("%d"),revision);
    headerOutput << _T("\t") << _T("static long REVISION = ") << myPrintf << _T(";\n");
    headerOutput << _T("\t") << _T("\n");

    headerOutput << _T("\t") << _T("//Miscellaneous Version Types") << _T("\n");
    myPrintf.Printf(_T("%d"),count);
    headerOutput << _T("\t") << _T("static long BUILDS_COUNT = ") << myPrintf << _T(";\n");

    myPrintf.Printf(_T("%d,%d,%d,%d"),major,minor,build,revision);
    headerOutput << _T("\t") << _T("#define RC_FILEVERSION ") << myPrintf << _T("\n");

    myPrintf.Printf(_T("\"%d, %d, %d, %d\\0\""),major,minor,build,revision);
    headerOutput << _T("\t") << _T("#define RC_FILEVERSION_STRING ") << myPrintf << _T("\n");

    myPrintf.Printf(_T("\"%d.%d.%d.%d\""),major,minor,build,revision);
    headerOutput << _T("\t") << _T("static char FULLVERSION_STRING[] = ") << myPrintf << _T(";\n");

    if (svn == 1)
    {
        wxString revision,date;
        if (!QuerySvn(svnDirectory, revision, date))
            wxMessageBox(_("Svn configuration files not found.\nVerify the Auto Versioning svn directory."),_("Error"),wxICON_ERROR);
        headerOutput << _T("\t") << _T("\n");
        headerOutput << _T("\t") << _T("//SVN Version") << _T("\n");
        headerOutput << _T("\t") << _T("static char SVN_REVISION[] = ") << _T("\"") + revision + _T("\"")<< _T(";\n");
        headerOutput << _T("\t") << _T("static char SVN_DATE[] = ") << _T("\"") + date + _T("\"")<< _T(";\n");
    }

    headerOutput << _T("\t") << _T("\n");

    if(language == _T("C++")){
        headerOutput << _T("}") << _T("\n");
    }

    headerOutput << _T("#endif //VERSION_h\n");

    wxFile versionHeaderFile(m_versionHeaderPath,wxFile::write);
    versionHeaderFile.Write(headerOutput);
    versionHeaderFile.Close();

    m_timerStatus->Start(1000);
}

void AutoVersioning::UpdateEditorDialog()
{

    m_versionEditorDialog->Major(m_versionConfig.ReadValue( MAJOR ));
    m_versionEditorDialog->Minor(m_versionConfig.ReadValue( MINOR ));
    m_versionEditorDialog->Build(m_versionConfig.ReadValue( BUILD_NUMBER ));
    m_versionEditorDialog->Revision(m_versionConfig.ReadValue( REVISION ));
    m_versionEditorDialog->Count(m_versionConfig.ReadValue( BUILD_COUNT ));

    m_versionEditorDialog->Auto(m_versionConfig.ReadValue( AUTO_INCREMENT ));
    m_versionEditorDialog->Dates(m_versionConfig.ReadValue( DATES ));
    m_versionEditorDialog->Svn(m_versionConfig.ReadValue( SVN ));
    m_versionEditorDialog->SvnDirectory(m_versionConfig.ReadString( SVN_DIRECTORY ));
    m_versionEditorDialog->Commit(m_versionConfig.ReadValue( COMMIT ));
    m_versionEditorDialog->CommitAsk(m_versionConfig.ReadValue( COMMIT_ASK ));
    m_versionEditorDialog->Language(m_versionConfig.ReadString( LANGUAGE ));

    m_versionEditorDialog->Status(m_versionConfig.ReadString( STATUS ));
    m_versionEditorDialog->StatusAbbreviation(m_versionConfig.ReadString( STATUS_ABBREVIATION ));

    m_versionEditorDialog->MinorMaximun(m_versionConfig.ReadValue( MINOR_MAX ));
    m_versionEditorDialog->BuildMaximun(m_versionConfig.ReadValue( BUILD_MAX ));
    m_versionEditorDialog->RevisionMaximun(m_versionConfig.ReadValue( REVISION_MAX ));
    m_versionEditorDialog->RevisionRandomMaximun(m_versionConfig.ReadValue( REVISION_RANDOM_MAX ));
    m_versionEditorDialog->BuildTimesToMinorIncrement(m_versionConfig.ReadValue( BUILD_TIMES_TO_MINOR_INCREMENT ));

    m_versionEditorDialog->Changes(m_versionConfig.ReadValue( CHANGES_LOG ));
    m_versionEditorDialog->ChangesTitle(m_versionConfig.ReadString( CHANGES_TITLE ));
}

void AutoVersioning::CommitChanges()
{
    cbProject* project = Manager::Get()->GetProjectManager()->GetActiveProject();

    if (project && IsAttached())
    {
        const wxString basepath = project->GetBasePath();
        m_versionConfigPath = basepath + _T("version.ini");
        m_versionHeaderPath = basepath + _T("version.h");

        if (wxFileExists(m_versionConfigPath))
        {
            m_versionConfig.Open(m_versionConfigPath);

            long major = m_versionConfig.ReadValue( MAJOR );
            long minor = m_versionConfig.ReadValue( MINOR );
            long build = m_versionConfig.ReadValue( BUILD_NUMBER );
            long revision = m_versionConfig.ReadValue( REVISION );
            long autoI = m_versionConfig.ReadValue( AUTO_INCREMENT );
            long buildH = m_versionConfig.ReadValue( BUILD_HISTORY );
            long modified = m_versionConfig.ReadValue( MODIFIED );

            long minorMax = m_versionConfig.ReadValue( MINOR_MAX);
            long buildMax = m_versionConfig.ReadValue( BUILD_MAX);
            long revisionMax = m_versionConfig.ReadValue( REVISION_MAX );
            long revisionRandomMax = m_versionConfig.ReadValue( REVISION_RANDOM_MAX );
            long buildTimes = m_versionConfig.ReadValue( BUILD_TIMES_TO_MINOR_INCREMENT );

            long changes = m_versionConfig.ReadValue( CHANGES_LOG );

            if (modified == 1)
            {
                srand((unsigned)time(0));
                revision += 1 + rand( ) % revisionRandomMax;

                if ((revisionMax != 0) && (revision > revisionMax))
                {
                    revision = 0;
                }

                if (buildMax == 0)
                    ++build;
                else if (build >= buildMax)
                    build = 0;
                else
                    ++build;

                if (autoI == 1)
                {
                    ++buildH;
                    if (buildH >= buildTimes)
                    {
                        buildH = 0;
                        ++minor;
                    }
                    if (minor > minorMax)
                    {
                        minor = 0;
                        ++major;
                    }
                }
            }

            m_versionConfig.WriteValue(MAJOR, major);
            m_versionConfig.WriteValue(MINOR, minor);
            m_versionConfig.WriteValue(BUILD_NUMBER, build);
            m_versionConfig.WriteValue(REVISION, revision);
            m_versionConfig.WriteValue(BUILD_HISTORY, buildH);

            m_versionConfig.Close();

            if (changes == 1)
            {
                GenerateChanges();
            }

            project->SaveAllFiles();
            UpdateVersionHeader();
        }
    }
}

void AutoVersioning::GenerateChanges()
{
    cbProject* project = Manager::Get()->GetProjectManager()->GetActiveProject();

    avChangesDlg changesDlg((wxWindow*) Manager::Get()->GetAppWindow(),0L);
    changesDlg.ShowModal();

    wxString changes = changesDlg.Changes();

    if (!changes.IsEmpty())
    {
        changes.Prepend(_T("        -"));
        changes.Replace(_T("\n"), _T("\n        -"));

        m_versionConfig.Open(m_versionConfigPath);

        long date = m_versionConfig.ReadValue( DATES );
        long major = m_versionConfig.ReadValue( MAJOR );
        long minor = m_versionConfig.ReadValue( MINOR );
        long build = m_versionConfig.ReadValue( BUILD_NUMBER );
        long revision = m_versionConfig.ReadValue( REVISION );
        long svn = m_versionConfig.ReadValue( SVN );
        wxString status = m_versionConfig.ReadString( STATUS );
        wxString statusAbbreviation = m_versionConfig.ReadString( STATUS_ABBREVIATION );
        wxString changesTitle = m_versionConfig.ReadString( CHANGES_TITLE );

        m_versionConfig.Close();

        wxDateTime actualDate = wxDateTime::Now();
        wxString value;

        changesTitle.Replace(_T("%d"),actualDate.Format(_T("%d")));
        changesTitle.Replace(_T("%o"),actualDate.Format(_T("%m")));
        changesTitle.Replace(_T("%y"),actualDate.Format(_T("%Y")));

        value.Printf(_T("%d"),major);
        changesTitle.Replace(_T("%M"),value);

        value.Printf(_T("%d"),minor);
        changesTitle.Replace(_T("%m"),value);

        value.Printf(_T("%d"),build);
        changesTitle.Replace(_T("%b"),value);

        value.Printf(_T("%d"),revision);
        changesTitle.Replace(_T("%r"),value);

        value.Printf(_T("%d"),svn);
        changesTitle.Replace(_T("%s"),value);

        changesTitle.Replace(_T("%T"),status);
        changesTitle.Replace(_T("%t"),statusAbbreviation);
        changesTitle.Replace(_T("%p"),project->GetTitle());


        wxString changesFile = project->GetBasePath() + _T("CHANGES.txt");
        wxString changesCurrentContent;
        if (wxFile::Exists(changesFile))
        {
            wxFFile file;

            file.Open(changesFile);
            file.ReadAll(&changesCurrentContent);
            file.Close();
        }

        wxString changesOutput = _T("");

        changesOutput << actualDate.Format(_T("%d %B %Y\n"));
        changesOutput << _T("   ") << changesTitle << _T("\n");
        changesOutput << _T("\n     Change log:\n");
        changesOutput << changes << _T("\n\n");
        changesOutput << changesCurrentContent;

        wxFile file;
        file.Open(changesFile,wxFile::write);
        file.Write(changesOutput);
        file.Close();

    }//If not changes.IsEmpty()
}
//}
