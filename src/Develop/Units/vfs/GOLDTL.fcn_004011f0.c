
// GOLDTL body differs from GOLD: passes `x` by VALUE (mov, not lea) and
// the second arg is 4, not 1.  GOLD is `(&x, 1, 1, a)` — per-target divergence,
// so a thin GOLDTL file rather than a shared body.

int __cdecl vfs_ReadData(char* buf, int size, int count, char* stream);

int __cdecl fcn_004011f0(void* a, void* x)
{
	return vfs_ReadData((char*) x, 4, 1, (char*) a);
}
