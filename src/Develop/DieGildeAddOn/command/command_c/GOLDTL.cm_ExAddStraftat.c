#include <stdio.h>
#include <string.h>

/* SIZE 0x2d */
typedef struct Straftat {
	int id;
	char pad04[0x12];
	int f16;
	char pad1a[0x13];
} Straftat;

/* SIZE 0xc */
typedef struct Area {
	unsigned int a;
	unsigned int b;
	unsigned int c;
	unsigned int d;
} Area;

extern int g_14cbca0;
extern int g_773d38;
extern char g_9a3800[];
extern char g_7f4ca0[];

void __cdecl srv_SeedRandom(int);
void __cdecl fcn_004b4650(char*, int);
int __cdecl gs_AddBeweis(int, int);
int __cdecl fcn_004f57e0(void);
void __cdecl fcn_004fa850(int, char, unsigned int*, unsigned int*);
void __cdecl fcn_004faa90(unsigned int, unsigned int, Area*);
int __cdecl gm_ResolveEntityById(char**, int, int, int);
int __cdecl gm_LookupEntityRecordById(int);
int __cdecl fcn_005463a0(int, int, int);
int __cdecl he_fn_Handlung(void);
void __cdecl fcn_005b2740(char*, char*);


/* Copies the crime description of a source record into the crime table,
 * resolves the offender, reports the new entry and walks the entity list
 * that belongs to the case. */
/* ADDRESS: GOLDTL 0x004c9a10 */
int __cdecl cm_ExAddStraftat(char* src, char* out)
{
	Straftat* rec;
	unsigned int v13;
	unsigned int v14;
	char* p;
	Straftat* ent;
	Area v16;
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
	ent = (Straftat*) gm_LookupEntityRecordById(*(int*) (src + 0x26));
	if (ent != 0 && *(char*) ((char*) ent + 2) == 6) {
		fcn_004b4650((char*) ent, 0x17);
	}
	rec = (Straftat*) (g_9a3800 + idx * 0x2d);
	memcpy(rec, src + 0x10, 0x2d);
	rec->id = g_773d38;
	sprintf(msg, "cm_ExAddStraftat(): Executed---- st_id = %i, taeter = %i, opfer = %i",
		g_773d38, *(int*) (src + 0x26), *(int*) (src + 0x22));
	taeter = *(int*) (src + 0x31);
	if (taeter == -1) {
		ent = (Straftat*) gm_LookupEntityRecordById(*(int*) (src + 0x22));
		if (ent != 0) {
			if (*(int*) ((char*) ent + 0x170) != 0) {
				taeter = *(int*) (*(char**) ((char*) ent + 0x170) + 1);
			} else if (*(int*) ((char*) ent + 0x16c) != 0) {
				taeter = *(int*) (*(char**) ((char*) ent + 0x16c) + 1);
			} else {
				srv_SeedRandom(*(int*) (src + 0x39));
			}
		} else {
			srv_SeedRandom(*(int*) (src + 0x39));
		}
	}
	fcn_004fa850(taeter, *(char*) (src + 0x2c), &v13, &v14);
	gm_ResolveEntityById(&p, 0, 0, taeter);
	if (p != 0) {
		if (*(int*) (p + 0x61) != 0) {
			v16.a = *(unsigned int*) (*(char**) (p + 0x61) + 0x4c);
			v16.b = *(unsigned int*) (*(char**) (p + 0x61) + 0x50);
			v16.c = *(unsigned int*) (*(char**) (p + 0x61) + 0x54);
		}
	} else {
		fcn_004faa90(v14, v13, &v16);
	}
	for (ent = (Straftat*) fcn_005463a0(1, 0, 0x18); ent != 0;
		ent = (Straftat*) he_fn_Handlung()) {
		if (*(int*) ((char*) ent + 0xc4) != *(int*) (g_9a3800 + idx * 0x2d + 0x16)) {
			continue;
		}
		slot = *(unsigned short*) ((char*) ent + 8);
		if (gs_AddBeweis(rec->id, *(int*) (g_7f4ca0 + slot * 0x21c + 4)) == 0) {
			break;
		}
		if (out != 0) {
			char* px;

			px = (char*) gm_LookupEntityRecordById(*(int*) ((char*) ent + 0xc4));
			if (px != 0) {
				fcn_005b2740(px, g_7f4ca0 + slot * 0x21c);
			}
		}
	}
	if (out != 0) {
		out[0] = 1;
		out[1] = 6;
		*(Straftat**) (out + 6) = rec;
	}
	return 0;
}
unsigned char _dpad_7731b8[2944];
