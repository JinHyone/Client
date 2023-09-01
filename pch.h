#pragma once

#include <vector>
#include <list>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <format>
#include <filesystem>
#include <map>
#include <functional>
#include <assert.h>
#include <queue>



#include "CorePch.h"

#include "Protocol.pb.h"
#include "Enum.pb.h"
#include "Struct.pb.h"

#include <Windows.h>


#include "types.h"
#include "Utils.h"
#include "Defines.h"
#include "enums.h"
#include "Values.h"

#define _CTRDEBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>

#ifdef _DEBUG
#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif // DEBUG

#pragma comment(lib, "msimg32.lib")


// »ç¿îµå
#include <mmsystem.h>
#include <dsound.h>
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "dsound.lib")

#ifdef _DEBUG
#pragma comment(lib, "ServerCore\\Debug\\ServerCore.lib")
#pragma comment(lib, "Protobuf\\Debug\\libprotobufd.lib")
#else
#pragma comment(lib, "ServerCore\\Release\\ServerCore.lib")
#pragma comment(lib, "Protobuf\\Release\\libprotobuf.lib")
#endif

using namespace std;
namespace fs = filesystem;