


extern float g_66413c;
extern float g_66416c;
extern float g_662d34;
extern float g_6629d0;
extern float g_6628a0;
extern float g_665368;

float __cdecl gm_RandomFloat01(void);
void __cdecl cm_RequestModifyEntityLevel(int, int, int);

int __cdecl gm_IncreaseEntitySkill(unsigned char* e, int idx)
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
		t2 *= 0.6f;
		t2 += g_6629d0;
		add = (unsigned char) ((gm_RandomFloat01() * t2 + (1.0f - t2)) * g_665368 * t1 + 1.0f);
		cur = e[idx + 0x80];
		if (add + cur > g_66413c) {
			add = (unsigned char) (g_66413c - cur);
		}
		if (add != 0) {
			cm_RequestModifyEntityLevel(*(int*) (e + 4), idx, add);
		}
	}
	return 1;
}
