#pragma once

static const int MAX_BLOCK = 1024;

class CMemoryPool
{
private:
	int				m_CurrBlockCount;	// ���� ������ ����
	int				m_BlockAddr;		// ��� �ּ�	
	unsigned char*	m_StartPoint;	// ��� ���۹���


public:
	CMemoryPool();
	~CMemoryPool();


	void* Allocate(size_t alloc_size);
	void Delocate(void *DeleteBlock, size_t Blocksize);
};

