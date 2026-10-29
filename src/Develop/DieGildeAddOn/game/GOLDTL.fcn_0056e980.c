extern int __cdecl fcn_00500e20(char*);
extern void __cdecl fcn_004c30a0(int, int, char*, int, int);
extern void __cdecl fcn_00546190(char*);
extern void __cdecl fcn_00500bb0(char*, int, int, int);
extern int __cdecl gm_RandomMod(int);

static void copy_clock(char* a0)
{
	*(int*) (a0 + 0x52) = *(int*) 0x7f4c00;
	*(int*) (a0 + 0x56) = *(int*) 0x7f4c04;
	*(int*) (a0 + 0x5a) = *(int*) 0x7f4c08;
	*(unsigned short*) (a0 + 0x5e) = *(unsigned short*) 0x7f4c0c;
}

/* Night-watchman clock action: starts the evening/morning announce sequence
 * when the game time enters the action's window. */
/* ADDRESS: GOLDTL 0x0056e980 */
void __cdecl fcn_0056e980(char* a0)
{
	int idx;
	int w;
	float tab;

	if (*(int*) 0x7f4c00 != *(int*) (a0 + 0x44)) {
		fcn_00546190(a0);
		return;
	}
	idx = fcn_00500e20((char*) 0x7f4c00);
	switch (*(int*) (a0 + 0x70)) {
	case 0:
		w = *(int*) 0x7f4c04 & 0xffff;
		tab = *(float*) (idx * 4 + 0x696540);
		if ((float) w < tab || tab + *(float*) 0x6628a0 <= (float) w) {
			copy_clock(a0);
			fcn_00500bb0((char*) 0x7f4c00, 0, 0, 1);
			return;
		}
		if (*(char*) 0x774964)
			fcn_004c30a0(-7, 0, (char*) 0x6a6d50, -1, 0xfa);
		if (*(char*) 0x7766b9 != 0 && *(char*) 0x774964 != 0 &&
		    (gm_RandomMod(10) & 0xffff) > 7 && *(char*) 0x774964 != 0) {
			fcn_004c30a0(*(int*) (a0 + 0xac), 0, (char*) 0x6a6d30, -1, 0xfa);
			switch (*(int*) (idx * 4 + 0x696540)) {
			case 0x40e00000:
				fcn_004c30a0(*(int*) (a0 + 0xac), 0, (char*) 0x6a6d10, -1, 0xfa);
				break;
			case 0x41000000:
				fcn_004c30a0(*(int*) (a0 + 0xac), 0,
					(char*) (idx == 2 ? 0x6a6cec : 0x6a6ccc), -1, 0xfa);
				break;
			case 0x41100000:
				fcn_004c30a0(*(int*) (a0 + 0xac), 0, (char*) 0x6a6cac, -1, 0x3e8);
				break;
			default:
				break;
			}
			if ((gm_RandomMod(10) & 0xffff) > 7)
				fcn_004c30a0(*(int*) (a0 + 0xac), 0, (char*) 0x6a6c8c, -1, 0x3e8);
		}
		copy_clock(a0);
		*(unsigned short*) (a0 + 0x56) = (unsigned short) (int) *(float*) (idx * 4 + 0x696550);
		*(int*) (a0 + 0x58) = 0;
		*(int*) (a0 + 0x70) += 1;
		return;
	case 1:
		w = *(int*) 0x7f4c04 & 0xffff;
		tab = *(float*) (idx * 4 + 0x696550);
		if ((float) w < tab || tab + *(float*) 0x6628a0 <= (float) w) {
			copy_clock(a0);
			fcn_00500bb0((char*) 0x7f4c00, 0, 0, 1);
			return;
		}
		if (*(char*) 0x774964)
			fcn_004c30a0(-7, 0, (char*) 0x6a6d50, -1, 0xfa);
		if (*(char*) 0x7766b9 != 0 && *(char*) 0x774964 != 0 &&
		    (gm_RandomMod(10) & 0xffff) > 7 && *(char*) 0x774964 != 0) {
			fcn_004c30a0(*(int*) (a0 + 0xac), 0, (char*) 0x6a6d30, -1, 0xfa);
			switch (*(int*) (idx * 4 + 0x696550)) {
			case 0x41980000:
				fcn_004c30a0(*(int*) (a0 + 0xac), 0, (char*) 0x6a6c6c, -1, 0xfa);
				break;
			case 0x41a00000:
				fcn_004c30a0(*(int*) (a0 + 0xac), 0,
					(char*) (idx == 2 ? 0x6a6c48 : 0x6a6c28), -1, 0xfa);
				break;
			case 0x41a80000:
				fcn_004c30a0(*(int*) (a0 + 0xac), 0, (char*) 0x6a6c08, -1, 0xfa);
				break;
			default:
				break;
			}
			if ((gm_RandomMod(10) & 0xffff) > 7)
				fcn_004c30a0(*(int*) (a0 + 0xac), 0, (char*) 0x6a6be8, -1, 0x3e8);
		}
		copy_clock(a0);
		*(unsigned short*) (a0 + 0x56) = 0x16;
		*(int*) (a0 + 0x58) = 0x1e;
		*(int*) (a0 + 0x70) += 1;
		return;
	case 2:
		if (*(unsigned short*) 0x7f4c04 < 0x16 || *(int*) 0x7f4c06 < 0x1e ||
		    *(int*) 0x7f4c06 >= 0x32) {
			copy_clock(a0);
			fcn_00500bb0((char*) 0x7f4c00, 0, 0, 1);
			return;
		}
		if (*(char*) 0x774964) {
			fcn_004c30a0(-7, 0, (char*) 0x6a6d50, -1, 0xfa);
			if (*(char*) 0x7766b9 != 0 && (gm_RandomMod(10) & 0xffff) > 7)
				fcn_004c30a0(*(int*) (a0 + 0xac), 0, (char*) 0x6a6bcc, -1, 0xfa);
		}
		fcn_00546190(a0);
		return;
	case -2:
	case -1:
		fcn_00546190(a0);
		return;
	default:
		return;
	}
}
