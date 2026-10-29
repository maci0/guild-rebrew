typedef struct {
	int f0;
	int f4;
	int f8;
	int fc;
	int f10;
} Unk44da60;

int __cdecl fcn_00401180(void*, void*);

/* ADDRESS: GOLDTL 0x0044da60 */
int __cdecl fcn_0044da60(void* a, Unk44da60* p)
{
	return fcn_00401180(a, (void*) (((p->f8 * 7) << 5) + p->f10 + 0xc1));
}
