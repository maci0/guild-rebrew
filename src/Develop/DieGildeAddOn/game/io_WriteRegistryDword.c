

extern int (__stdcall *imp_RegSetValueExA)(int, int, int, int, int*, int);

int __cdecl io_WriteRegistryDword(int a1, int a2, int a3)
{
	return imp_RegSetValueExA(a1, a2, 0, 4, &a3, 4);
}
