#include "stdafx.h"
#include "Line.h"


CLine::CLine()
{
}

CLine::CLine(LONG startx, LONG starty, LONG endx, LONG endy)
{
	m_tAreaInfo.ptStart.x = startx;
	m_tAreaInfo.ptStart.y = starty;
	m_tAreaInfo.ptEnd.x = endx;
	m_tAreaInfo.ptEnd.y=endy;

}


CLine::~CLine()
{
}

void CLine::Initialize()
{
	m_ObjType = LINE;
}

int CLine::Update()
{
	return NO_EVENT;
}

void CLine::Render(HDC hDC)
{

	MoveToEx(hDC, m_tAreaInfo.ptStart.x, m_tAreaInfo.ptStart.y, nullptr);
	LineTo(hDC, m_tAreaInfo.ptEnd.x, m_tAreaInfo.ptEnd.y);

}

void CLine::Release()
{
}
