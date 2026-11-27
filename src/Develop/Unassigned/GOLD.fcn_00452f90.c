/* ADDRESS: GOLD 0x00452f90 */
void __cdecl d3_ApplyMaterialVertexColors(char* mesh, char* obj)
{
	unsigned char flags;
	unsigned char high;
	unsigned char b211;
	unsigned char low;
	char* vert;
	int i;
	char* p;
	unsigned char col[4];
	float bias;
	float scale;
	float v;
	unsigned char out[4];

	flags = *(unsigned char*) (mesh + 0x212);
	b211 = *(unsigned char*) (mesh + 0x211);
	high = (unsigned char) ~b211 >> 7;
	low = (unsigned char) ~flags & 1;
	if (flags & 2) {
		return;
	}
	vert = *(char**) (obj + 4);
	for (i = 0; i < *(int*) (obj + 0xc); i++) {
		p = *(char**) (vert + 0x14);
		if (p != 0) {
			if (low) {
				*(unsigned char*) (vert + 0x26) =
					(unsigned char) ((((*(unsigned char*) (p + 0x68) >> 2)
						^ *(unsigned char*) (vert + 0x26)) & 4)
						^ *(unsigned char*) (vert + 0x26));
			}
			if (high != 0) {
				*(unsigned int*) col = *(unsigned int*) (p + 0x6c);
			} else {
				*(unsigned int*) col = *(unsigned int*) (obj + 0x190);
			}
			if (col[2] & 1) {
				int c;

				bias = (float) col[1];
				scale = (float) col[0];
				for (c = 0; c < 3; c++) {
					char* dst;

					dst = *(char**) (vert + c * 4);
					v = (((float*) dst)[0xc] * 0.30f
						+ ((float*) dst)[0xd] * 0.59f
						+ ((float*) dst)[0xe] * 0.11f
						+ bias) * 0.00390625f * scale;
					if (255.0f < v) {
						v = 255.0f;
					}
					out[0] = (unsigned char) (int) v;
					out[1] = out[0];
					out[2] = out[0];
					out[3] = out[0];
					*(int*) (dst + 0x40) = *(int*) out;
					*(int*) (dst + 0x44) = *(int*) out;
				}
			} else if (col[0] < 0xff) {
				int c;

				for (c = 0; c < 3; c++) {
					char* dst;

					dst = *(char**) (vert + c * 4);
					*(unsigned char*) (dst + 0x43) = col[0];
					*(unsigned char*) (dst + 0x47) = col[0];
				}
			}
		}
		vert += 0x28;
	}
}
