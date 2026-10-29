#include <math.h>
#include "he_tables.h"

extern Rec7dc6e0 g_7dc6e0[64];
extern float g_6628c8;
extern double g_662908;

void __cdecl fcn_00455350(char*, float*, float*);
int __cdecl fcn_004133e0(char*, float*, float*);
void __cdecl fcn_00438b40(char*, int*);

/* ADDRESS: GOLDTL 0x00546480 */
void __cdecl fcn_00546480(char* entity)
{
	Rec7dc6e0* list[32];
	Rec7dc6e0* slot;
	float angle;
	float pos[4];
	float lo;
	float hi;
	float t;
	float out[4];
	int count;
	int i;

	count = 0;
	for (slot = g_7dc6e0; (int) slot < (int) &g_7dc6e0[64]; slot++) {
		if (count >= 32) {
			break;
		}
		if ((char*) slot->c == entity) {
			list[count] = slot;
			count++;
		}
	}
	t = 0.0f;
	if (count != 1) {
		t = 100.0f;
	}
	fcn_00455350(entity, (float*) (entity + 0x4c), pos);
	fcn_004133e0(entity, &lo, &hi);
	pos[1] = hi;
	for (i = 0; i < count; i++) {
		slot = list[i];
		fcn_004133e0((char*) slot->d, &lo, &hi);
		angle = (float) i * g_6628c8 / (float) count;
		out[0] = (float) sin(angle) * t + pos[0];
		out[1] = (hi - lo) * g_662908 + pos[1];
		out[2] = (float) cos(angle) * t + pos[2];
		fcn_00438b40((char*) slot->d, (int*) out);
	}
}
