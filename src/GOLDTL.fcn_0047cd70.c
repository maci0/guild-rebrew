typedef struct Anim {
	void* seq;
	unsigned char frame;
	unsigned char b5;
	unsigned short w6;
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

void __cdecl fcn_0047cbf0(int x, int y, int tex, void* seq, int frame);
void __cdecl fcn_0047cba0(int x, int y, int tex, void* seq, int frame);

// FUNCTION: GOLDTL 0x47cd70
void __cdecl fcn_0047cd70(int i, int tex)
{
	short x;
	short y;

	if (((Anim*)g_100e7a0)[i].seq) {
		x = ((Anim*)g_100e7a0)[i].x;
		y = ((Anim*)g_100e7a0)[i].y;
		if (((Anim*)g_100e7a0)[i].looping) {
			fcn_0047cbf0(x + 6, y + 6, tex, ((Anim*)g_100e7a0)[i].seq, ((Anim*)g_100e7a0)[i].w6);
		}
		fcn_0047cba0(x, y, tex, ((Anim*)g_100e7a0)[i].seq, ((Anim*)g_100e7a0)[i].w6);
	}
}
