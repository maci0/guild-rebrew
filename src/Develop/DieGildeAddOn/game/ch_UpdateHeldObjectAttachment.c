#include <string.h>
extern char* lpObjektePROT;
extern char g_68b7ac[];

int* __cdecl gm_GetEquippedCombatGear(char*);
int __cdecl fcn_0064d41a(char*, char*, ...);
int __cdecl fcn_0065f220(char*, char*);
void __cdecl ch_SetBodyAttachment(char*, int, char*);

/* ADDRESS: GOLDDE 0x004bc180 */
void __cdecl ch_UpdateHeldObjectAttachment(char* entity)
{
	char buf[0x80];
	int* obj_rec;
	int obj_kind;
	char* name;

	obj_rec = gm_GetEquippedCombatGear(entity);
	if (obj_rec != 0 && *obj_rec != 0) {
		obj_kind = *obj_rec;
		name = lpObjektePROT + obj_kind * 0x40 + obj_kind;
		if (*(char**) (entity + 0x184) == 0)
			return;
		fcn_0064d41a(buf, g_68b7ac, _strupr(name + 1));
		if (*(char**) (*(char**) (entity + 0x184) + 0x64) != 0 &&
		    fcn_0065f220(*(char**) (*(char**) (entity + 0x184) + 0x64), buf) == 0)
			return;
		if (*(char**) (*(char**) (entity + 0x184) + 0x64) != 0)
			ch_SetBodyAttachment(*(char**) (entity + 0x184), 2, 0);
		ch_SetBodyAttachment(*(char**) (entity + 0x184), 2, buf);
		return;
	}
	if (*(char**) (entity + 0x184) != 0 && *(char**) (*(char**) (entity + 0x184) + 0x64) != 0)
		ch_SetBodyAttachment(*(char**) (entity + 0x184), 2, 0);
}
