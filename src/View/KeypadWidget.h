#pragma once

#include <wx/panel.h>

class wxTextCtrl;
class wxStaticText;

class KeypadWidget : public wxPanel
{
public:
    KeypadWidget(wxWindow* parent);

private:
    // Widgets
    wxTextCtrl* display;
    wxStaticText* statusText;
    
    // Constants
    const wxString CorrectPIN = "0123";
    const short ID_OFFSET = 10000;
    
    // Helpers
    void AppendDigit(const wxString& digit);
    void ClearAll();
    
    // Events    
    void OnVerify();
    void OnButtonClick(wxCommandEvent& event);
};
