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
#define BORDERWIDTH 2 //����(����)��Ե�Ŀ��
#define BORDERHEIGHT 0 //����(����)��Ե�ĸ߶�
#define GRILLEWIDTH 45  //������ÿ�����ӵĸ߶�
#define GRILLEHEIGHT 45 //������ÿ�����ӵĿ��
//��������鱣�����̳�ʼ״̬
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
	///��ͼ���б�
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
	///��ͼ���б�
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
	///��ͼ���б�
	//����ȡ���̵Ŀ���
	BITMAP BitMap;
	m_BoardBmp.LoadBitmap(IDB_CHESSBOARD);
	m_BoardBmp.GetBitmap(&BitMap);
	m_nBoardWidth =  BitMap.bmWidth; //���̿��
	m_nBoardHeight = BitMap.bmHeight;//���̸߶�
	m_BoardBmp.DeleteObject();


	memcpy(m_ChessBoard, InitChessBoard, 64);//��ʼ������
	
	CMoveGenerator *pMG;
	CEveluation *pEvel;

//Ĭ�����ã�������ֵ�������棬��������3��
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
		//X�����ƶ�����m_MoveChess.nChessID - 1Ϊ����ͼ��ID
		if (m_MoveChess.nChessID != NOCHESS)
			m_Chessman.Draw(&MemDC, m_MoveChess.nChessID - 1, m_MoveChess.ptMovePoint, ILD_TRANSPARENT);		
		//�����������Ļ
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
	memcpy(m_BackupChessBoard, m_ChessBoard, 64);//��������
	if (point.x > 0 && point.y > 0 &&point.x< m_nBoardWidth && point.y< m_nBoardHeight && 
		IsRed(m_ChessBoard[y][x]))
	{
		memcpy(m_BackupChessBoard, m_ChessBoard, 64);
		m_ptMoveChess.x = x;
		m_ptMoveChess.y = y;

		m_MoveChess.nChessID = m_ChessBoard[m_ptMoveChess.y][m_ptMoveChess.x];
		//������ԭλ�����
		m_ChessBoard[m_ptMoveChess.y][m_ptMoveChess.x] = NOCHESS;
	//�������е�����Ϊ������ڵ�
		point.x -= 18;
		point.y -= 22;
		m_MoveChess.ptMovePoint = point;
		InvalidateRect(NULL,FALSE);
		UpdateWindow();
		SetCapture();//��ռ���
	}
	CDialog::OnLButtonDown(nFlags, point);
}
//ȫ�ֱ�����ͳ�Ƶ��ù�ֵ�����Ĵ���
//��Eveluation �ж����
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
	//�ж��Ƿ����ƶ����ӣ�����Ϊ�Ϸ��ƶ�
	if (m_MoveChess.nChessID &&
		CMoveGenerator::IsValidMove(m_BackupChessBoard, m_ptMoveChess.x, m_ptMoveChess.y,
		x,y))
	{
		m_ChessBoard[y][x] = m_MoveChess.nChessID;
		bTurnSide = TRUE;
	}
	else//û�������ƶ����ָ�����
		memcpy(m_ChessBoard, m_BackupChessBoard, 64);
	
	m_MoveChess.nChessID = NOCHESS;//���
	InvalidateRect(NULL,FALSE);
	UpdateWindow();
	
	ReleaseCapture();//�ͷ���꽹��
	if (bTurnSide == TRUE)
	{
		timecount = GetTickCount();//��ʼʱ��
		m_pSE->SearchAGoodMove(m_ChessBoard);//�õ�������һ��	
		
		CString sNodeCount;
//�����Ի��ѵ�ʱ�䣬�����Ľڵ�����ʽ��Ϊһ���ַ���
		sNodeCount.Format(" ��ʱ %d ms. ������%d ���ڵ�.", GetTickCount() - timecount,count);
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
		//��ֹ�������ϳ�����
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
		m_MoveChess.ptMovePoint = point;//�����ƶ����ӵ�����
		InvalidateRect(NULL,FALSE);//ˢ�´���
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
	{//�û�����ѡ��
		if (m_pSE)
			delete m_pSE;//bug
		//ѡ����������
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
		//��������������
		m_pSE->SetSearchDepth(newGameDlg.GetSelectedPly());
		pEvel = new CEveluation;
	}
	else //ά��ԭ״�������¿�ʼ
		return;

	memcpy(m_ChessBoard, InitChessBoard, 64);//��ʼ������
	m_MoveChess.nChessID = NOCHESS;

	pMG = new CMoveGenerator;//�����߷�������
	m_pSE->SetMoveGenerator(pMG);//���߷�������ΰ����������
	m_pSE->SetEveluator(pEvel);//����ֵ���Ĵ�����������
	
	m_bGameOver = FALSE;

	InvalidateRect(NULL,FALSE);
	UpdateWindow();
}
