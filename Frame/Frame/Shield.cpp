#include "stdafx.h"
#include "Shield.h"


CShield::CShield()
	: m_fDistance(0.f),
	m_pTarget(nullptr)
{
}

CShield::CShield(CGameObject* _gameobj)
	: m_fDistance(0.f),
	m_pTarget(_gameobj)

{
}


CShield::~CShield()
{
	Release();
}

void CShield::Initialize()
{
	m_tInfo.fCX = 50.f;
	m_tInfo.fCY = 50.f;

	m_fAngle = 90.f;
	m_fSpeed = 5.f;
	m_fDistance = 100.f;
}

int CShield::Update()
{
	if (m_bIsDead)
		return DEAD_OBJ;

	m_fAngle += m_fSpeed;

	// 과제1. 타겟을 어떻게 얻어올 것인가? 
	// m_pTarget = ;

	m_tInfo.fX = m_pTarget->GetInfo().fX + cosf(m_fAngle * PI / 180.f) * m_fDistance;
	m_tInfo.fY = m_pTarget->GetInfo().fY - sinf(m_fAngle * PI / 180.f) * m_fDistance;

	return NO_EVENT;
}

void CShield::Render(HDC hDC)
{
	CGameObject::UpdateRect();
	Ellipse(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CShield::Release()
{
}
