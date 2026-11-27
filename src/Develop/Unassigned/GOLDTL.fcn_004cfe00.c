
/* ADDRESS: GOLDTL 0x004cfe00 */
void __cdecl d3_ResetActionTimers(void)
{
	int a;

	for (a = 0x9b4904; a < 0x9b4a44; a += 0x14) {
		*(int*) (a + 4) = -1;
		*(int*) a = 0;
		*(int*) (a + 8) = 0;
	}
}
