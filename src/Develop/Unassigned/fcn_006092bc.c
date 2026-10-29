/*
 * Library code, not game source. The declared 3488-byte extent is two adjacent
 * d3dx8.lib obj\i386\createmesh.obj code sections placed by the linker:
 *   0x6092bc (329 bytes)  GXTri3Mesh<unsigned int,0,-1>::Optimize2
 *   0x609405 (3159 bytes) CD3DXSkinMesh<unsigned int,0,-1>::ConvertToBlendedMesh
 * Both match the reference byte-for-byte except their own relocation fields
 * (9 and 47). They are __thiscall / __stdcall C++ members with SEH
 * (_except_handler3) frames, so no C body can reproduce them. Extent split and
 * evidence: .scratch/lead/stub2-report-2.md.
 */
/* ADDRESS: GOLDTL 0x006092bc */
int __cdecl fcn_006092bc(void)
{
    /* Stub kept so coverage accounting stays at NO_SOURCE 0; a faithful body
       cannot exist for a row that spans two library functions. */
    return 0;
}
