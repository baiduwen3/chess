// AlphaBetaAndTT.cpp: implementation of the CAlphaBetaAndTT class.
//带置换表的alpha beta剪枝
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "chess.h"
#include "AlphaBetaAndTT.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CAlphaBetaAndTT::CAlphaBetaAndTT()
{

}

CAlphaBetaAndTT::~CAlphaBetaAndTT()
{

}
CAlphaBetaAndTT::SearchAGoodMove(BYTE position[8][8])
{
	memcpy(CurPosition, position,64);
	CalculateInitHashKey(CurPosition);//计算初始棋盘哈希值
	m_nMaxDepth = m_nSearchDepth;
	alphabeta(m_nMaxDepth, -20000, 20000);
	MakeMove(&m_cmBestMove);
	memcpy(position, CurPosition, 64);
}


int CAlphaBetaAndTT::alphabeta(int depth, int alpha, int beta)
{
	int score;
	int Count,i;
	BYTE type;
	int side;

	i = IsGameOver(CurPosition, depth);
	if (i != 0)
		return i;

	side = (m_nMaxDepth-depth)%2;

	score = LookUpHashTable(alpha, beta, depth, side); 
	if (score != 66666) 
		return score;

	if (depth <= 0)	//叶子节点取估值
	{
		score = m_pEval->Eveluate(CurPosition, side );
		//将求得的估值放进置换表
		EnterHashTable(exact, score, depth, side );
		return score;
	}



	Count = m_pMG->CreatePossibleMove(CurPosition, depth, side);
	
    int eval_is_exact = 0;

	for (i=0;i<Count;i++) 
	{
		//产生该走法所对应节点的哈希值
		Hash_MakeMove(&m_pMG->m_MoveList[depth][i], CurPosition);
		type = MakeMove(&m_pMG->m_MoveList[depth][i]);
		
		score = -alphabeta(depth - 1, -beta, -alpha);
		//恢复当前节点的哈希值
		Hash_UnMakeMove(&m_pMG->m_MoveList[depth][i],type, CurPosition); 
		UnMakeMove(&m_pMG->m_MoveList[depth][i],type); 
        if (score >= beta) 
		{
			//将节点下边界存入置换表
			EnterHashTable(lower_bound, score, depth,side);
            return score;
        }

		if (score > alpha)
		{
			alpha = score;
			eval_is_exact = 1;
			if(depth == m_nMaxDepth)
				m_cmBestMove = m_pMG->m_MoveList[depth][i];
		}

	}
//将搜索结果放进置换表
    if (eval_is_exact) //确切值
		EnterHashTable(exact, alpha, depth,side);
    else //上边界
		EnterHashTable(upper_bound, alpha, depth,side);
	return alpha;
}
