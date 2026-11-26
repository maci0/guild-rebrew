#include <string.h>
#include "Develop/DieGildeAddOn/game/object_prototype.h"
extern char g_68b0d8[];
extern char g_68b1f8[];
extern char g_68b214[];
extern char* lpObjektePROT;
int __cdecl fcn_0064d41a(char*, char*, ...);
char* __cdecl ch_FindCharacterByName(char*);
char* __cdecl gm_StartFilteredEntitySearch(int, int, int, ...);
char* __cdecl fcn_00502cd0(int, int, int, ...);
int __cdecl init_EnsureObjektSceneContext(char*);
int __cdecl init_AllocateGebaeudeSceneSlot(char*);
void __cdecl ch_UseGate(char*, char*, char*, int, int, int);
char* __cdecl strupr(char*);

/* ADDRESS: GOLDTL 0x004cb450 */
int __cdecl cm_ExUseGate(char* command, char* result)
{
	char gate2[0x80];
	char search[0x80];
	char gate[0x80];
	char* o;
	char* s;
	char* d;
	char* v4;
	char* name;
	int id;
	int k;
	fcn_0064d41a(search, g_68b0d8, *(int*) (command + 0x10));
	o = ch_FindCharacterByName(search);
	if (!o)
		return 1;
	s = gm_StartFilteredEntitySearch(1, 1, *(int*) (command + 0x14));
	d = fcn_00502cd0(*(int*) (s + 0x5d), 1, 1, *(int*) (command + 0x18));
	id = *(int*) (o + 0x30);
	if (id != -1)
		v4 = fcn_00502cd0(*(int*) (s + 0x5d), 1, 1, id);
	else
		v4 = fcn_00502cd0(*(int*) (s + 0x5d), 1, 0, 0xfd);
	if (*(unsigned short*) d == 0xfd) {
		k = init_AllocateGebaeudeSceneSlot(s);
		fcn_0064d41a(gate, g_68b1f8);
	} else {
		name = (char*)&((OBJECT_PROTOTYPE*)lpObjektePROT)[*(unsigned short*) d];
		k = init_EnsureObjektSceneContext(d);
		fcn_0064d41a(gate, g_68b214, strupr(name + 1));
	}
	name = (char*)&((OBJECT_PROTOTYPE*)lpObjektePROT)[*(unsigned short*) v4];
	fcn_0064d41a(gate2, g_68b214, strupr(name + 1));
	if (k >= 0)
		ch_UseGate(o, gate2, gate, k, *(int*) (s + 1), *(int*) (d + 2));
	if (result) {
		result[0] = 2;
		result[1] = 0;
		*(int*) (result + 6) = 0;
	}
	return 0;
}
