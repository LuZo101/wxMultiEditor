#ifndef MAINFRAME_HPP
#define MAINFRAME_HPP
#include <wx/wfstream.h>
#include <wx/filedlg.h>
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
    void ShortcutSetup();
    void SetupLayout();
    void SetupMenuBar();
    void BindEvtHandler();

    void OnSave(wxCommandEvent &WXUNUSED(event));
    void OnAbout(wxCommandEvent &evt);
    void OnQuit(wxCommandEvent &evt);

    void OnTextCtrlAsciiEnter(wxCommandEvent &event);
    void OnTextCtrlHexEnter(wxCommandEvent &event);

    wxString StringToHex(const wxString &input);
    wxString HexToString(const wxString &input);

    wxString lastValidHex;
    bool isUpdatingAscii = false;
    bool isUpdatingHex= false;

    bool IsASCIIInput(wxChar c);
    bool IsHexInput(const wxString &input);

public:
    MainFrame(const wxString &title);
};

#endif