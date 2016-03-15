// AlphaBetaAndTT.h: interface for the CAlphaBetaAndTT class.
//´øÖÃ»»±íµÄalpha beta¼ôÖ¦
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ALPHABETAANDTT_H__E2F5F406_2D57_468E_93DD_B3872DF2A020__INCLUDED_)
#define AFX_ALPHABETAANDTT_H__E2F5F406_2D57_468E_93DD_B3872DF2A020__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SearchEngine.h"
#include "TranspositionTable.h"

class CAlphaBetaAndTT : 
	public CSearchEngine, 
	public CTranspositionTable  
{
public:
	CAlphaBetaAndTT();
	virtual ~CAlphaBetaAndTT();

	virtual SearchAGoodMove(BYTE position[8][8]);
protected:
	int alphabeta(int depth, int alpha, int beta);
};

#endif // !defined(AFX_ALPHABETAANDTT_H__E2F5F406_2D57_468E_93DD_B3872DF2A020__INCLUDED_)
