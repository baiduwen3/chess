// chessDlg.cpp : implementation file
//

#include "stdafx.h"
#include "chess.h"
#include "chessDlg.h"
#include "NewGame.h"
#include "MoveGenerator.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About
#define BORDERWIDTH 2 //棋盘(左右)边缘的宽度
#define BORDERHEIGHT 0 //棋盘(上下)边缘的高度
#define GRILLEWIDTH 45  //棋盘上每个格子的高度
#define GRILLEHEIGHT 45 //棋盘上每个格子的宽度
//下面的数组保存棋盘初始状态
const BYTE InitChessBoard[8][8]=
{
//X  0			1			2		3			4			5		6			7	 
	{B_ROOK,  B_KNIGHT, B_BISHOP,  B_QUEEN,  B_KING,  B_BISHOP,  B_KNIGHT,  B_ROOK},
	{B_PAWN,  B_PAWN,   B_PAWN,    B_PAWN,   B_PAWN,  B_PAWN,    B_PAWN,    B_PAWN},
	{NOCHESS, NOCHESS,  NOCHESS,   NOCHESS,  NOCHESS, NOCHESS,   NOCHESS,   NOCHESS},
	{NOCHESS, NOCHESS,  NOCHESS,   NOCHESS,  NOCHESS, NOCHESS,   NOCHESS,   NOCHESS},

	{NOCHESS, NOCHESS,  NOCHESS,   NOCHESS,  NOCHESS, NOCHESS,   NOCHESS,   NOCHESS},
	{NOCHESS, NOCHESS,  NOCHESS,   NOCHESS,  NOCHESS, NOCHESS,   NOCHESS,   NOCHESS},
	{R_PAWN,  R_PAWN,   R_PAWN,    R_PAWN,   R_PAWN,  R_PAWN,    R_PAWN,    R_PAWN},
	{R_ROOK,  R_KNIGHT, R_BISHOP,  R_QUEEN,  R_KING,  R_BISHOP,  R_KNIGHT,  R_ROOK},
//Y
//0
//1
//2
//3
///......
//7
};
////////////////////////
int IsGameOver(BYTE position[8][8])
{
	int i,j;
	BOOL RedLive = FALSE, BlackLive=FALSE; 
	
	for (i = 0; i < 8; i++)
		for (j = 0; j < 8; j++)
		{
			if (position[i][j] == B_KING)
				BlackLive = TRUE;
			if (position[i][j] == R_KING)
				RedLive  = TRUE;
		}
	if (RedLive && BlackLive)
		return FALSE;
	else
		return TRUE;
}
///////////////////////////
//////////////
class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	//enum { IDD = IDD_ABOUTBOX };
	enum { IDD = IDD_CHESS_DIALOG };
	CStatic	m_OutputInfo;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChessDlg dialog

CChessDlg::CChessDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CChessDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CChessDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CChessDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CChessDlg)
	DDX_Control(pDX, IDC_NODECOUNT, m_OutputInfo);
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CChessDlg, CDialog)
	//{{AFX_MSG_MAP(CChessDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_BN_CLICKED(IDC_NEWGAME, OnNewgame)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChessDlg message handlers

BOOL CChessDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	///棋图象列表
	m_Chessman.Create(IDB_BKING, 48, 12, RGB(255,0,255)); 
	CBitmap bm;
	bm.LoadBitmap(IDB_BROOK);
	m_Chessman.Add(&bm,RGB(255,0,255));
	bm.DeleteObject();
	bm.LoadBitmap(IDB_BKNIGHT);
	m_Chessman.Add(&bm,RGB(255,0,255));
	bm.DeleteObject();
	bm.LoadBitmap(IDB_BBISHOP);
	m_Chessman.Add(&bm,RGB(255,0,255));
	bm.DeleteObject();
	bm.LoadBitmap(IDB_BQUEEN);
	m_Chessman.Add(&bm,RGB(255,0,255));
	bm.DeleteObject();
	bm.LoadBitmap(IDB_BPAWN);
	m_Chessman.Add(&bm,RGB(255,0,255));
	bm.DeleteObject();
	///棋图象列表
	bm.LoadBitmap(IDB_WKING);
	m_Chessman.Add(&bm,RGB(255,0,255));
	bm.DeleteObject();
	bm.LoadBitmap(IDB_WROOK);
	m_Chessman.Add(&bm,RGB(255,0,255));
	bm.DeleteObject();
	bm.LoadBitmap(IDB_WKNIGHT);
	m_Chessman.Add(&bm,RGB(255,0,255));
	bm.DeleteObject();
	bm.LoadBitmap(IDB_WBISHOP);
	m_Chessman.Add(&bm,RGB(255,0,255));
	bm.DeleteObject();
	bm.LoadBitmap(IDB_WQUEEN);
	m_Chessman.Add(&bm,RGB(255,0,255));
	bm.DeleteObject();
	bm.LoadBitmap(IDB_WPAWN);
	m_Chessman.Add(&bm,RGB(255,0,255));
	bm.DeleteObject();
	///棋图象列表
	//下面取棋盘的宽，高
	BITMAP BitMap;
	m_BoardBmp.LoadBitmap(IDB_CHESSBOARD);
	m_BoardBmp.GetBitmap(&BitMap);
	m_nBoardWidth =  BitMap.bmWidth; //棋盘宽度
	m_nBoardHeight = BitMap.bmHeight;//棋盘高度
	m_BoardBmp.DeleteObject();


	memcpy(m_ChessBoard, InitChessBoard, 64);//初始化棋盘
	
	CMoveGenerator *pMG;
	CEveluation *pEvel;

//默认设置：负极大值搜索引擎，向下搜索3层
	m_pSE = new CNegamaxEngine;
/*	m_pSE = new CAlphaBetaEngine;
	m_pSE = new CPVS_Engine;
	m_pSE =new CAlphaBetaAndTT;
	m_pSE =new CAlphaBeta_HH;
	m_pSE =new CNegaScout_TT_HH;*/
	pMG = new CMoveGenerator;
	pEvel = new CEveluation;
	
	m_pSE->SetSearchDepth(3);
	m_pSE->SetMoveGenerator(pMG);
	m_pSE->SetEveluator(pEvel);
	m_MoveChess.nChessID = NOCHESS;
	m_bGameOver = FALSE;
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CChessDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CChessDlg::OnPaint() 
{
	CPaintDC dc(this);
	CDC MemDC;
	int i, j;
	POINT pt;
	CBitmap *pOldBmp;
	
	MemDC.CreateCompatibleDC( &dc );
	m_BoardBmp.LoadBitmap(IDB_CHESSBOARD);
	pOldBmp = MemDC.SelectObject(&m_BoardBmp);
	for (i = 0; i < 8; i++)
		for (j = 0; j < 8; j++)
		{
			if (m_ChessBoard[i][j] == NOCHESS)
				continue;
			pt.x = j*GRILLEHEIGHT+BORDERWIDTH+1;
			pt.y = i*GRILLEWIDTH+BORDERHEIGHT+1;
			m_Chessman.Draw(&MemDC, m_ChessBoard[i][j]-1, pt, ILD_TRANSPARENT);
		}
		//X绘制移动棋子m_MoveChess.nChessID - 1为棋子图象ID
		if (m_MoveChess.nChessID != NOCHESS)
			m_Chessman.Draw(&MemDC, m_MoveChess.nChessID - 1, m_MoveChess.ptMovePoint, ILD_TRANSPARENT);		
		//棋盘输出到屏幕
		dc.BitBlt(0, 0, m_nBoardWidth, m_nBoardHeight, &MemDC, 0, 0, SRCCOPY);
		MemDC.SelectObject(&pOldBmp);
		MemDC.DeleteDC();
		m_BoardBmp.DeleteObject();
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CChessDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CChessDlg::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if (m_bGameOver)
		return;
	int x,y;
	x=(point.x-BORDERWIDTH-1)/GRILLEWIDTH;
	y=(point.y-BORDERHEIGHT-1)/GRILLEHEIGHT;
	memcpy(m_BackupChessBoard, m_ChessBoard, 64);//备份棋盘
	if (point.x > 0 && point.y > 0 &&point.x< m_nBoardWidth && point.y< m_nBoardHeight && 
		IsRed(m_ChessBoard[y][x]))
	{
		memcpy(m_BackupChessBoard, m_ChessBoard, 64);
		m_ptMoveChess.x = x;
		m_ptMoveChess.y = y;

		m_MoveChess.nChessID = m_ChessBoard[m_ptMoveChess.y][m_ptMoveChess.x];
		//将棋子原位置清空
		m_ChessBoard[m_ptMoveChess.y][m_ptMoveChess.x] = NOCHESS;
	//让棋子中点坐标为鼠标所在点
		point.x -= 18;
		point.y -= 22;
		m_MoveChess.ptMovePoint = point;
		InvalidateRect(NULL,FALSE);
		UpdateWindow();
		SetCapture();//独占鼠标
	}
	CDialog::OnLButtonDown(nFlags, point);
}
//全局变量，统计调用估值函数的次数
//在Eveluation 中定义的
extern int count;
void CChessDlg::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	BOOL bTurnSide = FALSE; 

	if (m_bGameOver)
		return;

	int x,y;
	x=(point.x-BORDERWIDTH-1)/GRILLEWIDTH;
	y=(point.y-BORDERHEIGHT-1)/GRILLEHEIGHT;
	int timecount;
	//判断是否有移动棋子，并且为合法移动
	if (m_MoveChess.nChessID &&
		CMoveGenerator::IsValidMove(m_BackupChessBoard, m_ptMoveChess.x, m_ptMoveChess.y,
		x,y))
	{
		m_ChessBoard[y][x] = m_MoveChess.nChessID;
		bTurnSide = TRUE;
	}
	else//没有棋子移动，恢复棋盘
		memcpy(m_ChessBoard, m_BackupChessBoard, 64);
	
	m_MoveChess.nChessID = NOCHESS;//清空
	InvalidateRect(NULL,FALSE);
	UpdateWindow();
	
	ReleaseCapture();//释放鼠标焦点
	if (bTurnSide == TRUE)
	{
		timecount = GetTickCount();//起始时间
		m_pSE->SearchAGoodMove(m_ChessBoard);//让电脑走下一步	
		
		CString sNodeCount;
//将电脑花费的时间，评估的节点数格式化为一个字符串
		sNodeCount.Format(" 花时 %d ms. 搜索了%d 个节点.", GetTickCount() - timecount,count);
		m_OutputInfo.SetWindowText(sNodeCount);
	}
	
	if (IsGameOver(m_ChessBoard))
	{
		m_bGameOver = TRUE;
		MessageBox("Game Over! Press New Game to replay...");
	}
	
	count = 0;
	InvalidateRect(NULL, FALSE);
	UpdateWindow();
	CDialog::OnLButtonUp(nFlags, point);
}

void CChessDlg::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if (m_MoveChess.nChessID)
	{
		//防止将棋子拖出棋盘
		if( point.x < BORDERWIDTH)
			point.x = BORDERWIDTH;
		if( point.y < BORDERHEIGHT)
			point.y = BORDERHEIGHT;
		if( point.x > m_nBoardWidth - BORDERWIDTH)
			point.x = m_nBoardWidth - BORDERWIDTH;
		if( point.y > m_nBoardHeight - BORDERHEIGHT)
			point.y = m_nBoardHeight - BORDERHEIGHT;

		point.x -= 18;
		point.y -= 22;
		m_MoveChess.ptMovePoint = point;//保存移动棋子的坐标
		InvalidateRect(NULL,FALSE);//刷新窗口
		UpdateWindow();
	}
	CDialog::OnMouseMove(nFlags, point);
}

void CChessDlg::OnNewgame() 
{
	// TODO: Add your control notification handler code here
	CMoveGenerator * pMG;
	CEveluation *pEvel;

	CNewGame newGameDlg;
	if ( newGameDlg.DoModal() == IDOK)
	{//用户作了选择
		if (m_pSE)
			delete m_pSE;//bug
		//选择搜索引擎
		switch(newGameDlg.GetSelectedEngine())
		{
		case 0:
			m_pSE = new CNegamaxEngine;
			break;

		case 1:
			m_pSE = new CAlphaBetaEngine;
			break;

		case 2:
			m_pSE = new CPVS_Engine;
			break;

		case 3:
			m_pSE = new CAlphaBetaAndTT;
			break;

		case 4:
			m_pSE = new CAlphaBeta_HH;
			break;

		case 5:
			m_pSE = new CNegaScout_TT_HH;
			break;
		default:
			m_pSE = new CNegamaxEngine;
			break;
		}
		//设置搜索最大层数
		m_pSE->SetSearchDepth(newGameDlg.GetSelectedPly());
		pEvel = new CEveluation;
	}
	else //维持原状，不重新开始
		return;

	memcpy(m_ChessBoard, InitChessBoard, 64);//初始化棋盘
	m_MoveChess.nChessID = NOCHESS;

	pMG = new CMoveGenerator;//创建走法产生器
	m_pSE->SetMoveGenerator(pMG);//将走法产生器伟给搜索引擎
	m_pSE->SetEveluator(pEvel);//将估值核心传给搜索引擎
	
	m_bGameOver = FALSE;

	InvalidateRect(NULL,FALSE);
	UpdateWindow();
}
