#include <string.h>

extern unsigned char g_773d75;
extern double g_6640e8;

int __cdecl gm_LookupEntityRecordById(int);
int __cdecl fcn_00507b00(int);
int __cdecl fcn_0042e410(int);
int __cdecl fcn_0050dac0(short);
void __cdecl io_FormatTextBuffer(char*, int, ...);
void __cdecl fcn_004c51a0(int, int, unsigned char, int);
void __cdecl fcn_00545d40(int, int, char*, int, int, int);

/* ADDRESS: GOLDTL 0x004b6af0 */
int __cdecl fcn_004b6af0(int* a0)
{
	volatile double d;
	int* ent;
	int v;
	char buf[0x100];

	ent = (int*) gm_LookupEntityRecordById(*a0);
	if (!ent) {
		return 1;
	}
	if (fcn_00507b00(*(unsigned char*) ((char*) ent + 0x164)) == 7) {
		return 0x400;
	}
	v = 0xffff & (fcn_0042e410)(4);
	d = (double) v + 1.0;
	v = (int) ((double) fcn_0050dac0(*(short*) ent) * d * g_6640e8);
	io_FormatTextBuffer(buf, *(unsigned short*) ((char*) a0 + 4) + 0x12e7, v);
	fcn_004c51a0(*a0, -1, g_773d75, v);
	fcn_00545d40(1[ent], ent[1], buf, 0x100 < strlen(buf), 0x603, 0);
	return 0;
}
