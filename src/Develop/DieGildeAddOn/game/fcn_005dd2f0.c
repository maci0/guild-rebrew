#include <string.h>

unsigned short* __cdecl fcn_005cd440(unsigned int*, char*, int, int);
int __cdecl gm_LookupEntityRecordById(int);
int __cdecl fcn_005c6270(int, int);
void __cdecl fcn_004c54c0(int, int, int, int);
void __cdecl io_FormatTextBuffer(char*, int, ...);
void __cdecl fcn_00545d40(int, int, char*, int, int, int);

/* ADDRESS: GOLDTL 0x005dd2f0 */
unsigned int __cdecl fcn_005dd2f0(int a0, int a1)
{
	unsigned int q[20];
	char buf[0x100];
	char name[0x400];
	unsigned short* v2;
	unsigned short* v3;
	int v9;
	int i;

	if (*(char*) (a0 + 2) != 6) {
		v2 = (unsigned short*) gm_LookupEntityRecordById(*(int*) (a1 + 4));
		v3 = (unsigned short*) gm_LookupEntityRecordById(*(int*) (a1 + 8));
		if (v2 == 0) {
			return 0;
		}
		if (v3 == 0) {
			return 0;
		}
	} else {
		memset(q, 0, 0x50);
		for (i = 0; i < 8; i++) {
			q[8 + i] = 0xffffffff;
		}
		io_FormatTextBuffer(buf, 0x9c);
		q[2] = *(int*) 0x666018;
		q[0] = 0;
		q[1] = 0x400;
		q[4] = 6;
		q[3] = *(int*) 0x66601c;
		v2 = fcn_005cd440(q, buf, 0, 0);
		if (v2 == 0) {
			return 0;
		}
		q[5] = 3;
		*(unsigned short*) &q[7] = *v2;
		io_FormatTextBuffer(buf, 0x9e);
		v3 = fcn_005cd440(q, buf, 0, 0);
		if (v3 == 0) {
			return 0;
		}
	}
	v9 = ((fcn_005c6270(a0, 0x2c5) != 0) + 1) * -0x28;
	fcn_004c54c0(*(unsigned int*) ((char*) v2 + 4), *(unsigned int*) ((char*) v3 + 4), v9, 1);
	fcn_004c54c0(*(unsigned int*) ((char*) v3 + 4), *(unsigned int*) ((char*) v2 + 4), v9, 1);
	if (*(char*) ((char*) v2 + 2) == 6 || *(char*) ((char*) v2 + 2) == 7) {
		io_FormatTextBuffer(name, 0xfea, *v3);
		fcn_00545d40(*(unsigned int*) ((char*) v2 + 4), -1, name, 1, 0x5fb, 0);
	}
	if (*(char*) ((char*) v3 + 2) == 6 || *(char*) ((char*) v3 + 2) == 7) {
		io_FormatTextBuffer(name, 0xfeb, *v2, *v2);
		fcn_00545d40(*(unsigned int*) ((char*) v3 + 4), -1, name, 1, 0x5fb, 0);
	}
	return 1;
}
