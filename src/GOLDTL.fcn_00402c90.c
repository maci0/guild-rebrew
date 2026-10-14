extern void* g_14d0020[];
/* ADDRESS: GOLDTL 0x006b8010 */
extern int g_6b8010;
/* ADDRESS: GOLDTL 0x00402c90 */

int __cdecl fcn_00402c90(int a1, int a2)
{
	int count;
	void** p;
	void* e;

	count = 0;
	p = g_14d0020;
	do {
		e = *p;
		if (e != 0 && *(int*) ((char*) e + 0x124) != 0) {
			if (a1 == -1 || a1 == g_6b8010) {
				if (a2 != 0 ||
				    *(int*) (*(int*) ((char*) e + 0x34) + 0x218) != 1 ||
				    *(int*) ((char*) e + 0x128) != 0) {
					count++;
				}
			}
		}
		p++;
	} while ((int) p < 0x14d0c20);
	return count;
}
