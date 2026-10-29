typedef struct {
	int id;
	int b;
} fcn_004b2070_pair;

typedef struct {
	int a;
	fcn_004b2070_pair e[8];
} fcn_004b2070_group;
// SIZE 0x44

typedef struct {
	char name[0x74];
} fcn_004b2070_rec;

extern char g_1007bc0[];
extern char g_149d120[][0x74];
extern char g_6808a4[];

int __cdecl fcn_0065f2f0(char*, char*, int);
void __cdecl fcn_0042d670(fcn_004b2070_rec*);


/* ADDRESS: GOLDTL 0x004b2070 */
void __cdecl fcn_004b2070(void)
{
	int j;
	int i;

	for (j = 0; j < 4; j++) {
		((fcn_004b2070_group*)g_1007bc0)[j].a = 1;
		for (i = 0; i < 4; i++) {
			((fcn_004b2070_group*)g_1007bc0)[j].e[i].id = -1;
			((fcn_004b2070_group*)g_1007bc0)[j].e[i].b = 0xffff;
		}
	}
	for (i = 0; i < 128; i++) {
		if (fcn_0065f2f0(((fcn_004b2070_rec*)g_149d120)[i].name, g_6808a4, 9) == 0)
			fcn_0042d670(&((fcn_004b2070_rec*)g_149d120)[i]);
	}
}
