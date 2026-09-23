extern void* g_14d0020[];
// FUNCTION: GOLDTL 0x4032b0
// SIZE: 80

int __cdecl fcn_0065f220(int, int);

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
