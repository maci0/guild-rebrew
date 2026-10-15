


#pragma pack(2)
// SIZE 0xe
struct pos14 {
	int a;
	int b;
	int c;
	short d;
};
#pragma pack()

char* __cdecl fcn_00508e40(int);
#include "Develop/Units/Error/error_message.h"
char* __cdecl fcn_005463a0(int, int, int);
char* __cdecl fcn_005462a0(void);
void __cdecl fcn_00546190(char*);

void __cdecl fcn_0056e320(char* e)
{
	char* o;

	if (fcn_00508e40(*(int*) (e + 0xac)) == 0) {
		fcn_0041d9e0("he_AllocKillPlayer: player not found!");
		fcn_00546190(e);
		return;
	}
	for (o = fcn_005463a0(1, 0, 0x72); o != 0; o = fcn_005462a0()) {
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
