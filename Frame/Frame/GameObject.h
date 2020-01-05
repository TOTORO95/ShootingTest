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
	OBJECT_TYPE GetObjType() const { return m_ObjType; }
	void SetObjType(OBJECT_TYPE val) { m_ObjType = val; }
	TagArea GetAreaInfo() const { return m_tAreaInfo; }
	void SetAreaInfo(TagArea val) { m_tAreaInfo = val; }
	bool GetIsJump() const { return m_bIsJump; }
	void SetIsJump(bool val) { m_bIsJump = val; }
	float GetFlatY() const { return m_fFlatY; }
	void SetFlatY(float val) { m_fFlatY = val; }
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
	TagArea m_tAreaInfo;
	DWORD m_DwOldTime = GetTickCount();
	DWORD m_DwCurTime = 0;

	OBJECT_TYPE m_ObjType;
	INFO	m_tInfo;
	CGameObject* m_Target;
	RECT	m_tRect;
	bool	m_bIsJump;
	bool	m_bIsDead;
	float	m_fSpeed;
	float	m_fAngle;
	float	m_fRadian;
	float	m_fFlatY;

};

#define __GAMEOBJECT_H__
#endif

