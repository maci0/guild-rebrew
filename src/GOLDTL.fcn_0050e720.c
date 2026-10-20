extern float g_662910;

float __cdecl fcn_0050f980(int, int, int);
double __cdecl gm_RandomFloat01(void);

/* ADDRESS: GOLDTL 0x0050e720 */
int __cdecl fcn_0050e720(int a1, int a2, int a3, int a4)
{
	double d;
	double q;
	double da;

	da = (double) a3;
	q = fcn_0050f980(a1, a2, 1) * g_662910;
	d = q * da / a4;
	return gm_RandomFloat01() + 0.15 < d;
}
