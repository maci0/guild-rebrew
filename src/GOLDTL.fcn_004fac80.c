/* ADDRESS: GOLDTL 0x00696178 */
extern char g_696178[];
/* ADDRESS: GOLD 0x00617448 */
extern char g_696178[];



// SIZE 0x8
typedef struct {
	int a;
	int b;
} fcn_004fac80_E;

int __cdecl fcn_004fac80(int a1, int* out)
{
	fcn_004fac80_E* t;

	if (a1 >= 0x58) {
		return 0;
	}
	t = (fcn_004fac80_E*) g_696178;
	out[0] = t[a1].a;
	out[1] = t[a1].b;
	return 1;
}
