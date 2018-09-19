#include "stdafx.h"

#define NAME_LEN 50
#define PHONE_LEN 20
#define POS_LEN 400


std::chrono::high_resolution_clock::time_point g_time;

extern int g_map[MAP_SIZE][MAP_SIZE];
extern CMemoryPool* g_MemoryPool = nullptr;

CMemoryPool *CLIENT::m_MemPool = 0;


int main()
{
	vector<thread*> vWork_thread;
	CThread* th = new CThread();
	g_MemoryPool = new CMemoryPool;

	for (auto& cl : g_clients) 
		cl = new CLIENT();
	

	th->Initialize_Server();

	for (int i = 0; i < 6; ++i) {
		vWork_thread.push_back(new thread{ [&]() { th->Worker_Thread(); } });
	}

	thread accept_thread{ [&]() {th->Accept_Thread(); } };
	//thread ai_thread{ [&]() {th->NPC_AI_Thread(); } };
	thread timer_thread{ [&]() {th->Timer_Thread(); } };

	accept_thread.join();
	//ai_thread.join();
	timer_thread.join();

	for (auto& th : vWork_thread) {
		th->join();
		delete th;
	}

	vWork_thread.clear();
	th->Shutdown_Server();

	delete g_MemoryPool;
	



}