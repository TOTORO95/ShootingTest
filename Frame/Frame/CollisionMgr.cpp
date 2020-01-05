#include "stdafx.h"
#include "CollisionMgr.h"
#include "GameObject.h"

CCollisionMgr::CCollisionMgr()
{
}


CCollisionMgr::~CCollisionMgr()
{
}

void CCollisionMgr::CollisionRect(OBJECT_LIST& dstList, OBJECT_LIST& srcList)
{
	for (auto pDest : dstList)
	{
		for (auto pSrc : srcList)
		{
			RECT rc = {};

			// 두 사각형이 교차되었는지 판별하는 함수. 교차됐으면 TRUE, 아니면 FALSE 반환.
			// 두 사각형이 교차되었을 때 겹친 영역에 또다른 사각형이 만들어진다. 
			// 이 겹친 사각형을 첫번째 인자로 반환한다.
			if (IntersectRect(&rc, &pDest->GetRect(), &pSrc->GetRect()))
			{
				pDest->IsDead();
				pSrc->IsDead();
			}
		}
	}
}

void CCollisionMgr::CollisionRectEx(OBJECT_LIST& dstList, OBJECT_LIST& srcList)
{
	float fMoveX = 0.f, fMoveY = 0.f;

	for (auto pDest : dstList)
	{
		for (auto pSrc : srcList)
		{
			if (IntersectRectEx(pDest, pSrc, &fMoveX, &fMoveY))
			{
				float fX = pSrc->GetInfo().fX;
				float fY = pSrc->GetInfo().fY;

				if (fMoveX > fMoveY) // Y축으로 밀어냄
				{
					if (pDest->GetInfo().fY < fY)
						pSrc->SetPos(fX, fY + fMoveY);
					else
						pSrc->SetPos(fX, fY - fMoveY);
				}
				else // X축으로 밀어냄
				{
					if (pDest->GetInfo().fX < fX)
						pSrc->SetPos(fX + fMoveX, fY);
					else
						pSrc->SetPos(fX - fMoveX, fY);
				}
			}
		}
	}
}

void CCollisionMgr::CollisionSphere(OBJECT_LIST& dstList, OBJECT_LIST& srcList)
{
	for (auto pDest : dstList)
	{
		for (auto pSrc : srcList)
		{
			if (IntersectSphere(pDest, pSrc))
			{
				pDest->IsDead();
				pSrc->IsDead();
			}
		}
	}
}

void CCollisionMgr::CollsionLine(OBJECT_LIST & dstList, OBJECT_LIST & srcList)
{
	for (auto pDest : dstList)
	{
		for (auto pSrc : srcList)
		{
			if( pDest->GetInfo().fX>= pSrc->GetAreaInfo().ptStart.x 
				&& pDest->GetInfo().fX <= pSrc->GetAreaInfo().ptEnd.x)
			{
	
				pDest->SetFlatY(IntersectLine(pDest, pSrc));
				//if (!pDest->GetIsJump())
				//{
				//	cout << "수직충돌" << endl;
				//	pDest->SetPos(pDest->GetInfo().fX, (IntersectLine(pDest, pSrc)));
				//}
			}
		}
	}


}

bool CCollisionMgr::IntersectSphere(CGameObject* pDest, CGameObject* pSource)
{
	// 원충돌
	// 두 원의 반지름 합을 구한다. r1 + r2
	// 두 원의 중점 간 거리를 구한다. d
	// r1 + r2 >= d 조건을 만족하면 TRUE


	float r1 = pDest->GetInfo().fCX * 0.5f;
	float r2 = pSource->GetInfo().fCX * 0.5f;

	float w = pDest->GetInfo().fX - pSource->GetInfo().fX;
	float h = pDest->GetInfo().fY - pSource->GetInfo().fY;

	// sqrtf: 제곱근 구하는 함수. <cmath>에서 제공.
	float d = sqrtf(w * w + h * h);

	return r1 + r2 >= d;
}

bool CCollisionMgr::IntersectRectEx(CGameObject* pDest, CGameObject* pSource, float* pMoveX, float* pMoveY)
{
	// x축의 반지름 합과 거리를 구한다.
	// 이 때 x축의 반지름 합이 x축의 거리보다 크면 x쪽으로 겹쳤다.
	float fSumX = pDest->GetInfo().fCX * 0.5f + pSource->GetInfo().fCX * 0.5f;
	float fDistX = fabs(pDest->GetInfo().fX - pSource->GetInfo().fX);


	// y축의 반지름 합과 거리를 구한다.
	// 이 때 y축의 반지름 합이 y축의 거리보다 크면 y쪽으로 겹쳤다.
	float fSumY = pDest->GetInfo().fCY * 0.5f + pSource->GetInfo().fCY * 0.5f;
	float fDistY = fabs(pDest->GetInfo().fY - pSource->GetInfo().fY);


	if (fSumX >= fDistX && fSumY >= fDistY)
	{
		// 겹친영역의 크기 구하기.
		*pMoveX = fSumX - fDistX;
		*pMoveY = fSumY - fDistY;

		return true;
	}

	return false;
}

float CCollisionMgr::IntersectLine(CGameObject * pDest, CGameObject * pSrc)
{

	return ((pSrc->GetAreaInfo().ptEnd.y - pSrc->GetAreaInfo().ptStart.y)*
		(pDest->GetInfo().fX - pSrc->GetAreaInfo().ptStart.x) / 
		(pSrc->GetAreaInfo().ptEnd.x - pSrc->GetAreaInfo().ptStart.x) + pSrc->GetAreaInfo().ptStart.y) ;
}
