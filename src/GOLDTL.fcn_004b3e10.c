

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
