// chessDlg.h : header file
//

#if !defined(AFX_CHESSDLG_H__A1BB310F_E11B_40D5_B0FC_AB014CD4202E__INCLUDED_)
#define AFX_CHESSDLG_H__A1BB310F_E11B_40D5_B0FC_AB014CD4202E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "define.h"
#include "SearchEngine.h"
#include "NegamaxEngine.h"
#include "AlphaBetaEngine.h"
#include "AlphaBetaAndTT.h"
//#include "FAlphaBetaEngine.h"
#include "PVS_Engine.h"
//#include "NegaScout.h"
//#include "IDAlphabeta.h"
//#include "AspirationSearch.h"
#include "Alphabeta_HH.h"
//#include "mtd_f.h"
#include "NegaScout_TT_HH.h"

typedef struct _movechess
{
	BYTE nChessID;
	POINT ptMovePoint;
}MOVECHESS;
/////////////////////////////////////////////////////////////////////////////
// CChessDlg dialog

class CChessDlg : public CDialog
{
// Construction
public:
	CChessDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CChessDlg)
	enum { IDD = IDD_CHESS_DIALOG };
	CStatic	m_OutputInfo;
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChessDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CChessDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnNewgame();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	BOOL m_bGameOver;
	//显示棋盘 备份棋盘数组
	BYTE m_ChessBoard[8][8];
	BYTE m_BackupChessBoard[8][8];
	MOVECHESS m_MoveChess;//保存当前被拖动棋子的结构
	POINT m_ptMoveChess;//保存当前被拖动棋子的位置
	CBitmap m_BoardBmp;//用于显示棋盘
	CImageList m_Chessman;//用于绘棋子
	//棋盘大小
	int m_nBoardWidth; 
	int m_nBoardHeight;
	//搜索引擎指针
	CSearchEngine *m_pSE;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHESSDLG_H__A1BB310F_E11B_40D5_B0FC_AB014CD4202E__INCLUDED_)
