
/* ADDRESS: GOLDTL 0x0047c4c0 */
int __cdecl d2_CompareRenderQuadTex(const void* a, const void* b)
{
	return *(int*) ((char*) b + 0xa8) - *(int*) ((char*) a + 0xa8);
}
