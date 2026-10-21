/*
 * Client frame loop: window/render setup, the main round loop and shutdown.
 *
 * Reconstructed from 0x5438c0..0x54474b. The body tail-jumps into the
 * shutdown path at 0x53fa80.
 */

#include <string.h>

__declspec(dllimport) void __stdcall Sleep(unsigned long);
__declspec(dllimport) void* __stdcall LoadLibraryA(const char*);
__declspec(dllimport) void* __stdcall GetProcAddress(void*, const char*);
__declspec(dllimport) int __stdcall FreeLibrary(void*);

extern unsigned char g_7747b0;		/* 0x007747b0 */
extern int g_7e2500;			/* 0x007e2500 */
extern int g_7e46ac;			/* 0x007e46ac */
extern char* g_14ac5cc;			/* 0x014ac5cc */
extern char* g_14ac5d0;			/* 0x014ac5d0 */
extern int g_14ac5d4;			/* 0x014ac5d4 */
extern int g_14a54d4;			/* 0x014a54d4 */
extern int g_14a54d0;			/* 0x014a54d0 */
extern char* g_14ac630;			/* 0x014ac630 */
extern int g_7747e0;			/* 0x007747e0 */
extern int g_14cbca0;			/* 0x014cbca0 */
extern unsigned char g_77670a;		/* 0x0077670a */
extern int g_7747b4;			/* 0x007747b4 */
extern int g_7e4314;			/* 0x007e4314 */
extern int g_7e2510;			/* 0x007e2510 */
extern int g_7725c8;			/* 0x007725c8 */
extern int g_774958;			/* 0x00774958 */
extern int g_774954;			/* 0x00774954 */
extern int g_77497c;			/* 0x0077497c */
extern int g_774950;			/* 0x00774950 */
extern int g_774948;			/* 0x00774948 */
extern unsigned short g_774970;		/* 0x00774970 */
extern unsigned char g_77494c;		/* 0x0077494c */
extern unsigned char g_773de8;		/* 0x00773de8 */
extern unsigned char g_773d75;		/* 0x00773d75 */
extern int g_6a342c;			/* 0x006a342c */
extern int g_6a3764;			/* 0x006a3764 */
extern int g_6a3768;			/* 0x006a3768 */
extern int g_6a376c;			/* 0x006a376c */
extern int g_6a3770;			/* 0x006a3770 */
extern int g_1040490;			/* 0x01040490 */
extern int g_1040494;			/* 0x01040494 */
extern int g_10432a4;			/* 0x010432a4 */
extern int g_10421a0;			/* 0x010421a0 */
extern int g_10529c8;			/* 0x010529c8 */
extern int g_7747f8;			/* 0x007747f8 */
extern int g_7747fc;			/* 0x007747fc */
extern int g_7f3a30;			/* 0x007f3a30 */
extern int g_7f3a34;			/* 0x007f3a34 */
extern int g_774670;			/* 0x00774670 */
extern int g_774960;			/* 0x00774960 */
extern int g_fb5744;			/* 0x00fb5744 */
extern int g_68a9dc;			/* 0x0068a9dc */
extern int g_7e1d40;			/* 0x007e1d40 */

extern char g_7e1be0[];			/* 0x007e1be0 */
extern char g_68d714[];			/* 0x0068d714 */
extern char g_6a44f4[];			/* 0x006a44f4 */
extern char g_7e2520[];			/* 0x007e2520 */
extern char g_6a3778[];			/* 0x006a3778 */
extern char g_6a44e8[];			/* 0x006a44e8 */
extern char g_7e1d00[];			/* 0x007e1d00 */
extern char g_6a44c8[];			/* 0x006a44c8 */
extern char g_6a3448[];			/* 0x006a3448 */
extern char g_6a44a8[];			/* 0x006a44a8 */
extern char g_6750e8[];			/* 0x006750e8 */
extern char g_6790b0[];			/* 0x006790b0 */
extern char g_67d940[];			/* 0x0067d940 */
extern char g_6a4498[];			/* 0x006a4498 */
extern char g_6a4470[];			/* 0x006a4470 */
extern char g_6a448c[];			/* 0x006a448c */
extern char g_6b5c60[];			/* 0x006b5c60 */
extern char g_6a4420[];			/* 0x006a4420 */
extern char g_6a43d0[];			/* 0x006a43d0 */
extern char g_7e254a[];			/* 0x007e254a */
extern char g_7e21a0[];			/* 0x007e21a0 */
extern char g_7e2000[];			/* 0x007e2000 */
extern char g_6a33dc[];			/* 0x006a33dc */
extern char g_7f4c00[];			/* 0x007f4c00 */

void __cdecl srv_InitBuildingTypeTable(void);
void __cdecl fcn_004b20d0(int);
int __cdecl fcn_005435d0(void);
void __cdecl fcn_0051af00(void*, int);
int __cdecl fcn_00526120(void*, int);
void __cdecl fcn_0046ac30(void);
int __cdecl fcn_00470820(int, int, const char*);
void __cdecl fcn_00471b60(int);
int __cdecl fcn_00519190(int);
int __cdecl fcn_005373e0(void*, int);
void __cdecl fcn_00471e30(int);
void __cdecl fcn_00402220(int);
void __cdecl fcn_00420db0(int, int);
void __cdecl fcn_004c3d50(void);
int __cdecl fcn_005926f0(void);
void __cdecl fcn_0053f4c0(void);
void __cdecl fcn_004727a0(int, int);
void __cdecl fcn_0053f630(int, int);
void __cdecl fcn_005356e0(void);
void __cdecl fcn_0053f920(void);
void __cdecl fcn_005435e0(void);
void __cdecl fcn_0053fa80(void);
void __cdecl fcn_0053f720(void);
void __cdecl fcn_00538220(void);
void __cdecl fcn_00512500(void);
void __cdecl fcn_00514b50(unsigned char);
void __cdecl init_LocalData(void);
void __cdecl fcn_00515340(unsigned char);
void __cdecl fcn_005153f0(void);
int __cdecl fcn_00521920(void*, int);
void __cdecl fcn_0052a890(void*);
int __cdecl fcn_0052a310(void*);
void __cdecl fcn_0052a3a0(void*, int);
void __cdecl fcn_00516f60(void);
void __cdecl fcn_00528fd0(void);
void __cdecl fcn_00540020(void);
int __cdecl fcn_004c5790(int, void*);
int __cdecl fcn_004c4450(int);
void __cdecl fcn_00535960(void);
void __cdecl fcn_00535770(int);
void __cdecl fcn_004c44a0(void);
void __cdecl fcn_004c44b0(void);
int __cdecl fcn_004c44c0(void);
void __cdecl fcn_005490e0(void);
void __cdecl fcn_00549130(void);
void __cdecl fcn_00549240(void);
void __cdecl fcn_005491c0(void);
void __cdecl fcn_005459a0(int);
void __cdecl fcn_0059a340(void);
void __cdecl fcn_0042df30(void*, int);
void __cdecl fcn_00500bb0(void*, int, int, int);
void __cdecl fcn_00500c50(void*, int, int, int);
int __cdecl fcn_004c5700(void*);
void __cdecl fcn_00541620(void);
int __cdecl fcn_004e9ee0(void);
void __cdecl fcn_004ea350(void);
int __cdecl fcn_004c5980(void*);
void __cdecl fcn_00543080(void);
void __cdecl fcn_004c5150(int, int, int, int);
int __cdecl fcn_0050b750(int, int);
void __cdecl fcn_00514a20(void*);
void __cdecl fcn_005145a0(void*);
int __cdecl fcn_0064d41a(char*, const char*, ...);
void* __cdecl fcn_0064e2f9(char*, const char*);
int __cdecl fcn_0064e48f(void*, int, int);
int __cdecl fcn_0064e30c(void*);
void __cdecl fcn_0064ebe4(void*, int, int, void*);
void __cdecl fcn_0064ed28(void*, int, int, void*);
void __cdecl fcn_0064e1fd(void*);
void* __cdecl m_alloc(int, const char*);
void __cdecl m_FreeTracked(void*);
void __cdecl fcn_005e3fa0(char*);
void __cdecl fcn_0051e080(char*, char*, int);
void __cdecl fcn_005bd820(void);
void __cdecl fcn_00592630(void);
void __cdecl fcn_00514f10(void);
void __cdecl fcn_00514fc0(void);
void __cdecl fcn_005e2510(void);
void __cdecl fcn_00438da0(float, float, float, float, int, int, int, int, int);
int __cdecl fcn_00504e70(int);
int __cdecl fcn_00501510(int);
void __cdecl fcn_00510c90(int);
void __cdecl fcn_005110d0(int);
void __cdecl fcn_00526920(void*, int, void*);
void __cdecl fcn_004c5530(void*);
void* __cdecl fcn_00527000(void);
void __cdecl fcn_00526db0(void*);
void __cdecl fcn_004432d0(int, int);
void __cdecl fcn_0053fc80(void);

/* Rectangle-plus-handle records exchanged with the town view. */
typedef struct {
	int x;
	int y;
	int w;
	short h;
} SyncRect;

/* ADDRESS: GOLDTL 0x005438c0 */
void __cdecl fcn_005438c0(int a0)
{
	SyncRect r1;
	SyncRect r2;
	SyncRect r3;
	unsigned char buf[0xf8];
	unsigned char msg[0x114];
	char name[0x104];
	char path[0x104];
	int h;
	int n;
	int x;
	int p;
	int c;
	unsigned short count;
	void* fp;
	void* base;
	void* proc;

	if ((g_7747b0 & 1) && (a0 == 0)) {
		srv_InitBuildingTypeTable();
	}
	g_7e2500 = 0;
	if (g_7747b0 & 4) {
		h = -1;
		fcn_004b20d0(0);
		if (g_7747b0 & 0x10) {
			if (fcn_005435d0() == 1) {
				g_7e2500 = (int) LoadLibraryA(g_7e1be0);
				if (g_7e2500 == 0) {
					g_7e46ac = 0x66087;
					fcn_00526120(g_14ac5cc, 0x100);
					g_774958 = 0;
					g_774954 = 1;
					return;
				}
				h = fcn_00470820(0, 0, g_68d714);
				fcn_00471b60(h);
				fcn_00519190(0x3ff6);
				fcn_005373e0(0, 0x24087);
				proc = GetProcAddress((void*) g_7e2500, g_6a44f4);
				if (proc == 0) {
					FreeLibrary((void*) g_7e2500);
					g_7e2500 = 0;
					g_7e46ac = 0x66087;
					fcn_00471e30(h);
					fcn_00526120(g_14ac5cc, 0x100);
					g_774958 = 0;
					g_774954 = 1;
					return;
				}
				if (((int (__cdecl*) (int)) proc)((int) g_7e2520) == 0) {
					FreeLibrary((void*) g_7e2500);
					g_7e2500 = 0;
					g_7e46ac = 0x66087;
					fcn_00471e30(h);
					fcn_00526120(g_14ac5cc, 0x100);
					g_774958 = 0;
					g_774954 = 1;
					return;
				}
				Sleep(0x9c4);
				fcn_00402220(0x3039);
				g_77497c = 1;
			} else {
				for (;;) {
					g_7e46ac = 0x24087;
					fcn_0051af00(buf, 0x79);
					if (fcn_00526120(buf, 1) == 0) {
						break;
					}
					fcn_0046ac30();
					Sleep(1000);
				}
				g_774958 = 0;
				g_774954 = 1;
				return;
			}
		}
		fcn_00420db0((int) g_7e2000, g_7e2510);
		fcn_00471e30(h);
	} else {
		fcn_00420db0(0, 0);
		if (fcn_005435d0() != 1) {
			for (;;) {
				g_7725c8 = 0;
				g_7e46ac = 0x24087;
				fcn_0051af00(buf, 0x79);
				if (fcn_00526120(buf, 1) == 0) {
					break;
				}
				g_7725c8 = 1;
				fcn_0046ac30();
				Sleep(1000);
			}
			g_774958 = 0;
			g_774954 = 1;
			return;
		}
	}
	fcn_004c3d50();
	if (g_7747b0 & 0x44) {
		g_7725c8 = 0;
		if (fcn_005926f0() != 0) {
			if (g_7e2500 != 0) {
				Sleep(1000);
				FreeLibrary((void*) g_7e2500);
				g_7e2500 = 0;
			}
			g_774958 = 0;
			g_774954 = 1;
			return;
		}
	}
	g_7725c8 = 1;
	fcn_0053f4c0();
	fcn_004727a0(g_7e1d40, 1);
	if (g_7747b0 & 4) {
		n = g_14ac5d4;
	} else {
		n = g_14a54d4;
	}
	fcn_0053f630(n, 5);
	fcn_005356e0();
	fcn_0053f630(g_14a54d0, 5);
	fcn_0053f920();
	if ((g_7747b0 & 1) && (g_7747e0 != 0)) {
		fcn_005435e0();
	}
	fcn_0053f630(0, 10);
	if (g_7747b0 & 0x41) {
		if (g_7747b0 & 4) {
			if (g_14cbca0 == -1) {
				fcn_00526120(g_14ac5d0, 0);
				fcn_0053fa80();
				fcn_0053f720();
				return;
			}
			if (g_7747b0 & 0x40) {
				fcn_00514a20(g_7e254a);
			} else {
				fcn_005145a0(g_7e21a0);
			}
			g_7747b4 = 2;
		} else {
			fcn_0064d41a(name, g_6a44e8, g_6a3778, g_7e1d00);
			if (fcn_00521920(name, 2) == 0) {
				fcn_00538220();
				return;
			}
			fcn_005435e0();
			fcn_00514b50(g_773d75);
			init_LocalData();
			fcn_00515340(g_773d75);
			fcn_0053f630(0, 100);
			fcn_0053f630(0, 100);
			if (g_7747f8 != 0) {
				fcn_005153f0();
			}
		}
	} else if (g_7747b0 & 0x40) {
		g_7747b4 = 2;
		if (g_14cbca0 == -1) {
			fcn_00526120(g_14ac5d0, 0);
			fcn_0053fa80();
			fcn_0053f720();
			return;
		}
		fcn_00514a20(g_7e21a0);
	} else if (g_7747b0 & 2) {
		g_7747b4 = g_77670a;
		if (fcn_00521920(g_7e21a0, 1) == 0) {
			g_7e46ac = 0x46086;
			fcn_00526120(g_14ac630, 0);
			g_774954 = 1;
			fcn_0053fa80();
			fcn_0053f720();
			return;
		}
		fcn_0052a890(g_7f4c00);
		g_7e4314 = fcn_0052a310(g_7f4c00);
	}
	fcn_00512500();
	if (g_7747b0 & 1) {
		if (!(g_7747b0 & 4)) {
			r3.x = 0;
			fcn_00500c50(&r3, 6, 0, 0);
			x = fcn_004c5790(3, &r3);
			while (fcn_004c4450(x) == 0) {
				fcn_00535960();
			}
			if (g_7747fc != 0) {
				n = 750000;
			} else {
				n = (5 - g_7747b4) * 250;
			}
			p = 0x7f4ca2;
			do {
				if ((*(char*) (p + 6) != 0) &&
				    ((*(char*) p == 6) || (*(char*) p == 7))) {
					c = fcn_0050b750(n, g_773d75);
					fcn_004c5150(c, g_773d75, -1, *(int*) (p + 2));
				}
				p += 0x21c;
			} while (p < 0x85a0a2);
		}
		if (g_7747b0 & 1) {
			fcn_004b1e60();
		}
	}
	fcn_005356e0();
	fcn_005bd820();
	fcn_005356e0();
	fcn_0053f720();
	g_7725c8 = 0;
	fcn_00526db0(fcn_00527000());
	fcn_004432d0(0, 0);
	if ((g_7747b0 & 1) && (!(g_7747b0 & 0x40))) {
		fcn_00514f10();
		fcn_00514fc0();
		fcn_00592630();
	}
	fcn_005e2510();
	fcn_00438da0((float) (g_6a376c - g_6a3764),
	    (float) (g_6a3770 - g_6a3768), (float) g_6a3764,
	    (float) g_6a3768, g_10529c8, g_10421a0, g_10432a4,
	    g_1040494, g_1040490);
	if (g_7747b0 & 2) {
		fcn_0052a3a0(g_7f4c00, 0);
		if (g_7f3a30 != -1) {
			base = (void*) fcn_00504e70(g_7f3a30);
			x = fcn_00501510(g_7f3a34);
			g_774670 = 2;
			if ((base != 0) && (x != 0)) {
				fcn_00510c90(*(unsigned short*) x);
				c = *(int*) (x + 2);
			} else {
				fcn_005110d0(*(unsigned char*) base);
				c = -1;
			}
			fcn_00526920(base, c, g_6b5c60);
		}
	}
	for (;;) {
		if ((g_774970 >= 0x300) || (g_774954 != 0)) {
			break;
		}
		if (*(char*) ((g_774970 & 0xffff) * 0x21c + 0x7f4ca2) == 6) {
			break;
		}
		g_774970++;
	}
	if ((signed char) g_7747b0 < 0) {
		fcn_00580a30();
		memset(buf, 0, 0xf8);
		buf[4] = 0x87;
		*(int*) (buf + 0xc) = -1;
		buf[0x36] = 9;
		*(int*) (buf + 8) =
		    *(int*) ((g_774970 & 0xffff) * 0x21c + 0x7f4ca4);
		fcn_004c5530(buf);
	}
	for (;;) {
		if (fcn_005373e0((void*) 0x5438c0, 0x20007) == 0) {
			break;
		}
		if (g_774950 >= 0x320) {
			break;
		}
		g_774948 = 0;
		if (g_7747b0 & 0x42) {
			c = 0;
			count = g_774970;
			if (count != 0) {
				p = 0x7f4ca2;
				do {
					if (*(char*) p == 6) {
						c++;
					}
					p += 0x21c;
					count--;
				} while (count != 0);
				g_774948 = c;
			}
		} else {
			g_774970 = 0;
			g_774948 = 0;
			fcn_0053fc80();
		}
		for (;;) {
			if ((g_774970 >= 0x300) || (g_774954 != 0)) {
				break;
			}
			if (*(char*) ((g_774970 & 0xffff) * 0x21c +
			    0x7f4ca2) == 6) {
				break;
			}
			g_774970++;
		}
		if (*(char*) ((g_774970 & 0xffff) * 0x21c + 0x7f4ca2) != 6) {
			goto l_gate;
		}
		if (!(g_7747b0 & 0x46)) {
			r3.x = *(int*) 0x7f4c00;
			r3.y = *(int*) 0x7f4c04;
			r3.w = *(int*) 0x7f4c08;
			r3.h = *(short*) 0x7f4c0c;
			fcn_00500c50(&r3, 6, 0, 0);
			x = fcn_004c5790(3, &r3);
			while (fcn_004c4450(x) == 0) {
				fcn_00535960();
			}
		}
		if (g_7747b0 & 0x42) {
			fcn_00516f60();
			fcn_00528fd0();
			if (g_7747b0 & 4) {
				fcn_004c5790(1, 0);
				if (g_7747b0 & 4) {
					fcn_00535770(0x67fff);
				}
			}
		} else {
			fcn_00540020();
		}
		if (!(g_7747b0 & 2)) {
			fcn_004c44a0();
			if ((g_7747b0 & 8) ||
			    ((g_14cbca0 != -1) && (g_77494c & 8))) {
				fcn_005490e0();
				fcn_00549130();
				fcn_00549240();
			}
			fcn_005491c0();
			fcn_004c44b0();
			while (fcn_004c44c0() == 0) {
				fcn_00535960();
			}
		}
		if ((!(g_7747b0 & 0x42)) && (g_6a342c != 0) &&
		    (g_774954 == 0) && ((signed char) g_7747b0 >= 0)) {
			g_773de8 = 0;
			if (g_7747b0 & 4) {
				if (g_7747b0 & 0x10) {
					memset(buf, 0, 0x7c);
					*(int*) (buf + 4) = *(int*) g_6a33dc;
					buf[0] = 0;
					*(int*) (buf + 8) = *(int*) (g_6a33dc + 4);
					buf[0xc] = g_6a33dc[8];
					x = fcn_004c5790(15, buf);
					while (fcn_004c4450(x) == 0) {
						fcn_00535960();
					}
				}
			} else {
				fcn_0064d41a(name, g_6a44c8, g_6a3448);
				fp = (void*) fcn_0064e2f9(name, g_6750e8);
				if (fp != 0) {
					fcn_0064d41a(path, g_6a44a8, g_6a3448);
					fcn_0064e48f(fp, 0, 2);
					n = fcn_0064e30c(fp);
					fcn_0064e48f(fp, 0, 0);
					base = m_alloc(n, g_67d940);
					c = fcn_0064e2f9(path, g_6790b0);
					if (base != 0) {
						if (c != 0) {
							fcn_0064ebe4(base, n, 1, fp);
							fcn_0064ed28(base, n, 1,
							    (void*) c);
							fcn_0064e1fd((void*) c);
						}
						m_FreeTracked(base);
					}
					fcn_0064e1fd(fp);
				}
				fcn_0064d41a(name, g_6a4498, g_6a3778);
				fcn_005e3fa0(name);
				fcn_0051e080(g_6a4470, g_6a448c, 1);
			}
		}
		fcn_005459a0(g_774970 & 0xffff);
		g_fb5744 = 0;
		g_774960 = 0;
		fcn_0059a340();
		if (g_774954 != 0) {
			goto l_inc;
		}
		fcn_0042df30((void*) 0x538060, 1);
		if (!(g_7747b0 & 8)) {
			r2.x = *(int*) 0x7f4c00;
			r2.y = *(int*) 0x7f4c04;
			r2.w = *(int*) 0x7f4c08;
			r2.h = *(short*) 0x7f4c0c;
			while ((unsigned short) r2.y < 0x17) {
				fcn_00500bb0(&r2, 0x1e, 0, 0);
				x = fcn_004c5700(&r2);
				while (fcn_004c4450(x) == 0) {
					fcn_00535960();
				}
			}
		}
		fcn_00541620();
		if (g_774954 != 0) {
			goto l_inc;
		}
		if (g_774958 != 0) {
			goto l_inc;
		}
		g_7747b0 &= 0xbd;
		g_774948 += 1;
		goto l_gate;
l_inc:
		g_774948 += 1;
l_gate:
		if (g_774954 != 0) {
			goto l_step;
		}
		if (g_14cbca0 == -1) {
			fcn_0042df30((void*) 0x538060, 1);
			r1.x = *(int*) 0x7f4c00;
			r1.y = *(int*) 0x7f4c04;
			r1.w = *(int*) 0x7f4c08;
			r1.h = *(short*) 0x7f4c0c;
			while ((unsigned short) r1.y < 0x17) {
				fcn_00500bb0(&r1, 0x1e, 0, 0);
				x = fcn_004c5700(&r1);
				while (fcn_004c4450(x) == 0) {
					fcn_00535960();
				}
			}
			fcn_00500bb0(&r1, 0x18, 0, 0);
			fcn_00500c50(&r1, 6, 0, 0);
			fcn_004c5700(&r1);
			fcn_0042df30((void*) 0x538060, 0);
		}
		if (((g_77494c & 8) != 0) || (g_14cbca0 == -1)) {
			if (fcn_004e9ee0() != 0) {
				memset(msg, 0, 0x114);
				c = 0;
				for (p = 0x7f4ca4; p < 0x85a0a4; p += 0x21c) {
					if (*(char*) (p - 2) == 6) {
						*(int*) (msg + 0xc) = *(int*) p;
						*(int*) (msg + 0x34 + c * 4) =
						    *(int*) p;
						c++;
					} else if (*(char*) (p - 2) == 7) {
						*(int*) (msg + 0x34 + c * 4) =
						    *(int*) p;
						c++;
					}
				}
				msg[0x30] = (unsigned char) c;
				*(int*) (msg + 0x18) = *(int*) 0x7f4c00;
				*(int*) (msg + 0x1c) = *(int*) 0x7f4c04;
				*(int*) (msg + 0x20) = *(int*) 0x7f4c08;
				*(short*) (msg + 0x24) = *(short*) 0x7f4c0c;
				g_7e46ac = 0x24087;
				msg[8] = 1;
				*(int*) (msg + 0x14) = -1;
				msg[0x26] = 0x61;
				x = fcn_004c5980(msg);
				while (fcn_004c4450(x) == 0) {
					fcn_00535960();
				}
			} else {
				fcn_004ea350();
			}
		}
		if (g_7747b0 & 4) {
			fcn_00535770(0x24087);
		}
		fcn_00543080();
l_step:
		g_774950 += 1;
		if (g_774954 == 0) {
			continue;
		}
		break;
	}
	if (g_7747b0 & 4) {
		if (g_68a9dc == -1) {
			fcn_00526120(g_6a43d0, 0);
		} else if (g_68a9dc !=
		    *(int*) ((g_774970 & 0xffff) * 0x21c + 0x7f4ca4)) {
			fcn_00526120(g_6a4420, 0);
		}
	}
	if ((signed char) g_7747b0 < 0) {
		fcn_00580c20();
	}
	fcn_0053fa80();
}
