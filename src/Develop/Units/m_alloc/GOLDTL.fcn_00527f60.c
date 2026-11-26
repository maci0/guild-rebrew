#include <string.h>
#include <math.h>

/*
 * Town view refresh: element teardown/rebuild plus the label texts.
 *
 * The slot record at 0x007f4ca0 holds a kind byte at +0xa2; the body only
 * runs for kind 6. a0 bit 0 tears the element cache down and rebuilds it,
 * otherwise the cached labels are refreshed with their current texts.
 *
 * Element records live in the 0x2f4-byte instance array behind
 * 0x01015ea0; the created ids are kept in the g_6a25xx globals.
 */

extern unsigned char g_slot_table[];

extern unsigned short g_774970;
extern int d2_ScreenHeight;
extern int g_1040494;
extern int g_774674;
extern int g_774678;
extern int g_77467c;
extern int g_77250c;
extern int g_14ce860;
extern int g_14ce864;
extern unsigned char g_77534c;
extern unsigned char g_77670c;
extern unsigned char g_773d75;
extern char g_6b5c60[];
extern char* g_1015ea0;
extern int g_6a2578;
extern int g_6a257c;
extern int g_6a2580;
extern int g_6a2584;
extern int g_6a2588;
extern int g_6a258c;
extern int g_6a2590;
extern int g_6a2594;
extern int g_6a2598;
extern int g_6a25a0;
extern int g_6a25a4;
extern int g_6a25a8;
extern int g_6a25ac;
extern int g_6a25fc;
extern int g_6a2be8;
extern int g_6a4768;
extern int g_6a476c;
extern unsigned char* g_7746c8;
extern int g_7746c4;
extern int g_7746f8;
extern int g_774698;
extern int g_774720;
extern int g_67d8d4;
extern int d2_CurrentElementId;
extern int g_100f1dc;
extern int d2_CurrentWindowId;
extern int g_772544;
extern int g_77e8a0;
extern int d3_ActiveCamera;

void __cdecl fcn_0047a040(int, int, int, int);
int __cdecl fcn_0047cb60(int, int, int, int);
void __cdecl d2_DestroyElement(int);
int __cdecl d2_AddElementToWindow(int, int, int, int);
int __cdecl d2_ShowTxt(int, int, char*, int);
int __cdecl fcn_00469c30(int, int, int);
int __cdecl fcn_0046fcd0(int, int, char*);
void __cdecl fcn_005279f0(int);
char* __cdecl d2_SelectFont(int);
void __cdecl fcn_00500d60(int*, char*);
int __cdecl fcn_0051e070(void);
int __cdecl fcn_004fe330(char*, int);
void __cdecl d2_DrawDefaultFontText(int, int, int, char*, int);
void* __cdecl d2_GetResourceData(int);
int __cdecl fcn_0047cba0(int, int, int, void*, int);
int __cdecl fcn_0046bd20(int, int, int, int, int, char*, int);
void __cdecl d2_SetSlotVisibility(int, int);
void __cdecl fcn_00469c40(int, int, int);
void __cdecl fcn_0046f940(int, const char*);
int __cdecl fcn_00517c00(int, int, int, char*);
char* __cdecl gm_FindPublicTreasury(int);
int __cdecl fcn_0050d270(int);
int __cdecl gm_QueryEntitySum(int, int);
int __cdecl fcn_0050b710(int, int);
int __cdecl fcn_0051af00(char*, int, ...);
int __cdecl fcn_00465950(const char*);
int __cdecl d2_SetForm(int, int);
void __cdecl fcn_0066080a(char*);

/* Element record field: 0x2f4-byte stride behind the g_1015ea0 pointer. */
#define ELEM(i) ((char*) &((D2_CONTROL_TL*) g_1015ea0)[(i)])
#define EFIELD(i, off) (*(int*) (ELEM(i) + (off)))

/*
 * The frame keeps the two scalars ahead of the text buffers; the 8 bytes at
 * 0x18 are unreferenced padding the native frame still carries, so the
 * buffers stay at 0x20/0x120/0x220.
 */
struct town_frame {
	int tmp;	/* 0x10 */
	int pos;	/* 0x14, two shorts */
	int pad0;	/* 0x18 */
	int pad1;	/* 0x1c */
	char text[0x100];	/* 0x20 */
	char name[0x100];	/* 0x120 */
	char buf[0x100];	/* 0x220 */
};
#include "Develop/Units/d2.v1/d2_gui.h"
/* ADDRESS: GOLDTL 0x00527f60 */
void __cdecl fcn_00527f60(unsigned char a0, int a1)
{
	struct town_frame fr;
	int three = 3;
	int id;
	int val;
	int si;

	if (g_slot_table[2 + g_774970 * 0x21c] != 6) {
		return;
	}
	fcn_0047a040(0, 0, g_1040494, d2_ScreenHeight);
	if (g_774674) {
		fcn_0047cb60(g_14ce860 - 0x80, 0, g_77250c, g_774674);
	}
	if (g_774678) {
		fcn_0047cb60(g_14ce860 - 0x100, g_14ce864 - 0x80, g_77250c,
			     g_774678);
	}
	if (g_77467c) {
		fcn_0047cb60(*(int*) (0x6a24d8 + g_77534c * 4), 0, g_77250c,
			     g_77467c);
	}

	if (a0 & 1) {
		if (g_6a2578 != -1) {
			d2_DestroyElement(g_6a2578);
			g_6a2578 = -1;
		}
		if (g_6a257c != -1) {
			d2_DestroyElement(g_6a257c);
			g_6a257c = -1;
		}
		if (g_6a2580 != -1) {
			d2_DestroyElement(g_6a2580);
			g_6a2580 = -1;
		}
		if (g_6a25a0 != -1) {
			d2_DestroyElement(g_6a25a0);
			g_6a25a0 = -1;
		}
		if (g_6a25a4 != -1) {
			d2_DestroyElement(g_6a25a4);
			g_6a25a4 = -1;
		}
		if (g_6a2584 != -1) {
			d2_DestroyElement(g_6a2584);
			g_6a2584 = -1;
		}
		if (g_6a2588 != -1) {
			d2_DestroyElement(g_6a2588);
			g_6a2588 = -1;
		}
		if (g_6a258c != -1) {
			d2_DestroyElement(g_6a258c);
			g_6a258c = -1;
		}
		if (g_6a2590 != -1) {
			d2_DestroyElement(g_6a2590);
			g_6a2590 = -1;
		}
		if (g_6a2594 != -1) {
			d2_DestroyElement(g_6a2594);
			g_6a2594 = -1;
		}

		g_6a2578 = d2_AddElementToWindow(
			0x10, 8, *(int*) (g_slot_table + 0x54
					  + g_774970 * 0x21c), g_6a2598);
		((D2_CONTROL_TL*) g_1015ea0)[g_6a2578].flags_1d0 = 0x43;
		((D2_CONTROL_TL*) g_1015ea0)[g_6a2578].value_05c = 1;

		g_6a257c = d2_AddElementToWindow(0x23a, 0xd, 0x522, g_6a2598);
		((D2_CONTROL_TL*) g_1015ea0)[g_6a257c].flags_1d0 = 0x43;
		((D2_CONTROL_TL*) g_1015ea0)[g_6a257c].value_05c = 1;

		g_6a25a0 = d2_ShowTxt(0x39, 0xd, g_6b5c60, g_6a2598);
		((D2_CONTROL_TL*) g_1015ea0)[g_6a25a0].flags_1d0 = 0x43;
		((D2_CONTROL_TL*) g_1015ea0)[g_6a25a0].value_05c = 1;
		((D2_CONTROL_TL*) g_1015ea0)[g_6a25a0].font = 0x55;

		g_6a2588 = fcn_00469c30((short) (g_1040494 - 0x8d),
					(short) (d2_ScreenHeight - 0x73), 0x583);
		((D2_CONTROL_TL*) g_1015ea0)[g_6a2588].flags_1d0 = 0x43;
		((D2_CONTROL_TL*) g_1015ea0)[g_6a2588].value_05c = 1;

		g_6a258c = fcn_00469c30((short) (g_1040494 - 0x57),
					(short) (d2_ScreenHeight - 0x4f), 0x7d9);
		((D2_CONTROL_TL*) g_1015ea0)[g_6a258c].flags_1d0 = three;
		((D2_CONTROL_TL*) g_1015ea0)[g_6a258c].value_05c = 1;

		g_6a2584 = fcn_00469c30((short) (g_1040494 - 0x2a),
					(short) (d2_ScreenHeight - 0x66), 0x584);
		((D2_CONTROL_TL*) g_1015ea0)[g_6a2584].flags_1d0 = 0x43;
		((D2_CONTROL_TL*) g_1015ea0)[g_6a2584].value_05c = 1;

		g_6a2590 = fcn_00469c30((short) (g_1040494 - 0x4a), 0xd6,
					0x585);
		((D2_CONTROL_TL*) g_1015ea0)[g_6a2590].flags_1d0 = 0x43;
		((D2_CONTROL_TL*) g_1015ea0)[g_6a2590].value_05c = 1;

		g_6a2594 = fcn_00469c30((short) (g_1040494 - 0x48), 0xd7,
					0x551);
		((D2_CONTROL_TL*) g_1015ea0)[g_6a2594].flags_1d0 = 0x43;
		((D2_CONTROL_TL*) g_1015ea0)[g_6a2594].value_05c = 1;
		((D2_CONTROL_TL*) g_1015ea0)[g_6a2594].kind = 8;

		g_6a25a4 = fcn_0046fcd0((short) (g_1040494 - 0x6a),
					(short) (d2_ScreenHeight - 0x7e),
					g_6b5c60);
		((D2_CONTROL_TL*) g_1015ea0)[g_6a25a4].value_06c = 1;
		((D2_CONTROL_TL*) g_1015ea0)[g_6a25a4].font = 0x54;
		((D2_CONTROL_TL*) g_1015ea0)[g_6a25a4].width = 0x6b;
		((D2_CONTROL_TL*) g_1015ea0)[g_6a25a4].height = 0x20;
	} else if (g_77670c) {
		if (g_6a2578 != -1) {
			strcpy(ELEM(g_6a2578) + 0xcc, *(char**) 0x14ad034);
		}
		if (g_6a257c != -1) {
			strcpy(ELEM(g_6a257c) + 0xcc, *(char**) 0x14ad040);
		}
		if (g_6a25a0 != -1) {
			strcpy(ELEM(g_6a25a0) + 0xcc, *(char**) 0x14ad030);
		}
		if (g_6a2588 != -1) {
			strcpy(ELEM(g_6a2588) + 0xcc, *(char**) 0x14ad02c);
		}
		if (g_6a2584 != -1) {
			strcpy(ELEM(g_6a2584) + 0xcc, *(char**) 0x14ad028);
		}
		if (g_6a2594 != -1) {
			strcpy(ELEM(g_6a2594) + 0xcc, *(char**) 0x14ad038);
		}
	} else {
		if (g_6a2578 != -1) {
			*(ELEM(g_6a2578) + 0xcc) = *g_6b5c60;
		}
		if (g_6a257c != -1) {
			*(ELEM(g_6a257c) + 0xcc) = *g_6b5c60;
		}
		if (g_6a25a0 != -1) {
			*(ELEM(g_6a25a0) + 0xcc) = *g_6b5c60;
		}
		if (g_6a2588 != -1) {
			*(ELEM(g_6a2588) + 0xcc) = *g_6b5c60;
		}
		if (g_6a2584 != -1) {
			*(ELEM(g_6a2584) + 0xcc) = *g_6b5c60;
		}
		if (g_6a2594 != -1) {
			*(ELEM(g_6a2594) + 0xcc) = *g_6b5c60;
		}
	}

	fcn_005279f0(a1);
	d2_SelectFont(0x55);
	fcn_00500d60((int*) 0x7f4c00, (char*) &fr.pos);
	if (fcn_0051e070() == 2) {
		sprintf(fr.text, (char*) 0x6a2e5c,
			*(int*) (0x14a5450
				 + fcn_004fe330((char*) &fr.pos,
						*(short*) ((char*) &fr.pos + 2))
					 * 4));
		d2_DrawDefaultFontText(*(int*) (0x1015f44 + g_6a2598 * 0x3cc) + 0x181,
			     0x17, g_77250c, fr.text, 0);
	} else {
		sprintf(fr.text, (char*) 0x6a2e5c,
			*(int*) (0x14a5450
				 + fcn_004fe330((char*) &fr.pos,
						*(short*) ((char*) &fr.pos + 2))
					 * 4));
		d2_DrawDefaultFontText(*(int*) (0x1015f44 + g_6a2598 * 0x3cc) + 0x195,
			     0x17, g_77250c, fr.text, 0);
	}

	fr.tmp = *(int*) 0x7f4c06 % 0x3c;
	fcn_0047cba0(g_1040494 - 0x50, 0x11, g_77250c,
		     d2_GetResourceData(0x581),
		     (int) (fr.tmp * *(double*) 0x664108));

	fr.tmp = (*(int*) 0x7f4c04 & 0xffff) * 0x3c + *(int*) 0x7f4c06;
	fcn_0047cba0(g_1040494 - 0x50, 0x11, g_77250c,
		     d2_GetResourceData(0x582),
		     (int) (fr.tmp * *(double*) 0x662ad0
			    * *(double*) 0x665dd0) % 0x30);

	if (g_67d8d4 == g_6a25a8) {
		sprintf(fr.text, (char*) 0x6a2e50, *(int*) 0x7f4c04 & 0xffff,
			*(int*) 0x7f4c06);
		d2_SelectFont(0x54);
		fcn_0046bd20(g_1040494 - 0x50, 2, 0x2e, 0x14, g_77250c,
			     fr.text, 0x28);
		d2_SelectFont(0x55);
	}

	if (g_7746c8 == 0 && g_7746c4 == 0 && g_6a2594 != -1) {
		if (g_6a2590 != -1) {
			d2_SetSlotVisibility(g_6a2590, 0);
			d2_SetSlotVisibility(g_6a2594, 1);
			((D2_CONTROL_TL*) g_1015ea0)[g_6a2594].value_088 =
				(int) (fmod((double) *(float*) (d3_ActiveCamera + 0x88),
					    *(double*) 0x662958)
				       * *(float*) 0x665dc8
				       * *(double*) 0x665dc0
				       + *(double*) 0x665db8) % 0x30;
			goto hidden;
		}
	} else if (g_6a2590 != -1) {
		d2_SetSlotVisibility(g_6a2590, 1);
	}
	if (g_6a2594 != -1) {
		d2_SetSlotVisibility(g_6a2594, 0);
	}
hidden:
	d2_SelectFont(0x55);

	if (g_6a25a0 != -1) {
		fcn_00517c00(g_774970, 1, 2, fr.name);
		strcpy(fr.text, fr.name);
		fcn_0046f940(g_6a25a0, fr.text);
	}
	sprintf(fr.text, (char*) 0x67d444,
		*(int*) (0x7f4e34 + g_774970 * 0x21c));
	d2_DrawDefaultFontText(*(int*) (0x1015f44 + g_6a2598 * 0x3cc) + 0x23a, 0x17,
		     g_77250c, fr.text, 0);
	if (g_6a257c != -1) {
		fcn_00469c40(*(int*) (0x1015f44 + g_6a2598 * 0x3cc)
			     + g_772544 + 0x23d, 0x18, g_6a257c);
	}

	if (g_7746c4 != 0 || g_7746c8 != 0) {
		if (g_6a2580 != -1) {
			d2_DestroyElement(g_6a2580);
			g_6a2580 = -1;
		}
	} else {
		if (g_6a2580 == -1) {
			strcpy(fr.name, (char*) (0x868060 + g_773d75 * 0x2f4));
			fcn_0066080a(fr.name);
			sprintf(fr.buf, (char*) 0x6a2e38, fr.name);
			id = fcn_00465950(fr.buf);
			if (id != -1) {
				g_6a2580 = fcn_00469c30(
					(short) (g_1040494 - 0x6e), 0x5b, id);
			} else {
				g_6a2580 = fcn_00469c30(
					(short) (g_1040494 - 0x6e), 0x5b, 0x5b1);
			}
			((D2_CONTROL_TL*) g_1015ea0)[g_6a2580].flags_1d0 = 0x43;
			((D2_CONTROL_TL*) g_1015ea0)[g_6a2580].value_05c = 1;
		}
		if (g_77670c) {
			if (g_6a2580 != -1) {
				strcpy(ELEM(g_6a2580) + 0xcc,
				       *(char**) 0x14ad03c);
			}
		} else if (g_6a2580 != -1) {
			*(ELEM(g_6a2580) + 0xcc) = *g_6b5c60;
		}
		d2_SelectFont(0x56);
		strcpy(fr.name, (char*) (0x868080 + g_773d75 * 0x2f4));
		fcn_0046bd20(g_1040494 - 0x70, 0x5d, 0x68, 0x14, g_77250c,
			     fr.name, 8);
	}
	d2_SelectFont(0x54);

	if (g_7746f8 == 0) {
		if (g_7746c8 != 0 && *g_7746c8 == 'G') {
			si = *(int*) (g_7746c8 + 0x65);
		} else {
			si = g_773d75;
		}
		val = gm_QueryEntitySum(
			      *(int*) (0x7f4e18 + g_774970 * 0x21c), si)
			+ g_774698;
	} else {
		val = fcn_0050d270(*(int*) (gm_FindPublicTreasury(g_7746f8) + 0x14))
			+ g_774698;
		si = g_773d75;
	}
	if (g_6a25a4 != -1) {
		if (val != 0) {
			fr.tmp = fcn_0050b710(val, si);
			fcn_0051af00(fr.text, (int) 0x6a2e48,
				     (int) (double) fr.tmp, si);
			fcn_0046f940(g_6a25a4, fr.text);
		} else {
			fcn_0046f940(g_6a25a4,
				     (char*) *(int*) 0x14acf20);
		}
	}

	if (g_6a2578 != -1) {
		if (((D2_CONTROL_TL*) g_1015ea0)[g_6a2578].value_008
		    != *(int*) (g_slot_table + 0x54 + g_774970 * 0x21c)) {
			d2_DestroyElement(g_6a2578);
			g_6a2578 = -1;
			g_6a2578 = d2_AddElementToWindow(
				0x10, 8,
				*(int*) (g_slot_table + 0x54
					 + g_774970 * 0x21c),
				g_6a2598);
			((D2_CONTROL_TL*) g_1015ea0)[g_6a2578].flags_1d0 = three;
			((D2_CONTROL_TL*) g_1015ea0)[g_6a2578].value_05c = 1;
		}
	}
	if (g_6a476c < 0) {
		return;
	}
	if (g_6a4768 > three) {
		d2_SetSlotVisibility(g_6a25fc, 1);
		val = g_774720;
	} else {
		d2_SetSlotVisibility(g_6a25fc, 0);
		g_774720 = 0;
		val = 0;
	}
	if (g_100f1dc != -1 && d2_CurrentElementId == g_6a25fc) {
		val = (val == 0);
		g_774720 = val;
	}
	if (g_6a2be8 == g_6a4768
	    && (g_100f1dc == -1 || d2_CurrentElementId != g_6a25fc)) {
		goto stored;
	}
	if (val) {
		d2_SetForm(g_77e8a0, 0);
		fcn_00469c40(g_1040494 - g_6a4768 * 0x20 - 0x1d,
			     *(int*) (0x1015f48 + d2_CurrentWindowId * 0x3cc),
			     *(int*) (0x10161bc + d2_CurrentWindowId * 0x3cc));
		fcn_00469c40(g_1040494 - g_6a4768 * 0x20 - 0x4d,
			     d2_ScreenHeight - 0x21, g_6a25fc);
	} else {
		d2_SetForm(g_77e8a0, 0);
		fcn_00469c40(g_1040494 - 0x7d,
			     *(int*) (0x1015f48 + d2_CurrentWindowId * 0x3cc),
			     *(int*) (0x10161bc + d2_CurrentWindowId * 0x3cc));
		fcn_00469c40(g_1040494 - 0xad, d2_ScreenHeight - 0x21, g_6a25fc);
	}
stored:
	g_6a2be8 = g_6a4768;
	if (g_774720) {
		fcn_0047a040(0, 0, g_1040494 - 0x8c, d2_ScreenHeight);
		fcn_0047cba0(g_1040494 - g_6a4768 * 0x20 - 0x37,
			     d2_ScreenHeight - 0x37, g_77250c,
			     d2_GetResourceData(g_6a25ac + 3), 0);
		fcn_0047a040(0, 0, g_1040494, d2_ScreenHeight);
	}
}
