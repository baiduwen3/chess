// MoveGenerator.h: interface for the CMoveGenerator class.
////走法产生器
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MOVEGENERATOR_H__83658614_F014_4F54_A6DD_C71C37292A9D__INCLUDED_)
#define AFX_MOVEGENERATOR_H__83658614_F014_4F54_A6DD_C71C37292A9D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
//走法产生器
class CMoveGenerator  
{
public:
	CMoveGenerator();
	virtual ~CMoveGenerator();
	//用以检验一个走法是否合法
	static BOOL IsValidMove(BYTE position[8][8], int nFromX, 
								int nFromY, int nToX, int nToY);
	//产生给定棋局所有可能的走法
	int CreatePossibleMove(BYTE position[8][8], int nPly,int nSide);
	//存放走法
	CHESSMOVE m_MoveList[10][100];
protected:
	//给定棋局王的走法
	void Gen_KingMove(BYTE position[8][8], int i, int j, int nPly);//(x,y)=(i,j)
	//给定棋局车的走法
	void Gen_RookMove(BYTE position[8][8], int i, int j, int nPly);
	//给定棋局马的走法
	void Gen_KnightMove(BYTE position[8][8], int i, int j, int nPly);
	//给定棋局象的走法
	void Gen_BishopMove(BYTE position[8][8], int i, int j, int nPly);
	//给定棋局后的走法
	void Gen_QueenMove(BYTE position[8][8],  int i, int j, int nPly);
	//给定棋局红兵的走法
	void Gen_RPawnMove(BYTE position[8][8],  int i, int j, int nPly);
	//给定棋局黑兵的走法
	void Gen_BPawnMove(BYTE position[8][8], int i, int j, int nPly);
	//在m_moveList中加入一走法
	int AddMove(int nFromX, int nFromY,int nToX,int nToY,int nPly);
	//记录走法数量
	int m_nMoveCount;
};

#endif // !defined(AFX_MOVEGENERATOR_H__83658614_F014_4F54_A6DD_C71C37292A9D__INCLUDED_)
