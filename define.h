//define.h // data structure and macros
#ifndef define_h_
#define define_h_

#define NOCHESS 0    //û������

#define B_KING       1  //����
#define B_ROOK       2  //�ڳ�
#define B_KNIGHT     3  //����
#define B_BISHOP     4  //����
#define B_QUEEN		 5  //�ں�
#define B_PAWN       6  //�ڱ�
#define B_BEGIN      B_KING
#define B_END        B_PAWN

#define R_KING       7   //����
#define R_ROOK       8   //�쳵
#define R_KNIGHT     9   //����
#define R_BISHOP     10  //����
#define R_QUEEN		 11  //���
#define R_PAWN	     12  //���
#define R_BEGIN      R_KING
#define R_END        R_PAWN

#define IsBlack(x)  (x>=B_BEGIN&&x<=B_END)
#define IsRed(x)  (x>=R_BEGIN&&x<=R_END)
//�Ƿ�ͬ������
#define IsSameSide(x,y)  ((IsBlack(x)&&IsBlack(y))||(IsRed(x)&&IsRed(y)))
//����һ������λ�ýṹ
typedef struct _chessmanposition
{
	BYTE		x;
	BYTE		y;
}CHESSMANPOS;
//�߷��ṹ
typedef struct _chessmove
{
	short	  	    ChessID;	//������ʲô����
	CHESSMANPOS	From;
	CHESSMANPOS	To;			//
	int			    Score;		// ��ֵ
}CHESSMOVE;

#endif //define_h_