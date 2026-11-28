#include <math.h>
#include "he_tables.h"

extern Rec7dc6e0 g_7dc6e0[64];
extern float d3_TwoPi;
#include "Develop/DieGildeAddOn/game/game_data.h"

void __cdecl d3_TransformPoint(char*, float*, float*);
int __cdecl d3_GetObjectVerticalBounds(char*, float*, float*);
void __cdecl d3_SetNodePosition(char*, int*);

/* ADDRESS: GOLDTL 0x00546480 */
/* ADDRESS: GOLDDE 0x0052cb00 */
void __cdecl he_ArrangeEntityMarkers(char* entity)
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
	d3_TransformPoint(entity, (float*) (entity + 0x4c), pos);
	d3_GetObjectVerticalBounds(entity, &lo, &hi);
	pos[1] = hi;
	for (i = 0; i < count; i++) {
		slot = list[i];
		d3_GetObjectVerticalBounds((char*) slot->d, &lo, &hi);
		angle = (float) i * d3_TwoPi / (float) count;
		out[0] = (float) sin(angle) * t + pos[0];
		out[1] = (hi - lo) * 0.5 + pos[1];
		out[2] = (float) cos(angle) * t + pos[2];
		d3_SetNodePosition((char*) slot->d, (int*) out);
	}
}
