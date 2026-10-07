extern int g_67a370;

char __cdecl fcn_0045b990(char*, float*, int*, int*, float*);
unsigned short __cdecl fcn_0042e410(int);
char __cdecl fcn_00407e30(char*, float*, float*, int, int, int*, int*, int, int);
void __cdecl fcn_0045b920(char*, int, int, int);

// FUNCTION: GOLD 0x00405160
// FUNCTION: GOLDTL 0x405c70

/* Places a marker on a free cell near a position of the current room map. */
int __cdecl fcn_00405c70(float* pos, int marker)
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
	x = fcn_0042e410(10) + col - 4;
	y = fcn_0042e410(10) + row - 4;
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
	if (fcn_00407e30(map, pos, pos, x, y, &x, &y, 600, 0)) {
		fcn_0045b920(map, x, y, marker);
	} else {
		fcn_0045b920(map, col, row, marker);
	}
	return 1;
}
