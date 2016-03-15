// TranspositionTable.h: interface for the CTranspositionTable class.
//�û���
//Ϊ�˲��ظ�����ͬ������֣����Ǽ�¼��������������ֺ��������
//Ϊ�˿��ٲ�����֣����ǲ��ù�ϣ������¼
//Ϊ��ʹϵ�о�����ɢ��������32 ��64λ���������ʶ
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TRANSPOSITIONTABLE_H__3E48F44A_ADA6_4240_BAEA_A5AAA1D98BDE__INCLUDED_)
#define AFX_TRANSPOSITIONTABLE_H__3E48F44A_ADA6_4240_BAEA_A5AAA1D98BDE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
//����ö�������ݣ���ȷ �±߽� �ϱ߽�
enum ENTRY_TYPE{ exact , lower_bound, upper_bound}; 
typedef struct HASHITEM{
    LONGLONG checksum;	// 64λУ����
	ENTRY_TYPE  entry_type;//��������
    short depth;//��ʱȡֵ�����
    short eval;//�ڵ��ֵ
}HashItem;

class CTranspositionTable  
{
public:
	CTranspositionTable();
	virtual ~CTranspositionTable();
//���������ֵĹ�ϣֵ 
	void CalculateInitHashKey(BYTE CurPosition[8][8]);
	//���������߷������������µĹ�ϣֵ
	void Hash_MakeMove(CHESSMOVE* move,BYTE CurPosition[8][8]);
	//���������߷��Ĺ�ϣֵ��ʹ֮�ص��߹�֮ǰ
	void Hash_UnMakeMove(CHESSMOVE* move,BYTE nChessID,BYTE CurPosition[8][8]);

	///��ѯ��ϣ���е�ǰ�ڵ��ֵ
	int LookUpHashTable(int alpha, int beta, int depth,int TableNo);
	//����ǰ�ڵ��ֵ�����ϣ��
	void EnterHashTable(ENTRY_TYPE entry_type, short eval, short depth,int TableNo);

	UINT m_nHashKey32[13][8][8];//32λ������飬��������32λ��ϣֵ
	ULONGLONG m_ulHashKey64[13][8][8];//32λ������飬��������32λ��ϣֵ
	HashItem *m_pTT[2];//�û���ͷָ��
	void InitializeHashKey();//��ʼ��������飬������ϣ��
	UINT m_HashKey32;//32λ��ϣֵ 
	LONGLONG m_HashKey64;//64λ��ϣֵ
};

#endif // !defined(AFX_TRANSPOSITIONTABLE_H__3E48F44A_ADA6_4240_BAEA_A5AAA1D98BDE__INCLUDED_)
