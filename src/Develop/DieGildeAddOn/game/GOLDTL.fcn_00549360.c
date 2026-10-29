


#include <string.h>

extern int g_6b8010;
extern int g_67a370;

char* __cdecl fcn_00508e40(int);
unsigned short __cdecl gm_RandomMod(int);
int __cdecl fcn_00406340(char* e, char* name, int param);
int __cdecl fcn_004bc8a0(int, int, float (*)[4]);
char __cdecl fcn_0045b990(int, float*, int*, int*, int*);
char* __cdecl fcn_0040c120(char*, int, int, int, int);

void __cdecl he_CharacterBehavior(char* u, int where)
{
	int* p;
	int n;
	int k;
	int a;
	int world;
	int b;
	int c;
	char* e;
	char* r;
	int i;
	float list[8][4];

	if (g_6b8010 != 0) {
		return;
	}
	p = (int*) (u + 0x8c);
	for (k = 8; k != 0; k--, p++) {
		if (*p == -1) {
			continue;
		}
		e = fcn_00508e40(*p);
		if (e == 0 || *(int*) (*(char**) (e + 0x184) + 0x128) != 0) {
			continue;
		}
		if (gm_RandomMod(100) > 40) {
			char g[3][0x20] = { "gestik/durch_haar_fahr", "gestik/kopf_kratzen", "gestik/mit_faust_droh" };

			fcn_00406340(*(char**) (e + 0x184), g[gm_RandomMod(3)], gm_RandomMod(3) + 1);
			fcn_00406340(*(char**) (e + 0x184), g[gm_RandomMod(3)], gm_RandomMod(3) + 1);
		} else {
			world = *(int*) (((char*)g_67a370) + 0xb0);
			n = gm_RandomMod(3) + 1;
			n = fcn_004bc8a0(where, n, list);
			for (i = 0; i < n; i++) {
				if (fcn_0045b990(world, list[i], &b, &a, &c) != 0) {
					r = fcn_0040c120(*(char**) (e + 0x184), 0x2d, b, a, 0);
					strcpy(r + 0x70, "he_CharacterBehavior");
				}
			}
		}
	}
}
