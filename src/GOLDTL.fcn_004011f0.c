
// GOLDTL body differs from GOLD: passes `x` by VALUE (mov, not lea) and
// the second arg is 4, not 1.  GOLD is `(&x, 1, 1, a)` — per-target divergence,
// so a thin GOLDTL file rather than a shared body.

int __cdecl fcn_004306b0(void*, int, int, int);

void __cdecl fcn_004011f0(int a, void* x)
{
	fcn_004306b0(x, 4, 1, a);
}
