extern float g_6628a8;
extern float g_662a34;

void __cdecl fcn_004518a0(float* v);
float __cdecl fcn_004519d0(float* m, float* e);

/* ADDRESS: GOLDTL 0x00451a40 */
float __cdecl fcn_00451a40(float* m, float* out, float* e)
{
    float a[3];
    float b[3];
    float c[3];
    float s0;
    float s1;
    float s2;
    float r;
    int i;

    a[0] = (m[8] - m[0xc]) + (m[0x18] - m[0x1c]) +
           (m[0] - m[4]) + (m[0x10] - m[0x14]);
    a[1] = (m[9] - m[0xd]) + (m[0x19] - m[0x1d]) +
           (m[1] - m[5]) + (m[0x11] - m[0x15]);
    a[2] = (m[0xa] - m[0xe]) + (m[0x1a] - m[0x1e]) +
           (m[2] - m[6]) + (m[0x12] - m[0x16]);
    fcn_004518a0(a);

    b[0] = (m[8] - m[0]) + (m[0x18] - m[0x10]) +
           (m[0xc] - m[4]) + (m[0x1c] - m[0x14]);
    b[1] = (m[9] - m[1]) + (m[0x19] - m[0x11]) +
           (m[0xd] - m[5]) + (m[0x1d] - m[0x15]);
    b[2] = (m[0xa] - m[2]) + (m[0x1a] - m[0x12]) +
           (m[0xe] - m[6]) + (m[0x1e] - m[0x16]);
    fcn_004518a0(b);

    c[0] = (m[8] - m[0x18]) + (m[0] - m[0x10]) +
           (m[0xc] - m[0x1c]) + (m[4] - m[0x14]);
    c[1] = (m[9] - m[0x19]) + (m[1] - m[0x11]) +
           (m[0xd] - m[0x1d]) + (m[5] - m[0x15]);
    c[2] = (m[0xa] - m[0x1a]) + (m[2] - m[0x12]) +
           (m[0xe] - m[0x1e]) + (m[6] - m[0x16]);
    fcn_004518a0(c);

    r = fcn_004519d0(a, e);

    s0 = 0.0f;
    s1 = 0.0f;
    s2 = 0.0f;
    for (i = 0; i < 8; i++) {
        s0 += m[i * 4];
        s1 += m[i * 4 + 1];
        s2 += m[i * 4 + 2];
    }
    out[0] = s0 * g_662a34;
    out[1] = s1 * g_662a34;
    out[2] = s2 * g_662a34;
    return r;
}
