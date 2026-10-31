extern int g_774650;
extern int g_774658;
extern int g_774654;
extern int g_774670;
extern int g_77493c;
extern int g_774708;
extern int g_774954;
extern int g_774938;
extern int g_774934;
extern int g_774930;
extern int g_7e35c0[];
extern int g_7e46ac;
extern int g_7e2700;
extern int g_7e4300;
extern unsigned short g_774970;
extern int g_7f4c04;
extern char g_7f4ca0[];
extern int g_14a5544;
extern unsigned int g_aecde4;
extern unsigned int g_6b7fac;
extern int g_14cbca0;
extern char g_774964;
extern char g_774660;
extern char g_6a33f4[];
extern int g_6a2c08;
extern char g_7f4c00[];
extern int g_6b8010;
extern int g_6b8014;
extern int g_6b8008;
extern int g_773dd8;
extern int g_7746c4;
extern int g_7746c8;
extern int g_67530c;
extern int g_6a2c04;
extern int g_7e4534;
extern int g_6b8300;
extern int g_772f6c;
extern int g_14ce8e8;
extern int g_67d370;
extern int g_1015ea0;
extern int g_7746a4;
extern int g_7746ac;
extern int g_774668;
extern int g_6b5cc0;
extern int g_7725c8;
extern int g_7749e4;
extern int g_67d8dc;
extern int g_6a99e8;
extern int g_6a25ac;
extern int g_6a2c0c;
extern int g_772f54;
extern char g_14cf71d;
extern char g_14cf738;
extern int g_7746cc;
extern int g_6b5de0;
extern char g_1052be0[];
extern char g_7747b0;
extern unsigned char g_14cf950;
extern short g_14cf900;
extern short g_14cf902;
extern int g_100f1e8;
extern int g_100f1ec;
extern int g_7725d0;
extern int g_14ce8cc;
extern int g_67d8d4;
extern int g_6a25a8;
extern int g_774800;
extern int g_774960;
extern char g_774966;
extern int g_6a25a0;
extern int g_6a257c;
extern int g_6a2584;
extern int g_6a2588;
extern int g_6a258c;
extern int g_6a2580;
extern int g_6a2578;
extern int g_100f1dc;
extern int g_6a24e8;
extern int g_fb5744;
extern int g_14a5524;
extern int g_6a3760;
extern char g_7747ad;
extern char g_774988[];
extern int g_774980;
extern int g_772e84;
extern int g_14ac5e8;
#include "GOLDTL.fcn_005373e0_gconf.h"
extern char g_5438c0[];
extern char g_7e1f70[];
extern char g_6b5c60[];
extern char g_6a33c8[];
extern char g_6a33dc[];
extern char g_6a33e8[];
extern int g_6772c4;
extern int g_7766a0;
extern float g_665e44;
extern float g_662a68;

extern void *memcpy(void *, const void *, unsigned int);

extern void fcn_005356e0();
extern void fcn_412630();
extern void fcn_004116d0();
extern int fcn_004e6a30();
extern void fcn_00533a40();
extern void fcn_00474e80();
extern void fcn_00533090();
extern void ReportClientMessage();
extern void fcn_00545aa0();
extern void fcn_00546d90();
extern void fcn_004c5700();
extern int fcn_004e6650();
extern void fcn_004c3ff0();
extern void fcn_004c4940();
extern void cm_ExecCommand();
extern void ProcessActiveContexts();
extern void fcn_465fe0();
extern void fcn_0052a960();
extern void fcn_00454f80();
extern void fcn_00413380();
extern void fcn_00444190();
extern void fcn_00530a00();
extern void fcn_00530c60();
extern void fcn_00529890();
extern void ch_UpdatePendingPositions();
extern void ch_Update();
extern void fcn_00402ff0();
extern void fcn_005e8b10();
extern void fcn_004efde0();
extern void fcn_00536bb0();
extern void fcn_004c0cd0();
extern void fcn_004c16c0();
extern void fcn_004c0b40();
extern void fcn_004c2860();
extern void fcn_00537080();
extern void fcn_00415d70();
extern void fcn_005348a0();
extern void fcn_005345b0();
extern void fcn_00534b90();
extern void fcn_00418e00();
extern void fcn_00419990();
extern void fcn_00422150();
extern void fcn_0052fde0();
extern void fcn_00475220();
extern void d2_SetOverlayAnimation();
extern void sv_HandleObjects();
extern void fcn_00531620();
extern void fcn_00531d20();
extern void fcn_00590670();
extern void fcn_00527f60();
extern void fcn_0046a110();
extern void fcn_004da1b0();
extern void fcn_00532650();
extern void fcn_00532900();
extern void fcn_005329a0();
extern void fcn_4d03e0();
extern void fcn_00532bd0();
extern void fcn_005337a0();
extern void fcn_005337f0();
extern void fcn_00526b70();
extern void fcn_0047c560();
extern void fcn_0047cdf0();
extern void fcn_00472a50();
extern void fcn_00411fe0();
extern void fcn_00537320();
extern void fcn_0041bcb0();
extern void fcn_0041fc80();
extern void fcn_00427370();
extern void fcn_5e43f0();
extern void fcn_00536b10();
extern void fcn_00536810();
extern void fcn_00537210();
extern void fcn_005356b0();
extern void fcn_005e4c50();
extern void fcn_005924d0();
extern void fcn_00592470();
extern void fcn_005d4a20();
extern void fcn_005d46d0();
extern void fcn_005c67d0();
extern void fcn_005c8c40();
extern void fcn_005e4cd0();
extern void fcn_005d42e0();
extern void fcn_005d0660();
extern void fcn_0042df30();
extern void fcn_00526660();
extern void fcn_004b6470();
extern void fcn_64d41a();
extern void fcn_005e41b0();
extern void fcn_00535850();


/* ADDRESS: GOLDTL 0x005373e0 */
int __cdecl fcn_005373e0(int a0, unsigned int flags)
{
	int result;
	float t;
	int z;
	char s[260];
	char buf[260];
	int i;
	int f;
	char *p;
	int addr;

	z = 0;
	g_7e46ac = flags;
	fcn_005356e0();
	fcn_412630();
	if (a0 != 0) {
		if (*(int *) ((char *) g_7e35c0 + g_774650 * 8) != a0) {
			fcn_004116d0();
		}
		if (g_774970 != 0xffff) {
			if ((g_7f4ca0[(unsigned short) g_774970 * 540 + 2] == 6 ||
				g_7f4ca0[(unsigned short) g_774970 * 540 + 2] == 7) &&
				g_7f4ca0[(unsigned short) g_774970 * 540 + 8] == 0 &&
				g_774650 > g_774658) {
				p = (char *) fcn_004e6a30(
					*(int *) (g_7f4ca0 + (unsigned short) g_774970 * 540 + 0x20c));
				if (p != 0 && p[8] == 8 && !(flags & 0x10000)) {
					g_774654 = g_774650 - g_774658;
					fcn_00533a40(g_14a5544);
				}
			}
		}
	}
	if (flags & 4) {
		fcn_00474e80();
	}
	if (g_77493c != 0) {
		g_774670 = 1;
	}
	if (g_774654 == 0 && (flags & 0x100) && !(flags & 0x100000)) {
		fcn_00533090(flags);
	}
	g_774708 = a0;
	if (a0 != 0) {
		if (*(int *) ((char *) g_7e35c0 + g_774650 * 8) == a0) {
			result = 1;
		} else if (g_774654 != 0) {
			result = 0;
		} else {
			result = 1;
			for (addr = 0x7e35c0; addr < 0x7e39c0; addr += 8) {
				if (*(int *) addr == a0) {
					ReportClientMessage(g_6a33f4);
					result = 0;
					break;
				}
			}
			if (result != 0) {
				g_774650++;
				*(int *) ((char *) g_7e35c0 + g_774650 * 8) = a0;
			}
		}
		if (g_774654 != 0 && result != 0) {
			g_774654--;
			if (g_774650 != 0) {
				*(int *) ((char *) g_7e35c0 + g_774650 * 8) = z;
				g_774650--;
			}
			result = 0;
		}
	} else {
		result = 1;
	}
	if ((flags & 1) && g_774954 == 0) {
		if (flags & 0x100) {
			fcn_00545aa0();
		}
		fcn_00546d90();
		if (g_14cbca0 == -1 && g_6b7fac > g_aecde4 && g_774964 != 0) {
			fcn_004c5700(g_7e1f70);
		}
		if (!(flags & 0x10000) && g_774964 != 0 && g_7e2700 == 0 &&
			fcn_004e6650() != 0 && g_774660 != 0) {
			g_774654 = 1;
		}
	}
	if (flags & 0x20000) {
		if (g_6b7fac > g_aecde4) {
			fcn_004c3ff0();
			fcn_004c4940();
			cm_ExecCommand();
			g_aecde4 = g_6b7fac + 7;
		}
	}
	if (result == 0 || g_7e2700 != 0) {
		g_774670++;
	}
	if (flags & 0x200) {
		ProcessActiveContexts();
	}
	if (g_774670 == 0) {
		if (flags & 0x80) {
			fcn_465fe0();
		}
		if (g_774670 == 0 && (flags & 0x40) && g_6a2c08 != 0) {
			if (!(flags & 0x10000) && (flags & 0x40000)) {
				fcn_0052a960(g_7f4c00);
			}
			if (g_6b8010 == 0) {
				fcn_00454f80(g_773dd8, g_6b8014, g_6b8008);
			}
			fcn_00413380();
			fcn_00444190();
		}
	}
	i = g_7746c4;
	if (i == 0) {
		i = g_7746c8;
	}
	z = flags & 0x8000;
	if (z == 0 && g_774964 != 0) {
		fcn_00530a00(i);
	}
	if (i != 0 && !(flags & 0x10000)) {
		fcn_00530c60(i);
		fcn_00529890(i);
		g_67530c = *(int *) (i + 1);
	} else {
		g_67530c = -1;
	}
	if (g_6a2c04 != 0) {
		ch_UpdatePendingPositions();
		ch_Update();
		fcn_00402ff0();
	}
	if (g_774964 != 0) {
		fcn_005e8b10();
		fcn_004efde0();
	}
	p = (char *) (flags & 0x4000);
	if (p != 0 && (g_7f4c04 & 0xffff) != g_7e4534) {
		fcn_00536bb0();
	}
	if (g_774938 != 0) {
		fcn_004c0cd0();
	}
	if (g_774934 != 0) {
		fcn_004c16c0();
		fcn_004c0b40();
	}
	if (g_774930 != 0 && (flags & 0x40000)) {
		fcn_004c2860();
	}
	if (g_774670 == 0) {
		if (g_6b8300 != 0 && p != 0 && (flags & 0x40)) {
			fcn_00537080();
		}
		if (g_774670 == 0) {
			if ((flags & 0x10000) && g_772f6c != 0) {
				fcn_00415d70(g_772f6c);
			}
			if (g_774670 == 0 && g_7e4300 != 0) {
				if (z != 0) {
					fcn_005348a0();
				} else {
					fcn_005345b0();
				}
				fcn_00534b90();
			}
		}
	}
	if (g_774934 != 0) {
		fcn_00418e00();
		if (g_774938 != 0) {
			fcn_00419990();
		}
		fcn_00422150();
	}
	if (g_774654 == 0 && !(flags & 0x100000)) {
		if (z == 0) {
			fcn_0052fde0();
		}
		f = flags & 0x10;
		if (f == 0) {
			if (g_14ce8e8 == 0) {
				if (g_67d370 == -1 ||
					!(*(char *) (g_1015ea0 + g_67d370 * 756 + 0x1d0) & 0x40)) {
					fcn_00475220(g_6b5c60);
				}
				g_7746a4 = 0;
				g_7746ac = 0;
				if (z == 0) {
					d2_SetOverlayAnimation(0, 0);
				}
			}
		}
		if (g_14ce8e8 == 0) {
			if (f != 0) {
				sv_HandleObjects();
			}
			if (flags & 0x20) {
				fcn_00531620();
				fcn_00531d20();
			}
		}
	}
	if (flags & 0x400) {
		fcn_00590670();
	}
	if (g_774670 == 0 && (flags & 0x80)) {
		f = flags & 0x1000;
		if (!(f != 0 && g_14ce8e8 == 0 && g_774668 == 0 && g_6b5cc0 == 0 &&
			g_7e4300 == 0 && g_7725c8 == 0 && g_7749e4 == 0)) {
			g_67d8dc = 0;
		} else {
			g_67d8dc = 1;
			if (g_6a99e8 != -1) {
				g_67d8dc = 0;
			}
		}
		if (g_6a25ac != -1 && (flags & 0x100) && g_6a2c0c != 0) {
			fcn_00527f60(2, flags);
		}
		fcn_0046a110((~flags >> 6) & 1);
		if (g_772f54 != 0) {
			fcn_004da1b0();
		}
		if (f != 0 && g_774650 == g_774658 && g_7749e4 == 0) {
			fcn_00532650();
			if (g_14cf71d != 0) {
				fcn_00532900();
			} else if (g_14cf738 != 0) {
				fcn_005329a0();
			}
		}
		if (flags & 0x80000) {
			fcn_4d03e0();
		} else if ((flags & 8) && (g_7746cc != 0 || g_7746c8 != 0)) {
			fcn_00532bd0();
		}
		if (f != 0 && g_14ce8e8 == 0 && g_774668 == 0 && g_6b5cc0 == 0 &&
			g_7e4300 == 0 && g_7725c8 == 0 && g_7749e4 == 0) {
			fcn_005337a0();
		}
		fcn_005337f0();
		fcn_00526b70();
		fcn_0047c560(0, 0, 0);
		(*(void (__stdcall **) (int, int)) (*(int *) g_6b5de0 + 0xa0))(g_6b5de0, (int) g_1052be0);
		fcn_0047cdf0();
	} else if (g_7e2700 != 0) {
		fcn_00472a50();
	}
	fcn_00411fe0();
	if (g_6772c4 != 0) {
		g_100f1e8 = g_14cf900;
		g_100f1ec = g_14cf902;
	}
	fcn_00537320(flags);
	if (g_774670 == 0 && (flags & 0x80)) {
		fcn_0041bcb0();
	}
	if (g_14cf950 == 1 && (flags & 0x2000)) {
		t = (float) (g_7766a0 & 0xff) * g_665e44;
		fcn_0041fc80((int) (((float) *((unsigned char *) &g_7766a0 + 2) * t) * g_662a68));
		fcn_00427370((int) (((float) *((unsigned char *) &g_7766a0 + 1) * t) * g_662a68));
		fcn_5e43f0();
		t = (float) (g_7766a0 & 0xff) * g_665e44;
		fcn_0041fc80((int) ((float) *((unsigned char *) &g_7766a0 + 2) * t));
		fcn_00427370((int) ((float) *((unsigned char *) &g_7766a0 + 1) * t));
	}
	fcn_00536b10();
	if (g_774964 != 0) {
		if ((g_7747b0 & 4) && g_7725d0 == 0 && g_14cf950 == 0x1c && (flags & 0x2000)) {
			fcn_00536810();
		}
		if (g_774964 != 0) {
			if (g_14cf950 == 0xcf || (g_14ce8cc != 0 && g_67d8d4 == g_6a25a8)) {
				if (!(flags & 0x10000) && g_774660 == 0 && !(g_7747b0 & 4)) {
					if (g_774800 == 0) {
						fcn_00537210();
					} else {
						g_774960 = 1;
						fcn_005356b0(g_5438c0);
					}
				}
			}
			if (g_774964 != 0) {
				if (g_774966 == 0 && !(g_7747b0 & 4) && z == 0 && g_14cf950 == 0x39) {
					fcn_005e4c50();
				}
				if (g_774964 != 0 && !(flags & 0x300000)) {
					fcn_005924d0();
				}
			}
		}
	}
	if (g_6a25ac != -1 && (flags & 0x2000) && !(flags & 0x100000) &&
		g_774650 == g_774658) {
		if (g_774964 != 0) {
			fcn_00592470();
		}
		if (g_774970 != 0xffff && (unsigned char) g_7f4ca0[(unsigned short) g_774970 * 540 + 8] > 0) {
			if (g_100f1dc != -1) {
				i = g_67d370;
				if (i == g_6a25a0) {
					fcn_005d4a20();
				} else if (i == g_6a257c) {
					fcn_005d46d0();
				} else if (i == g_6a2584) {
					fcn_005c67d0();
				} else if (i == g_6a2588) {
					fcn_005c8c40();
				} else if (i == g_6a258c) {
					fcn_005e4cd0();
				} else if (i == g_6a2580) {
					fcn_005d42e0();
				} else if (i == g_6a2578) {
					fcn_005d0660(*(int *) (g_7f4ca0 + (unsigned short) g_774970 * 540 + 4),
						0x11, 0, 0x657c7);
				}
			}
		} else if (g_100f1dc != -1) {
			i = g_67d370;
			if (i == g_6a25a0 || i == g_6a257c || i == g_6a2584 ||
				i == g_6a2588 || i == g_6a2580 || i == g_6a2578) {
				fcn_00533a40(g_14a5544);
			}
		}
	}
	g_6a24e8++;
	i = flags & 0x10000;
	if (i == 0) {
		if ((g_774654 == 0 && g_7e2700 == 0 && g_fb5744 != 0 && g_774960 == 0) ||
			(g_14cbca0 == -1 && (unsigned short) g_7f4c04 >= 0x17 && g_774960 == 0)) {
			if ((char) g_7747b0 >= 0) {
				g_774960 = 1;
				fcn_0042df30(g_538060, 1);
				g_7e46ac |= 0x100000;
				fcn_00526660(g_14a5524, 0xc4);
				fcn_005356b0(g_5438c0);
			}
		}
	}
	if (g_774960 != 0 && g_774654 == 0 &&
		*(int *) ((char *) g_7e35c0 + g_774650 * 8) == (int) 0x59a340) {
		g_774654 = 1;
	}
	if (i == 0 && g_7747ad == 0 && g_6a3760 != -1 && g_774964 != 0) {
		g_7747ad = 1;
		fcn_0042df30(g_538060, 1);
		fcn_004b6470(0x65fff);
		fcn_0042df30(g_538060, 0);
		g_7747ad = 0;
	}
	if (g_774988[0] != 0 && !(g_7e46ac & 0x200000)) {
		if (g_774980 == 1) {
			memcpy(s, g_6a33e8, 10);
		} else if (g_774980 == 0) {
			memcpy(s, g_6a33dc, 9);
		} else {
			fcn_64d41a(s, g_6a33c8, g_774980);
		}
		i = 0;
		do {
			s[i] = g_774988[i];
			i++;
		} while (s[i - 1] != 0);
		g_774988[0] = 0;
		fcn_005e41b0(s, buf);
	}
	if (g_772e84 > 0 && !(g_7e46ac & 0x200000)) {
		g_772e84--;
		fcn_00535850(flags, g_14ac5e8);
	}
	if (g_774670 > 0) {
		g_774670--;
	}
	return result;
}
