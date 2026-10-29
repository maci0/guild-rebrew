


char* __cdecl fcn_00502cd0(int, int, int, ...);

int __cdecl fcn_005764a0(char* e, unsigned short t)
{
	char* r;

	if (t == 0x24b || t == 0x256 || t == 0x266) {
		r = fcn_00502cd0(*(int*) (e + 0x5d), 2, 6, 0, t);
		if (r != 0 && *(int*) (r + 0x1c) > 0) {
			return 1;
		}
	}
	return 0;
}
