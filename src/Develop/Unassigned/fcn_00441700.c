void __cdecl d3_BuildFloorGeometry(void* p);

/* ADDRESS: GOLDTL 0x00441700 */
void __cdecl fcn_00441700(void* p, int v)
{
    if (p) {
        *(int*)((char*)p + 0x84) = v;
        d3_BuildFloorGeometry(p);
    }
}
