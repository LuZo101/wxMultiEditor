#ifndef MAINFRAME_HPP
#define MAINFRAME_HPP

#include <wx/wfstream.h>
#include <wx/filedlg.h>
#include <wx/wx.h>
#include <cstdint>
#include <vector>
#include <fstream>
#include <wx/txtstrm.h>

enum ID
{
    PANEL = 3,
    INPUT_ASCII,
    INPUT_HEX,
    MBAR_SAVE,
    MBAR_ABOUT,
    MBAR_QUIT
};

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

    wxComboBox *conversionFrom;
    wxComboBox *conversionTo;

    void CreateControls();
    void ShortcutSetup();
    void SetupLayout();
    void SetupMenuBar();
    void BindEvtHandler();

    void OnSave(wxCommandEvent &WXUNUSED(event));
    void OnAbout(wxCommandEvent &evt);
    void OnQuit(wxCommandEvent &evt);

    void OnTextCtrlAsciiEnter(wxCommandEvent &event);
    void OnTextCtrlHexEnter(wxCommandEvent &event);

    wxString lastValidASCI;
    wxString lastValidHEX;
    bool isUpdatingAscii = false;
    bool isUpdatingHex = false;

public:
    MainFrame(const wxString &title);
};

#endif
