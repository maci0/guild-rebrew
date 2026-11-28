extern char* d3_ActiveCamera;
extern char* d3_SceneRootSentinelTail;
extern char d3_SceneRootSentinel[];
extern int d3_ActiveScene;

void __cdecl d3_SetActiveCamera(char*);
void __cdecl d3_SetObjectRotation(char*, char*);

/* ADDRESS: GOLD 0x0043ca20 */
void __cdecl d3_RegisterSceneObject(char* o)
{
	if (*(int*) (o + 0x218) == 3 && d3_ActiveCamera == 0) {
		d3_SetActiveCamera(o);
		d3_SetObjectRotation(o, o + 0x84);
	}
	if (*(int*) (o + 0x218) != 0) {
		*(char**) (o + 0x1f4) = d3_SceneRootSentinelTail;
		*(char**) (o + 0x1f0) = d3_SceneRootSentinel;
		*(char**) (d3_SceneRootSentinelTail + 0x1f0) = o;
		d3_SceneRootSentinelTail = o;
		o[0x210] |= 3;
	}
	*(int*) (o + 0x208) = d3_ActiveScene;
}
