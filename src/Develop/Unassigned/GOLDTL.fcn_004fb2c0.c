#include <string.h>
extern float g_773d4c, g_773d50, g_773d54, g_99ec14;

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
	if (g_773d4c == *(float*) 0x6628a8) {
		d = ((double) v + *(double*) 0x6629c8) * g_773d54;
		g_773d50 = (float) d;
		g_773d4c = (float) (d * *(double*) 0x6640f8);
	} else {
		d = ((double) v + *(double*) 0x6629c8) * g_773d54;
		g_773d50 = (float) ((d - g_773d50) * *(float*) 0x6628cc + g_773d50);
	}
	g_99ec14 = (float) ((g_773d50 - g_773d4c) * *(double*) 0x6653d0);
	*(int*) 0x99f590 = *(int*) 0x7f4c00;
	*(int*) 0x99f594 = *(int*) 0x7f4c04;
	*(int*) 0x99f598 = *(int*) 0x7f4c08;
	*(unsigned short*) 0x99f59c = *(unsigned short*) 0x7f4c0c;
	return (int) g_773d50;
}
