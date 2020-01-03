#include "stdafx.h"
#include "Bullet.h"


CBullet::CBullet()	
{
}

CBullet::CBullet(CGameObject * _gameobj, BULLET_TYPE _bulletType)
{
	SetBulletType(_bulletType);
	SetTarget(_gameobj);
}


CBullet::~CBullet()
{
	Release();
}

void CBullet::Initialize()
{
	m_tInfo.fCX = 20.f;
	m_tInfo.fCY = 20.f;

	m_fSpeed = 5.f;
}

int CBullet::Update()
{
	if (m_bIsDead)
		return DEAD_OBJ;

	if (0.f > m_tInfo.fX || 0.f > m_tInfo.fY || 
		(float)WINCX < m_tInfo.fX || (float)WINCY < m_tInfo.fY)
		return DEAD_OBJ;
	Move();
	//m_tInfo.fX += cosf(m_fAngle * PI / 180.f) * m_fSpeed;
	//m_tInfo.fY -= sinf(m_fAngle * PI / 180.f) * m_fSpeed;

	return NO_EVENT;
}

void CBullet::Render(HDC hDC)
{
	CGameObject::UpdateRect();
	Ellipse(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CBullet::Move()
{
	switch (BulletType)
	{
	case STRAIGHT:
		m_tInfo.fX += cosf(m_fAngle * PI / 180.f) * m_fSpeed;
		m_tInfo.fY -= sinf(m_fAngle * PI / 180.f) * m_fSpeed;
		break;
	case TRAKING:
		if (GetTarget() != nullptr)
		{
			//m_tInfo.fX += cosf(m_fAngle * PI / 180.f) * 10;
			//m_tInfo.fY -= sinf(m_fAngle * PI / 180.f) * 10;
			CalcAngle(GetTarget()->GetInfo());
			if (m_tInfo.fY < GetTarget()->GetInfo().fY)
			{
				//float fx=Lerp(m_tInfo.fX, m_tInfo.fX -= cosf(m_fAngle) * m_fSpeed, (m_DwCurTime % 100) / 1000.f);
				//float fy=Lerp(m_tInfo.fY, m_tInfo.fY += sinf(m_fAngle) * m_fSpeed, (m_DwCurTime % 100) / 1000.f);
				m_tInfo.fX -= cosf(m_fRadian) * m_fSpeed;
				m_tInfo.fY += sinf(m_fRadian) * m_fSpeed;
			}
			else
			{
				//float fx = Lerp(m_tInfo.fX, m_tInfo.fX -= cosf(m_fAngle) * m_fSpeed, (m_DwCurTime % 100) / 1000.f);
				//float fy = Lerp(m_tInfo.fY, m_tInfo.fY += sinf(-m_fAngle) * m_fSpeed, (m_DwCurTime % 100) / 1000.f);
				m_tInfo.fX -= cosf(m_fRadian) * m_fSpeed;
				m_tInfo.fY += sinf(-m_fRadian)* m_fSpeed;
			}
			cout << "X=" << m_tInfo.fX << " ,  Y=" << m_tInfo.fY << endl;
		}
		break;
	default:
		break;
	}
}

void CBullet::Release()
{
}
