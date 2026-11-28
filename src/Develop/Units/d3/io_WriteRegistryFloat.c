extern char str_fmt_float[];


void __cdecl fcn_0064d41a(void*, void*, double);
void __cdecl io_WriteRegistryString(int, int, void*);

void __cdecl io_WriteRegistryFloat(int key, int name, float value)
{
	char buf[0x80];

	fcn_0064d41a(buf, str_fmt_float, (double) value);
	io_WriteRegistryString(key, name, buf);
}
