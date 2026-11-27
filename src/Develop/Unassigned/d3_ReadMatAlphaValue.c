typedef struct {
	int f0;
	int f4;
	int f8;
	int fc;
	int f10;
} D3_BIN_MAT_ALPHA_VAL_CTX;

int __cdecl vfs_ReadByte(void*, void*);

/* ADDRESS: GOLDTL 0x0044da60 */
int __cdecl d3_ReadMatAlphaValue(void* a, D3_BIN_MAT_ALPHA_VAL_CTX* p)
{
	return vfs_ReadByte(a, (void*) (((p->f8 * 7) << 5) + p->f10 + 0xc1));
}
