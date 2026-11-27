


typedef struct {
	int a;
	int n;
	float f;
} stat12;
// SIZE 0xc

extern float g_6628a0;

void __cdecl gm_SummarizeEntityOwnership(int, int, stat12*);

int __cdecl gm_HasThreeEntityHoldings(int ownerRef)
{
	stat12 stats;

	gm_SummarizeEntityOwnership(ownerRef, 0x15, &stats);
	if (stats.n < 3 || stats.f < g_6628a0)
		return 0;
	gm_SummarizeEntityOwnership(ownerRef, 0x14, &stats);
	if (stats.n < 3 || stats.f < g_6628a0)
		return 0;
	gm_SummarizeEntityOwnership(ownerRef, 0x12, &stats);
	if (stats.n < 3 || stats.f < g_6628a0)
		return 0;
	return 1;
}
