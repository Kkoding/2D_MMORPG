#pragma once
class CIocp
{
private:
	HANDLE m_iocp;

public:

	BOOL GQCS(LPDWORD, PULONG_PTR, LPOVERLAPPED*);

	BOOL PQCS(ULONG, WSAOVERLAPPED*);

	BOOL CreateIOCP();
	BOOL CreateIOCP(SOCKET, int ,int* error_txt = NULL);

public:
	CIocp();
	~CIocp();
};

