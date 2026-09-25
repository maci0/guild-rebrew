// FUNCTION: GOLD 0x4206d0
// SIZE: 176
// FUNCTION: GOLDTL 0x0041bcd0
// SIZE: 176

extern int g_6b6f3c;
void __cdecl fcn_0041bdc0(void);
int __cdecl fcn_0041be70(void);
void __cdecl fcn_0041bf00(void);
int __cdecl fcn_0041bf90(void* dst, int n);
void __cdecl fcn_0041c290(int a);
void __cdecl fcn_0041c3b0(int a, int b);
int __cdecl fcn_0041c470(void* dst, void* src, int w, int h, int pitch);
void __cdecl fcn_0041bd80(int a);

int __cdecl fcn_0041bcd0(void* dst, void* src, int w, int h, int mode, int pitch, int fmt)
{
	if (g_6b6f3c == 0) {
		g_6b6f3c = 1;
		fcn_0041bdc0();
	}
	if (!fcn_0041be70()) {
		fcn_0041bf00();
		return 0;
	}
	if (!fcn_0041bf90(dst, w * h)) {
		fcn_0041bf00();
		return 0;
	}
	fcn_0041c290(mode);
	fcn_0041c3b0(0, 0);
	if (!fcn_0041c470(dst, src, w, h, pitch)) {
		fcn_0041bf00();
		return 0;
	}
	fcn_0041bf00();
	fcn_0041bd80(fmt);
	return 1;
}
