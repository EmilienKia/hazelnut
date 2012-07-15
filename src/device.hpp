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

#ifndef _DEVICE_HPP_
#define _DEVICE_HPP_

#include <upsclient.h>
#include <map>
#include <list>

class Device
{
public:
	Device():id(), upsconn(NULL){}
	Device(const wxString& id, UPSCONN_t* upsconn):id(id), upsconn(upsconn){}
	Device(const Device& device):id(device.id), upsconn(device.upsconn){}

	bool IsOk()const{return !id.IsEmpty();}

	wxString getId()const{return id;}
	
	wxString getVar(const wxString& name);
	wxString getVar(const char* name);
	std::map<wxString,wxString> getVars();

	static std::list<Device> getUps(UPSCONN_t* upsconn);


	wxString getManufacturer();
	wxString getModel();
	
protected:
	wxString mfr, model;
	
	wxString id;
	UPSCONN_t* upsconn;
};

#endif // _DEVICE_HPP_
