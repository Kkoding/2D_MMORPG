#include "stdafx.h"
#include "CIocp.h"


BOOL CIocp::GQCS(LPDWORD pdwNumberOfbyte, PULONG_PTR pulCompetionkey, LPOVERLAPPED* pOverlapped)
{
	BOOL ret = GetQueuedCompletionStatus(m_iocp, pdwNumberOfbyte, pulCompetionkey, pOverlapped, INFINITE);
	if (FALSE == ret ) {
		return FALSE;
	}
	return S_OK;
}

BOOL CIocp::PQCS(ULONG pKey, WSAOVERLAPPED* Overlapped)
{
	BOOL ret = PostQueuedCompletionStatus(m_iocp, 1, pKey, Overlapped);
	return 0;
}

BOOL CIocp::CreateIOCP()
{
	m_iocp = CreateIoCompletionPort(INVALID_HANDLE_VALUE, 0, NULL, 0);
	return (m_iocp != NULL);
}

BOOL CIocp::CreateIOCP(SOCKET socket, int id, int* error_txt)
{
	HANDLE handle = CreateIoCompletionPort(reinterpret_cast<HANDLE>(socket)
		, m_iocp, id, 0);
	if (handle != m_iocp && NULL != error_txt)
		*error_txt = GetLastError();
	return (handle == m_iocp);
}

CIocp::CIocp()
{
}


CIocp::~CIocp()
{
	CloseHandle(m_iocp);
}
