// NewGame.cpp : implementation file
//

#include "stdafx.h"
#include "chess.h"
#include "NewGame.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNewGame dialog


CNewGame::CNewGame(CWnd* pParent /*=NULL*/)
	: CDialog(CNewGame::IDD, pParent)
{
	//{{AFX_DATA_INIT(CNewGame)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CNewGame::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNewGame)
	DDX_Control(pDX, IDC_PLY, m_SetPly);
	DDX_Control(pDX, IDC_LISTENGINE, m_SearchEngineList);
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CNewGame, CDialog)
	//{{AFX_MSG_MAP(CNewGame)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNewGame message handlers

void CNewGame::OnOK() 
{
	// TODO: Add extra validation here
	//保存用户选择的搜索引擎号码
	m_nSelectedEngine = m_SearchEngineList.GetCurSel();
	//保存用户选择的搜索层数
	m_nSelectedPly = m_SetPly.GetPos();
	 
	CDialog::OnOK();
}

BOOL CNewGame::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	//在listbox中加入负极大值搜索引擎字样
	m_SearchEngineList.AddString("负极大值搜索引擎");
	m_SearchEngineList.AddString("Alpha Beta剪枝搜索引擎");
	m_SearchEngineList.AddString("极小窗口搜索引擎");
	m_SearchEngineList.AddString("结合置换表的Alpha－Beta剪枝搜索引擎");
	m_SearchEngineList.AddString("结合历史启发的Alpha-Beta搜索引擎");
	m_SearchEngineList.AddString("结合历史启发和置换表的Alpha-Beta搜索引擎");
	
	m_SearchEngineList.SetCurSel(0);///默认选择每一个搜索引擎
	m_SetPly.SetRange(1, 10);//设定搜索深度范围
	m_SetPly.SetPos(3);//默认的搜索层数为3
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
