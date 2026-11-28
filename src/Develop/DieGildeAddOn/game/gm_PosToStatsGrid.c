


extern char tp_ch_PathGrid[];

char __cdecl d3sm_3D2SuperMap(char*, int, int*, int*, int*);

/* ADDRESS: GOLDDE 0x004e64d0 */
int __cdecl gm_PosToStatsGrid(int position, int* column, int* row)
{
	char* g;
	int div;
	int tmp;

	g = (*(char**)tp_ch_PathGrid);
	div = *(int*) (g + 0x20) / 8;
	if (d3sm_3D2SuperMap(g, position, column, row, &tmp) != 0) {
		*column /= div;
		*row /= div;
		return 1;
	}
	return 0;
}
