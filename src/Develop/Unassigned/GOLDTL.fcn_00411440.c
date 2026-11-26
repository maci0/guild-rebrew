

int __cdecl io_ReadRegistryString(int, int, char*);
double __cdecl fcn_0064d62e(char*);

float __cdecl fcn_00411440(int a1, int a2)
{
	char buf[0x80];

	if (io_ReadRegistryString(a1, a2, buf) != 0) {
		return (float) fcn_0064d62e(buf);
	}
	return 0.0f;
}
