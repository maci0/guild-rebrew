char* __cdecl fcn_00402610(char*);
char __cdecl fcn_0045b990(char*, float*, int*, int*, float*);
void __cdecl fcn_00441720(int, float*, int, int*, int*, float*);
int __cdecl fcn_00413190(int);
void __cdecl fcn_00438b40(char*, float*);

// FUNCTION: GOLD 0x406a70
// SIZE: 336
// FUNCTION: GOLDTL 0x407610
// SIZE: 326

/* Eases a character's height towards the ground of its map cell; returns
 * the cell type. */
int __cdecl fcn_00407610(char* ev)
{
	char* map;
	char* obj;
	char* node;
	int cell;
	int row;
	int col;
	float ground;
	float height;
	float pos[4];

	map = fcn_00402610(*(char**) (ev + 0x14));
	obj = *(char**) (ev + 0x14);
	cell = 0;
	node = *(char**) (obj + 0x34);
	if (map != 0) {
		pos[0] = *(float*) (node + 0x4c);
		pos[1] = *(float*) (node + 0x50);
		pos[2] = *(float*) (node + 0x54);
		if (fcn_0045b990(map, pos, &col, &row, &height)) {
			cell = *(int*) (*(char**) (map + 0x24) + (*(int*) (map + 0x20) * row + col) * 0x1c);
			if ((cell != 0 && cell != 0xd) || *(int*) (*(char**) (obj + 0x88) + 0xac) != 0) {
				node = *(char**) (obj + 0x34);
				if (*(int*) (*(char**) (obj + 0x88) + 0xac) != 0) {
					fcn_00441720(*(int*) (*(char**) (obj + 0x88) + 0xac), (float*) (node + 0x4c), 1, &col, &row, &ground);
					if (cell == 0 || cell == 0xd || !(ground - height < -5.0)) {
						height = ground;
					}
				}
				if (fcn_00413190(*(int*) (obj + 0x88)) == 0) {
					height += 3.0f;
				}
				*(float*) (node + 0x50) = (height - *(float*) (node + 0x50)) * 0.25f + *(float*) (node + 0x50);
				fcn_00438b40(node, (float*) (node + 0x4c));
			}
		}
	}
	return cell;
}

/* Pair list walked by fcn_00407760. count at +0, bytes at +8. */
// SIZE 0xc
typedef struct PairRun {
	int count;
	int pad4;
	unsigned char* bytes;
} PairRun;

// FUNCTION: GOLDTL 0x407760
// SIZE: 159

int __cdecl fcn_00407760(char* flags, PairRun* src, char* dst, char* scale)
{
	int step;
	int i;
	int n;
	int hi;
	unsigned char* bytes;

	n = 0;
	i = 1;
	if (flags != 0 && (flags[4] & 0x10) != 0) {
		step = 2;
	} else {
		step = (int) (*(float*) 0x6628e0 / *(float*) (scale + 0x10) + *(float*) 0x6628cc);
		if (step < i) {
			step = i;
		}
	}
	while (i < src->count) {
		bytes = src->bytes;
		hi = bytes[i * 2 + 1];
		n = n + 1;
		dst[n * 2 - 2] = bytes[i * 2];
		dst[n * 2 - 1] = (char) hi;
		i = i + step;
	}
	if (i != src->count - 1) {
		bytes = src->bytes;
		hi = bytes[src->count * 2 - 1];
		n = n + 1;
		dst[n * 2 - 2] = bytes[src->count * 2 - 2];
		dst[n * 2 - 1] = (char) hi;
	}
	return n;
}
