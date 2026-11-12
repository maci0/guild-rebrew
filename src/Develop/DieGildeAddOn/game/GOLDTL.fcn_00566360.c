#include <string.h>

extern int g_6b8010;
extern char g_6b5c60[];

int __cdecl fcn_004c4450(int);
char* __cdecl gm_LookupEntityRecordById(int);
char* __cdecl gm_SearchTable67(int);
int __cdecl fcn_00507870(char*);
int __cdecl fcn_004c5620(int, char*);
int __cdecl fcn_00426cc0(int);
void __cdecl fcn_00428720(int);
int __cdecl fcn_00413190(int);
void __cdecl fcn_004432d0(int, int);
void __cdecl fcn_004030e0(char*);
char* __cdecl fcn_004fe2e0(char*, int, float*, float*, int, int);
void __cdecl fcn_00407800(int, int, char*);
char* __cdecl evt_LoadGfxScript(char*);
void __cdecl fcn_00428340(char*, int, ...);
void __cdecl fcn_004c5420(int, int, int, int, int);
void __cdecl fcn_00546190(char*);

/* ADDRESS: GOLDTL 0x00566360 */
void __cdecl fcn_00566360(char* a0)
{
	int v3;
	int v15;
	int v6;
	float pos[4];
	float rot[4];
	int v7;
	char name[0x80];
	char* o;
	char* ent;
	char* handle;
	char* p;
	int v30;

	o = a0;
	if (*(int*) (o + 0x84) != -1) {
		if (!fcn_004c4450(*(int*) (o + 0x84))) {
			return;
		}
	}
	ent = gm_LookupEntityRecordById(*(unsigned int*) (o + 0xac));
	if (ent == 0) {
		fcn_00546190(o);
		return;
	}
	if (*(int*) (ent + 0x184) != 0) {
		p = gm_SearchTable67(*(unsigned int*) (o + 0x10));
		if (p != 0 && *(int*) (*(int*) (ent + 0x184) + 0x2c) != *(int*) (p + 1)) {
			return;
		}
	}

	switch (*(int*) (o + 0x70)) {
	case 0:
		if ((unsigned char) o[0x78] & 2) {
			*(int*) (o + 0xb0) = fcn_00507870(ent);
		}
		*(int*) (o + 0x70) = *(int*) (o + 0x70) + 1;
		return;
	case 1:
		if ((unsigned char) o[0x78] & 4) {
			return;
		}
		handle = (char*) *(int*) (o + 0xb0);
		if (handle != (char*) -1 && !fcn_004c4450((int) handle)) {
			return;
		}
		*(int*) (o + 0xb0) = -1;
		*(int*) (o + 0x84) = fcn_004c5620(2, o);
		return;
	case 2:
		if (*(int*) (ent + 0x184) == 0) {
			if ((unsigned char) o[0x78] & 2) {
				fcn_004c5420(*(unsigned int*) (ent + 4), 0x1cc, 4, 0, 0x1000000);
			}
			fcn_00546190(o);
			return;
		}
		handle = (char*) *(int*) (*(int*) (ent + 0x184) + 0x28);
		if (handle != (char*) -1) {
			fcn_00428720(fcn_00426cc0((int) handle));
		}
		*(int*) (o + 0x70) = *(int*) (o + 0x70) + 1;
		return;
	case 3:
		v6 = *(int*) (ent + 0x184);
		if (*(int*) (v6 + 0x28) != -1) {
			return;
		}
		if (v6 == 0) {
			if ((unsigned char) o[0x78] & 2) {
				fcn_004c5420(*(unsigned int*) (ent + 4), 0x1cc, 4, 0, 0x1000000);
			}
			fcn_00546190(o);
			return;
		}
		v15 = g_6b8010;
		v7 = fcn_00413190(*(unsigned int*) (v6 + 0x88));
		name[0] = g_6b5c60[0];
		memset(name + 1, 0, 0x7f);
		fcn_004432d0(v7, 1);
		v6 = *(int*) (ent + 0x184);
		pos[0] = *(float*) (*(int*) (v6 + 0x34) + 0x4c);
		pos[1] = *(float*) (*(int*) (v6 + 0x34) + 0x50);
		pos[2] = *(float*) (*(int*) (v6 + 0x34) + 0x54);
		rot[0] = *(float*) (*(int*) (v6 + 0x34) + 0x84);
		rot[1] = *(float*) (*(int*) (v6 + 0x34) + 0x88);
		rot[2] = *(float*) (*(int*) (v6 + 0x34) + 0x8c);
		v3 = *(int*) (v6 + 0x2c);
		v30 = *(int*) (v6 + 0x30);
		strcpy(name, (char*) (v6 + 0x1a8));
		fcn_004030e0((char*) v6);
		*(unsigned int*) (ent + 0x184) = 0;
		*(char*) (ent + 0x1f4) = 0;
		p = fcn_004fe2e0(ent, v7, pos, rot, 0, 0);
		*(char**) (ent + 0x184) = p;
		if (p != 0) {
			*(unsigned int*) (p + 0x2c) = v3;
			*(int*) (*(int*) (ent + 0x184) + 0x30) = v30;
			if (name[0]) {
				fcn_00407800(*(int*) (ent + 0x184), 2, name);
			}
			p = evt_LoadGfxScript((char*) 0x6a68bc);
			if (p != 0) {
				fcn_00428340(p, 5, (int) pos[0], (int) pos[1], (int) pos[2], 0x28, 0xb4);
				if (v30 != -1) {
					*(int*) (p + 0x104) = v30;
				} else {
					*(unsigned int*) (p + 0x104) = v3;
				}
				*(unsigned int*) (p + 0xc8c) = 1;
			}
		}
		fcn_004432d0(v15, 1);
		o = a0;
		if ((unsigned char) o[0x78] & 2) {
			fcn_004c5420(*(unsigned int*) (ent + 4), 0x1cc, 4, 0, 0x1000000);
		}
		fcn_00546190(o);
		return;
	case -2:
	case -1:
		if ((unsigned char) o[0x78] & 2) {
			fcn_004c5420(*(unsigned int*) (ent + 4), 0x1cc, 4, 0, 0x1000000);
		}
		fcn_00546190(o);
		return;
	default:
		return;
	}
}
