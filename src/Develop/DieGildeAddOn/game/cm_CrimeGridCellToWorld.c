


extern char tp_ch_PathGrid[];

unsigned short __cdecl gm_RandomMod(int);
void __cdecl d3_GridPointToWorld(char*, int, int, int);

void __cdecl cm_CrimeGridCellToWorld(int x, int y, int c)
{
	char* g;
	int d;
	int a;
	int b;

	g = (*(char**)tp_ch_PathGrid);
	d = *(int*) (g + 0x20) / 8;
	a = gm_RandomMod(d) + d * x;
	b = gm_RandomMod(d) + d * y;
	d3_GridPointToWorld(g, a, b, c);
}
