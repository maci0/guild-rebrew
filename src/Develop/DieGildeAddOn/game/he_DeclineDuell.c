#include "Develop/client_types.h"

typedef struct {
	int v[6];
} Row_54f4a0;

extern pos14_7f4c00 gm_GameTime;
extern float g_662924;

void __cdecl io_FormatTextBuffer(void*, int, ...);
void __cdecl he_PostEntityMessage(int, int, void*, int, int, void*);
void __cdecl cm_RequestChangeBits(int, int, int, int, int);
int __cdecl srv_GetEntityOfficeSlot(unsigned char*, void*, void*);
float __cdecl gm_GetEntitySkill(char*, int);
unsigned short __cdecl gm_RandomMod(unsigned short);
void __cdecl amt_AdjustOfficeHoldersFavor(unsigned char*, int, int);
void __cdecl cm_RequestCopyEntityData(int, int, int, int);
void __cdecl cm_SendSetHE(int, char*);

/* ADDRESS: GOLDTL 0x0054f4a0 */
void __cdecl he_DeclineDuell(char* a0, char* firstEntity, unsigned char* secondEntity)
{
	Row_54f4a0 role;
	Row_54f4a0 slot;
	char buf[0x400];
	int ret;
	int textId;

	ret = 0;
	if (firstEntity[2] == 6 || firstEntity[2] == 7) {
		if (secondEntity[9] != 0) {
			textId = 0x1d69;
		} else {
			textId = 0x1d68;
		}
		io_FormatTextBuffer(buf, 0x1d81, *(unsigned short*) secondEntity, *(unsigned short*) secondEntity, textId);
		he_PostEntityMessage(*(int*) (firstEntity + 4), *(int*) (firstEntity + 4), buf, 0, 0x5fb, 0);
		cm_RequestChangeBits(*(int*) (firstEntity + 4), 0x1c8, 4, 0, 0x400);
		cm_RequestChangeBits(*(int*) (secondEntity + 4), 0x1c8, 4, 0, 0x400);
	}
	if (secondEntity[0x166] != 0) {
		if (srv_GetEntityOfficeSlot(secondEntity, &role, &slot) != 0) {
			ret = role.v[1];
		}
		else {
			ret = (unsigned short) gm_RandomMod(3) + 1;
		}
	}
	amt_AdjustOfficeHoldersFavor(secondEntity, ret, -9 - (int) (gm_GetEntitySkill(firstEntity, 4) * 8.0f) - (gm_RandomMod(8) & 0xffff));
	cm_RequestCopyEntityData(*(int*) (firstEntity + 4), *(int*) (secondEntity + 4), -0x14, 1);
	*(pos14_7f4c00*) (a0 + 0x52) = gm_GameTime;
	cm_SendSetHE(-1, a0);
}
