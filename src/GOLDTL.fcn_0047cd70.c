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

extern Anim g_100e7a0[0x30];

void __cdecl fcn_0047cbf0(int x, int y, int tex, void* seq, int frame);
void __cdecl fcn_0047cba0(int x, int y, int tex, void* seq, int frame);

// FUNCTION: GOLDTL 0x47cd70
// SIZE: 125
void __cdecl fcn_0047cd70(int i, int tex)
{
	short x;
	short y;

	if (g_100e7a0[i].seq) {
		x = g_100e7a0[i].x;
		y = g_100e7a0[i].y;
		if (g_100e7a0[i].looping) {
			fcn_0047cbf0(x + 6, y + 6, tex, g_100e7a0[i].seq, g_100e7a0[i].w6);
		}
		fcn_0047cba0(x, y, tex, g_100e7a0[i].seq, g_100e7a0[i].w6);
	}
}
