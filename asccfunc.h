#pragma once
#include <utility>
#include "asctypedefs.h"
void call(uintptr_t funcaddr, int argsptr) {
	ASCCfunc func = (ASCCfunc)funcaddr;
	func(argsptr);
}