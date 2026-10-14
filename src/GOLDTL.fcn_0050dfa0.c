


int __cdecl fcn_00502cd0(int, int, int, int);
int __cdecl fcn_0050df70(void*, int);

int __cdecl fcn_0050dfa0(void* a1, int a2)
{
	int r;

	r = fcn_00502cd0(*(int*) ((char*) a1 + 0x14), 1, 0, a2);
	if (r == 0) {
		return 0;
	}
	return fcn_0050df70(a1, r);
}
