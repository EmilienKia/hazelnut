/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * hazelnut
 * Copyright (C) Emilien Kia 2012 <emilien.kia@gmail.com>
 * 
hazelnut is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * hazelnut is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif
#include <wx/wx.h>

#include "config-dialog.hpp"

#include "app.hpp"

// ----------------------------------------------------------------------------
// HazelnutConfigDialog implementation
// ----------------------------------------------------------------------------

BEGIN_EVENT_TABLE(HazelnutConfigDialog, wxDialog)
    EVT_BUTTON(wxID_ABOUT, HazelnutConfigDialog::OnAbout)
    EVT_BUTTON(wxID_OK, HazelnutConfigDialog::OnOK)
    EVT_BUTTON(wxID_EXIT, HazelnutConfigDialog::OnExit)
    EVT_CLOSE(HazelnutConfigDialog::OnCloseWindow)
END_EVENT_TABLE()


HazelnutConfigDialog::HazelnutConfigDialog(const wxString& title)
        : wxDialog(NULL, wxID_ANY, title)
{
    wxSizer * const sizerTop = new wxBoxSizer(wxVERTICAL);

    wxSizerFlags flags;
    flags.Border(wxALL, 10);

    sizerTop->Add(new wxStaticText
                      (
                        this,
                        wxID_ANY,
                        wxT("Press 'Hide me' to hide this window, Exit to quit.")
                      ), flags);

    sizerTop->Add(new wxStaticText
                      (
                        this,
                        wxID_ANY,
                        wxT("Double-click on the taskbar icon to show me again.")
                      ), flags);

    sizerTop->AddStretchSpacer()->SetMinSize(200, 50);

    wxSizer * const sizerBtns = new wxBoxSizer(wxHORIZONTAL);
    sizerBtns->Add(new wxButton(this, wxID_ABOUT, wxT("&About")), flags);
    sizerBtns->Add(new wxButton(this, wxID_OK, wxT("&Hide")), flags);
    sizerBtns->Add(new wxButton(this, wxID_EXIT, wxT("E&xit")), flags);

    sizerTop->Add(sizerBtns, flags.Align(wxALIGN_CENTER_HORIZONTAL));
    SetSizerAndFit(sizerTop);
    Centre();
}

HazelnutConfigDialog::~HazelnutConfigDialog()
{
}

void HazelnutConfigDialog::OnAbout(wxCommandEvent& WXUNUSED(event))
{
    wxGetApp().About();
}

void HazelnutConfigDialog::OnOK(wxCommandEvent& WXUNUSED(event))
{
    Hide();
}

void HazelnutConfigDialog::OnExit(wxCommandEvent& WXUNUSED(event))
{
    wxGetApp().Exit();
}

void HazelnutConfigDialog::OnCloseWindow(wxCloseEvent& event)
{
    event.Veto();
    Hide();
}


