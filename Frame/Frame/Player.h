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
	// CGameObject��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Render(HDC hDC) override;

private:
	virtual void Release() override;

private:
	void KeyInput();

private:
	float			m_fGunX;	// ���� ���� X
	float			m_fGunY;	// ���� ���� Y
	float			m_fGunLength; // ���� ����

	OBJECT_LIST*	m_pBulletList;
	OBJECT_LIST*	m_pShieldList;
};

