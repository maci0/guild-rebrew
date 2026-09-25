char* __cdecl fcn_00402610(char*);
char __cdecl fcn_0045b990(char*, float*, int*, int*, float*);
void __cdecl fcn_00441720(int, float*, int, int*, int*, float*);
int __cdecl fcn_00413190(int);
void __cdecl fcn_00438b40(char*, float*);

// FUNCTION: GOLDTL 0x4053a0
// SIZE: 260

/* Drops an object onto the ground of its map cell; returns the cell type. */
int __cdecl fcn_004053a0(char* obj, int force)
{
	char* map;
	char* node;
	int cell;
	int result;
	int row;
	int col;
	float height;
	float pos[4];

	map = fcn_00402610(obj);
	node = *(char**) (obj + 0x34);
	result = 0;
	if (map != 0) {
		*(int*) &pos[0] = *(int*) (node + 0x4c);
		*(int*) &pos[1] = *(int*) (node + 0x50);
		*(int*) &pos[2] = *(int*) (node + 0x54);
		if (fcn_0045b990(map, pos, &col, &row, &height)) {
			cell = *(int*) (*(char**) (map + 0x24) + (*(int*) (map + 0x20) * row + col) * 0x1c);
			if (force != 0 || (cell != 0 && cell != 0xd)) {
				if (*(int*) (*(char**) (obj + 0x88) + 0xac) != 0) {
					fcn_00441720(*(int*) (*(char**) (obj + 0x88) + 0xac), pos, 1, &col, &row, &height);
				}
				if (fcn_00413190(*(int*) (obj + 0x88)) == 0) {
					pos[1] = height + 3.0f;
				} else {
					pos[1] = height;
				}
				fcn_00438b40(node, pos);
			}
			result = cell;
		} else {
			result = 0;
		}
	}
	return result;
}
