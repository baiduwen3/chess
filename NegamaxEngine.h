// NegamaxEngine.h: interface for the CNegamaxEngine class.
//������ֵ��������
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_NEGAMAXENGINE_H__985D7BFD_D003_4FFD_8683_74FB183FDDE4__INCLUDED_)
#define AFX_NEGAMAXENGINE_H__985D7BFD_D003_4FFD_8683_74FB183FDDE4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SearchEngine.h"

class CNegamaxEngine : public CSearchEngine  
{
public:
	CNegamaxEngine();
	virtual ~CNegamaxEngine();
	//�����ҳ���������ϵ���һ���߷�
	virtual SearchAGoodMove(BYTE position[8][8]);
	//SearchAGoodMove(BYTE position[8][8]);
protected:
	//������ֵ��������
	int NegaMax(int depth);
};

#endif // !defined(AFX_NEGAMAXENGINE_H__985D7BFD_D003_4FFD_8683_74FB183FDDE4__INCLUDED_)
