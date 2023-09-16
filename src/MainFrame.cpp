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
    inputUp = new wxTextCtrl(panel, INPUT_UP, "Your ASCII Code here", wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER);
    inputUp->SetFont(font);

    // Create "Input Down" text control, set its font, and add a default value
    inputDown = new wxTextCtrl(panel, INPUT_DOWN, "Your DEC Code here", wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER);
    inputDown->SetFont(font);

    // Create a vertical box sizer for the ComboBoxes and text controls
    wxBoxSizer *sizerFrame = new wxBoxSizer(wxVERTICAL);

    // Create the "From" ComboBox
    wxString conversionOptions[] = {"ASCII", "DEC", "BIN", "OCT", "HEX"};
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
    conversionFrom->SetSelection(0); // Wähle den ersten Eintrag aus (z. B. "ASCII") als Standardwert.
    conversionTo->SetSelection(1);   // Wähle den zweiten Eintrag aus (z. B. "HEX") als Standardwert.

    Bind(wxEVT_MENU, &MainFrame::OnSave, this, ID::MBAR_SAVE);
    Bind(wxEVT_MENU, &MainFrame::OnAbout, this, ID::MBAR_ABOUT);
    Bind(wxEVT_MENU, &MainFrame::OnQuit, this, ID::MBAR_QUIT);
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
        Logic logic;

        Logic::ConversionResult conversionResult = logic.FormatData(inputUData, inputDData, from, to);

        // Hier sollte der Text in die Datei geschrieben werden
        wxFileOutputStream output_stream(filePath);
        wxTextOutputStream textStream(output_stream);

        // Schreibe den formatierten Inhalt in die Datei
        textStream << "Input:\n" << conversionResult.input << "\n\nOutput:\n" << conversionResult.output;

        if (output_stream.IsOk())
        {
            wxLogMessage("Datei erfolgreich gespeichert: %s", filePath.c_str());
        }
        else
        {
            wxLogError("Fehler beim Schreiben in die Datei.");
        }
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
        if (sourceCtrl == inputUp && !isUpdatingDown)
        {
            isUpdatingUp = true;
            ConvertAndUpdate();
            isUpdatingUp = false;
        }
        else if (sourceCtrl == inputDown && !isUpdatingUp)
        {
            isUpdatingDown = true;
            ConvertAndUpdate();
            isUpdatingDown = false;
        }
    }
    event.Skip();
}

void MainFrame::UpdateValues(const wxString &input, const wxString &from, const wxString &to, wxTextCtrl *inputToUpdate, wxString &lastValidInput, wxString &lastValidOutput)
{
    Logic logic;

    wxString convertedValue;
    if (inputToUpdate == inputUp)
    {
        convertedValue = logic.ConvertNumberSystemUp(input, from, to);
    }
    else
    {
        convertedValue = logic.ConvertNumberSystemDown(input, from, to);
    }
    wxLogMessage("Conversion: From: %s, To: %s, Input: %s, Output: %s", from, to, input, convertedValue);

    if (!convertedValue.IsEmpty())
    {
        inputToUpdate->ChangeValue(convertedValue);
        lastValidInput = input;
        lastValidOutput = convertedValue;
    }
    else
    {
        inputToUpdate->ChangeValue(lastValidInput);
    }
}

void MainFrame::OnTextCtrlUpEnter(wxCommandEvent &event)
{
    if (isUpdatingDown)
        return;

    isUpdatingUp = true;

    wxString from = conversionFrom->GetStringSelection();
    wxString to = conversionTo->GetStringSelection();
    wxString upText = inputUp->GetValue();

    UpdateValues(upText, from, to, inputDown, lastValidASCI, lastValidHEX);

    isUpdatingUp = false;
    event.Skip();
}
void MainFrame::OnTextCtrlDownEnter(wxCommandEvent &event)
{
    if (isUpdatingUp)
        return;

    isUpdatingDown = true;

    wxString from = conversionTo->GetStringSelection(); // Hier habe ich die Zuweisungen angepasst
    wxString to = conversionFrom->GetStringSelection(); // Hier habe ich die Zuweisungen angepasst
    wxString downText = inputDown->GetValue();

    UpdateValues(downText, from, to, inputUp, lastValidHEX, lastValidASCI);

    isUpdatingDown = false;
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

    wxString input, output;

    if (currentTextCtrl == TEXT_CTRL_INPUT_UP)
    {
        input = inputUp->GetValue();
    }
    else if (currentTextCtrl == TEXT_CTRL_INPUT_DOWN)
    {
        input = inputDown->GetValue();
    }

    Logic logic;
    output = logic.ConvertNumberSystem(input, from, to);

    if (currentTextCtrl == TEXT_CTRL_INPUT_UP)
    {
        inputDown->ChangeValue(output);
    }
    else if (currentTextCtrl == TEXT_CTRL_INPUT_DOWN)
    {
        inputUp->ChangeValue(output);
    }
}
