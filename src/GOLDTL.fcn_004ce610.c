


unsigned short* __cdecl fcn_00502cd0(int, int, int);
unsigned short* __cdecl fcn_00502850(void);
char* __cdecl fcn_004ce590(int);

char* __cdecl fcn_004ce610(char* x)
{
	unsigned short* e;
	char* r;

	e = fcn_00502cd0(*(int*) (x + 0x178), 1, 5);
	while (e != 0) {
		r = fcn_004ce590(*e);
		if (r != 0) {
			if ((*(int*) (r + 0x58) == 1 || *(int*) (r + 0x58) == 2) && *(int*) ((char*) e + 0x20) <= 0)
				return fcn_004ce590(0);
			return r;
		}
		e = fcn_00502850();
	}
	return fcn_004ce590(0);
}
