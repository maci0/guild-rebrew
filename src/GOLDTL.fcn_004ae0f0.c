typedef struct {
	int id;
	int b;
} fcn_004ae0f0_pair;

typedef struct {
	int a;
	fcn_004ae0f0_pair e[8];
} fcn_004ae0f0_group;
// SIZE 0x44

extern char g_1007bc0[];

// FUNCTION: GOLD 0x004adfb0
// FUNCTION: GOLDTL 0x4ae0f0

int __cdecl fcn_004ae0f0(int id)
{
	int j;
	int i;

	for (j = 0; j < 4; j++) {
		for (i = 0; i < 8; i++) {
			if (((fcn_004ae0f0_group*)g_1007bc0)[j].e[i].id == id)
				return 0;
		}
	}
	return 1;
}
