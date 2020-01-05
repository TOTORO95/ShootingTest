#pragma once

#ifndef __OBJECT_FACTORY_H__

class CGameObject;

/* 추상 팩토리 패턴 */
// 객체 생성 통일 및 캡슐화에 초점을 둔 디자인 패턴

template <typename T>
class CObjectFactory 
{
public:
	static CGameObject* CreateObject()
	{
		CGameObject* pObject = new T;
		pObject->Initialize();	

		return pObject;
	}
	static CGameObject* CreateObject(CGameObject* _gameobj)
	{
		CGameObject* pObject = new T(_gameobj);
		pObject->Initialize();

		return pObject;
	}

	static CGameObject* CreateObject(float x, float y)
	{
		CGameObject* pObject = new T;
		pObject->Initialize();
		pObject->SetPos(x, y);

		return pObject;
	}

	static CGameObject* CreateObject(float x, float y, float degree, CGameObject* _gameobj,BULLET_TYPE _type=STRAIGHT)
	{
		CGameObject* pObject = new T(_gameobj, _type);
		pObject->Initialize();
		pObject->SetPos(x, y);
		pObject->SetAngle(degree);

		return pObject;
	}
	static CGameObject* CreateObject(LONG startx, LONG starty, LONG endx, LONG endy)
	{
		CGameObject* pObject = new T(startx,starty,endx,endy);
		pObject->Initialize();

		return pObject;
	}


};

#define __OBJECT_FACTORY_H__
#endif
