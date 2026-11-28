extern char gm_CityStatsBuffer[];
extern char g_99f5e4[];
extern char g_99f5e8[];
extern char g_99f5ec[];
extern char g_99f604[];
extern char g_99ec14[];
extern char gm_LastCityPopTime[];
extern char gm_CityPopulation[];
extern char gm_TargetCityPopulation[];
extern char gm_DisasterState[];
extern char g_99f6a0[];
unsigned int __cdecl vfs_fwrite(void* buf, int size, int count, char* stream);

#include "Develop/client_types.h"

extern GRAPH_SAMPLE g_99ec20[16];
extern CRIME_GRID_CELL gm_CrimeGrid[9][8];

/* ADDRESS: GOLDTL 0x005208e0 */
/* ADDRESS: GOLDDE 0x00509bb0 */
int __cdecl ls_SaveCityStatsAndCrimeGrid(char* fp)
{
	int i;
	int r;

	if (vfs_fwrite((void*) &gm_CityStatsBuffer, 4, 1, fp) <= 0) {
		return 0;
	}
	if (vfs_fwrite((void*) &g_99f5e4, 4, 1, fp) <= 0) {
		return 0;
	}
	if (vfs_fwrite((void*) &g_99f5e8, 4, 1, fp) <= 0) {
		return 0;
	}
	if (vfs_fwrite((void*) &g_99f5ec, 4, 1, fp) <= 0) {
		return 0;
	}
	if (vfs_fwrite((void*) ((int) &g_99f5ec + 0x4), 4, 1, fp) <= 0) {
		return 0;
	}
	if (vfs_fwrite((void*) ((int) &g_99f5ec + 0x8), 4, 1, fp) <= 0) {
		return 0;
	}
	if (vfs_fwrite((void*) ((int) &g_99f5ec + 0xc), 4, 1, fp) <= 0) {
		return 0;
	}
	if (vfs_fwrite((void*) ((int) &g_99f5ec + 0x10), 4, 1, fp) <= 0) {
		return 0;
	}
	if (vfs_fwrite((void*) ((int) &g_99f5ec + 0x14), 4, 1, fp) <= 0) {
		return 0;
	}
	if (vfs_fwrite((void*) &g_99f604, 4, 1, fp) <= 0) {
		return 0;
	}
	if (vfs_fwrite((void*) &g_99ec14, 4, 1, fp) <= 0) {
		return 0;
	}
	if (vfs_fwrite((void*) &gm_LastCityPopTime, 4, 1, fp) <= 0) {
		return 0;
	}
	if (vfs_fwrite((void*) ((int) &gm_LastCityPopTime + 0x4), 2, 1, fp) <= 0) {
		return 0;
	}
	if (vfs_fwrite((void*) ((int) &gm_LastCityPopTime + 0x6), 4, 1, fp) <= 0) {
		return 0;
	}
	if (vfs_fwrite((void*) ((int) &gm_LastCityPopTime + 0xa), 4, 1, fp) <= 0) {
		return 0;
	}
	if (vfs_fwrite((void*) &gm_CityPopulation, 4, 1, fp) <= 0) {
		return 0;
	}
	if (vfs_fwrite((void*) &gm_TargetCityPopulation, 4, 1, fp) <= 0) {
		return 0;
	}
	if (vfs_fwrite((void*) &gm_DisasterState, 4, 1, fp) <= 0) {
		return 0;
	}
	if (vfs_fwrite((void*) ((int) &gm_DisasterState + 0x4), 4, 1, fp) <= 0) {
		return 0;
	}
	if (vfs_fwrite((void*) ((int) &gm_DisasterState + 0x8), 4, 1, fp) <= 0) {
		return 0;
	}
	if (vfs_fwrite((void*) ((int) &gm_DisasterState + 0xc), 4, 1, fp) <= 0) {
		return 0;
	}
	if (vfs_fwrite((void*) ((int) &gm_DisasterState + 0x10), 4, 1, fp) <= 0) {
		return 0;
	}
	if (vfs_fwrite((void*) ((int) &gm_DisasterState + 0x14), 4, 1, fp) <= 0) {
		return 0;
	}
	if (vfs_fwrite((void*) ((int) &gm_DisasterState + 0x18), 4, 1, fp) <= 0) {
		return 0;
	}
	if (vfs_fwrite((void*) ((int) &gm_DisasterState + 0x1c), 4, 1, fp) <= 0) {
		return 0;
	}
	if (vfs_fwrite((void*) ((int) &gm_DisasterState + 0x20), 4, 1, fp) <= 0) {
		return 0;
	}
	for (i = 0; i < 16; i++) {
		if (vfs_fwrite(&g_99ec20[i].a, 4, 1, fp) <= 0) {
			return 0;
		}
		if (vfs_fwrite(&g_99ec20[i].b, 4, 1, fp) <= 0) {
			return 0;
		}
		if (vfs_fwrite(&g_99ec20[i].c, 4, 1, fp) <= 0) {
			return 0;
		}
		if (vfs_fwrite(&g_99ec20[i].d, 4, 1, fp) <= 0) {
			return 0;
		}
		if (vfs_fwrite(&g_99ec20[i].e, 4, 1, fp) <= 0) {
			return 0;
		}
	}
	if (vfs_fwrite((void*) &g_99f6a0, 0x44, 1, fp) <= 0) {
		return 0;
	}
	if (vfs_fwrite((void*) ((int) &g_99f6a0 + 0x44), 0x44, 1, fp) <= 0) {
		return 0;
	}
	if (vfs_fwrite((void*) ((int) &g_99f6a0 + 0x88), 0x44, 1, fp) <= 0) {
		return 0;
	}
	if (vfs_fwrite((void*) ((int) &g_99f6a0 + 0xcc), 0x44, 1, fp) <= 0) {
		return 0;
	}
	if (vfs_fwrite((void*) ((int) &g_99f6a0 + 0x110), 0x44, 1, fp) <= 0) {
		return 0;
	}
	for (r = 0; r < 8; r++) {
		for (i = 0; i < 8; i++) {
			if (vfs_fwrite(&gm_CrimeGrid[r][i].demand, 2, 1, fp) <= 0) {
				return 0;
			}
			if (vfs_fwrite(&gm_CrimeGrid[r][i].supply, 2, 1, fp) <= 0) {
				return 0;
			}
			if (vfs_fwrite(&gm_CrimeGrid[r][i].pad4[0], 1, 1, fp) <= 0) {
				return 0;
			}
			if (vfs_fwrite(&gm_CrimeGrid[r][i].pad4[4], 4, 1, fp) <= 0) {
				return 0;
			}
		}
	}
	return 1;
}
