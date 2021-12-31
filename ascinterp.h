#pragma once
#include <thread>
#include <vector>
#include "ascheap.h"
#include "ascfuncs.h"
#include "asccfunc.h"
#include "ascopcodes.h"
#include "asctypedefs.h"
namespace ASCInterp {
	struct instruction {
		byte inst;
		uintptr_t operand;
		int val;
		instruction(byte ins, uintptr_t operan, int va) {
			inst = ins;
			operand = operan;
			val = va;
		}
		instruction(){}
	};
	class interpreter {
	public:
		instruction getstackind(int index) {
			std::pair<std::pair<byte, uintptr_t>, int> data = stack[index];
			return instruction(data.first.first, data.first.second, data.second);
		}
		void clearstack() {
			stack.clear();
		}
		void run() {
			runinternal();
		}
		interpreter(std::vector<byte> opcodes) {
			for (int i = 0; i < opcodes.size(); i += (sizeof(uintptr_t) + sizeof(int) + sizeof(byte))) {
				byte opcode = opcodes[i];
				uintptr_t operand = *(uintptr_t*)(&(opcodes[i]) + sizeof(byte));
				int val = *(int*)(&(opcodes[i]) + sizeof(byte) + sizeof(uintptr_t));
				std::pair<std::pair<byte, uintptr_t>, int> inst;
				inst.first.first = opcode;
				inst.first.second = operand;
				inst.second = val;
				stack.push_back(inst);
			}
		}
	private:
		void runinternal() {
			while (stack.size() > 0) {
				instruction currentinst = getstackind(0);
				switch (currentinst.inst) {
				case opcodes::CALL:
					call(currentinst.operand, currentinst.val);
					break;
				case opcodes::SET:
					if (((signed int)ASCHeap::heap.size()) - 1 < (signed int)currentinst.operand) {
						ASCHeap::heap.push_back(std::make_pair<byte, int>((byte)types::RAW, 0));
					}
					ASCHeap::heap[currentinst.operand].first = types::RAW;
					ASCHeap::heap[currentinst.operand].second = currentinst.val;
					break;
				case opcodes::SETEND:
					if (((signed int)ASCHeap::heap.size()) - 1 < (signed int)currentinst.operand) {
						ASCHeap::heap.push_back(std::make_pair<byte, int>((byte)currentinst.val, 0));
					}
					ASCHeap::heap[currentinst.operand].first = (byte)currentinst.val;
					ASCHeap::heap[currentinst.operand].second = 0;
					break;
				default:
					std::cout << "[ERROR] Illegal instruction invoked.\n";
				}
				if (stack.size() == 1)
					break;
				stack.erase(stack.begin());
			}
		}
		std::vector<std::pair<std::pair<byte, uintptr_t>, int>> stack;
	};
}