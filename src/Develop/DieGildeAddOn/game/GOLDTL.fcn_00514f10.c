extern int g_67a370;
extern int g_6b8300;



char* __cdecl gm_StartFilteredEntitySearch(int, int);
char* __cdecl gm_AddObjekt(void);
char* __cdecl gm_FindNextFilteredEntity(void);
void __cdecl fcn_0052db70(char*);
void __cdecl fcn_004379a0(char*, int, int, void*, void*);
char __cdecl fcn_00514e80(char*);
void __cdecl fcn_00514e30(void);
void __cdecl fcn_00598510(void);
void __cdecl fcn_0045b290(int, int);

void __cdecl fcn_00514f10(void)
{
	char* e;
	char* o;

	for (e = gm_StartFilteredEntitySearch(1, 6); e != 0; e = gm_FindNextFilteredEntity()) {
		o = *(char**) (e + 0x61);
		if (o != 0) {
			o[0x216] = (o[0x216] & 0xfd) | 1;
			fcn_0052db70(e);
		}
	}
	fcn_004379a0(((char*)g_67a370), 0, 0x40, (void*) fcn_00514e80, 0);
	fcn_00514e30();
	fcn_00598510();
	fcn_0045b290(*(int*) (((char*)g_67a370) + 0xb0), g_6b8300);
}
