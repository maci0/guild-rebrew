


#include "Develop/client_types.h"
extern pos14_7f4c00 gm_GameTime;
extern int d3_ActiveScene;

void __cdecl gm_GetSeason(char*);
void __cdecl d3_TraverseSceneObjects(int, int, int, void*);
void __cdecl d3_ApplyVegetationTextureSet(void);
void __cdecl d3_ApplySeasonTextureSet(void);
void __cdecl d3_UpdateTerrainSeasonTextures(void);

/* ADDRESS: GOLDDE 0x004d1840 */
void __cdecl d3_UpdateSeasonTextures(void)
{
	gm_GetSeason(((char*)&gm_GameTime));
	d3_TraverseSceneObjects(d3_ActiveScene, 0, 0xc0, d3_ApplyVegetationTextureSet);
	d3_TraverseSceneObjects(d3_ActiveScene, 0, 0xc0, d3_ApplySeasonTextureSet);
	d3_UpdateTerrainSeasonTextures();
}
