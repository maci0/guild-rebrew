extern char* evt_CurrentScript;

#include "Develop/Units/m_alloc/m_alloc_checks.h"
void __cdecl evt_LogScriptError(char*, int, const char*);


/* SetEmitterVelocity: sets a particle emitter's velocity in hundredths. */
/* ADDRESS: GOLDTL 0x00410230 */
/* ADDRESS: GOLDDE 0x0040f030 */
int __cdecl SetEmitterVelocity(char** obj, int* x, int* y, int* z)
{
	char* o;
	float vx;
	float vy;
	float vz;

	o = *obj;
	if (!m_is_tracked(o)) {
		evt_LogScriptError(evt_CurrentScript, *(int*) (evt_CurrentScript + 0x118), "SetEmitterVelocity: invalid handle...");
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
