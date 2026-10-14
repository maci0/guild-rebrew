


typedef struct {
	short w[7];
} Rec14;
// SIZE 0xe

#include "client_types.h"
extern pos14_7f4c00 g_7f4c00;

char* __cdecl fcn_00508e40(int);
void __cdecl fcn_0041d9e0(const char*, ...);
void __cdecl fcn_00546190(char*);

void __cdecl fcn_0056e110(char* e)
{
	char* p;

	p = fcn_00508e40(*(int*) (e + 0xac));
	if (p == 0) {
		fcn_0041d9e0("he_AllocDiePlayer: player not found!");
		fcn_00546190(e);
		return;
	}
	p[8] = 0;
	*(Rec14*) (e + 0x52) = (*(Rec14*)&g_7f4c00);
}
