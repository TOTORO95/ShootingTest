#include "stdafx.h"
#include "Player.h"
#include "Bullet.h"
#include "Shield.h"

CPlayer::CPlayer()
	: m_fGunX(0.f), m_fGunY(0.f),
	m_fGunLength(0.f),
	m_pBulletList(nullptr),
	m_pShieldList(nullptr)
{
}


CPlayer::~CPlayer()
{
	Release();
}

void CPlayer::SetBulletList(OBJECT_LIST* pBulletList)
{
	m_pBulletList = pBulletList;
}

void CPlayer::SetShieldList(OBJECT_LIST* pShieldList)
{
	m_pShieldList = pShieldList;
}

void CPlayer::Initialize()
{
	m_tInfo.fX = 400.f;
	m_tInfo.fY = 300.f;
	m_tInfo.fCX = 50.f;
	m_tInfo.fCY = 50.f;
	m_ObjType = PLAYER;
	m_fSpeed = 5.f;
	m_fAngle = 90.f;	// Degree
	m_fGunLength = 100.f;
}

int CPlayer::Update()
{
	KeyInput();

	// 180도 -> pi라디안
	// 1도 -> pi / 180 라디안
	// 1라디안 -> 180 / pi 도
	m_fGunX = m_tInfo.fX + cosf(m_fAngle * PI / 180.f) * m_fGunLength;
	m_fGunY = m_tInfo.fY - sinf(m_fAngle * PI / 180.f) * m_fGunLength;

	return NO_EVENT;
}

void CPlayer::Render(HDC hDC)
{
	CGameObject::UpdateRect();
	Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);

	// 포신 그리기
	MoveToEx(hDC, (int)m_tInfo.fX, (int)m_tInfo.fY, nullptr);
	LineTo(hDC, (int)m_fGunX, (int)m_fGunY);
}

void CPlayer::Release()
{
}

void CPlayer::KeyInput()
{	
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
		m_tInfo.fX -= m_fSpeed;
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
		m_tInfo.fX += m_fSpeed;
	if (GetAsyncKeyState(VK_UP) & 0x8000)
	{
		m_tInfo.fY -= m_fSpeed;
		//m_tInfo.fX += cosf(m_fAngle * PI / 180.f) * m_fSpeed;
		//m_tInfo.fY -= sinf(m_fAngle * PI / 180.f) * m_fSpeed;
	}
	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
	{
		m_tInfo.fY+= m_fSpeed;

		//m_tInfo.fX += cosf(m_fAngle * PI / 180.f) * -m_fSpeed;
		//m_tInfo.fY -= sinf(m_fAngle * PI / 180.f) * -m_fSpeed;
	}

	if (GetAsyncKeyState(VK_SPACE) & 0x8000)//점프
	{
		m_DwCurTime = GetTickCount();//TODO: 요기만드는중
		m_tInfo.fY += m_fSpeed*0.01;
	}
	if (GetAsyncKeyState('A') & 0x8000)
	{
		m_DwCurTime = GetTickCount();
		if (m_DwCurTime - m_DwOldTime >= 100)
		{
			NULL_CHECK(m_pShieldList);
			m_pShieldList->push_back(CObjectFactory<CShield>::CreateObject(this));
			m_DwOldTime = m_DwCurTime;
		}

	}
	if (GetAsyncKeyState('S') & 0x8000)
	{
		m_DwCurTime = GetTickCount();
		if (m_DwCurTime - m_DwOldTime >= 300)
		{
			NULL_CHECK(m_pShieldList);
			m_pBulletList->push_back(CObjectFactory<CBullet>::CreateObject(m_fGunX, m_fGunY, m_fAngle,m_Target,TRAKING));
			m_DwOldTime = m_DwCurTime;
		}


		// 과제3. 몬스터 추적하는 유도미사일 구현. (미사일 기준으로 가까운 몬스터를 추적)
	}
}
