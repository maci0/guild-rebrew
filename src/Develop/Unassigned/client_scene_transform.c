extern void* g_14d0020[];

int __cdecl fcn_0065f220(int, int);

/* ADDRESS: GOLD 0x00402a70 */
/* ADDRESS: GOLDTL 0x004032b0 */
void* __cdecl fcn_004032b0(int a1)
{
	int i;
	void* e;

	i = 0;
	do {
		e = g_14d0020[i];
		if (e != 0) {
			if (fcn_0065f220(*(int*) ((char*) e + 0x34), a1) == 0) {
				break;
			}
		}
		i++;
	} while (i < 0x300);
	if (i < 0x300) {
		return g_14d0020[i];
	}
	return 0;
}

/* ADDRESS: GOLDTL 0x00403300 */
/* ADDRESS: GOLD 0x00402ac0 */
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
