extern volatile int gm_GameTicks;

void* __cdecl m_alloc(int size, char* tag);
void __cdecl d3_CreateSkyDomeBuffers(char* p);
void __cdecl d3_ResetSkyDomeNormals(char* p, int a);

/* ADDRESS: GOLDTL 0x00459ae0 */
/* ADDRESS: GOLDDE 0x0044f2a0 */
char* __cdecl d3_CreateSky(int a, int b, int c)
{
	char* p;

	p = (char*) m_alloc(0x390, "d3_sky:Create");
	if (p != 0) {
		*(int*) (p + 8) = -1;
		*(int*) (p + 0x24) = 0;
		*(int*) (p + 0x18) = a;
		*(int*) (p + 0x28) = gm_GameTicks;
		*(int*) (p + 0x2c) = 0;
		*(int*) (p + 0x1c) = b;
		*(int*) (p + 0x20) = c;
		d3_CreateSkyDomeBuffers(p);
		d3_ResetSkyDomeNormals(p, 1);
	}
	return p;
}
