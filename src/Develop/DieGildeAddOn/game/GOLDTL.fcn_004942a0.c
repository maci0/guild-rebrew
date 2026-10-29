typedef struct Player {
	char pad0[0x40];
	int x;
	int y;
	char pad48[0x2f4 - 0x48];
} Player;
// SIZE 0x2f4

typedef struct Share {
	int amount;
	int kind;
	int goal;
} Share;

extern char g_868060[];

#include "Develop/DieGildeAddOn/game/spiel.h"
float __cdecl fcn_00502820(int x0, int y0, int x1, int y1);
unsigned short __cdecl gm_RandomMod(int n);

/* ADDRESS: GOLDTL 0x004942a0 */
void __cdecl fcn_004942a0(unsigned short* e, Share* out)
{
	int total;
	float dist[3];
	int table[3][4];
	float max;
	float inv;
	int i;

	table[0][0] = 4;
	table[0][1] = 0;
	table[0][2] = 3;
	table[0][3] = 1;
	table[1][0] = 3;
	table[1][1] = 1;
	table[1][2] = 2;
	table[1][3] = 0;
	table[2][0] = 2;
	table[2][1] = 0;
	table[2][2] = 4;
	table[2][3] = 1;
	total = (int) (gm_WalkEntityChain(*e) * 0.025f);
	max = 0;
	for (i = 0; i < 3; i++) {
		dist[i] = fcn_00502820(((Player*)g_868060)[0].x, ((Player*)g_868060)[0].y, ((Player*)g_868060)[i + 1].x, ((Player*)g_868060)[i + 1].y);
		if (dist[i] > max) {
			max = dist[i];
		}
		out[i].kind = table[i][0];
		out[i].goal = table[i][1 + gm_RandomMod(3)];
	}
	inv = 1.0f / max;
	for (i = 0; i < 3; i++) {
		dist[i] = inv * dist[i];
		out[i].amount = (int) (total * dist[i]);
	}
}
