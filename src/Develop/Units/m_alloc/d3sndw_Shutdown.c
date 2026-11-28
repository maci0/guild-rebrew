#include "Develop/Units/m_alloc/m_alloc.h"

extern float* d3snd_ProbeSinTable;
extern char* d3sndw_SlotWaterIds;
extern char* d3sndw_SlotStates;

/* ADDRESS: GOLDTL 0x004195f0 */
/* ADDRESS: GOLDDE 0x00417330 */
void __cdecl d3sndw_Shutdown(void)
{
	if (d3snd_ProbeSinTable != 0) {
		m_FreeTracked(d3snd_ProbeSinTable);
		d3snd_ProbeSinTable = 0;
		m_FreeTracked(d3sndw_SlotWaterIds);
		d3sndw_SlotWaterIds = 0;
		m_FreeTracked(d3sndw_SlotStates);
		d3sndw_SlotStates = 0;
		d3sndw_SlotWaterIds = 0;
		d3snd_ProbeSinTable = 0;
	}
}
