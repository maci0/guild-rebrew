


#include <string.h>

// SIZE 0x30
typedef struct {
	int v[12];
} ALLOC_RAUM_BLK;

#pragma pack(push, 1)
// SIZE 0x9c
typedef struct {
	unsigned char type;
	char pad0[0x13];
	unsigned short id;
	int value;
	unsigned short extra;
	int has_blk;
	ALLOC_RAUM_BLK blk;
	char pad2[0x4c];
} ALLOC_RAUM_MSG;
#pragma pack(pop)

int __cdecl cm_EnqueueClientPacket(void*);

int __cdecl cm_RequestAllocRaum(unsigned char id, int value, ALLOC_RAUM_BLK* block, unsigned short extra)
{
	ALLOC_RAUM_MSG msg;

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
	return cm_EnqueueClientPacket(&msg);
}
