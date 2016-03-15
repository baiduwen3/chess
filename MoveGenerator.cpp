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
//nPly 当前搜索层数
///nSide 指明哪一方走，TRUE为红方 FALSE为黑方
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
					continue;//若产生黑棋走法，跳过红棋
				if (nSide && IsBlack(nChessID))
					continue;//若产生红棋走法，跳过黑棋
				switch(nChessID)
				{
				case R_KING:
				case B_KING://王
					Gen_KingMove(position, i, j, nPly);
					break;
					
				case R_BISHOP://象
				case B_BISHOP:
					Gen_BishopMove(position, i, j, nPly);
					break;
					
				case R_KNIGHT:		
				case B_KNIGHT://马	
					Gen_KnightMove(position, i, j, nPly);
					break;
					
				case R_ROOK:
				case B_ROOK://车
					Gen_RookMove(position, i, j, nPly);
					break;
					
				case R_PAWN://红兵
					Gen_RPawnMove(position, i, j, nPly);
					break;
					
				case B_PAWN://黑兵
					Gen_BPawnMove(position, i, j, nPly);
					break;
					
				case B_QUEEN:
				case R_QUEEN://后
					Gen_QueenMove(position, i, j, nPly);
					break;
					
				default:
					break;
					
				}
			}
		}
		
		return m_nMoveCount;//返回走法总数
}
//判断给定棋局上，从From 到To是否合法
//若合法返回TRUE 否则FALSE
BOOL CMoveGenerator::IsValidMove(BYTE position[8][8], int nFromX, int nFromY, int nToX, int nToY)
{
	int i, j;
	int nMoveChessID, nTargetID;
	
	if (nFromY ==  nToY && nFromX == nToX)
		return FALSE;//目的与源相同
	
	nMoveChessID = position[nFromY][nFromX];
	nTargetID = position[nToY][nToX];
	
	if (IsSameSide(nMoveChessID, nTargetID))
		return FALSE;//不能吃自己的棋
	
	switch(nMoveChessID)
	{
	case R_KING: //王  
	case B_KING:
		if(abs(nFromY - nToY)>1) 
			return FALSE;//王只能走到其周边的格子上
		if(abs(nToX - nFromX)>1)
			return FALSE;//王不能在直线上走两格
		break;

	case R_BISHOP:  //象 
	case B_BISHOP:  
		if(abs(nFromY - nToY) != abs(nToX - nFromX)) 
			return FALSE;//象只能走斜线
		if(nToY>nFromY)//向下
		{
			if(nToX>nFromX)//向右下方走
			{
				for(i=nFromY+1,j=nFromX+1;i<nToY&&j<nToX;i++,j++)
					if(position[i][j] != NOCHESS)
						return FALSE;
			}
			else//向左下方走
			{
				for(i=nFromY+1,j=nFromX-1;i<nToY&&j>nToX;i++,j--)
					if(position[i][j] != NOCHESS)
						return FALSE;
			}
		}
		else //向上
		{
			if(nToX>nFromX)//向右上方走
			{
				for(i=nFromY-1,j=nFromX+1;i>nToY&&j<nToX;i--,j++)
					if(position[i][j] != NOCHESS)
						return FALSE;
			}
			else//向左上方走
			{
				for(i=nFromY-1,j=nFromX-1;i>nToY&&j>nToX;i--,j--)
					if(position[i][j] != NOCHESS)
						return FALSE;
			}
		}
		break;
		
		
	case B_PAWN: 	//黑兵
		if(nFromX!=nToX)
		{
			if(abs(nFromX-nToX)==1 && (nFromY-nToY==-1) && IsRed(nTargetID))
				return TRUE;//吃
			else
				return	FALSE;
		}
		else 
		{
			if(nFromY-nToY==-1&&nTargetID==NOCHESS)
				return TRUE;//走了一格
			else 
				if(nFromY==1 && (nFromY-nToY)==-2&&nTargetID==NOCHESS&&position[nFromY+1][nFromX]==NOCHESS)//第一步走了二格
					return TRUE;
				else
					return FALSE;
		}
		break;
		
	case R_PAWN:    //红兵
		if(nFromX!=nToX)
		{
			if(abs(nFromX-nToX)==1 && (nFromY-nToY==1) && IsBlack(nTargetID))
				return TRUE;//吃
			else
				return	FALSE;
		}
		else 
		{
			if(nFromY-nToY==1&&nTargetID==NOCHESS)
				return TRUE;//走了一格
			else 
				if(nFromY==6 && (nFromY-nToY)==2&&nTargetID==NOCHESS&&position[nFromY-1][nFromX]==NOCHESS)//第一步走了二格
					return TRUE;
				else
					return FALSE;
		}
		break;
		
	case B_ROOK:      
	case R_ROOK:  //车  
		
		if(nFromY != nToY && nFromX != nToX)
			return FALSE;	//车走直线:
		
		if(nFromY == nToY)//路线中间有棋子挡道
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
	case R_KNIGHT://马
		
		if(!((abs(nToX-nFromX)==1 && abs(nToY-nFromY)==2)
			||(abs(nToX-nFromX)==2&&abs(nToY-nFromY)==1)))
			return FALSE;//马走日字
		break;
	
	case B_QUEEN:    
	case R_QUEEN://后
		if(!(nFromY == nToY || nFromX == nToX ||
							(abs(nFromY - nToY) == abs(nToX - nFromX))))
			return FALSE;//非直走也非斜走
		/////////////////////////////////
		//路线中间有棋子挡道
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
			else//X!=x && Y!=Y 走斜线
			{
				if(nToY>nFromY)//向下
				{
					if(nToX>nFromX)//向右下方走
					{
						for(i=nFromY+1,j=nFromX+1;i<nToY&&j<nToX;i++,j++)
							if(position[i][j] != NOCHESS)
								return FALSE;
					}
					else//向左下方走
					{
						for(i=nFromY+1,j=nFromX-1;i<nToY&&j>nToX;i++,j--)
							if(position[i][j] != NOCHESS)
								return FALSE;
					}
				}
				else //向 上
				{
					if(nToX>nFromX)//向右上方走
					{
						for(i=nFromY-1,j=nFromX+1;i>nToY&&j<nToX;i--,j++)
							if(position[i][j] != NOCHESS)
								return FALSE;
					}
					else//向左上方走
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
//位移步调
const int movex[9]={0,1,1,0,-1,-1,-1,0,1};
const int movey[9]={0,0,-1,-1,-1,0,1,1,1};
//马的位移步调
const int moveknightx[9]={0,2,2,1,-1,-2,-2,-1,1};
const int moveknighty[9]={0,1,-1,-2,-2,-1,1,2,2};
///产生王的合法走法
///i,j表示棋子位置 nPly表示插入到List第几层
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
//产生象的合法走法
///i,j表示棋子位置 nPly表示插入到List第几层/
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
//产生马的合法走法
///i,j表示棋子位置 nPly表示插入到List第几层
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
//产生红兵的合法走法
///i,j表示棋子位置 nPly表示插入到List第几层
void CMoveGenerator::Gen_RPawnMove(BYTE position[8][8], int i, int j, int nPly)
{
	int x,y;
	x=i;
	y=j-1;//向前一步走
	if(x>=0&&x<8&&y>=0&&y<8&&IsValidMove(position,i,j,x,y))
		AddMove(i,j,x,y,nPly);
	y=j-2;//向前二步走
	if(x>=0&&x<8&&y>=0&&y<8&&IsValidMove(position,i,j,x,y))
		AddMove(i,j,x,y,nPly);
	x=i-1;
	y=j-1;//向左前吃子
	if(x>=0&&x<8&&y>=0&&y<8&&IsValidMove(position,i,j,x,y))
		AddMove(i,j,x,y,nPly);
	x=i+1;
	y=j-1;//向右前吃子
	if(x>=0&&x<8&&y>=0&&y<8&&IsValidMove(position,i,j,x,y))
		AddMove(i,j,x,y,nPly);
}
//产生黑兵的合法走法
///i,j表示棋子位置 nPly表示插入到List第几层
void CMoveGenerator::Gen_BPawnMove(BYTE position[8][8], int i, int j, int nPly)
{
	int x,y;
	x=i;
	y=j+1;//向前一步走
	if(x>=0&&x<8&&y>=0&&y<8&&IsValidMove(position,i,j,x,y))
		AddMove(i,j,x,y,nPly);
	y=j+2;//向前二步走
	if(x>=0&&x<8&&y>=0&&y<8&&IsValidMove(position,i,j,x,y))
		AddMove(i,j,x,y,nPly);
	x=i-1;
	y=j+1;//向左前吃子
	if(x>=0&&x<8&&y>=0&&y<8&&IsValidMove(position,i,j,x,y))
		AddMove(i,j,x,y,nPly);
	x=i+1;
	y=j+1;//向右前吃子
	if(x>=0&&x<8&&y>=0&&y<8&&IsValidMove(position,i,j,x,y))
		AddMove(i,j,x,y,nPly);
}
//产生后的合法走法
///i,j表示棋子位置 nPly表示插入到List第几层
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
//产生车的合法走法
///i,j表示棋子位置 nPly表示插入到List第几层
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
