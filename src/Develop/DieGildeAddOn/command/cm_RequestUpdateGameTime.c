#include "Develop/client_types.h"
extern pos14_7f4c00 gm_GameTime;



int __cdecl cm_EnqueueClientPacket(void*);

typedef struct
{
	int a;
	int b;
	int c;
	short d;
} Quad4;
// SIZE 0x10

int __cdecl gm_CompareGameTime(void*, char*);

int __cdecl cm_RequestUpdateGameTime(Quad4* stamp)
{
	char buf[0x9c];

	if (gm_CompareGameTime(stamp, ((char*)&gm_GameTime)) == 0) {
		return -1;
	}
	buf[0] = 0x1e;
	*(int*) (buf + 0x10) = stamp->a;
	*(int*) (buf + 0x14) = stamp->b;
	*(int*) (buf + 0x18) = stamp->c;
	*(short*) (buf + 0x1c) = stamp->d;
	return cm_EnqueueClientPacket(buf);
}
