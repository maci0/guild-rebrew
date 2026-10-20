void __cdecl fcn_00471e30(int);
void __cdecl fcn_004125c0(int, int);
int __cdecl fcn_00591190(int);
int __cdecl fcn_00590b80(int);
int __cdecl fcn_005909d0(int);
int __cdecl fcn_005913e0(int);
int __cdecl fcn_00591490(int*);
void __cdecl fcn_004707d0(int);

/* ADDRESS: GOLDTL 0x00590670 */
void __cdecl fcn_00590670(void)
{
	unsigned short* p;
	int v3;
	int v4;
	int v5;
	int v6;
	int v7;
	unsigned char b;

	v4 = 0;
	v6 = 0;
	v7 = 0;
	p = 0;
	v3 = *(int*) 0x100f888;
	v5 = *(int*) 0x6a99e8;
	if ((v3 == -1 && v5 != -1)
		|| (*(int*) 0x774a24 != 0 && *(int*) 0x14ce8e8 == 0 && v5 != -1)) {
		fcn_00471e30(*(int*) 0x6a99e8);
		*(int*) 0x6a99e8 = -1;
		*(int*) 0x6a99f0 = -1;
		*(int*) 0x6a99ec = -1;
		*(int*) 0x774a24 = 0;
		*(int*) 0x6772c4 = 1;
		fcn_004125c0(*(int*) 0x100f1e8, *(int*) 0x100f1ec);
		v3 = *(int*) 0x100f888;
		v5 = *(int*) 0x6a99e8;
	}
	if (*(int*) 0x7746a4 != 0 && *(int*) 0x774a24 != *(int*) 0x7746a4
		&& *(int*) 0x14ce8e8 != 0) {
		v4 = 0;
		if (*(int*) 0x7746ac == 0) {
			v7 = *(int*) 0x7746a4;
		}
		else {
			v4 = *(unsigned short*) 0x7746ac;
			if (v4 == 0) {
				v7 = *(int*) 0x7746a4;
			}
		}
		*(int*) 0x774a24 = *(int*) 0x7746a4;
		*(int*) 0x6a99ec = -1;
	}
	if (v3 != -1 && v3 != *(int*) 0x6a99ec) {
		p = *(unsigned short**) (*(int*) 0x1015ea0 + 0x2f0
			+ *(int*) 0x67d370 * 0x2f4);
		if (p != 0) {
			if ((unsigned int) p >= 0x7f4ca0 && (unsigned int) p <= 0x85a09f) {
				if (*p == 0xffff) {
					p = 0;
				}
			}
			else if ((unsigned int) p >= 0x90e094 && (unsigned int) p < 0x90e094 + 0x5480) {
				v6 = *(unsigned char*) p;
				if (v6 >= 0x58) {
					v6 = 0;
				}
			}
			else if ((unsigned int) p >= 0x868050 && (unsigned int) p < 0x868050 + 0x653c) {
				v6 = ((int) p - 0x868050) / 0x24d;
			}
			else if ((unsigned int) p >= 0x868054 && (unsigned int) p < 0x868054 + 0xa790c) {
				v4 = *p;
				if (v4 >= 0x2dc) {
					v4 = 0;
				}
			}
			else if ((unsigned int) p >= 0x99ec10 && (unsigned int) p < 0x99ec10 + 0x5cee) {
				v4 = ((int) p - 0x99ec10) / 0x41;
			}
			else {
				p = 0;
			}
		}
		else if (0xdf <= v3) {
			if (0x427 <= v3) {
				if (v3 <= 0x47e) {
					v6 = v3 - 0x427;
				}
			}
			else {
				v4 = v3 - 0xdf;
			}
		}
		else if (0x427 <= v3) {
			if (v3 <= 0x47e) {
				v6 = v3 - 0x427;
			}
		}
		*(int*) 0x774a24 = 0;
	}
	if (v4 != 0 || v6 != 0 || v7 != 0 || p != 0) {
		if (v5 != -1) {
			fcn_00471e30(v5);
			v5 = -1;
			*(int*) 0x6a99e8 = -1;
			*(int*) 0x6a99f0 = -1;
			v3 = *(int*) 0x100f888;
		}
		if (v4 != 0) {
			b = *(unsigned char*) (0x99ec10 + v4 * 0x41);
			if (b != 0x20 && b != 0x17 && b != 0x25 && b != 0x27) {
				v5 = fcn_00591190(v4);
			}
			else {
				v5 = fcn_00590b80(v4);
			}
			v3 = *(int*) 0x100f888;
			*(int*) 0x6a99e8 = v5;
		}
		else if (v6 != 0) {
			v5 = fcn_005909d0(v6);
			v3 = *(int*) 0x100f888;
			*(int*) 0x6a99e8 = v5;
		}
		else if (v7 != 0) {
			v5 = fcn_005913e0(v7);
			v3 = *(int*) 0x100f888;
			*(int*) 0x6a99e8 = v5;
		}
		else if (p != 0) {
			v5 = fcn_00591490((int*) p);
			v3 = *(int*) 0x100f888;
			*(int*) 0x6a99e8 = v5;
		}
		if (v5 == -1) {
			*(int*) 0x6a99ec = -1;
			*(int*) 0x774a24 = 0;
		}
		else {
			*(int*) 0x6a99f0 = *(int*) (v5 * 700 + 0x1038144);
			*(int*) 0x6a99ec = v3;
			if (*(int*) 0x14ce8e8 != 0) {
				*(int*) 0x6772c4 = 0;
			}
		}
	}
	if (v5 != -1) {
		*(int*) 0x7725c8 = 1;
		*(int*) 0x774a28 = 1;
		fcn_004707d0(v5);
		return;
	}
	if (*(int*) 0x774a28 == 0) {
		return;
	}
	*(int*) 0x7725c8 = 0;
	*(int*) 0x774a28 = 0;
}
