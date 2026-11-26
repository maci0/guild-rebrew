#include <stdio.h>
#include <math.h>
#include "Develop/DieGildeAddOn/game/building_prototype.h"
extern char* lpGebaeudePROT;

typedef struct TransportBuildingRow {
	unsigned char kind;
	char fields[0x24c];
} TransportBuildingRow;

typedef struct TransportStats {
	char fields[0xb0];
	int total;
	char* list;
} TransportStats;

unsigned short* __cdecl gm_StartFilteredEntitySearch(int, ...);
char* __cdecl gm_FindNextFilteredEntity(void);
int __cdecl gm_ResolveEntityById(void**, void**, void**, int);
int __cdecl gm_CheckEntityType(unsigned char*);
char* __cdecl gm_SearchTable67(int);
unsigned short __cdecl gm_RandomMod(unsigned short);
void __cdecl gm_AddTime(int*, int, int, int);
void __cdecl d3_TransformPoint(char*, char*, float*);
void __cdecl he_FreeAction(char*);
char* __cdecl he_StartHandlungSearch(int, int, int);
void __cdecl fcn_004c51a0(int, int, char, int);
void __cdecl fcn_004c5420(int, int, int, int, int);
int __cdecl gm_GetBuildingTechEffect(unsigned char*, int, int);
int __cdecl fcn_0050ddf0(int, int);
int __cdecl gm_CalcEntityInventoryStats(char*, void*);
void __cdecl ReportClientMessage(const char*);

#pragma pack(1)
typedef struct Span14 {
	int x;
	int y;
	int z;
	unsigned short w;
} Span14;
#pragma pack()

/* ADDRESS: GOLDTL 0x0055d0d0 */
void __cdecl he_AllocTransport(char* action)
{
	char* query;
	char* second;
	char* best;
	char* p;
	char* rec;
	char* node;
	TransportStats stats;
	char nbuf[256];
	float f;
	double base_speed;
	float fbest;
	double distance, dx, dy, dz;
	float pnew[4];
	float pold[4];
	int found_first;
	char* first;
	int found_second;
	int i;
	int type;
	int v;
	int idx;

	found_first = 0;
	found_second = 0;
	*(int*) (action + 0xe8) = -1;
	*(int*) (action + 0xd4) = 0;
	*(Span14*) (action + 0x52) = *(Span14*) (action + 0x44);
	*(char*) (action + 0xd0) = 0;
	*(Span14*) (action + 0x60) = *(Span14*) (action + 0x44);

	first = (char*) gm_StartFilteredEntitySearch(1, 1, *(int*) (action + 0xb0));
	if (first == 0) {
		goto done;
	}
	gm_ResolveEntityById(0, (void**) &query, 0, *(int*) (action + 0xac));
	if (query == 0) {
		goto done;
	}
	second = (char*) gm_StartFilteredEntitySearch(1, 1, *(int*) (action + 0xb4));
	if (second == 0) {
		goto done;
	}

	idx = *(unsigned char*) second;
	if (((BUILDING_PROTOTYPE *)lpGebaeudePROT)[idx].category == 10 && query != 0 &&
	    (*(unsigned char*) (query + 0x20) & 1) != 0) {
		best = second;
		fbest = 1e8f;
		d3_TransformPoint((char*) *(int*) (first + 0x61),
		             (char*) (*(int*) (first + 0x61) + 0x4c), pold);
		p = (char*) gm_StartFilteredEntitySearch(1, 5, 10);
		if (p != 0) {
			do {
				d3_TransformPoint((char*) *(int*) (p + 0x61),
				             (char*) (*(int*) (p + 0x61) + 0x4c), pnew);
				dx = (double) pnew[0] - pold[0];
				dy = (double) pnew[1] - pold[1];
				dz = (double) pnew[2] - pold[2];
				distance = sqrt(dz * dz + dy * dy + dx * dx);
				if (distance < fbest) {
					best = p;
					fbest = (float) distance;
				}
				p = gm_FindNextFilteredEntity();
			} while (p != 0);
			if (best != second) {
				type = *(int*) (action + 0xf4);
				if (type != 0 && type != -1) {
					rec = he_StartHandlungSearch(1, 1, type);
					if (rec != 0) {
						for (i = 0; i < 3; i++) {
							node = rec + 0xb8 + i * 4;
							if (*(int*) (node + 0xc) == *(int*) (second + 1)) {
								*(int*) (node + 0xc) = *(int*) (best + 1);
							}
							if (*(int*) node == *(int*) (second + 1)) {
								*(int*) node = *(int*) (best + 1);
							}
						}
						if (*(int*) (rec + 0xb0) == *(int*) (second + 1)) {
							*(int*) (rec + 0xb0) = *(int*) (best + 1);
						}
					}
				}
				*(int*) (action + 0xb4) = *(int*) (best + 1);
				second = best;
			}
		}
	}

	if (gm_CheckEntityType((unsigned char*) first) != 0) {
		found_first = 1;
	}
	if (gm_CheckEntityType((unsigned char*) second) != 0) {
		found_second = 1;
	}

	if (found_first) {
		if (found_second) {
			*(int*) (action + 0xc8) = 4;
			if (first == second) {
				ReportClientMessage((char*) 0x6a62dc);
				he_FreeAction(action);
				return;
			}
		} else {
			*(int*) (action + 0xc8) = 2;
		}
	} else if (found_second) {
		*(int*) (action + 0xc8) = 1;
	} else {
		*(int*) (action + 0xc8) = 3;
	}

	*(int*) (action + 0xb8) = *(int*) (second + 0x30) + *(int*) (first + 0x30);
	*(int*) (action + 0xc4) = *(int*) (first + 1);
	*(char*) (action + 0xd0) = 0;
	gm_AddTime((int*) (action + 0x52), 0, 0, 1);

	if (query == 0) {
		goto done;
	}
	rec = gm_SearchTable67(*(int*) (query + 0x1c));
	idx = *(unsigned char*) (query + 0x12);
	node = *(char**) (query + 0x3b);
	base_speed = (double) idx * *(float*) 0x662910 * *(double*) 0x662908 +
	             *(double*) 0x664128;
	f = (float) base_speed;
	*(float*) (node + 0x1a0) = f;
	if (*(short*) query == 0x136) {
		*(float*) (node + 0x1a0) = (float) (base_speed - *(double*) 0x662b20);
	} else if (*(short*) query == 0x135) {
		*(float*) (node + 0x1a0) = (float) (base_speed + *(double*) 0x664e60);
	}
	if (rec != 0) {
		v = gm_GetBuildingTechEffect((unsigned char*) rec, 0x11, 1);
		f = (float) (((double) v * *(double*) 0x6640e8 + *(double*) 0x6629c8) *
		    *(float*) (node + 0x1a0));
		*(float*) (node + 0x1a0) = f;
		*(float*) (action + 0xc0) = f;
	}
	*(unsigned char*) (query + 0x13) = *(unsigned char*) (query + 0x13) | 0x40;
	if ((*(unsigned char*) (action + 0x78) & 2) != 0) {
		fcn_004c5420(*(int*) (query + 2), 0x13, 1, 0x40, 0);
	}
	*(int*) (query + 0x24) = (int) action;
	*(int*) (action + 0x10) = *(int*) (query + 2);

	if ((*(unsigned char*) (query + 0x20) & 1) != 0) {
		gm_CalcEntityInventoryStats(query, &stats);
		if (stats.total > 0) {
			*(int*) (action + 0xcc) = stats.total / 16000 + (unsigned short) gm_RandomMod(2);
		} else {
			*(int*) (action + 0xcc) = 0;
		}
		if (*(int*) (action + 0xcc) > 2) {
			*(int*) (action + 0xcc) = 2;
		}
		if (*(int*) (action + 0xcc) != 0) {
			sprintf(nbuf, (char*) 0x6a62a8, *(int*) (action + 0xcc));
			*(char*) (query + 0x28) = *(char*) (action + 0xcc);
			v = fcn_0050ddf0(stats.total, (int) *(char*) (query + 0x28));
			if ((*(unsigned char*) (action + 0x78) & 2) != 0) {
				fcn_004c51a0(-1, *(int*) ((char*) 0x7f4ca4 +
				              *(unsigned short*) (action + 8) * 0x21c),
				             *(char*) 0x773d75, v);
				*(int*) (action + 0x84) = -1;
				*(int*) (action + 0xec) = -1;
				return;
			}
		} else {
			*(char*) (query + 0x28) = 0;
		}
	}

	*(int*) (action + 0x84) = -1;
	*(int*) (action + 0xec) = -1;
	return;

done:
	he_FreeAction(action);
}
