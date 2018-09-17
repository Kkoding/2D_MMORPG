#pragma once
#pragma once
#pragma comment(lib, "ws2_32")
#pragma comment(lib, "winmm.lib")

using namespace std;

#include <WinSock2.h>
#include <winsock.h>
#include <Windows.h>
#include <iostream>
#include <thread>
#include <vector>
#include <unordered_set>
#include <mutex>
#include <chrono>
#include <queue>
#include <fstream>
#include <random>
#include <ctime>


#include <sqlext.h>

//////////////////////////////////////////

extern "C" {
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
}

using namespace chrono;

#include <tchar.h>
#include <thread>
#include <vector>
#include <mutex>
#include <chrono>
#include <list>

#include "luaconf.h"
#include "enum.h"
#include "struct.h"
#include "protocol.h"


#include "CGameTimer.h"
#include "CIocp.h"
#include "CObjectPool.h"
extern CLIENT* g_clients[NUM_OF_NPC];

#include "CThread.h"
#include "CPlayer.h"

