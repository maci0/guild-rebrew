


typedef struct {
	int a;
	int n;
	float f;
} stat12;
// SIZE 0xc

extern float flt_1_0;

void __cdecl gm_SummarizeEntityOwnership(int, int, stat12*);

/* ADDRESS: GOLDDE 0x004a2e60 */
int __cdecl gm_HasThreeEntityHoldings(int ownerRef)
{
	stat12 stats;

	gm_SummarizeEntityOwnership(ownerRef, 0x15, &stats);
	if (stats.n < 3 || stats.f < flt_1_0)
		return 0;
	gm_SummarizeEntityOwnership(ownerRef, 0x14, &stats);
	if (stats.n < 3 || stats.f < flt_1_0)
		return 0;
	gm_SummarizeEntityOwnership(ownerRef, 0x12, &stats);
	if (stats.n < 3 || stats.f < flt_1_0)
		return 0;
	return 1;
}
