#pragma once

class comparison {
	bool reverse;
public:
	comparison() {}
	bool operator() (const Timer_Event first, const Timer_Event second) const {
		return first.exec_time > second.exec_time;
	}
};
class CMemoryPool;



class CThread
{
private:
	
	int g_map[MAP_SIZE][MAP_SIZE];
	CIocp m_iocp;
	SOCKET m_listenSocket;

	priority_queue <Timer_Event, vector<Timer_Event>, comparison> timer_queue;
	mutex tq_lock;


	////DB
	SQLHDBC m_hdbc;
	SQLHENV m_henv;
	SQLRETURN m_retcode;
	SQLWCHAR ID[NAME_LEN];
	int xPos, yPos, iExp, iExps, iAtt, ihp, iLv;
	SQLLEN LID = 0, LxPos = 0, LyPos = 0, L_lv, L_hp, L_exp, L_exps, L_att;
	SQLHSTMT m_hstmt = 0;
	SQLWCHAR dbID[NAME_LEN];
	int db_x_pos, db_y_pos, db_lv, db_exp, db_exps, db_attack, db_hp;
	SQLLEN S_ID = 0, S_xPos = 0, S_yPos = 0, S_lv, S_hp, S_exps, S_att, S_exp;
	wchar_t m_sqldata[255];
	char m_savebuf[255];

public:

	void Initialize_Server();
	void Initialize_NPC();
	void Accept_Thread();
	void Worker_Thread();
	void NPC_AI_Thread();
	void Timer_Thread();


	void InitializeDB();
	void DB_thread();
	void SavePositionToDB(int ci);

	//////	NPC
	void NPC_Attack(int);
	void WakeUpNPC(int id)
	{
		if (true == g_clients[id]->is_active) return;
		g_clients[id]->is_active = true;
		Timer_Event event = { id, high_resolution_clock::now() + 1s ,E_MOVE };
		tq_lock.lock();
		timer_queue.push(event);
		tq_lock.unlock();
	}
	void NPC_HP(int ci, int obj, unsigned char packet[]);
	void NPC_Respawn(int npc);
	void NPC_Random_Move(int id);



	///// PACKET
public:
	void SendPacket(int cl, void *packet);
	void SendDisconnectedPacket(int client, int object);
	void SendPutPlayerPacket(int client, int object);
	void SendPositionPacket(int client, int object);
	void SendRemovePlayerPacket(int client, int object);
	void SendStatePacket(int client, int object);
	void SendChatPacket(int client, int object, wchar_t *mess);

	int CheckMove(int id);
	void Check_Battle(int ci, unsigned char packet[])
	{
		cs_packet_skill *my_packet = reinterpret_cast<cs_packet_skill*>(packet);
		for (int i = NPC_START; i < NUM_OF_NPC; ++i)
			if (g_clients[i]->is_active)
				if (Is_Attcked(ci, i))
					NPC_HP(ci, i, packet);
	}

	void Player_Respawn(int ci);
	void Buy_State(int ci, unsigned char packet[]);
	void ProcessPacket(int ci, unsigned char packet[]);

	void DisconnectClient(int ci);
	void Shutdown_Server()
	{
		closesocket(m_listenSocket);
		
		m_iocp.~CIocp();
		WSACleanup();
	}


public:
	bool Is_Attcked(int from, int to)
	{
		if (g_clients[from]->x - 1 == g_clients[to]->x && g_clients[from]->y == g_clients[to]->y) return true;
		if (g_clients[from]->x + 1 == g_clients[to]->x && g_clients[from]->y == g_clients[to]->y) return true;
		if (g_clients[from]->x == g_clients[to]->x && g_clients[from]->y - 1 == g_clients[to]->y) return true;
		if (g_clients[from]->x == g_clients[to]->x && g_clients[from]->y + 1 == g_clients[to]->y) return true;
		return false;
	}

	bool Is_Buy(int from, int x, int y)
	{
		if (g_clients[from]->x == x && g_clients[from]->y == y) return true;
		return false;
	}

	bool Is_NPC(int id)
	{
		return (id >= NPC_START) && (id < NUM_OF_NPC);
	}
	bool Is_Close(int from, int to)
	{
		return (g_clients[from]->x - g_clients[to]->x)
			* (g_clients[from]->x - g_clients[to]->x)
			+ (g_clients[from]->y - g_clients[to]->y)
			* (g_clients[from]->y - g_clients[to]->y) <= VIEW_RADIUS * VIEW_RADIUS;
	}




public:
	void SetPos(int beginX, int endX, int beginY, int endY, int startNum, int endNUM)
	{
		std::default_random_engine dre(unsigned int(NULL));
		std::uniform_int_distribution<> limitX(beginX, endX);
		std::uniform_int_distribution<> limitY(beginY, endY);


		for (int i = startNum; i < endNUM; ++i)
		{
			g_clients[i]->x = limitX(dre);
			g_clients[i]->y = limitY(dre);
			g_clients[i]->initi_x = g_clients[i]->x;
			g_clients[i]->initi_y = g_clients[i]->y;
		}
	}

public:
	CThread();
	~CThread();
};
