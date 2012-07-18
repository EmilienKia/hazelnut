/*
 * wxColoredGauge
 * Copyright (C) Emilien Kia 2012 <emilien.kia@gmail.com>
 * 
 * wxColoredGauge is free software: you can redistribute it and/or modify it
 * under the terms of at your convenience:
 *  - the CeCILL-C licence as published by CEA, CNRS and INRIA 
 * at http://www.cecill.info
 *  - the GNU Lesser General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * wxColoredGauge is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 * You should have received a copy of the CeCILL-C licence along
 * with this program.  If not, see <http://www.cecill.info/>.
 */
#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif
#include <wx/wx.h>

#include <wx/dcbuffer.h>
#include <wx/graphics.h>

#include "colored-gauge.hpp"

wxString wxColoredGauge::wxColoredGaugeName = wxT("wxColoredGauge");

BEGIN_EVENT_TABLE(wxColoredGauge, wxControl)
	EVT_PAINT(wxColoredGauge::OnPaint)
END_EVENT_TABLE()

wxColoredGauge::wxColoredGauge()
{
}

wxColoredGauge::~wxColoredGauge()
{
}

wxColoredGauge::wxColoredGauge(wxWindow* parent, wxWindowID id, float value, float min, float max, const wxPoint& pos, const wxSize& size, long style, const wxString& name)
{
	Create(parent, id, value, min, max, pos, size, style, name);
}

bool wxColoredGauge::Create(wxWindow* parent, wxWindowID id, float value, float min, float max, const wxPoint& pos, const wxSize& size, long style, const wxString& name)
{
	if(!wxWindow::Create(parent, id, pos, size, style|wxFULL_REPAINT_ON_RESIZE, name))
		return false;
	CommonInit(value, min, max);
	
	return true;
}

void wxColoredGauge::CommonInit(float value, float min, float max)
{
	InheritAttributes();
	SetInitialBestSize(wxSize(-1, 24));
	SetBackgroundStyle(wxBG_STYLE_CUSTOM);
	SetRange(min, max);
	SetValue(value);
}

void wxColoredGauge::OnPaint(wxPaintEvent& event)
{
	wxAutoBufferedPaintDC dc(this);
	wxGraphicsContext* gc = wxGraphicsContext::Create(dc);
	
	wxSize csz = GetClientSize();

	// Draw dummy background
	gc->SetPen(*wxTRANSPARENT_PEN);
	gc->SetBrush(*wxGREY_BRUSH);
	gc->DrawRectangle(0, 0, csz.x, csz.y);
	
	// Draw backgrounds:
	gc->SetPen(*wxTRANSPARENT_PEN);
	bool isOver = false;
	
	for(ColourMap::reverse_iterator it=colourMap.rbegin(); it!=colourMap.rend(); it++)
	{
		float idx = it->first;
		Colours& col = it->second;
		int pos;
		
		if(idx > GetValue())
		{
			pos = ValToCoord(idx);
			gc->SetBrush(wxBrush(col.low));
			gc->DrawRectangle(0, 0, pos, csz.y);

			pos = ValToCoord(GetValue());
			gc->SetBrush(wxBrush(col.hi));
			gc->DrawRectangle(0, 0, pos, csz.y);
		}
		else
		{
			pos = ValToCoord(idx);
			gc->SetBrush(wxBrush(col.hi));
			gc->DrawRectangle(0, 0, pos, csz.y);
		}
	}

	// Draw separators
	gc->SetBrush(*wxTRANSPARENT_BRUSH);
	gc->SetPen(*wxBLACK_PEN);
	for(MarkMap::iterator it=markMap.begin(); it!=markMap.end(); it++)
	{
		wxPoint2DDouble  pt[2];
		int pos = ValToCoord(it->first);
		pt[0] = wxPoint2DDouble(pos, csz.y - csz.y*it->second);
		pt[1] = wxPoint2DDouble(pos, csz.y);
		gc->DrawLines(2, pt);
	}
	
	// Draw hilight
	gc->SetPen(*wxTRANSPARENT_PEN);
	gc->SetBrush(gc->CreateLinearGradientBrush(0, 0, 0, csz.y/3.0, wxColour(255, 255, 255, 172), wxColour(255, 255, 255, 0)));
	gc->DrawRectangle(0, 0, csz.x, csz.y/3.0);
	// Draw shadow
	gc->SetPen(*wxTRANSPARENT_PEN);
	gc->SetBrush(gc->CreateLinearGradientBrush(0, csz.y*2.0/3.0, 0, csz.y, wxColour(0, 0, 0, 0), wxColour(0, 0, 0, 92)));
	gc->DrawRectangle(0, csz.y*2.0/3.0, csz.x, csz.y);

	delete gc;
}

void wxColoredGauge::SetMark(float pos, float sz)
{
	if(sz<0.1)
		sz = 0.1;
	else if(sz>1.0)
		sz = 1.0;
	markMap[pos] = sz;
	Refresh();
}

void wxColoredGauge::ClearMarks()
{
	markMap.clear();
	Refresh();
}

void wxColoredGauge::SetColorStep(float pos, wxColour hi, wxColour low)
{
	Colours col;
	col.hi = hi;
	col.low = low;
	colourMap[pos] = col;
	Refresh();
}

void wxColoredGauge::ClearColorSteps()
{
	colourMap.clear();
	Refresh();
}

void wxColoredGauge::SetValue(float val)
{
	value = val;
	Refresh();
}

void wxColoredGauge::SetRange(float _min, float _max)
{
	if(_min<_max)
	{
		min = _min;
		max = _max;
	}
	else if(_min==_max)
	{
		min = _min;
		_max = min + 1;
	}
	else
	{
		min = _max;
		max = _min;
	}
	Refresh();
}

int wxColoredGauge::ValToCoord(float value)const
{
	return (int) ((value-min)*GetClientSize().x/(max-min));
}

float wxColoredGauge::CoordToVal(int coord)const
{
	int szx = GetClientSize().x;
	if(szx==0)
		return 0;
	return ((float)coord*(max-min))/szx + min;
}
