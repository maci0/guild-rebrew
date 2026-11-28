#include <string.h>

typedef struct
{
	int i[0x3cc / 4];
} fcn_0046f390_Win;
// SIZE 0x3cc

#include "Develop/client_types.h"
extern Win_1015f40 d2_Windows[0x60];
extern int g_77259c;

void __cdecl d2_DestroyElement(int id);
void __cdecl m_FreeTracked(int p);
void __cdecl d2_ReleaseSurface(int surf);
void __cdecl d3_SafeReleaseSceneResource(int tex);
void __cdecl d2_SubRefcount(int id);

/* ADDRESS: GOLDTL 0x0046f390 */
int __cdecl d2_DestroyWindow(int win)
{
	fcn_0046f390_Win* w;

	if (win > 0x60) {
		return 0;
	}
	w = &((fcn_0046f390_Win*)d2_Windows)[win];
	if (w->i[0x290 / 4] == 0) {
		return 0;
	}
	while (w->i[0x2c / 4] != 0) {
		d2_DestroyElement(*(int*) w->i[0x28 / 4]);
	}
	if (w->i[0x28 / 4] != 0) {
		m_FreeTracked(w->i[0x28 / 4]);
		w->i[0x28 / 4] = 0;
	}
	if (w->i[0x30 / 4] != 0) {
		d2_ReleaseSurface(w->i[0x30 / 4]);
	}
	if (w->i[0x34 / 4] != 0) {
		d2_ReleaseSurface(w->i[0x34 / 4]);
	}
	if (w->i[0x38 / 4] != 0) {
		d2_ReleaseSurface(w->i[0x38 / 4]);
	}
	if (w->i[0x3a0 / 4] != 0) {
		d3_SafeReleaseSceneResource(w->i[0x3a0 / 4]);
	}
	if (w->i[0x398 / 4] != -1) {
		d2_SubRefcount(w->i[0x398 / 4]);
	}
	if (w->i[0x3c / 4] != 0) {
		m_FreeTracked(w->i[0x3c / 4]);
		w->i[0x3c / 4] = 0;
	}
	memset(w, 0, sizeof(fcn_0046f390_Win));
	w->i[0] = win;
	w->i[0x3c0 / 4] = -1;
	g_77259c--;
	return 1;
}
