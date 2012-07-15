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

#ifndef _CONFIG_DIALOG_HPP_
#define _CONFIG_DIALOG_HPP_

#include <list>

#include "device.hpp"

class HazelnutConfigDialog: public wxDialog
{
public:
    HazelnutConfigDialog(const wxString& title);
    virtual ~HazelnutConfigDialog();

	void RefreshList();
	
protected:
	std::list<Device> devices;
	
	wxChoice* choice;
	
	void OnRefreshUPSList(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
    void OnOK(wxCommandEvent& event);
    void OnExit(wxCommandEvent& event);
	
    void OnCloseWindow(wxCloseEvent& event);

	void OnChoicePowerSource(wxCommandEvent& event);
	
    DECLARE_EVENT_TABLE()
};


#endif // _CONFIG_DIALOG_HPP_
