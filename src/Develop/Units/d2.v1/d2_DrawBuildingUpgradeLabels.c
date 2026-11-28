extern int d2_ScreenSurface;
extern int d3_ActiveScene;

// SIZE 0xc8

#include "Develop/client_types.h"
extern s_7e46c0 g_7e46c0[32];



void __cdecl d2_SelectFont(int);
char __cdecl d3_GetObjectScreenRect(char*, int*);
void __cdecl d2_DrawWordWrappedText(int, int, int, int, int, char*, int);
void __cdecl d3_TraverseSceneObjects(int, int, int, void*);
void __cdecl d3_DrawBuildingUpgradeLabel(void);

void __cdecl d2_DrawBuildingUpgradeLabels(void)
{
	int r[4];
	s_7e46c0* p;
	char* e;

	d2_SelectFont(0x54);
	for (p = g_7e46c0; (int) p < (int) &g_7e46c0[32]; p++) {
		e = p->e;
		if (e != 0 && (*(int*) (e + 0x1cc) != 0 || *(int*) (e + 0x218) == 0) &&
		    d3_GetObjectScreenRect(e, r) != 0) {
			d2_DrawWordWrappedText(r[0] + (r[2] - r[0]) / 2 - 0x50, r[1], 0xa0, 0x60, d2_ScreenSurface,
			             p->name, 0x28);
		}
	}
	d3_TraverseSceneObjects(d3_ActiveScene, 0, 0x20, (void*) d3_DrawBuildingUpgradeLabel);
}
