extern int g_772848;
extern int g_77284c;
extern int g_772890;
extern int g_772894;
extern int g_772898;
extern int g_77289c;
extern int g_7728b4;
extern int g_7728b8;
extern float g_772850;
extern float g_772854;
extern float g_772858;
extern float g_772860;
extern float g_772864;
extern float g_772868;
extern float g_772870;
extern float g_772874;
extern float g_772878;
extern float g_772880;
extern float g_772884;
extern float g_772888;
extern float g_6660f4;
extern unsigned char g_773d75;

int __cdecl fcn_004efd30(int);
int __cdecl fcn_004a6160(char*, void*, int, void*);
void __cdecl fcn_004f10d0(char*, int*, int*);
void __cdecl fcn_004f0f60(int, void*);
float __cdecl fcn_004f1290(char*);
int __cdecl fcn_005e8de0(int, int, void*);
int __cdecl fcn_005e8e50(int, float, void*, void*);
int __cdecl fcn_005ea4d0(void*, void*, void*, void*, void*, void*, void*, void*, void*);
int __cdecl _ftol(void);
float __cdecl fcn_004f0eb0(int, int, int);
int __cdecl fcn_004f0ff0(int, int, int, int, void*, void*);
int __cdecl fcn_0050b810(int, int);
int __cdecl gm_RandomMod(int);

/* ADDRESS: GOLDTL 0x004a6210 */
int __cdecl fcn_004a6210(char* a0, char* a1, int a2)
{
	char buf0[0x40];
	char buf1[16];
	int entry[8];
	float pos[16];
	float spread;
	float level;
	int row;
	int col;
	int state;
	int i;
	int* p;
	int* dst;

	g_772848 = -1;
	g_77284c = -1;
	p = (int*) fcn_004efd30(*(int*) (a1 + 1));
	if (p == 0) {
		return 0;
	}
	if (fcn_004a6160(a1, buf0, a2, buf1) != 0) {
		return 0;
	}
	fcn_004f10d0(a1, &row, &col);
	col = gm_RandomMod(col + 1) & 0xffff;
	fcn_004f0f60(col, buf1);
	if (*(int*) (a0 + 0x194) < *(int*) (buf1 + 4)) {
		return 0;
	}
	level = fcn_004f1290(a1);
	row = gm_RandomMod(row + 1) & 0xffff;
	fcn_005e8de0(g_6660f4, *(int*) (col * 0xc + 0x665290), entry);
	fcn_005e8e50(*(int*) (col * 0xc + 0x665288),
		level * *(float*) (col * 0xc + 0x66528c), entry, &pos[0]);
	pos[4] = pos[0];
	pos[1] = pos[6];
	pos[2] = -0.2617994f;
	pos[3] = 0.7853982f;
	if (fcn_005ea4d0(buf0, buf1, &pos[4], &pos[7], &pos[8], &pos[9],
			&pos[10], &pos[11], &pos[12]) != 0) {
		return 0;
	}
	state = _ftol();
	spread = fcn_004f0eb0(col, state, row + 1);
	if (*(float*) (p + 2 + row) < spread) {
		return 0;
	}
	if (fcn_004f0ff0((int) a0, col, state, row + 1, &pos[13], &pos[14]) == 0) {
		return 0;
	}
	pos[15] = (float) fcn_0050b810(*(int*) (a0 + 0x178), g_773d75);
	if ((int) _ftol() < (int) pos[14]) {
		return 0;
	}
	g_772850 = pos[0];
	g_772854 = pos[5];
	g_772858 = pos[6];
	g_772860 = pos[11];
	g_772864 = pos[12];
	g_772868 = pos[13];
	g_772880 = pos[10];
	g_772884 = pos[7];
	g_772888 = pos[8];
	g_772870 = pos[9];
	g_772874 = pos[10];
	g_772878 = pos[11];
	g_772848 = *(int*) (a0 + 4);
	g_7728b4 = (int) pos[14];
	g_77284c = *(int*) (a1 + 1);
	g_7728b8 = (int) pos[13];
	g_772898 = state;
	g_772894 = row + 1;
	g_772890 = (int) pos[9];
	g_77289c = col;
	dst = (int*) 0x7728a0;
	for (i = 0; i < 5; i++) {
		dst[i] = entry[i];
	}
	return 1;
}
