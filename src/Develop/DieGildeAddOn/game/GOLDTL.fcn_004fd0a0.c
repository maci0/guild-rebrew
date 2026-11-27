/* Per-tick refresh of the visible entity rows: sends the three slot amounts
 * and the averaged fill level, then updates the row's animation values. */

extern int g_773d48;
extern unsigned char g_slot_table[2];
extern int g_aed32c;
extern double g_6629c8;
#include "Develop/DieGildeAddOn/game/game_data.h"
extern double g_6640f0;

void __cdecl gm_FindRichestEntity(short*, int*);
int __cdecl gm_WalkEntityChain(unsigned short);
void __cdecl cm_BeginPacketFieldDelta(char*, int);
void __cdecl cm_AppendPacketFieldDelta(int, int, int, int*);
void __cdecl cm_RequestChangeAttribute(void);
void __cdecl cm_StepCommandQueue(void);
void __cdecl cm_RequestChangeFloat(int, int, float);
void __cdecl cm_BeginSecondaryPacketDelta(int*);
int __cdecl cm_AppendDesireDelta(unsigned char, float);
void __cdecl cm_SendChangeDesire(void);

/* ADDRESS: GOLDTL 0x004fd0a0 */
void __cdecl fcn_004fd0a0(void)
{
	short flag;
	int n;
	int total;
	int count;
	int v;
	int r;
	int i;
	/* Unaligned 8-byte temp: the native body stores the ratio as a qword at
	 * [esp+0x24] without a /Oy frame, so it cannot be a plain `double` local. */
	float dmem[2];
	float inv;

	char* e;

	gm_FindRichestEntity(&flag, &n);
	g_773d48 = 0;
	for (e = (char*) g_slot_table; (int) e < (int) g_slot_table + 0x65400; e += 0x21c) {
		if (g_773d48 > 0x40) {
			cm_StepCommandQueue();
			g_773d48 = 0;
		}
		if (*(short*) e == -1) {
			continue;
		}
		if (*(unsigned char*) (e + 2) >= 0xa) {
			continue;
		}
		if (*(unsigned char*) (e + 8) <= 0) {
			continue;
		}
		total = 0;
		count = 0;
		r = gm_WalkEntityChain(*(unsigned short*) e);
		cm_BeginPacketFieldDelta(e, *(int*) (e + 4));
		for (i = 0; i < 3; i++) {
			v = *(int*) (e + 0x1d8 + i * 4);
			total += v;
			count += v != 0;
			cm_AppendPacketFieldDelta(4, 1, (int) e + 0x1d4 + i * 4 - g_aed32c, &v);
		}
		count = (r + total) / (count + 1);
		cm_AppendPacketFieldDelta(4, 1, ((int) e - g_aed32c) + 0x1e0, &r);
		*(double*) dmem = (double) count / (double) r;
		if (!(*(double*) dmem < g_6629c8)) {
			*(double*) dmem = 1.0;
		}
		inv = 1.0f - (float) r / (float) n;
		cm_RequestChangeAttribute();
		g_773d48++;
		cm_RequestChangeFloat(*(int*) (e + 4), 0x1e4, -(*(float*) (e + 0x1e4) - (*(double*) dmem + inv) * 0.5));
		inv = (float) (-(*(float*) (e + 0xb4) - g_6640f0 * *(float*) (e + 0xb4)));
		cm_BeginSecondaryPacketDelta((int*) e);
		cm_AppendDesireDelta(3, inv);
		cm_SendChangeDesire();
		g_773d48++;
	}
	g_773d48 = 0;
}
