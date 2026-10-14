extern int* g_6b7d78;



int __cdecl fcn_0064d470(int, int);

int* __cdecl fcn_00422730(int a1)
{
	int* node;

	node = g_6b7d78;
	while (node != 0) {
		if (fcn_0064d470((int) node + 0x32, a1) != 0) {
			break;
		}
		node = (int*) node[0x13c / 4];
	}
	return node;
}
