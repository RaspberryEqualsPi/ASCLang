#pragma once
#include <vector>
#include "asctypes.h"
#include "asctypedefs.h"
namespace ASCHeap {
	struct ASCHeapValue {
		byte type = types::INT;
		int size = 1;
		std::vector<byte> data;
	};
	std::vector<ASCHeapValue> heap;
}