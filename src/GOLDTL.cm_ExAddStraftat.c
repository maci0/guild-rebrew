#include <stdio.h>
#include <string.h>

extern int g_14cbca0;
extern int g_773d38;
extern char g_9a3800[];
extern char g_7f4ca0[];

void __cdecl srv_SeedRandom(int);
void __cdecl fcn_004b4650(char*, int);
int __cdecl fcn_004f5770(int, int);
int __cdecl fcn_004f57e0(void);
void __cdecl fcn_004fa850(int, char, unsigned int*, unsigned int*);
void __cdecl fcn_004faa90(unsigned int, unsigned int, unsigned int*);
int __cdecl fcn_005015e0(char**, int, int, int);
int __cdecl fcn_00508e40(int);
int __cdecl fcn_005463a0(int, int, int);
int __cdecl fcn_005462a0(void);
void __cdecl fcn_005b2740(char*, char*);

/* ADDRESS: GOLDTL 0x004c9a10 */

/* Copies the crime description of a source record into the crime table,
 * resolves the offender, reports the new entry and walks the entity list
 * that belongs to the case. */
int __cdecl cm_ExAddStraftat(char* src, char* out)
{
	int* rec;
	unsigned int v13;
	unsigned int v14;
	char* p;
	char* ent;
	struct { unsigned int a; unsigned int b; unsigned int c; } v16;
	char msg[0x200];
	int taeter;
	int idx;
	unsigned short slot;

	if (g_14cbca0 != -1) {
		g_773d38 = *(int*) (src + 0x10);
	} else {
		g_773d38 = g_773d38 + 1;
	}
	idx = fcn_004f57e0();
	if (idx == -1) {
		return -1;
	}
	ent = (char*) fcn_00508e40(*(int*) (src + 0x26));
	if (ent != 0 && *(char*) (ent + 2) == 6) {
		fcn_004b4650(ent, 0x17);
	}
	rec = (int*) (g_9a3800 + idx * 0x2d);
	memcpy(rec, src + 0x10, 0x2d);
	*rec = g_773d38;
	sprintf(msg, "cm_ExAddStraftat(): Executed---- st_id = %i, taeter = %i, opfer = %i",
		g_773d38, *(int*) (src + 0x26), *(int*) (src + 0x22));
	taeter = *(int*) (src + 0x31);
	if (taeter == -1) {
		ent = (char*) fcn_00508e40(*(int*) (src + 0x22));
		if (ent != 0) {
			if (*(int*) (ent + 0x170) != 0) {
				taeter = *(int*) (*(char**) (ent + 0x170) + 1);
			} else if (*(int*) (ent + 0x16c) != 0) {
				taeter = *(int*) (*(char**) (ent + 0x16c) + 1);
			} else {
				srv_SeedRandom(*(int*) (src + 0x39));
			}
		} else {
			srv_SeedRandom(*(int*) (src + 0x39));
		}
	}
	fcn_004fa850(taeter, *(char*) (src + 0x2c), &v14, &v13);
	fcn_005015e0(&p, 0, 0, taeter);
	if (p != 0) {
		if (*(int*) (p + 0x61) != 0) {
			v16.a = *(unsigned int*) (*(char**) (p + 0x61) + 0x4c);
			v16.b = *(unsigned int*) (*(char**) (p + 0x61) + 0x50);
			v16.c = *(unsigned int*) (*(char**) (p + 0x61) + 0x54);
		}
	} else {
		fcn_004faa90(v14, v13, &v16);
	}
	for (ent = (char*) fcn_005463a0(1, 0, 0x18); ent != 0;
		ent = (char*) fcn_005462a0()) {
		if (*(int*) (ent + 0xc4) != *(int*) ((char*) rec + 0x16)) {
			continue;
		}
		slot = *(unsigned short*) (ent + 8);
		if (fcn_004f5770(*rec, *(int*) (g_7f4ca0 + slot * 0x21c + 4)) == 0) {
			break;
		}
		if (out != 0) {
			char* px;

			px = (char*) fcn_00508e40(*(int*) (ent + 0xc4));
			if (px != 0) {
				fcn_005b2740(px, g_7f4ca0 + slot * 0x21c);
			}
		}
	}
	if (out != 0) {
		out[0] = 1;
		out[1] = 6;
		*(int**) (out + 6) = rec;
	}
	return 0;
}
