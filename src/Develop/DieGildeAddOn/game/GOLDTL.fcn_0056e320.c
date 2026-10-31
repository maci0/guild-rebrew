


#pragma pack(2)
// SIZE 0xe
struct pos14 {
	int a;
	int b;
	int c;
	short d;
};
#pragma pack()

char* __cdecl gm_LookupEntityRecordById(int);
#include "Develop/Units/Error/error_message.h"
char* __cdecl fcn_005463a0(int, int, int);
char* __cdecl he_fn_Handlung(void);
void __cdecl fcn_00546190(char*);

void __cdecl he_AllocKillPlayer(char* e)
{
	char* o;

	if (gm_LookupEntityRecordById(*(int*) (e + 0xac)) == 0) {
		ReportClientMessage("he_AllocKillPlayer: player not found!");
		fcn_00546190(e);
		return;
	}
	for (o = fcn_005463a0(1, 0, 0x72); o != 0; o = he_fn_Handlung()) {
		if (o != e && *(int*) (o + 0xac) == *(int*) (e + 0xac)) {
			fcn_00546190(e);
			return;
		}
	}
	*(int*) (e + 0xb4) = -1;
	*(struct pos14*) (e + 0x52) = *(struct pos14*) (e + 0x44);
	*(int*) (e + 0xb0) = -1;
	*(int*) (e + 0x84) = -1;
}
