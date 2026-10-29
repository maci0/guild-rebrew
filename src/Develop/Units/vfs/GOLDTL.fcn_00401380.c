

void __cdecl fcn_00401360(int, int);
void __cdecl vfs_fwrite(int, int, int, int);

void __cdecl fcn_00401380(int a1, int a2, int a3)
{
	fcn_00401360(a1, a2);
	vfs_fwrite(a3, a2, 1, a1);
}
