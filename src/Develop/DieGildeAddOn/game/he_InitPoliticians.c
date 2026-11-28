int __cdecl cm_SendSetHE(int, char*);

#include "Develop/client_types.h"
extern pos14_7f4c00 gm_GameTime;

// SIZE 0x10
struct POLITICIANS_SLOT {
	int a;
	int b;
	char c[4];
	int pad;
};


/* ADDRESS: GOLDTL 0x005595e0 */
void __cdecl he_InitPoliticians(char* o)
{
	int i;

	*(int*) (o + 0x70) = 0;
	if ((o[0x78] & 4) == 0) {
		for (i = 0; i < 10; i++) {
			((struct POLITICIANS_SLOT*) (o + 0xac))[i].a = -1;
			((struct POLITICIANS_SLOT*) (o + 0xac))[i].b = -1;
			((struct POLITICIANS_SLOT*) (o + 0xac))[i].c[0] = 0;
			((struct POLITICIANS_SLOT*) (o + 0xac))[i].c[1] = 0;
			((struct POLITICIANS_SLOT*) (o + 0xac))[i].c[2] = 0;
			((struct POLITICIANS_SLOT*) (o + 0xac))[i].c[3] = 0;
		}
		*(pos14_7f4c00*) (o + 0x52) = gm_GameTime;
		*(short*) (o + 0x56) = 0xb;
		*(int*) (o + 0x58) = 0;
		*(int*) (o + 0x84) = cm_SendSetHE(0, o);
	}
}
