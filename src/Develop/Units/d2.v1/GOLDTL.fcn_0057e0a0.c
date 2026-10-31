extern int g_774a14;
extern int *g_665f08;
extern int g_7749e4;
extern int g_6b5cbc;
extern int g_6b5cc0;
extern int g_7e2700;
extern int g_774a18;
extern int g_6b7fac;
extern int g_6b7fc0;
extern int g_774650;
extern int g_774658;
extern int g_774654;

int __cdecl fcn_00423460(int);
int __cdecl fcn_004237f0(int, int);
void __cdecl fcn_004707d0(int);
void __cdecl fcn_00472640(int, int);
void __cdecl d2_SetOverlayAnimation(int, int);
int __cdecl fcn_004c3030(int, int, int, int);
void __cdecl fcn_00532ef0(void);
void __cdecl fcn_00533a40(int);
void __cdecl fcn_00545c50(int);
int __cdecl fcn_0057e880(int, int, int, int);
int __cdecl fcn_00580140(void);
int __cdecl fcn_00580290(void);
void __cdecl fcn_00580320(void);
void __cdecl fcn_005803f0(void);
void __cdecl fcn_00580420(void);
void __cdecl fcn_005804f0(void);
void __cdecl fcn_00580610(void);
void __cdecl fcn_005806d0(void);
int __cdecl fcn_00580960(void);
void __cdecl fcn_00584160(int);

/* ADDRESS: GOLDTL 0x0057e0a0 */
int __cdecl fcn_0057e0a0(void)
{
	void (__cdecl *cb)(int);

	if (g_774a14 == 0) {
		return -4;
	}
	if (g_665f08[6] == 0) {
		return -4;
	}
	if (*(int *)((int)g_665f08[7] + 0x74) == 0) {
		return -4;
	}
	if (g_7749e4 == *(int *)((int)g_665f08[7] + 0x74) && g_665f08[0] != 2) {
		if (g_6b5cbc != 0 || g_7e2700 != 0) {
			goto ret0;
		}
		d2_SetOverlayAnimation(0, 0);
		g_665f08[0] = 3;
	}
	if (g_7749e4 != *(int *)((int)g_665f08[7] + 0x74)) {
		g_665f08[0] = g_665f08[1];
	}
	if (g_665f08[0xc] == 1 && g_665f08[0] != 9) {
		g_665f08[0xc] = 0;
		fcn_005804f0();
		fcn_00584160(2);
	}
	if (g_774a18 == 0) {
		return 0;
	}
	fcn_00580610();
	if (g_6b5cbc != 0) {
		return 0;
	}
	if (g_7e2700 != 0) {
		return 0;
	}
	switch (g_665f08[0]) {
	case 1:
		if (g_6b5cc0 != 0) {
			break;
		}
		if (fcn_00580140() != 0) {
			return -4;
		}
		g_665f08[0xe] = 0;
		g_665f08[0xf] = 0;
		g_665f08[0] = 2;
		if (*(int *)((int)g_665f08[6] + 8) == 1 || *(int *)((int)g_665f08[6] + 8) == 2) {
			g_665f08[1] = 4;
			g_665f08[0xb] = 0;
		} else {
			g_665f08[1] = 0xb;
			g_665f08[0xb] = 1;
		}
		if (*(int *)((int)g_665f08[6] + 8) == 2) {
			g_665f08[0xf] = 1;
		}
		if (*(int *)((int)g_665f08[6] + 0x38) != 0) {
			fcn_0057e880(2, 0, 0, 0);
		}
		g_665f08[0x14] = 0;
		if (*(int *)((int)g_665f08[6] + 0x64) == 0) {
			g_665f08[0x16] = 0;
		} else {
			g_665f08[0x16] = 1;
		}
		g_665f08[0x15] = 0;
		g_665f08[0x17] = 0;
		g_665f08[0x18] = -1;
		cb = *(void (__cdecl **)(int))((int)g_665f08[6] + 0x34);
		if (cb != 0) {
			cb(0);
		}
		fcn_00545c50(*(int *)((int)g_665f08[7] + 0x74));
		d2_SetOverlayAnimation(0, 0);
		return 0;
	case 2:
		if (fcn_00580290() != 1) {
			break;
		}
		g_665f08[0] = g_665f08[1];
		g_665f08[2] = (*(volatile unsigned int *)&g_6b7fac);
		g_665f08[3] = (*(volatile unsigned int *)&g_6b7fac);
		g_665f08[4] = 0;
		fcn_00545c50(0);
		return 0;
	case 3:
		if (fcn_00580290() != 1) {
			break;
		}
		g_665f08[0] = g_665f08[1];
		goto ret0;
ret0:
		fcn_00545c50(0);
		return 0;
	case 4:
		if (*(int *)((int)g_665f08[6] + 0x40) == 3) {
			fcn_0057e880(0, 0, 0, 0);
			return 0;
		}
		if ((*(volatile unsigned int *)&g_6b7fac) > *(int *)((int)g_665f08[6] + 0x2c) + g_665f08[2]) {
			g_665f08[2] = (*(volatile unsigned int *)&g_6b7fac);
			if (g_665f08[10] == 0 && *(int *)((int)g_665f08[6] + 0x14) != 0) {
				g_665f08[10] = 1;
				fcn_00580320();
			}
		} else {
			if ((*(volatile unsigned int *)&g_6b7fac) > g_665f08[2] + 0x238) {
				if (g_665f08[10] != 1) {
					return 0;
				}
				g_665f08[2] = (*(volatile unsigned int *)&g_6b7fac);
				g_665f08[10] = 0;
				fcn_005803f0();
			}
		}
		if (g_665f08[10] == 1) {
			fcn_004707d0(g_665f08[9]);
			return 0;
		}
		break;
	case 5:
		g_665f08[2] = (*(volatile unsigned int *)&g_6b7fac);
		g_665f08[10] = 0;
		fcn_005803f0();
		g_665f08[0xf] = 2;
		if (*(unsigned int *)((int)g_665f08[6] + 0x50) <= 0) {
			goto label7;
		}
		g_665f08[0x10] = 0;
		g_665f08[0] = 6;
		g_665f08[1] = 6;
		fcn_005806d0();
		return 0;
label7:
		g_665f08[0] = 7;
		g_665f08[1] = 7;
		return 0;
	case 6:
		g_6b7fc0 = (unsigned int)(*(int *)(*(int *)((int)g_665f08[6] + 0x58) + g_665f08[0x10] * 0x10) + g_665f08[3]) <= (unsigned int)(*(volatile unsigned int *)&g_6b7fac);
		fcn_00472640(g_665f08[0x13], g_6b7fc0);
		if (fcn_00580960() != 1) {
			break;
		}
		g_665f08[0x10] = g_665f08[0x10] + 1;
		g_665f08[2] = (*(volatile unsigned int *)&g_6b7fac);
		if ((unsigned int)g_665f08[0x10] < *(unsigned int *)((int)g_665f08[6] + 0x50)) {
			g_665f08[3] = (*(volatile unsigned int *)&g_6b7fac);
			fcn_005806d0();
			return 0;
		}
		goto label7;
	case 7:
		g_665f08[0xf] = 3;
		g_665f08[3] = (*(volatile unsigned int *)&g_6b7fac);
		g_665f08[0x14] = 0;
		fcn_005806d0();
		g_6b7fc0 = 0;
		if (*(int *)((int)g_665f08[6] + 0x4c) != 0) {
			g_665f08[0] = 9;
			g_665f08[1] = 9;
		} else {
			g_665f08[0] = 0xa;
			g_665f08[1] = 0xa;
			g_665f08[0xb] = (*(int *)((int)g_665f08[6] + 0x24) == 0);
		}
		return 0;
	case 9:
		if (g_665f08[10] == 1) {
			g_665f08[2] = (*(volatile unsigned int *)&g_6b7fac);
			g_665f08[10] = 0;
			fcn_005803f0();
		}
		if (g_665f08[0xc] == 0 && *(int *)((int)g_665f08[6] + 0x1c) != 0) {
			g_665f08[0xc] = 1;
			fcn_00580420();
			fcn_00584160(0);
		}
		if (g_665f08[0xc] == 1) {
			fcn_004707d0(g_665f08[0xd]);
		}
		fcn_00584160(1);
		return 0;
	case 10:
		if (g_665f08[10] == 1) {
			g_665f08[2] = (*(volatile unsigned int *)&g_6b7fac);
			g_665f08[10] = 0;
			fcn_005803f0();
		}
		if ((*(volatile unsigned int *)&g_6b7fac) > *(int *)((int)g_665f08[6] + 0x44) + g_665f08[3]) {
			fcn_00532ef0();
			g_774654 = g_774650 - g_774658;
			g_665f08[0] = 0xb;
			g_665f08[1] = 0xb;
			g_665f08[3] = (*(volatile unsigned int *)&g_6b7fac);
		}
		if (g_665f08[0xb] != 0) {
			break;
		}
		if (*(int *)((int)g_665f08[6] + 0x24) == 0) {
			break;
		}
		fcn_00533a40(*(int *)(*(int *)((int)g_665f08[6] + 0x24) * 4 + 0x14a5320));
		if (*(int *)((int)g_665f08[6] + 0x28) != 0) {
			if (g_665f08[5] != 0) {
				if (fcn_00423460(g_665f08[5]) != 0) {
					fcn_004237f0(g_665f08[5], 0);
				}
				g_665f08[5] = 0;
			}
			g_665f08[5] = fcn_004c3030(-7, 0, *(int *)((int)g_665f08[6] + 0x28), -1);
		}
		g_665f08[0xb] = 1;
		fcn_00580140();
		return 0;
	case 11:
		if (g_665f08[10] == 1) {
			g_665f08[2] = (*(volatile unsigned int *)&g_6b7fac);
			g_665f08[10] = 0;
			fcn_005803f0();
		}
		if ((*(volatile unsigned int *)&g_6b7fac) > *(int *)((int)g_665f08[6] + 0x30) + g_665f08[3]) {
			fcn_00532ef0();
			g_774654 = g_774650 - g_774658;
			g_665f08[0] = 0xc;
			g_665f08[1] = 0xc;
			g_665f08[3] = (*(volatile unsigned int *)&g_6b7fac);
		}
		if (g_665f08[0xb] != 0) {
			break;
		}
		if (*(int *)((int)g_665f08[6] + 0x24) == 0) {
			break;
		}
		fcn_00533a40(*(int *)(*(int *)((int)g_665f08[6] + 0x24) * 4 + 0x14a5320));
		if (*(int *)((int)g_665f08[6] + 0x28) != 0) {
			if (g_665f08[5] != 0) {
				if (fcn_00423460(g_665f08[5]) != 0) {
					fcn_004237f0(g_665f08[5], 0);
				}
				g_665f08[5] = 0;
			}
			g_665f08[5] = fcn_004c3030(-7, 0, *(int *)((int)g_665f08[6] + 0x28), -1);
		}
		g_665f08[0xb] = 1;
		fcn_00580140();
		return 0;
	case 12:
		if (g_665f08[10] == 1) {
			g_665f08[2] = (*(volatile unsigned int *)&g_6b7fac);
			g_665f08[10] = 0;
			fcn_005803f0();
		}
		cb = *(void (__cdecl **)(int))((int)g_665f08[6] + 0x34);
		if (cb != 0) {
			cb(1);
		}
		g_665f08[6] = *(int *)((int)g_665f08[6] + 0x70);
		g_665f08[0] = 1;
		g_665f08[1] = 1;
		fcn_00533a40((int)(void *)0x6b5c60);
		break;
	default:
		break;
	}
	return 0;
}
