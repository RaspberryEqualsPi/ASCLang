#include <iostream>
#include "ascmain.h"
#include "ascfuncs.h"
void testfunc(int argptr) {
	std::cout << "called with argument " << argptr << "\n";
}
byte* ui2b(unsigned int i) {
	byte b1 = *(byte*)&i;
	byte b2 = *(byte*)((int)&i + sizeof(byte));
	byte b3 = *(byte*)((int)&i + sizeof(byte) * 2);
	byte b4 = *(byte*)((int)&i + sizeof(byte) * 3);
	byte* res = (byte*)malloc(4);
	res[0] = b1;
	res[1] = b2;
	res[2] = b3;
	res[3] = b4;
	return res;
}
void ph(std::map<int, std::pair<byte, int>> heap) {
	for (auto const& [key, val] : heap) {
		std::cout << "key: " << key << " first: " << (int)val.first << ", second: " << (int)val.second << "\n";
	}
}
int main() {
	uintptr_t funcaddr = (uintptr_t)print;
	byte* funcad = ui2b(funcaddr);
	byte* one = ui2b(1);
	byte* two = ui2b(2);
	std::vector<byte> code = { opcodes::SET, one[0], one[1], one[2], one[3], one[0], one[1], one[2], one[3], opcodes::SETEND, two[0], two[1], two[2], two[3], one[0], one[1], one[2], one[3], opcodes::CALL, funcad[0], funcad[1], funcad[2], funcad[3], one[0], one[1], one[2], one[3] };
	free(funcad);
	free(one);
	ASCInterp::interpreter inter(code);
	inter.run();
	ASCInterp::instruction inst = inter.getstackind(0);
	std::cout << (uintptr_t)testfunc << "\n";
	std::cout << (int)inst.inst << ", " << inst.operand << ", " << inst.val << "\n";
	ph(ASCHeap::heap);
}