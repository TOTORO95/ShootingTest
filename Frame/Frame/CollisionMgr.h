#pragma once
class CCollisionMgr
{
private:
	CCollisionMgr();
	~CCollisionMgr();

public:
	static void CollisionRect(OBJECT_LIST& dstList, OBJECT_LIST& srcList);
	static void CollisionRectEx(OBJECT_LIST& dstList, OBJECT_LIST& srcList);
	static void CollisionSphere(OBJECT_LIST& dstList, OBJECT_LIST& srcList);

private:
	static bool IntersectSphere(CGameObject* pDest, CGameObject* pSource);
	static bool IntersectRectEx(CGameObject* pDest, CGameObject* pSource, float* pMoveX, float* pMoveY);
};

