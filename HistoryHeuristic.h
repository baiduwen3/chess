// HistoryHeuristic.h: interface for the CHistoryHeuristic class.
//��ʷ����
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
	//����ʷ��¼���
	void ResetHistoryTable();
	//ȡĳһ�߷�����ʷ�÷�
	int GetHistoryScore(CHESSMOVE *move);
	//����÷�
	void EnterHistoryScore(CHESSMOVE *move,int depth);
	//�Ե�ǰ���н��й鲢����
	void MergeSort(CHESSMOVE *source, int n, BOOL direction);
protected:
	//��С��������MergePass���� 
	void Merge(CHESSMOVE *source, CHESSMOVE *target, int l,int m, int r);
	//�ϲ�����õ����������ݶΣ�MergeSort���� 
	void MergePass(CHESSMOVE *source, CHESSMOVE *target, const  int s, const  int n, const BOOL direction);
	//�Ӵ�С����MergePass���� 
	void Merge_A(CHESSMOVE *source, CHESSMOVE *target, int l,int m, int r);
	int m_HistoryTable[90][90];//��ʷ�÷ֱ�
	CHESSMOVE m_TargetBuff[100]; //�����õĻ������

};

#endif // !defined(AFX_HISTORYHEURISTIC_H__3F9AC577_D776_4E5C_91C2_AD8E05F3AD07__INCLUDED_)
