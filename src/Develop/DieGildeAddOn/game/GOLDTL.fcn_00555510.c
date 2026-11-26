#include "Develop/DieGildeAddOn/game/entity_record.h"
#pragma optimize("y", off)
#include <string.h>
extern char g_7f4ca0[];
extern char g_6a5e88[];
extern char g_773d75;
extern short g_aed32c;
extern float g_665e9c;
extern double g_662a08;

char* __cdecl gm_StartFilteredEntitySearch(int, ...);
char* __cdecl fcn_00502cd0(int, ...);
char* __cdecl gm_FindNextFilteredEntity(void);
void __cdecl he_FreeAction(char*);
int __cdecl fcn_00555490(short*, int*, int*);
float __cdecl fcn_0050bb50(int, unsigned char);
int __cdecl gm_RandomMod(unsigned short);
int __cdecl gm_AccumulateTyped2(int);
void __cdecl fcn_004c4eb0(unsigned int);
void __cdecl fcn_004c4ef0(unsigned int);
int __cdecl fcn_004c51f0(int, int, short, int, char, int);
void __cdecl fcn_004c51a0(int, int, char, int);
int __cdecl fcn_004c4670(unsigned char, unsigned char, short, void*);
void __cdecl cm_BeginPacketFieldDelta(int, int);
void __cdecl fcn_004c5360(void);
void __cdecl gm_AddTime(int*, int, int, int);

/* ADDRESS: GOLDTL 0x00555510 */
void __cdecl gm_SimulateWirtshaus(char* action)
{
	struct {
		unsigned char* p0;
		char* p4;
		char* p8;
	} ent[16];
	int v;
	int x1;
	int y1;
	int count;
	int mx;
	int idx;
	int end;
	int w;
	int i;
	char* p;
	char* q;

	if (*(int*) (action + 0x70) == -2) {
		he_FreeAction(action);
		return;
	}
	p = (char*) ent; count = sizeof(ent);
	__asm {
		mov edi, p
		mov ebx, count
		xor eax, eax
		lea ecx, [edi+edi*2]
		and ecx, 3
		sub ebx, ecx
		jle short fill_done_555510
		rep stosb
		mov ecx, ebx
		and ebx, 3
		shr ecx, 2
		rep stosd
	fill_done_555510:
		add ecx, ebx
		rep stosb
	}

	i = 0;
	ent[0].p0 = (unsigned char*) gm_StartFilteredEntitySearch(1, 5, 0x16);
	if (ent[0].p0 != 0) {
		p = (char*) ent;
		do {
			if (i >= 0x10) {
				break;
			}
			q = fcn_00502cd0(*(int*) (*(char**) p + 0x5d), 2, 0, 0x2a, 6);
			if (q != 0) {
				*(int*) (p + 4) = (int) fcn_00502cd0(*(int*) (q + 0x14), 1, 0, 0x179);
				*(int*) (p + 8) = (int) fcn_00502cd0(*(int*) (q + 0x14), 1, 0, 0x17a);
			}
			i++;
			p += 0xc;
		} while ((*(int*) p = (int) gm_FindNextFilteredEntity()) != 0);
	}
	if (*(int*) (action + 0x70) != 0) {
		return;
	}
	i = *(int*) (action + 0xac);
	end = i + 0x180;
	for (; i < end; i++) {
		if (fcn_00555490((short*) ((char *)&((ENTITY_RECORD*)g_7f4ca0)[i]), (int*) ent, &idx) != 0) {
			x1 = (int) (fcn_0050bb50(0x179, g_773d75) * g_662a08);
			y1 = (int) (fcn_0050bb50(0x17a, g_773d75) * g_662a08);
			v = gm_RandomMod(4) + 3;
			w = gm_AccumulateTyped2((int) ((char *)&((ENTITY_RECORD*)g_7f4ca0)[i]));
			mx = x1;
			if (x1 <= y1) {
				mx = y1;
			}
			if ((float) w > (float) mx * g_665e9c && ent[idx].p4 != 0 && ent[idx].p8 != 0) {
				if ((unsigned short) gm_RandomMod(2) != 0) {
					fcn_004c4eb0((unsigned int) g_6a5e88);
					fcn_004c51f0(-1, *(int*) (ent[idx].p4 + 6), 0x179, 1, g_773d75, 0);
					fcn_004c51a0(-1, *(unsigned int*) ((char *)&((ENTITY_RECORD*)g_7f4ca0)[i] + 4), g_773d75, (int) ((float) x1 * g_665e9c));
					fcn_004c51a0(*(unsigned int*) ((char *)&((ENTITY_RECORD*)g_7f4ca0)[*(unsigned short*) (ent[idx].p0 + 0x27)] + 4), -1, g_773d75, x1);
					cm_BeginPacketFieldDelta((int) ent[idx].p0, *(int*) (ent[idx].p0 + 1));
					fcn_004c4670(4, 1, (int) *(unsigned short*) ent[idx].p0 - g_aed32c + 0x65, &x1);
					fcn_004c4670(2, 1, (int) *(unsigned short*) ent[idx].p0 - g_aed32c + 0x6b, &v);
					fcn_004c5360();
					fcn_004c4ef0((unsigned int) g_6a5e88);
					cm_BeginPacketFieldDelta((int) ent[idx].p0, *(int*) (ent[idx].p0 + 1));
					fcn_004c4670(2, 1, (int) *(unsigned short*) ent[idx].p0 - g_aed32c + 0x69, &v);
					fcn_004c5360();
				} else {
					fcn_004c4eb0((unsigned int) g_6a5e88);
					fcn_004c51f0(-1, *(int*) (ent[idx].p8 + 6), 0x17a, 1, g_773d75, 0);
					fcn_004c51a0(-1, *(unsigned int*) ((char *)&((ENTITY_RECORD*)g_7f4ca0)[i] + 4), g_773d75, (int) ((float) y1 * g_665e9c));
					fcn_004c51a0(*(unsigned int*) ((char *)&((ENTITY_RECORD*)g_7f4ca0)[*(unsigned short*) (ent[idx].p0 + 0x27)] + 4), -1, g_773d75, y1);
					cm_BeginPacketFieldDelta((int) ent[idx].p0, *(int*) (ent[idx].p0 + 1));
					fcn_004c4670(4, 1, (int) *(unsigned short*) ent[idx].p0 - g_aed32c + 0x65, &y1);
					fcn_004c4670(2, 1, (int) *(unsigned short*) ent[idx].p0 - g_aed32c + 0x6b, &v);
					fcn_004c5360();
					fcn_004c4ef0((unsigned int) g_6a5e88);
					cm_BeginPacketFieldDelta((int) ent[idx].p0, *(int*) (ent[idx].p0 + 1));
					fcn_004c4670(2, 1, (int) *(unsigned short*) ent[idx].p0 - g_aed32c + 0x69, &v);
					fcn_004c5360();
				}
			} else if (w > x1 && ent[idx].p4 != 0) {
				fcn_004c4eb0((unsigned int) g_6a5e88);
				fcn_004c51f0(-1, *(int*) (ent[idx].p4 + 6), 0x179, 1, g_773d75, 0);
				fcn_004c51a0(-1, *(unsigned int*) ((char *)&((ENTITY_RECORD*)g_7f4ca0)[i] + 4), g_773d75, (int) ((float) x1 * g_665e9c));
				fcn_004c51a0(*(unsigned int*) ((char *)&((ENTITY_RECORD*)g_7f4ca0)[*(unsigned short*) (ent[idx].p0 + 0x27)] + 4), -1, g_773d75, x1);
				cm_BeginPacketFieldDelta((int) ent[idx].p0, *(int*) (ent[idx].p0 + 1));
				fcn_004c4670(4, 1, (int) *(unsigned short*) ent[idx].p0 - g_aed32c + 0x65, &x1);
				fcn_004c4670(2, 1, (int) *(unsigned short*) ent[idx].p0 - g_aed32c + 0x6b, &v);
				fcn_004c5360();
				fcn_004c4ef0((unsigned int) g_6a5e88);
				cm_BeginPacketFieldDelta((int) ent[idx].p0, *(int*) (ent[idx].p0 + 1));
				fcn_004c4670(2, 1, (int) *(unsigned short*) ent[idx].p0 - g_aed32c + 0x69, &v);
				fcn_004c5360();
			} else if (w > y1) {
				if (ent[idx].p8 != 0) {
					fcn_004c4eb0((unsigned int) g_6a5e88);
					fcn_004c51f0(-1, *(int*) (ent[idx].p8 + 6), 0x17a, 1, g_773d75, 0);
					fcn_004c51a0(-1, *(unsigned int*) ((char *)&((ENTITY_RECORD*)g_7f4ca0)[i] + 4), g_773d75, (int) ((float) y1 * g_665e9c));
					fcn_004c51a0(*(unsigned int*) ((char *)&((ENTITY_RECORD*)g_7f4ca0)[*(unsigned short*) (ent[idx].p0 + 0x27)] + 4), -1, g_773d75, y1);
					cm_BeginPacketFieldDelta((int) ent[idx].p0, *(int*) (ent[idx].p0 + 1));
					fcn_004c4670(4, 1, (int) *(unsigned short*) ent[idx].p0 - g_aed32c + 0x65, &y1);
					fcn_004c4670(2, 1, (int) *(unsigned short*) ent[idx].p0 - g_aed32c + 0x6b, &v);
					fcn_004c5360();
					fcn_004c4ef0((unsigned int) g_6a5e88);
					cm_BeginPacketFieldDelta((int) ent[idx].p0, *(int*) (ent[idx].p0 + 1));
					fcn_004c4670(2, 1, (int) *(unsigned short*) ent[idx].p0 - g_aed32c + 0x69, &v);
					fcn_004c5360();
				} else if (w > x1) {
					cm_BeginPacketFieldDelta((int) ent[idx].p0, *(int*) (ent[idx].p0 + 1));
					fcn_004c4670(2, 1, (int) *(unsigned short*) ent[idx].p0 - g_aed32c + 0x69, &v);
					fcn_004c5360();
				}
			}
		}
	}
	*(int*) (action + 0xac) = end;
	if (end >= 0x300) {
		*(int*) (action + 0xac) = 0;
		*(int*) (action + 0xb0) = 0;
		*(int*) (action + 0x52) = *(int*) (action + 0x52) + 1;
		*(unsigned short*) (action + 0x56) = 0x16;
		*(int*) (action + 0x58) = 0x1e;
		return;
	}
	gm_AddTime((int*) (action + 0x52), 0, 0xf, 0);
}
