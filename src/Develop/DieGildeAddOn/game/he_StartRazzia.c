#include "Develop/client_types.h"
extern pos14_7f4c00 gm_GameTime;

// SIZE 0xf8
struct msg {
	int f0;
	char b4;
	char pad[3];
	int f8;
	int fc;
	char pad2[0x18];
	pos14_7f4c00 pos;
	char b36;
	char pad3[0x21];
	char b58;
	char pad4[3];
	char b5c;
	char pad5[0x9b];
};




char* __cdecl gm_StartFilteredEntitySearch(int, int, int);
void __cdecl gm_AddTime(pos14_7f4c00*, int, int, int);
int __cdecl cm_SendSetHE(int, char*);

/* ADDRESS: GOLDDE 0x00534770 */
void __cdecl he_StartRazzia(char* o)
{
	if (o[0x78] & 2) {
		if (gm_StartFilteredEntitySearch(1, 1, *(int*) (o + 0xac)) == 0) {
			*(pos14_7f4c00*) (o + 0x52) = gm_GameTime;
			gm_AddTime((pos14_7f4c00*) (o + 0x52), 0, 0, 1);
			*(int*) (o + 0x84) = cm_SendSetHE(-1, o);
		}
		*(pos14_7f4c00*) (o + 0x52) = gm_GameTime;
		gm_AddTime((pos14_7f4c00*) (o + 0x52), 0, 0, 1);
		*(int*) (o + 0x84) = cm_SendSetHE(0, o);
	}
}
