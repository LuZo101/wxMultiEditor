#include "MainFrame.hpp"
#include "Logic.hpp"
#include <wx/filedlg.h>

enum ID
{
    PANEL = 3,
    INPUT_ASCII,
    INPUT_HEX,
    MBAR_SAVE,
    MBAR_ABOUT,
    MBAR_QUIT
};

MainFrame::MainFrame(const wxString &title) : wxFrame(nullptr, wxID_ANY, title)
{
    SetupLayout();
    SetupMenuBar();
    BindEvtHandler();
}

void MainFrame::SetupLayout()
{
    panel = new wxPanel(this, PANEL, wxDefaultPosition, wxDefaultSize);
    panel->SetBackgroundColour(wxColour(75, 184, 72));

    inputASCI = new wxTextCtrl(panel, INPUT_ASCII, "Your ASCII Code here", wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER);
    inputHEX = new wxTextCtrl(panel, INPUT_HEX, "Your HEX Code here", wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER);

    wxBoxSizer *sizerFrame = new wxBoxSizer(wxVERTICAL);
    sizerFrame->Add(inputASCI, 1, wxEXPAND | wxALL, 5);
    sizerFrame->Add(inputHEX, 1, wxEXPAND | wxALL, 5);

    panel->SetSizerAndFit(sizerFrame);
}

void MainFrame::SetupMenuBar()
{
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

void MainFrame::BindEvtHandler()
{
    Bind(wxEVT_MENU, &MainFrame::OnSave, this, MBAR_SAVE);
    Bind(wxEVT_MENU, &MainFrame::OnAbout, this, MBAR_ABOUT);
    Bind(wxEVT_MENU, &MainFrame::OnQuit, this, MBAR_QUIT);

    inputASCI->Bind(wxEVT_TEXT, &MainFrame::OnTextCtrlAsciiEnter, this, INPUT_ASCII);
    inputHEX->Bind(wxEVT_TEXT, &MainFrame::OnTextCtrlHexEnter, this, INPUT_HEX);
}

void MainFrame::OnSave(wxCommandEvent &WXUNUSED(event))
{
    wxFileDialog saveFileDialog(this, _("Save MD file"), "", "", "MARKDOWN (*.md)|*.md", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);

    if (saveFileDialog.ShowModal() == wxID_CANCEL)
        return;

    wxFileOutputStream output_stream(saveFileDialog.GetPath());

    if (!output_stream.IsOk())
    {
        wxLogError("Cannot save current contents in file '%s'.", saveFileDialog.GetPath());
        return;
    }
}

void MainFrame::OnAbout(wxCommandEvent &evt)
{
    wxMessageDialog dialog(this, wxString("wxEditor, transform ASCII to HEX, DEZ, BIN\nby LuZo101"), "About this Program", wxICON_QUESTION);
    dialog.ShowModal();
}

void MainFrame::OnQuit(wxCommandEvent &evt)
{
    Close(true);
}

void MainFrame::OnTextCtrlAsciiEnter(wxCommandEvent &event)
{
    if (!isUpdatingHex)
    {
        isUpdatingAscii = true;
        wxString asciiText = inputASCI->GetValue();
        inputHEX->SetValue(StringToHex(asciiText));
        isUpdatingAscii = false;
    }
    event.Skip();
}

void MainFrame::OnTextCtrlHexEnter(wxCommandEvent &event)
{
    if (!isUpdatingAscii)
    {
        isUpdatingHex = true;
        wxString hexText = inputHEX->GetValue();

        if (IsHexInput(hexText))
        {
            inputASCI->SetValue(HexToString(hexText));
        }
        else
        {
            wxMessageBox("Invalid HEX!", "Error", wxOK | wxICON_ERROR);
        }
        isUpdatingHex = false;
    }
    event.Skip();
}


wxString MainFrame::StringToHex(const wxString &input)
{
    wxString hex;
    bool hasInvalidASCII = false;

    for (size_t i = 0; i < input.length(); i++)
    {
        wxChar c = input[i];

        if (IsASCIIInput(c))
        {
            hex += wxString::Format("%02X ", static_cast<unsigned int>(c));
        }
        else
        {
            hasInvalidASCII = true;
            break;
        }
    }

    if (hasInvalidASCII)
    {
        wxMessageBox("Invalid ASCII!", "Error", wxOK | wxICON_ERROR);
    }

    return hex;
}

wxString MainFrame::HexToString(const wxString &input)
{
    wxString text;
    wxString cleanedInput = input;
    cleanedInput.Replace(" ", "");

    size_t inputLen = cleanedInput.length();
    size_t numPairs = inputLen / 2;

    for (size_t i = 0; i < numPairs; i++)
    {
        wxString hex = cleanedInput.Mid(i * 2, 2);
        long value;

        if (hex.ToLong(&value, 16))
        {
            text += static_cast<wxChar>(value);
        }
    }

    return text;
}

bool MainFrame::IsASCIIInput(wxChar c)
{
    return c < 128;
}

bool MainFrame::IsHexInput(const wxString &input)
{
    wxString hexChars = "0123456789ABCDEFabcdef ";

    for (size_t i = 0; i < input.length(); i++)
    {
        wxChar c = input[i];

        if (hexChars.Find(c) == wxString::npos)
        {
            return false;
        }
    }

    return true;
}

void MainFrame::ShortcutSetup()
{
    wxAcceleratorEntry entries[2];
    entries[0].Set(wxACCEL_SHIFT | wxACCEL_CTRL, (int)'S', MBAR_SAVE);
    entries[1].Set(wxACCEL_CTRL, (int)'Q', MBAR_QUIT);
    wxAcceleratorTable accel(2, entries);
    SetAcceleratorTable(accel);
}
