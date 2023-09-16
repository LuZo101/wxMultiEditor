#ifndef LOGIC_HPP
#define LOGIC_HPP

#include <wx/string.h>
#include <wx/tokenzr.h>
#include <wx/log.h>
#include <map>
#include <functional>

class Logic
{
public:
    struct ConversionResult
    {
        wxString input;
        wxString output;
    };
    // Convert the number system based on the given input, source format, and target format
    static wxString ConvertNumberSystem(const wxString &input, const wxString &from, const wxString &to);
        // Format the data based on the given input data, source format, and target format

    ConversionResult FormatData(const wxString &inputUData, const wxString &inputDData, const wxString &from, const wxString &to);
  
    // Check if the given character is a valid ASCII input
    static bool IsASCIIInput(wxChar c);

    static wxString ConvertNumberSystemUp(const wxString &from, const wxString &to, const wxString &inputUp);
    static wxString ConvertNumberSystemDown(const wxString &from, const wxString &to, const wxString &inputDown);

    // Convert a number from one base to another
    static wxString BaseToBase(const wxString &input, int fromBase, int toBase);

    // Convert a number to a specific base
    static wxString ConvertBase(long value, int toBase);

    // Convert a string to its hexadecimal representation
    static wxString StringToHex(const wxString &input);

    // Convert a hexadecimal string to its string representation
    static wxString HexToString(const wxString &input);

    // Convert a string to its decimal representation
    static wxString StringToDec(const wxString &input);

    // Convert a string to its binary representation
    static wxString StringToBin(const wxString &input);

    // Convert a string to its octal representation
    static wxString StringToOct(const wxString &input);

    // Convert a decimal string to its string representation
    static wxString DecToString(const wxString &dec);

    // Convert a binary string to its string representation
    static wxString BinToString(const wxString &bin);

    // Convert an octal string to its string representation
    static wxString OctToString(const wxString &oct);
};

#endif // LOGIC_HPP
