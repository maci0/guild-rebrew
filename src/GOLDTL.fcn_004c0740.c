char* __cdecl fcn_00502cd0(int, int, int, int, int);
char* __cdecl gm_NextEntityQueryMatch(void);
int __cdecl fcn_004be340(char*);
unsigned int __cdecl fcn_00430910(void*, int, int, void*);

/* ADDRESS: GOLD 0x004bff40 */
/* ADDRESS: GOLDTL 0x004c0740 */

int __cdecl fcn_004c0740(void* stream)
{
	int count;
	char* q;
	char* n;

	count = 0;
	for (q = fcn_00502cd0(0, 2, 7, 4, 0x1d); q != 0; q = gm_NextEntityQueryMatch()) {
		if (*(char**) (q + 0x29) != 0)
			count += fcn_004be340(*(char**) (q + 0x29));
	}
	if (!(fcn_00430910(&count, 4, 1, stream) > 0))
		return 0;
	for (q = fcn_00502cd0(0, 2, 7, 4, 0x1d); q != 0; q = gm_NextEntityQueryMatch()) {
		if (*(char**) (q + 0x29) != 0) {
			for (n = *(char**) (q + 0x29); n != 0; n = *(char**) (n + 0x3c)) {
				if (!(fcn_00430910(n, 4, 1, stream) > 0))
					return 0;
				if (!(fcn_00430910(n + 4, 4, 1, stream) > 0))
					return 0;
				if (!(fcn_00430910(n + 8, 0x18, 1, stream) > 0))
					return 0;
				if (!(fcn_00430910(n + 0x20, 0x18, 1, stream) > 0))
					return 0;
			}
		}
	}
	return 1;
}
