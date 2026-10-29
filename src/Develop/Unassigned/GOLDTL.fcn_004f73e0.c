


int  __cdecl fcn_005d97f0(void*, void*);
extern char g_679060[];
void __cdecl fcn_0051af00(void*, int, int);

int __cdecl fcn_004f73e0(void* a1, void* a2)
{
	int r;

	r = 2;
	if (*(int*) a2 != 3 && *(int*) a2 != 1) {
		return 1;
	}
	if (*(char*) ((char*) a1 + 2) != 6 && *(char*) ((char*) a1 + 2) != 5) {
		return 1;
	}
	if (*(int*) a2 == 3 && *(char*) ((char*) a1 + 2) == 6) {
		r = fcn_005d97f0(a1, a2) | 2;
	} else if (*(int*) a2 == 1 && *(char*) ((char*) a1 + 2) == 6) {
		fcn_0051af00((char*) a2 + 0x14, (int) g_679060, 0x1d35);
	}
	return r;
}
