// src/App.cpp
#include <wx/wx.h>
#include <vector>

class KeypadFrame : public wxFrame {
public:
    KeypadFrame() : wxFrame(nullptr, wxID_ANY, "Keypad Lock", wxDefaultPosition, wxSize(320, 480)) {
        SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_FRAMEBK));

        // Layout container
        wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

        // 1. PIN Display Field
        m_display = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxSize(-1, 40), 
                                  wxTE_READONLY | wxTE_CENTRE | wxTE_PASSWORD);
        wxFont font = m_display->GetFont();
        font.SetPointSize(18);
        font.SetWeight(wxFONTWEIGHT_BOLD);
        m_display->SetFont(font);
        mainSizer->Add(m_display, 0, wxEXPAND | wxALL, 15);

        // 2. Status / Attempts Label
        m_statusText = new wxStaticText(this, wxID_ANY, "Enter 4-digit PIN", 
                                       wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER_HORIZONTAL);
        mainSizer->Add(m_statusText, 0, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 10);

        // 3. Keypad Grid Sizer
        wxGridSizer* grid = new wxGridSizer(4, 3, 10, 10);

        // Keypad button labels (0-9, Clear, Enter)
        const wxString labels[12] = {
            "1", "2", "3",
            "4", "5", "6",
            "7", "8", "9",
            "C", "0", "OK"
        };

        for (int i = 0; i < 12; ++i) {
            wxButton* btn = new wxButton(this, 1000 + i, labels[i], wxDefaultPosition, wxSize(60, 50));
            wxFont btnFont = btn->GetFont();
            btnFont.SetPointSize(14);
            btn->SetFont(btnFont);
            
            grid->Add(btn, 1, wxEXPAND);
            btn->Bind(wxEVT_BUTTON, &KeypadFrame::OnButtonClicked, this);
            m_buttons.push_back(btn);
        }

        mainSizer->Add(grid, 1, wxEXPAND | wxALL, 15);
        SetSizer(mainSizer);
        Layout();
    }

private:
    wxTextCtrl* m_display;
    wxStaticText* m_statusText;
    std::vector<wxButton*> m_buttons;

    const wxString CORRECT_PIN = "1234";
    int m_failedAttempts = 0;
    const int MAX_ATTEMPTS = 3;

    void OnButtonClicked(wxCommandEvent& evt) {
        int id = evt.GetId() - 1000;
        
        // Disable actions if locked out
        if (m_failedAttempts >= MAX_ATTEMPTS) return;

        if (id >= 0 && id <= 8) { // Digits 1-9
            AppendDigit(wxString::Format("%d", id + 1));
        } else if (id == 10) {    // Digit 0
            AppendDigit("0");
        } else if (id == 9) {     // "C" Clear
            m_display->Clear();
        } else if (id == 11) {    // "OK" Submit
            VerifyPIN();
        }
    }

    void AppendDigit(const wxString& digit) {
        if (m_display->GetValue().Length() < 4) {
            m_display->AppendText(digit);
        }
    }

    void VerifyPIN() {
        wxString entered = m_display->GetValue();

        if (entered == CORRECT_PIN) {
            // SUCCESS ENDING
            m_statusText->SetLabelText("Access Granted!");
            m_statusText->SetForegroundColour(*wxGREEN);
            
            wxMessageBox("Access Granted! Welcome.", "Success", 
                         wxOK | wxICON_INFORMATION, this);
            
            m_display->Clear();
            m_failedAttempts = 0;
            m_statusText->SetForegroundColour(*wxBLACK);
            m_statusText->SetLabelText("Enter 4-digit PIN");
        } 
        else {
            // FAIL ENDING
            m_failedAttempts++;
            m_display->Clear();

            if (m_failedAttempts >= MAX_ATTEMPTS) {
                // Lockout State
                m_statusText->SetLabelText("LOCKED OUT!");
                m_statusText->SetForegroundColour(*wxRED);

                for (auto* btn : m_buttons) {
                    btn->Enable(false);
                }

                wxMessageBox("Too many failed attempts! Keypad locked.", "Access Denied", 
                             wxOK | wxICON_ERROR, this);
            } 
            else {
                int remaining = MAX_ATTEMPTS - m_failedAttempts;
                m_statusText->SetLabelText(wxString::Format("Incorrect PIN! %d attempt(s) left.", remaining));
                m_statusText->SetForegroundColour(*wxRED);
            }
        }
    }
};

class MyApp : public wxApp {
public:
    virtual bool OnInit() override {
        KeypadFrame* frame = new KeypadFrame();
        frame->Show(true);
        return true;
    }
};

// Generates WinMain for MSVC / CMake WIN32
wxIMPLEMENT_APP(MyApp);