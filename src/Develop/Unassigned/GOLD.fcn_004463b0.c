#define I32(p) (*(int*)(p))
#define U32(p) (*(unsigned int*)(p))
#define F32(p) (*(float*)(p))
/* ADDRESS: GOLD 0x004463b0 */
char __cdecl fcn_004463b0(char* terrain, float* position, char coarse, int* outX, int* outY, float* height)
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
    x = position[0] - F32(terrain + 0x90);
    z = position[2] - F32(terrain + 0x98);
    if (F32(terrain + 0xa0) != 0.0f)
        x /= F32(terrain + 0xa0);
    if (F32(terrain + 0xb8) != 0.0f)
        z /= F32(terrain + 0xb8);
    *outX = (int)(x + 0.5f);
    *outY = (int)(z + 0.5f);
    size = I32(terrain);
    if (*outX < 0 || *outX >= size || *outY < 0 || *outY >= size)
        return 0;
    if (!height)
        return 1;
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
    iz = ~(step - 1) & *outY;
    u = (x - (int)ix) / (float)step;
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
    return 1;
}
