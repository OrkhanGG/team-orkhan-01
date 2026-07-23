#include "MainFrame.hpp"
#include "View/KeypadWidget.h"

MainFrame::MainFrame(const wxString& title) :
    wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxSize(320, 480))
{
    new KeypadWidget(this);

    Centre();
}
