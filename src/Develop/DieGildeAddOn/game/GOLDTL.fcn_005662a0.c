void __cdecl fcn_00546190(char*);

#include "client_types.h"
extern pos14_7f4c00 g_7f4c00;




char* __cdecl fcn_005463a0(int, int, int, ...);
char* __cdecl he_fn_Handlung(void);
char* __cdecl gm_LookupEntityRecordById(int);
void __cdecl fcn_00500bb0(pos14_7f4c00*, int, int, int);
void __cdecl fcn_004c5420(int, int, int, int, int);

void __cdecl fcn_005662a0(char* o)
{
	char* p;
	char* e;

	for (p = fcn_005463a0(1, 0, 0x32); p != 0; p = he_fn_Handlung()) {
		if (p != o && *(int*) (o + 0xac) == *(int*) (p + 0xac)) {
			fcn_00546190(o);
			return;
		}
	}
	*(int*) (o + 0xb0) = -1;
	*(pos14_7f4c00*) (o + 0x52) = g_7f4c00;
	fcn_00500bb0((pos14_7f4c00*) (o + 0x52), 0, 0, 1);
	e = gm_LookupEntityRecordById(*(int*) (o + 0xac));
	if (e == 0) {
		fcn_00546190(o);
		return;
	}
	if (o[0x78] & 2) {
		fcn_004c5420(*(int*) (e + 4), 0x1cc, 4, 0x1000000, 0);
	}
}
