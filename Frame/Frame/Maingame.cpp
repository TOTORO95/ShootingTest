#include "stdafx.h"
#include "Maingame.h"
#include "Player.h"
#include "Monster.h"

CMaingame::CMaingame()
{
}

CMaingame::~CMaingame()
{
	Release();
}

void CMaingame::Initialize()
{
	srand(unsigned(time(nullptr)));

	m_hDC = GetDC(g_hWnd);	

	// Player	
	m_ObjectList[PLAYER].push_back(CObjectFactory<CPlayer>::CreateObject());
	//dynamic_cast<CPlayer*>(m_ObjectList[PLAYER].front())->SetBulletList(&m_ObjectList[BULLET]);
	//dynamic_cast<CPlayer*>(m_ObjectList[PLAYER].front())->SetShieldList(&m_ObjectList[SHIELD]);

	// Monster
	//float fX = 0.f, fY = 0.f;

	//for (int i = 0; i < 5; ++i)
	//{
	//	fX = float(rand() % WINCX);
	//	fY = float(rand() % WINCY);		

	//	m_ObjectList[MONSTER].push_back(CObjectFactory<CMonster>::CreateObject(fX, fY));
	//}
}

void CMaingame::Update()
{
	// ���ͷ����� ����(�ݺ��� ����)
	// ��ü ���� ���ϼ��� ������ �� ������ ����
	for (int i = 0; i < OBJECT_END; ++i)
	{
		auto iter_begin = m_ObjectList[i].begin();
		auto iter_end = m_ObjectList[i].end();

		for (; iter_begin != iter_end; )
		{
			int iEvent = (*iter_begin)->Update();

			if (DEAD_OBJ == iEvent)
			{
				SafeDelete((*iter_begin));
				iter_begin = m_ObjectList[i].erase(iter_begin);
			}
			else
				++iter_begin;
		}
	}

	//CCollisionMgr::CollisionRect(m_ObjectList[BULLET], m_ObjectList[MONSTER]);
	//CCollisionMgr::CollisionSphere(m_ObjectList[SHIELD], m_ObjectList[BULLET]);
	//CCollisionMgr::CollisionSphere(m_ObjectList[BULLET], m_ObjectList[MONSTER]);
	//CCollisionMgr::CollisionRectEx(m_ObjectList[MONSTER], m_ObjectList[PLAYER]);
	//CDetectMgr::DetectObj(m_ObjectList[PLAYER], m_ObjectList[MONSTER]);
}

void CMaingame::Render()
{
	Rectangle(m_hDC, 0, 0, WINCX, WINCY);

	// ���ͷ����� ����(�ݺ��� ����)
	for (int i = 0; i < OBJECT_END; ++i)
	{
		auto iter_begin = m_ObjectList[i].begin();
		auto iter_end = m_ObjectList[i].end();

		for (; iter_begin != iter_end; ++iter_begin)
			(*iter_begin)->Render(m_hDC);
	}	

	// �ؽ�Ʈ ���.
	//TCHAR szBuf[64] = L"";
	//swprintf_s(szBuf, L"Bullet size: %d", m_ObjectList[BULLET].size());

	//TextOut: ������ ��ǥ�κ��� �ؽ�Ʈ ���
	//TextOut(m_hDC, 100, 100, szBuf, lstrlen(szBuf));

	//DrawText: ������ �簢�� ���� �ȿ� �ؽ�Ʈ ���
	//RECT rc = { 100, 100, 200, 200 };
	//DrawText(m_hDC, szBuf, lstrlen(szBuf), &rc, DT_NOCLIP);

}

void CMaingame::Release()
{
	ReleaseDC(g_hWnd, m_hDC);	

	for (int i = 0; i < OBJECT_END; ++i)
	{
		for_each(m_ObjectList[i].begin(), m_ObjectList[i].end(), SafeDelete<CGameObject*>);
		m_ObjectList[i].clear();
	}
}
