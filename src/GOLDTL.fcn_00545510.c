extern int g_7749d4;
#include "client_types.h"
extern unit_77e980 g_77e980[1024];



void __cdecl fcn_00546190(char*);

void __cdecl fcn_00545510(void)
{
	int i;

	for (i = 0; i <= g_7749d4 && i < 0x400; i++) {
		if (((char*)g_77e980)[i * 0x14c] != 0) {
			fcn_00546190(((char*)g_77e980) + i * 0x14c);
		}
	}
}
