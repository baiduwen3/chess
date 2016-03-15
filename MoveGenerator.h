// MoveGenerator.h: interface for the CMoveGenerator class.
////�߷�������
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MOVEGENERATOR_H__83658614_F014_4F54_A6DD_C71C37292A9D__INCLUDED_)
#define AFX_MOVEGENERATOR_H__83658614_F014_4F54_A6DD_C71C37292A9D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
//�߷�������
class CMoveGenerator  
{
public:
	CMoveGenerator();
	virtual ~CMoveGenerator();
	//���Լ���һ���߷��Ƿ�Ϸ�
	static BOOL IsValidMove(BYTE position[8][8], int nFromX, 
								int nFromY, int nToX, int nToY);
	//��������������п��ܵ��߷�
	int CreatePossibleMove(BYTE position[8][8], int nPly,int nSide);
	//����߷�
	CHESSMOVE m_MoveList[10][100];
protected:
	//������������߷�
	void Gen_KingMove(BYTE position[8][8], int i, int j, int nPly);//(x,y)=(i,j)
	//������ֳ����߷�
	void Gen_RookMove(BYTE position[8][8], int i, int j, int nPly);
	//�����������߷�
	void Gen_KnightMove(BYTE position[8][8], int i, int j, int nPly);
	//�����������߷�
	void Gen_BishopMove(BYTE position[8][8], int i, int j, int nPly);
	//������ֺ���߷�
	void Gen_QueenMove(BYTE position[8][8],  int i, int j, int nPly);
	//������ֺ�����߷�
	void Gen_RPawnMove(BYTE position[8][8],  int i, int j, int nPly);
	//������ֺڱ����߷�
	void Gen_BPawnMove(BYTE position[8][8], int i, int j, int nPly);
	//��m_moveList�м���һ�߷�
	int AddMove(int nFromX, int nFromY,int nToX,int nToY,int nPly);
	//��¼�߷�����
	int m_nMoveCount;
};

#endif // !defined(AFX_MOVEGENERATOR_H__83658614_F014_4F54_A6DD_C71C37292A9D__INCLUDED_)
