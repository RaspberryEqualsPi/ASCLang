#pragma once
#include <vector>
#include <iostream>
#include "ascheap.h"
#include "asctypes.h"
#include "asctypedefs.h"
int ASC_ToInt(std::vector<byte> data) {
	int res;
	byte* resb = (byte*)malloc(4);
	resb[0] = data[0];
	resb[1] = data[1];
	resb[2] = data[2];
	resb[3] = data[3];
	res = *(int*)resb;
	free(resb);
	return res;
}
void print(int argsptr) {
	byte type;
	std::vector<int> data;
	int i = argsptr;
	while (ASCHeap::heap[i].first == types::RAW) {
		data.push_back(ASCHeap::heap[i].second);
		i++;
	}
	type = ASCHeap::heap[i].first;
	switch (type) {
	case types::ENDINT:
		std::cout << data[0] << "\n";
	}
}