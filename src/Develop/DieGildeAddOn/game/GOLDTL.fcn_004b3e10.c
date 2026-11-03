

typedef struct {
	int f0;
	int f4;
	int f8;
	char pad[0x14];
	char f20;
	char pad2[3];
} rec24;
// SIZE 0x24

extern signed char g_6a3440;
extern char g_10069a0[];

void __cdecl sim_SetSyncParams(int*, int, int, int);

rec24* __cdecl fcn_004b3e10(int a1, int a2)
{
	int i;

	if ((*(char*)&g_6a3440) == 5) {
		((rec24*)g_10069a0)[0].f0 = a2;
		((rec24*)g_10069a0)[0].f4 = a1;
		((rec24*)g_10069a0)[0].f8 = 0;
		sim_SetSyncParams(&((rec24*)g_10069a0)[0].f8, 0, 0, 0);
		((rec24*)g_10069a0)[0].f20 = 0;
		return &((rec24*)g_10069a0)[0];
	}
	for (i = 0; i < 128; i++) {
		if (((rec24*)g_10069a0)[i].f0 == 0) {
			((rec24*)g_10069a0)[i].f0 = a2;
			((rec24*)g_10069a0)[i].f4 = a1;
			((rec24*)g_10069a0)[i].f8 = 0;
			sim_SetSyncParams(&((rec24*)g_10069a0)[i].f8, 0, 0, 0);
			((rec24*)g_10069a0)[i].f20 = 0;
			return &((rec24*)g_10069a0)[i];
		}
	}
	return 0;
}
#if defined(REBREW_SERVER) || defined(REBREW_GOLD)
#if defined(REBREW_SERVER) || defined(REBREW_GOLD)
unsigned char _dpad_10058a0[4352];
unsigned char _dpad_10069a0[6784];
#else
/* Reference gaps only; the emitted objects inside the span keep their own rows. */
unsigned char _dpad_10058c0[32];
unsigned char _dpad_10058e8[24];
unsigned char _dpad_1005914[2044];
unsigned char _dpad_1006118[2044];
unsigned char _dpad_1006918[8];
unsigned char _dpad_1006924[124];
unsigned char _dpad_10069ac[20];
unsigned char _dpad_10069c1[4575];
unsigned char _dpad_1007ba1[31];
unsigned char _dpad_1007bc2[270];
unsigned char _dpad_1007cd8[8];
unsigned char _dpad_1007d40[288];
unsigned char _dpad_1007e68[1080];
unsigned char _dpad_10082a4[380];
#endif
#else
/* Reference gaps only; the emitted objects inside the span keep their own rows. */
unsigned char _dpad_10058c0[32];
unsigned char _dpad_10058e8[24];
unsigned char _dpad_1005914[2044];
unsigned char _dpad_1006118[2044];
unsigned char _dpad_1006918[8];
unsigned char _dpad_1006924[124];
unsigned char _dpad_10069ac[20];
unsigned char _dpad_10069c1[4575];
unsigned char _dpad_1007ba1[31];
unsigned char _dpad_1007bc2[270];
unsigned char _dpad_1007cd8[8];
unsigned char _dpad_1007d40[288];
unsigned char _dpad_1007e68[1080];
unsigned char _dpad_10082a4[380];
#endif
