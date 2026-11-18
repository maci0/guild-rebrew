


extern char g_1043370[];

char __cdecl fcn_0045b990(char*, int, int*, int*, int*);

int __cdecl fcn_004fa6f0(int position, int* column, int* row)
{
	char* g;
	int div;
	int tmp;

	g = (*(char**)g_1043370);
	div = *(int*) (g + 0x20) / 8;
	if (fcn_0045b990(g, position, column, row, &tmp) != 0) {
		*column /= div;
		*row /= div;
		return 1;
	}
	return 0;
}
