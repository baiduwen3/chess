// MoveGenerator.cpp: implementation of the CMoveGenerator class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "chess.h"
#include "MoveGenerator.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMoveGenerator::CMoveGenerator()
{

}

CMoveGenerator::~CMoveGenerator()
{

}
int CMoveGenerator::AddMove(int nFromX, int nFromY, int nToX, int nToY,int nPly)
{
	m_MoveList[nPly][m_nMoveCount].From.x = nFromX;
	m_MoveList[nPly][m_nMoveCount].From.y = nFromY;
	m_MoveList[nPly][m_nMoveCount].To.x = nToX;
	m_MoveList[nPly][m_nMoveCount].To.y = nToY;
	m_nMoveCount++;
	return m_nMoveCount;
}
//nPly ��ǰ��������
///nSide ָ����һ���ߣ�TRUEΪ�췽 FALSEΪ�ڷ�
///
int CMoveGenerator::CreatePossibleMove(BYTE position[8][8], int nPly, int nSide)
{
	int     nChessID;
	int		i,j;
	
	m_nMoveCount = 0;
	for (i = 0; i < 8; i++)//x
		for (j = 0; j < 8; j++)//y
		{
			if (position[j][i] != NOCHESS)
			{
				nChessID = position[j][i];
				if (!nSide && IsRed(nChessID))
					continue;//�����������߷�����������
				if (nSide && IsBlack(nChessID))
					continue;//�����������߷�����������
				switch(nChessID)
				{
				case R_KING:
				case B_KING://��
					Gen_KingMove(position, i, j, nPly);
					break;
					
				case R_BISHOP://��
				case B_BISHOP:
					Gen_BishopMove(position, i, j, nPly);
					break;
					
				case R_KNIGHT:		
				case B_KNIGHT://��	
					Gen_KnightMove(position, i, j, nPly);
					break;
					
				case R_ROOK:
				case B_ROOK://��
					Gen_RookMove(position, i, j, nPly);
					break;
					
				case R_PAWN://���
					Gen_RPawnMove(position, i, j, nPly);
					break;
					
				case B_PAWN://�ڱ�
					Gen_BPawnMove(position, i, j, nPly);
					break;
					
				case B_QUEEN:
				case R_QUEEN://��
					Gen_QueenMove(position, i, j, nPly);
					break;
					
				default:
					break;
					
				}
			}
		}
		
		return m_nMoveCount;//�����߷�����
}
//�жϸ�������ϣ���From ��To�Ƿ�Ϸ�
//���Ϸ�����TRUE ����FALSE
BOOL CMoveGenerator::IsValidMove(BYTE position[8][8], int nFromX, int nFromY, int nToX, int nToY)
{
	int i, j;
	int nMoveChessID, nTargetID;
	
	if (nFromY ==  nToY && nFromX == nToX)
		return FALSE;//Ŀ����Դ��ͬ
	
	nMoveChessID = position[nFromY][nFromX];
	nTargetID = position[nToY][nToX];
	
	if (IsSameSide(nMoveChessID, nTargetID))
		return FALSE;//���ܳ��Լ�����
	
	switch(nMoveChessID)
	{
	case R_KING: //��  
	case B_KING:
		if(abs(nFromY - nToY)>1) 
			return FALSE;//��ֻ���ߵ����ܱߵĸ�����
		if(abs(nToX - nFromX)>1)
			return FALSE;//��������ֱ����������
		break;

	case R_BISHOP:  //�� 
	case B_BISHOP:  
		if(abs(nFromY - nToY) != abs(nToX - nFromX)) 
			return FALSE;//��ֻ����б��
		if(nToY>nFromY)//����
		{
			if(nToX>nFromX)//�����·���
			{
				for(i=nFromY+1,j=nFromX+1;i<nToY&&j<nToX;i++,j++)
					if(position[i][j] != NOCHESS)
						return FALSE;
			}
			else//�����·���
			{
				for(i=nFromY+1,j=nFromX-1;i<nToY&&j>nToX;i++,j--)
					if(position[i][j] != NOCHESS)
						return FALSE;
			}
		}
		else //����
		{
			if(nToX>nFromX)//�����Ϸ���
			{
				for(i=nFromY-1,j=nFromX+1;i>nToY&&j<nToX;i--,j++)
					if(position[i][j] != NOCHESS)
						return FALSE;
			}
			else//�����Ϸ���
			{
				for(i=nFromY-1,j=nFromX-1;i>nToY&&j>nToX;i--,j--)
					if(position[i][j] != NOCHESS)
						return FALSE;
			}
		}
		break;
		
		
	case B_PAWN: 	//�ڱ�
		if(nFromX!=nToX)
		{
			if(abs(nFromX-nToX)==1 && (nFromY-nToY==-1) && IsRed(nTargetID))
				return TRUE;//��
			else
				return	FALSE;
		}
		else 
		{
			if(nFromY-nToY==-1&&nTargetID==NOCHESS)
				return TRUE;//����һ��
			else 
				if(nFromY==1 && (nFromY-nToY)==-2&&nTargetID==NOCHESS&&position[nFromY+1][nFromX]==NOCHESS)//��һ�����˶���
					return TRUE;
				else
					return FALSE;
		}
		break;
		
	case R_PAWN:    //���
		if(nFromX!=nToX)
		{
			if(abs(nFromX-nToX)==1 && (nFromY-nToY==1) && IsBlack(nTargetID))
				return TRUE;//��
			else
				return	FALSE;
		}
		else 
		{
			if(nFromY-nToY==1&&nTargetID==NOCHESS)
				return TRUE;//����һ��
			else 
				if(nFromY==6 && (nFromY-nToY)==2&&nTargetID==NOCHESS&&position[nFromY-1][nFromX]==NOCHESS)//��һ�����˶���
					return TRUE;
				else
					return FALSE;
		}
		break;
		
	case B_ROOK:      
	case R_ROOK:  //��  
		
		if(nFromY != nToY && nFromX != nToX)
			return FALSE;	//����ֱ��:
		
		if(nFromY == nToY)//·���м������ӵ���
		{
			if(nFromX < nToX)
			{
				for(i = nFromX + 1; i < nToX; i++)
					if(position[nFromY][i] != NOCHESS)
						return FALSE;

			}
			else
			{
				for(i = nToX + 1; i < nFromX; i++)
					if(position[nFromY][i] != NOCHESS)
						return FALSE;
			}
		}
		else
		{
			if(nFromY < nToY)
			{
				for(j = nFromY + 1; j < nToY; j++)
					if(position[j][nFromX] != NOCHESS)
						return FALSE;
			}
			else
			{
				for(j= nToY + 1; j < nFromY; j++)
					if(position[j][nFromX] != NOCHESS)
						return FALSE;
			}
		}
		
		break;
		
	case B_KNIGHT:    
	case R_KNIGHT://��
		
		if(!((abs(nToX-nFromX)==1 && abs(nToY-nFromY)==2)
			||(abs(nToX-nFromX)==2&&abs(nToY-nFromY)==1)))
			return FALSE;//��������
		break;
	
	case B_QUEEN:    
	case R_QUEEN://��
		if(!(nFromY == nToY || nFromX == nToX ||
							(abs(nFromY - nToY) == abs(nToX - nFromX))))
			return FALSE;//��ֱ��Ҳ��б��
		/////////////////////////////////
		//·���м������ӵ���
		if(nFromY == nToY)
		{
			if(nFromX < nToX)
			{
				for(i = nFromX + 1; i < nToX; i++)
					if(position[nFromY][i] != NOCHESS)
						return FALSE;

			}
			else
			{
				for(i = nToX + 1; i < nFromX; i++)
					if(position[nFromY][i] != NOCHESS)
						return FALSE;
			}
		}
		else//Y!=Y
		{
			if(nFromX == nToX)
			{
				if(nFromY < nToY)
				{
					for(j = nFromY + 1; j < nToY; j++)
						if(position[j][nFromX] != NOCHESS)
							return FALSE;
				}
				else
				{
					for(j= nToY + 1; j < nFromY; j++)
						if(position[j][nFromX] != NOCHESS)
							return FALSE;
				}
			}//if X==X &&Y!=Y
			else//X!=x && Y!=Y ��б��
			{
				if(nToY>nFromY)//����
				{
					if(nToX>nFromX)//�����·���
					{
						for(i=nFromY+1,j=nFromX+1;i<nToY&&j<nToX;i++,j++)
							if(position[i][j] != NOCHESS)
								return FALSE;
					}
					else//�����·���
					{
						for(i=nFromY+1,j=nFromX-1;i<nToY&&j>nToX;i++,j--)
							if(position[i][j] != NOCHESS)
								return FALSE;
					}
				}
				else //�� ��
				{
					if(nToX>nFromX)//�����Ϸ���
					{
						for(i=nFromY-1,j=nFromX+1;i>nToY&&j<nToX;i--,j++)
							if(position[i][j] != NOCHESS)
								return FALSE;
					}
					else//�����Ϸ���
					{
						for(i=nFromY-1,j=nFromX-1;i>nToY&&j>nToX;i--,j--)
							if(position[i][j] != NOCHESS)
								return FALSE;
					}
				}
			}//else X!=x && Y!=Y
		}//else Y!=Y
		break;
	default:
		return FALSE;
	}
	
	return TRUE;
}
//λ�Ʋ���
const int movex[9]={0,1,1,0,-1,-1,-1,0,1};
const int movey[9]={0,0,-1,-1,-1,0,1,1,1};
//���λ�Ʋ���
const int moveknightx[9]={0,2,2,1,-1,-2,-2,-1,1};
const int moveknighty[9]={0,1,-1,-2,-2,-1,1,2,2};
///�������ĺϷ��߷�
///i,j��ʾ����λ�� nPly��ʾ���뵽List�ڼ���
void CMoveGenerator::Gen_KingMove(BYTE position[8][8], int i, int j, int nPly)
{
	int k,x,y;
	for(k=1;k<9;k++)
	{
		x=i+movex[k];
		y=j+movey[k];
		if(x>=0&&x<8&&y>=0&&y<8&&IsValidMove(position,i,j,x,y))
			AddMove(i,j,x,y,nPly);
	}		
}
//������ĺϷ��߷�
///i,j��ʾ����λ�� nPly��ʾ���뵽List�ڼ���/
void CMoveGenerator::Gen_BishopMove(BYTE position[8][8], int i, int j, int nPly)
{
	int k,x,y;
	for(k=2;k<9;k+=2)
	{
		x=i+movex[k];
		y=j+movey[k];
		while(x>=0&&x<8&&y>=0&&y<8)
		{
			if(IsValidMove(position,i,j,x,y))
				AddMove(i,j,x,y,nPly);
			x+=movex[k];
			y+=movey[k];
		}
	}	
}
//������ĺϷ��߷�
///i,j��ʾ����λ�� nPly��ʾ���뵽List�ڼ���
void CMoveGenerator::Gen_KnightMove(BYTE position[8][8], int i, int j, int nPly)
{
	int k,x,y;
	for(k=1;k<9;k++)
	{
		x=i+moveknightx[k];
		y=j+moveknighty[k];
		if(x>=0&&x<8&&y>=0&&y<8&&IsValidMove(position,i,j,x,y))
			AddMove(i,j,x,y,nPly);
	}	
}
//��������ĺϷ��߷�
///i,j��ʾ����λ�� nPly��ʾ���뵽List�ڼ���
void CMoveGenerator::Gen_RPawnMove(BYTE position[8][8], int i, int j, int nPly)
{
	int x,y;
	x=i;
	y=j-1;//��ǰһ����
	if(x>=0&&x<8&&y>=0&&y<8&&IsValidMove(position,i,j,x,y))
		AddMove(i,j,x,y,nPly);
	y=j-2;//��ǰ������
	if(x>=0&&x<8&&y>=0&&y<8&&IsValidMove(position,i,j,x,y))
		AddMove(i,j,x,y,nPly);
	x=i-1;
	y=j-1;//����ǰ����
	if(x>=0&&x<8&&y>=0&&y<8&&IsValidMove(position,i,j,x,y))
		AddMove(i,j,x,y,nPly);
	x=i+1;
	y=j-1;//����ǰ����
	if(x>=0&&x<8&&y>=0&&y<8&&IsValidMove(position,i,j,x,y))
		AddMove(i,j,x,y,nPly);
}
//�����ڱ��ĺϷ��߷�
///i,j��ʾ����λ�� nPly��ʾ���뵽List�ڼ���
void CMoveGenerator::Gen_BPawnMove(BYTE position[8][8], int i, int j, int nPly)
{
	int x,y;
	x=i;
	y=j+1;//��ǰһ����
	if(x>=0&&x<8&&y>=0&&y<8&&IsValidMove(position,i,j,x,y))
		AddMove(i,j,x,y,nPly);
	y=j+2;//��ǰ������
	if(x>=0&&x<8&&y>=0&&y<8&&IsValidMove(position,i,j,x,y))
		AddMove(i,j,x,y,nPly);
	x=i-1;
	y=j+1;//����ǰ����
	if(x>=0&&x<8&&y>=0&&y<8&&IsValidMove(position,i,j,x,y))
		AddMove(i,j,x,y,nPly);
	x=i+1;
	y=j+1;//����ǰ����
	if(x>=0&&x<8&&y>=0&&y<8&&IsValidMove(position,i,j,x,y))
		AddMove(i,j,x,y,nPly);
}
//������ĺϷ��߷�
///i,j��ʾ����λ�� nPly��ʾ���뵽List�ڼ���
void CMoveGenerator::Gen_QueenMove(BYTE position[8][8], int i, int j, int nPly)
{
	int k,x,y;
	for(k=1;k<9;k++)
	{
		x=i+movex[k];
		y=j+movey[k];
		while(x>=0&&x<8&&y>=0&&y<8)
		{
			if(IsValidMove(position,i,j,x,y))
				AddMove(i,j,x,y,nPly);
			x+=movex[k];
			y+=movey[k];
		}
	}	
}
//�������ĺϷ��߷�
///i,j��ʾ����λ�� nPly��ʾ���뵽List�ڼ���
void CMoveGenerator::Gen_RookMove(BYTE position[8][8], int i, int j, int nPly)
{
	int k,x,y;
	for(k=1;k<9;k+=2)
	{
		x=i+movex[k];
		y=j+movey[k];
		while(x>=0&&x<8&&y>=0&&y<8)
		{
			if(IsValidMove(position,i,j,x,y))
				AddMove(i,j,x,y,nPly);
			x+=movex[k];
			y+=movey[k];
		}
	}	
}
