


typedef struct {
	int a;
	int n;
	float f;
} stat12;
// SIZE 0xc

extern float flt_1_0;

void __cdecl gm_SummarizeEntityOwnership(int, int, stat12*);

/* ADDRESS: GOLDDE 0x004a2dc0 */
int __cdecl gm_HasEntityTypes13AndOptionalOwnership(int key)
{
	stat12 s;

	gm_SummarizeEntityOwnership(key, 0x13, &s);
	if (s.f < flt_1_0)
		return 0;
	gm_SummarizeEntityOwnership(key, 4, &s);
	if (s.n > 0 && s.f < flt_1_0)
		return 0;
	gm_SummarizeEntityOwnership(key, 0x10, &s);
	if (s.n > 0 && s.f < flt_1_0)
		return 0;
	return 1;
}
