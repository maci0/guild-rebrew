extern float g_6628a8;
extern float g_662a34;

void __cdecl fcn_004518a0(float* v);
void __cdecl fcn_004519d0(float* m, float* e);

/* ADDRESS: GOLDTL 0x00451a40 */
void __cdecl fcn_00451a40(float* m, float* out, float* e)
{
    float basis[16] = { 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 };
    float u[3];
    float v[3];
    float s0;
    float s1;
    float s2;
    int i;

    u[0] = m[0x10] - m[0x14];
    u[1] = m[0x11] - m[0x15];
    u[2] = m[0x12] - m[0x16];
    v[0] = m[0] - m[4];
    v[1] = m[1] - m[5];
    v[2] = m[2] - m[6];
    u[0] = v[0] + u[0];
    u[1] = v[1] + u[1];
    u[2] = v[2] + u[2];
    v[0] = m[0x18] - m[0x1c];
    v[1] = m[0x19] - m[0x1d];
    v[2] = m[0x1a] - m[0x1e];
    u[0] = v[0] + u[0];
    u[1] = v[1] + u[1];
    u[2] = v[2] + u[2];
    v[0] = m[8] - m[0xc];
    v[1] = m[9] - m[0xd];
    v[2] = m[0xa] - m[0xe];
    basis[0] = v[0] + u[0];
    basis[1] = v[1] + u[1];
    basis[2] = v[2] + u[2];
    fcn_004518a0(basis + 0);

    u[0] = m[0x1c] - m[0x14];
    u[1] = m[0x1d] - m[0x15];
    u[2] = m[0x1e] - m[0x16];
    v[0] = m[0xc] - m[4];
    v[1] = m[0xd] - m[5];
    v[2] = m[0xe] - m[6];
    u[0] = v[0] + u[0];
    u[1] = v[1] + u[1];
    u[2] = v[2] + u[2];
    v[0] = m[0x18] - m[0x10];
    v[1] = m[0x19] - m[0x11];
    v[2] = m[0x1a] - m[0x12];
    u[0] = v[0] + u[0];
    u[1] = v[1] + u[1];
    u[2] = v[2] + u[2];
    v[0] = m[8] - m[0];
    v[1] = m[9] - m[1];
    v[2] = m[0xa] - m[2];
    basis[4] = v[0] + u[0];
    basis[5] = v[1] + u[1];
    basis[6] = v[2] + u[2];
    fcn_004518a0(basis + 4);

    u[0] = m[4] - m[0x14];
    u[1] = m[5] - m[0x15];
    u[2] = m[6] - m[0x16];
    v[0] = m[0xc] - m[0x1c];
    v[1] = m[0xd] - m[0x1d];
    v[2] = m[0xe] - m[0x1e];
    u[0] = v[0] + u[0];
    u[1] = v[1] + u[1];
    u[2] = v[2] + u[2];
    v[0] = m[0] - m[0x10];
    v[1] = m[1] - m[0x11];
    v[2] = m[2] - m[0x12];
    u[0] = v[0] + u[0];
    u[1] = v[1] + u[1];
    u[2] = v[2] + u[2];
    v[0] = m[8] - m[0x18];
    v[1] = m[9] - m[0x19];
    v[2] = m[0xa] - m[0x1a];
    basis[8] = v[0] + u[0];
    basis[9] = v[1] + u[1];
    basis[10] = v[2] + u[2];
    fcn_004518a0(basis + 8);

    fcn_004519d0(basis, e);

    s0 = g_6628a8;
    s1 = g_6628a8;
    s2 = g_6628a8;
    for (i = 0; i < 8; i++) {
        s0 += m[i * 4];
        s1 += m[i * 4 + 1];
        s2 += m[i * 4 + 2];
    }
    out[0] = s0 * g_662a34;
    out[1] = s1 * g_662a34;
    out[2] = s2 * g_662a34;
}
