#include <string.h>

extern char* g_772500;
extern int g_772514;
extern char* g_77255c;
extern int g_774654;
extern unsigned short g_774970;
extern int g_67d370;
extern int g_7f4c00;
extern int g_7f4c04;
extern int g_7f4c08;
extern unsigned short g_7f4c0c;
extern int g_100f1dc;
extern int g_14abc88;
extern int g_14abc90;
extern int g_14abc94;
extern int g_14ce8e0;
extern int g_666018;
extern int g_66601c;

int __cdecl fcn_00470820(int a, int b, const char* name);
void __cdecl d2_SetForm(int dialog, int slot);
void __cdecl fcn_005340f0(int screen);
void __cdecl fcn_00471b60(int dialog);
void __cdecl d2_SetOverlayAnimation(int a, int b);
void __cdecl io_AppendText(const char* text, int value);
void __cdecl fcn_00533a60(int screen, int a, int* out, int count, int b,
	int c);
void __cdecl fcn_005ca560(void* desc);
void __cdecl fcn_005ca740(int x, int y, int screen, int id, void* desc,
	int flag);
int __cdecl gm_LookupEntityRecordById(unsigned int id);
int __cdecl fcn_005463a0(int a, int b, int c);
void __cdecl fcn_00472640(int value, int flag);
char* __cdecl io_FormatTextBuffer(char* buf, int id, ...);
int __cdecl fcn_00526120(char* text, int flag);
void* __cdecl fcn_005cd440(void* desc, int a, int b, int c);
int __cdecl fcn_00525f60(void* p, int flag);
int __cdecl fcn_004c5620(int mode, int arg);
void __cdecl fcn_005100f0(int handle, int value);
void __cdecl fcn_004c54c0(int a, int b, int c, int d);
int __cdecl fcn_004c4450(int handle);
int __cdecl fcn_005373e0(int func, int id);

/* ADDRESS: GOLDTL 0x0059fa80 */
void __cdecl fcn_0059fa80(int a0, unsigned short* a1, int a2)
{
	unsigned int v3;
	unsigned int v4;
	unsigned int v11;
	int pair[2];
	int v21;
	int v22;
	int v19;
	int v5;
	int v8;
	int v9;
	int v7;
	unsigned short* v6;
	unsigned short* v10;
	unsigned int flags[20];
	char text[512];
	char buf[64];
	char title[512];
	char cmd[0x40];

	v7 = a2;
	v6 = a1;
	v3 = *(unsigned int*) &a1[2];
	v4 = *(unsigned int*) (a2 + 4);
	v8 = fcn_00470820(0, 0, "locations\\wohnsitz\\geliebte2");
	d2_SetForm(v8, 0);
	fcn_005340f0(g_772514);
	fcn_00471b60(v8);
	d2_SetOverlayAnimation(0, 0);
	d2_SetForm(v8, 1);
	io_AppendText("$C$Z$[%1N3$]", *v6);
	d2_SetForm(v8, 3);
	fcn_00533a60(g_772514, 0, pair, 2, g_14abc90, g_14abc94);
	d2_SetForm(v8, 2);
	v22 = 0x19;
	v21 = (*(int*) (g_77255c + 0xc) - (int) *(short*) (g_772500 + 0x1ebd8)) / 2;
	*(unsigned int*) cmd = (unsigned int) v6;
	*(unsigned int*) (cmd + 0x30) = 0;
	fcn_005ca560(cmd);
	fcn_005ca740(v21, v22, g_772514, 0x54, cmd, 1);
	g_100f1dc = -1;
	for (;;) {
		if (gm_LookupEntityRecordById(v3) && fcn_005463a0(1, 1, v4)) {
			v5 = 1;
			if (*(int*) (v7 + 0xbc) < g_7f4c00)
				v19 = 1;
			else
				v19 = 0;
		} else {
			v5 = 0;
			v19 = 0;
		}
		fcn_00472640(pair[1], v19);
		if (!g_14ce8e0 && v5) {
			if (g_100f1dc != -1) {
				if (g_67d370 != pair[0]) {
					if (g_67d370 == pair[1]) {
						memset(flags, 0, sizeof(flags));
						flags[1] = 0x20400;
						flags[4] = 6;
						flags[2] = g_666018;
						flags[3] = g_66601c;
						io_FormatTextBuffer(cmd, 0x1a53);
						io_FormatTextBuffer(buf, 0x1a54);
						v10 = (unsigned short*) fcn_005cd440(flags,
							g_14abc88, 0, 0);
						if (v10 != 0) {
							io_FormatTextBuffer(title, 0x1a5b, 2, *v6,
								*v10);
							if (fcn_00526120(title, 1) && (v11 = g_774970,
								fcn_00525f60((char*) (v11 * 0x21c + 0x7f4ca0), 2))) {
								*(int*) (v7 + 0xbc) = g_7f4c00;
								fcn_004c5620(3, v7);
								fcn_005100f0(*(unsigned int*) (a0 + 4),
									0xfffffffe);
								fcn_004c54c0(*(unsigned int*) &v10[2],
									*(unsigned int*) &v6[2], 0xffffffdf, 1);
								g_774654 = 1;
							}
						}
					}
				} else {
					if (*(char*) ((unsigned int) g_774970 * 0x21c + 0x7f4ca9))
						v19 = 0x1a58;
					else
						v19 = 0x1a57;
					io_FormatTextBuffer(text, v19, *v6);
					if (fcn_00526120(text, 1)) {
						*(int*) (v7 + 0x52) = g_7f4c00;
						*(unsigned int*) (v7 + 0x56) = g_7f4c04;
						*(unsigned int*) (v7 + 0x5a) = g_7f4c08;
						*(unsigned short*) (v7 + 0x5e) = g_7f4c0c;
						*(int*) (v7 + 0xbc) = g_7f4c00;
						v9 = fcn_004c5620(1, v7);
						if (v9 != -1) {
							while (!fcn_004c4450(v9))
								fcn_005373e0(0, 0x20007);
						}
						g_774654 = 1;
					}
				}
			}
		} else {
			g_774654 = 1;
		}
		if (!fcn_005373e0(0x59fa80, 0x677c7)) {
			fcn_00471e30(v8);
			return;
		}
	}
}
