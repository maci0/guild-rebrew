extern float flt_0_0;

/* ADDRESS: GOLDTL 0x004356c0 */
/* ADDRESS: GOLDDE 0x0042ec80 */
char* __cdecl d3_SelectBaseMorphSlot(char* a)
{
	float best;
	char* res;
	char* e;
	int i;

	best = flt_0_0;
	res = 0;
	if (a[0x4a0] != 0) {
		e = a + 0x460;
		for (i = 3; i != 0; i--) {
			if (*(int*) (e + 0x28) != 0 && *(float*) e > best) {
				best = *(float*) e;
				res = e - 0x40;
			}
			e -= 0x7c;
		}
	}
	return res;
}
