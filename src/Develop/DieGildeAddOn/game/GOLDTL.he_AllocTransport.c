#include <stdio.h>
#include <math.h>

extern char* g_entity_type_table;

unsigned short* __cdecl gm_StartFilteredEntitySearch(int, ...);
char* __cdecl gm_FindNextFilteredEntity(void);
int __cdecl gm_ResolveEntityById(void**, void**, void**, int);
int __cdecl gm_CheckEntityType(unsigned char*);
char* __cdecl gm_SearchTable67(int);
int __cdecl gm_RandomMod(int);
void __cdecl fcn_00500bb0(int*, int, int, int);
void __cdecl fcn_00455350(char*, char*, float*);
void __cdecl fcn_00546190(char*);
char* __cdecl fcn_005463a0(int, int, int);
void __cdecl fcn_004c51a0(int, int, char, int);
void __cdecl fcn_004c5420(int, int, int, int, int);
int __cdecl fcn_0050c710(unsigned char*, int, int);
int __cdecl fcn_0050ddf0(int, int);
int __cdecl fcn_0050de80(char*, void*);
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
void __cdecl he_AllocTransport(char* a0)
{
	char* query;
	char* second;
	char* best;
	char* p;
	char* rec;
	char* node;
	char buf[176];
	int len;
	char nbuf[240];
	float f;
	float fbest;
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
	*(int*) (a0 + 0xe8) = -1;
	*(int*) (a0 + 0xd4) = 0;
	*(Span14*) (a0 + 0x52) = *(Span14*) (a0 + 0x44);
	*(char*) (a0 + 0xd0) = 0;
	*(Span14*) (a0 + 0x60) = *(Span14*) (a0 + 0x44);

	first = (char*) gm_StartFilteredEntitySearch(1, 1, *(int*) (a0 + 0xb0));
	if (first == 0) {
		goto done;
	}
	gm_ResolveEntityById(0, (void**) &query, 0, *(int*) (a0 + 0xac));
	if (query == 0) {
		goto done;
	}
	second = (char*) gm_StartFilteredEntitySearch(1, 1, *(int*) (a0 + 0xb4));
	if (second == 0) {
		goto done;
	}

	idx = *(unsigned char*) second;
	if (g_entity_type_table[idx * 0x24d] == '\n' && query != 0 &&
	    (*(unsigned char*) (query + 0x20) & 1) != 0) {
		fbest = 1e8f;
		fcn_00455350((char*) *(int*) (first + 0x61),
		             (char*) (*(int*) (first + 0x61) + 0x4c), pold);
		best = second;
		p = (char*) gm_StartFilteredEntitySearch(1, 5, 10);
		if (p != 0) {
			do {
				fcn_00455350((char*) *(int*) (p + 0x61),
				             (char*) (*(int*) (p + 0x61) + 0x4c), pnew);
				f = (float) ((pnew[0] - pold[0]) * (pnew[0] - pold[0]) +
				             (pnew[1] - pold[1]) * (pnew[1] - pold[1]) +
				             (pnew[2] - pold[2]) * (pnew[2] - pold[2]));
				f = (float) sqrt(f);
				if (f < fbest) {
					best = p;
					fbest = f;
				}
				p = gm_FindNextFilteredEntity();
			} while (p != 0);
			if (best != second) {
				type = *(int*) (a0 + 0xf4);
				if (type != 0 && type != -1) {
					rec = fcn_005463a0(1, 1, type);
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
				*(int*) (a0 + 0xb4) = *(int*) (best + 1);
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
			*(int*) (a0 + 0xc8) = 4;
			if (first == second) {
				ReportClientMessage((char*) 0x6a62dc);
				fcn_00546190(a0);
				return;
			}
		} else {
			*(int*) (a0 + 0xc8) = 2;
		}
	} else if (found_second) {
		*(int*) (a0 + 0xc8) = 1;
	} else {
		*(int*) (a0 + 0xc8) = 3;
	}

	*(int*) (a0 + 0xb8) = *(int*) (second + 0x30) + *(int*) (first + 0x30);
	*(int*) (a0 + 0xc4) = *(int*) (first + 1);
	*(char*) (a0 + 0xd0) = 0;
	fcn_00500bb0((int*) (a0 + 0x52), 0, 0, 1);

	if (query == 0) {
		goto done;
	}
	rec = gm_SearchTable67(*(int*) (query + 0x1c));
	idx = *(unsigned char*) (query + 0x12);
	node = *(char**) (query + 0x3b);
	f = (float) ((float) idx * *(float*) 0x662910 * *(double*) 0x662908 +
	             *(double*) 0x664128);
	*(float*) (node + 0x1a0) = f;
	if (*(short*) query == 0x136) {
		*(float*) (node + 0x1a0) = (float) (f - *(double*) 0x662b20);
	} else if (*(short*) query == 0x135) {
		*(float*) (node + 0x1a0) = (float) (f + *(double*) 0x664e60);
	}
	if (rec != 0) {
		v = fcn_0050c710((unsigned char*) rec, 0x11, 1);
		f = (float) ((double) v * *(double*) 0x6640e8 + *(double*) 0x6629c8) *
		    *(float*) (node + 0x1a0);
		*(float*) (node + 0x1a0) = f;
		*(float*) (a0 + 0xc0) = f;
	}
	*(unsigned char*) (query + 0x13) = *(unsigned char*) (query + 0x13) | 0x40;
	if ((*(unsigned char*) (a0 + 0x78) & 2) != 0) {
		fcn_004c5420(*(int*) (query + 2), 0x13, 1, 0x40, 0);
	}
	*(int*) (query + 0x24) = (int) a0;
	*(int*) (a0 + 0x10) = *(int*) (query + 2);

	if ((*(unsigned char*) (query + 0x20) & 1) != 0) {
		fcn_0050de80(query, buf);
		if (len > 0) {
			*(int*) (a0 + 0xcc) = len / 16000 + (unsigned short) gm_RandomMod(2);
		} else {
			*(int*) (a0 + 0xcc) = 0;
		}
		if (*(int*) (a0 + 0xcc) > 2) {
			*(int*) (a0 + 0xcc) = 2;
		}
		if (*(int*) (a0 + 0xcc) != 0) {
			sprintf(nbuf, (char*) 0x6a62a8, *(int*) (a0 + 0xcc));
			*(char*) (query + 0x28) = *(char*) (a0 + 0xcc);
			v = fcn_0050ddf0(len, (int) *(char*) (query + 0x28));
			if ((*(unsigned char*) (a0 + 0x78) & 2) != 0) {
				fcn_004c51a0(-1, *(int*) ((char*) 0x7f4ca4 +
				              *(unsigned short*) (a0 + 8) * 135),
				             *(char*) 0x773d75, v);
				*(int*) (a0 + 0x84) = -1;
				*(int*) (a0 + 0xec) = -1;
				return;
			}
		} else {
			*(char*) (query + 0x28) = 0;
		}
	}

	*(int*) (a0 + 0x84) = -1;
	*(int*) (a0 + 0xec) = -1;
	return;

done:
	fcn_00546190(a0);
}
