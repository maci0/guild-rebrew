


// SIZE 0x188
#include "Develop/client_types.h"
typedef Tabs_7e43a8 Tabs;

extern int g_7e4530;
extern Tabs_7e43a8 gm_HourlyWeatherSlots;

unsigned int __cdecl vfs_fwrite(void* p, int size, int n, int f);
int __cdecl ls_SaveWeatherState(int f);
int __cdecl ls_SaveRenderSlots(int f);

/* ADDRESS: GOLDDE 0x0050ab10 */
int __cdecl ls_SaveWeatherAndSlots(int stream)
{
	int i;

	if (vfs_fwrite(&g_7e4530, 4, 1, stream) <= 0) {
		return 0;
	}
	for (i = 0; i < 24; i++) {
		if (vfs_fwrite(&gm_HourlyWeatherSlots.a[i], 4, 1, stream) <= 0) {
			return 0;
		}
		if (vfs_fwrite(&gm_HourlyWeatherSlots.b[i], 4, 1, stream) <= 0) {
			return 0;
		}
		if (vfs_fwrite(&gm_HourlyWeatherSlots.c[i], 4, 1, stream) <= 0) {
			return 0;
		}
		if (vfs_fwrite(&gm_HourlyWeatherSlots.d[i], 4, 1, stream) <= 0) {
			return 0;
		}
	}
	if (ls_SaveWeatherState(stream) == 0) {
		return 0;
	}
	if (ls_SaveRenderSlots(stream) == 0) {
		return 0;
	}
	return 1;
}
