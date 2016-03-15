// AlphaBeta_HH.cpp: implementation of the CAlphaBeta_HH class.
//有历史启发的alpha beta 搜索引擎
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "chess.h"
#include "AlphaBeta_HH.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CAlphaBeta_HH::CAlphaBeta_HH()
{

}

CAlphaBeta_HH::~CAlphaBeta_HH()
{

}
CAlphaBeta_HH::SearchAGoodMove(BYTE position[8][8])
{
	memcpy(CurPosition, position,64);
	m_nMaxDepth = m_nSearchDepth;
	ResetHistoryTable();//初始化历史记录表
	alphabeta(m_nMaxDepth, -20000, 20000);
	MakeMove(&m_cmBestMove);
	memcpy(position, CurPosition, 64);
}

int CAlphaBeta_HH::alphabeta(int depth, int alpha, int beta)
{
	int score;
	int Count,i;
	BYTE type;

	i = IsGameOver(CurPosition, depth);
	if (i != 0)
		return i;

	if (depth <= 0)	//叶子节点取估值
		return m_pEval->Eveluate(CurPosition, (m_nMaxDepth-depth)%2);
	
	Count = m_pMG->CreatePossibleMove(CurPosition, depth, (m_nMaxDepth-depth)%2);
	
//取所有走法的历史得分
	for (i=0;i<Count;i++) 
	{
		m_pMG->m_MoveList[depth][i].Score = 
			           GetHistoryScore(&m_pMG->m_MoveList[depth][i]);
	}
	//按历史得分排序
	MergeSort(m_pMG->m_MoveList[depth], Count, 0);
	int bestmove = -1;
	for (i=0;i<Count;i++) 
	{

		type = MakeMove(&m_pMG->m_MoveList[depth][i]);
		score = -alphabeta(depth - 1, -beta, -alpha);
		UnMakeMove(&m_pMG->m_MoveList[depth][i],type); 

		if (score > alpha)
		{
			alpha = score;
			if(depth == m_nMaxDepth)
				m_cmBestMove = m_pMG->m_MoveList[depth][i];
			bestmove = i;
		}
        if (alpha >= beta) 
		{
			bestmove = i;
			break;
		}
				
	}
	//将最佳走法汇入历史记录表
	if (bestmove != -1)
	EnterHistoryScore(&m_pMG->m_MoveList[depth][bestmove], depth);
	return alpha;
}

