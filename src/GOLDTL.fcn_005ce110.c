extern int g_772514;
extern char g_7f4ca0[];

int __cdecl fcn_004e8b80(int, int, char*);
int __cdecl fcn_00470820(int, int, char*);
void __cdecl fcn_00471b60(int);
void __cdecl fcn_004727a0(int, int);
void __cdecl fcn_0046e830(int, int, int, int, int);
int __cdecl fcn_00519190(int, ...);
int __cdecl fcn_00508e40(int);
int __cdecl fcn_004ad2b0(void);
int __cdecl fcn_005373e0(void*, int);
void __cdecl fcn_005ce0f0(void);
void __cdecl fcn_00471e30(int);

/* ADDRESS: GOLDTL 0x005ce110 */
void __cdecl fcn_005ce110(int a0)
{
	char rec[0x88];
	char* s;
	char* v5;
	char* v6;
	unsigned short* h;
	unsigned short* pick[4];
	int v8;
	int v9;
	int n;
	int i;
	int j;
	int k;
	int found;

	n = fcn_004e8b80(a0, 6, rec);
	if (n <= 0) {
		return;
	}
	v8 = fcn_00470820(0, 0, "special\\tagesordnung");
	fcn_00471b60(v8);
	fcn_004727a0(v8, 2);
	fcn_004727a0(v8, 4);
	fcn_0046e830(0xffffffff, 0xffffffff, g_772514, g_772514, 0x767);
	fcn_004727a0(v8, 3);
	fcn_004727a0(v8, 5);
	fcn_0046e830(0xffffffff, 0xffffffff, g_772514, g_772514, 0x767);
	fcn_004727a0(v8, 1);
	fcn_00519190((int) (g_7f4ca0 + 0x13a3));
	fcn_004727a0(v8, 2);
	fcn_00519190(0x139e);
	found = 0;
	for (i = 0; i < n; i++) {
		if (rec[i * 0x18 + 0xc] == 2) {
			s = (char*) fcn_00508e40(*(int*) (rec + i * 0x18));
			v6 = (char*) fcn_00508e40(*(int*) (rec + i * 0x18 + 0x10));
			if (s != 0 && v6 != 0) {
				found = 1;
				if (*(char*) (s + 9) != 0) {
					v9 = *(unsigned char*) (rec + i * 0x18 + 4) + 0x27b;
				} else {
					v9 = *(unsigned char*) (rec + i * 0x18 + 4) + 0x253;
				}
				fcn_00519190(0x139f, *(unsigned short*) v6, *(unsigned short*) s, v9);
			}
		}
	}
	if (found == 0) {
		fcn_00519190(0x139d);
	}
	fcn_004727a0(v8, 3);
	if (a0 >= 8) {
		k = fcn_004ad2b0();
		v9 = 0;
		pick[0] = 0;
		pick[1] = 0;
		pick[2] = 0;
		pick[3] = 0;
		if (k != 0) {
			if (k != 0x24) {
				if (k != 0x25) {
					v9 = 0x4000;
				} else {
					v9 = 0;
				}
			} else {
				v9 = 0x8000;
			}
		}
		i = 0;
		h = (unsigned short*) g_7f4ca0;
		do {
			if ((int) h >= 0x85a0a0) {
				break;
			}
			if ((*(unsigned int*) ((char*) h + 0x1cc) & v9) != 0) {
				pick[i] = h;
				i += 1;
			}
			h = (unsigned short*) ((char*) h + 0x21c);
		} while (i < 4);
		fcn_00519190(0x13a2);
		if (k != 0) {
			fcn_00519190(0x13a3, k + 0x253);
			for (j = 0; j < i; j++) {
				if (j != 0) {
					fcn_00519190((int) "$A$Z%1N2", *pick[j]);
				} else {
					fcn_00519190((int) "$2A$Z%1N2", *pick[0]);
				}
			}
		}
		if (i == 0) {
			goto no_pick;
		}
	} else {
		fcn_00519190(0x13a0);
		i = 0;
		for (j = 0; j < n; j++) {
			if (rec[j * 0x18 + 8] == 3) {
				i = 1;
				found = 0;
				fcn_00519190(0x13a1, *(unsigned char*) (rec + j * 0x18) + 0x253);
				k = 0;
				h = (unsigned short*) g_7f4ca0;
				do {
					if (k >= 4) {
						break;
					}
					if (*(unsigned char*) ((char*) h + 0x168) == *(unsigned char*) (rec + j * 0x18)) {
						found = 1;
						fcn_00519190((int) "$A$Z%1N2", *h);
						k += 1;
					}
					h = (unsigned short*) ((char*) h + 0x21c);
				} while ((int) h < 0x85a0a0);
				if (found == 0) {
					fcn_00519190(0x139d);
				}
			}
		}
		if (i != 0) {
			goto have_pick;
		}
no_pick:
		fcn_00519190(0x139d);
	}
have_pick:
	do {
		if (*(int*) 0x14ce8e0 != 0) {
			*(int*) 0x774654 = 1;
		}
	} while (fcn_005373e0((void*) fcn_005ce0f0, 0x657c7) != 0);
	fcn_00471e30(v8);
}
