#include "client_types.h"
extern pos14_7f4c00 gm_GameTime;



int __cdecl fcn_004c4330(void*);

typedef struct
{
	int a;
	int b;
	int c;
	short d;
} Quad4;
// SIZE 0x10

int __cdecl fcn_00500cb0(void*, char*);

int __cdecl fcn_004c5700(Quad4* stamp)
{
	char buf[0x9c];

	if (fcn_00500cb0(stamp, ((char*)&gm_GameTime)) == 0) {
		return -1;
	}
	buf[0] = 0x1e;
	*(int*) (buf + 0x10) = stamp->a;
	*(int*) (buf + 0x14) = stamp->b;
	*(int*) (buf + 0x18) = stamp->c;
	*(short*) (buf + 0x1c) = stamp->d;
	return fcn_004c4330(buf);
}
