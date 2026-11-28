extern float flt_0_0;

void __cdecl d3_NormalizeVector(float* v);
void __cdecl d3_MatrixToEulerAngles(float* m, float* e);

/* ADDRESS: GOLDTL 0x00451a40 */
void __cdecl d3_ExtractBoxCenterAndAngles(float* corners, float* centerOut, float* anglesOut)
{
    float basis[16];
    float u[4];
    float v[4];
    float c[4];
    float t[4];
    int i;

    basis[14] = 0.0f;
    basis[13] = 0.0f;
    basis[12] = 0.0f;
    basis[11] = 0.0f;
    basis[9] = 0.0f;
    basis[8] = 0.0f;
    basis[7] = 0.0f;
    basis[6] = 0.0f;
    basis[4] = 0.0f;
    basis[3] = 0.0f;
    basis[2] = 0.0f;
    basis[1] = 0.0f;
    basis[15] = 1.0f;
    basis[10] = 1.0f;
    basis[5] = 1.0f;
    basis[0] = 1.0f;
    u[0] = corners[0x10] - corners[0x14];
    u[1] = corners[0x11] - corners[0x15];
    u[2] = corners[0x12] - corners[0x16];
    v[0] = corners[0] - corners[4];
    v[1] = corners[1] - corners[5];
    v[2] = corners[2] - corners[6];
    u[0] = v[0] + u[0];
    u[1] = v[1] + u[1];
    u[2] = v[2] + u[2];
    v[0] = corners[0x18] - corners[0x1c];
    v[1] = corners[0x19] - corners[0x1d];
    v[2] = corners[0x1a] - corners[0x1e];
    u[0] = v[0] + u[0];
    u[1] = v[1] + u[1];
    u[2] = v[2] + u[2];
    v[0] = corners[8] - corners[0xc];
    v[1] = corners[9] - corners[0xd];
    v[2] = corners[0xa] - corners[0xe];
    t[0] = v[0] + u[0];
    t[1] = v[1] + u[1];
    t[2] = v[2] + u[2];
    basis[0] = t[0];
    basis[1] = t[1];
    basis[2] = t[2];
    d3_NormalizeVector(basis + 0);

    u[0] = corners[0x1c] - corners[0x14];
    u[1] = corners[0x1d] - corners[0x15];
    u[2] = corners[0x1e] - corners[0x16];
    v[0] = corners[0xc] - corners[4];
    v[1] = corners[0xd] - corners[5];
    v[2] = corners[0xe] - corners[6];
    u[0] = v[0] + u[0];
    u[1] = v[1] + u[1];
    u[2] = v[2] + u[2];
    v[0] = corners[0x18] - corners[0x10];
    v[1] = corners[0x19] - corners[0x11];
    v[2] = corners[0x1a] - corners[0x12];
    u[0] = v[0] + u[0];
    u[1] = v[1] + u[1];
    u[2] = v[2] + u[2];
    v[0] = corners[8] - corners[0];
    v[1] = corners[9] - corners[1];
    v[2] = corners[0xa] - corners[2];
    t[0] = v[0] + u[0];
    t[1] = v[1] + u[1];
    t[2] = v[2] + u[2];
    basis[4] = t[0];
    basis[5] = t[1];
    basis[6] = t[2];
    d3_NormalizeVector(basis + 4);

    u[0] = corners[4] - corners[0x14];
    u[1] = corners[5] - corners[0x15];
    u[2] = corners[6] - corners[0x16];
    v[0] = corners[0xc] - corners[0x1c];
    v[1] = corners[0xd] - corners[0x1d];
    v[2] = corners[0xe] - corners[0x1e];
    u[0] = v[0] + u[0];
    u[1] = v[1] + u[1];
    u[2] = v[2] + u[2];
    v[0] = corners[0] - corners[0x10];
    v[1] = corners[1] - corners[0x11];
    v[2] = corners[2] - corners[0x12];
    u[0] = v[0] + u[0];
    u[1] = v[1] + u[1];
    u[2] = v[2] + u[2];
    v[0] = corners[8] - corners[0x18];
    v[1] = corners[9] - corners[0x19];
    v[2] = corners[0xa] - corners[0x1a];
    t[0] = v[0] + u[0];
    t[1] = v[1] + u[1];
    t[2] = v[2] + u[2];
    basis[8] = t[0];
    basis[9] = t[1];
    basis[10] = t[2];
    d3_NormalizeVector(basis + 8);

    d3_MatrixToEulerAngles(basis, anglesOut);

    c[0] = flt_0_0;
    c[1] = flt_0_0;
    c[2] = flt_0_0;
    for (i = 0; i < 8; i++) {
        c[0] += corners[i * 4];
        c[1] += corners[i * 4 + 1];
        c[2] += corners[i * 4 + 2];
    }
    centerOut[0] = c[0] * 0.125f;
    centerOut[1] = c[1] * 0.125f;
    centerOut[2] = c[2] * 0.125f;
}
