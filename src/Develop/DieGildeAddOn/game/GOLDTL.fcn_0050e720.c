

float __cdecl gm_CalcEntityFavor(unsigned int a0, unsigned int a1, unsigned int a2);
double __cdecl gm_RandomFloat01(void);

/* ADDRESS: GOLDTL 0x0050e720 */
int __cdecl fcn_0050e720(int a1, int a2, int numerator, int denominator)
{
	double d;

	d = gm_CalcEntityFavor(a1, a2, 1) * 0.01f;
	return d * numerator / denominator > gm_RandomFloat01() + 0.15;
}
