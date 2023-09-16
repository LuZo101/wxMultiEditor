#define CATCH_CONFIG_MAIN
#include "catch_amalgamated.hpp"
#include "Logic.hpp"
TEST_CASE("StringToHex and HexToString", "[Logic]")
{
    // Testen der Konvertierung von StringToHex und HexToString
    wxString input = "Hello";
    wxString hex = Logic::StringToHex(input);
    wxString result = Logic::HexToString(hex);
    REQUIRE(result == input);
}

TEST_CASE("StringToDec and DecToString", "[Logic]")
{
    // Testen der Konvertierung von StringToDec und DecToString
    wxString input = "Hello";
    wxString dec = Logic::StringToDec(input);
    wxString result = Logic::DecToString(dec);
    REQUIRE(result == input);
}

TEST_CASE("StringToBin and BinToString", "[Logic]")
{
    // Testen der Konvertierung von StringToBin und BinToString
    wxString input = "Hello";
    wxString bin = Logic::StringToBin(input);
    wxString result = Logic::BinToString(bin);
    REQUIRE(result == input);
}

TEST_CASE("StringToOct and OctToString", "[Logic]")
{
    // Testen der Konvertierung von StringToOct und OctToString
    wxString input = "Hello";
    wxString oct = Logic::StringToOct(input);
    wxString result = Logic::OctToString(oct);
    REQUIRE(result == input);
}

TEST_CASE("BaseToBase", "[Logic]")
{
    // Testen der Konvertierung von einer Basis in eine andere
    wxString inputHex = "1A";
    wxString inputDec = "26";
    wxString inputBin = "11010";
    wxString inputOct = "32";

    REQUIRE(Logic::BaseToBase(inputHex, 16, 10) == inputDec);
    REQUIRE(Logic::BaseToBase(inputDec, 10, 16) == inputHex);
    REQUIRE(Logic::BaseToBase(inputBin, 2, 10) == inputDec);
    REQUIRE(Logic::BaseToBase(inputOct, 8, 10) == inputDec);
    // Fügen Sie weitere Tests für andere Basis-Konvertierungen hinzu.
}
