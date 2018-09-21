#pragma once

static const int MAX_BLOCK = 4096;



class CMemoryPool
{
private:
	int				m_CurrBlockCount;	// ���� ������ ����
	int				m_BlockAddr;		// ��� �ּ�	
	unsigned char*	m_StartPoint;		// ��� ���۹���
	mutex			m_lock;

public:
	CMemoryPool();
	~CMemoryPool();

	void Curr();
	void* Allocate(size_t alloc_size);
	void Delocate(void *DeleteBlock, ULONGLONG Blocksize);
};

