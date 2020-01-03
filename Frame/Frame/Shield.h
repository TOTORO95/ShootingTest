#pragma once
#include "GameObject.h"
class CShield :
	public CGameObject
{
public:
	CShield();
	CShield(CGameObject* _gameobj);
	virtual ~CShield();

public:
	// CGameObject��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Render(HDC hDC) override;

private:
	virtual void Release() override;

private:
	float			m_fDistance;
	CGameObject*	m_pTarget;
};

