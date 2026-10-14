char __cdecl fcn_0045b990(char* map, float* pos, int* col, int* row, float* height);

/* Average the scaled height samples in the 8 by 8 cells around pos.
 * A missing map returns the shared zero; a miss on the cell lookup
 * returns the zero accumulator without the final scale.
 * col sits under height. Both arms read acc through a volatile so the
 * load is hoisted to just after the lookup call. */
/* ADDRESS: GOLDTL 0x00413d10 */

float __cdecl fcn_00413d10(float* pos)
{
	char* world;
	char* map;
	// SIZE 0x8
	struct Slot {
		int col;
		float height;
	} cell;
	int row;
	float acc;
	int k;
	int dx;
	int width;
	int off;

	acc = 0.0f;
	world = *(char**) 0x67a370;
	if (world != 0) {
		map = *(char**) (world + 0xb0);
		if (map != 0) {
			if (fcn_0045b990(map, pos, &cell.col, &row, &cell.height) != 0) {
				acc = *(volatile float*) &acc;
				width = *(int*) (map + 0x20);
				k = -4;
				off = (row - 4) * width;
				do {
					for (dx = -4; dx < 4; dx = dx + 1) {
						if (row + k > 0 && row + k < width - 1 && cell.col + dx > 0 && cell.col + dx < width - 1) {
							acc = acc + ((float) *(unsigned char*) (*(char**) (map + 0x28) + off + dx + cell.col) * *(float*) (map + 0x14) + *(float*) (map + 4));
						} else {
							acc = acc + cell.height;
						}
					}
					off = off + width;
					k = k + 1;
				} while (k < 4);
				return acc * *(float*) 0x662a38;
			}
			acc = *(volatile float*) &acc;
			return acc;
		}
	}
	return *(float*) 0x6628a8;
}
