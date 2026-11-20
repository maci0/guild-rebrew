void __cdecl he_FreeAction(char*);

#include "client_types.h"
extern pos14_7f4c00 gm_GameTime;




unsigned short* __cdecl gm_LookupEntityRecordById(int);
void __cdecl fcn_00529160(int, int, int, char*);
void __cdecl fcn_00500bb0(pos14_7f4c00*, int, int, int);

void __cdecl fcn_005601e0(char* o)
{
	int any;
	int i;
	unsigned short* e;

	any = 0;
	for (i = 0; i < *(unsigned char*) (o + 0xac); i++) {
		e = gm_LookupEntityRecordById(((int*) (o + 0x8c))[i]);
		if (e != 0) {
			any |= 1;
			fcn_00529160(0, 0, *e, o);
		}
	}
	if (any == 0) {
		he_FreeAction(o);
		return;
	}
	*(pos14_7f4c00*) (o + 0x52) = gm_GameTime;
	*(int*) (o + 0x70) = 1;
	fcn_00500bb0((pos14_7f4c00*) (o + 0x52), 0, 5, 0);
}
