typedef struct {
	int id;
	int b;
} fcn_004b2020_pair;

typedef struct {
	int a;
	fcn_004b2020_pair e[8];
} fcn_004b2020_group;
// SIZE 0x44

extern char g_1007bc0[];


/* ADDRESS: GOLDTL 0x004b2020 */
int __cdecl fcn_004b2020(unsigned short g)
{
	int i;

	if (g >= 4)
		return 0;
	((fcn_004b2020_group*)g_1007bc0)[g].a = 1;
	for (i = 0; i < 4; i++) {
		((fcn_004b2020_group*)g_1007bc0)[g].e[i].id = -1;
		((fcn_004b2020_group*)g_1007bc0)[g].e[i].b = 0xffff;
	}
	return 1;
}
