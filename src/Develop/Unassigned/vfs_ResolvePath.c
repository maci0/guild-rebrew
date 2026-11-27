


int __cdecl vfs_LookupPath(int, int, int*);
void __cdecl fcn_0042f240(int, int, int, int);

int __cdecl vfs_ResolvePath(int path, int root, int a3, int a4)
{
	int file;

	file = vfs_LookupPath(path, root, &root);
	if (file != 0) {
		fcn_0042f240(file, root, a3, a4);
		return a4;
	}
	return 0;
}
