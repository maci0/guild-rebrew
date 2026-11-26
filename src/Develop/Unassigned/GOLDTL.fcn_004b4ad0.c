


typedef struct {
	int a;
	int n;
	float f;
} stat12;
// SIZE 0xc

extern float g_6628a0;

void __cdecl gm_SummarizeEntityOwnership(int, int, stat12*);

int __cdecl gm_HasEntityTypes13AndOptionalOwnership(int key)
{
	stat12 s;

	gm_SummarizeEntityOwnership(key, 0x13, &s);
	if (s.f < g_6628a0)
		return 0;
	gm_SummarizeEntityOwnership(key, 4, &s);
	if (s.n > 0 && s.f < g_6628a0)
		return 0;
	gm_SummarizeEntityOwnership(key, 0x10, &s);
	if (s.n > 0 && s.f < g_6628a0)
		return 0;
	return 1;
}
