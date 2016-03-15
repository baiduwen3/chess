// AlphaBetaEngine.h: interface for the CAlphaBetaEngine class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ALPHABETAENGINE_H__830DCDE9_368D_433F_98C4_44ECB8697C65__INCLUDED_)
#define AFX_ALPHABETAENGINE_H__830DCDE9_368D_433F_98C4_44ECB8697C65__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SearchEngine.h"

class CAlphaBetaEngine : public CSearchEngine  
{
public:
	CAlphaBetaEngine();
	virtual ~CAlphaBetaEngine();
	
	virtual SearchAGoodMove(BYTE position[8][8]);

protected:
	int alphabeta(int depth, int alpha, int beta);
};

#endif // !defined(AFX_ALPHABETAENGINE_H__830DCDE9_368D_433F_98C4_44ECB8697C65__INCLUDED_)
