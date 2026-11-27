#include "Develop/Units/d2.v1/d2_gui.h"

int __cdecl d2_MeasureTextWidth(const char* s, int a);

/* ADDRESS: GOLDTL 0x0046f940 */
void __cdecl d2_SetLabelText(int i, const char* s)
{
	const char* p;
	char* d;
	char c;

	p = s;
	d = *(char**) (((char*)&((D2_CONTROL_TL*)g_1015ea0)[i].value_088));
	do {
		c = *p++;
		*d++ = c;
	} while (c != 0);
	if (*(int*) (((char*)&((D2_CONTROL_TL*)g_1015ea0)[i].value_06c)) == 0 && *(int*) (((char*)&((D2_CONTROL_TL*)g_1015ea0)[i].value_070)) == 0) {
		*(int*) (((char*)&((D2_CONTROL_TL*)g_1015ea0)[i].width)) = d2_MeasureTextWidth(s, *(int*) (((char*)&((D2_CONTROL_TL*)g_1015ea0)[i].font)));
	}
}
