// FUNCTION: GOLD 0x004c45c0
// SIZE: 133
// FUNCTION: GOLDTL 0x4c4f30
// SIZE: 133

#include <string.h>

// SIZE 0x30
typedef struct {
	int v[12];
} Blk30;

#pragma pack(push, 1)
// SIZE 0x9c
typedef struct {
	unsigned char type;
	char pad0[0x13];
	unsigned short id;
	int value;
	unsigned short extra;
	int has_blk;
	Blk30 blk;
	char pad2[0x4c];
} Msg4f30;
#pragma pack(pop)

int __cdecl fcn_004c4330(void*);

int __cdecl fcn_004c4f30(unsigned char a1, int a2, Blk30* a3, unsigned short a4)
{
	Msg4f30 m;

	m.type = 0xa;
	if (a1 == 0) {
		return -1;
	}
	m.id = a1;
	m.value = a2;
	m.extra = a4;
	if (a3 != 0) {
		m.blk = *a3;
		m.has_blk = 1;
	} else {
		memset(&m.blk, 0, sizeof(m.blk));
		m.has_blk = 0;
	}
	return fcn_004c4330(&m);
}
