// GLOBAL: GOLDTL 0x1008524
extern int g_1008524;
// GLOBAL: GOLD 0xf83ea4
extern int g_1008524;
// GLOBAL: GOLDTL 0x100af80
extern int g_100af80[];
// GLOBAL: GOLD 0xf86900
extern int g_100af80[];
// FUNCTION: GOLD 0x00495790
// SIZE: 39
// FUNCTION: GOLDTL 0x495150
// SIZE: 39

int __cdecl fcn_00495150(int a1)
{
	int i;
	int n;

	n = g_1008524;
	for (i = 0; i < n; i++) {
		if (g_100af80[i] == a1) {
			return 1;
		}
	}
	return 0;
}
