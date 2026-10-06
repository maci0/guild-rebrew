// FUNCTION: GOLD 0x004ef440
// FUNCTION: GOLDTL 0x4f13a0

int __cdecl cm_GetBuildingStatCount(char*);

int __cdecl fcn_004f13a0(char* a1)
{
	int n;
	int c;
	char* p;

	n = cm_GetBuildingStatCount(a1);
	c = 0;
	if (n == 0) {
		return 0;
	}
	if (n > 0) {
		p = *(char**) (*(char**) (a1 + 0x65) + 0x20);
		do {
			if (*(int*) p != -1) {
				c++;
			}
			p += 0x44;
		} while (--n != 0);
	}
	return c;
}
