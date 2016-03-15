// PVS_Engine.h: interface for the CPVS_Engine class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PVS_ENGINE_H__1A29B62A_F1A4_4D4C_B223_4A5CE2456911__INCLUDED_)
#define AFX_PVS_ENGINE_H__1A29B62A_F1A4_4D4C_B223_4A5CE2456911__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SearchEngine.h"

class CPVS_Engine : public CSearchEngine  
{
public:
	CPVS_Engine();
	virtual ~CPVS_Engine();
	virtual SearchAGoodMove(BYTE position[8][8]);

protected:
	int PrincipalVariation(int depth, int alpha, int beta);
};

#endif // !defined(AFX_PVS_ENGINE_H__1A29B62A_F1A4_4D4C_B223_4A5CE2456911__INCLUDED_)
