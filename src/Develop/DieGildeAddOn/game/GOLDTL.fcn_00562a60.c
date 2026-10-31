


// SIZE 0x21c
struct house {
	char pad0[0x21c];
};

// SIZE 0x8
typedef struct F8 {
	int mask;
	int b;
} F8;

#include "client_types.h"
extern pos14_7f4c00 g_7f4c00;
extern char g_7f4ca0[];
extern __int64 g_666018;

char* __cdecl gm_LookupEntityRecordById(int);
char* __cdecl gm_StartFilteredEntitySearch(int, int, int);
int __cdecl fcn_004c64b0(int, int, int, int, int, int, char*);
int __cdecl fcn_004a5e60(struct house* p, int kind, F8 f, int c, float r, int* out);

void __cdecl fcn_00562a60(char* e)
{
	char* h;
	char* t;
	int found;

	gm_LookupEntityRecordById(*(int*) (e + 0xb4));
	*(pos14_7f4c00*) (e + 0x52) = g_7f4c00;
	if (*(int*) (e + 0x10) == -1) {
		t = gm_StartFilteredEntitySearch(1, 5, 0x16);
		if (t != 0 || (t = gm_StartFilteredEntitySearch(1, 5, 0xf)) != 0) {
			*(int*) (e + 0x10) = *(int*) (t + 1);
		}
	}
	*(int*) (e + 0xc8) = -1;
	*(int*) (e + 0xcc) = fcn_004c64b0(0x11, *(int*) (e + 0x10), -1, 0, 2, 0x154, "PRUEGEL");
	h = gm_LookupEntityRecordById(*(int*) (e + 0xb4));
	if (*(char**) (h + 0x170) != 0) {
		t = *(char**) (h + 0x170);
	} else {
		t = gm_StartFilteredEntitySearch(1, 4, *(unsigned short*) h);
	}
	if (t == 0) {
		if (fcn_004a5e60(&((struct house*)g_7f4ca0)[*(unsigned short*) (e + 8)], 6, (*(F8*)&g_666018), 0, 100.0f, &found) != 0) {
			t = gm_StartFilteredEntitySearch(1, 1, found);
		}
	}
	*(int*) (e + 0xd0) = *(int*) (t + 1);
}
