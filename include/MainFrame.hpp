#ifndef MAINFRAME_HPP
#define MAINFRAME_HPP

#include <wx/wx.h>
#include <wx/menu.h>
#include <wx/panel.h>
#include <wx/textctrl.h>
#include <wx/combobox.h>
#include "Logic.hpp"
#include <wx/textctrl.h>
#include <wx/file.h>
#include <wx/textfile.h>
#include <wx/wfstream.h>
class MainFrame : public wxFrame
{
public:
    MainFrame(const wxString &title);

private:
    wxPanel *panel;
    wxTextCtrl *inputUp;
    wxTextCtrl *inputDown;
    wxComboBox *conversionFrom;
    wxComboBox *conversionTo;
    wxMenuBar *mbar;
    wxMenu *mbarMore;

    enum TextCtrlType
    {
        TEXT_CTRL_INPUT_UP,
        TEXT_CTRL_INPUT_DOWN
    };

    TextCtrlType currentTextCtrl;
    bool isUpdatingUp = false;
    bool isUpdatingDown = false;
    wxString lastValidASCI;
    wxString lastValidHEX;

    void SetupLayout();
    void SetupMenuBar();
    void BindEvtHandler();
    void OnSave(wxCommandEvent &);
    void OnAbout(wxCommandEvent &);
    void OnQuit(wxCommandEvent &);
    void OnTextCtrlChange(wxCommandEvent &event);
    void OnTextCtrlUpEnter(wxCommandEvent &event);
    void OnTextCtrlDownEnter(wxCommandEvent &event);
    void ShortcutSetup();
    void OnConversionFromChanged(wxCommandEvent &event);
    void OnConversionToChanged(wxCommandEvent &event);
    void ConvertAndUpdate();

    // Define enum for custom event IDs (if needed)
    enum ID
    {
        MBAR_SAVE = wxID_HIGHEST + 1,
        MBAR_ABOUT,
        MBAR_QUIT,
        INPUT_DOWN,
        INPUT_UP,
        PANEL,
        CB_UP,
        CB_DOWN
    };
};

#endif // MAINFRAME_HPP
