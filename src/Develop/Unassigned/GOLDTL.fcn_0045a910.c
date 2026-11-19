typedef float* (__cdecl* Corners45a910)(char* obj, char* m, char* p);

void __cdecl d3_UpdateObjectCameraTransform(char* obj, char* cam, int flag);

/* Clamps eight 0x50-byte rows of the corner buffer against the first
 * three floats: low corner to the minimum, +0x10 corner to the maximum. */
/* ADDRESS: GOLDTL 0x0045a910 */
char __cdecl fcn_0045a910(char* object, float* bounds)
{
	unsigned int v4;
	char* m;
	unsigned char flags;
	float* src;
	float* row;
	int j;
	int k;

	v4 = *(unsigned int*) (object + 0x1ec);
	if (v4 != 0) {
		m = *(char**) (object + 0x1cc);
		if (m != 0) {
			flags = *(unsigned char*) (object + 0x216);
			if ((flags & 3) == 0 || (flags & 0xc) != 0) {
				if ((flags & 0x20) == 0) {
					d3_UpdateObjectCameraTransform(object, *(char**) 0x6b8014, 0);
				}
				src = (*(Corners45a910*) (*(char**) (m + 0x318) + 0x1f0))(object, m, *(char**) (object + 0x1ec) + 8);
				for (j = 0; j < 8; j++) {
					row = src + j * 20;
					for (k = 0; k < 3; k++) {
						bounds[k] = (double) bounds[k] < row[k] ? bounds[k] : row[k];
						bounds[k + 4] = (double) bounds[k + 4] > row[k] ? bounds[k + 4] : row[k];
					}
				}
			}
		}
	}
	return 1;
}
