#include <string.h>

#pragma intrinsic(memcpy)

float __cdecl fcn_004fc460(char* p);

/* ADDRESS: GOLDTL 0x004fb2c0 */
int __cdecl fcn_004fb2c0(void)
{
	float buf[10];
	float v;
	double d;

	v = fcn_004fc460((char*) buf);
	memcpy((void*) 0x99f5e0, buf, 40);
	d = ((double) v + *(double*) 0x6629c8) * *(float*) 0x773d54;
	if (*(float*) 0x773d4c == *(float*) 0x6628a8) {
		*(float*) 0x773d50 = (float) d;
		*(float*) 0x773d4c = (float) (d * *(double*) 0x6640f8);
	} else {
		*(float*) 0x773d50 = (float) ((d - *(float*) 0x773d50) * *(float*) 0x6628cc + *(float*) 0x773d50);
	}
	*(float*) 0x99ec14 = (float) ((*(float*) 0x773d50 - *(float*) 0x773d4c) * *(double*) 0x6653d0);
	*(int*) 0x99f590 = *(int*) 0x7f4c00;
	*(int*) 0x99f594 = *(int*) 0x7f4c04;
	*(int*) 0x99f598 = *(int*) 0x7f4c08;
	*(unsigned short*) 0x99f59c = *(unsigned short*) 0x7f4c0c;
	return (int) *(float*) 0x773d50;
}
