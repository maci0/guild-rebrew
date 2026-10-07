// FUNCTION: GOLD 0x0040e670
// FUNCTION: GOLDTL 0x0040f580

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

void __cdecl fcn_004463f0(int a, int b, float v);

int __cdecl fcn_0040f580(int* a, int* b, int* pct)
{
	fcn_004463f0(*a, *b, MAX(MIN(*pct * 0.01f, 1.0f), 0.0f));
	return 1;
}
