#ifndef MAINFRAME_HPP
#define MAINFRAME_HPP

#include <wx/wx.h>
#include <cstdint>
#include <vector>
#include <fstream>
class MainFrame : public wxFrame
{
private:
    wxPanel *panel;
    wxMenuBar *mbar;
    wxMenu *mbarMore;
    wxMenuItem *mbarFile;
    wxMenuItem *mbarAbout;
    wxMenuItem *mbarQuit;

    wxTextCtrl *inputASCI;
    wxTextCtrl *inputHEX;
    wxBoxSizer *sizerFrame;

    void CreateControls();
    void BindEvtHandler();
    void SetupLayout();

    void SetupMenuBar();

public:
    MainFrame(const wxString &title);
};

#endif