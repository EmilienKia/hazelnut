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
#include "pixmaps/nut-banner.xpm"


// ----------------------------------------------------------------------------
// HazelnutConfigDialog implementation
// ----------------------------------------------------------------------------

BEGIN_EVENT_TABLE(HazelnutConfigDialog, wxDialog)
	EVT_BUTTON(wxID_REVERT, HazelnutConfigDialog::OnRefreshUPSList)
    EVT_BUTTON(wxID_ABOUT, HazelnutConfigDialog::OnAbout)
    EVT_BUTTON(wxID_OK, HazelnutConfigDialog::OnOK)
    EVT_BUTTON(wxID_EXIT, HazelnutConfigDialog::OnExit)
    EVT_CLOSE(HazelnutConfigDialog::OnCloseWindow)
	EVT_CHOICE(wxID_ANY, HazelnutConfigDialog::OnChoicePowerSource)
END_EVENT_TABLE()


HazelnutConfigDialog::HazelnutConfigDialog(const wxString& title)
        : wxDialog(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(512, 300))
{
    wxSizer* gsz = new wxBoxSizer(wxVERTICAL);

	gsz->Add(new wxStaticBitmap(this, wxID_ANY, wxBitmap(nut_banner_xpm)), 0, wxALIGN_CENTER_HORIZONTAL);
	{
		wxSizer* sz = new wxBoxSizer(wxHORIZONTAL);
		sz->Add(new wxStaticText(this, wxID_ANY, wxT("Power source:")), 0, wxALIGN_CENTER_VERTICAL|wxALL, 4);
		sz->Add(choice = new wxChoice(this, wxID_ANY), 1, wxALL, 4);
		sz->Add(new wxButton(this, wxID_REVERT, wxT("Reload")), 0, wxALIGN_CENTER_VERTICAL|wxALL, 4);
		gsz->Add(sz, 0, wxEXPAND);
	}

	{
		wxSizer*  sz = new wxBoxSizer(wxHORIZONTAL);
		sz->Add(new wxButton(this, wxID_ABOUT, wxT("&About")), 0, wxALL, 10);
		sz->Add(new wxButton(this, wxID_OK, wxT("&Hide")), 0, wxALL, 10);
		sz->Add(new wxButton(this, wxID_EXIT, wxT("E&xit")), 0, wxALL, 10);
		gsz->Add(sz, 0, wxALIGN_CENTER_HORIZONTAL);
	}
    SetSizer(gsz);
    Centre();

	RefreshList();
}

HazelnutConfigDialog::~HazelnutConfigDialog()
{
}

void HazelnutConfigDialog::RefreshList()
{
	devices = wxGetApp().getUps();
	wxString current = wxGetApp().GetDevice().getId();
	
	choice->Clear();
	choice->Append(wxT("None"));
	if(current.IsEmpty())
		choice->SetSelection(0);

	for(std::list<Device>::iterator it=devices.begin(); it!=devices.end(); it++)
	{
		Device& dev = *it;
		wxString label = dev.getManufacturer() + wxT(" - ") + dev.getModel();
		int idx = choice->Append(label, &dev);
		if(dev.getId()==current)
			choice->SetSelection(idx);
	}
}

void HazelnutConfigDialog::OnChoicePowerSource(wxCommandEvent& WXUNUSED(event))
{
	int sel = choice->GetSelection();
	if(sel==-1 || sel==0)
		wxGetApp().SetDevice(Device());
	else
		wxGetApp().SetDevice(*(Device*)choice->GetClientData(sel));
}

void HazelnutConfigDialog::OnRefreshUPSList(wxCommandEvent& WXUNUSED(event))
{
	RefreshList();
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


