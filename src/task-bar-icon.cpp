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

#include "task-bar-icon.hpp"
#include "app.hpp"

// ----------------------------------------------------------------------------
// HazelnutTaskBarIcon implementation
// ----------------------------------------------------------------------------

BEGIN_EVENT_TABLE(HazelnutTaskBarIcon, wxTaskBarIcon)
    EVT_MENU(wxID_ABOUT, HazelnutTaskBarIcon::OnMenuAbout)
    EVT_MENU(wxID_PROPERTIES, HazelnutTaskBarIcon::OnMenuProperties)
    EVT_MENU(wxID_EXIT, HazelnutTaskBarIcon::OnMenuExit)
    EVT_TASKBAR_LEFT_DCLICK(HazelnutTaskBarIcon::OnLeftButtonDClick)
END_EVENT_TABLE()

wxMenu* HazelnutTaskBarIcon::CreatePopupMenu()
{
    wxMenu *menu = new wxMenu;
    menu->Append(wxID_ABOUT, wxT("About..."));
    menu->AppendSeparator();
    menu->Append(wxID_PROPERTIES, wxT("Properties..."));
    menu->AppendSeparator();
    menu->Append(wxID_EXIT, wxT("Exit"));
    return menu;
}

void HazelnutTaskBarIcon::OnMenuAbout(wxCommandEvent&)
{
    wxGetApp().About();
}

void HazelnutTaskBarIcon::OnMenuProperties(wxCommandEvent&)
{
    wxGetApp().ShowDialog();
}

void HazelnutTaskBarIcon::OnLeftButtonDClick(wxTaskBarIconEvent&)
{
    wxGetApp().ShowDialog();
}

void HazelnutTaskBarIcon::OnMenuExit(wxCommandEvent&)
{
    wxGetApp().Exit();
}

