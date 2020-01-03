#pragma once

#ifndef __GAMEOBJECT_H__

class CGameObject
{
public:
	CGameObject();
	virtual ~CGameObject();

	CGameObject* GetTarget() const { return m_Target; }
	void SetTarget(CGameObject* val) { m_Target = val; }
	bool GetIsDead() const { return m_bIsDead; }
	void SetIsDead(bool val) { m_bIsDead = val; }
public:
	const INFO& GetInfo() const;
	const RECT& GetRect() const;

public:
	void SetPos(float x, float y);
	void SetAngle(float degree);

public:
	virtual void Initialize() = 0;
	virtual int Update() = 0;
	virtual void Render(HDC hDC) = 0;

protected:
	virtual void Release() = 0;	

public:
	bool IsDead();
	void CalcAngle(INFO _target);
	float Lerp(float p1, float p2, float d1);

protected:
	void UpdateRect();

protected:
	DWORD m_DwOldTime = GetTickCount();
	DWORD m_DwCurTime = 0;

	INFO	m_tInfo;
	CGameObject* m_Target;
	RECT	m_tRect;

	bool	m_bIsDead;
	float	m_fSpeed;
	float	m_fAngle;
	float	m_fRadian;
};

#define __GAMEOBJECT_H__
#endif

