int __cdecl d2_GetBankEntry(int, int);

extern char* g_1015ea0;

typedef struct
{
	char pad_00[0xc];
	int f0c;
	int f10;
	int f14;
	char pad_18[0x74];
	int f8c;
	int f90;
	int f94;
	char pad_98[4];
	int f9c;
	char pad_a0[0x254];
} SLIDER_THUMB_DEF;
// SIZE 0x2f4
#include "Develop/Units/d2.v1/d2_gui.h"
/* ADDRESS: GOLDTL 0x00467870 */
int __cdecl d2_ComputeSliderThumbPos(int idx, int* out1, int* out2)
{
	int e;
	char* lo;
	char* hi;
	int d;
	int q;
	int v;
	int r;

	e = *(int*) (&((D2_CONTROL_TL*) g_1015ea0)[idx].data);
	lo = (char*) d2_GetBankEntry(e, 0);
	d2_GetBankEntry(e, 1);
	hi = (char*) d2_GetBankEntry(e, 3);
	d = ((D2_CONTROL_TL*) g_1015ea0)[idx].payload.fields.value_094 - ((D2_CONTROL_TL*) g_1015ea0)[idx].payload.fields.value_090;
	q = ((D2_CONTROL_TL*) g_1015ea0)[idx].payload.fields.value_08c - ((D2_CONTROL_TL*) g_1015ea0)[idx].payload.fields.value_090;
	v = (int) ((float) ((D2_CONTROL_TL*) g_1015ea0)[idx].payload.fields.value_09c / d * q);
	r = v - (((unsigned short) *(short*) (hi + 2)) >> 1)
	    + (unsigned short) *(short*) (lo + 2)
	    + ((D2_CONTROL_TL*) g_1015ea0)[idx].x;
	*out1 = r;
	*out2 = ((D2_CONTROL_TL*) g_1015ea0)[idx].y;
	return 1;
}
