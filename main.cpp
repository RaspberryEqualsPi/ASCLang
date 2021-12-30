#include <iostream>
#include "ascmain.h"
void testfunc(int argptr) {
	std::cout << "called with argument " << argptr << "\n";
}
int main() {
	call((uintptr_t)testfunc, 10);
	uintptr_t funcaddr = (uintptr_t)testfunc;
	byte b1 = *(byte*)&funcaddr;
	byte b2 = *(byte*)((int)&funcaddr + sizeof(byte));
	byte b3 = *(byte*)((int)&funcaddr + sizeof(byte) * 2);
	byte b4 = *(byte*)((int)&funcaddr + sizeof(byte) * 3);
	std::vector<byte> code = {opcodes::CALL, b1, b2, b3, b4, 0, 0, 0, 0, opcodes::CALL, b1, b2, b3, b4, 0, 0, 0, 0};
	ASCInterp::interpreter inter(code);
	inter.run();
	ASCInterp::instruction inst = inter.getstackind(0);
	std::cout << (uintptr_t)testfunc << "\n";
	std::cout << (int)inst.inst << ", " << inst.operand << ", " << inst.val << "\n";
}