


int __cdecl vfs_LookupPath(int, int, int*);
void __cdecl fcn_0042f240(int, int, int, int);

int __cdecl fcn_0042f690(int a1, int a2, int a3, int a4)
{
	int r;

	r = vfs_LookupPath(a1, a2, &a2);
	if (r != 0) {
		fcn_0042f240(r, a2, a3, a4);
		return a4;
	}
	return 0;
}
