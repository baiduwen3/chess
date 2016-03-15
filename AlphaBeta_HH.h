// AlphaBeta_HH.h: interface for the CAlphaBeta_HH class.
//有历史启发的alpha beta 搜索引擎
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ALPHABETA_HH_H__5534A3BE_C0DB_4C67_B18F_448311A18340__INCLUDED_)
#define AFX_ALPHABETA_HH_H__5534A3BE_C0DB_4C67_B18F_448311A18340__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SearchEngine.h"
#include "HistoryHeuristic.h"

class CAlphaBeta_HH : 
	public CSearchEngine, 
	public CHistoryHeuristic  
{
public:
	CAlphaBeta_HH();
	virtual ~CAlphaBeta_HH();

	virtual SearchAGoodMove(BYTE position[8][8]);

protected:
	int alphabeta(int depth, int alpha, int beta);

};

#endif // !defined(AFX_ALPHABETA_HH_H__5534A3BE_C0DB_4C67_B18F_448311A18340__INCLUDED_)
