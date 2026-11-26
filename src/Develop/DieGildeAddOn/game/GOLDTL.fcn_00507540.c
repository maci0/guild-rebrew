#include <math.h>
#include <string.h>
#include "Develop/DieGildeAddOn/game/game_timestamp.h"







typedef struct {
	char pad0[0x164];
	unsigned char stat;
	char pad1[0x174 - 0x165];
	int day;
	char pad2[0x21c - 0x178];
} Ent;

extern Ent g_7f4ca0[];

int __cdecl gm_GetOppositeStatIndex(int stat);
int __cdecl gm_MapEntityStatRange(int stat);
float __cdecl gm_GetEntitySkill(Ent* e, int k);
int __cdecl fcn_00500cb0(GAME_TIMESTAMP* a, GAME_TIMESTAMP* b);
int __cdecl gm_GetElapsedMinutes(GAME_TIMESTAMP* a, GAME_TIMESTAMP* b);
void __cdecl gm_AddTime(GAME_TIMESTAMP* t, int a, int b, int c);

/* ADDRESS: GOLDTL 0x00507540 */
float __cdecl fcn_00507540(int idx, GAME_TIMESTAMP* out)
{
	int r;
	int k;
	int n;
	int d;
	unsigned short h;
	float v;
	float f;
	float num;

	r = gm_GetOppositeStatIndex(g_7f4ca0[idx].stat);
	if (r == 0 || r >= 6)
		return 0.0f;
	k = gm_MapEntityStatRange(g_7f4ca0[idx].stat);
	if (k == 0xb)
		v = gm_GetEntitySkill(&g_7f4ca0[idx], 2);
	else if (k == 0xc)
		v = gm_GetEntitySkill(&g_7f4ca0[idx], 3);
	else if (k == 0xa)
		v = gm_GetEntitySkill(&g_7f4ca0[idx], 3);
	else if (k == 8)
		v = gm_GetEntitySkill(&g_7f4ca0[idx], 0);
	else if (k == 9)
		v = gm_GetEntitySkill(&g_7f4ca0[idx], 4);
	else
		v = gm_GetEntitySkill(&g_7f4ca0[idx], 1);
	if (!(v > 0.25f))
		v = 0.25f;
	num = (float) r * 16.0f + 72.0f;
	n = (int) (num / (v + 1.0f));
	{
		GAME_TIMESTAMP a;
		GAME_TIMESTAMP b;
		GAME_TIMESTAMP z;
		memset(&a, 0, sizeof(a));
		memset(&b, 0, sizeof(b));
		memset(&z, 0, sizeof(z));

		a.unit_0 = (int) ((double) n * 0.041666666666666664);
		a.hour = (unsigned short) (int) fmod((double) n, 24.0);
		if ((float) a.hour > 21.0f) {
			a.unit_0++;
			a.hour = (unsigned short) (int) ((float) a.hour - 21.0f + 7.0f);
		} else if ((float) a.hour < 7.0f) {
			a.hour += 6;
		}
		d = g_7f4ca0[idx].day;
		h = (unsigned short) gm_GameTime.b;
		b.unit_0 = d;
		b.hour = h;
		if (fcn_00500cb0(&b, &a) < 0) {
			f = (float) gm_GetElapsedMinutes(&z, &b) / (float) gm_GetElapsedMinutes(&z, &a);
			gm_AddTime(&a, gm_GameTime.a * 24 + h, 0, 0);
			gm_AddTime(&a, -h - d * 24, 0, 0);
			*out = a;
			return f;
		}
	}
	return 1.0f;
}
