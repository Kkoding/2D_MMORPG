#include "stdafx.h"
#include "CMemoryPool.h"



CMemoryPool::CMemoryPool()
{
	m_BlockAddr = 0;
	m_CurrBlockCount = 0;
	m_StartPoint = 0;
}


CMemoryPool::~CMemoryPool()
{
	delete m_StartPoint;
}

void CMemoryPool::Curr()
{

	int n =  m_CurrBlockCount; 
	cout << n << endl;

}

void* CMemoryPool::Allocate(size_t obj_size)
{
	if (!m_StartPoint) {

		m_StartPoint = new UCHAR[sizeof(CLIENT)*MAX_BLOCK];

		m_CurrBlockCount = MAX_BLOCK;

		UCHAR* addr = m_StartPoint;

		for (int i = 0; i < MAX_BLOCK - 1; ++i) {
			*addr = i;
			addr += sizeof(CLIENT);
		}
	}
	if (0 == m_CurrBlockCount) return 0;

	UCHAR* newblock = m_StartPoint + (obj_size * m_BlockAddr);
	m_BlockAddr = *newblock;

	m_CurrBlockCount--;
	return (void*)newblock;
}

void CMemoryPool::Delocate(void * DeleteBlock, ULONGLONG Blocksize)
{
	//오류체크
	if (m_CurrBlockCount >= MAX_BLOCK) return;

	*(reinterpret_cast<int *>(DeleteBlock)) = m_BlockAddr;
	
	
	unsigned blocknum = (reinterpret_cast<unsigned char *>(DeleteBlock) - m_StartPoint) / reinterpret_cast<int>(&Blocksize);
	int distanceFromStart = reinterpret_cast<UCHAR>(&blocknum);

	m_BlockAddr = distanceFromStart;
	++m_CurrBlockCount;

}