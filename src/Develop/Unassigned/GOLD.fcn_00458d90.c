void __cdecl fcn_00454500(float*);
void __cdecl fcn_00458cd0(int, int, float*, float*);
void __cdecl fcn_00453ed0(float*, float*, float*);

/* ADDRESS: GOLD 0x00458d90 */
void __cdecl fcn_00458d90(int source, char* view, int flags, float* out)
{
    float identity[16];
    float transform[16];

    fcn_00454500(identity);
    if (view != 0) {
        fcn_00458cd0(source, flags, identity, transform);
        transform[12] -= *(float*) (view + 0x4c);
        transform[13] -= *(float*) (view + 0x50);
        transform[14] -= *(float*) (view + 0x54);
        transform[12] -= *(float*) (view + 0x78);
        transform[13] -= *(float*) (view + 0x7c);
        transform[14] -= *(float*) (view + 0x80);
        fcn_00453ed0(transform, (float*) (view + 0x18c), out);
    } else {
        fcn_00458cd0(source, flags, identity, out);
    }
}
