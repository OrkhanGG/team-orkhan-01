#include "App.hpp"
#include "MainFrame.hpp"

wxIMPLEMENT_APP(App);

bool App::OnInit()
{
    if (!wxApp::OnInit())
    {
        return false;
    }

    auto* frame = new MainFrame();
    frame->Show(true);
    return true;
}
