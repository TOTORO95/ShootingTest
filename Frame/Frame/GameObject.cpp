#include "stdafx.h"
#include "GameObject.h"


CGameObject::CGameObject()
	: m_bIsDead(false),
	m_fSpeed(0.f),
	m_fAngle(0.f)
{
	ZeroMemory(&m_tInfo, sizeof(INFO));
	ZeroMemory(&m_tRect, sizeof(RECT));
}


CGameObject::~CGameObject()
{
}

const INFO& CGameObject::GetInfo() const
{
	// TODO: 여기에 반환 구문을 삽입합니다.
	return m_tInfo;
}

const RECT& CGameObject::GetRect() const
{
	// TODO: 여기에 반환 구문을 삽입합니다.
	return m_tRect;
}

void CGameObject::SetPos(float x, float y)
{
	m_tInfo.fX = x;
	m_tInfo.fY = y;
}

void CGameObject::SetAngle(float degree)
{
	m_fAngle = degree;
}

bool CGameObject::IsDead()
{
	return m_bIsDead = true;
}

void CGameObject::CalcAngle(INFO _target)
{
	float fx = m_tInfo.fX - _target.fX;
	float fy = m_tInfo.fY - _target.fY;
	float fr = sqrtf(fx*fx + fy*fy);
	m_fRadian =acosf(fx/fr);
}

float CGameObject::Lerp(float p1, float p2, float ft)
{
	return float(p1 + ((float)(p2 - p1) * ft));


}

void CGameObject::UpdateRect()
{
	m_tRect.left = LONG(m_tInfo.fX - m_tInfo.fCX * 0.5f);
	m_tRect.top = LONG(m_tInfo.fY - m_tInfo.fCY * 0.5f);
	m_tRect.right = LONG(m_tInfo.fX + m_tInfo.fCX * 0.5f);
	m_tRect.bottom = LONG(m_tInfo.fY + m_tInfo.fCY * 0.5f);
}
