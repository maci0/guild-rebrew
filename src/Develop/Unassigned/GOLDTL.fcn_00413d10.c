char __cdecl fcn_0045b990(char* map, float* pos, int* col, int* row, float* height);

/* ADDRESS: GOLDTL 0x00413d10 */
float __cdecl fcn_00413d10(float* pos)
{
	char* world;
	char* map;
	int col;
	float height;
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
			if (fcn_0045b990(map, pos, &col, &row, &height) != 0) {
				acc = *(volatile float*) &acc;
				k = -4;
				width = *(int*) (map + 0x20);
				off = (row - 4) * width;
				do {
					for (dx = -4; dx < 4; dx = dx + 1) {
						if (row + k < width - 1 && dx + col < width - 1 && row + k > 0 && dx + col > 0) {
							acc = acc + ((float) *(unsigned char*) (*(char**) (map + 0x28) + off + dx + col) * *(float*) (map + 0x14) + *(float*) (map + 4));
						} else {
							acc = acc + height;
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
