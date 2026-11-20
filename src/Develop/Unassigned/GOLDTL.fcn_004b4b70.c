


typedef struct {
	int a;
	int n;
	float f;
} stat12;
// SIZE 0xc

extern float g_6628a0;

void __cdecl gm_SummarizeEntityOwnership(int, int, stat12*);

int __cdecl fcn_004b4b70(int ownerRef)
{
	stat12 s;

	gm_SummarizeEntityOwnership(ownerRef, 0x15, &s);
	if (s.n < 3 || s.f < g_6628a0)
		return 0;
	gm_SummarizeEntityOwnership(ownerRef, 0x14, &s);
	if (s.n < 3 || s.f < g_6628a0)
		return 0;
	gm_SummarizeEntityOwnership(ownerRef, 0x12, &s);
	if (s.n < 3 || s.f < g_6628a0)
		return 0;
	return 1;
}
