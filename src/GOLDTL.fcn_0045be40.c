// FUNCTION: GOLD 0x0045f9e0
// SIZE: 135
// FUNCTION: GOLDTL 0x45be40
// SIZE: 135

#include <string.h>

extern int g_10405cc;
extern int g_6b7fdc;
extern char g_6b89f0[];

int __cdecl fcn_0042f690(char*, int, int, char*);

void __cdecl fcn_0045be40(char* name)
{
	char buf[0x100];

	strcpy(buf, "*");
	strcat(buf, name);
	strcat(buf, ".BMP");
	fcn_0042f690(buf, g_10405cc, g_6b7fdc, g_6b89f0);
}
