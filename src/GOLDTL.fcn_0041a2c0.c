// FUNCTION: GOLDTL 0x0041a2c0
// SIZE: 184

// SIZE 0x508
typedef struct {
	char pad[0x504];
	void* data;
} E41a2c0;

extern E41a2c0* g_6b5dd0;
extern int g_6b5de8;
void __cdecl fcn_0041ddd0(void* p);
void* __cdecl fcn_0064d740(void* dst, const void* src, unsigned int n);

void __cdecl fcn_0041a2c0(int idx)
{
	fcn_0041ddd0(g_6b5dd0[idx].data);
	g_6b5dd0[idx].data = 0;
	if (--g_6b5de8 != 0) {
		fcn_0041ddd0(g_6b5dd0[idx].data);
		g_6b5dd0[idx].data = 0;
		fcn_0064d740(&g_6b5dd0[idx], &g_6b5dd0[idx + 1], g_6b5de8 * sizeof(E41a2c0) - idx * sizeof(E41a2c0));
		return;
	}
	fcn_0041ddd0(g_6b5dd0);
	g_6b5dd0 = 0;
}
