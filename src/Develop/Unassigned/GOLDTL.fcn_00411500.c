

extern int (__stdcall *g_662008)(int, int, int, int, int*, int);

int __cdecl io_WriteRegistryDword(int a1, int a2, int a3)
{
	return g_662008(a1, a2, 0, 4, &a3, 4);
}
