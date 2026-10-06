// FUNCTION: GOLD 0x4f9ce0
// FUNCTION: GOLDTL 0x4fc340

extern float g_6628bc;
extern const double g_6640f8;
extern double g_662ad8;

void __cdecl fcn_004f4830(int, int*);

double __cdecl fcn_004fc340(void)
{
	int a[9];
	int b[9];

	fcn_004f4830(0, a);
	fcn_004f4830(1, b);
	return (4 - a[6]) * g_6628bc * g_6640f8 + (1 - b[6]) * g_662ad8;
}
