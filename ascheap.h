#pragma once
#include <map>
#include "asctypes.h"
#include "asctypedefs.h"
namespace ASCHeap {
	int lastretloc;
	std::map<int, std::pair<byte, int>> heap;
}