#pragma once
class CPlayer
{
private:
	int x;
	int y;
	char id[10];
	int initi_x;
	int initi_y;

	std::chrono::high_resolution_clock::time_point last_move_time;

	bool is_active;
	bool connect;

	lua_State *L;

	SOCKET client_socket;
	OverlappedEx recv_over;
	unsigned char packet_buf[MAX_PACKET_SIZE];
	int prev_packet_data;
	int curr_packet_size;
	std::unordered_set<int> view_list;
	std::mutex vl_lock;

	int bye;
	bool move;
	int count;

	int hp;
	int level;
	int exp;
	int attack;
	int maxhp;

	bool trac;
	int trac_client;
	int turn;
	int monster_level;
	bool die;
	int exp_sum;
	high_resolution_clock::time_point revival_time;
	high_resolution_clock::time_point active_time;


public:
	int getX() { return x; }
	int getY() { return y; }
	int getCount() { return count; }

	bool setConnect(bool s) { connect = s; }
	bool setLua(lua_State* s) { L = s; }





//private:
//	static CPlayer* Instance;
//public:
//	static CPlayer* getInstance()
//	{
//		if (nullptr == Instance)
//			Instance = new CPlayer();
//		return Instance;
//	};
//
//	static void Release()
//	{
//		if (nullptr != Instance)
//			delete Instance;
//		Instance = nullptr;
//	}



private:
	CPlayer();
public:
	~CPlayer();
};

#define PLAYERSINGLE CPlayer::getInstance()