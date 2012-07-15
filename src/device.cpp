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

#include "device.hpp"

// ----------------------------------------------------------------------------
// Device implementation
// ----------------------------------------------------------------------------

wxString Device::getVar(const wxString& name)
{
	const char*  query[] = {"VAR", NULL, NULL};
	query[1] = (const char*)id.mb_str(wxConvISO8859_1);
	query[2] = (const char*)name.mb_str(wxConvISO8859_1);
	char** answer;
	unsigned int nbanswer;
	int res = upscli_get(upsconn, 3, query, &nbanswer, &answer);
	if(res==-1 || nbanswer<2)
		return wxString();
	else
		return wxString(answer[1], wxConvISO8859_1);
}

wxString Device::getVar(const char* name)
{
	char buffer[256];
	strncpy(buffer, (const char*)id.mb_str(wxConvISO8859_1), 255);
	
	const char*  query[] = {"VAR", buffer, name};
	char** answer;
	unsigned int nbanswer;
	int res = upscli_get(upsconn, 3, query, &nbanswer, &answer);
	if(res==-1)
	{
//		printf("getVar %s fails\n", query[1]);
		return wxString();
	}
	else
	{
//		printf("getVar %d: %s = %s\n", res, name, answer[3]);
		return wxString(answer[3], wxConvISO8859_1);
	}
}

std::map<wxString,wxString> Device::getVars()
{
	std::map<wxString,wxString> ret;
	const char*  query[] = {"VAR", NULL};
	query[1] = (const char*)id.mb_str(wxConvISO8859_1);
	char** answer;
	unsigned int nbanswer;
	int res = upscli_list_start(upsconn, 2, query);
	if(res==-1)
		return ret;
	while(upscli_list_next(upsconn, 2, query, &nbanswer, &answer)==1)
	{
		if(nbanswer>=3)
			ret[wxString(answer[1], wxConvISO8859_1)] = wxString(answer[2], wxConvISO8859_1);
	}
	return ret;
}

std::list<Device> Device::getUps(UPSCONN_t* upsconn)
{
	std::list<Device> ret;

	if(!upsconn)
		return ret;

	const char* query[] = {"UPS"};
	char** answer;
	unsigned int nbanswer;
	int res = upscli_list_start(upsconn, 1, query);
	if(res==-1)
	{
		printf("*** %d : %s\n", upscli_upserror(upsconn), upscli_strerror(upsconn));
		return ret;
	}
	while(upscli_list_next(upsconn, 1, query, &nbanswer, &answer)>0)
	{
		if(nbanswer>=2)
			ret.push_back(Device(wxString(answer[1], wxConvISO8859_1), upsconn));
	}
	return ret;
}

wxString Device::getManufacturer()
{
	if(mfr.IsEmpty() && IsOk())
	{
		mfr = getVar("device.mfr");
	}
	return mfr;
}

wxString Device::getModel()
{
	if(model.IsEmpty() && IsOk())
	{
		model = getVar("device.model");
	}
	return model;
}

