/* Pick three free building sites around the selected plot and place the
 * scene objects there. */

extern char g_7f4ca0[];
extern __int64 g_666018;
extern int g_66601c;
char* __cdecl gm_LookupEntityRecordById(int);
int __cdecl io_FormatTextBuffer(char*, int, ...);
int __cdecl fcn_005cd440(int*, char*, int, int);
int __cdecl fcn_005c6270(void*, int);
unsigned int __cdecl gm_RandomMod(int);
void __cdecl fcn_004c54c0(int, int, int, int);
void __cdecl fcn_00545d40(int, int, char*, int, int, char*);
int __cdecl fcn_005c6220(int, char*);
void __cdecl fcn_005dbe90(char*);

/* ADDRESS: GOLDTL 0x005dd5a0 */
unsigned int __cdecl fcn_005dd5a0(unsigned short* a0, unsigned int* a1)
{
	char v10[256];
	char v11[2048];
	unsigned int v8[20];
	unsigned short* v12[3];
	char v13[4];
	int v14;
	int v15;
	int v16;
	int v3;
	int v4;
	int v5;
	int v6;
	int v7;
	char v2;

	a1[4] = 1;
	if ((char) a0[1] == 6) {
		for (v6 = 0; v6 < 0x14; v6++) {
			v8[v6] = 0;
		}
		for (v6 = 0; v6 < 8; v6++) {
			v8[v6 + 7] = 0xffffffff;
		}
		io_FormatTextBuffer(v10, 0x9c);
		v8[2] = *(unsigned int*) &g_666018;
		v8[0] = 0;
		v8[1] = 0x400;
		v8[4] = 6;
		v8[3] = g_66601c;
		v4 = fcn_005cd440((int*) v8, v10, 0, 0);
	} else {
		v4 = (int) gm_LookupEntityRecordById(a1[1]);
	}
	if (!v4) {
		return 0;
	}
	v6 = (fcn_005c6270((void*) a0, 0x2c5) != 0) + 1;
	v5 = gm_RandomMod(0x300) & 0xffff;
	v14 = 0x300;
	do {
		if (v5 != *(unsigned short*) v4 && v5 != *a0) {
			v7 = v5 * 0x21c;
			if (*(short*) (g_7f4ca0 + v7) != -1 &&
			    *(unsigned char*) (g_7f4ca0 + v7 + 2) < 10 &&
			    *(char*) (g_7f4ca0 + v7 + 0x166)) {
				v12[0] = (unsigned short*) (g_7f4ca0 + v7);
				break;
			}
		}
		v14 -= 1;
		v5 = (v5 + 1) % 0x300;
	} while (v14);
	v5 = gm_RandomMod(0x300) & 0xffff;
	v14 = 0x300;
	do {
		if (v5 != *(unsigned short*) v4 && v5 != *a0 && v5 != *v12[0]) {
			v7 = v5 * 0x21c;
			if (*(short*) (g_7f4ca0 + v7) != -1 &&
			    *(unsigned char*) (g_7f4ca0 + v7 + 2) < 10 &&
			    *(char*) (g_7f4ca0 + v7 + 0x166)) {
				v12[1] = (unsigned short*) (g_7f4ca0 + v7);
				break;
			}
		}
		v5 = (v5 + 7) % 0x300;
		v14 -= 1;
	} while (v14);
	v5 = gm_RandomMod(0x300) & 0xffff;
	v14 = 0x300;
	while (v5 == *(unsigned short*) v4 || v5 == *a0 ||
	       v5 == *v12[0] || v5 == *v12[1] ||
	       (v7 = v5 * 0x21c, *(short*) (g_7f4ca0 + v7) == -1) ||
	       *(unsigned char*) (g_7f4ca0 + v7 + 2) >= 10 ||
	       !*(char*) (g_7f4ca0 + v7 + 0x166)) {
		v5 = (v5 + 0xd) % 0x300;
		v14 -= 1;
		if (!v14) {
			v15 = (int) v12[2];
			goto label_5dd807;
		}
	}
	v15 = v5 * 0x21c + (int) g_7f4ca0;
	v12[2] = (unsigned short*) v15;
label_5dd807:
	v6 *= -0x14;
	fcn_004c54c0(*(int*) (v4 + 4), *(int*) (v12[0] + 2), v6, 1);
	v3 = (int) v12[1];
	fcn_004c54c0(*(int*) (v4 + 4), *(int*) (v12[1] + 2), v6, 1);
	fcn_004c54c0(*(int*) (v4 + 4), *(int*) (v15 + 4), v6, 1);
	if ((char) *(unsigned short*) (v4 + 2) == 6 ||
	    (char) *(unsigned short*) (v4 + 2) == 7) {
		io_FormatTextBuffer(v11, 0xfec, *(unsigned short*) v12[0],
		             *(unsigned short*) v12[1], *(unsigned short*) v15);
		fcn_00545d40(*(int*) (v4 + 4), 0xffffffff, v11, 1, 0x5fb, 0);
	}
	io_FormatTextBuffer(v11, 0xfed, *(unsigned short*) v4);
	for (v6 = 0; v6 < 3; v6++) {
		v2 = (char) v12[v6][1];
		if (v2 == 6 || v2 == 7) {
			fcn_00545d40(*(int*) (v12[v6] + 2), 0xffffffff, v11, 0, 0x5fb,
			             0);
		}
	}
	if ((char) a0[1] != 6) {
		return 1;
	}
	v6 = fcn_005c6220((int) *(unsigned short*) *a1, v13);
	io_FormatTextBuffer(v11, 0xfe8, *(unsigned short*) (v6 + 0x18) + 1,
	             *(unsigned short*) v12[0], *(unsigned short*) v3, *(unsigned short*) v15);
	fcn_005dbe90(v11);
	return 1;
}
