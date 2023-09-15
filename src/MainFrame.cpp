#include "MainFrame.hpp"
#include "Logic.hpp"
#include <wx/filedlg.h>
#include <wx/txtstrm.h>
#include <wx/file.h>
MainFrame::MainFrame(const wxString &title) : wxFrame(nullptr, wxID_ANY, title)
{
    SetupLayout();
    SetupMenuBar();
    BindEvtHandler();
}

void MainFrame::SetupLayout()
{
    // Create and set up the panel
    panel = new wxPanel(this, PANEL);
    panel->SetBackgroundColour(wxColour(75, 184, 72));

    // Define the font for the text controls
    wxFont font(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);

    // Create "Input Up" text control, set its font, and add a default value
    inputUp = new wxTextCtrl(panel, INPUT_UP, "Your ASCII Code here");
    inputUp->SetFont(font);

    // Create "Input Down" text control, set its font, and add a default value
    inputDown = new wxTextCtrl(panel, INPUT_DOWN, "Your HEX Code here");
    inputDown->SetFont(font);

    // Create a vertical box sizer for the ComboBoxes and text controls
    wxBoxSizer *sizerFrame = new wxBoxSizer(wxVERTICAL);

    // Create the "From" ComboBox
    wxString conversionOptions[] = {"ASCII", "HEX", "DEC", "BIN", "OCT"};
    conversionFrom = new wxComboBox(panel, wxID_ANY, conversionOptions[0], wxDefaultPosition, wxDefaultSize, WXSIZEOF(conversionOptions), conversionOptions, wxCB_DROPDOWN);

    // Create the "To" ComboBox
    conversionTo = new wxComboBox(panel, wxID_ANY, conversionOptions[1], wxDefaultPosition, wxDefaultSize, WXSIZEOF(conversionOptions), conversionOptions, wxCB_DROPDOWN);

    // Add the "Input Up" text control and "From" ComboBox
    sizerFrame->Add(inputUp, 1, wxEXPAND | wxALL, 5);
    sizerFrame->Add(conversionFrom, 0, wxEXPAND | wxALL, 5);

    // Add the "Input Down" text control and "To" ComboBox
    sizerFrame->Add(inputDown, 1, wxEXPAND | wxALL, 5);
    sizerFrame->Add(conversionTo, 0, wxEXPAND | wxALL, 5);

    // Set the sizer for the panel and adjust its size to fit the contents
    panel->SetSizerAndFit(sizerFrame);
}

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
void MainFrame::BindEvtHandler()
{
    // Bind wxEVT_TEXT to a single event handler for all TextCtrl elements
    inputUp->Bind(wxEVT_TEXT, &MainFrame::OnTextCtrlChange, this, INPUT_UP);
    inputDown->Bind(wxEVT_TEXT, &MainFrame::OnTextCtrlChange, this, INPUT_DOWN);

    Bind(wxEVT_MENU, &MainFrame::OnSave, this, ID::MBAR_SAVE);
    Bind(wxEVT_MENU, &MainFrame::OnAbout, this, ID::MBAR_ABOUT);
    Bind(wxEVT_MENU, &MainFrame::OnQuit, this, ID::MBAR_QUIT);

    // Bind wxEVT_COMBOBOX for conversionFrom and conversionTo
    conversionFrom->Bind(wxEVT_COMBOBOX, &MainFrame::OnConversionFromChanged, this);
    conversionTo->Bind(wxEVT_COMBOBOX, &MainFrame::OnConversionToChanged, this);
}

void MainFrame::OnSave(wxCommandEvent &)
{
    wxFileDialog saveFileDialog(this, _("Save MD file"), "", "", "MARKDOWN (*.md)|*.md", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);

    if (saveFileDialog.ShowModal() != wxID_CANCEL)
    {
        // Hier die Konvertierung von wxString zu std::string durchführen
        std::string filePath = std::string(saveFileDialog.GetPath());

        wxTextFile textFile;
        if (textFile.Create(filePath))
        {
            for (int i = 0; i < 10; i++) // Beispiel: Schreibe 10 Zeilen in die Datei
            {
                textFile.AddLine(wxString::Format("Zeile %d", i));
            }
            textFile.Write();
        }
        else
        {
            wxLogError("Fehler beim Erstellen der Datei.");
        }

        wxString inputUData = inputUp->GetValue();
        wxString inputDData = inputDown->GetValue();

        // Holen Sie die aktuellen Werte der ComboBoxes
        wxString from = conversionFrom->GetStringSelection();
        wxString to = conversionTo->GetStringSelection();

        // Passen Sie den Aufruf von Logic::FormatData an, um die zusätzlichen Parameter zu übergeben
        wxString formattedContent = Logic::FormatData(inputUData, inputDData, from, to);

        // Hier sollte der Text in die Datei geschrieben werden
        wxFileOutputStream output_stream(filePath);
        wxTextOutputStream textStream(output_stream);
        textStream << formattedContent;
    }
}

void MainFrame::OnAbout(wxCommandEvent &)
{
    wxMessageDialog dialog(this, "wxEditor, transform ASCII to HEX, DEZ, BIN\nby LuZo101", "About this Program", wxICON_QUESTION);
    dialog.ShowModal();
}

void MainFrame::OnQuit(wxCommandEvent &)
{
    Close(true);
}

void MainFrame::OnTextCtrlChange(wxCommandEvent &event)
{
    wxTextCtrl *sourceCtrl = wxDynamicCast(event.GetEventObject(), wxTextCtrl);

    if (sourceCtrl)
    {
        if (sourceCtrl == inputUp)
        {
            currentTextCtrl = TextCtrlType::TEXT_CTRL_INPUT_UP;
            OnTextCtrlUpEnter(event);
        }
        else if (sourceCtrl == inputDown)
        {
            currentTextCtrl = TextCtrlType::TEXT_CTRL_INPUT_DOWN;
            OnTextCtrlDownEnter(event);
        }
    }
    wxString text = sourceCtrl->GetValue();
    event.Skip();
}

void MainFrame::OnTextCtrlUpEnter(wxCommandEvent &event)
{
    if (!isUpdatingDown)
    {
        isUpdatingUp = true;

        wxString from = conversionFrom->GetStringSelection();
        wxString to = conversionTo->GetStringSelection();

        wxString upText = inputUp->GetValue();
        wxString downValue;

        if (from == "ASCII" && to == "HEX")
        {
            downValue = Logic::StringToHex(upText);
        }
        else if (from == "ASCII" && to == "DEC")
        {
            downValue = Logic::StringToDec(upText);
        }
        else if (from == "ASCII" && to == "BIN")
        {
            downValue = Logic::StringToBin(upText);
        }
        else if (from == "ASCII" && to == "OCT")
        {
            downValue = Logic::StringToOct(upText);
        }
        // ... (fügen Sie hier weitere Kombinationen hinzu)

        if (!downValue.IsEmpty())
        {
            inputDown->ChangeValue(downValue);
            lastValidASCI = upText;
            lastValidHEX = downValue; // Sie sollten hier auch andere lastValid Variablen entsprechend aktualisieren
        }
        else
        {
            inputUp->ChangeValue(lastValidASCI);
        }

        isUpdatingUp = false;
    }
    event.Skip();
}

void MainFrame::OnTextCtrlDownEnter(wxCommandEvent &event)
{
    if (!isUpdatingUp)
    {
        isUpdatingDown = true;

        wxString from = conversionFrom->GetStringSelection();
        wxString to = conversionTo->GetStringSelection();

        wxString downText = inputDown->GetValue();
        wxString upValue;

        if (from == "HEX" && to == "ASCII")
        {
            upValue = Logic::HexToString(downText);
        }
        else if (from == "DEC" && to == "ASCII")
        {
            upValue = Logic::DecToString(downText);
        }
        else if (from == "BIN" && to == "ASCII")
        {
            upValue = Logic::BinToString(downText);
        }
        else if (from == "OCT" && to == "ASCII")
        {
            upValue = Logic::OctToString(downText);
        }
        // ... (fügen Sie hier weitere Kombinationen hinzu)

        if (!upValue.IsEmpty())
        {
            inputUp->ChangeValue(upValue);
            lastValidASCI = upValue; // Sie sollten hier auch andere lastValid Variablen entsprechend aktualisieren
            lastValidHEX = downText;
        }
        else
        {
            wxMessageBox("Invalid input!", "Error", wxOK | wxICON_ERROR);
            inputDown->ChangeValue(lastValidHEX); // Sie sollten hier auch andere lastValid Variablen entsprechend aktualisieren
        }

        isUpdatingDown = false;
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
void MainFrame::OnConversionFromChanged(wxCommandEvent &event)
{
    wxString from = conversionFrom->GetStringSelection();
    wxString to = conversionTo->GetStringSelection();

    wxLogMessage("Conversion from changed: From: %s, To: %s", from, to);

    ConvertAndUpdate();
}

void MainFrame::OnConversionToChanged(wxCommandEvent &event)
{
    wxString from = conversionFrom->GetStringSelection();
    wxString to = conversionTo->GetStringSelection();

    wxLogMessage("Conversion to changed: From: %s, To: %s", from, to);

    ConvertAndUpdate();
}
void MainFrame::ConvertAndUpdate()
{
    wxString from = conversionFrom->GetStringSelection();
    wxString to = conversionTo->GetStringSelection();

    // Debugging-Ausgaben
    wxLogMessage("From: %s, To: %s", from, to);

    wxString input;
    wxString output;

    if (from == "ASCII")
    {
        input = inputUp->GetValue();
    }
    else if (from == "HEX")
    {
        input = inputDown->GetValue();
    }

    // Debugging-Ausgaben
    wxLogMessage("Input: %s", input);

    // Verwenden Sie die ConvertNumberSystem-Funktion, um die Konvertierung durchzuführen
    output = Logic::ConvertNumberSystem(input, from, to);

    // Debugging-Ausgaben
    wxLogMessage("Output: %s", output);

    if (to == "ASCII")
    {
        inputUp->SetValue(output);
    }
    else if (to == "HEX")
    {
        inputDown->SetValue(output);
    }
}

