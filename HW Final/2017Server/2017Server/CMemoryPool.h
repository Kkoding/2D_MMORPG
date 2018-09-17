#pragma once

static const int MAX_BLOCK = 1024;

class CMemoryPool
{
private:
	int				m_CurrBlockCount;	// 현재 가능한 갯수
	int				m_BlockAddr;		// 블록 주소	
	unsigned char*	m_StartPoint;	// 블록 시작번지


public:
	CMemoryPool();
	~CMemoryPool();


	void* Allocate(size_t alloc_size);
	void Delocate(void *DeleteBlock, size_t Blocksize);
};

