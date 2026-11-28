#include <string.h>
extern int g_102d028, g_102d02c, g_67d388, d2_CurrentElementId; extern char* d2_Controls;
char* __cdecl d3_FindTextureByName(char*); char __cdecl d3_PickObjectSurfaceUV(float, float, int, char*, float*, float*);
#include "Develop/Units/d2.v1/d2_gui.h"
/* ADDRESS: GOLDTL 0x0046acf0 */
/* ADDRESS: GOLDDE 0x0045e4e0 */
int __cdecl d2_HitTestRenderableForm(int screenX, int screenY, int unused2, int unused3, int unused4)
{
	char* q;
	char* name;
	char* p;
	char* obj;
	char* e;
	char* t;


	int* list;
	int i;
	int j;
	int cnt;
	int px;
	int py;
	float f1;
	float f2;

	g_102d028 = 0;
	g_102d02c = 0;
	*(char*) 0x1015d00 = 0;
	for (q = (char*) 0x10382d8; (int) q < 0x1040618; q += 0x2bc) {
		if (!*(int*) (q - 8)) {
			continue;
		}
		if (!*(int*) q) {
			continue;
		}
		if (!*(int*) (q + 4)) {
			continue;
		}
		for (i = 0; i < 2; i++) {
			if (i == 0) {
				name = q + 0x1c;
			}
			else if (i == 1) {
				name = q + 0x5c;
			}
			else {
				continue;
			}
			if (!*name) {
				continue;
			}
			obj = d3_FindTextureByName(name);
			if (!obj) {
				continue;
			}
			if (!d3_PickObjectSurfaceUV((float) screenX, (float) screenY, 0, obj, &f1, &f2)) {
				continue;
			}
			goto found;
		}
	}
	return -1;
found:
	px = (int) ((double) *(unsigned int*) (obj + 0x64) * f1);
	py = (int) ((double) *(unsigned int*) (obj + 0x64) * f2);
	if (i == 1) {
		py += 0x100;
	}
	g_102d028 = px;
	g_102d02c = py;
	strcpy((char*) 0x1015d00, obj);



	screenX = *(int*) (q - 0x14) - 1;
	p = q - 0x194 + screenX * 4;
	for (; screenX >= 0; screenX--) {
		t = (char*) 0x1015f40 + *(int*) p * 0x3cc;
		cnt = *(int*) (t + 0x2c);
		list = *(int**) (t + 0x28);
		{
			for (j = 0; j < cnt; j++) {
				obj = (char*) &((D2_CONTROL_TL*) d2_Controls)[list[j]];
				if (px < *(int*) (obj + 0x10)) {
					continue;
				}
				if (px > *(int*) (obj + 0x10) + *(int*) (obj + 0x18)) {
					continue;
				}
				if (py < *(int*) (obj + 0x14)) {
					continue;
				}
				if (py > *(int*) (obj + 0x14) + *(int*) (obj + 0x1c)) {
					continue;
				}
				if (*(int*) (obj + 0x20) == 0x40) {
					g_67d388 = *(int*) (obj + 0x88);
					continue;
				}
				d2_CurrentElementId = (*(int**) (t + 0x28))[j];
				if (*(int*) (obj + 0x40)) {
					g_67d388 = **(int**) (obj + 0x40);
				}
				return *(int*) (obj + 8);
			}
		}
		p -= 4;
	}
	d2_CurrentElementId = -1;
	return -1;
}
