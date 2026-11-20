#include "client_types.h"



#pragma pack(push, 2)
// SIZE 0xe






#pragma pack(pop)


extern pos14_7f4c00 gm_GameTime;

void __cdecl he_FreeAction(char* p);
void __cdecl fcn_00500bb0(pos14_7f4c00* s, int a, int b, int c);

void __cdecl fcn_005529a0(char* p)
{
	int i;
	int* q;

	p[0xd8] = 0;
	q = (int*) (p + 0x8c);
	for (i = 0; i < 6; i++) {
		if (*q++ != -1) {
			p[0xd8]++;
		}
	}
	if (p[0xd8] == 0) {
		he_FreeAction(p);
		return;
	}
	for (i = 0; i < 6; i++) {
		((int*) (p + 0xac))[i] = -1;
	}
	p[0xd2] = 0;
	*(pos14_7f4c00*) (p + 0xc4) = (*(pos14_7f4c00*)&gm_GameTime);
	*(pos14_7f4c00*) (p + 0x52) = (*(pos14_7f4c00*)&gm_GameTime);
	fcn_00500bb0((pos14_7f4c00*) (p + 0x52), 0, 2, 0);
}
