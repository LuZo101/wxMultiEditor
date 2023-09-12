#include "../include/MainFrame.hpp"
#include "../include/Logic.hpp"

enum ID
{
    PANEL = 3,
    INPUT_ASCII,
    INPUT_HEX,
    SIZER_PANEL
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
    sizerPanel = new wxBoxSizer(panel, SIZER_PANEL,);
    inputASCI = new wxTextCtrl(this, INPUT_ASCII, "Your Ascii Code hier", wxPoint(100, 10), wxSize(360, 580));
    inputHEX = new wxTextCtrl(this, INPUT_ASCII, "Your HEX Code hier", wxPoint(10, 10), wxSize(360, 580));
}

void MainFrame::CreateControls()
{
}
void MainFrame::BindEvtHandler()
{
}
