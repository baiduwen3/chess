// SearchEngine.cpp: implementation of the CSearchEngine class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "chess.h"
#include "SearchEngine.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSearchEngine::CSearchEngine()
{

}

CSearchEngine::~CSearchEngine()
{
	delete m_pMG;//删去挂在搜索引擎上的走法产生器
	delete m_pEval;//删去挂在搜索引擎上的估值核心
}

BYTE CSearchEngine::MakeMove(CHESSMOVE* move)
{
	BYTE nChessID,thisChessID;
	nChessID = CurPosition[move->To.y][move->To.x];
	thisChessID=CurPosition[move->From.y][move->From.x];
	CurPosition[move->To.y][move->To.x] = CurPosition[move->From.y][move->From.x];
	CurPosition[move->From.y][move->From.x] = NOCHESS;
	return nChessID;
}

void CSearchEngine::UnMakeMove(CHESSMOVE* move,BYTE nChessID)
{
	CurPosition[move->From.y][move->From.x] = CurPosition[move->To.y][move->To.x];
	CurPosition[move->To.y][move->To.x] = nChessID;
}


int CSearchEngine::IsGameOver(BYTE position[8][8], int nDepth)
{
	int i,j;
	BOOL RedLive = FALSE, BlackLive=FALSE; 
	
	for (i = 0; i < 8; i++)
		for (j = 0; j < 8; j++)
		{
			if (position[i][j] == B_KING)
				BlackLive = TRUE;
			if (position[i][j] == R_KING)
				RedLive  = TRUE;
		}

	i = (m_nMaxDepth - nDepth + 1) % 2;
	//以下的产生胜负已定局面的估值
	//
	if (!RedLive)//红方负
		if (i)
			return 19990 + nDepth;//奇数层返回极大值
		else
			return -19990 - nDepth;//偶数层返回极小值
	if (!BlackLive)//黑方负
		if (i)
			return -19990 - nDepth;//奇数层返回极小值
		else
			return 19990 + nDepth;//偶数层返回极大值
	return 0;
}
