// HistoryHeuristic.h: interface for the CHistoryHeuristic class.
//历史启发
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_HISTORYHEURISTIC_H__3F9AC577_D776_4E5C_91C2_AD8E05F3AD07__INCLUDED_)
#define AFX_HISTORYHEURISTIC_H__3F9AC577_D776_4E5C_91C2_AD8E05F3AD07__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CHistoryHeuristic  
{
public:
	CHistoryHeuristic();
	virtual ~CHistoryHeuristic();
	//将历史记录清空
	void ResetHistoryTable();
	//取某一走法的历史得分
	int GetHistoryScore(CHESSMOVE *move);
	//保存得分
	void EnterHistoryScore(CHESSMOVE *move,int depth);
	//对当前队列进行归并排序
	void MergeSort(CHESSMOVE *source, int n, BOOL direction);
protected:
	//从小到大排序，MergePass调用 
	void Merge(CHESSMOVE *source, CHESSMOVE *target, int l,int m, int r);
	//合并排序好的两相邻数据段，MergeSort调用 
	void MergePass(CHESSMOVE *source, CHESSMOVE *target, const  int s, const  int n, const BOOL direction);
	//从大到小排序，MergePass调用 
	void Merge_A(CHESSMOVE *source, CHESSMOVE *target, int l,int m, int r);
	int m_HistoryTable[90][90];//历史得分表
	CHESSMOVE m_TargetBuff[100]; //排序用的缓冲队列

};

#endif // !defined(AFX_HISTORYHEURISTIC_H__3F9AC577_D776_4E5C_91C2_AD8E05F3AD07__INCLUDED_)
