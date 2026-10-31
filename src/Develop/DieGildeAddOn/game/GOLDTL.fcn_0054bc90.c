extern void __cdecl gm_ResolveEntityById(char**, int, int, int);
extern char* __cdecl fcn_00502cd0(int, ...);
extern void __cdecl fcn_00546190(char*);
extern char* __cdecl fcn_005463a0(int, int, int, ...);
extern int __cdecl fcn_004943e0(unsigned short*, unsigned short*);
extern void __cdecl io_FormatTextBuffer(char*, int, ...);
extern void __cdecl fcn_004c4510(char*, unsigned int);
extern int __cdecl fcn_004c4570(unsigned char, unsigned char, unsigned short, char*);
extern void __cdecl fcn_004c5360(void);
extern int __cdecl fcn_004c5620(int, char*);
extern int __cdecl fcn_00500cb0(char*, char*);
extern void __cdecl fcn_00545780(char*);
extern int __cdecl fcn_00545d40(int, int, char*, unsigned char, int, char*);
extern int __cdecl fcn_00545670(char*, int, int, char*, int);
extern int __cdecl d2_SetForm(int, int);
extern void __cdecl io_AppendText(int, ...);
extern void __cdecl fcn_00500bb0(void*, int, int, int);
extern int __cdecl fcn_004c3030(int, int, char*, int);

/* ADDRESS: GOLDTL 0x0054bc90 */
void __cdecl fcn_0054bc90(char* a0)
{
	char text[512];
	char* v10;
	char* v13;
	char* v15;
	char* arr;
	int v1;
	int v2;
	int v11;
	int v16;
	int state;
	int idx;
	unsigned short v5;
	unsigned short v6;
	unsigned short* v3;
	unsigned short* v7;
	char v4;

	v13 = 0;
	v15 = 0;
	v10 = 0;
	if (*(int*) (a0 + 0x70) == -1 || *(int*) (a0 + 0x70) == -2)
		goto close;
	if (*(int*) (a0 + 0xbc) == 0) {
		gm_ResolveEntityById(&v10, 0, 0, *(unsigned int*) (a0 + 0x10));
		if (v10 == 0)
			goto close;
		v13 = fcn_00502cd0(*(unsigned int*) (v10 + 0x5d), 1, 0, 0x17);
		if (v13 == 0)
			goto close;
		v5 = *(unsigned short*) (v10 + 0x27);
		if (v5 == 0xffff)
			goto close;
	} else if (*(int*) (a0 + 0xbc) == 1) {
		v15 = fcn_005463a0(2, 1, *(unsigned int*) (a0 + 0xc0), 0, 0x37);
		if (v15 == 0)
			goto close;
		v5 = *(unsigned short*) (v15 + 8);
	} else {
		fcn_00546190(a0);
		return;
	}
	v1 = (unsigned int) v5 * 0x21c;
	v7 = (unsigned short*) (v1 + 0x7f4ca0);
	if (v7 == 0)
		goto close;
	v4 = *(char*) ((unsigned int) *(unsigned short*) (a0 + 8) * 0x21c + 0x7f4ca2);
	v2 = (unsigned int) *(unsigned short*) (a0 + 8) * 0x21c;
	v3 = (unsigned short*) (v2 + 0x7f4ca0);
	if (v4 != 6 && v4 != 7)
		*(int*) (a0 + 0x70) = 2;
	state = *(int*) (a0 + 0x70);
	if (state == 0)
		goto dialog;
	if (state == 1)
		goto state1;
	if (state != 2) {
	close:
		if (*(int*) (a0 + 0x74))
			fcn_00545780(a0);
		fcn_00546190(a0);
		return;
	}
	if (fcn_004943e0(v7, v3) != 1)
		goto state2_unequal;
	v16 = *(int*) (v3 + 2);
	idx = 0;
	if (*(int*) (a0 + 0xbc) == 0)
		arr = v13 + 0x1c;
	else
		arr = v15 + 0xac;
	for (;;) {
		if (*(int*) (arr + idx * 4) == v16)
			break;
		idx++;
		if (idx >= 4) {
			fcn_00546190(a0);
			return;
		}
	}
	if (idx >= 4) {
	close2:
		fcn_00546190(a0);
		return;
	}
	io_FormatTextBuffer(text, 0x1785, *v3);
	goto state2_report;
state2_unequal:
	v11 = -1;
	idx = 0;
	if (*(int*) (a0 + 0xbc) == 0) {
		v16 = *(int*) (v3 + 2);
		arr = v13 + 0x1c;
		for (;;) {
			if (*(int*) (arr + idx * 4) == v16)
				break;
			idx++;
			if (idx >= 4) {
				fcn_00546190(a0);
				return;
			}
		}
		fcn_004c4510(v13, *(unsigned int*) (v13 + 2));
		fcn_004c4570(4, 1, idx * 4 + 0x1c, (char*) &v11);
		fcn_004c5360();
	} else {
		v16 = *(int*) (v3 + 2);
		arr = v15 + 0xac;
		for (;;) {
			if (*(int*) (arr + idx * 4) == v16)
				break;
			idx++;
			if (idx >= 4) {
				fcn_00546190(a0);
				return;
			}
		}
		*(int*) (v15 + 0xac + idx * 4) = -1;
		fcn_004c5620(0, a0);
	}
	if (idx >= 4)
		goto close2;
	io_FormatTextBuffer(text, 0x1786, *v3);
state2_report:
	v16 = *(int*) (v1 + 0x7f4ca4);
	fcn_00545d40(v16, -1, text, 0, 0x5ec, 0);
	fcn_00546190(a0);
	return;
state1:
	if (fcn_00500cb0((char*) 0x7f4c00, a0 + 0x52) > 0) {
		fcn_00545780(a0);
		*(int*) (a0 + 0x70) = *(int*) (a0 + 0x70) + 1;
		return;
	}
	if (*(int*) 0x100f884 != *(int*) (*(int*) (a0 + 0x74) + 8))
		return;
	v11 = -1;
	if (*(int*) 0x100f1dc == -1)
		return;
	if (*(int*) 0x100f1dc == 2) {
		v16 = *(int*) (v3 + 2);
		idx = 0;
		if (*(int*) (a0 + 0xbc) == 0)
			arr = v13 + 0x1c;
		else
			arr = v15 + 0xac;
		for (;;) {
			if (*(int*) (arr + idx * 4) == v16)
				break;
			idx++;
			if (idx >= 4) {
				fcn_00545780(a0);
				fcn_00546190(a0);
				return;
			}
		}
		if (idx >= 4) {
			fcn_00545780(a0);
			fcn_00546190(a0);
			return;
		}
		io_FormatTextBuffer(text, 0x1785, *v3);
	} else if (*(int*) 0x100f1dc == 1) {
		v16 = *(int*) (v3 + 2);
		idx = 0;
		if (*(int*) (a0 + 0xbc) == 0) {
			arr = v13 + 0x1c;
			for (;;) {
				if (*(int*) (arr + idx * 4) == v16)
					break;
				idx++;
				if (idx >= 4) {
					fcn_00545780(a0);
					fcn_00546190(a0);
					return;
				}
			}
			fcn_004c4510(v13, *(unsigned int*) (v13 + 2));
			fcn_004c4570(4, 1, idx * 4 + 0x1c, (char*) &v11);
			fcn_004c5360();
		} else {
			arr = v15 + 0xac;
			for (;;) {
				if (*(int*) (arr + idx * 4) == v16)
					break;
				idx++;
				if (idx >= 4) {
					fcn_00545780(a0);
					fcn_00546190(a0);
					return;
				}
			}
			*(int*) (v15 + 0xac + idx * 4) = -1;
			fcn_004c5620(0, a0);
		}
		if (idx >= 4) {
			fcn_00545780(a0);
			fcn_00546190(a0);
			return;
		}
		io_FormatTextBuffer(text, 0x1786, *v3);
	} else {
		fcn_00545780(a0);
		fcn_00546190(a0);
		return;
	}
	v16 = *(int*) (v1 + 0x7f4ca4);
	fcn_00545d40(v16, -1, text, 0, 0x5ec, 0);
	fcn_00545780(a0);
	fcn_00546190(a0);
	return;
dialog:
	fcn_00545670(a0, 0, 0, (char*) 0x6a5a10, 0x5ec);
	if (*(int*) (a0 + 0x74) == 0) {
		fcn_00546190(a0);
		return;
	}
	d2_SetForm(*(int*) (*(int*) (a0 + 0x74) + 8), 0);
	v6 = *v7;
	if (*(int*) (a0 + 0xbc) != 0)
		io_AppendText(0x1771, *(unsigned short*) (v10 + 0x27), *v3, a0 + 0xac, v6, *v3);
	else
		io_AppendText(0x1770, *(unsigned short*) (v10 + 0x27), *v3, a0 + 0xac, v10, v6, *v3);
	*(int*) (a0 + 0x44) = *(int*) 0x7f4c00;
	*(int*) (a0 + 0x48) = *(int*) 0x7f4c04;
	*(int*) (a0 + 0x4c) = *(int*) 0x7f4c08;
	*(unsigned short*) (a0 + 0x50) = *(unsigned short*) 0x7f4c0c;
	*(int*) (a0 + 0x52) = *(int*) 0x7f4c00;
	*(int*) (a0 + 0x56) = *(int*) 0x7f4c04;
	*(int*) (a0 + 0x5a) = *(int*) 0x7f4c08;
	*(unsigned short*) (a0 + 0x5e) = *(unsigned short*) 0x7f4c0c;
	fcn_00500bb0(a0 + 0x52, 0x18, 0, 0);
	fcn_004c3030(-7, 0, (char*) 0x6a5a34, 0);
	*(int*) (a0 + 0x70) = *(int*) (a0 + 0x70) + 1;
}
