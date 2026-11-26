#include <stdlib.h>
#pragma intrinsic(strcat)
#include "client_data.h"
typedef struct F8 {
	unsigned int mask;
	int b;
} F8;
/* SIZE 0x8 */
/* role and slot records copied by srv_GetEntityOfficeSlot */
typedef struct OfficeRecord {
	int v[6];
} OfficeRecord;
/* SIZE 0x18 */
int __cdecl fcn_004a5e60(void *, int, F8, float, float, int *); int __cdecl gm_ResolveEntityById(void *, int, int, int);
#include "Develop/DieGildeAddOn/game/entity_record.h"
extern char g_868060[];
unsigned short __cdecl gm_RandomMod(int);
int __cdecl gm_WalkEntityChain(unsigned short);
void __cdecl fcn_004c51a0(int, int, unsigned char, int);
void __cdecl cm_BeginPacketFieldDelta(void *, int);
void __cdecl cm_AppendPacketFieldDelta(int, int, int, void *);
void __cdecl cm_AppendPacketFieldValue(int, int, int, void *);
void __cdecl fcn_004c5360(void);
unsigned int __cdecl fcn_004a55c0(void *, unsigned int, unsigned int *, float, float, unsigned short *);
int __cdecl srv_GetEntityOfficeSlot(void *, void *, void *);
void __cdecl amt_SendOfficeCommand(void *, int, int, int, int);
void __cdecl fcn_00545d40(int, int, char *, int, int, char *);
void __cdecl io_FormatTextBuffer(char *, int, ...);
int __cdecl fcn_0064d41a(char *, char *, ...);
#include "Develop/DieGildeAddOn/game/game_data.h"
/* ADDRESS: GOLDTL 0x005d9000 */
void __cdecl fcn_005d9000(unsigned char *e, int mode)
{
	char msg[0x400];
	char t1[0x400];
	char t2[0x400];
	char t4[0x400];
	char t3[0x400];
	unsigned char *ent;
	ENTITY_RECORD *best;
	int found;
	char delta;
	int i;
	int score;

	if (mode < 0 || mode > 5)
		return;
	io_FormatTextBuffer(msg, 0x1df7, *(unsigned short *) e);
	if (mode == 0) {
		F8 f;
		int v;
		int r;

		f.mask = 0x80;
		f.b = 0;
		if (fcn_004a5e60(e, 2, f, 0.0f, 100.0f, &found) == 0)
			return;
		gm_ResolveEntityById(&ent, 0, 0, found);
		best = &((ENTITY_RECORD*)g_7f4ca0)[*(unsigned short *) (ent + 0x27)];
		v = gm_WalkEntityChain(best->entity_index);
		r = gm_RandomMod(3) + 2;
		score = (int) ((double) r * ((double) v * 0.01));
		fcn_004c51a0(best->entity_id, -1, g_773d75, score);
		io_FormatTextBuffer(t1, 0x1df8, best->entity_index, ent, best->entity_index, score,
					 &g_868060[g_773d75 * 0x2f4 + 0x20]);
	} else if (mode == 1) {
		int a;

		io_FormatTextBuffer(t1, 0x1df9);
		io_FormatTextBuffer(t2, 0x1dfa);
		fcn_0064d41a(t3, "%s%s%s", msg, t1, t2);
		io_FormatTextBuffer(t2, 0x1dfb);
		fcn_0064d41a(t4, "%s%s", msg, t1, t2);
		strcat(msg, t1);
		for (i = 0; i < 768; i++) {
			best = &((ENTITY_RECORD*)g_7f4ca0)[i];
			if (best->entity_index != 0xffff) {
				if (best->unk_024 < -0x14) {
					if (gm_RandomMod(2) != 0) {
						a = abs(best->unk_024 / 2);
						cm_BeginPacketFieldDelta(best, best->entity_id);
						cm_AppendPacketFieldDelta(4, 1, 0x24, &a);
						fcn_004c5360();
						if (best->entity_state == 6 || best->entity_state == 7)
							fcn_00545d40(best->entity_id, -1, t3, 1, 0x601, 0);
					} else {
						if (best->entity_state == 6 || best->entity_state == 7)
							fcn_00545d40(best->entity_id, -1, t4, 1, 0x601, 0);
					}
				} else if (best->entity_state == 6 || best->entity_state == 7) {
					fcn_00545d40(best->entity_id, -1, msg, 1, 0x601, 0);
				}
			}
		}
		return;
	} else if (mode == 2) {
		F8 f;

		f.mask = 0xa07c43b0;
		f.b = 1;
		if (fcn_004a5e60(e, 2, f, 0.0f, 100.0f, &found) == 0)
			return;
		gm_ResolveEntityById(&ent, 0, 0, found);
		best = &((ENTITY_RECORD*)g_7f4ca0)[*(unsigned short *) (ent + 0x27)];
		delta = (char) (ent[0x5c] - gm_RandomMod(0x10) - 10);
		if (delta <= 0)
			return;
		cm_BeginPacketFieldDelta(ent, *(int *) (ent + 1));
		cm_AppendPacketFieldDelta(1, 1, 0x5c, &delta);
		fcn_004c5360();
		io_FormatTextBuffer(t1, 0x1dfc, best->entity_index, ent);
	} else if (mode == 3) {
		OfficeRecord role;
		OfficeRecord slot;
		unsigned int a;
		unsigned short b;

		a = 0x400800;
		if (fcn_004a55c0(e, 1, &a, 0.0f, 100.0f, &b) == 0)
			return;
		best = &((ENTITY_RECORD*)g_7f4ca0)[b];
		if (srv_GetEntityOfficeSlot(best, &role, &slot) == 0)
			return;
		amt_SendOfficeCommand((void *) slot.v[0], 0, 0, 4, 0xff);
		io_FormatTextBuffer(t1, 0x1dfd, best->entity_index, best->entity_index, best->entity_index);
	} else if (mode == 4) {
		unsigned int a;
		unsigned short b;
		int picked;
		int n;

		a = 0x300000;
		delta = gm_RandomMod(0x15);
		if (fcn_004a55c0(e, 1, &a, 0.0f, 100.0f, &b) == 0)
			return;
		best = &((ENTITY_RECORD*)g_7f4ca0)[b];
		picked = -1;
		n = gm_RandomMod(5);
		for (i = 5; i != 0; i--) {
			if (*((unsigned char *) best + 0x80 + n) < 0xe7) {
				picked = n;
				break;
			}
			n = (n + 1) % 5;
		}
		if (picked == -1)
			return;
		cm_BeginPacketFieldDelta(best, best->entity_id);
		cm_AppendPacketFieldValue(1, 1, picked + 0x80, &delta);
		fcn_004c5360();
		io_FormatTextBuffer(t1, 0x1dfe, best->entity_index, best->entity_index, picked + 0x16b7);
	} else if (mode == 5) {
		ENTITY_RECORD *slots[8];
		F8 f;
		int id;
		int n;
		int v;
		int bv;

		n = 0;
		for (i = 0; i < 768 && n < 8; i++) {
			if (((ENTITY_RECORD*)g_7f4ca0)[i].entity_state == 6 || ((ENTITY_RECORD*)g_7f4ca0)[i].entity_state == 7
				|| ((ENTITY_RECORD*)g_7f4ca0)[i].entity_state == 5) {
				slots[n] = &((ENTITY_RECORD*)g_7f4ca0)[i];
				n++;
			}
		}
		best = slots[0];
		bv = gm_WalkEntityChain(best->entity_index);
		for (i = 1; i < n; i++) {
			v = gm_WalkEntityChain(slots[i]->entity_index);
			if (v < bv) {
				bv = v;
				best = slots[i];
			}
		}
		f.mask = 0xb07d43b4;
		f.b = 1;
		if (fcn_004a5e60(best, 4, f, 0.0f, 100.0f, &id) == 0)
			return;
		v = gm_RandomMod(5) + 3;
		score = (int) ((float) v * bv * 0.01f);
		gm_ResolveEntityById(&ent, 0, 0, id);
		fcn_004c51a0(best->entity_id, -1, g_773d75, score);
		io_FormatTextBuffer(t1, 0x1dff, best->entity_index, ent, best->entity_index, score);
	} else {
		return;
	}
	strcat(msg, t1);
	for (i = 0; i < 768; i++) {
		if (((ENTITY_RECORD*)g_7f4ca0)[i].entity_state == 6 || ((ENTITY_RECORD*)g_7f4ca0)[i].entity_state == 7)
			fcn_00545d40(((ENTITY_RECORD*)g_7f4ca0)[i].entity_id, -1, msg, 1, 0x5fe, 0);
	}
}
