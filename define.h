//define.h // data structure and macros
#ifndef define_h_
#define define_h_

#define NOCHESS 0    //没有棋子

#define B_KING       1  //黑王
#define B_ROOK       2  //黑车
#define B_KNIGHT     3  //黑马
#define B_BISHOP     4  //黑象
#define B_QUEEN		 5  //黑后
#define B_PAWN       6  //黑兵
#define B_BEGIN      B_KING
#define B_END        B_PAWN

#define R_KING       7   //红王
#define R_ROOK       8   //红车
#define R_KNIGHT     9   //红马
#define R_BISHOP     10  //红象
#define R_QUEEN		 11  //红后
#define R_PAWN	     12  //红兵
#define R_BEGIN      R_KING
#define R_END        R_PAWN

#define IsBlack(x)  (x>=B_BEGIN&&x<=B_END)
#define IsRed(x)  (x>=R_BEGIN&&x<=R_END)
//是否同方棋子
#define IsSameSide(x,y)  ((IsBlack(x)&&IsBlack(y))||(IsRed(x)&&IsRed(y)))
//定义一个棋子位置结构
typedef struct _chessmanposition
{
	BYTE		x;
	BYTE		y;
}CHESSMANPOS;
//走法结构
typedef struct _chessmove
{
	short	  	    ChessID;	//标明是什么棋子
	CHESSMANPOS	From;
	CHESSMANPOS	To;			//
	int			    Score;		// 分值
}CHESSMOVE;

#endif //define_h_