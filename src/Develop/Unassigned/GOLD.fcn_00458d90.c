void __cdecl d3_SetIdentityMatrix4x4(float*);
void __cdecl d3_ComposeNodeMatrix(int, int, float*, float*);
void __cdecl d3_MultiplyAffineMatrices(float*, float*, float*);

/* ADDRESS: GOLD 0x00458d90 */
void __cdecl d3_BuildViewMatrix(int source, char* view, int flags, float* out)
{
    float identity[16];
    float transform[16];

    d3_SetIdentityMatrix4x4(identity);
    if (view != 0) {
        d3_ComposeNodeMatrix(source, flags, identity, transform);
        transform[12] -= *(float*) (view + 0x4c);
        transform[13] -= *(float*) (view + 0x50);
        transform[14] -= *(float*) (view + 0x54);
        transform[12] -= *(float*) (view + 0x78);
        transform[13] -= *(float*) (view + 0x7c);
        transform[14] -= *(float*) (view + 0x80);
        d3_MultiplyAffineMatrices(transform, (float*) (view + 0x18c), out);
    } else {
        d3_ComposeNodeMatrix(source, flags, identity, out);
    }
}
