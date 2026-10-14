


extern char* g_773da8;

int __cdecl fcn_00502cd0(int a, int b, int c, int d, int e);
unsigned char* __cdecl fcn_004f18d0(int a, char* e, unsigned char* prev, void* filter, int mask);
int __cdecl fcn_004f1850(void);

unsigned char* __cdecl fcn_004f43b0(char* e, unsigned char lim)
{
	unsigned char* best;
	unsigned char* r;

	best = 0;
	if (*(unsigned short*) (e + 0x27) == 0xffff || *(unsigned short*) (e + 0x27) == *((unsigned short*)g_773da8)) {
		return 0;
	}
	if (!fcn_00502cd0(*(int*) (e + 0x5d), 2, 4, 0x1f8, 6)) {
		return 0;
	}
	r = fcn_004f18d0(0, e, best, (void*) fcn_004f1850, 0xff);
	while (r != 0) {
		if (r[0xc] < lim && (best == 0 || r[0xc] < best[0xc])) {
			best = r;
		}
		r = fcn_004f18d0(0, e, r, (void*) fcn_004f1850, 0xff);
	}
	return best;
}
