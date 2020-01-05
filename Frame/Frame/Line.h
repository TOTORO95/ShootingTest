#pragma once
#include "GameObject.h"
class CLine :
	public CGameObject
{
public:
	CLine();
	CLine(LONG startx, LONG starty, LONG endx, LONG endy);
	~CLine();

	// CGameObject을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;



};

