// PVS_Engine.cpp: implementation of the CPVS_Engine class.
//这是一种最小窗口搜索引擎，设定每一次搜索到的就是好的，直到找到一个更好的
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "chess.h"
#include "PVS_Engine.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPVS_Engine::CPVS_Engine()
{

}

CPVS_Engine::~CPVS_Engine()
{

}
CPVS_Engine::SearchAGoodMove(BYTE position[8][8])
{
	memcpy(CurPosition, position, 64);
	m_nMaxDepth = m_nSearchDepth;

//	for (m_nMaxDepth = 1; m_nMaxDepth <= m_nSearchDepth; m_nMaxDepth++)
	
	   PrincipalVariation(m_nMaxDepth, -20000, 20000);
	
	
	MakeMove(&m_cmBestMove);
	memcpy(position, CurPosition, 64);
}

int CPVS_Engine::PrincipalVariation(int depth, int alpha, int beta)
{
	int score;
	int Count,i;
	BYTE type;
	int best;

	i = IsGameOver(CurPosition, depth);
	if (i != 0)
		return i;

	if (depth <= 0)	//叶子节点取估值
		return m_pEval->Eveluate(CurPosition, (m_nMaxDepth-depth)%2);
	
	Count = m_pMG->CreatePossibleMove(CurPosition, depth, (m_nMaxDepth-depth)%2);
	
//产生第一个节点
	type = MakeMove(&m_pMG->m_MoveList[depth][0]);
	//使用全窗口搜索第一个节点
	best = -PrincipalVariation( depth-1, -beta, -alpha);
	//撤销第一个节点
	UnMakeMove(&m_pMG->m_MoveList[depth][0],type); 
	if(depth == m_nMaxDepth)
		m_cmBestMove = m_pMG->m_MoveList[depth][0];

	for (i=1;i<Count;i++) 
	{
		
		if(best < beta) 
		{
			if (best > alpha) 
				alpha = best;
			type = MakeMove(&m_pMG->m_MoveList[depth][i]);
			//使用极小窗口
			score = -PrincipalVariation(depth-1, -alpha-1, -alpha);
			if (score > alpha && score < beta) 
			{
				//fail high 重新搜索
				best = -PrincipalVariation(depth-1, -beta, -score);
				if(depth == m_nMaxDepth)
					m_cmBestMove = m_pMG->m_MoveList[depth][i];
			}
			else if (score > best)
			{
				best = score;//命中
				if(depth == m_nMaxDepth)
					m_cmBestMove = m_pMG->m_MoveList[depth][i];
			}
			UnMakeMove(&m_pMG->m_MoveList[depth][i],type); 
		}
	}

	return best;
}
