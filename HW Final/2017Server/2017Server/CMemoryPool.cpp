#include "stdafx.h"
#include "CMemoryPool.h"



CMemoryPool::CMemoryPool()
{
	m_CurrBlockCount = 0;
	m_BlockAddr = 0;
}


CMemoryPool::~CMemoryPool()
{
	delete m_StartPoint;
}

void* CMemoryPool::Allocate(size_t alloc_size)
{
	// �ƹ��͵� �ȉ���ִ�.
	if (!m_StartPoint) {

		m_StartPoint = static_cast<unsigned char*>(malloc(alloc_size* MAX_BLOCK));

		m_CurrBlockCount = MAX_BLOCK;

		UCHAR* addr = m_StartPoint;

		// �Ҵ�����
		for (int i = 0; i < MAX_BLOCK; ++i) {
			*addr = i + 1;
			addr += alloc_size;
		}
	}

	// ��á��?
	if (0 == m_CurrBlockCount) return 0;



	UCHAR* newblock = m_StartPoint + (alloc_size * m_BlockAddr);
	m_BlockAddr = *newblock;

	m_CurrBlockCount--;

	return (void*)newblock;
}

void CMemoryPool::Delocate(void * DeleteBlock, size_t Blocksize)
{
	//����üũ
	if (m_CurrBlockCount >= MAX_BLOCK) return;


	*(static_cast<int *>(DeleteBlock)) = m_BlockAddr;


	int distanceFromStart =
		static_cast<int>((static_cast<unsigned char *>
		(DeleteBlock)-m_StartPoint) / static_cast<int>(Blocksize));

	m_BlockAddr = distanceFromStart;
	++m_CurrBlockCount;


}