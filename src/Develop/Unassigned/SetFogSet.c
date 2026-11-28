


#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

void __cdecl d3_InterpolateSceneFog(int a, int b, float v);

/* ADDRESS: GOLDDE 0x0040e380 */
int __cdecl SetFogSet(int* a, int* b, int* pct)
{
	d3_InterpolateSceneFog(*a, *b, MAX(MIN(*pct * 0.01f, 1.0f), 0.0f));
	return 1;
}
