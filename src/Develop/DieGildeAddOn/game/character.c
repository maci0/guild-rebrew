void __cdecl fcn_00438b40(char*, int*);
void __cdecl fcn_004053a0(void*, int);
void __cdecl fcn_00403e20(void*, int);
void __cdecl fcn_004033e0(void*);
#ifdef REBREW_GOLD
void __cdecl fcn_00453270(char*);
#endif
#include <stdio.h>
#include <string.h>
#include "ch_motion.h"

#include "../../Units/d3/d3_object.h"

#ifdef REBREW_GOLD
#define fcn_00443900 fcn_00447fd0
#define fcn_00413190 fcn_00411be0
#define fcn_00402aa0 fcn_00402540
#define fcn_0040cfb0 fcn_0040c090
#endif

char __cdecl fcn_00443900(void*, void*, void*);
void __cdecl fcn_00438c40(void*, float*);
int __cdecl fcn_00413190(void*);
void __cdecl fcn_00402aa0(char*);
void __cdecl fcn_0040cfb0();
char* __cdecl fcn_0040c230(char*, void (__cdecl*)(), unsigned char, int, ...);
void __cdecl fcn_00425bf0(char*, int, const char*);

extern void* g_14d0020[];

void __cdecl ch_SetPosition(char* a1, float* a2, int flag)
{
	fcn_00438b40(*(char**) (a1 + 0x34), (int*) a2);
#ifdef REBREW_GOLD
	if (flag != 0) {
		fcn_00453270(*(char**) (a1 + 0x34));
	}
#endif
	fcn_004053a0(a1, 0);
	if (*(int*) ((char*) a1 + 0x124) != 0) {
		fcn_00403e20(a1, 0);
#ifdef REBREW_GOLD
		if (flag != 0) {
			fcn_00453270(**(char***) (a1 + 0x124));
		}
#endif
	}
	if (*(int*) ((char*) a1 + 0x22c) != 0) {
		fcn_004033e0(a1);
	}
}

int __cdecl ch_MoveCharacter2Universe(char* obj, void* universe)
{
	char buf[0x100];
	D3_OBJECT* n;

	if (obj != 0 && *(void**) (obj + 0x88) != 0 && universe != 0
	    && fcn_00443900(*(void**) (obj + 0x34), *(void**) (obj + 0x88), universe)) {
		fcn_00438c40(*(void**) (obj + 0x34), g_662d70);
		if (*(void***) (obj + 0x124) != 0) {
			fcn_00443900(**(void***) (obj + 0x124), *(void**) (obj + 0x88), universe);
		}
		if (*(void**) (obj + 0x22c) != 0) {
			fcn_00443900(*(void**) (obj + 0x22c), *(void**) (obj + 0x88), universe);
		}
		*(void**) (obj + 0x88) = universe;
		if (fcn_00413190(universe) == 0) {
			n = *(D3_OBJECT**) (obj + 0x34);
			n->darstellungsflag = g_6752a4;
		} else {
			n = *(D3_OBJECT**) (obj + 0x34);
			n->darstellungsflag = 0;
		}
		if (universe == (void*) g_67a370 && (*(D3_OBJECT**) (obj + 0x34))->kontext == 0) {
			sprintf(buf, "ch_MoveCharacter2Universe(): character deflated, will be inflated:%s", obj + 0x170);
			fcn_00402aa0(obj);
		}
		return 1;
	}
	return 0;
}

int __cdecl TakeObjectScript(char** ch, char** ani, int* kind, char** dummy, unsigned char* level, char** func)
{
	char* task;

	if (g_6b7ebc != 0 && *(int (__cdecl**)()) (g_6b7ebc + 0x44) == (int (__cdecl*)()) TakeObjectScript) {
		if (*(int*) (*ch + 0x128) != 0) {
			*(int (__cdecl**)()) (g_6b7e98 + 0xc60) = (int (__cdecl*)()) TakeObjectScript;
		}
		return 0;
	}
	if (*ch == 0) {
		fcn_00425bf0(g_6b7e98, *(int*) (g_6b7e98 + 0x118), "TakeObjectScript(): Invalid character");
		return 1;
	}
	if (*dummy == 0) {
		fcn_00425bf0(g_6b7e98, *(int*) (g_6b7e98 + 0x118), "TakeObjectScript(): Invalid dummy");
		return 1;
	}
	task = fcn_0040c230(*ch, fcn_0040cfb0, *level, 0x31, *kind);
	if (task != 0) {
		strcpy(task + 0xf0, *ani);
		if (*dummy != 0 && *(D3_OBJECT_DRAW_DATA**) (*dummy + 0x1ec) != 0 && (*(D3_OBJECT_DRAW_DATA**) (*dummy + 0x1ec))->teile[0].name != 0) {
			strcpy(task + 0x130, (*(D3_OBJECT_DRAW_DATA**) (*dummy + 0x1ec))->teile[0].name);
		}
		strcpy(task + 0x90, *func);
		*(int*) (task + 0x17c) = g_6791c8;
	}
	if (*(int*) (g_6b7e98 + 0xc84) == 1) {
		*(int (__cdecl**)()) (g_6b7e98 + 0xc60) = (int (__cdecl*)()) TakeObjectScript;
	}
	return 0;
}

void __cdecl ch_UpdatePendingPositions(void)
{
	char** p;
	char* obj;
	char* task;
	float position[4];
	float value;

	p = (char**) g_14d0020;
	do {
		obj = *p;
		if (obj != 0 && (obj[0x8c] & 1) != 0
		    && *(int*) (obj + 0x88) == g_67a370) {
			value = *(float*) (*(char**) (obj + 0x34) + 0x4c);
			position[0] = value + *(float*) (obj + 0x54);
			value = *(float*) (*(char**) (obj + 0x34) + 0x50);
			position[1] = value + *(float*) (obj + 0x58);
			value = *(float*) (*(char**) (obj + 0x34) + 0x54);
			position[2] = value + *(float*) (obj + 0x5c);
			task = *(char**) (obj + 0x128);
			if (task != 0) {
				if (task[9] != '-') {
					ch_SetPosition(obj, position, 0);
				}
			} else {
				ch_SetPosition(obj, position, 0);
			}
			obj[0x8c] &= ~1;
		}
		p++;
	} while ((int) p < (int) ((char**) g_14d0020 + 0x300));
}
