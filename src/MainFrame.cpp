#include "MainFrame.hpp"

MainFrame::MainFrame()
    : wxFrame(nullptr, wxID_ANY, "Team Orkhan 01", wxDefaultPosition, wxSize(800, 600))
{
    auto* menuFile = new wxMenu;
    menuFile->Append(ID_Hello, "&Hello...\tCtrl-H", "Say hello");
    menuFile->AppendSeparator();
    menuFile->Append(wxID_EXIT);

    auto* menuHelp = new wxMenu;
    menuHelp->Append(wxID_ABOUT);

    auto* menuBar = new wxMenuBar;
    menuBar->Append(menuFile, "&File");
    menuBar->Append(menuHelp, "&Help");
    SetMenuBar(menuBar);

    CreateStatusBar();
    SetStatusText("Welcome to Team Orkhan 01");

    Bind(wxEVT_MENU, &MainFrame::OnHello, this, ID_Hello);
    Bind(wxEVT_MENU, &MainFrame::OnExit, this, wxID_EXIT);
    Bind(wxEVT_MENU, &MainFrame::OnAbout, this, wxID_ABOUT);

    Centre();
}

void MainFrame::OnHello(wxCommandEvent& /*event*/)
{
    wxLogMessage("Hello from wxWidgets!");
}

void MainFrame::OnExit(wxCommandEvent& /*event*/)
{
    Close(true);
}

void MainFrame::OnAbout(wxCommandEvent& /*event*/)
{
    wxMessageBox(
        "Team Orkhan 01\nA wxWidgets desktop application.",
        "About Team Orkhan 01",
        wxOK | wxICON_INFORMATION);
}
