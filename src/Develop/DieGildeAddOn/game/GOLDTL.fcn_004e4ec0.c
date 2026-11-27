


#include "client_types.h"
extern pos14_7f4c00 gm_GameTime;
extern int g_67a370;

void __cdecl gm_GetSeason(char*);
void __cdecl d3_TraverseSceneObjects(int, int, int, void*);
void __cdecl d3_ApplyVegetationTextureSet(void);
void __cdecl d3_ApplySeasonTextureSet(void);
void __cdecl fcn_00516040(void);

void __cdecl d3_UpdateSeasonTextures(void)
{
	gm_GetSeason(((char*)&gm_GameTime));
	d3_TraverseSceneObjects(g_67a370, 0, 0xc0, d3_ApplyVegetationTextureSet);
	d3_TraverseSceneObjects(g_67a370, 0, 0xc0, d3_ApplySeasonTextureSet);
	fcn_00516040();
}
