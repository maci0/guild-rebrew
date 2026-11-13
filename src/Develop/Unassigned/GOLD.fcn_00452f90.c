/* ADDRESS: GOLD 0x00452f90 */
void __cdecl fcn_00452f90(char* mesh, char* obj)
{
	unsigned char flags;
	unsigned char high;
	int count;
	char* vert;
	int i;
	float* p;
	float scale;
	float bias;
	float v;
	unsigned char out[4];

	flags = *(unsigned char*) (mesh + 0x212);
	high = (unsigned char) (~*(unsigned char*) (mesh + 0x211) >> 7);
	if (flags & 2) {
		return;
	}
	count = *(int*) (obj + 0xc);
	vert = *(char**) (obj + 4);
	for (i = 0; i < count; i++) {
		p = *(float**) (vert + 0x14);
		if (p == 0) {
			goto next;
		}
		if ((flags & 1) == 0) {
			*(unsigned char*) (vert + 0x26) =
				(unsigned char) ((((*(unsigned char*) ((char*) p + 0x68) >> 2)
					^ *(unsigned char*) (vert + 0x26)) & 4)
					^ *(unsigned char*) (vert + 0x26));
		}
		if (high != 0) {
			scale = *(float*) ((char*) p + 0x6c);
		} else {
			scale = *(float*) (obj + 0x190);
		}
		bias = (float) (unsigned char) (int) scale;
		scale = (float) ((unsigned char) (int) (*(float*) &scale));
		{
			int c;

			for (c = 0; c < 3; c++) {
				v = (*(float**) (vert + c * 4))[0xc] * 0.30f
					+ (*(float**) (vert + c * 4))[0xd] * 0.59f
					+ (*(float**) (vert + c * 4))[0xe] * 0.11f;
				v = (v + bias) * 0.00390625f * scale;
				if (!(v < 255.0f)) {
					v = 255.0f;
				}
				out[0] = (unsigned char) (int) v;
				out[1] = out[0];
				out[2] = out[0];
				out[3] = out[0];
				*(int*) (*(char**) (vert + c * 4) + 0x40) = *(int*) out;
				*(int*) (*(char**) (vert + c * 4) + 0x44) = *(int*) out;
			}
		}
next:
		vert += 0x28;
	}
}
