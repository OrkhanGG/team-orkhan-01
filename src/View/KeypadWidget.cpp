#include "KeypadWidget.h"

#include <wx/sizer.h>
#include <wx/textctrl.h>
#include <wx/stattext.h>
#include <wx/button.h>
#include <wx/msgdlg.h>

KeypadWidget::KeypadWidget(wxWindow* parent)
    : wxPanel(parent, wxID_ANY)
{
    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
    
    display = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxSize(-1, 40), wxTE_READONLY | wxTE_CENTRE);
    statusText = new wxStaticText(this, wxID_ANY, "Enter 4-digit PIN");

    wxGridSizer* grid = new wxGridSizer(4, 3, 0, 0);
    
    const short labelsSize = 12;
    const wxString labels[labelsSize] = {
        "1", "2", "3",
        "4", "5", "6",
        "7", "8", "9",
        "C", "0", "OK"
    };
    for (int i = 0; i < labelsSize; ++i)
    {
        wxButton* btn = new wxButton(this, ID_OFFSET + i, labels[i]);
        grid->Add(btn, 1, wxEXPAND);
    
        btn->Bind(wxEVT_BUTTON, &KeypadWidget::OnButtonClick, this);
    }

    mainSizer->Add(display, 0, wxEXPAND | wxALL, 15);
    mainSizer->Add(statusText, 0, wxCENTER, 0);
    mainSizer->Add(grid, 1, wxEXPAND | wxALL, 15);

    SetSizer(mainSizer);
    Layout();
}

void KeypadWidget::OnButtonClick(wxCommandEvent& event)
{
    wxButton* btn = dynamic_cast<wxButton*>(event.GetEventObject());
    if (btn)
    {
        const int evaluatedID = event.GetId() - ID_OFFSET;
        if (evaluatedID == 11)
        {
            // OK button is clicked
            OnVerify();
        }
        else if (evaluatedID == 9)
        {
            ClearAll();
        }
        else
        {
            AppendDigit(btn->GetLabel());
        }
    }
}

void KeypadWidget::AppendDigit(const wxString& digit)
{
    display->AppendText(digit);
}

void KeypadWidget::ClearAll()
{
    display->Clear();
}

void KeypadWidget::OnVerify()
{
    if (display->GetValue() == CorrectPIN)
    {
        statusText->SetForegroundColour(wxColour(0,175,0));
        statusText->SetLabelText("Access Granted!");
        
        wxMessageBox("The gate is unlocked");
    }
    else
    {
        statusText->SetForegroundColour(wxColour(255,0,0));
        statusText->SetLabelText("Access Denied!");
        
        wxMessageBox("The gate could not be unlocked");
    }
}
