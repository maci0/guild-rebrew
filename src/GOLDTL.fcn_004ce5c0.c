


unsigned short* __cdecl fcn_00502cd0(int, int, int);
unsigned short* __cdecl gm_NextEntityQueryMatch(void);
int __cdecl fcn_004ce590(int);

int __cdecl fcn_004ce5c0(char* a1)
{
	unsigned short* p;
	int r;

	for (p = fcn_00502cd0(*(int*) (a1 + 0x178), 1, 5); p != 0; p = gm_NextEntityQueryMatch()) {
		r = fcn_004ce590(*p);
		if (r != 0) {
			return r;
		}
	}
	return fcn_004ce590(0);
}
