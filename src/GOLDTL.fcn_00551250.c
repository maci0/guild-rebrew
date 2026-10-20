#include "client_types.h"

extern pos14_7f4c00 g_7f4c00;
extern int g_7f4ca4[];
extern unsigned char g_773d75;

void __cdecl fcn_004c5150(int, int, unsigned char, int);
void __cdecl fcn_00500bb0(void*, int, int, int);
void __cdecl fcn_00546190(void*);

/* ADDRESS: GOLDTL 0x00551250 */
void __cdecl fcn_00551250(char* u)
{
	switch (*(int*) (u + 0x70)) {
	case 0:
		fcn_004c5150(-1, g_7f4ca4[*(unsigned short*) (u + 8) * 135], g_773d75,
		    *(int*) (u + 0xac));
		if (--*(int*) (u + 0xb0) == 0) {
			fcn_00546190(u);
			return;
		}
		*(pos14_7f4c00*) (u + 0x52) = g_7f4c00;
		fcn_00500bb0(u + 0x52, 0x18, 0, 0);
		break;
	case -1:
	case -2:
		fcn_00546190(u);
		break;
	}
}
