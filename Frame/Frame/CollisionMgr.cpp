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

			// �� �簢���� �����Ǿ����� �Ǻ��ϴ� �Լ�. ���������� TRUE, �ƴϸ� FALSE ��ȯ.
			// �� �簢���� �����Ǿ��� �� ��ģ ������ �Ǵٸ� �簢���� ���������. 
			// �� ��ģ �簢���� ù��° ���ڷ� ��ȯ�Ѵ�.
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

				if (fMoveX > fMoveY) // Y������ �о
				{
					if (pDest->GetInfo().fY < fY)
						pSrc->SetPos(fX, fY + fMoveY);
					else
						pSrc->SetPos(fX, fY - fMoveY);
				}
				else // X������ �о
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
				//	cout << "�����浹" << endl;
				//	pDest->SetPos(pDest->GetInfo().fX, (IntersectLine(pDest, pSrc)));
				//}
			}
		}
	}


}

bool CCollisionMgr::IntersectSphere(CGameObject* pDest, CGameObject* pSource)
{
	// ���浹
	// �� ���� ������ ���� ���Ѵ�. r1 + r2
	// �� ���� ���� �� �Ÿ��� ���Ѵ�. d
	// r1 + r2 >= d ������ �����ϸ� TRUE


	float r1 = pDest->GetInfo().fCX * 0.5f;
	float r2 = pSource->GetInfo().fCX * 0.5f;

	float w = pDest->GetInfo().fX - pSource->GetInfo().fX;
	float h = pDest->GetInfo().fY - pSource->GetInfo().fY;

	// sqrtf: ������ ���ϴ� �Լ�. <cmath>���� ����.
	float d = sqrtf(w * w + h * h);

	return r1 + r2 >= d;
}

bool CCollisionMgr::IntersectRectEx(CGameObject* pDest, CGameObject* pSource, float* pMoveX, float* pMoveY)
{
	// x���� ������ �հ� �Ÿ��� ���Ѵ�.
	// �� �� x���� ������ ���� x���� �Ÿ����� ũ�� x������ ���ƴ�.
	float fSumX = pDest->GetInfo().fCX * 0.5f + pSource->GetInfo().fCX * 0.5f;
	float fDistX = fabs(pDest->GetInfo().fX - pSource->GetInfo().fX);


	// y���� ������ �հ� �Ÿ��� ���Ѵ�.
	// �� �� y���� ������ ���� y���� �Ÿ����� ũ�� y������ ���ƴ�.
	float fSumY = pDest->GetInfo().fCY * 0.5f + pSource->GetInfo().fCY * 0.5f;
	float fDistY = fabs(pDest->GetInfo().fY - pSource->GetInfo().fY);


	if (fSumX >= fDistX && fSumY >= fDistY)
	{
		// ��ģ������ ũ�� ���ϱ�.
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
