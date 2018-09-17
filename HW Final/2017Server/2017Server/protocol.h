#include<Windows.h>
#include <unordered_set>
#include <mutex>
#include "..\..\2017Server\2017Server\lua.h"

#define MAX_BUFF_SIZE   4000
#define MAX_PACKET_SIZE  255

// npc°¡ ¸¹À¸¹Ç·Î ÁöÇüÀ» ³ÐÇôÁÜ
#define BOARD_WIDTH   600
#define BOARD_HEIGHT  400
//#define BOARD_WIDTH   100
//#define BOARD_HEIGHT  100

#define VIEW_RADIUS   10

#define MAX_USER 999	

#define NPC_START  1000
//#define NUM_OF_NPC  10000

// ¸Ê ³ÐÈ÷´Ï±î Àû¾îº¸ÀÌ´Ï npc¼ýÀÚ¸¦ ´Ã·ÁÁÜ
#define NUM_OF_NPC  2100

#define MY_SERVER_PORT  4000

#define MAX_STR_SIZE  100

#define MAP_SIZE 300

#define CS_UP    1
#define CS_DOWN  2
#define CS_LEFT  3
#define CS_RIGHT    4
#define CS_CHAT		5
#define CS_SKILL	6
#define CS_TP	7	
#define CS_STORE	8

#define SC_POS           1
#define SC_PUT_PLAYER    2
#define SC_REMOVE_PLAYER 3
#define SC_CHAT			 4
#define SC_STATE		5
#define SC_STORE		6
#define SC_LOGIN_FAILED 7

#pragma pack (push, 1)

struct cs_packet_up {
	BYTE size;
	BYTE type;
	BYTE zone;
};

struct cs_packet_down {
	BYTE size;
	BYTE type;
};

struct cs_packet_left {
	BYTE size;
	BYTE type;
};

struct cs_packet_right {
	BYTE size;
	BYTE type;
};

struct cs_packet_chat {
	BYTE size;
	BYTE type;
	WCHAR message[MAX_STR_SIZE];
};

struct cs_packet_skill {
	BYTE size;
	BYTE type;
	BYTE value;
	BYTE damage;
};

struct cs_packet_store {
	int max_hp;
	int exp_sum;
	int attack;
};

struct sc_packet_pos {
	BYTE size;
	BYTE type;
	WORD id;
	int x;
	int y;
};

struct sc_packet_put_player {
	BYTE size;
	BYTE type;
	WORD id;
	int x;
	int y;
};
struct sc_packet_remove_player {
	BYTE size;
	BYTE type;
	WORD id;
};

struct sc_packet_chat {
	BYTE size;
	BYTE type;
	WORD id;
	WCHAR message[MAX_STR_SIZE];
};

struct sc_pakcet_discon {
	BYTE size;
	BYTE type;
	WORD id;
};

struct sc_packet_state {
	BYTE size;
	BYTE type;
	WORD id;

	unsigned long long hp;
	int max_hp;

	BYTE level;

	unsigned long long exp;
	int expsum;

	BYTE attack;
};

struct OverlappedEx {
	WSAOVERLAPPED over;
	WSABUF wsabuf;
	unsigned char IOCP_buf[MAX_BUFF_SIZE];
	OPTYPE event_type;
	int event_target;
};

struct CLIENT {
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
	std::chrono::high_resolution_clock::time_point revival_time;
	std::chrono::high_resolution_clock::time_point active_time;
	

	void Reset()
	{
		hp = 0;
		die = true;
		exp = 0;
	}

	void SetInitiate()
	{
		x = 4;
		y = 4;
		curr_packet_size = 0;
		prev_packet_data = 0;
		die = false;
		maxhp = 100;
		connect = true;
		exp = 0;

	}
	
};


struct Timer_Event {
	int object_id;
	std::chrono::high_resolution_clock::time_point exec_time;
	Event_Type event;
};


#pragma pack (pop)