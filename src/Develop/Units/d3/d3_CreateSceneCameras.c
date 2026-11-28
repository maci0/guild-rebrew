extern int g_6b8484;
extern char* d3_TopViewCamera;
extern char* d3_FrontViewCamera;
extern char* d3_SideViewCamera;
extern char g_6b8004;
extern char s_67a9ac[];
extern char s_67a9c4[];
extern char s_67a9bc[];
extern char s_67a9b4[];

char* __cdecl d3_SpawnObject(int kind, char* name);
void __cdecl d3_SetNodePositionXYZ(char* o, float x, float y, float z);
void __cdecl d3_SetObjectEulerRotation(char* o, float x, float y, float z);
void __cdecl d3_RegisterSceneObjectTl(char* o);

/* ADDRESS: GOLDTL 0x00444040 */
void __cdecl d3_CreateSceneCameras(void)
{
	(*(char**)&g_6b8484) = d3_SpawnObject(3, s_67a9ac);
	d3_SetNodePositionXYZ((*(char**)&g_6b8484), 0.0f, 0.0f, -256.0f);
	d3_SetObjectEulerRotation((*(char**)&g_6b8484), 0.0f, 0.0f, 0.0f);
	d3_RegisterSceneObjectTl((*(char**)&g_6b8484));
	if (g_6b8004 != 0) {
		d3_TopViewCamera = d3_SpawnObject(3, s_67a9c4);
		d3_SetNodePositionXYZ(d3_TopViewCamera, 0.0f, 256.0f, 0.0f);
		d3_SetObjectEulerRotation(d3_TopViewCamera, -1.5707964f, 0.0f, 0.0f);
		d3_RegisterSceneObjectTl(d3_TopViewCamera);
		d3_TopViewCamera[0x214] &= 0x7f;
		d3_FrontViewCamera = d3_SpawnObject(3, s_67a9bc);
		d3_SetNodePositionXYZ(d3_FrontViewCamera, 0.0f, 0.0f, -256.0f);
		d3_SetObjectEulerRotation(d3_FrontViewCamera, 0.0f, 0.0f, 0.0f);
		d3_RegisterSceneObjectTl(d3_FrontViewCamera);
		d3_FrontViewCamera[0x214] &= 0x7f;
		d3_SideViewCamera = d3_SpawnObject(3, s_67a9b4);
		d3_SetNodePositionXYZ(d3_SideViewCamera, 256.0f, 0.0f, 0.0f);
		d3_SetObjectEulerRotation(d3_SideViewCamera, 0.0f, 1.5707964f, 0.0f);
		d3_RegisterSceneObjectTl(d3_SideViewCamera);
		d3_SideViewCamera[0x214] &= 0x7f;
	}
}
