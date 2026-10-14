/* ADDRESS: GOLDTL 0x0077dda0 */
extern char g_77dda0[];
/* ADDRESS: GOLD 0x006f9f60 */
extern char g_77dda0[];



typedef struct {
	int f0;
	float f4;
	int f8;
	int fc;
} fcn_00589390_sub;
// SIZE 0x10

typedef struct {
	int head0;
	int head4;
	fcn_00589390_sub s[3];
} fcn_00589390_rec;
// SIZE 0x38

void __cdecl fcn_00589390(void)
{
	fcn_00589390_rec* base;
	int i;
	int j;

	base = (fcn_00589390_rec*) g_77dda0;
	for (i = 0; i < 3; i++) {
		base[i].head0 = -1;
		for (j = 0; j < 3; j++) {
			base[i].s[j].f0 = -1;
			base[i].s[j].f4 = 100000.0f;
			base[i].s[j].f8 = 0;
			base[i].s[j].fc = 0;
		}
	}
}
