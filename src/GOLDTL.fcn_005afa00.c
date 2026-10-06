// FUNCTION: GOLD 0x5a65d0
// FUNCTION: GOLDTL 0x5afa00

int __cdecl fcn_00525fb0(int);
void __cdecl fcn_0052a0c0(int, int);
void __cdecl fcn_005bdc30(int, int, int, void*, int);
void __cdecl fcn_0052a2d0(void);
void __cdecl fcn_005305a0(void);
void __cdecl fcn_005af7f0(void);
extern int g_14abcdc;

void __cdecl fcn_005afa00(int a)
{
	if (fcn_00525fb0(a) == 0 && a != 0) {
		fcn_0052a0c0(a, 0);
		fcn_005bdc30(4, 0, g_14abcdc, fcn_005af7f0, 0);
		fcn_0052a2d0();
		fcn_005305a0();
	}
}
