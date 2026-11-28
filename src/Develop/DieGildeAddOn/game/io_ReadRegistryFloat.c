

int __cdecl io_ReadRegistryString(int, int, char*);
double __cdecl fcn_0064d62e(char*);

float __cdecl io_ReadRegistryFloat(int key, int name)
{
	char buf[0x80];

	if (io_ReadRegistryString(key, name, buf) != 0) {
		return (float) fcn_0064d62e(buf);
	}
	return 0.0f;
}
