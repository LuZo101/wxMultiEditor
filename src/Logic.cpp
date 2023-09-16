#include "Logic.hpp"

struct PairComparator
{
    bool operator()(const std::pair<wxString, wxString> &a, const std::pair<wxString, wxString> &b) const
    {
        return a.first < b.first || (a.first == b.first && a.second < b.second);
    }
};
wxString Logic::ConvertNumberSystemUp(const wxString &from, const wxString &to, const wxString &inputUp)
{    return ConvertNumberSystem(inputUp, from, to);
}

wxString Logic::ConvertNumberSystemDown(const wxString &to, const wxString &from, const wxString &inputDown)
{
     return ConvertNumberSystem(inputDown, from, to);
}

wxString Logic::ConvertNumberSystem(const wxString &input, const wxString &from, const wxString &to)
{
    if (from == to)
    {
        return input;
    }

    using ConverterFunc = std::function<wxString(const wxString &)>;

    std::map<std::pair<wxString, wxString>, ConverterFunc, PairComparator> converters = {
        {{"ASCII", "HEX"}, [](const wxString &s) -> wxString
         { return StringToHex(s); }},
        {{"HEX", "ASCII"}, [](const wxString &s) -> wxString
         { return HexToString(s); }},
        {{"ASCII", "DEC"}, [](const wxString &s) -> wxString
         { return StringToDec(s); }},
        {{"DEC", "ASCII"}, [](const wxString &s) -> wxString
         { return DecToString(s); }},
        {{"ASCII", "BIN"}, [](const wxString &s) -> wxString
         { return StringToBin(s); }},
        {{"BIN", "ASCII"}, [](const wxString &s) -> wxString
         { return BinToString(s); }},
        {{"ASCII", "OCT"}, [](const wxString &s) -> wxString
         { return StringToOct(s); }},
        {{"OCT", "ASCII"}, [](const wxString &s) -> wxString
         { return OctToString(s); }},
        {{"DEC", "BIN"}, [](const wxString &s) -> wxString
         { return BaseToBase(s, 10, 2); }},
        {{"BIN", "DEC"}, [](const wxString &s) -> wxString
         { return BaseToBase(s, 2, 10); }},
        {{"DEC", "OCT"}, [](const wxString &s) -> wxString
         { return BaseToBase(s, 10, 8); }},
        {{"OCT", "DEC"}, [](const wxString &s) -> wxString
         { return BaseToBase(s, 8, 10); }},
        {{"HEX", "BIN"}, [](const wxString &s) -> wxString
         { return BaseToBase(s, 16, 2); }},
        {{"BIN", "HEX"}, [](const wxString &s) -> wxString
         { return BaseToBase(s, 2, 16); }},
    };

    auto it = converters.find({from, to});
    return (it != converters.end()) ? it->second(input) : "";
}

wxString Logic::FormatData(const wxString &inputUData, const wxString &inputDData, const wxString &from, const wxString &to)
{
    wxString formattedData;

    // Hier kannst du deine Formatierungslogik implementieren
    // Verwende die Eingabedaten (inputUData und inputDData), das Ursprungsformat (from) und das Zielformat (to), um die Daten zu formatieren.

    // Beispiel:
    if (from == "HEX" && to == "ASCII")
    {
        // Implementiere die Umwandlung von HEX zu ASCII
        formattedData = HexToString(inputUData);
    }
    else if (from == "ASCII" && to == "HEX")
    {
        // Implementiere die Umwandlung von ASCII zu HEX
        formattedData = StringToHex(inputUData);
    }
    // Füge weitere Formatierungsfälle hinzu, wie du sie benötigst.

    return formattedData;
}

wxString Logic::BaseToBase(const wxString &input, int fromBase, int toBase)
{
    long value;
    if (wxString(input).ToLong(&value, fromBase))
    {
        // Umwandlung von einer Basis in eine andere
        wxString result;
        result.Printf(wxT("%ld"), value);
        if (toBase == 16)
        {
            result = wxString::Format(wxT("%X"), value);
        }
        else if (toBase == 8)
        {
            result = wxString::Format(wxT("%o"), value);
        }
        else if (toBase == 2)
        {
            result = wxString::Format(wxT("%b"), value);
        }
        return result;
    }
    return "";
}

wxString Logic::StringToHex(const wxString &input)
{
    wxString hex;
    for (size_t i = 0; i < input.length(); i++)
    {
        hex += wxString::Format("%02X ", static_cast<unsigned int>(input[i]));
    }
    return hex;
}

wxString Logic::HexToString(const wxString &input)
{
    wxString text;
    wxStringTokenizer tokenizer(input, " ");
    while (tokenizer.HasMoreTokens())
    {
        wxString token = tokenizer.GetNextToken();
        long value;
        if (token.ToLong(&value, 16))
        {
            text += static_cast<wxChar>(value);
        }
        else
        {
            // Fehlermeldung für ungültige hexadezimale Zeichenfolge
            wxLogError("Ungültige hexadezimale Zeichenfolge: %s", token);
        }
    }
    return text;
}

wxString Logic::StringToDec(const wxString &input)
{
    wxString dec;
    for (size_t i = 0; i < input.length(); i++)
    {
        wxChar c = input[i];
        if (c < 128)
        {
            dec += wxString::Format("%d ", static_cast<int>(c));
        }
    }
    return dec;
}

wxString Logic::StringToBin(const wxString &input)
{
    wxString bin;
    for (size_t i = 0; i < input.length(); i++)
    {
        wxChar c = input[i];
        if (c < 128)
        {
            for (int j = 7; j >= 0; j--)
            {
                bin += ((c >> j) & 1) ? "1" : "0";
            }
            bin += " ";
        }
    }
    return bin;
}

wxString Logic::StringToOct(const wxString &input)
{
    wxString oct;
    for (size_t i = 0; i < input.length(); i++)
    {
        wxChar c = input[i];
        if (c < 128)
        {
            oct += wxString::Format("%o ", static_cast<int>(c));
        }
    }
    return oct;
}

wxString Logic::DecToString(const wxString &dec)
{
    wxString text;
    wxStringTokenizer tokenizer(dec, " ");
    while (tokenizer.HasMoreTokens())
    {
        wxString token = tokenizer.GetNextToken();
        long value;
        if (token.ToLong(&value))
        {
            text += static_cast<wxChar>(value);
        }
    }
    return text;
}

wxString Logic::BinToString(const wxString &bin)
{
    wxString text;
    wxStringTokenizer tokenizer(bin, " ");
    while (tokenizer.HasMoreTokens())
    {
        wxString token = tokenizer.GetNextToken();
        long value;
        if (token.ToLong(&value, 2))
        {
            text += static_cast<wxChar>(value);
        }
    }
    return text;
}

wxString Logic::OctToString(const wxString &oct)
{
    wxString text;
    wxStringTokenizer tokenizer(oct, " ");
    while (tokenizer.HasMoreTokens())
    {
        wxString token = tokenizer.GetNextToken();
        long value;
        if (token.ToLong(&value, 8))
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
