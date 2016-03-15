// Eveluation.h: interface for the CEveluation class.
///估值核心
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EVELUATION_H__54518296_84B4_4F6B_9C63_D4427A0269C7__INCLUDED_)
#define AFX_EVELUATION_H__54518296_84B4_4F6B_9C63_D4427A0269C7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
//定义每种棋子的基本价值
////兵100 ，马350，象350，车500，后1000
#define BASEVALUE_PAWN 100
#define BASEVALUE_BISHOP 350
#define BASEVALUE_ROOK 500
#define BASEVALUE_KNIGHT 350
#define BASEVALUE_QUEEN 1000
#define BASEVALUE_KING 15000
//PG定义每种棋子的灵活性
//也就是每多一个可走的位置应加的分值
//兵15 ，马12，象12，车6，后3，王0
#define FLEXIBILITY_PAWN 15
#define FLEXIBILITY_BISHOP 12
#define FLEXIBILITY_KNIGHT 12
#define FLEXIBILITY_ROOK 6
#define FLEXIBILITY_QUEEN 3
#define FLEXIBILITY_KING 0
class CEveluation  
{
public:
	CEveluation();
	virtual ~CEveluation();
	//估值函数 bIsRedTurn标明轮到谁走棋
	virtual int Eveluate(BYTE position[8][8], BOOL bIsRedTurn);

protected:
	//列举与给定位置棋子相关的棋子
	int GetRelatePiece(BYTE position[8][8],int i, int j);
	//判断nFrom上的棋子能否走到 nTO位置
//	BOOL CanTouch(BYTE position[8][8], int nFromX, int nFromY, int nToX, int nToY);	
	//将一个位置加入 相关队列
	AddPoint(int x, int y);
	//取得不同位置兵的附加价值
	int GetBingValue(int x, int y, BYTE CurSituation[][8]);
	int m_BaseValue[13];//存放棋子基本价值
	int m_FlexValue[13];//存放棋子灵活性分值
	short m_AttackPos[8][8];//存放每一位置被 威胁的信息
	BYTE m_GuardPos[8][8];//存放每一位置被保护的信息
	BYTE m_FlexibilityPos[8][8];//存放每一位置上的棋子灵活性分值
	int m_chessValue[8][8];//存放每一位置上的棋子的总分值
	int nPosCount;//记录一个棋子的相关位置个数
	POINT RelatePos[30];//记录一个棋子的相关位置
};


#endif // !defined(AFX_EVELUATION_H__54518296_84B4_4F6B_9C63_D4427A0269C7__INCLUDED_)
