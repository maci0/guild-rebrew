typedef int (__cdecl* SCENE_EVENT_HANDLER)(char*, int, char*);

extern int g_67a590;
extern int d3_ActiveScene;

int __cdecl vfs_ReadDword(void* stream, void* dst);
char* __cdecl vfs_ReadCString(void* stream, char* text);
int __cdecl d3_FindSceneEventId(char*);
char __cdecl d3e_RegisterSceneEvent(char*, int, int, char*);

/* ADDRESS: GOLD 0x0043ea10 */
void __cdecl d3e_ReadSceneEvents(void* r)
{
	int n;
	char val[0x100];
	char name[0x100];
	int i;
	int id;

	vfs_ReadDword(r, &n);
	for (i = 0; i < n; i++) {
		vfs_ReadCString(r, name);
		id = d3_FindSceneEventId(name);
		vfs_ReadCString(r, val);
		d3e_RegisterSceneEvent(((char*)d3_ActiveScene), id, (*(SCENE_EVENT_HANDLER*)&g_67a590)(((char*)d3_ActiveScene), id, val), val);
	}
}
