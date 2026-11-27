#define I32(p) (*(int*)(p))
#define U32(p) (*(unsigned int*)(p))
#define F32(p) (*(float*)(p))

#if defined(REBREW_GOLD)
/* ADDRESS: GOLD 0x004463b0 */
char __cdecl d3_GetFloorHeight(char* terrain, float* position, char coarse, int* outX, int* outY, float* height)
{
    float x;
    float z;
    float u;
    float v;
    unsigned int step;
    unsigned int ix;
    unsigned int iz;


    int size;
    unsigned char* triangles;
    int kind;
    float base;
    float dx;
    float dz;
    if (!terrain)
        return 0;
    x = position[0];
    x -= F32(terrain + 0x90);
    z = position[2];
    z -= F32(terrain + 0x98);
    if (F32(terrain + 0xa0) != 0.0f)
        x = (float) ((double) x / F32(terrain + 0xa0));
    if (F32(terrain + 0xb8) != 0.0f)
        z = (float) ((double) z / F32(terrain + 0xb8));
    *outX = (int)(x + 0.5f);
    *outY = (int)(z + 0.5f);
    size = I32(terrain);
    if (*outX < 0 || *outX >= size || *outY < 0 || *outY >= size)
        return 0;
    if (!height)
        goto fail_1;
    triangles = *(unsigned char**)(terrain + 0x24);
    step = 1;
    if (coarse) {
        kind = *(unsigned char*)(terrain + (*outX / I32(terrain + 4) + *outY / I32(terrain + 4) * 8) * 100 + 0x13e);
        if (kind == 2 || kind == 4) {
            triangles = *(unsigned char**)(terrain + 0x24 + (kind >> 1) * 4);
            step = kind;
        }
    }
    ix = ~(step - 1) & *outX;
    u = (x - (int)ix) / (float)step;
    iz = ~(step - 1) & *outY;
    v = (z - (int)iz) / (float)step;



    if (triangles && (triangles[ix / step + ((iz / step) * size) / step] & 0x80)) {
        if (v + u > 1.0f) {
            base = (*(unsigned char**)(terrain + 0x10))[((ix + step) & U32(terrain + 0xc)) + ((iz + step) & U32(terrain + 0xc)) * size];
            dx = (*(unsigned char**)(terrain + 0x10))[ix + ((iz + step) & U32(terrain + 0xc)) * size] - base;
            dz = (*(unsigned char**)(terrain + 0x10))[((ix + step) & U32(terrain + 0xc)) + iz * size] - base;
            u = 1.0f - u;
            v = 1.0f - v;
        } else {
            base = (*(unsigned char**)(terrain + 0x10))[ix + iz * size];
            dx = (*(unsigned char**)(terrain + 0x10))[((ix + step) & U32(terrain + 0xc)) + iz * size] - base;
            dz = (*(unsigned char**)(terrain + 0x10))[ix + ((iz + step) & U32(terrain + 0xc)) * size] - base;
        }
    } else {
        if ((1.0f - v) + u > 1.0f) {
            base = (*(unsigned char**)(terrain + 0x10))[((ix + step) & U32(terrain + 0xc)) + iz * size];
            dx = (*(unsigned char**)(terrain + 0x10))[ix + iz * size] - base;
            dz = (*(unsigned char**)(terrain + 0x10))[((ix + step) & U32(terrain + 0xc)) + ((iz + step) & U32(terrain + 0xc)) * size] - base;
            u = 1.0f - u;
        } else {
            base = (*(unsigned char**)(terrain + 0x10))[ix + ((iz + step) & U32(terrain + 0xc)) * size];
            dx = (*(unsigned char**)(terrain + 0x10))[((ix + step) & U32(terrain + 0xc)) + ((iz + step) & U32(terrain + 0xc)) * size] - base;
            dz = (*(unsigned char**)(terrain + 0x10))[ix + iz * size] - base;
            v = 1.0f - v;
        }
    }
    *height = (dx * u + dz * v + base) * F32(terrain + 0xc4) + F32(terrain + 0x94);
    goto fail_1;
fail_1:
	return 1;
}
#else
/* ADDRESS: GOLDTL 0x00441720 */
unsigned char __cdecl d3_GetFloorHeight(int* floor, float* worldPos, unsigned int coarse, unsigned int* gridX, unsigned int* gridZ, float* heightOut)
{
	float pp[4];
	float v13;
	float hx;
	float hz;
	unsigned char* data;
	unsigned int mask;
	unsigned int width;
	int b;
	unsigned int s;
	int v4;
	int v3;
	int v7;
	int v9;
	int v6;
	float v11;
	float v12;

	if (floor == 0) {
		return 0;
	}
	pp[0] = worldPos[0] - *(float*) ((char*) floor + 0x50);
	pp[2] = worldPos[2] - *(float*) ((char*) floor + 0x58);
	if (*(float*) ((char*) floor + 0x60) != 0.0f) {
		pp[0] = pp[0] / *(float*) ((char*) floor + 0x60);
	}
	if (*(float*) ((char*) floor + 0x78) != 0.0f) {
		pp[2] = pp[2] / *(float*) ((char*) floor + 0x78);
	}
	v4 = (int) (pp[0] + 0.5f);
	*gridX = v4;
	v3 = (int) (pp[2] + 0.5f);
	*gridZ = v3;
	if (v4 < 0 || v4 >= floor[0] || v3 < 0 || v3 >= floor[0]) {
		return 0;
	}
	if (heightOut == 0) {
		goto fail_1;
	}
	width = floor[0];
	mask = floor[3];
	data = (unsigned char*) floor[9];
	s = 1;
	if ((unsigned char) coarse != 0) {
		b = *(unsigned char*) ((char*) floor + (v4 / floor[1] + (v3 / floor[1]) * 8) * 500 + 0x28e);
		if (b == 2 || b == 4) {
			data = (unsigned char*) floor[(b >> 1) + 9];
			s = b;
		}
	}
	v4 = v4 & ~(s - 1);
	v3 = v3 & ~(s - 1);
	hx = (pp[0] - (float) v4) / (float) s;
	hz = (pp[2] - (float) v3) / (float) s;
	if (data != 0 && (*(unsigned char*) (data + (unsigned int) v4 / s + ((unsigned int) v3 / s * (int) width) / s) & 0x80) != 0) {
		if (hz + hx > 1.0f) {
			v6 = ((v3 + s) & mask) * width;
			v9 = (v4 + s) & mask;
			v13 = (float) ((unsigned char*) floor[4])[v9 + v6];
			v11 = (float) ((unsigned char*) floor[4])[v6 + v4] - v13;
			v12 = (float) ((unsigned char*) floor[4])[v3 * width + v9] - v13;
			hx = 1.0f - hx;
			hz = 1.0f - hz;
		} else {
			v13 = (float) ((unsigned char*) floor[4])[width * v3 + v4];
			v11 = (float) ((unsigned char*) floor[4])[((v4 + s) & mask) + width * v3] - v13;
			v12 = (float) ((unsigned char*) floor[4])[((v3 + s) & mask) * width + v4] - v13;
		}
	} else {
		if (1.0f - hz + hx > 1.0f) {
			v9 = (v4 + s) & mask;
			v13 = (float) ((unsigned char*) floor[4])[width * v3 + v9];
			v11 = (float) ((unsigned char*) floor[4])[width * v3 + v4] - v13;
			v12 = (float) ((unsigned char*) floor[4])[((v3 + s) & mask) * width + v9] - v13;
			hx = 1.0f - hx;
		} else {
			v7 = ((v3 + s) & mask) * width;
			v13 = (float) ((unsigned char*) floor[4])[v7 + v4];
			v11 = (float) ((unsigned char*) floor[4])[((v4 + s) & mask) + v7] - v13;
			hz = 1.0f - hz;
			v12 = (float) ((unsigned char*) floor[4])[width * v3 + v4] - v13;
		}
	}
	*heightOut = (v11 * hx + v12 * hz + v13) * *(float*) ((char*) floor + 0x84) + *(float*) ((char*) floor + 0x54);
	goto fail_1;
fail_1:
	return 1;
}
#endif
