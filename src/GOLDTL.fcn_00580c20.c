// FUNCTION: GOLD 0x00578630
// SIZE: 196
// FUNCTION: GOLDTL 0x00580c20
// SIZE: 196

extern int* g_665f08;
extern int g_7749f8[];
extern int g_774a10;
extern int g_774a14;
extern int g_774a18;

void __cdecl fcn_004230e0(int);
void __cdecl fcn_00580cf0(int);
void __cdecl fcn_00471e30(int);

void __cdecl fcn_00580c20(void)
{
	int i;

	for (i = 0; i < 6; i++) {
		if (g_7749f8[i] != 0) {
			fcn_004230e0(g_7749f8[i]);
		}
	}
	fcn_00580cf0(g_774a10);
	g_774a10 = 0;
	g_665f08[0] = 0;
	g_665f08[2] = 0;
	g_665f08[3] = 0;
	g_665f08[4] = 0;
	g_665f08[5] = 0;
	g_665f08[6] = 0;
	g_665f08[7] = 0;
	g_665f08[8] = -1;
	fcn_00471e30(g_665f08[9]);
	g_665f08[9] = -1;
	fcn_00471e30(g_665f08[13]);
	g_665f08[13] = -1;
	g_665f08[5] = 0;
	g_774a14 = 0;
	g_774a18 = 0;
}
