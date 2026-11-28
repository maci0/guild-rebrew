extern int d3_ActiveScene;

unsigned short __cdecl gm_RandomMod(unsigned short);
char __cdecl d3sm_SampleHeight(char*, float*, int*, int*, int*);
char __cdecl ch_FindWalkableCell(char*, float*, float*, int, int, int*, int*, int, int);
void __cdecl d3_GridPointToWorld(char*, int, int, float*);


/* ADDRESS: GOLDTL 0x004bc8a0 */
int __cdecl ch_GenerateNearbyWalkablePoints(float* position, int count, float* out)
{
	int ny;
	int y;
	int x;
	int z;
	int nx;
	int idx;
	char* grid;

	grid = *(char**) (((char*)d3_ActiveScene) + 0xb0);
	d3sm_SampleHeight(grid, position, &x, &y, &z);
	for (idx = 0; idx < count; idx++) {
		nx = gm_RandomMod(10) + x - 4;
		ny = gm_RandomMod(10) + y - 4;
		if (*(int*) (grid + 0x20) - 2 < nx)
			nx = *(int*) (grid + 0x20) - 2;
		if (nx < 2)
			nx = 2;
		if (*(int*) (grid + 0x20) - 2 < ny)
			ny = *(int*) (grid + 0x20) - 2;
		if (ny < 2)
			ny = 2;
		if (ch_FindWalkableCell(grid, position, position, nx, ny, &nx, &ny, 0x258, 0) != 0)
			d3_GridPointToWorld(grid, nx, ny, out + idx * 4);
		else
			d3_GridPointToWorld(grid, x, y, out + idx * 4);
	}
	return count;
}
