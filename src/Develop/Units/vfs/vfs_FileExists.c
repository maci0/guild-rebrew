extern int vfs_RootDir;




int __cdecl vfs_LookupPath(int, int, int*);

/* ADDRESS: GOLDDE 0x00401090 */
int __cdecl vfs_FileExists(int a)
{
	return vfs_LookupPath(a, vfs_RootDir, &a) != 0;
}
