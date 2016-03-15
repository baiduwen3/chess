// SearchEngine.h: interface for the CSearchEngine class.
///������������Ľӿںͼ������ú���
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
//���Ľӿڣ�Ϊ��ǰ�����߳���һ��
	virtual SearchAGoodMove(BYTE position[8][8])=0;
	//�趨����������
	virtual SetSearchDepth(int nDepth){m_nSearchDepth = nDepth;};
	//�趨��ֵ����
	virtual SetEveluator(CEveluation *pEval){m_pEval = pEval;};
//�趨�߷�������
	virtual SetMoveGenerator(CMoveGenerator *pMG){m_pMG = pMG;};

protected:
	//����ĳһ�߷������ߺ�����
	virtual BYTE MakeMove(CHESSMOVE* move);
	//�ָ�ĳһ�߷�
	virtual void UnMakeMove(CHESSMOVE* move,BYTE type);
	//�ж�ĳһ����Ƿ�ֳ�ʤ��
	virtual int IsGameOver(BYTE position[8][8], int nDepth);
	BYTE CurPosition[8][8];//����ʱ�õ����
	CHESSMOVE m_cmBestMove;//��¼����߷�
	CMoveGenerator *m_pMG;//�߷�������ָ��
	CEveluation *m_pEval;//��ֵ����ָ��
	int m_nSearchDepth;//����������
	int m_nMaxDepth;//��ǰ������������
};

#endif // !defined(AFX_SEARCHENGINE_H__FD959FD5_93C0_4C2E_A302_453BBCF87032__INCLUDED_)
