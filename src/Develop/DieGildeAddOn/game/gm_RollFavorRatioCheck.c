

float __cdecl gm_CalcEntityFavor(unsigned int a0, unsigned int a1, unsigned int a2);
double __cdecl gm_RandomFloat01(void);

/* ADDRESS: GOLDTL 0x0050e720 */
/* ADDRESS: GOLDDE 0x004f9460 */
int __cdecl gm_RollFavorRatioCheck(int entity1, int entity2, int numerator, int denominator)
{
	double scaledFavor;

	scaledFavor = gm_CalcEntityFavor(entity1, entity2, 1) * 0.01f;
	return scaledFavor * numerator / denominator > gm_RandomFloat01() + 0.15;
}
