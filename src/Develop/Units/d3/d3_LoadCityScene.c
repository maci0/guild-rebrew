extern int d3_ActiveScene;


int __cdecl sprintf(char*, const char*, ...);
#include "Develop/Units/d3/client_scene_loader.h"
void __cdecl d3_TraverseSceneObjects(int, int, int, void (__cdecl*)(void));
void __cdecl d3_InitBuildingSceneAnimRates(void);

/* ADDRESS: GOLDDE 0x004fb840 */
char __cdecl d3_LoadCityScene(const char* name)
{
	char path[256];

	sprintf(path, "scenes/*stadt_%s.ed3", name);
	if (!d3_LoadScene(path, 0, 0)) {
		return 0;
	}
	d3_TraverseSceneObjects(d3_ActiveScene, 0, 6, d3_InitBuildingSceneAnimRates);
	return 1;
}
