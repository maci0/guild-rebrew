// FUNCTION: GOLD 0x58aff0
// SIZE: 128
// FUNCTION: GOLDTL 0x005934d0
// SIZE: 128

extern int* g_774a34;

int __cdecl fcn_004ce1d0(void);
int __cdecl fcn_004c4450(int);
void __cdecl fcn_00535960(void);
int* __cdecl fcn_004ce180(void);
int __cdecl fcn_004ce3e0(int);

void __cdecl fcn_005934d0(void)
{
	int h;
	int r;
	int i;

	h = fcn_004ce1d0();
	while (fcn_004c4450(h) == 0) {
		fcn_00535960();
	}
	g_774a34 = fcn_004ce180();
	r = -1;
	for (i = 1; i < 9; i++) {
		if (g_774a34[i] != 0) {
			r = fcn_004ce3e0(g_774a34[i]);
		}
	}
	if (r != -1) {
		while (fcn_004c4450(r) == 0) {
			fcn_00535960();
		}
	}
}
