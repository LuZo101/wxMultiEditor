#ifndef LOGIC_HPP
#define LOGIC_HPP

#include <ostream>
#include <string>
#include <algorithm>
#include <cstdint>
#include <wx/string.h>

class Logic
{
public:
    static wxString StringToHex(const wxString &input);
    static wxString HexToString(const wxString &input);
    static bool IsASCIIInput(wxChar c);
    static bool IsHexInput(const wxString &input);
    static wxString FormatData(const wxString &ascii, const wxString &hex);
};

#endif // LOGIC_HPP