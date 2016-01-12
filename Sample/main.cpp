#include <wx/wx.h>


#include "gpPanel.h"
#include "gpLineLayer.h"

#include <vld.h>


class MyCandleLayer : public gpLayer
{

};

class MyCandleStick1 : public mpFXYCandleStick
{
public:

	virtual bool GetNext(double & x, double & yCandleMin, double & yCandleMax, double& yStickMin, double& yStickMax) override
	{
		if (mIndex > 100)
			return false;

		x = mIndex++;

		yCandleMax = 225;
		yCandleMin = 205;
		yStickMax = 10;
		yStickMin = 2;
	}

	virtual void Rewind() override
	{
		mIndex = 0;
	}

	virtual double GetMaxX() override
	{
		return 100;
	}

	virtual double GetMaxY() override
	{
		return 1000;
	}

	virtual double GetMinX() override
	{
		return 0;
	}

	virtual double GetMinY() override
	{
		return 200;
	}

private:

	int mIndex{ 0 };
};

// application class
class wxMiniApp : public wxApp
{
public:
	// function called at the application initialization
	virtual bool OnInit();

	// event handler for button click
	void OnClick(wxCommandEvent& event) {
		GetTopWindow()->Close();
	}
};

IMPLEMENT_APP(wxMiniApp);

bool wxMiniApp::OnInit()
{
	// create a new frame and set it as the top most application window
	wxSize clientsize(640, 320);
	wxFrame* frame = new wxFrame(NULL, -1, wxT("gpPanel Test"), wxDefaultPosition, clientsize);
	frame->SetMinClientSize(clientsize);

	//init gpPanel
	gpPanel* graphPanel = new gpPanel(frame, -1, wxDefaultPosition, clientsize);

	//create new histogram layer
	gpLineLayer  *ll = new gpLineLayer("Test", "xxx", "yyy");

	gpSeries* s1 = ll->AddSeriesLayer("line1");
	gpSeries* s2 = ll->AddSeriesLayer("line2");

	//Push data to gpLayer
	for (int i = 0; i < 120; i++)
	{
		s1->DataPush(i, (rand() + 1) % 1024);
		s2->DataPush(i, (rand() + 1) % 1024);
	}

	//add gpLayer to gpPanel
	graphPanel->AddLayer(ll, POPUP_FILE | POPUP_CHART | POPUP_EDIT | POPUP_HELP | POPUP_FIT);

	ll->RefreshChart();
	graphPanel->Fit(ll);

	SetTopWindow(frame);
	// show main frame
	GetTopWindow()->Show();

	// enter the application's main loop
	return true;
}
