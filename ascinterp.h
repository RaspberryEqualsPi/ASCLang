#pragma once
#include <vector>
#include "asctypedefs.h"
namespace ASCInterp {
	struct instruction {
		byte inst;
		uintptr_t operand;
	};
	class interpreter {
	private:
		std::vector<std::pair<byte, uintptr_t>> stack;
	};
}