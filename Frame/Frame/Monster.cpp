#include "stdafx.h"
#include "Monster.h"


CMonster::CMonster()
{
}


CMonster::~CMonster()
{
	Release();
}

void CMonster::Initialize()
{
	m_fSpeed = 2.0;
	m_tInfo.fCX = 50.f;
	m_tInfo.fCY = 50.f;
}

int CMonster::Update()
{
	if (m_bIsDead)
		return DEAD_OBJ;
	Move();
	
	// 과제2. 플레이어 따라가기. (역삼각함수 acosf를 이용하여 각도 구하기)

	

	return NO_EVENT;
}

void CMonster::Render(HDC hDC)
{
	CGameObject::UpdateRect();
	Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	MoveToEx(hDC, m_tInfo.fX, m_tInfo.fY,NULL);
	if (m_tInfo.fY < GetTarget()->GetInfo().fY)
		LineTo(hDC,m_tInfo.fX -cosf(m_fRadian) * 50, m_tInfo.fY+sinf(m_fRadian) * 50);
	else
		LineTo(hDC, m_tInfo.fX-cosf(-m_fRadian) * 50, m_tInfo.fY+sinf(-m_fRadian) * 50);
}

void CMonster::Move()
{
	if (GetTarget()!=nullptr)
	{
		CalcAngle(GetTarget()->GetInfo());
		if (m_tInfo.fY < GetTarget()->GetInfo().fY)
		{
			m_tInfo.fX -= cosf(m_fRadian) * m_fSpeed;
			m_tInfo.fY += sinf(m_fRadian) * m_fSpeed;

		}
		else
		{
			m_tInfo.fX -= cosf(m_fRadian) * m_fSpeed;
			m_tInfo.fY += sinf(-m_fRadian) * m_fSpeed;
		}
	}

}

void CMonster::Release()
{
}
