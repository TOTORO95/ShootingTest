#pragma once

#ifndef __BULLET_H__

#include "GameObject.h"
class CBullet :	public CGameObject
{
public:
	CBullet();
	CBullet(CGameObject * _gameobj, BULLET_TYPE _bulletType);
	virtual ~CBullet();

	BULLET_TYPE GetBulletType() const { return BulletType; }
	void SetBulletType(BULLET_TYPE val) { BulletType = val; }
public:
	// CGameObject을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Render(HDC hDC) override;
private:
	void Move();
	virtual void Release() override;
private:
	BULLET_TYPE BulletType;
};

#define __BULLET_H__
#endif
