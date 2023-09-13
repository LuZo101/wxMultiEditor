#include "App.hpp"

bool App::OnInit()
{
    // Korrigiere den Konstruktoraufruf, um nur ein Argument zu übergeben
    MainFrame *mainframe = new MainFrame("wxEditor");
    mainframe->Show(true);
    mainframe->SetClientSize(800,600);
    mainframe->Center();
    return true;
}

wxIMPLEMENT_APP(App);
