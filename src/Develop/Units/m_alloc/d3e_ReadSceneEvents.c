

typedef int (__cdecl* SCENE_EVENT_HANDLER)(char*, int, char*);

extern int g_67a590;
extern int d3_ActiveScene;
#ifdef REBREW_GOLD
int __cdecl vfs_ReadDword(void* stream, void* dst);
#else
int __cdecl fcn_004011f0(void* stream, void* dst);
#endif
char* __cdecl vfs_ReadCString(void* stream, char* text);
int __cdecl d3_FindSceneEventId(char*);
char __cdecl d3e_RegisterSceneEvent(char*, int, int, char*);

/* ADDRESS: GOLDTL 0x0043b850 */
void __cdecl d3e_ReadSceneEvents(void* r)
{
	int n;
	char val[0x100];
	char name[0x100];
	int i;
	int id;

#ifdef REBREW_GOLD
	vfs_ReadDword(r, &n);
#else
	fcn_004011f0(r, &n);
#endif
	for (i = 0; i < n; i++) {
		vfs_ReadCString(r, name);
		id = d3_FindSceneEventId(name);
		vfs_ReadCString(r, val);
		d3e_RegisterSceneEvent(((char*)d3_ActiveScene), id, (*(SCENE_EVENT_HANDLER*)&g_67a590)(((char*)d3_ActiveScene), id, val), val);
	}
}
