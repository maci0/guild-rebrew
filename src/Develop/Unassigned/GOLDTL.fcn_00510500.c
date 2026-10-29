


void* __cdecl fcn_00502cd0(int, int, int, ...);

int __cdecl fcn_00510500(char* e)
{
	int n;

	n = 1;
	if (fcn_00502cd0(*(int*) (e + 0x5d), 2, 6, 0, 0x285)) {
		n = 2;
	}
	if (fcn_00502cd0(*(int*) (e + 0x5d), 2, 6, 0, 0x288)) {
		n++;
	}
	return n;
}
