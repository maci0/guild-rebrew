#include "client_types.h"

extern pos14_7f4c00 g_7f4c00;

char* __cdecl fcn_00508e40(int id);
void __cdecl fcn_00529160(int, int, int, char*);
int __cdecl fcn_00529670(char*, char*);
void __cdecl fcn_00546190(char* unit);
int __cdecl gm_ResolveEntityById(void**, void**, void**, int);
unsigned short* __cdecl gm_SetupEntityQuery(unsigned char*);
void __cdecl fcn_004c5c80(int);
int __cdecl fcn_004c5da0(int, int, int, char*, int, char*);
void __cdecl fcn_004c5ed0(int, char*, int);
void __cdecl fcn_00500bb0(void*, int, int, int);
void __cdecl fcn_0057ceb0(char* entity);
int __cdecl fcn_0057d7e0(char* e);
void __cdecl fcn_0057d830(char* u, int count);
int __cdecl gm_RandomMod(int);

/* ADDRESS: GOLDTL 0x0057d0d0 */
void __cdecl fcn_0057d0d0(char* entity)
{
	int found;
	int mode;
	int flag;
	int objs[4];
	int i;
	int n;
	int k;
	int v;
	char* o;
	char* q;

	int* ids;

	n = 0;
	objs[0] = 0;
	objs[1] = 0;
	objs[2] = 0;
	objs[3] = 0;
	found = 0;
	ids = (int*) (entity + 0x8c);
	i = 4;
	do {
		v = *ids;
		if (v != -1) {
			o = fcn_00508e40(v);
			if (o != 0) {
				objs[n] = (int) o;
				n++;
			}
		}
		ids++;
		i--;
	} while (i != 0);
	v = *(int*) (entity + 0x70);
	if (v == -1 || v == -2 || n == 0) {
		for (i = 0; i < n; i++) {
			fcn_00529160(0, 0, *(unsigned short*) objs[i], 0);
		}
		fcn_00546190(entity);
		return;
	}
	if (v != 0) {
		gm_ResolveEntityById((void**) &found, 0, 0, *(int*) (entity + 0xd0));
		if (found == 0) {
			*(int*) (entity + 0x70) = -1;
			*(pos14_7f4c00*) (entity + 0x52) = g_7f4c00;
			return;
		}
		if (*(int*) (entity + 0x70) == 1) {
			char anim[10][64] = {
				"zirkus/anfeuern",
				"zirkus/handstand",
				"zirkus/handstand2",
				"zirkus/lachen",
				"zirkus/lang_winken",
				"zirkus/posieren",
				"zirkus/ruecksalto",
				"zirkus/ruecksalto2",
				"zirkus/stehend_beschwoeren",
				"zirkus/tief_verbeugen"
			};

			for (i = 0; i < n; i++) {
				if (fcn_00529670((char*) objs[i], (char*) found) == 0) {
					*(int*) (entity + 0x70) = 1;
					*(pos14_7f4c00*) (entity + 0x52) = g_7f4c00;
					fcn_00500bb0(entity + 0x52, 0, 5, 0);
					return;
				}
			}
			if (*(int*) (entity + 0xb0) <= 0) {
				for (i = 0; i < n; i++) {
					fcn_00529160(0, 0, *(unsigned short*) objs[i], 0);
				}
				fcn_0057ceb0(entity);
				*(int*) (entity + 0x70) = -1;
				*(pos14_7f4c00*) (entity + 0x52) = g_7f4c00;
				return;
			}
			*(pos14_7f4c00*) (entity + 0x52) = g_7f4c00;
			fcn_00500bb0(entity + 0x52, 2, 0, 0);
			*(int*) (entity + 0x70) = 2;
			for (i = 0; i < n; i++) {
				o = (char*) objs[i];
				if (*(int*) (o + 0x184) != 0) {
					k = 8;
					do {
						fcn_004c5ed0(*(int*) (o + 4),
						    anim[gm_RandomMod(10) & 0xffff],
						    (gm_RandomMod(2) & 0xffff) + 1);
						k--;
					} while (k != 0);
				}
			}
			return;
		}
		if (*(int*) (entity + 0x70) == 2) {
			for (i = 0; i < n; i++) {
				fcn_004c5c80(*(int*) (objs[i] + 4));
			}
			fcn_0057d830(entity, n);
			*(int*) (entity + 0xb0) = *(int*) (entity + 0xb0) - 0x78;
			*(pos14_7f4c00*) (entity + 0x52) = g_7f4c00;
			*(int*) (entity + 0x70) = 0;
		}
		return;
	}
	mode = -1;
	if (*(int*) (entity + 0xb0) > 0) {
		found = fcn_0057d7e0(entity);
		flag = 1;
		*(int*) (entity + 0xbc) = *(int*) (entity + 0xbc) + 1;
	}
	else {
		gm_ResolveEntityById((void**) &found, 0, 0, *(int*) (entity + 0x10));
		flag = 0;
		if (found != 0) {
			q = (char*) gm_SetupEntityQuery((unsigned char*) found);
			if (q != 0) {
				mode = *(int*) (q + 2);
			}
		}
	}
	if (found == 0) {
		*(int*) (entity + 0x70) = -1;
		*(pos14_7f4c00*) (entity + 0x52) = g_7f4c00;
		return;
	}
	*(int*) (entity + 0xd0) = *(int*) (found + 1);
	for (i = 0; i < n; i++) {
		o = (char*) objs[i];
		fcn_00529160(0, 0, *(unsigned short*) o, entity);
		fcn_004c5c80(*(int*) (o + 4));
		fcn_004c5da0(*(int*) (o + 4), *(int*) (found + 1), mode, 0, flag, "Bettler");
	}
	*(int*) (entity + 0x70) = 1;
	*(pos14_7f4c00*) (entity + 0x52) = g_7f4c00;
	fcn_00500bb0(entity + 0x52, 0, 10, 0);
}
