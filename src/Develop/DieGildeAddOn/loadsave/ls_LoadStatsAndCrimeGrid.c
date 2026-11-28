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
#include "Develop/DieGildeAddOn/loadsave/loadsave.h"
#include "Develop/client_types.h"

extern GRAPH_SAMPLE g_99ec20[16];
extern CRIME_GRID_CELL gm_CrimeGrid[9][8];

/* ADDRESS: GOLDTL 0x005246e0 */
/* ADDRESS: GOLDDE 0x0050d9b0 */
unsigned int __cdecl ls_LoadStatsAndCrimeGrid(unsigned int stream)
{
	int i;
	int j;
	int value;

	value = 0;
	if (!ls_ReadVfsDataChecked((void*) &gm_CityStatsBuffer, 4, 1, (void*) stream))
		return 0;
	if (!ls_ReadVfsDataChecked((void*) &g_99f5e4, 4, 1, (void*) stream))
		return 0;
	if (!ls_ReadVfsDataChecked((void*) &g_99f5e8, 4, 1, (void*) stream))
		return 0;
	if (!ls_ReadVfsDataChecked((void*) &g_99f5ec, 4, 1, (void*) stream))
		return 0;
	if (!ls_ReadVfsDataChecked((void*) ((int) &g_99f5ec + 0x4), 4, 1, (void*) stream))
		return 0;
	if (!ls_ReadVfsDataChecked((void*) ((int) &g_99f5ec + 0x8), 4, 1, (void*) stream))
		return 0;
	if (!ls_ReadVfsDataChecked((void*) ((int) &g_99f5ec + 0xc), 4, 1, (void*) stream))
		return 0;
	if (!ls_ReadVfsDataChecked((void*) ((int) &g_99f5ec + 0x10), 4, 1, (void*) stream))
		return 0;
	if (!ls_ReadVfsDataChecked((void*) ((int) &g_99f5ec + 0x14), 4, 1, (void*) stream))
		return 0;
	if (!ls_ReadVfsDataChecked((void*) &g_99f604, 4, 1, (void*) stream))
		return 0;
	if (!ls_ReadVfsDataChecked((void*) &g_99ec14, 4, 1, (void*) stream))
		return 0;
	if (!ls_ReadVfsDataChecked((void*) &gm_LastCityPopTime, 4, 1, (void*) stream))
		return 0;
	if (!ls_ReadVfsDataChecked((void*) ((int) &gm_LastCityPopTime + 0x4), 2, 1, (void*) stream))
		return 0;
	if (!ls_ReadVfsDataChecked((void*) ((int) &gm_LastCityPopTime + 0x6), 4, 1, (void*) stream))
		return 0;
	if (!ls_ReadVfsDataChecked((void*) ((int) &gm_LastCityPopTime + 0xa), 4, 1, (void*) stream))
		return 0;
	if (!ls_ReadVfsDataChecked((void*) &gm_CityPopulation, 4, 1, (void*) stream))
		return 0;
	if (!ls_ReadVfsDataChecked((void*) &gm_TargetCityPopulation, 4, 1, (void*) stream))
		return 0;
	if (!ls_ReadVfsDataChecked((void*) &gm_DisasterState, 4, 1, (void*) stream))
		return 0;
	if (!ls_ReadVfsDataChecked((void*) ((int) &gm_DisasterState + 0x4), 4, 1, (void*) stream))
		return 0;
	if (!ls_ReadVfsDataChecked((void*) ((int) &gm_DisasterState + 0x8), 4, 1, (void*) stream))
		return 0;
	if (!ls_ReadVfsDataChecked((void*) ((int) &gm_DisasterState + 0xc), 4, 1, (void*) stream))
		return 0;
	if (!ls_ReadVfsDataChecked((void*) ((int) &gm_DisasterState + 0x10), 4, 1, (void*) stream))
		return 0;
	if (!ls_ReadVfsDataChecked((void*) ((int) &gm_DisasterState + 0x14), 4, 1, (void*) stream))
		return 0;
	if (!ls_ReadVfsDataChecked((void*) ((int) &gm_DisasterState + 0x18), 4, 1, (void*) stream))
		return 0;
	if (!ls_ReadVfsDataChecked((void*) ((int) &gm_DisasterState + 0x1c), 4, 1, (void*) stream))
		return 0;
	if (!ls_ReadVfsDataChecked((void*) ((int) &gm_DisasterState + 0x20), 4, 1, (void*) stream))
		return 0;
	for (i = 0; i < 16; i++) {
		if (!ls_ReadVfsDataChecked(&g_99ec20[i].a, 4, 1, (void*) stream))
			return 0;
		if (!ls_ReadVfsDataChecked(&g_99ec20[i].b, 4, 1, (void*) stream))
			return 0;
		if (!ls_ReadVfsDataChecked(&g_99ec20[i].c, 4, 1, (void*) stream))
			return 0;
		if (!ls_ReadVfsDataChecked(&g_99ec20[i].d, 4, 1, (void*) stream))
			return 0;
		if (!ls_ReadVfsDataChecked(&g_99ec20[i].e, 4, 1, (void*) stream))
			return 0;
	}
	if (!ls_ReadVfsDataChecked((void*) &g_99f6a0, 0x44, 1, (void*) stream))
		return 0;
	if (!ls_ReadVfsDataChecked((void*) ((int) &g_99f6a0 + 0x44), 0x44, 1, (void*) stream))
		return 0;
	if (!ls_ReadVfsDataChecked((void*) ((int) &g_99f6a0 + 0x88), 0x44, 1, (void*) stream))
		return 0;
	if (!ls_ReadVfsDataChecked((void*) ((int) &g_99f6a0 + 0xcc), 0x44, 1, (void*) stream))
		return 0;
	if (!ls_ReadVfsDataChecked((void*) ((int) &g_99f6a0 + 0x110), 0x44, 1, (void*) stream))
		return 0;
	for (i = 0; i < 8; i++) {
		for (j = 0; j < 8; j++) {
			if (!ls_ReadVfsDataChecked(&gm_CrimeGrid[i][j].demand, 2, 1, (void*) stream))
				return 0;
			if (!ls_ReadVfsDataChecked(&gm_CrimeGrid[i][j].supply, 2, 1, (void*) stream))
				return 0;
			if (!ls_ReadVfsDataChecked(&gm_CrimeGrid[i][j].pad4[0], 1, 1, (void*) stream))
				return 0;
			if (!ls_ReadVfsDataChecked(&gm_CrimeGrid[i][j].pad4[4], 4, 1, (void*) stream))
				return 0;
		}
	}
	return 1;
}
