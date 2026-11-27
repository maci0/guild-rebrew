extern char g_6772b4[];


void __cdecl fcn_0064d41a(void*, void*, double);
void __cdecl io_WriteRegistryString(int, int, void*);

void __cdecl io_WriteRegistryFloat(int key, int name, float value)
{
	char buf[0x80];

	fcn_0064d41a(buf, g_6772b4, (double) value);
	io_WriteRegistryString(key, name, buf);
}
