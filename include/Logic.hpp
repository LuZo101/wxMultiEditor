#ifndef LOGIC_HPP
#define LOGIC_HPP

#include <wx/wx.h>
#include <wx/tokenzr.h>
#include <map>
#include <functional>
class Logic
{
public:
    static wxString ConvertNumberSystem(const wxString &input, const wxString &from, const wxString &to);
    static wxString DecToBin(const wxString &dec);
    static wxString BinToDec(const wxString &bin);
    static wxString DecToOct(const wxString &dec);
    static wxString OctToDec(const wxString &oct);
    static wxString HexToBin(const wxString &hex);
    static wxString BinToHex(const wxString &bin);
    static wxString StringToDec(const wxString &input);
    static wxString BaseToBase(const wxString &input, int fromBase, int toBase);
    static wxString StringToHex(const wxString &input);
    static wxString HexToString(const wxString &input);
    static wxString StringToBin(const wxString &input);
    static wxString StringToOct(const wxString &input);
    static wxString DecToString(const wxString &dec);
    static wxString BinToString(const wxString &bin);
    static wxString OctToString(const wxString &oct);
    static wxString FormatData(const wxString &inputUData, const wxString &inputDData, const wxString &from, const wxString &to);

    static bool IsASCIIInput(wxChar c);
    static bool IsHexInput(const wxString &input);

private:
    struct PairComparator
    {
        bool operator()(const std::pair<wxString, wxString> &a, const std::pair<wxString, wxString> &b) const
        {
            return a.first < b.first || (a.first == b.first && a.second < b.second);
        }
    };

    using ConvertNumberSystemFunc = std::function<wxString(const wxString &)>;
    std::map<std::pair<wxString, wxString>, ConvertNumberSystemFunc, PairComparator> converters;
};

#endif // LOGIC_HPP
