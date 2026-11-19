#include "Develop/DieGildeAddOn/game/game_player.h"
extern unsigned char g_773d75;
#include "Develop/DieGildeAddOn/game/game_data.h"
extern char g_7f4ca0[];
extern char g_7f4ca4[];
extern int g_774654;
extern char g_67728c[];

typedef struct {
	int d;
	int pad4;
	unsigned char f8;
	char rest[0x213];
} Entry5aa;

int __cdecl fcn_00502cd0(int, int, int, int, int);
int __cdecl gm_WalkEntityChain(unsigned short);
int __cdecl gm_AccumulateTyped2(char*);
int __cdecl fcn_00470820(int, int, char*);
void __cdecl d2_SetOverlayAnimation(int, int);
void __cdecl fcn_00471b60(int);
void __cdecl fcn_00471e30(int);
int __cdecl fcn_00471f80(int);
int __cdecl fcn_00472250(int, int, int);
void __cdecl fcn_00472380(int, int, int, int);
void __cdecl d2_SetForm(int, int);
int __cdecl io_AppendText(int, ...);
void __cdecl fcn_005340f0(int);
void __cdecl fcn_004c5150(int, int, char, int);
void __cdecl fcn_004c54c0(int, int, int, int);
int __cdecl fcn_0050b710(int, unsigned char);
int __cdecl fcn_0050b750(int, unsigned char);
int __cdecl fcn_00526010(void*, int, unsigned char);
void __cdecl fcn_005c9030(int, int, int, int*);
int __cdecl io_FormatTextBuffer(char*, char*, ...);
int __cdecl fcn_00526120(char*, int);
int __cdecl fcn_005373e0(void*, int);
void __cdecl fcn_00532ef0(void);

/* ADDRESS: GOLDTL 0x005aaf60 */
void __cdecl fcn_005aaf60(char* a0)
{
	char buf[512];
	int dlg;
	int ok;
	int h;
	int c;
	int a;
	int b;
	float total;
	float frac;
	int m;
	int n;
	int cnt;
	int v;
	int d;
	int i;
	int off;
	float scale;

	ok = 0;
	c = -1;
	a = -1;
	b = -1;
	if (a0 == 0) {
		return;
	}
	if (*(unsigned short*) (a0 + 0x27) == 0xffff) {
		return;
	}
	if (*(unsigned short*) (a0 + 0x27) == g_774970) {
		return;
	}
	h = fcn_00502cd0(*(int*) (a0 + 0x5d), 2, 6, 0, 0xe8);
	if (h == 0) {
		return;
	}
	m = gm_WalkEntityChain(g_774970) > 1 ? gm_WalkEntityChain(g_774970) : 1;
	n = gm_WalkEntityChain(*(unsigned short*) (a0 + 0x27)) > 1
		? gm_WalkEntityChain(*(unsigned short*) (a0 + 0x27)) : 1;
	cnt = (int) ((total = (float) (m + n)) * 0.01f);
	v = gm_AccumulateTyped2((char*) (g_774970 * 0x21c + (int) g_7f4ca0));
	if (v >= cnt) {
		ok = 1;
	}
	dlg = fcn_00470820(0, 0, "Locations\\Kirche\\Spenden");
	d2_SetOverlayAnimation(0, 0);
	fcn_00471b60(dlg);
	d2_SetForm(dlg, 0);
	fcn_005340f0(d2_CurrentWindowId);
	d2_SetForm(dlg, 1);
	io_AppendText(0x1986);
	if (!ok) {
		io_AppendText(0x1987, g_774970,
			*(unsigned short*) (g_8680b4 + (unsigned char) g_773d75 * 0x2f4) * 2 + 0x9a8);
	} else {
		c = io_AppendText(0x1988, g_774970, *(unsigned short*) (a0 + 0x27), 0x48c,
			*(unsigned short*) (g_8680b4 + (unsigned char) g_773d75 * 0x2f4) * 2 + 0x9a8);
		fcn_005c9030(cnt, v, 0x20, &b);
		c = fcn_00472250(dlg, 1, c);
		fcn_00472380(c, fcn_0050b710(cnt, g_773d75), fcn_0050b710(b, g_773d75),
			fcn_0050b710(cnt, g_773d75));
		d2_SetForm(dlg, 2);
		n = io_AppendText(0x1989);
		a = fcn_00472250(dlg, 2, n);
		b = fcn_00472250(dlg, 2, n + 1);
	}
	g_100f1dc = -1;
	do {
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		}
		if (g_100f1dc != -1) {
			if (d2_CurrentElementId == a) {
				d = fcn_00471f80(c);
				d = fcn_0050b750(d, g_773d75);
				if (fcn_00526010((char*) (g_774970 * 0x21c + (int) g_7f4ca0), d,
					g_773d75) != 0) {
					fcn_004c5150(*(int*) (h + 2), *(int*) (g_774970 * 0x21c + (int) g_7f4ca4),
						g_773d75, d);
					frac = (float) (d * 255) / total;
					fcn_004c54c0(*(int*) (g_774970 * 0x21c + (int) g_7f4ca4),
						*(int*) (*(unsigned short*) (a0 + 0x27) * 0x21c + (int) g_7f4ca4), (int) frac, 1);
					scale = frac * 0.2f;
					for (i = 0; i < 0x300; i++) {
						Entry5aa* ent;
						if (i == g_774970) {
							continue;
						}
						ent = (Entry5aa*) g_7f4ca4;
						d = ent[i].d;
						if (d == -1) {
							continue;
						}
						off = *(unsigned short*) (a0 + 0x27) * 0x21c;
						if (d == *(int*) (g_7f4ca4 + off)) {
							continue;
						}
						if (*(unsigned char*) (g_7f4ca4 + off + 8) != ent[i].f8) {
							continue;
						}
						fcn_004c54c0(*(int*) (g_7f4ca4 + g_774970 * 0x21c), d, (int) scale, 1);
					}
					io_FormatTextBuffer(buf, g_67728c, 0x1986, 0x198a);
					fcn_00526120(buf, 0);
					g_774654 = 1;
				}
			} else if (d2_CurrentElementId == b) {
				g_774654 = 1;
			}
		}
	} while (fcn_005373e0((void*) fcn_005aaf60, 0x677c7) != 0);
	fcn_00471e30(dlg);
	fcn_00532ef0();
}
