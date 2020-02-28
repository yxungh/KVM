#include "stdafx.h"
#include "XChart.h"
#include "XColumnChart.h"
#include "XProgressBar.h"
#include "XPiechart.h"
#include "XPercentage.h"
#include "XString.h"
#include "XInserument.h"


XChart::XChart()
{
}

XChart::~XChart()
{
}

void XChart::RectScale(RECTF& rect)
{
	rect.X*=m_dwScale;
	rect.Y*=m_dwScale;
	rect.Width*=m_dwScale;
	rect.Height*=m_dwScale;
}

XChart* XChart::Get(CHART chartType)
{
	switch(chartType)
	{
		case CHART::CHART_CLOUMN_NODE:
			{
				static XColumnChart chart;
				return &chart;
			}
			break;
		case CHART::CHART_CLOUMN_USER:
			{
				static XColumnChart chart;
				return &chart;
			}
			break;
		case CHART::CHART_CLOUMN_GROUP:
			{
				static XColumnChart chart;
				return &chart;
			}
			break;
		case CHART::CHART_CLOUMN_SYSTEM:
			{
				static XColumnChart chart;
				return &chart;
			}
			break;
		case CHART::CHART_PROGRESS:
			{
				static XProgressBar bar;
				return &bar;
			}
			break;
		case CHART::CHART_PIE:
			{
				static XPiechart chart;
				return &chart;
			}
			break;
		case CHART::CHART_PERCENTAGE:
			{
				static XPercentage chart;
				return &chart;
			}
			break;
		case CHART::CHART_STRING:
			{
				static XString str;
				return &str;
			}
			break;
		case CHART::CHART_INSTRUMENT:
			{
				static XInserument instrument;
				return &instrument;
			}
			break;
		default:
			break;
	}
	return NULL;
}