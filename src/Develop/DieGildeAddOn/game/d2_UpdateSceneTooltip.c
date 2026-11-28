#include "Develop/DieGildeAddOn/game/client_data.h"
extern int g_100f888, g_6a99e8, g_14ce8e8, g_6772c4, d2_MouseX, d2_MouseY, d2_CurrentElementId, d2_SuppressOverlay; void __cdecl d2_DestroyForm(int); void __cdecl io_SetMouseCursorPos(int, int);
#include "Develop/Units/d2.v1/d2_gui.h"
#include "Develop/DieGildeAddOn/game/object_prototype.h"
int __cdecl d2_OpenObjektUpgradeTooltip(int);
int __cdecl d2_ShowObjectTooltip(int);
int __cdecl d2_CreateGebaeudeTooltip(int);
int __cdecl d2_ShowContactTooltip(int);
int __cdecl d2_ShowPersonTooltip(int*);
void __cdecl d2_BringFormToFront(int);
#include "Develop/DieGildeAddOn/game/game_data.h"
/* ADDRESS: GOLDTL 0x00590670 */
void __cdecl d2_UpdateSceneTooltip(void)
{
	unsigned short* p;
	unsigned short* q;
	int v3;
	int v4;
	int tooltipWindow;
	int v6;
	int v7;
	unsigned char b;
	v4 = 0;
	v6 = 0;
	p = 0;
	v3 = g_100f888;
	tooltipWindow = g_6a99e8;
	if ((v3 == -1 && *(int*) 0x6a99ec != -1)
		|| (*(int*) 0x774a24 != 0 && g_14ce8e8 == 0 && tooltipWindow != -1)) {
		d2_DestroyForm(g_6a99e8);
		g_6a99e8 = -1;
		*(int*) 0x6a99f0 = -1;
		*(int*) 0x6a99ec = -1;
		*(int*) 0x774a24 = 0;
		g_6772c4 = 1;
		io_SetMouseCursorPos(d2_MouseX, d2_MouseY);
		v3 = g_100f888;
		tooltipWindow = g_6a99e8;
	}
	v7 = 0;
	if (*(int*) &d2_HoveredSceneObject != 0 && *(int*) 0x774a24 != *(int*) &d2_HoveredSceneObject
		&& g_14ce8e8 != 0) {
		v4 = 0;
		if (*(int*) &sv_HoveredObjekt == 0) {
			v7 = *(int*) &d2_HoveredSceneObject;
		}
		else {
			v4 = *(unsigned short*) sv_HoveredObjekt;
			if (v4 == 0) {
				v7 = *(int*) &d2_HoveredSceneObject;
			}
		}
		*(int*) 0x774a24 = *(int*) &d2_HoveredSceneObject;
		*(int*) 0x6a99ec = -1;
	}
	if (v3 != -1 && v3 != *(int*) 0x6a99ec) {
		q = *(unsigned short**)&((D2_CONTROL_TL*)d2_Controls)[d2_CurrentElementId]
			.associated_object;
		if (q != 0) {
			if ((unsigned int) q >= 0x7f4ca0 && (unsigned int) q <= 0x85a09f) {
				p = q;
				if (*q == 0xffff) {
					p = 0;
				}
			}
			else if ((unsigned int) q >= (unsigned int) *(int*) &lpGebaeudeINST && (unsigned int) q < (unsigned int) (*(int*) &lpGebaeudeINST + 0xa900)) {
				v6 = *(unsigned char*) q;
				if (v6 >= 0x58) {
					v6 = 0;
				}
			}
			else if ((unsigned int) q >= (unsigned int) *(int*) &lpGebaeudePROT && (unsigned int) q < (unsigned int) (*(int*) &lpGebaeudePROT + 0xca78)) {
				v6 = ((int) q - *(int*) &lpGebaeudePROT) / 0x24d;
			}
			else if ((unsigned int) q >= (unsigned int) *(int*) &lpObjekteINST && (unsigned int) q < (unsigned int) (*(int*) &lpObjekteINST + 0x14f218)) {
				v4 = *q;
				if (v4 >= 0x2dc) {
					v4 = 0;
				}
			}
			else if ((unsigned int) q >= (unsigned int) *(int*) &lpObjektePROT && (unsigned int) q < (unsigned int) (*(int*) &lpObjektePROT + 0xb9dc)) {
				v4 = ((int) q - *(int*) &lpObjektePROT) / 0x41;
			}
		}
		else if (0xdf <= v3) {
			if (0x427 <= v3) {
				if (v3 < 0x47f) {
					v6 = v3 - 0x427;
				}
			}
			else {
				v4 = v3 - 0xdf;
			}
		}
		else if (0x427 <= v3) {
			if (v3 < 0x47f) {
				v6 = v3 - 0x427;
			}
		}
		*(int*) 0x774a24 = 0;
	}
	if (v4 != 0 || v6 != 0 || v7 != 0 || p != 0) {
		if (tooltipWindow != -1) {
			d2_DestroyForm(tooltipWindow);
			tooltipWindow = -1;
			g_6a99e8 = -1;
			*(int*) 0x6a99f0 = -1;
			v3 = g_100f888;
		}
		if (v4 != 0) {
			b = ((OBJECT_PROTOTYPE *)(*(int *) &lpObjektePROT))[v4].kind;
			if (b != 0x20 && b != 0x17 && b != 0x25 && b != 0x27) {
				tooltipWindow = d2_OpenObjektUpgradeTooltip(v4);
			}
			else {
				tooltipWindow = d2_ShowObjectTooltip(v4);
			}
			v3 = g_100f888;
			g_6a99e8 = tooltipWindow;
		}
		else if (v6 != 0) {
			tooltipWindow = d2_CreateGebaeudeTooltip(v6);
			v3 = g_100f888;
			g_6a99e8 = tooltipWindow;
		}
		else if (v7 != 0) {
			tooltipWindow = d2_ShowContactTooltip(v7);
			v3 = g_100f888;
			g_6a99e8 = tooltipWindow;
		}
		else if (p != 0) {
			tooltipWindow = d2_ShowPersonTooltip((int*) p);
			v3 = g_100f888;
			g_6a99e8 = tooltipWindow;
		}
		if (tooltipWindow == -1) {
			*(int*) 0x6a99ec = -1;
			*(int*) 0x774a24 = 0;
		}
		else {
			*(int*) 0x6a99ec = v3;
			*(int*) 0x6a99f0 = *(int*) (tooltipWindow * 700 + (unsigned long)&d2_FormPageWindows);
			if (g_14ce8e8 != 0) {
				g_6772c4 = 0;
			}
		}
	}
	if (tooltipWindow != -1) {
		d2_SuppressOverlay = 1;
		*(int*) 0x774a28 = 1;
		d2_BringFormToFront(tooltipWindow);
		return;
	}
	if (*(int*) 0x774a28 == 0) {
		return;
	}
	d2_SuppressOverlay = 0;
	*(int*) 0x774a28 = 0;
}
