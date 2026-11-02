


#include <string.h>
#include "Develop/DieGildeAddOn/game/cutscene.h"

char* __cdecl cut_FindCutsceneById(int);

void __cdecl cut_FreeCutscene(int a1)
{
	char* p;

	p = cut_FindCutsceneById(a1);
	if (p != 0) {
		memset(p, 0, 0x114);
		*(int*) p = -1;
	}
}

#ifndef REBREW_GOLD
void __cdecl cut_FreeAllCutscenes(void)
{
	int a;

	for (a = 0x9a9660; a < 0x9afde0; a += 0x114) {
		if (*(int*) a != -1) {
			cut_FreeCutscene(*(int*) a);
		}
	}
}

#endif

int __cdecl cut_AddParticipant(int id, int v)
{
	char* p;
	int i;

	p = cut_FindCutsceneById(id);
	if (p != 0) {
		for (i = 0; i < *(unsigned char*) (p + 0x30); i++) {
			if (*(int*) (p + 0x34 + i * 4) == v) {
				return 0;
			}
		}
		if (*(unsigned char*) (p + 0x30) < 0x10) {
			*(int*) (p + 0x34 + *(unsigned char*) (p + 0x30) * 4) = v;
			p[0x30]++;
			return 1;
		}
	}
	return 0;
}


extern int* g_772f40;
extern char g_9b0e20[];

int __cdecl cut_RemoveParticipant(int a, int b)
{
	unsigned char* s;
	int i;

	s = (unsigned char*) cut_FindCutsceneById(a);
	if (s == 0)
		return 0;
	for (i = 0; i < s[0x30]; i++) {
		if (*(int*) (s + 0x34 + i * 4) == b) {
			*(int*) (s + 0x34 + i * 4) = -1;
			break;
		}
	}
	if (g_772f40 != 0 && *g_772f40 == a) {
		for (i = 0; i < 16; i++) {
			if (*(int*) (g_9b0e20 + i * 0x35c + 0x10) == b) {
				*(int*) (g_9b0e20 + i * 0x35c + 0x10) = -1;
				break;
			}
		}
	}
	return 1;
}
