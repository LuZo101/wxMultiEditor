#include "../include/MainFrame.hpp"
#include "../include/Logic.hpp"
#include <wx/filedlg.h>
enum ID
{
    PANEL = 3,
    INPUT_ASCII,
    INPUT_HEX,
    SIZER_PANEL,
    MBAR,
    MBAR_SAVE,
    MBAR_ABOUT,
    MBAR_QUIT
};
MainFrame::MainFrame(const wxString &title) : wxFrame(nullptr, wxID_ANY, title)
{
    BindEvtHandler();
    SetupLayout();
    CreateControls();
}
void MainFrame::SetupLayout()
{
    panel = new wxPanel(this, PANEL, wxDefaultPosition, wxDefaultSize);
    panel->SetBackgroundColour(wxColour(75, 184, 72));

    // Create inputASCI and inputHEX after creating the panel
    inputASCI = new wxTextCtrl(panel, INPUT_ASCII, "Your Ascii Code hier", wxPoint(100, 10), wxSize(-1, 33));
    inputHEX = new wxTextCtrl(panel, INPUT_ASCII, "Your HEX Code hier", wxPoint(10, 10));

    // Create sizer and add controls to it
    sizerFrame = new wxBoxSizer(wxVERTICAL);
    sizerFrame->Add(inputASCI, 1, wxEXPAND, 5);
    sizerFrame->Add(inputHEX, 1, wxEXPAND, 5);
    // Set the panel's sizer
    panel->SetSizer(sizerFrame);
}
void MainFrame::SetupMenuBar()
{
    // create mbar
    mbar = new wxMenuBar();
    mbarMore = new wxMenu();

    mbarFile = new wxMenuItem(mbarMore, MBAR_SAVE, "Save As..");
    mbarMore->Append(mbarFile);

    mbarAbout = new wxMenuItem(mbarMore, MBAR_ABOUT, "About");
    mbarMore->Append(mbarAbout);

    mbarQuit = new wxMenuItem(mbarMore, MBAR_QUIT, "Quit");
    mbarMore->Append(mbarQuit);
    mbar->Append(mbarMore, "More");
    SetMenuBar(mbar);
    ShortcutSetup();
}
void MainFrame::CreateControls()
{
    SetupMenuBar();
}
void MainFrame::BindEvtHandler()
{
    this->Bind(wxEVT_MENU, &MainFrame::OnSave, this, MBAR_SAVE);
    this->Bind(wxEVT_MENU, &MainFrame::OnAbout, this, MBAR_ABOUT);
    this->Bind(wxEVT_MENU, &MainFrame::OnClose, this, MBAR_QUIT);
}
void MainFrame::OnSave(wxCommandEvent &WXUNUSED(event))
{
    wxFileDialog
        saveFileDialog(this, _("Save MD file"), "", "",
                       "MARKDOWN (*.md)|*.md", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
    if (saveFileDialog.ShowModal() == wxID_CANCEL)
        return; // the user changed idea...

    // save the current contents in the file;
    // this can be done with e.g. wxWidgets output streams:
    wxFileOutputStream output_stream(saveFileDialog.GetPath());
    if (!output_stream.IsOk())
    {
        wxLogError("Cannot save current contents in file '%s'.", saveFileDialog.GetPath());
        return;
    }
}

void MainFrame::OnAbout(wxCommandEvent &evt)
{
    wxMessageDialog dialog(this, wxString("wxEditor, transform ASCII in HEX, DEZ, BIN\nby LuZo101"), "About this Program", wxICON_QUESTION);
    dialog.ShowModal();
}

void MainFrame::OnClose(wxCommandEvent &evt)
{
    wxMessageDialog dialog(this, wxString("CIAO"), "C U ", wxICON_STOP);

    dialog.ShowModal();
    evt.Skip();

    this->Close(true);
}

void MainFrame::ShortcutSetup()
{
    wxAcceleratorEntry entries[2];
    entries[0].Set(wxACCEL_SHIFT | wxACCEL_CTRL, (int)'S', MBAR_SAVE);
    entries[1].Set(wxACCEL_CTRL, (int)'Q', MBAR_QUIT);
    wxAcceleratorTable accel(2, entries);
    this->SetAcceleratorTable(accel);
}