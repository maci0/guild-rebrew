// FUNCTION: GOLD 0x005d0a10
// FUNCTION: GOLDTL 0x005dcf40

extern float g_66413c;
extern float g_66416c;
extern float g_662d34;
extern float g_6629d0;
extern float g_6628a0;
extern float g_665368;

float __cdecl gm_RandomFloat01(void);
void __cdecl fcn_004c6ba0(int, int, int);

int __cdecl fcn_005dcf40(unsigned char* e, int idx)
{
	int cur;
	unsigned char add;
	float t1;
	float t2;

	if (idx >= 5 || e[idx + 0x80] >= g_66413c) {
		return 0;
	}
	{
		t1 = (g_66413c - e[idx + 0x80]) * g_66416c;
		t2 = t1;
		t2 *= g_662d34;
		t2 += g_6629d0;
		add = (unsigned char) ((gm_RandomFloat01() * t2 + (g_6628a0 - t2)) * g_665368 * t1 + g_6628a0);
		cur = e[idx + 0x80];
		if (add + cur > g_66413c) {
			add = (unsigned char) (g_66413c - cur);
		}
		if (add != 0) {
			fcn_004c6ba0(*(int*) (e + 4), idx, add);
		}
	}
	return 1;
}
