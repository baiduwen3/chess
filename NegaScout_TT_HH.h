// NegaScout_TT_HH.h: interface for the CNegaScout_TT_HH class.
//有历史启发，带置换表的alpha beta 搜索引擎
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_NEGASCOUT_TT_HH_H__0C4A34F8_2B85_4C8D_95EE_39371A0F37DE__INCLUDED_)
#define AFX_NEGASCOUT_TT_HH_H__0C4A34F8_2B85_4C8D_95EE_39371A0F37DE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SearchEngine.h"
#include "HistoryHeuristic.h"
#include "TranspositionTable.h"

class CNegaScout_TT_HH : 
	public CSearchEngine, 
	public CHistoryHeuristic, 
	public CTranspositionTable  
{
public:
	CNegaScout_TT_HH();
	virtual ~CNegaScout_TT_HH();

	virtual SearchAGoodMove(BYTE position[8][8]);

protected:
	int NegaScout(int depth, int alpha, int beta);
};

#endif // !defined(AFX_NEGASCOUT_TT_HH_H__0C4A34F8_2B85_4C8D_95EE_39371A0F37DE__INCLUDED_)
