

#include "Develop/DieGildeAddOn/game/entity_record.h"













extern int g_664e1c[3];
extern int g_664e28[3];
extern int g_6653bc;
extern unsigned char g_773d75;

void __cdecl gm_RandomizeIntArray(int, int *);
int __cdecl _ftol(void);
int __cdecl gm_RandomMod(int);
int __cdecl gm_GetRangeStatId(int, int);
int __cdecl gm_IsInRange(int);
int __cdecl cm_RequestAllocSpieler(int, int, int, int, int, int, int, int);
int __cdecl cm_GetCommandStatus(int);
void __cdecl cm_StepCommandQueue(void);
float __cdecl gm_RandomFloat01(void);
char *__cdecl cm_GetCommandResult(int);
void __cdecl cm_RequestMoveCredits(int, int, unsigned char, int);
#include "Develop/DieGildeAddOn/command/client_packet_builder.h"
void __cdecl cm_AppendPacketFieldDelta(int, int, int, int *);
void __cdecl cm_RequestChangeAttribute(void);
void __cdecl cm_RequestChangeBits(int, int, int, int, int);

/* ADDRESS: GOLD 0x4ad7a0 */
void __cdecl gm_ReplenishOfficeCandidates(void)
{
	int cnt;
	int seven;
	int kind;
	float score[3];
	int owner[3];
	int kinds[3];
	int ids[15];
	int i;
	int j;
	int k;
	int h;
	int x;
	int v;
	int mask;
	char *candidate;
	ENTITY_RECORD *p;

	ids[0] = 1;
	ids[1] = 2;
	ids[2] = 3;
	ids[3] = 4;
	ids[4] = 5;
	ids[5] = 6;
	ids[6] = 7;
	ids[7] = 8;
	ids[8] = 9;
	ids[9] = 10;
	ids[10] = 11;
	ids[11] = 12;
	ids[12] = 13;
	ids[13] = 14;
	ids[14] = 15;
	score[0] = 0.0f;
	score[1] = 0.0f;
	score[2] = 0.0f;
	owner[0] = -1;
	owner[1] = -1;
	owner[2] = -1;
	kinds[0] = 15;
	kinds[1] = 21;
	kinds[2] = 27;
	for (i = 0; i < 768; i++) {
		p = ((ENTITY_RECORD*)&((ENTITY_RECORD_VIEW*)g_7f4ca0)[i]);
		if (p->unk_00d >= 7 &&
		    (p->entity_state == 6 || p->entity_state == 7 || p->entity_state == 5 || p->entity_state == 4 ||
			p->entity_state == 3 || p->entity_state == 2)) {
			k = 3;
			do {
				j = k - 1;
				if ((p->entity_flags & g_664e28[j]) == 0 && (p->entity_flags & g_664e1c[j]) != 0) {
					if (p->entity_id != owner[(j + 1) % 3] && p->entity_id != owner[(j + 2) % 3]) {
						score[j] += 0.67f;
						owner[j] = p->entity_id;
					}
					score[j] += 0.33f;
				}
			} while (--k != 0);
		}
	}
	gm_RandomizeIntArray(15, ids);
	for (j = 0, k = 0; j < 3; j++) {
		for (cnt = (int) score[j]; cnt < 2; cnt++) {
			x = gm_GetRangeStatId(ids[k++], (unsigned short) gm_RandomMod(3) + 4);
			h = cm_RequestAllocSpieler(3, -1, -1, gm_RandomMod(8) + 0x19, -1, x, 0, gm_IsInRange(x));
			if (h != -1) {
				do {
					if (cm_GetCommandStatus(h) != 0) {
						break;
					}
					cm_StepCommandQueue();
				} while (1);
			}
			if (cm_GetCommandStatus(h) != 1) {
				return;
			}
			seven = 7;
			v = (int) (g_6653bc * ((gm_RandomFloat01() + 1.0f) * 0.5f));
			kind = kinds[j];
			candidate = cm_GetCommandResult(h);
			cm_RequestMoveCredits(*(int *) (candidate + 4), -1, g_773d75, v);
			cm_BeginPacketFieldDelta(candidate, *(int *) (candidate + 4));
			cm_AppendPacketFieldDelta(1, 1, 0xd, &seven);
			cm_AppendPacketFieldDelta(1, 1, 0x167, &kind);
			cm_RequestChangeAttribute();
			mask = g_664e1c[j];
			if (j == 2) {
				mask |= g_664e1c[(unsigned short) gm_RandomMod(j)];
			}
			cm_RequestChangeBits(*(int *) (candidate + 4), 0x1cc, 4, mask, 0);
		}
	}
}
