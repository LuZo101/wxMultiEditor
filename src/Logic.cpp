#include "Logic.hpp"

wxString Logic::StringToHex(const wxString &input)
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
        // Handle invalid ASCII here
        return "";
    }

    return hex;
}

wxString Logic::HexToString(const wxString &input)
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

bool Logic::IsASCIIInput(wxChar c)
{
    return c < 128;
}

bool Logic::IsHexInput(const wxString &input)
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

wxString Logic::FormatData(const wxString &ascii, const wxString &hex)
{
    wxString formattedContent;
    formattedContent += "ASCII:\n________\n";
    formattedContent += ascii;
    formattedContent += "\n\nHEX:\n_________\n";
    formattedContent += hex;

    return formattedContent;
}
