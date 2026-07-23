#include "App.hpp"

#include "Frame/MainFrame.hpp"

bool App::OnInit()
{
    MainFrame* mainFrame = new MainFrame("Security Application");
    mainFrame->Show(true);

    return true;
}

wxIMPLEMENT_APP(App);
