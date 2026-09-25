// FUNCTION: GOLD 0x004cdac0
// SIZE: 87
// FUNCTION: GOLDTL 0x4ce680
// SIZE: 87

unsigned short* __cdecl fcn_00502cd0(int, int, int);
unsigned short* __cdecl gm_NextEntityQueryMatch(void);
char* __cdecl fcn_004ce590(int);

unsigned short* __cdecl fcn_004ce680(char* a1)
{
	unsigned short* p;
	char* r;

	for (p = fcn_00502cd0(*(int*) (a1 + 0x178), 1, 5); p != 0; p = gm_NextEntityQueryMatch()) {
		r = fcn_004ce590(*p);
		if (r != 0) {
			if ((*(int*) (r + 0x58) == 1 || *(int*) (r + 0x58) == 2) && *(int*) ((char*) p + 0x20) <= 0) {
				return 0;
			}
			return p;
		}
	}
	return 0;
}
