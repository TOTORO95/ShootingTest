#pragma once
#include "GameObject.h"
class CPlayer :	public CGameObject
{
public:
	CPlayer();
	virtual ~CPlayer();

public:
	void SetBulletList(OBJECT_LIST* pBulletList);
	void SetShieldList(OBJECT_LIST* pShieldList);

public:
	// CGameObject을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Render(HDC hDC) override;

private:
	virtual void Release() override;

private:
	void KeyInput();

private:
	float			m_fGunX;	// 포신 끝점 X
	float			m_fGunY;	// 포신 끝점 Y
	float			m_fGunLength; // 포신 길이

	OBJECT_LIST*	m_pBulletList;
	OBJECT_LIST*	m_pShieldList;
};

