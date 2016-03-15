// Eveluation.h: interface for the CEveluation class.
///��ֵ����
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EVELUATION_H__54518296_84B4_4F6B_9C63_D4427A0269C7__INCLUDED_)
#define AFX_EVELUATION_H__54518296_84B4_4F6B_9C63_D4427A0269C7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
//����ÿ�����ӵĻ�����ֵ
////��100 ����350����350����500����1000
#define BASEVALUE_PAWN 100
#define BASEVALUE_BISHOP 350
#define BASEVALUE_ROOK 500
#define BASEVALUE_KNIGHT 350
#define BASEVALUE_QUEEN 1000
#define BASEVALUE_KING 15000
//PG����ÿ�����ӵ������
//Ҳ����ÿ��һ�����ߵ�λ��Ӧ�ӵķ�ֵ
//��15 ����12����12����6����3����0
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
	//��ֵ���� bIsRedTurn�����ֵ�˭����
	virtual int Eveluate(BYTE position[8][8], BOOL bIsRedTurn);

protected:
	//�о������λ��������ص�����
	int GetRelatePiece(BYTE position[8][8],int i, int j);
	//�ж�nFrom�ϵ������ܷ��ߵ� nTOλ��
//	BOOL CanTouch(BYTE position[8][8], int nFromX, int nFromY, int nToX, int nToY);	
	//��һ��λ�ü��� ��ض���
	AddPoint(int x, int y);
	//ȡ�ò�ͬλ�ñ��ĸ��Ӽ�ֵ
	int GetBingValue(int x, int y, BYTE CurSituation[][8]);
	int m_BaseValue[13];//������ӻ�����ֵ
	int m_FlexValue[13];//�����������Է�ֵ
	short m_AttackPos[8][8];//���ÿһλ�ñ� ��в����Ϣ
	BYTE m_GuardPos[8][8];//���ÿһλ�ñ���������Ϣ
	BYTE m_FlexibilityPos[8][8];//���ÿһλ���ϵ���������Է�ֵ
	int m_chessValue[8][8];//���ÿһλ���ϵ����ӵ��ܷ�ֵ
	int nPosCount;//��¼һ�����ӵ����λ�ø���
	POINT RelatePos[30];//��¼һ�����ӵ����λ��
};


#endif // !defined(AFX_EVELUATION_H__54518296_84B4_4F6B_9C63_D4427A0269C7__INCLUDED_)
