// TranspositionTable.h: interface for the CTranspositionTable class.
//置换表
//为了不重复搜索同样的棋局，我们记录下所搜索过的棋局和搜索结果
//为了快速查找棋局，我们采用哈希表来记录
//为了使系列尽量分散，我们用32 和64位随机数来标识
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TRANSPOSITIONTABLE_H__3E48F44A_ADA6_4240_BAEA_A5AAA1D98BDE__INCLUDED_)
#define AFX_TRANSPOSITIONTABLE_H__3E48F44A_ADA6_4240_BAEA_A5AAA1D98BDE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
//定义枚举型数据，精确 下边界 上边界
enum ENTRY_TYPE{ exact , lower_bound, upper_bound}; 
typedef struct HASHITEM{
    LONGLONG checksum;	// 64位校验码
	ENTRY_TYPE  entry_type;//数据类型
    short depth;//此时取值的深度
    short eval;//节点的值
}HashItem;

class CTranspositionTable  
{
public:
	CTranspositionTable();
	virtual ~CTranspositionTable();
//计算给定棋局的哈希值 
	void CalculateInitHashKey(BYTE CurPosition[8][8]);
	//根据所给走法，增量生成新的哈希值
	void Hash_MakeMove(CHESSMOVE* move,BYTE CurPosition[8][8]);
	//撤消所给走法的哈希值，使之回到走过之前
	void Hash_UnMakeMove(CHESSMOVE* move,BYTE nChessID,BYTE CurPosition[8][8]);

	///查询哈希表中当前节点的值
	int LookUpHashTable(int alpha, int beta, int depth,int TableNo);
	//将当前节点的值存入哈希表
	void EnterHashTable(ENTRY_TYPE entry_type, short eval, short depth,int TableNo);

	UINT m_nHashKey32[13][8][8];//32位随机数组，用于生成32位哈希值
	ULONGLONG m_ulHashKey64[13][8][8];//32位随机数组，用于生成32位哈希值
	HashItem *m_pTT[2];//置换表头指针
	void InitializeHashKey();//初始化随机数组，创建哈希表
	UINT m_HashKey32;//32位哈希值 
	LONGLONG m_HashKey64;//64位哈希值
};

#endif // !defined(AFX_TRANSPOSITIONTABLE_H__3E48F44A_ADA6_4240_BAEA_A5AAA1D98BDE__INCLUDED_)
