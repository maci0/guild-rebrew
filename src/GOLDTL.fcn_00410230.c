extern char* g_6b7e98;

#include "Develop/Units/m_alloc/m_alloc_checks.h"
void __cdecl fcn_00425bf0(char*, int, const char*);

/* ADDRESS: GOLDTL 0x00410230 */

/* SetEmitterVelocity: sets a particle emitter's velocity in hundredths. */
int __cdecl fcn_00410230(char** obj, int* x, int* y, int* z)
{
	char* o;
	float vx;
	float vy;
	float vz;

	o = *obj;
	if (!m_is_tracked(o)) {
		fcn_00425bf0(g_6b7e98, *(int*) (g_6b7e98 + 0x118), "SetEmitterVelocity: invalid handle...");
		return 0;
	}
	vy = *y * 0.01f;
	vz = *z * 0.01f;
	vx = *x * 0.01f;
	*(float*) (o + 0x80) = vx;
	*(float*) (o + 0x84) = vy;
	*(float*) (o + 0x88) = vz;
	return 0;
}
