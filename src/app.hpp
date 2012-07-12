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

#ifndef _APP_HPP_
#define _APP_HPP_

#include "device.hpp"

class HazelnutTaskBarIcon;
class HazelnutConfigDialog;

class HazelnutApp : public wxApp
{
public:
	
    virtual bool OnInit();

	void SetDevice(const Device& dev);
	void Update();
    
    void About();
    void ShowDialog();
    void Exit();

	
    HazelnutTaskBarIcon*  taskBarIcon;
    HazelnutConfigDialog* dialog;
	
	Device   device;
	wxTimer* timer;
	
	UPSCONN_t upsconn;


	void OnTimerUpdate(wxTimerEvent& event);
	
	DECLARE_EVENT_TABLE()
};

DECLARE_APP(HazelnutApp);

#endif // _APP_HPP_
