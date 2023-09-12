#include "../include/MainFrame.hpp"
#include "../include/Logic.hpp"

enum ID
{
    PANEL = 3,
    INPUT_ASCII,
    INPUT_HEX,
    SIZER_PANEL,
    MBAR,
    MBAR_FILE,
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
    inputASCI = new wxTextCtrl(panel, INPUT_ASCII, "Your Ascii Code hier", wxPoint(100, 10));
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

    mbarFile = new wxMenuItem(mbarMore, MBAR_FILE, "Save As..");
    mbarMore->Append(mbarFile);

    mbarAbout = new wxMenuItem(mbarMore, MBAR_ABOUT, "About");
    mbarMore->Append(mbarAbout);

    mbarQuit = new wxMenuItem(mbarMore, MBAR_QUIT, "Quit");
    mbarMore->Append(mbarQuit);
    mbar->Append(mbarMore, "More");
    SetMenuBar(mbar);
}
void MainFrame::CreateControls()
{
    SetupMenuBar();
}
void MainFrame::BindEvtHandler()
{
}
