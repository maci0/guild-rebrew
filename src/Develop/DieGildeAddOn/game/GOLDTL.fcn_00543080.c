__declspec(dllimport) void __stdcall Sleep(unsigned long);

int __cdecl fcn_0043a9c0();
int __cdecl fcn_0043aa30();
int __cdecl fcn_004432d0();
int __cdecl fcn_0046ac30();
int __cdecl fcn_00469e30();
int __cdecl fcn_0046f740();
int __cdecl fcn_00470820();
int __cdecl fcn_00471d80();
int __cdecl fcn_00471e30();
int __cdecl fcn_00472250();
int __cdecl fcn_00472380();
int __cdecl fcn_00472640();
int __cdecl d2_SetForm();
int __cdecl fcn_00476970();
int __cdecl fcn_00495890();
int __cdecl fcn_004ad8c0();
int __cdecl fcn_004b3aa0();
int __cdecl fcn_004bceb0();
int __cdecl fcn_004c30a0();
int __cdecl fcn_004c54c0();
int __cdecl fcn_004e4f10();
int __cdecl fcn_004e6910();
int __cdecl fcn_004e7700();
int __cdecl fcn_004eafe0();
int __cdecl fcn_004f5830();
int __cdecl fcn_004f4d10();
int __cdecl fcn_004facb0();
int __cdecl fcn_004fb390();
int __cdecl fcn_004fb630();
int __cdecl fcn_004fb650();
int __cdecl fcn_004fb7a0();
int __cdecl fcn_004fcc20();
int __cdecl fcn_004fd050();
int __cdecl fcn_004fd280();
int __cdecl fcn_004ff0f0();
int __cdecl fcn_00500d60();
int __cdecl fcn_005016c0();
int __cdecl gm_FindNextFilteredEntity();
int __cdecl gm_StartFilteredEntitySearch();
int __cdecl fcn_005155e0();
int __cdecl fcn_00519190();
int __cdecl fcn_00522c0();
int __cdecl fcn_00526120();
int __cdecl fcn_005356b0();
int __cdecl fcn_00535770();
int __cdecl fcn_005373e0();
int __cdecl fcn_005421f0();
int __cdecl fcn_005422c0();
int __cdecl fcn_005435d0();
int __cdecl fcn_005448e0();
int __cdecl fcn_00546de0();
int __cdecl fcn_0053f100();
int __cdecl fcn_00546f80();
int __cdecl fcn_00547770();
int __cdecl fcn_005490a0();
int __cdecl fcn_005490d0();
int __cdecl fcn_0051af00();
int __cdecl fcn_00535570();
int __cdecl fcn_00535960();
int __cdecl gm_RandomMod(int);

/* ADDRESS: GOLDTL 0x00543080 */
void __cdecl fcn_00543080(void)
{
	int v1;
	unsigned short v2;
	unsigned char* v3;
	unsigned int* v4;
	int v5;
	int v11;
	char v6[256];
	char v7[48];
	unsigned int* v8;
	char* v9;
	int st[2];

	v1 = *(unsigned char*) 0x772d10;
	v5 = -1;
	fcn_004fa750();
	v11 = 0;
	v8 = (unsigned int*) 0x7f4e68;
	do {
		fcn_004e7700(&v8[-0x72]);
		*v8 = *v8 & 0xe0874703;
		v8[1] = v8[1] & 0x3d31ffc7;
		if (*(char*) ((int) v8 - 0x1c6) == 6) {
			v5 = v11;
		}
		v8 = &v8[0x87];
		v11 += 1;
	} while ((int) v8 < 0x85a268);
	*(short*) 0x774970 = (short) v5;
	fcn_00546de0();
	if (!(*(int*) 0x7747b0 & 4) && 7 <= (unsigned short) gm_RandomMod(10)) {
		v11 = fcn_005435d0();
		while (v11 != 1) {
			*(int*) 0x7725c8 = 0;
			*(int*) 0x7e46ac = 0x24087;
			fcn_0051af00(v6, 0x79);
			if (!fcn_00526120(v6, 1)) {
				*(int*) 0x774954 = 1;
				fcn_005356b0(0x5438c0);
				return;
			}
			fcn_0046ac30();
			Sleep(1000);
			v11 = fcn_005435d0();
		}
	}
	*(int*) 0x7e46ac = 0x24087;
	if (*(int*) 0x7747b0 & 4) {
		fcn_00535770(0x24087);
	}
	fcn_004e4f10(0);
	if (fcn_004e6910(v5) && *(int*) 0x6a3420) {
		*(int*) 0x1040488 = 0;
		*(int*) 0x1040480 = *(int*) 0x1040494;
		*(int*) 0x1040484 = 0;
		*(int*) 0x104048c = *(int*) 0x1040490;
		fcn_00476970(*(int*) 0x77250c);
		fcn_00469e30(0x79d);
	}
	fcn_0053f100();
	fcn_00546f80();
	if (*(int*) 0x6a3420) {
		v2 = fcn_00470820(0, 0, 0x6a43ac);
		fcn_00471d80(v2, 3);
		d2_SetForm(v2, 1);
		fcn_00519190(0x7d);
		fcn_00500d60(0x7f4c00, v7);
		d2_SetForm(v2, 0);
		fcn_00471e30(v2);
	}
	v3 = (unsigned char*) gm_StartFilteredEntitySearch(1, 6);
	while (v3) {
		if (*v3 != 0x1e) {
			if (*(char*) (*(int*) 0x868050 + *v3 * 0x24d) == 7) {
				v3[0x69] = 0;
				v3[0x6a] = 0;
				v3[0x6b] = 0;
				v3[0x6c] = 0;
			}
		} else {
			v5 = fcn_005155e0(v3);
			v2 = *(unsigned short*) 0x6b8010;
			if (v5 != -1) {
				fcn_004432d0((int) *(char*) (*(unsigned char*) (*(int*) 0x868050 + *v3 * 0x24d) + 0x7f3b00), 1);
				fcn_0043aa30(3);
				fcn_004bceb0(*(unsigned int*) &v3[0x71]);
				fcn_0043a9c0(3);
				fcn_004432d0(v2, 1);
			}
		}
		v3 = (unsigned char*) gm_FindNextFilteredEntity();
	}
	v5 = 0;
	fcn_005016c0();
	fcn_004facb0();
	if ((*(int*) 0x77494c & 8) || *(int*) 0x14cbca0 == -1) {
		fcn_004f5830();
		fcn_00535960();
		Sleep(100);
		v9 = (char*) 0x7f4ca8;
		do {
			if (*(short*) &v9[-8] != -1 && *v9) {
				fcn_005422c0(v5);
			}
			v9 = &v9[0x21c];
			v5 += 1;
		} while ((int) v9 < 0x85a0a8);
		fcn_00535960();
		Sleep(100);
		fcn_004ff0f0();
		fcn_00535960();
		Sleep(100);
		fcn_004fd0a0();
		fcn_00535960();
		Sleep(100);
		fcn_004fd280(3);
		fcn_004fcc20();
		fcn_00535960();
		Sleep(100);
		fcn_004fd050();
		fcn_004eafe0();
		fcn_00535960();
		Sleep(100);
		fcn_005490a0();
		fcn_005490d0();
		fcn_00535960();
		Sleep(100);
		fcn_004f4d10();
		fcn_00535960();
		Sleep(100);
		fcn_00495890();
		fcn_00535960();
		Sleep(100);
		fcn_004fb390();
		fcn_004fb630(st);
		if (st[1] != -1) {
			fcn_004fb7a0();
		} else {
			fcn_004fb650(1, 0x3f800000, 0x3f000000, *(double*) 0x662aa0 - (double) (4 - *(int*) 0x7747b4) * *(double*) 0x662cc0);
		}
		fcn_00547770();
		fcn_00535960();
		Sleep(100);
		v4 = (unsigned int*) 0x7f4ca4;
		do {
			fcn_004c54c0(0xffffffff, *v4, 0, 3);
			v4 = &v4[0x87];
		} while ((int) v4 < 0x85a0a4);
		fcn_004c54c0(0xffffffff, 0xffffffff, 0, 4);
		fcn_004ad8c0();
	} else {
		fcn_004fd280(2);
	}
	v4 = (unsigned int*) 0x7f4e8c;
	do {
		*v4 = 0;
		v4 = &v4[0x87];
	} while ((int) v4 < 0x85a28c);
	if (*(int*) 0x6a3420) {
		if (*(int*) 0x774965 && !(*(int*) 0x7747b0 & 4)) {
			v2 = fcn_00535570();
			d2_SetForm(v2, 2);
			fcn_00519190(0x7d);
			d2_SetForm(v2, 1);
			fcn_00519190(0x1ba0, *(int*) 0x774970 & 0xffff, *(int*) 0x774970 & 0xffff);
			fcn_004c30a0(0xfffffff9, 0, 0x6a438c, 0xffffffff, 0);
			v5 = fcn_005373e0(0x543080, 0x66087);
			while (v5) {
				if (*(int*) 0x100f1dc == 2) {
					*(int*) 0x774654 = 1;
				}
				v5 = fcn_005373e0(0x543080, 0x66087);
			}
			fcn_00471e30(v2);
			fcn_005448e0();
			*(int*) 0x774954 = 1;
		}
		if (*(int*) 0x6a3420 && !*(int*) 0x774954) {
			v2 = (*(int*) 0x77494c & 8) || *(int*) 0x14cbca0 == -1;
			fcn_004b3aa0(v2);
		}
	}
	if (!(*(int*) 0x77494c & 8) && *(int*) 0x14cbca0 != -1) {
		*(char*) 0x772d10 = (char) v1;
		return;
	}
	fcn_005421f0();
	*(char*) 0x772d10 = (char) v1;
}
