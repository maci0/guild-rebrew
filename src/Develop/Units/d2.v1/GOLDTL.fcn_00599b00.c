#include "client_dialog_helpers.h"

/* City construction dialog ("BAUEN\\STADT_BAUEN"). Builds the category
 * list, keeps one hotkey row per building category, then runs the message
 * loop that reacts to the chosen building and to the close messages. */

extern short g_774970;
extern int g_772514;
extern int g_100f1dc;
extern int g_14ce8e0;
extern int g_7746f8;
extern int g_774654;
extern int g_1015ea0;
extern int g_10162e8;
extern int g_10162ec;
extern int g_10162f0;
extern int g_10162f4;
extern unsigned char g_773d75;
extern int g_68a2a8;
extern int g_6b5c60;
extern int g_67d370;


int __cdecl fcn_0050e4a0(int a);
int __cdecl fcn_00502cd0(int a, int b, int c, int d);
void __cdecl fcn_00471b60(int dlg);
int __cdecl fcn_0050d200(int a, int b);
int __cdecl fcn_0046f740(int a, int b, int c, int d);
int __cdecl fcn_0046fac0(int a, int b, int c, int d);
void __cdecl fcn_00472900(int a, int b);
void __cdecl fcn_0046f940(int a, int b);
int __cdecl fcn_00526070(int a, int b, int c);
int __cdecl fcn_005988b0(int a, void* b, int c, int d);
void __cdecl fcn_00455350(int a, int b, void* c);
void __cdecl fcn_00598740(void* a, int b);
void __cdecl fcn_004c5530(void* a);
void __cdecl fcn_0050bc10(int a, int b, void* c);
void __cdecl fcn_0046ed00(int a, int b, int c);
int __cdecl fcn_005373e0(int a, int b);

/* ADDRESS: GOLDTL 0x00599b00 */
void __cdecl fcn_00599b00(void)
{
	static int cats[4] = {8, 9, 10, 1};
	unsigned char* catp;
	char name[0x100];
	char key[0x40];
	int raw;
	int dlg;
	int i;
	int row;
	int ofs;
	int cat;
	int last;
	int ent;
	unsigned char* rec;
	unsigned char kind;
	char* src;
	char* dst;
	char c;

	last = -1;
	raw = fcn_0050e4a0(1);
	raw = *(int*) (raw + 0x5d);
	ent = fcn_00502cd0(raw, 2, 6, 0);
	dlg = fcn_00470820(0, 0, (char*) 0x6aa2a8);
	fcn_00471b60(dlg);
	d2_SetForm(dlg, 0);
	g_7746f8 = 1;
	i = g_772514 * 0x3cc;
	*(int*) (i + 0x10162e8) = 0x18;
	*(int*) (i + 0x10162ec) = 0x18;
	*(int*) (i + 0x10162f0) = 0x18;
	*(int*) (i + 0x10162f4) = 0x18;
	d2_SetForm(dlg, 1);
	fcn_00519190((void*) 0x17f3, dlg, (void*) 1);
	d2_SetForm(dlg, 2);
	ofs = 0;
	row = 0x40;
	for (i = 0; cats[i] != 0; i++) {
		cat = cats[i];
		rec = lpGebaeudePROT + cat;
		kind = rec[cat * 0x24c];
		if (kind != last && last != -1) {
			row += 0x50;
			ofs = 0;
		}
		fcn_0050d200((int) ((unsigned short) g_774970 * 0x21c
		    + 0x7f4ca0), cat);
		last = kind;
		raw = fcn_0046f740(ofs + 0x30, row - 0x30, cat + 0x427,
		    g_772514);
		raw *= 0x2f4;
		*(int*) (raw + 0x5c + g_1015ea0) = 1;
		*(int*) (raw + 0x1d0 + g_1015ea0) = 3;
		src = *(char**) (cat * 0x38 + 0x14a6558);
		dst = (char*) (raw + 0xcc + g_1015ea0);
		do {
			c = *src++;
			*dst++ = c;
		} while (c != 0);
		*(int*) (raw + 0x1cc + g_1015ea0) = 0x54;
		fcn_0050bc10((int) ((unsigned short) g_774970 * 0x21c
		    + 0x7f4ca0), cat, key);
		ent = fcn_0046fac0(ofs + 2, row, 0x6b5c60, g_772514);
		fcn_00472900(ent, 0x54);
		fcn_0046f940(ent, key);
		ofs += 0x60;
		*(int*) (ent * 0x2f4 + 0x18 + g_1015ea0) = 0x8c;
		*(int*) (ent * 0x2f4 + 0x6c + g_1015ea0) = 1;
	}
	for (;;) {
		if (g_100f1dc > 0x426 && g_100f1dc < 0x480) {
			i = g_100f1dc - 0x427;
			if (raw != -1) {
				*(int*) (raw * 0x2f4 + 0x38 + g_1015ea0) = 0;
				*(int*) (raw * 0x2f4 + 0x3c + g_1015ea0) = 0;
			}
			raw = g_67d370;
			ent = fcn_0050d200((int) ((unsigned short) g_774970
			    * 0x21c + 0x7f4ca0), i);
			ent = fcn_00526070(ent, *(int*) (ent + 0x14), ent);
			if (ent != 0) {
				fcn_00471af0(dlg, 1);
				i = fcn_005988b0(i, name, dlg, 0);
				if (i == 0) {
					fcn_00471af0(dlg, 1);
				} else {
					fcn_00455350(i, i + 0x4c, key);
					fcn_00598740(key, i);
					{
						int k = 0;
						dst = key;
						do {
							name[k] = *dst++;
							k++;
						} while (*(dst - 1) != 0);
					}
					fcn_004c5530(name);
					g_774654 = 1;
				}
			}
		}
		if (g_100f1dc == 3) {
			d2_SetForm(dlg, 3);
			fcn_0046ed00(0, -0x46, g_772514);
		} else if (g_100f1dc == 4) {
			d2_SetForm(dlg, 3);
			fcn_0046ed00(0, 0x46, g_772514);
		}
		if (g_14ce8e0 != 0)
			g_774654 = 1;
		if (fcn_005373e0(0x599b00, 0x657c7) == 0) {
			if (dlg != -1)
				fcn_00471e30(dlg);
			g_7746f8 = 0;
			return;
		}
	}
}
