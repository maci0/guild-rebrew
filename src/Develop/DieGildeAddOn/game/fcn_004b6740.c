#include <string.h>

extern unsigned char g_773d75;
extern double g_662a48;
extern double g_6640e8;

int __cdecl fcn_00508e40(int);
int __cdecl fcn_0042e410(int);
int __cdecl fcn_0050dac0(short);
void __cdecl fcn_0051af00(char*, int, ...);
void __cdecl fcn_004c51a0(int, int, unsigned char, int);
void __cdecl fcn_00545d40(int, int, char*, int, int, int);

/* ADDRESS: GOLDTL 0x004b6740 */
int __cdecl fcn_004b6740(int* a0)
{
	char buf[0x100];
	int* ent;
	int v;
	int w;
	double d;

	ent = (int*) fcn_00508e40(*a0);
	if (ent == 0)
		return 1;
	if (*(unsigned char*) ((char*) ent + 0x166) == 0xe)
		return 0x400;
	v = fcn_0042e410(3) & 0xffff;
	d = (double) v + g_662a48;
	w = fcn_0050dac0(*(short*) ent);
	v = (int) (((double) w * d) * g_6640e8);
	fcn_0051af00(buf, *(unsigned short*) ((char*) a0 + 4) + 0x12e7, v);
	fcn_004c51a0(*a0, -1, g_773d75, v);
	fcn_00545d40(ent[1], ent[1], buf, 0x100 < strlen(buf), 0x603, 0);
	return 0;
}
