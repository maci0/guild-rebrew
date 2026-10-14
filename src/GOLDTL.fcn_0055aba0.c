


#include "client_types.h"
extern pos14_7f4c00 g_7f4c00;

int __cdecl fcn_004c5620(int, char*);
void __cdecl fcn_00546190(char*);

void __cdecl fcn_0055aba0(char* u)
{
	if (*(int*) (u + 0x70) != -1 && *(int*) (u + 0x70) != -2) {
		if (u[0x78] & 4) {
			return;
		}
		*(pos14_7f4c00*) (u + 0x52) = g_7f4c00;
		*(int*) (u + 0x84) = fcn_004c5620(-1, u);
	} else {
		fcn_00546190(u);
	}
}
