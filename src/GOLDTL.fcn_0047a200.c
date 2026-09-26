typedef struct Anim {
	void* seq;
	unsigned char frame;
	unsigned char b5;
	short w6;
	int looping;
	char running;
	char padd;
	short x;
	short y;
	short pad12;
} Anim;
// SIZE 0x14

#include "client_types.h"
extern Anim_100e7a0 g_100e7a0[0x30];

// FUNCTION: GOLDTL 0x47a200
// SIZE: 123
int __cdecl fcn_0047a200(short x, short y, void* img, unsigned char flag)
{
	int i;

	for (i = 0; i < 0x30; i++) {
		if (((Anim*)g_100e7a0)[i].seq == 0) {
			break;
		}
	}
	if (i >= 0x30) {
		return -1;
	}
	((Anim*)g_100e7a0)[i].seq = img;
	((Anim*)g_100e7a0)[i].x = x;
	((Anim*)g_100e7a0)[i].y = y;
	((Anim*)g_100e7a0)[i].frame = 0;
	((Anim*)g_100e7a0)[i].b5 = 0;
	((Anim*)g_100e7a0)[i].w6 = 0;
	if (flag & 1) {
		((Anim*)g_100e7a0)[i].looping = 1;
	}
	return i;
}
