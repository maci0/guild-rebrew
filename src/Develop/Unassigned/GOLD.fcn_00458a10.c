/* ADDRESS: GOLD 0x00458a10 */
void __cdecl fcn_00458a10(char* obj, const float* in, float* out)
{
    float x;
    float y;
    float z;

    out[0] = *(float*) (obj + 0x78) + in[0];
    out[1] = *(float*) (obj + 0x7c) + in[1];
    out[2] = *(float*) (obj + 0x80) + in[2];
    obj = *(char**) (obj + 0x1f8);
    while (obj != 0) {
        x = *(float*) (obj + 0x6c) + out[0];
        y = *(float*) (obj + 0x70) + out[1];
        z = *(float*) (obj + 0x74) + out[2];
        out[0] = z * *(float*) (obj + 0x1ac) + y * *(float*) (obj + 0x19c) + x * *(float*) (obj + 0x18c);
        out[1] = z * *(float*) (obj + 0x1b0) + y * *(float*) (obj + 0x1a0) + x * *(float*) (obj + 0x190);
        out[2] = z * *(float*) (obj + 0x1b4) + y * *(float*) (obj + 0x1a4) + x * *(float*) (obj + 0x194);
        out[0] -= *(float*) (obj + 0x6c);
        out[1] -= *(float*) (obj + 0x70);
        out[2] -= *(float*) (obj + 0x74);
        out[0] += *(float*) (obj + 0x4c);
        out[1] += *(float*) (obj + 0x50);
        out[2] += *(float*) (obj + 0x54);
        out[0] += *(float*) (obj + 0x78);
        out[1] += *(float*) (obj + 0x7c);
        out[2] += *(float*) (obj + 0x80);
        obj = *(char**) (obj + 0x1f8);
    }
}
