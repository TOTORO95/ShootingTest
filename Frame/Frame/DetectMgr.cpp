#include "stdafx.h"
#include "DetectMgr.h"
#include "GameObject.h"

void CDetectMgr::DetectObj(OBJECT_LIST & dstList, OBJECT_LIST & srcList)
{

	for (auto pDest : dstList)
	{
		for (auto pSrc : srcList)
		{
			if (pDest->GetTarget() == nullptr|| pDest->IsDead())
				pDest->SetTarget(pSrc);
			
			pSrc->SetTarget(pDest);
		}
	}
}
