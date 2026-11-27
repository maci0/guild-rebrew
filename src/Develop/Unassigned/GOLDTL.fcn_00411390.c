

typedef int (__stdcall* fcn_00411390_fn)(int, int, int, int, int*, int*);

int __cdecl io_TryReadRegistryDword(int a1, int value, int* out)
{
	int local;

	local = 4;
	if ((*(fcn_00411390_fn*) 0x662004)(a1, value, 0, 0, &value, &local) == 0) {
		*out = value;
		return 1;
	}
	return 0;
}
