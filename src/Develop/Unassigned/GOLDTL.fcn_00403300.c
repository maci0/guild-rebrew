extern void* g_14d0020[];

/* ADDRESS: GOLDTL 0x00403300 */
void* __cdecl fcn_00403300(int key)
{
	int i;
	void* p;

	for (i = 0; i < 0x300; i++) {
		p = g_14d0020[i];
		if (p != 0 && *(int*) ((char*) p + 0x34) == key) {
			return g_14d0020[i];
		}
	}
	return 0;
}
