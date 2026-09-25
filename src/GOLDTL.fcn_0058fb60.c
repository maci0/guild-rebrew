// GLOBAL: GOLDTL 0x14b5798
extern int g_14b5798;
// GLOBAL: GOLD 0x144a638
extern int g_14b5798;
// FUNCTION: GOLD 0x005875c0
// SIZE: 50
// FUNCTION: GOLDTL 0x58fb60
// SIZE: 50

int __cdecl fcn_00525fb0(int);
void __cdecl fcn_0058bb10(int, int, int, int, void*);
void __cdecl fcn_00532ef0(void);
void __cdecl fcn_0058d180(void);

void __cdecl fcn_0058fb60(int a)
{
	if (fcn_00525fb0(a) == 0) {
		fcn_0058bb10(0, a, g_14b5798, 1, fcn_0058d180);
		fcn_00532ef0();
	}
}
