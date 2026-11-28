extern int vfs_RootDir;




int __cdecl vfs_LookupPath(int, int, int*);

int __cdecl vfs_FileExists(int a)
{
	return vfs_LookupPath(a, vfs_RootDir, &a) != 0;
}
