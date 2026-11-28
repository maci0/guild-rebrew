#include "Develop/DieGildeAddOn/game/client_method_registry.h"
extern AM_METHOD am_Methods[];
extern float g_662918;
extern float g_662914;
extern const float flt_100_0;
extern float g_662c98;
int __cdecl gm_SumStraftatSeverity(int);

/* ADDRESS: GOLDTL 0x004a4680 */
/* ADDRESS: GOLDDE 0x00493080 */
int __cdecl ai_ComputeActionScore(float* o0, float* o1, int idx, char* s, int* p4)
{
	float base;
	float v9;
	float v8;
	float v10;
	float contribution;
	char* t;
	AM_METHOD* method;
	int i;
	int found;

	if (p4 == 0) {
		base = 1.0f;
	} else {
		base = (float) *(int*) ((char*) p4 + 0xc);
	}
	{
		int bonus = gm_SumStraftatSeverity(*(int*) (s + 4));
		v9 = (float) bonus + base;
		v9 = (*(float*) (s + 0x10c) - 2.0f) * v9;
	}
	*o1 = 0.0f;
	*o0 = 0.0f;
	method = &am_Methods[idx];
	if ((unsigned char) method->flags & *(unsigned char*) (s + 0x218)) {
		v10 = g_662c98;
		v8 = g_662914;
		found = 1;
	} else {
		v10 = g_662914;
		v8 = flt_100_0;
		found = 0;
	}
	t = (char*) &method->effects[0].value;
	for (i = 0; !found && i < 4; i++) {
		if (*(char*) (t - 4) == *(char*) (s + 0x130)
			&& *(float*) t > 0.0f) {
			found = 1;
		}
		t += 8;
	}
	t = (char*) &method->other_effects[0].value;
	for (i = 0; !found && i < 4; i++) {
		if (*(char*) (t - 4) == *(char*) (s + 0x130)
			&& *(float*) t > 0.0f) {
			found = 1;
		}
		t += 8;
	}
	t = (char*) method->effects;
	for (i = 4; i != 0; i--) {
		if (*(float*) (t + 4) > 0.0f) {
			if (*(unsigned char*) t == *(unsigned char*) (s + 0x130)) {
				contribution = (*(float*) (s + (*(unsigned char*) t + 0xc) * 0xc)
					* *(float*) (t + 4)) / (v10 + v9);
			} else {
				contribution = (*(float*) (s + (*(unsigned char*) t + 0xc) * 0xc)
					* *(float*) (t + 4)) / (v8 + v9);
			}
		} else {
			contribution = *(float*) (t + 4);
			if (*(unsigned char*) t == *(unsigned char*) (s + 0x130)) {
				contribution = contribution / v10;
			} else {
				contribution = contribution / v8;
			}
			contribution = contribution * *(float*) (s + (*(unsigned char*) t + 0xc) * 0xc);
		}
		*o0 += contribution;
		if (*(float*) (t + 0x44) > 0.0f) {
			if (*(unsigned char*) (t + 0x40) == *(unsigned char*) (s + 0x130)) {
				contribution = (*(float*) (s + (*(unsigned char*) (t + 0x40) + 0xc) * 0xc)
					* *(float*) (t + 0x44)) / (v10 + v9);
			} else {
				contribution = (*(float*) (s + (*(unsigned char*) (t + 0x40) + 0xc) * 0xc)
					* *(float*) (t + 0x44)) / (v8 + v9);
			}
		} else {
			contribution = *(float*) (t + 0x44);
			if (*(unsigned char*) (t + 0x40) == *(unsigned char*) (s + 0x130)) {
				contribution = contribution / v10;
			} else {
				contribution = contribution / v8;
			}
			contribution = contribution * *(float*) (s + (*(unsigned char*) (t + 0x40) + 0xc) * 0xc);
		}
		*o1 += contribution;
		t += 8;
	}
	return found;
}
