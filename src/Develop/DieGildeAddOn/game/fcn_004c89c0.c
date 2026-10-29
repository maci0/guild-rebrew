#include <string.h>

int __cdecl fcn_004c4dc0(char*, int);
char* __cdecl gm_AllocObjekt(int parent_id, int type, int param3);

/* ADDRESS: GOLDTL 0x004c89c0 */
int __cdecl fcn_004c89c0(char* a0, char* a1)
{
	char* p;
	int v;

	if (*(int*) 0x14cbca0 != -1) {
		*(int*) 0x699364 = *(int*) (a0 + 0x35);
	}
	v = fcn_004c4dc0(a0, *(int*) (a0 + 0x10));
	*(int*) (a0 + 0x10) = v;
	p = gm_AllocObjekt(v, *(unsigned short*) (a0 + 0x14), 1);
	if (p == 0) {
		return 1;
	}
	*(int*) 0x68a9d8 = *(int*) (p + 2);
	memcpy(p + 0x1c, a0 + 0x16, 0x1f);
	if (a1 != 0) {
		*a1 = 1;
	}
	return 0;
}
