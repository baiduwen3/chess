// Eveluation.cpp: implementation of the CEveluation class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "chess.h"
#include "Eveluation.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
//����ĸ���ֵ
const int BA0[8][8]=
{
	{1000,  1000,  1000,  1000,  1000,  1000,  1000,  1000},
	{100,100,100,100,100,100,100,100},
	{75,75,75,75 ,75 ,75,75,75},
	{30,30,70,100,100,70,30,30},
	{20,30,70,100,100,70,30,20},
	{20,20,30, 50, 50,30,20,20},
	{20,20,20, 20, 20,20,20,20},
	{ 0, 0, 0,  0,  0, 0, 0, 0},
};
//�ڱ��ĸ���ֵ
const int BA1[8][8]=
{	
	{ 0, 0, 0,  0,  0, 0, 0, 0},
	{20,20,20, 20, 20,20,20,20},
	{20,20,30, 50, 50,30,20,20},
	{20,30,70,100,100,70,30,20},
	{30,30,70,100,100,70,30,30},
	{75,75,75,75,75,75,75,75},
	{100,100,100,100,100,100,100,100},
	{1000,  1000,  1000,  1000,  1000,  1000,  1000,  1000},

};
//λ�Ʋ���
const int movex[9]={0,1,1,0,-1,-1,-1,0,1};
const int movey[9]={0,0,-1,-1,-1,0,1,1,1};
//���λ�Ʋ���
const int moveknightx[9]={0,2,2,1,-1,-2,-2,-1,1};
const int moveknighty[9]={0,1,-1,-2,-2,-1,1,2,2};

int CEveluation:: GetBingValue(int x, int y, BYTE CurSituation[][8])
{
	if (CurSituation[y][x] == R_PAWN)
		return BA0[y][x];
	
	if (CurSituation[y][x] == B_PAWN)
		return BA1[y][x];

	return 0;
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CEveluation::CEveluation()
{
	//��ʼ��
	m_BaseValue[B_KING] = BASEVALUE_KING; 
	m_BaseValue[B_ROOK] = BASEVALUE_ROOK; 
	m_BaseValue[B_KNIGHT] = BASEVALUE_KNIGHT; 
	m_BaseValue[B_BISHOP] = BASEVALUE_BISHOP; 
	m_BaseValue[B_QUEEN] = BASEVALUE_QUEEN; 
	m_BaseValue[B_PAWN] = BASEVALUE_PAWN; 

	m_BaseValue[R_KING] = BASEVALUE_KING; 
	m_BaseValue[R_ROOK] = BASEVALUE_ROOK; 
	m_BaseValue[R_KNIGHT] = BASEVALUE_KNIGHT; 
	m_BaseValue[R_BISHOP] = BASEVALUE_BISHOP; 
	m_BaseValue[R_QUEEN] = BASEVALUE_QUEEN; 
	m_BaseValue[R_PAWN] = BASEVALUE_PAWN; 

	m_FlexValue[B_KING] = FLEXIBILITY_KING; 
	m_FlexValue[B_ROOK] = FLEXIBILITY_ROOK; 
	m_FlexValue[B_KNIGHT] = FLEXIBILITY_KNIGHT; 
	m_FlexValue[B_BISHOP] = FLEXIBILITY_BISHOP; 
	m_FlexValue[B_QUEEN] = FLEXIBILITY_QUEEN; 
	m_FlexValue[B_PAWN] = FLEXIBILITY_PAWN; 

	m_FlexValue[R_KING] = FLEXIBILITY_KING; 
	m_FlexValue[R_ROOK] = FLEXIBILITY_ROOK; 
	m_FlexValue[R_KNIGHT] = FLEXIBILITY_KNIGHT; 
	m_FlexValue[R_BISHOP] = FLEXIBILITY_BISHOP; 
	m_FlexValue[R_QUEEN] = FLEXIBILITY_QUEEN; 
	m_FlexValue[R_PAWN] = FLEXIBILITY_PAWN; 

}

CEveluation::~CEveluation()
{
}
int count=0;//ȫ�ֱ�����ͳ�Ƶ��ù�ֵ�����Ĵ���
int CEveluation::Eveluate(BYTE position[8][8], BOOL bIsRedTurn)
{
	int i, j, k;
	int nChessType, nTargetType;
	count++;
//��ʼ����ʱ����
	memset(m_chessValue,0, 256);
	memset(m_AttackPos,0, 128); 
	memset(m_GuardPos,0, 64); 
	memset(m_FlexibilityPos, 0, 64);

	for(i = 0; i < 8; i++)
		for(j = 0; j < 8; j++)
		{
			if(position[i][j] != NOCHESS)
			{
				nChessType = position[i][j];
				GetRelatePiece(position, i, j);//y x
				for (k = 0; k < nPosCount; k++)
				{
					nTargetType = position[RelatePos[k].y][RelatePos[k].x];
					if (nTargetType == NOCHESS)
					{
						m_FlexibilityPos[i][j]++;	//���������
					}
					else
					{
						if (IsSameSide(nChessType, nTargetType))
						{
							m_GuardPos[RelatePos[k].y][RelatePos[k].x]++;
						}else
						{
							m_AttackPos[RelatePos[k].y][RelatePos[k].x]++;
							m_FlexibilityPos[i][j]++;	
							switch (nTargetType)
							{
							case R_KING:
								if (!bIsRedTurn)//���Ǻ����ܹ������ڷ�����һ�� �򷵻�ʧ�ܼ�ֵ
									return 18888;
								break;
							case B_KING:
								if (bIsRedTurn)//���Ǻ����ܹ������췽����һ�� �򷵻�ʧ�ܼ�ֵ
									return 18888;
								break;
							default://�������ӣ�������в��
								m_AttackPos[RelatePos[k].y][RelatePos[k].x] += (30 + (m_BaseValue[nTargetType] - m_BaseValue[nChessType])/10)/10;
								break;
							}
						}
					}
				}
			}
		}
//����ͳ��ɨ�赽������
	for(i = 0; i < 8; i++)
		for(j = 0; j < 8; j++)
		{
			if(position[i][j] != NOCHESS)
			{
				nChessType = position[i][j];
				m_chessValue[i][j]++;
				//��������Է� ֵ
				m_chessValue[i][j] += m_FlexValue[nChessType] * m_FlexibilityPos[i][j];
				//���ϱ��ĸ���ֵ
				m_chessValue[i][j] += GetBingValue(j, i, position);
			}
		}
	//����ͳ��ɨ�赽������
	int nHalfvalue;
	for(i = 0; i < 8; i++)
		for(j = 0; j <8; j++)
		{
			if(position[i][j] != NOCHESS)
			{
				nChessType = position[i][j];
				//���ӵĻ�����ֵ��1/16��Ϊ��в/����������
				nHalfvalue = m_BaseValue[nChessType]/16;
				//ÿ�����ӵĻ�����ֵ���ܼ�ֵ
				m_chessValue[i][j] += m_BaseValue[nChessType];
				
				if (IsRed(nChessType))
				{
					if (m_AttackPos[i][j])//��ǰ���屻��в
					{
						if (bIsRedTurn)//����ֵ�������
						{
							if (nChessType == R_KING)
							{
								m_chessValue[i][j]-= 20;//����Ǻ�����ֵ��20
							}
							else//��������
							{
								m_chessValue[i][j] -= nHalfvalue * 2;
								if (m_GuardPos[i][j])//������
									m_chessValue[i][j] += nHalfvalue;
							}
						}
						else//��ǰ���屻��в �ֵ�������
						{
							if (nChessType == R_KING)
								return 18888;//ʧ�� ������
							m_chessValue[i][j] -= nHalfvalue*10;
							if (m_GuardPos[i][j])
								m_chessValue[i][j] += nHalfvalue*9;
						}
						//���ϱ���в��
						///��ֹһ������вһ����������ֵ����û�з�Ӧ
						m_chessValue[i][j] -= m_AttackPos[i][j];
					}
					else//û���ܵ���в
					{
						if (m_GuardPos[i][j])//�ܵ��˱���������һ��ְ�
							m_chessValue[i][j] += 5;
					}
				}
				else//���� ͬ��
				{
					if (m_AttackPos[i][j])
					{
						if (!bIsRedTurn)
						{
							if (nChessType == B_KING)									
							{
								m_chessValue[i][j]-= 20;
							}
							else
							{
								m_chessValue[i][j] -= nHalfvalue * 2;
								if (m_GuardPos[i][j])
									m_chessValue[i][j] += nHalfvalue;
							}
						}
						else
						{
							if (nChessType == B_KING)
								return 18888;
							m_chessValue[i][j] -= nHalfvalue*10;
							if (m_GuardPos[i][j])
								m_chessValue[i][j] += nHalfvalue*9;
						}
						m_chessValue[i][j] -= m_AttackPos[i][j];
					}
					else
					{
						if (m_GuardPos[i][j])
							m_chessValue[i][j] += 5;
					}
				}
			}
		}
//������ͳ����ÿһ�����ӵ��ܼ�ֵ
//����ͳ�ƺ��˫�����ܷ�
	int nRedValue = 0; 
	int	nBlackValue = 0;

	for(i = 0; i < 8; i++)
		for(j = 0; j < 8; j++)
		{
			nChessType = position[i][j];
//			if (nChessType == R_KING || nChessType == B_KING)
//				m_chessValue[i][j] = 10000;	
			if (nChessType != NOCHESS)
			{
				if (IsRed(nChessType))//�Ѻ췽��ֵ����
				{
					nRedValue += m_chessValue[i][j];	
				}
				else//�Ѻڷ���ֵ����
				{
					nBlackValue += m_chessValue[i][j];	
				}
			}
		}
		//���ع�ֵ
		if (bIsRedTurn)
		{
			return nRedValue - nBlackValue;
		}
		else
		{
			return  nBlackValue-nRedValue ;
		}
}

CEveluation::AddPoint(int  x, int y)
{
	RelatePos[nPosCount].x = x;
	RelatePos[nPosCount].y = y;
	nPosCount++;
}

//λ�Ʋ���
//���λ�Ʋ���
//from MoveGenerator.cpp
//extern int movex[9],movey[9],moveknightx[9],moveknighty[9];
//�о����λ��
//���������ߵ�λ�úͿ��Ա�����λ��
//
int CEveluation::GetRelatePiece(BYTE position[8][8], int i, int j)//y x
{
	nPosCount = 0;//��AddPoint������
	BYTE nChessID;
//	BYTE flag;
	int k,x,y;
	
	nChessID = position[i][j];
	switch(nChessID)
	{
	case R_KING:
	case B_KING:

		for(k=1;k<9;k++)
		{
			x=j+movex[k];
			y=i+movey[k];
			if(x>=0&&x<8&&y>=0&&y<8)
				AddPoint(x, y);
		}		
		break;
						
	case R_BISHOP:				
	case B_BISHOP:
		
		for(k=2;k<9;k+=2)
		{
			x=j+movex[k];
			y=i+movey[k];
			while(x>=0&&x<8&&y>=0&&y<8)
			{
				if(NOCHESS==position[y][x])
					AddPoint(x,y);
				else//�����˵�һ������
				{
					AddPoint(x, y);
					break;
				}
				x+=movex[k];
				y+=movey[k];
			}
		}	
		break;
				
	case R_KNIGHT:		
	case B_KNIGHT:	
		
		for(k=1;k<9;k++)
		{
			x=j+moveknightx[k];
			y=i+moveknighty[k];
			if(x>=0&&x<8&&y>=0&&y<8)
				AddPoint(x, y);
		}	
		break;
					
	case R_ROOK:
	case B_ROOK:

		for(k=1;k<9;k+=2)
		{
			x=j+movex[k];
			y=i+movey[k];
			while(x>=0&&x<8&&y>=0&&y<8)
			{
				if(NOCHESS==position[y][x])
					AddPoint(x,y);
				else//�����˵�һ������
				{
					AddPoint(x, y);
					break;
				}
				x+=movex[k];
				y+=movey[k];
			}
		}	
		break;
					
	case B_PAWN:

		x=i;
		y=j+1;//��ǰһ����
		if(y<8&&NOCHESS==position[y][x])
			AddPoint(x,y);
		y=j+2;//��ǰ������
		if(j==1&&y<8&&NOCHESS==position[y][x])
			AddPoint(x,y);
		x=i-1;
		y=j+1;//����ǰ����
		if(x>=0&&y<8&&IsRed(position[y][x]))
			AddPoint(x,y);
		x=i+1;
		y=j+1;//����ǰ����
		if(x<8&&y<8&&IsRed(position[y][x]))
			AddPoint(x,y);
		break;
					
	case R_PAWN:
			
		x=i;
		y=j-1;//��ǰһ����
		if(y>=0&&NOCHESS==position[y][x])
			AddPoint(x,y);
		y=j-2;//��ǰ������
		if(j==6&&y>=0&&NOCHESS==position[y][x])
			AddPoint(x,y);
		x=i-1;
		y=j-1;//����ǰ����
		if(x>=0&&y>=0&&IsRed(position[y][x]))
			AddPoint(x,y);
		x=i+1;
		y=j-1;//����ǰ����
		if(x<8&&y>=0&&IsRed(position[y][x]))
			AddPoint(x,y);
		break;
				
	case B_QUEEN:
	case R_QUEEN:

		for(k=1;k<9;k+=1)
		{
			x=j+movex[k];
			y=i+movey[k];
			while(x>=0&&x<8&&y>=0&&y<8)
			{
				if(NOCHESS==position[y][x])
					AddPoint(x,y);
				else//�����˵�һ������
				{
					AddPoint(x, y);
					break;
				}
				x+=movex[k];
				y+=movey[k];
			}
		}	
		break;
					
	default:
		break;					
	}
	return nPosCount ;				
}