extern char* g_772500;
#include "Develop/Units/d2.v1/d2_gui.h"
extern int d2_ScreenHeight;
extern int g_1040494;

int __cdecl d2_AllocateElement(void);
void* __cdecl d2_GetResourceData(int);

/* ADDRESS: GOLDTL 0x004675f0 */
int __cdecl d2_CreateValueGauge(int x, int y, int barLength, int value, int maxValue, int resourceId, int flags)
{
	int id;
	char* p0;
	char* p1;
	char* p3;
	int f1;
	short f2;
	short f3;
	int m;
	int v;

	id = d2_AllocateElement();
	p1 = g_772500 + (resourceId + 1) * 0x54;
	p0 = g_772500 + resourceId * 0x54;
	p3 = g_772500 + (resourceId + 3) * 0x54;
	if (flags & 1) {
		f2 = *(short*) (p1 + 0x50);
		f3 = *(short*) (p0 + 0x50);
		m = f2 > f3 ? f2 : f3;
		f1 = *(short*) (p3 + 0x50);
		if (m <= f1)
			m = f1;
		*(int*) (((char*)&((D2_CONTROL_TL*)g_1015ea0)[id].width)) = m;
		v = barLength + *(short*) (p0 + 0x52) * 2;
		*(int*) (((char*)&((D2_CONTROL_TL*)g_1015ea0)[id].height)) = v;
	} else if (flags & 2) {
		f2 = *(short*) (p1 + 0x52);
		f3 = *(short*) (p0 + 0x52);
		m = f2 > f3 ? f2 : f3;
		f1 = *(short*) (p3 + 0x52);
		if (m <= f1)
			m = f1;
		*(int*) (((char*)&((D2_CONTROL_TL*)g_1015ea0)[id].width)) = barLength + *(short*) (p0 + 0x50) * 2;
		v = m;
		*(int*) (((char*)&((D2_CONTROL_TL*)g_1015ea0)[id].height)) = v;
	}
	*(int*) (((char*)&((D2_CONTROL_TL*)g_1015ea0)[id].kind)) = 0x45;
	*(int*) (((char*)&((D2_CONTROL_TL*)g_1015ea0)[id].value_05c)) = 1;
	*(int*) (((char*)&((D2_CONTROL_TL*)g_1015ea0)[id].x)) = x;
	*(int*) (((char*)&((D2_CONTROL_TL*)g_1015ea0)[id].y)) = y;
	*(int*) (((char*)&((D2_CONTROL_TL*)g_1015ea0)[id].value_008)) = 0;
	*(int*) (((char*)&((D2_CONTROL_TL*)g_1015ea0)[id] + 0x08c)) = value;
	*(int*) (((char*)&((D2_CONTROL_TL*)g_1015ea0)[id].payload.fields.value_094)) = maxValue;
	*(int*) (((char*)&((D2_CONTROL_TL*)g_1015ea0)[id].payload.fields.value_098)) = flags;
	*(int*) (((char*)&((D2_CONTROL_TL*)g_1015ea0)[id] + 0x090)) = value;
	*(int*) (((char*)&((D2_CONTROL_TL*)g_1015ea0)[id].payload.fields.value_09c)) = barLength;
	*(int*) (((char*)&((D2_CONTROL_TL*)g_1015ea0)[id].payload.fields.value_0a0)) = maxValue / 2;
	*(int*) (((char*)&((D2_CONTROL_TL*)g_1015ea0)[id].payload.fields.value_0a4)) = resourceId;
	*(int*) (((char*)&((D2_CONTROL_TL*)g_1015ea0)[id].clip_top)) = 0;
	*(int*) (((char*)&((D2_CONTROL_TL*)g_1015ea0)[id].clip_bottom)) = d2_ScreenHeight;
	*(int*) (((char*)&((D2_CONTROL_TL*)g_1015ea0)[id].clip_left)) = 0;
	*(int*) (((char*)&((D2_CONTROL_TL*)g_1015ea0)[id].clip_right)) = g_1040494;
	*(int*) (((char*)&((D2_CONTROL_TL*)g_1015ea0)[id].data)) = (int) d2_GetResourceData(resourceId);
	return id;
}
