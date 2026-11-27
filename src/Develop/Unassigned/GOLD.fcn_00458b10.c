void __cdecl d3_TransformPoint(char* object, float* position, float* out);

/* ADDRESS: GOLD 0x00458b10 */
void __cdecl d3_TransformPointToView(char* object, char* camera, float* position, float* out)
{
    float v[4];

    if ((*(unsigned char*)(object + 0x210) & 0x80) != 0 || camera == 0) {
        d3_TransformPoint(object, position, out);
        return;
    }
    d3_TransformPoint(object, position, v);
    v[0] -= *(float*)(camera + 0x4c);
    v[1] -= *(float*)(camera + 0x50);
    v[2] -= *(float*)(camera + 0x54);
    v[0] -= *(float*)(camera + 0x78);
    v[1] -= *(float*)(camera + 0x7c);
    v[2] -= *(float*)(camera + 0x80);
    out[0] = v[2] * *(float*)(camera + 0x1ac) + v[1] * *(float*)(camera + 0x19c) + v[0] * *(float*)(camera + 0x18c);
    out[1] = v[2] * *(float*)(camera + 0x1b0) + v[1] * *(float*)(camera + 0x1a0) + v[0] * *(float*)(camera + 0x190);
    out[2] = v[2] * *(float*)(camera + 0x1b4) + v[1] * *(float*)(camera + 0x1a4) + v[0] * *(float*)(camera + 0x194);
}
