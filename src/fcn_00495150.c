// FUNCTION: GOLDTL 0x495150
// SIZE: 39

extern int g_100af80[];

int __cdecl fcn_00495150(int a1)
{
	int i;
	int n;

	n = *(int*) 0x1008524;
	for (i = 0; i < n; i++) {
		if (g_100af80[i] == a1) {
			return 1;
		}
	}
	return 0;
}
