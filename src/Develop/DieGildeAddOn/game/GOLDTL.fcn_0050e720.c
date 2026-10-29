extern float g_662910;

double __cdecl fcn_0050f980(int, int, int);
double __cdecl gm_RandomFloat01(void);

/* ADDRESS: GOLDTL 0x0050e720 */
int __cdecl fcn_0050e720(int a1, int a2, int a3, int a4)
{
	double d;

	d = fcn_0050f980(a1, a2, 1) * g_662910;
	return d * a3 / a4 > gm_RandomFloat01() + 0.15;
}
