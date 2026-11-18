


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

int __cdecl fcn_004c4f30(unsigned char id, int value, Blk30* block, unsigned short extra)
{
	Msg4f30 msg;

	msg.type = 0xa;
	if (id == 0) {
		return -1;
	}
	msg.id = id;
	msg.value = value;
	msg.extra = extra;
	if (block != 0) {
		msg.blk = *block;
		msg.has_blk = 1;
	} else {
		memset(&msg.blk, 0, sizeof(msg.blk));
		msg.has_blk = 0;
	}
	return fcn_004c4330(&msg);
}
