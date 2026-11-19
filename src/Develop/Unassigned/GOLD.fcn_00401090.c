extern int g_6b7fdc;




int __cdecl vfs_LookupPath(int, int, int*);

int __cdecl vfs_FileExists(int a)
{
	return vfs_LookupPath(a, g_6b7fdc, &a) != 0;
}
