void __cdecl fcn_0043c2c0(void* p);

/* ADDRESS: GOLDTL 0x00441700 */
void __cdecl fcn_00441700(void* p, int v)
{
    if (p) {
        *(int*)((char*)p + 0x84) = v;
        fcn_0043c2c0(p);
    }
}
