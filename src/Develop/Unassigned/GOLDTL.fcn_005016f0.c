#include "client_town.h"

extern char* lpObjektePROT;
extern int __cdecl fcn_00502450(int a, int b);
extern int __cdecl fcn_005024e0(int a, int b);
extern float __cdecl eval_ObjektPreis2Credits(int a, int b);

/* ADDRESS: GOLDTL 0x005016f0 */
void __cdecl fcn_005016f0(int which)
{
	char* src; char* def;
	char* dst;
	unsigned char kind;
	int i;

	i = 0;
	src = (char*) 0x696608;
	dst = (char*) 0x85abc0 + which * 0x2a90;
	do {
		def = lpObjektePROT + *(unsigned short*) (dst - 0x30) * 0x41; *(int*) (dst - 0x24) = *(int*) (src - 0x24);
		*(int*) dst = *(int*) src;
		kind = *def;
		if (kind != 0x17 && kind != 0x25) {
			*(float*) (dst - 0x10) = (float) fcn_00502450(which, i);
		} else {
			*(int*) (dst + 4) = fcn_005024e0(which, i);
		}
		*(float*) (dst + 8) = eval_ObjektPreis2Credits(*(unsigned short*) (dst - 0x30), 100);
		*(int*) (dst - 0xc) = *(int*) (dst - 0x10);
		src += 0x80;
		i++;
		dst += 0x80;
	} while ((int) src < 0x699088);
}
