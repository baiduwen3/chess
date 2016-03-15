// NegamaxEngine.cpp: implementation of the CNegamaxEngine class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "chess.h"
#include "NegamaxEngine.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CNegamaxEngine::CNegamaxEngine()
{

}

CNegamaxEngine::~CNegamaxEngine()
{

}
CNegamaxEngine::SearchAGoodMove(BYTE position[8][8])
{
	m_nMaxDepth = m_nSearchDepth;//������������
//��������
	memcpy(CurPosition, position, 64);
	//�ҳ�����߷�
	NegaMax(m_nMaxDepth);
	//����
	MakeMove(&m_cmBestMove);
	//�����ߺ�����
	memcpy(position, CurPosition, 64);
}
//extern int count;

int CNegamaxEngine::NegaMax(int depth)
{
	int current = -20000 ;
	int score;
	int Count,i;
	BYTE type;

	i = IsGameOver(CurPosition, depth);
	if (i != 0)
		return i;

	if (depth <= 0)	//Ҷ�ӽڵ�ȡ��ֵ
    	return m_pEval->Eveluate(CurPosition, (m_nMaxDepth-depth)%2);
	
	Count = m_pMG->CreatePossibleMove(CurPosition, depth, (m_nMaxDepth-depth)%2);
//���������߷�
	for (i=0;i<Count;i++) 
	{

		type = MakeMove(&m_pMG->m_MoveList[depth][i]);
		score = -NegaMax(depth - 1);
		UnMakeMove(&m_pMG->m_MoveList[depth][i],type); 
		
		if (score > current)//�����ֵ
		{
			current = score;
			if(depth == m_nMaxDepth)//��Ѱ����߷�
			{
				m_cmBestMove = m_pMG->m_MoveList[depth][i];
			}
		}

	}

	return current;
}
