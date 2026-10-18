/* Inferred pointer-slot name; native storage owner remains unknown. */
extern void* d3d_VertexBuffer;

/* ADDRESS: GOLD 0x004364f0 */
int __cdecl fcn_004364f0(void** out_ptr, int* out_count)
{
    *out_ptr = d3d_VertexBuffer;
    *out_count = 0x800;
    return 0;
}
