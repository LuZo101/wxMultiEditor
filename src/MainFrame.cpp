#include "MainFrame.hpp"
#include "Logic.hpp"
#include <wx/filedlg.h>
#include <wx/txtstrm.h>

MainFrame::MainFrame(const wxString &title) : wxFrame(nullptr, wxID_ANY, title)
{
    SetupLayout();
    SetupMenuBar();
    BindEvtHandler();
}
// Set up the main layout of the frame
void MainFrame::SetupLayout()
{
    // Create and set up the panel
    panel = new wxPanel(this, PANEL);
    panel->SetBackgroundColour(wxColour(75, 184, 72));

    // Define the font for the text controls
    wxFont font(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);

    // Create ASCII input text control, set its font, and add a default value
    inputASCI = new wxTextCtrl(panel, INPUT_ASCII, "Your ASCII Code here");
    inputASCI->SetFont(font);

    // Create HEX input text control, set its font, and add a default value
    inputHEX = new wxTextCtrl(panel, INPUT_HEX, "Your HEX Code here");
    inputHEX->SetFont(font);

    // Create a vertical box sizer for the Comboboxes and text controls
    wxBoxSizer *sizerFrame = new wxBoxSizer(wxVERTICAL);

    // Create the "From" Combobox
    wxString conversionOptionsFrom[] = {"ASCII", "HEX", "DEC", "BIN", "OCT"};
    conversionFrom = new wxComboBox(panel, wxID_ANY, conversionOptionsFrom[0], wxDefaultPosition, wxDefaultSize, WXSIZEOF(conversionOptionsFrom), conversionOptionsFrom, wxCB_DROPDOWN);

    // Create the "To" Combobox
    wxString conversionOptionsTo[] = {"ASCII", "HEX", "DEC", "BIN", "OCT"};
    conversionTo = new wxComboBox(panel, wxID_ANY, conversionOptionsTo[1], wxDefaultPosition, wxDefaultSize, WXSIZEOF(conversionOptionsTo), conversionOptionsTo, wxCB_DROPDOWN);

    // Add the "From" Combobox under the ASCII input
    sizerFrame->Add(inputASCI, 1, wxEXPAND | wxALL, 5);
    sizerFrame->Add(conversionFrom, 0, wxEXPAND | wxALL, 5);

    // Add the "To" Combobox under the HEX input
    sizerFrame->Add(inputHEX, 1, wxEXPAND | wxALL, 5);
    sizerFrame->Add(conversionTo, 0, wxEXPAND | wxALL, 5);

    // Set the sizer for the panel and adjust its size to fit the contents
    panel->SetSizerAndFit(sizerFrame);
}


// Set up the menu bar
void MainFrame::SetupMenuBar()
{
    mbar = new wxMenuBar();
    mbarMore = new wxMenu();

    mbarMore->Append(ID::MBAR_SAVE, "Save As..");
    mbarMore->Append(ID::MBAR_ABOUT, "About");
    mbarMore->Append(ID::MBAR_QUIT, "Quit");

    mbar->Append(mbarMore, "More");
    SetMenuBar(mbar);
    ShortcutSetup();
}

// Bind events to their handlers
void MainFrame::BindEvtHandler()
{
    Bind(wxEVT_MENU, &MainFrame::OnSave, this, ID::MBAR_SAVE);
    Bind(wxEVT_MENU, &MainFrame::OnAbout, this, ID::MBAR_ABOUT);
    Bind(wxEVT_MENU, &MainFrame::OnQuit, this, ID::MBAR_QUIT);

    inputASCI->Bind(wxEVT_TEXT, &MainFrame::OnTextCtrlAsciiEnter, this, INPUT_ASCII);
    inputHEX->Bind(wxEVT_TEXT, &MainFrame::OnTextCtrlHexEnter, this, INPUT_HEX);
}
void MainFrame::OnSave(wxCommandEvent &)
{
    wxFileDialog saveFileDialog(this, _("Save MD file"), "", "", "MARKDOWN (*.md)|*.md", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);

    if (saveFileDialog.ShowModal() != wxID_CANCEL)
    {
        wxFileOutputStream output_stream(saveFileDialog.GetPath());
        if (!output_stream.IsOk())
        {
            wxLogError("Cannot save current contents in file '%s'.", saveFileDialog.GetPath());
            return;
        }

        wxString asciiData = inputASCI->GetValue();
        wxString hexData = inputHEX->GetValue();

        wxString formattedContent = Logic::FormatData(asciiData, hexData);

        wxTextOutputStream textStream(output_stream);
        textStream << formattedContent;
    }
}

// About event handler
void MainFrame::OnAbout(wxCommandEvent &)
{
    wxMessageDialog dialog(this, "wxEditor, transform ASCII to HEX, DEZ, BIN\nby LuZo101", "About this Program", wxICON_QUESTION);
    dialog.ShowModal();
}

// Quit event handler
void MainFrame::OnQuit(wxCommandEvent &)
{
    Close(true);
}

void MainFrame::OnTextCtrlAsciiEnter(wxCommandEvent &event)
{
    if (!isUpdatingHex)
    {
        isUpdatingAscii = true;
        wxString asciiText = inputASCI->GetValue();
        wxString hexValue = Logic::StringToHex(asciiText);

        if (!hexValue.IsEmpty()) // Check if the conversion was successful
        {
            inputHEX->SetValue(hexValue);
            lastValidASCI = asciiText; // Store the last valid ASCII input
            lastValidHEX = hexValue;   // Store the corresponding HEX value
        }
        else
        {
            inputASCI->SetValue(lastValidASCI); // Restore the last valid ASCII input
        }

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

        if (Logic::IsHexInput(hexText))
        {
            wxString asciiValue = Logic::HexToString(hexText);
            inputASCI->SetValue(asciiValue);
            lastValidHEX = hexText;     // Store the last valid HEX input
            lastValidASCI = asciiValue; // Store the corresponding ASCII value
        }
        else
        {
            wxMessageBox("Invalid HEX!", "Error", wxOK | wxICON_ERROR);
            inputHEX->SetValue(lastValidHEX); // Restore the last valid HEX input
        }

        isUpdatingHex = false;
    }
    event.Skip();
}

void MainFrame::ShortcutSetup()
{
    wxAcceleratorEntry entries[2];
    entries[0].Set(wxACCEL_SHIFT | wxACCEL_CTRL, (int)'S', ID::MBAR_SAVE);
    entries[1].Set(wxACCEL_CTRL, (int)'Q', ID::MBAR_QUIT);
    wxAcceleratorTable accel(2, entries);
    SetAcceleratorTable(accel);
}
