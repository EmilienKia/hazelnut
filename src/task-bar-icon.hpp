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

#ifndef _TASK_BAR_ICON_HPP_
#define _TASK_BAR_ICON_HPP_

#include <wx/taskbar.h>

class HazelnutTaskBarIcon : public wxTaskBarIcon
{
public:
#if defined(__WXOSX__) && wxOSX_USE_COCOA
    HazelnutTaskBarIcon(wxTaskBarIconType iconType = DEFAULT_TYPE)
    :   wxTaskBarIcon(iconType)
#else
    HazelnutTaskBarIcon()
#endif
    {}

    void OnMenuAbout(wxCommandEvent&);
    void OnMenuProperties(wxCommandEvent&);
    void OnMenuExit(wxCommandEvent&);

    void OnLeftButtonDClick(wxTaskBarIconEvent&);
    
    virtual wxMenu *CreatePopupMenu();

    DECLARE_EVENT_TABLE()
};

#endif // _TASK_BAR_ICON_HPP_
