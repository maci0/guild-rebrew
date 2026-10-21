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
extern char g_538060[];
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

extern void fcn_5356e0();
extern void fcn_412630();
extern void fcn_4116d0();
extern int fcn_4e6a30();
extern void fcn_533a40();
extern void fcn_474e80();
extern void fcn_533090();
extern void fcn_41d9e0();
extern void fcn_545aa0();
extern void fcn_546d90();
extern void fcn_4c5700();
extern int fcn_4e6650();
extern void fcn_4c3ff0();
extern void fcn_4c4940();
extern void fcn_4c4b00();
extern void fcn_4297c0();
extern void fcn_465fe0();
extern void fcn_52a960();
extern void fcn_454f80();
extern void fcn_413380();
extern void fcn_444190();
extern void fcn_530a00();
extern void fcn_530c60();
extern void fcn_529890();
extern void fcn_403040();
extern void fcn_405e20();
extern void fcn_402ff0();
extern void fcn_5e8b10();
extern void fcn_4efde0();
extern void fcn_536bb0();
extern void fcn_4c0cd0();
extern void fcn_4c16c0();
extern void fcn_4c0b40();
extern void fcn_4c2860();
extern void fcn_537080();
extern void fcn_415d70();
extern void fcn_5348a0();
extern void fcn_5345b0();
extern void fcn_534b90();
extern void fcn_418e00();
extern void fcn_419990();
extern void fcn_422150();
extern void fcn_52fde0();
extern void fcn_475220();
extern void fcn_473a90();
extern void fcn_5305d0();
extern void fcn_531620();
extern void fcn_531d20();
extern void fcn_590670();
extern void fcn_527f60();
extern void fcn_46a110();
extern void fcn_4da1b0();
extern void fcn_532650();
extern void fcn_532900();
extern void fcn_5329a0();
extern void fcn_4d03e0();
extern void fcn_532bd0();
extern void fcn_5337a0();
extern void fcn_5337f0();
extern void fcn_526b70();
extern void fcn_47c560();
extern void fcn_47cdf0();
extern void fcn_473320();
extern void fcn_411fe0();
extern void fcn_537320();
extern void fcn_41bcb0();
extern void fcn_41fc80();
extern void fcn_4238d0();
extern void fcn_5e43f0();
extern void fcn_536b10();
extern void fcn_536810();
extern void fcn_537210();
extern void fcn_5356b0();
extern void fcn_5e4c50();
extern void fcn_5924d0();
extern void fcn_592470();
extern void fcn_5d4a20();
extern void fcn_5d46d0();
extern void fcn_5c67d0();
extern void fcn_5c8c40();
extern void fcn_5e4cd0();
extern void fcn_5d42e0();
extern void fcn_5d0660();
extern void fcn_42df30();
extern void fcn_526660();
extern void fcn_4b6470();
extern void fcn_64d41a();
extern void fcn_5e41b0();
extern void fcn_535850();

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
	fcn_5356e0();
	fcn_412630();
	if (a0 != 0) {
		if (*(int *) ((char *) g_7e35c0 + g_774650 * 8) != a0) {
			fcn_4116d0();
		}
		if (g_774970 != 0xffff) {
			if ((g_7f4ca0[(unsigned short) g_774970 * 540 + 2] == 6 ||
				g_7f4ca0[(unsigned short) g_774970 * 540 + 2] == 7) &&
				g_7f4ca0[(unsigned short) g_774970 * 540 + 8] == 0 &&
				g_774650 > g_774658) {
				p = (char *) fcn_4e6a30(
					*(int *) (g_7f4ca0 + (unsigned short) g_774970 * 540 + 0x20c));
				if (p != 0 && p[8] == 8 && !(flags & 0x10000)) {
					g_774654 = g_774650 - g_774658;
					fcn_533a40(g_14a5544);
				}
			}
		}
	}
	if (flags & 4) {
		fcn_474e80();
	}
	if (g_77493c != 0) {
		g_774670 = 1;
	}
	if (g_774654 == 0 && (flags & 0x100) && !(flags & 0x100000)) {
		fcn_533090(flags);
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
					fcn_41d9e0(g_6a33f4);
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
			fcn_545aa0();
		}
		fcn_546d90();
		if (g_14cbca0 == -1 && g_6b7fac > g_aecde4 && g_774964 != 0) {
			fcn_4c5700(g_7e1f70);
		}
		if (!(flags & 0x10000) && g_774964 != 0 && g_7e2700 == 0 &&
			fcn_4e6650() != 0 && g_774660 != 0) {
			g_774654 = 1;
		}
	}
	if (flags & 0x20000) {
		if (g_6b7fac > g_aecde4) {
			fcn_4c3ff0();
			fcn_4c4940();
			fcn_4c4b00();
			g_aecde4 = g_6b7fac + 7;
		}
	}
	if (result == 0 || g_7e2700 != 0) {
		g_774670++;
	}
	if (flags & 0x200) {
		fcn_4297c0();
	}
	if (g_774670 == 0) {
		if (flags & 0x80) {
			fcn_465fe0();
		}
		if (g_774670 == 0 && (flags & 0x40) && g_6a2c08 != 0) {
			if (!(flags & 0x10000) && (flags & 0x40000)) {
				fcn_52a960(g_7f4c00);
			}
			if (g_6b8010 == 0) {
				fcn_454f80(g_773dd8, g_6b8014, g_6b8008);
			}
			fcn_413380();
			fcn_444190();
		}
	}
	i = g_7746c4;
	if (i == 0) {
		i = g_7746c8;
	}
	z = flags & 0x8000;
	if (z == 0 && g_774964 != 0) {
		fcn_530a00(i);
	}
	if (i != 0 && !(flags & 0x10000)) {
		fcn_530c60(i);
		fcn_529890(i);
		g_67530c = *(int *) (i + 1);
	} else {
		g_67530c = -1;
	}
	if (g_6a2c04 != 0) {
		fcn_403040();
		fcn_405e20();
		fcn_402ff0();
	}
	if (g_774964 != 0) {
		fcn_5e8b10();
		fcn_4efde0();
	}
	p = (char *) (flags & 0x4000);
	if (p != 0 && (g_7f4c04 & 0xffff) != g_7e4534) {
		fcn_536bb0();
	}
	if (g_774938 != 0) {
		fcn_4c0cd0();
	}
	if (g_774934 != 0) {
		fcn_4c16c0();
		fcn_4c0b40();
	}
	if (g_774930 != 0 && (flags & 0x40000)) {
		fcn_4c2860();
	}
	if (g_774670 == 0) {
		if (g_6b8300 != 0 && p != 0 && (flags & 0x40)) {
			fcn_537080();
		}
		if (g_774670 == 0) {
			if ((flags & 0x10000) && g_772f6c != 0) {
				fcn_415d70(g_772f6c);
			}
			if (g_774670 == 0 && g_7e4300 != 0) {
				if (z != 0) {
					fcn_5348a0();
				} else {
					fcn_5345b0();
				}
				fcn_534b90();
			}
		}
	}
	if (g_774934 != 0) {
		fcn_418e00();
		if (g_774938 != 0) {
			fcn_419990();
		}
		fcn_422150();
	}
	if (g_774654 == 0 && !(flags & 0x100000)) {
		if (z == 0) {
			fcn_52fde0();
		}
		f = flags & 0x10;
		if (f == 0) {
			if (g_14ce8e8 == 0) {
				if (g_67d370 == -1 ||
					!(*(char *) (g_1015ea0 + g_67d370 * 756 + 0x1d0) & 0x40)) {
					fcn_475220(g_6b5c60);
				}
				g_7746a4 = 0;
				g_7746ac = 0;
				if (z == 0) {
					fcn_473a90(0, 0);
				}
			}
		}
		if (g_14ce8e8 == 0) {
			if (f != 0) {
				fcn_5305d0();
			}
			if (flags & 0x20) {
				fcn_531620();
				fcn_531d20();
			}
		}
	}
	if (flags & 0x400) {
		fcn_590670();
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
			fcn_527f60(2, flags);
		}
		fcn_46a110((~flags >> 6) & 1);
		if (g_772f54 != 0) {
			fcn_4da1b0();
		}
		if (f != 0 && g_774650 == g_774658 && g_7749e4 == 0) {
			fcn_532650();
			if (g_14cf71d != 0) {
				fcn_532900();
			} else if (g_14cf738 != 0) {
				fcn_5329a0();
			}
		}
		if (flags & 0x80000) {
			fcn_4d03e0();
		} else if ((flags & 8) && (g_7746cc != 0 || g_7746c8 != 0)) {
			fcn_532bd0();
		}
		if (f != 0 && g_14ce8e8 == 0 && g_774668 == 0 && g_6b5cc0 == 0 &&
			g_7e4300 == 0 && g_7725c8 == 0 && g_7749e4 == 0) {
			fcn_5337a0();
		}
		fcn_5337f0();
		fcn_526b70();
		fcn_47c560(0, 0, 0);
		(*(void (__stdcall **) (int, int)) (*(int *) g_6b5de0 + 0xa0))(g_6b5de0, (int) g_1052be0);
		fcn_47cdf0();
	} else if (g_7e2700 != 0) {
		fcn_473320();
	}
	fcn_411fe0();
	if (g_6772c4 != 0) {
		g_100f1e8 = g_14cf900;
		g_100f1ec = g_14cf902;
	}
	fcn_537320(flags);
	if (g_774670 == 0 && (flags & 0x80)) {
		fcn_41bcb0();
	}
	if (g_14cf950 == 1 && (flags & 0x2000)) {
		t = (float) (g_7766a0 & 0xff) * g_665e44;
		fcn_41fc80((int) (((float) *((unsigned char *) &g_7766a0 + 2) * t) * g_662a68));
		fcn_4238d0((int) (((float) *((unsigned char *) &g_7766a0 + 1) * t) * g_662a68));
		fcn_5e43f0();
		t = (float) (g_7766a0 & 0xff) * g_665e44;
		fcn_41fc80((int) ((float) *((unsigned char *) &g_7766a0 + 2) * t));
		fcn_4238d0((int) ((float) *((unsigned char *) &g_7766a0 + 1) * t));
	}
	fcn_536b10();
	if (g_774964 != 0) {
		if ((g_7747b0 & 4) && g_7725d0 == 0 && g_14cf950 == 0x1c && (flags & 0x2000)) {
			fcn_536810();
		}
		if (g_774964 != 0) {
			if (g_14cf950 == 0xcf || (g_14ce8cc != 0 && g_67d8d4 == g_6a25a8)) {
				if (!(flags & 0x10000) && g_774660 == 0 && !(g_7747b0 & 4)) {
					if (g_774800 == 0) {
						fcn_537210();
					} else {
						g_774960 = 1;
						fcn_5356b0(g_5438c0);
					}
				}
			}
			if (g_774964 != 0) {
				if (g_774966 == 0 && !(g_7747b0 & 4) && z == 0 && g_14cf950 == 0x39) {
					fcn_5e4c50();
				}
				if (g_774964 != 0 && !(flags & 0x300000)) {
					fcn_5924d0();
				}
			}
		}
	}
	if (g_6a25ac != -1 && (flags & 0x2000) && !(flags & 0x100000) &&
		g_774650 == g_774658) {
		if (g_774964 != 0) {
			fcn_592470();
		}
		if (g_774970 != 0xffff && (unsigned char) g_7f4ca0[(unsigned short) g_774970 * 540 + 8] > 0) {
			if (g_100f1dc != -1) {
				i = g_67d370;
				if (i == g_6a25a0) {
					fcn_5d4a20();
				} else if (i == g_6a257c) {
					fcn_5d46d0();
				} else if (i == g_6a2584) {
					fcn_5c67d0();
				} else if (i == g_6a2588) {
					fcn_5c8c40();
				} else if (i == g_6a258c) {
					fcn_5e4cd0();
				} else if (i == g_6a2580) {
					fcn_5d42e0();
				} else if (i == g_6a2578) {
					fcn_5d0660(*(int *) (g_7f4ca0 + (unsigned short) g_774970 * 540 + 4),
						0x11, 0, 0x657c7);
				}
			}
		} else if (g_100f1dc != -1) {
			i = g_67d370;
			if (i == g_6a25a0 || i == g_6a257c || i == g_6a2584 ||
				i == g_6a2588 || i == g_6a2580 || i == g_6a2578) {
				fcn_533a40(g_14a5544);
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
				fcn_42df30(g_538060, 1);
				g_7e46ac |= 0x100000;
				fcn_526660(g_14a5524, 0xc4);
				fcn_5356b0(g_5438c0);
			}
		}
	}
	if (g_774960 != 0 && g_774654 == 0 &&
		*(int *) ((char *) g_7e35c0 + g_774650 * 8) == (int) 0x59a340) {
		g_774654 = 1;
	}
	if (i == 0 && g_7747ad == 0 && g_6a3760 != -1 && g_774964 != 0) {
		g_7747ad = 1;
		fcn_42df30(g_538060, 1);
		fcn_4b6470(0x65fff);
		fcn_42df30(g_538060, 0);
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
		fcn_5e41b0(s, buf);
	}
	if (g_772e84 > 0 && !(g_7e46ac & 0x200000)) {
		g_772e84--;
		fcn_535850(flags, g_14ac5e8);
	}
	if (g_774670 > 0) {
		g_774670--;
	}
	return result;
}
