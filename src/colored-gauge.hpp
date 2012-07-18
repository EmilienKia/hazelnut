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

#ifndef _COLORED_GAUGE_HPP_
#define _COLORED_GAUGE_HPP_

#include <map>

class wxColoredGauge: public wxControl 
{
public:
	static wxString wxColoredGaugeName;
	
	wxColoredGauge();
	virtual ~wxColoredGauge();
	wxColoredGauge(wxWindow* parent, wxWindowID id, float value, float min=0.0, float max=100.0, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = 0, const wxString& name = wxPanelNameStr);
	virtual bool Create(wxWindow* parent, wxWindowID id, float value, float min=0.0, float max=100.0, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = 0, const wxString& name = wxPanelNameStr);

	virtual void SetValue(float val);
	virtual float GetValue()const{return value;}
	virtual void SetRange(float min, float max);
	virtual float GetRangeMin()const{return min;}
	virtual float GetRangeMax()const{return max;}

	virtual void SetColorStep(float pos, wxColour hi, wxColour low);
	virtual void ClearColorSteps();

	virtual void SetMark(float pos, float sz=1.0);
	virtual void ClearMarks();

	virtual int ValToCoord(float value)const;
	virtual float CoordToVal(int coord)const;
	
private:
	float min, max, value;

	struct Colours{
		wxColour hi, low;
	};
	typedef std::map<float, Colours> ColourMap;
	ColourMap colourMap;

	typedef std::map<float, float> MarkMap;
	MarkMap markMap;

	void CommonInit(float value, float min, float max);

	void OnPaint(wxPaintEvent& event);

	DECLARE_EVENT_TABLE();
};

#endif // _COLORED_GAUGE_HPP_
