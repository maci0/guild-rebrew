typedef float* (__cdecl* Corners45a910)(char* obj, char* m, char* p);

void __cdecl fcn_00438100(char* obj, char* cam, int flag);

/* Clamps eight 0x50-byte rows of the corner buffer against the first
 * three floats: low corner to the minimum, +0x10 corner to the maximum. */
/* ADDRESS: GOLDTL 0x0045a910 */
char __cdecl fcn_0045a910(char* a0, float* a1)
{
	unsigned int v4;
	char* m;
	unsigned char v2;
	float* src;
	float* row;
	int j;
	int k;

	v4 = *(unsigned int*) (a0 + 0x1ec);
	if (v4 != 0) {
		m = *(char**) (a0 + 0x1cc);
		if (m != 0) {
			v2 = *(unsigned char*) (a0 + 0x216);
			if ((v2 & 3) == 0 || (v2 & 0xc) != 0) {
				if ((v2 & 0x20) == 0) {
					fcn_00438100(a0, *(char**) 0x6b8014, 0);
				}
				src = (*(Corners45a910*) (*(char**) (m + 0x318) + 0x1f0))(a0, m, *(char**) (a0 + 0x1ec) + 8);
				for (j = 0; j < 8; j++) {
					row = src + j * 20;
					for (k = 0; k < 3; k++) {
						a1[k] = (double) a1[k] < row[k] ? a1[k] : row[k];
						a1[k + 4] = (double) a1[k + 4] > row[k] ? a1[k + 4] : row[k];
					}
				}
			}
		}
	}
	return 1;
}
