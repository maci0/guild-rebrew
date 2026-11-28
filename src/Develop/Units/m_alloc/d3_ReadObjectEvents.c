

typedef int (__cdecl* fcn_0043b7b0_f)(char*, int, char*);

extern int g_67a590;

#ifdef REBREW_GOLD
int __cdecl vfs_ReadDword(void* a, void* b);
#else
int __cdecl fcn_004011f0(void* stream, void* dst);
#endif
char* __cdecl vfs_ReadCString(void* stream, char* text);
int __cdecl d3_FindSceneEventId(char*);
char __cdecl d3_SetObjectEvent(char*, int, int, char*);

/* ADDRESS: GOLD 0x0043e970 */
/* ADDRESS: GOLDDE 0x00434560 */
void __cdecl d3_ReadObjectEvents(void* r, char* o)
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
		if (o != 0) {
			d3_SetObjectEvent(o, id, (*(fcn_0043b7b0_f*)&g_67a590)(o, id, val), val);
		}
	}
}
