extern char g_67d934[];

unsigned int __cdecl d2_ReadBmpDimensions(void*);
void* __cdecl m_alloc(unsigned int, char*);
unsigned char __cdecl d2_GetBMPData(void* a0, void* a1, int a3);


/* ADDRESS: GOLDTL 0x00475740 */
void* __cdecl d2_LoadBitmap8(void* src)
{
	unsigned int dim;
	void* p;

	dim = d2_ReadBmpDimensions(src);
	if (dim == 0)
		return 0;
	p = m_alloc((dim >> 16) * (dim & 0xffff), g_67d934);
	d2_GetBMPData(src, p, 1);
	return p;
}
