// FUNCTION: GOLD 0x4e5980
// SIZE: 179
// FUNCTION: GOLDTL 0x4e7490
// SIZE: 179

#include <string.h>

extern char g_68d8f4[];
extern char g_68d8d0[];

int __cdecl fcn_0064d41a(char*, char*, ...);

void __cdecl fcn_004e7490(char* e, char* out)
{
	unsigned int f;

	fcn_0064d41a(out, g_68d8f4, *(float*) (e + 0x10), *(float*) (e + 0x14), *(float*) (e + 0x18),
	    *(float*) (e + 0x1c), *(float*) (e + 0x20), *(int*) (e + 0x24), *(short*) (e + 0x28));
	f = *(unsigned int*) (e + 0x2c);
	fcn_0064d41a(out + strlen(out), g_68d8d0, f & 0xf, (f >> 4) & 0xf, (f >> 8) & 0xf, (f >> 12) & 3,
	    (f >> 14) & 7, (f >> 17) & 7, (f >> 20) & 7, (f >> 23) & 3, (f >> 25) & 0xf);
}
