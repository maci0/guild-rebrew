typedef struct {
	int f0;
	int f4;
	int f8;
	int fc;
	int f10;
} Unk44da60;

int __cdecl vfs_ReadByte(void*, void*);

/* ADDRESS: GOLDTL 0x0044da60 */
int __cdecl fcn_0044da60(void* a, Unk44da60* p)
{
	return vfs_ReadByte(a, (void*) (((p->f8 * 7) << 5) + p->f10 + 0xc1));
}
