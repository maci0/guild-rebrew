// FUNCTION: GOLDTL 0x58c4f0
// SIZE: 378

// SIZE 0x2f4
struct gadget {
	char pad0[0x38];
	int focus;
	int hot;
	char pad40[0x1c];
	int visible;
	char pad60[0x170];
	int mode;
	char pad1d4[0x11c];
	char* image;
};

// SIZE 0x41
struct icon {
	char pad[0x41];
};

extern struct gadget* g_1015ea0;
extern struct icon* g_99ec10;
extern int g_665f58[4];
extern int g_665f84[4];
extern int g_772514;
extern char g_6811b0[];

void __cdecl fcn_004727a0(int, int);
int __cdecl fcn_00519190(int, ...);
int __cdecl fcn_0046f740(int, int, int, int);
void __cdecl fcn_00472640(int, int);

void __cdecl fcn_0058c4f0(char* a, int dlg, int mode, int* ids, int* sel)
{
	char* s;
	int i;

	s = *(char**) (a + 0x65);
	fcn_004727a0(dlg, mode);
	fcn_00519190((int) g_6811b0);
	for (i = 0; i < 4; i++) {
		ids[i] = fcn_0046f740(6 + i * 0x6c, 0, g_665f58[i], g_772514);
		g_1015ea0[ids[i]].visible = 1;
		g_1015ea0[ids[i]].mode = 3;
		g_1015ea0[ids[i]].image = (char*) &g_99ec10[g_665f84[i]];
	}
	fcn_00472640(ids[1], (unsigned char) s[0x19]);
	fcn_00472640(ids[2], (unsigned char) s[0x1a]);
	fcn_00472640(ids[3], (unsigned char) s[0x1b]);
	if (*sel == 3 && s[0x1b] == 1) {
		g_1015ea0[ids[3]].hot = 1;
	} else if (*sel == 2 && s[0x1a] == 1) {
		g_1015ea0[ids[2]].hot = 1;
	} else if (*sel == 1 && s[0x19] == 1) {
		g_1015ea0[ids[1]].hot = 1;
	} else {
		g_1015ea0[ids[0]].hot = 1;
		*sel = 0;
	}
	g_1015ea0[ids[*sel]].focus = 1;
}
