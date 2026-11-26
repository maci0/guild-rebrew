#include <string.h>

extern unsigned char g_773d75;

int __cdecl gm_IsSlotActivePerson(unsigned short);
int __cdecl fcn_0064fcaf(char*);
int __cdecl gm_FindObjektPrototypeByName(char*);
int __cdecl cm_SendSellObjekt(int, int, int, int, unsigned char, int);

/* ADDRESS: GOLDTL 0x004b0a90 */
int __cdecl fcn_004b0a90(int a0, int a1, char* arg)
{
	char* s;
	int r;
	int i;
	char* e;

	if (*arg != '-') {
		return 0;
	}
	s = arg + 1;
	if (strlen(s) < 4) {
		return 0;
	}
	s += 3;
	fcn_0064fcaf(s + 1);
	r = gm_FindObjektPrototypeByName(s);
	if (r == 0) {
		return 0;
	}
	for (i = 0, e = (char*) 0x7f4e09; (int) e < (int) 0x85a209; e += 0x21c, i++) {
		if (gm_IsSlotActivePerson((unsigned short) i) != 0) {
			if (*(char*) (e - 3) != 0 || *e != 0) {
				cm_SendSellObjekt(*(int*) (e - 0x165), -1, r, 1, g_773d75, 0);
			}
		}
	}
	return 1;
}
