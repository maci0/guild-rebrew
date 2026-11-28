#include <string.h>

extern unsigned char gm_ActiveTownIndex;

int __cdecl gm_IsSlotActivePerson(unsigned short);
int __cdecl fcn_0064fcaf(char*);
int __cdecl gm_FindObjektPrototypeByName(char*);
int __cdecl cm_SendSellObjekt(int, int, int, int, unsigned char, int);

/* ADDRESS: GOLDTL 0x004b0a90 */
int __cdecl hst_CmdAmtstraegerInventarPlus(int unused0, int unused1, char* arg)
{
	char* s;
	int objId;
	int i;
	char* slot;

	if (*arg != '-') {
		return 0;
	}
	s = arg + 1;
	if (strlen(s) < 4) {
		return 0;
	}
	s += 3;
	fcn_0064fcaf(s + 1);
	objId = gm_FindObjektPrototypeByName(s);
	if (objId == 0) {
		return 0;
	}
	for (i = 0, slot = (char*) 0x7f4e09; (int) slot < (int) 0x85a209; slot += 0x21c, i++) {
		if (gm_IsSlotActivePerson((unsigned short) i) != 0) {
			if (*(char*) (slot - 3) != 0 || *slot != 0) {
				cm_SendSellObjekt(*(int*) (slot - 0x165), -1, objId, 1, gm_ActiveTownIndex, 0);
			}
		}
	}
	return 1;
}
