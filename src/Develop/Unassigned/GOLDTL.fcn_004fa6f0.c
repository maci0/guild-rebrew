


extern char g_1043370[];

char __cdecl d3sm_SampleHeight(char*, int, int*, int*, int*);

int __cdecl gm_PosToStatsGrid(int position, int* column, int* row)
{
	char* g;
	int div;
	int tmp;

	g = (*(char**)g_1043370);
	div = *(int*) (g + 0x20) / 8;
	if (d3sm_SampleHeight(g, position, column, row, &tmp) != 0) {
		*column /= div;
		*row /= div;
		return 1;
	}
	return 0;
}
