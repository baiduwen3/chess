// SearchEngine.h: interface for the CSearchEngine class.
///定义搜索引擎的接口和几个公用函数
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SEARCHENGINE_H__FD959FD5_93C0_4C2E_A302_453BBCF87032__INCLUDED_)
#define AFX_SEARCHENGINE_H__FD959FD5_93C0_4C2E_A302_453BBCF87032__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "MoveGenerator.h"
#include "Eveluation.h"

class CSearchEngine  
{
public:
	CSearchEngine();
	virtual ~CSearchEngine();
//博弈接口，为当前局面走出下一步
	virtual SearchAGoodMove(BYTE position[8][8])=0;
	//设定最大搜索深度
	virtual SetSearchDepth(int nDepth){m_nSearchDepth = nDepth;};
	//设定估值引擎
	virtual SetEveluator(CEveluation *pEval){m_pEval = pEval;};
//设定走法产生器
	virtual SetMoveGenerator(CMoveGenerator *pMG){m_pMG = pMG;};

protected:
	//根据某一走法产生走后的棋局
	virtual BYTE MakeMove(CHESSMOVE* move);
	//恢复某一走法
	virtual void UnMakeMove(CHESSMOVE* move,BYTE type);
	//判断某一棋局是否分出胜负
	virtual int IsGameOver(BYTE position[8][8], int nDepth);
	BYTE CurPosition[8][8];//搜索时用的棋局
	CHESSMOVE m_cmBestMove;//记录最佳走法
	CMoveGenerator *m_pMG;//走法产生器指针
	CEveluation *m_pEval;//估值核心指针
	int m_nSearchDepth;//最大搜索深度
	int m_nMaxDepth;//当前搜索的最大深度
};

#endif // !defined(AFX_SEARCHENGINE_H__FD959FD5_93C0_4C2E_A302_453BBCF87032__INCLUDED_)
