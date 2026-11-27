extern int SonnenstrahlenAktiv;
extern int g_633444;

int __cdecl d3_GetSceneContextIndex(char*);
char __cdecl d3_SelectSceneContext(int, char);
void __cdecl d3_DestroyObject(void*);

/* ADDRESS: GOLD 0x00417560 */
void __cdecl d3_DestroySonnenstrahlen(void* obj)
{
	int found;
	int handle;
	int sun;

	sun = g_633444;
	found = -1;
	handle = *(int*) ((char*) obj + 0x208);
	if (handle != *(int*) 0x5fb5b0) {
		handle = d3_GetSceneContextIndex((char*) handle);
		d3_SelectSceneContext(handle, 1);
		found = handle;
	}
	d3_DestroyObject(obj);
	SonnenstrahlenAktiv = 0;
	if (found != -1) {
		d3_SelectSceneContext(sun, 1);
	}
}
