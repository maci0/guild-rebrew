extern int g_67a370;

char __cdecl fcn_0045b990(char*, float*, int*, int*, float*);
unsigned short __cdecl gm_RandomMod(int);
char __cdecl ch_FindWalkableCell(char*, float*, float*, int, int, int*, int*, int, int);
void __cdecl d3_GridPointToWorld(char*, int, int, int);


/* Places a marker on a free cell near a position of the current room map. */
/* ADDRESS: GOLDTL 0x00405c70 */
int __cdecl ch_SelectNearbyPosition(float* pos, int marker)
{
	char* map;
	int col;
	int row;
	float height;
	int x;
	int y;

	map = *(char**) (((char*)g_67a370) + 0xb0);
	if (map == 0) {
		return 0;
	}
	fcn_0045b990(map, pos, &col, &row, &height);
	x = gm_RandomMod(10) + col - 4;
	y = gm_RandomMod(10) + row - 4;
	if (*(int*) (map + 0x20) - 2 < x) {
		x = *(int*) (map + 0x20) - 2;
	}
	if (x < 2) {
		x = 2;
	}
	if (*(int*) (map + 0x20) - 2 < y) {
		y = *(int*) (map + 0x20) - 2;
	}
	if (y < 2) {
		y = 2;
	}
	if (ch_FindWalkableCell(map, pos, pos, x, y, &x, &y, 600, 0)) {
		d3_GridPointToWorld(map, x, y, marker);
	} else {
		d3_GridPointToWorld(map, col, row, marker);
	}
	return 1;
}
