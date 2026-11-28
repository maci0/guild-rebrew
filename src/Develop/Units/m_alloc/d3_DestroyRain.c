

void __cdecl m_FreeTracked(void*);

/* ADDRESS: GOLDDE 0x004138e0 */
void __cdecl d3_DestroyRain(char* rain)
{
	if (rain == 0) {
		return;
	}
	if (*(int*) (rain + 0x10) != 0) {
		m_FreeTracked((void*) *(int*) (rain + 0x10));
		*(int*) (rain + 0x10) = 0;
	}
	m_FreeTracked(rain);
}
