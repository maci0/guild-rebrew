#include <string.h>

// SIZE 0x190
typedef struct Figure {
	unsigned short id;
	char pad2[2];
	unsigned int seed;
	char pad8[0x184 - 8];
	char* model;
	char pad188[4];
	int icon;
} Figure;

// SIZE 0x44
typedef struct HeadSet {
	char pad0[4];
	char name[0x30];
	int head[4];
} HeadSet;

extern char g_10432c0;
extern int g_773d40;
extern char* g_773d44;

char* __cdecl fcn_0064d470(const char* s, const char* sub);
char* __cdecl fcn_0064d1a0(char* s, int c);
int __cdecl fcn_0064d41a(char* buf, const char* fmt, ...);
int __cdecl fcn_0065f220(const char* a, const char* b);
HeadSet* __cdecl fcn_004fda30(int id);

// FUNCTION: GOLDTL 0x004fdfe0
void __cdecl fcn_004fdfe0(Figure* f)
{
	char icon[0x80];
	int i;
	int j;
	int found;

	found = 0;
	if (f == 0) {
		return;
	}
	if (f->model != 0 && g_773d44 != 0) {
		int lod;
		char* o;
		char* lst;
		char* name;

		if (*(char**) (f->model + 0x88) == &g_10432c0) {
			return;
		}
		o = *(char**) (*(char**) (f->model + 0x34) + 0x1ec) + 0xf4;
		lst = *(char**) (o + 0x318);
		lod = *(unsigned char*) (o + 0x4a1);
		for (i = 0; i < *(int*) (lst + 0x1e4) && found == 0; i++) {
			name = *(char**) (lst + 0x200) + (*(int*) (lst + 0x1e4) * lod + i) * 0x40;
			if (*name == 0) {
				continue;
			}
			if (fcn_0064d470(name, "kopf") != 0 || fcn_0064d470(name, "KOPF") != 0 || fcn_0064d470(name, "HEAD") != 0
			    || fcn_0064d470(name, "head") != 0) {
				fcn_0064d41a(icon, "%s_ICON.bmp", name);
				for (j = 0; j < g_773d40; j++) {
					if (g_773d44[j * 0x30] == 0) {
						break;
					}
					if (fcn_0065f220(icon, &g_773d44[j * 0x30]) == 0) {
						found = 1;
						f->icon = j + 0x639;
						break;
					}
				}
			}
		}
		if (found != 0) {
			return;
		}
	} else {
		HeadSet* hs;
		int n;
		char base[0x80];
		char kind[0x80];
		char* p;
		int* slot;

		hs = fcn_004fda30(f->id);
		n = 0;
		if (hs->head[0] == 0xff) {
			strcpy(base, hs->name);
			p = fcn_0064d1a0(base, '_');
			if (p != 0) {
				strcpy(kind, p + 1);
				*p = 0;
			}
			slot = hs->head;
			for (i = 0; i < 4; i++, slot++) {
				*slot = 0;
				fcn_0064d41a(icon, "%s_HEAD%i_%s_ICON.bmp", base, i, kind);
				if (fcn_0064d470(base, "zigeunermeister") != 0) {
					fcn_0064d41a(icon, "%s_HEAD%i_ICON.bmp", base, i);
				}
				*slot = 0xff;
				for (j = 0; j < g_773d40; j++) {
					if (g_773d44[j * 0x30] == 0) {
						break;
					}
					if (fcn_0065f220(icon, &g_773d44[j * 0x30]) == 0) {
						*slot = j;
						break;
					}
				}
			}
		}
		for (; n < 4; n++) {
			if (hs->head[n] == 0xff) {
				break;
			}
		}
		if (n != 0) {
			f->icon = hs->head[f->seed % n] + 0x639;
			return;
		}
	}
	f->icon = 0x639;
}
