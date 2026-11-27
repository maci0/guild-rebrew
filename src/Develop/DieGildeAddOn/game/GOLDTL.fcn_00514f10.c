extern int g_67a370;
extern int g_6b8300;



char* __cdecl gm_StartFilteredEntitySearch(int, int);
char* __cdecl gm_AddObjekt(void);
char* __cdecl gm_FindNextFilteredEntity(void);
void __cdecl gm_UpdateBuildingSmokeEffect(char*);
void __cdecl d3_VisitSceneObjects(char*, int, int, void*, void*);
char __cdecl d3_ClassifyBuildingSceneObject(char*);
void __cdecl d3_RebuildSceneQuadtreeAndLighting(void);
void __cdecl d3_ReleaseUnusedSceneObjects(void);
void __cdecl d3sm_Rebuild(int, int);

void __cdecl d3_RebuildWorldScene(void)
{
	char* e;
	char* o;

	for (e = gm_StartFilteredEntitySearch(1, 6); e != 0; e = gm_FindNextFilteredEntity()) {
		o = *(char**) (e + 0x61);
		if (o != 0) {
			o[0x216] = (o[0x216] & 0xfd) | 1;
			gm_UpdateBuildingSmokeEffect(e);
		}
	}
	d3_VisitSceneObjects(((char*)g_67a370), 0, 0x40, (void*) d3_ClassifyBuildingSceneObject, 0);
	d3_RebuildSceneQuadtreeAndLighting();
	d3_ReleaseUnusedSceneObjects();
	d3sm_Rebuild(*(int*) (((char*)g_67a370) + 0xb0), g_6b8300);
}
