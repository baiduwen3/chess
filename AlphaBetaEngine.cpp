// AlphaBetaEngine.cpp: implementation of the CAlphaBetaEngine class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "chess.h"
#include "AlphaBetaEngine.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CAlphaBetaEngine::CAlphaBetaEngine()
{

}

CAlphaBetaEngine::~CAlphaBetaEngine()
{

}
CAlphaBetaEngine::SearchAGoodMove(BYTE position[8][8])
{
	memcpy(CurPosition, position, 64);
	m_nMaxDepth = m_nSearchDepth;
	alphabeta(m_nMaxDepth, -20000, 20000);
	MakeMove(&m_cmBestMove);
	memcpy(position, CurPosition, 64);
}

int CAlphaBetaEngine::alphabeta(int depth, int alpha, int beta)
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
		}
        if (alpha >= beta) 
              break;//剪枝，放弃搜索剩下的节点

				
	}
	return alpha;
}
