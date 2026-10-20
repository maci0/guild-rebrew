/* ADDRESS: GOLDTL 0x00441720 */
int __cdecl fcn_00441720(int* a0, float* a1, unsigned int a2, unsigned int* a3, unsigned int* a4, float* a5)
{
	float fx;
	float fz;
	float v13;
	float hx;
	float hz;
	unsigned char* data;
	unsigned int mask;
	unsigned int width;
	unsigned int stride;
	int b;
	int s;
	int v4;
	int v3;
	int v7;
	int v9;
	int v6;
	float v11;
	float v12;

	if (a0 == 0) {
		return 0;
	}
	fx = a1[0] - *(float*) ((char*) a0 + 0x50);
	fz = a1[2] - *(float*) ((char*) a0 + 0x58);
	if (*(float*) ((char*) a0 + 0x60) != *(float*) 0x6628a8) {
		fx = fx / *(float*) ((char*) a0 + 0x60);
	}
	if (*(float*) ((char*) a0 + 0x78) != *(float*) 0x6628a8) {
		fz = fz / *(float*) ((char*) a0 + 0x78);
	}
	v4 = (int) (fx + *(float*) 0x6628cc);
	*a3 = v4;
	v3 = (int) (fz + *(float*) 0x6628cc);
	*a4 = v3;
	if (v4 < 0 || a0[0] <= v4 || v3 < 0 || a0[0] <= v3) {
		return 0;
	}
	if (a5 == 0) {
		return 1;
	}
	width = a0[0];
	stride = a0[1];
	mask = a0[3];
	data = (unsigned char*) a0[9];
	s = 1;
	if ((unsigned char) a2 != 0) {
		b = *(unsigned char*) ((char*) a0 + (v4 / (int) stride + (v3 / (int) stride) * 8) * 500 + 0x28e);
		if (b == 2 || b == 4) {
			data = (unsigned char*) a0[b / 2 + 9];
			s = b;
		}
	}
	v4 = v4 & ~(s - 1);
	v3 = v3 & ~(s - 1);
	fx = (fx - (float) v4) / (float) s;
	fz = (fz - (float) v3) / (float) s;
	if (data != 0 && (*(unsigned char*) (data + (unsigned int) v4 / s + ((unsigned int) v3 / s * (int) width) / s) & 0x80) != 0) {
		if (!(fz + fx > *(float*) 0x6628a0)) {
			v13 = (float) data[width * v3 + v4];
			v11 = (float) data[((v4 + s) & mask) + width * v3] - v13;
			v12 = -v13;
		} else {
			v9 = (v4 + s) & mask;
			v6 = ((v3 + s) & mask) * width;
			v13 = (float) data[v9 + v6];
			v11 = (float) data[v6 + v4] - v13;
			v12 = (float) data[v3 * width + v9] - v13;
			fx = *(float*) 0x6628a0 - fx;
			fz = *(float*) 0x6628a0 - fz;
		}
	} else {
		if (!(*(float*) 0x6628a0 - fz + fx > *(float*) 0x6628a0)) {
			v7 = ((v3 + s) & mask) * width;
			v13 = (float) data[v7 + v4];
			v11 = (float) data[((v4 + s) & mask) + v7] - v13;
			fz = *(float*) 0x6628a0 - fz;
			v12 = -v13;
		} else {
			v9 = (v4 + s) & mask;
			v13 = (float) data[width * v3 + v9];
			v11 = (float) data[width * v3 + v4] - v13;
			v12 = (float) data[((v3 + s) & mask) * width + v9] - v13;
			fx = *(float*) 0x6628a0 - fx;
		}
	}
	*a5 = (v11 * fx + v12 * fz + v13) * *(float*) ((char*) a0 + 0x84) + *(float*) ((char*) a0 + 0x54);
	return 1;
}
