#include "Develop/DieGildeAddOn/game/game_data.h"
extern unsigned char* lpGebaeudeINST;

#pragma pack(1)
// SIZE 0xa
struct ref_fb5761 {
	char type;
	char pad[4];
	char* ref;
	char pad2;
};
#pragma pack()

extern struct ref_fb5761 g_fb5761[0x8000];



void __cdecl d3_SelectSceneContext(int, int);

void __cdecl fcn_0051e9d0(void)
{
	int save;
	int i;

	save = d3_CurrentContextIndex;
	d3_SelectSceneContext(0, 1);
	for (i = 0; i < 0x100; i++) {
		if (((char*)lpGebaeudeINST)[i * 0xa9] != 0 && *(char**) (((char*)lpGebaeudeINST) + i * 0xa9 + 0x61) != 0) {
			*(int*) (*(char**) (((char*)lpGebaeudeINST) + i * 0xa9 + 0x61) + 0x204) =
			    *(int*) (((char*)lpGebaeudeINST) + i * 0xa9 + 1);
		}
	}
	d3_SelectSceneContext(save, 1);
	for (i = 0; i < 0x8000; i++) {
		if (g_fb5761[i].ref != 0) {
			if (g_fb5761[i].type == 1) {
				g_fb5761[i].ref = *(char**) (g_fb5761[i].ref + 4);
			}
			if (g_fb5761[i].type == 3) {
				g_fb5761[i].ref = *(char**) (g_fb5761[i].ref + 2);
			}
			if (g_fb5761[i].type == 2) {
				g_fb5761[i].ref = *(char**) (g_fb5761[i].ref + 1);
			}
			if (g_fb5761[i].type == 9) {
				g_fb5761[i].ref = *(char**) g_fb5761[i].ref;
			}
		}
	}
}
