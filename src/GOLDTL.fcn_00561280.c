


typedef struct {
	short w[7];
} Rec14;
// SIZE 0xe

#include "client_types.h"
extern pos14_7f4c00 g_7f4c00;

void __cdecl fcn_00500bb0(char*, int, int, int);
void __cdecl fcn_00546190(char*);

void __cdecl fcn_00561280(char* e)
{
	switch (*(int*) (e + 0x70)) {
	case 3:
		*(Rec14*) (e + 0x52) = (*(Rec14*)&g_7f4c00);
		fcn_00500bb0(e + 0x52, 0, 1, 0);
		break;
	case 9:
		fcn_00546190(e);
		break;
	}
}
