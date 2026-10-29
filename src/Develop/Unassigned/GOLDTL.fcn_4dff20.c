
// fcn_004de610 — out = [0x9afe00 + ([0x772f60] % [0x68bfc8])*4] % a; [0x772f60]++; return out.

/* ADDRESS: GOLDTL 0x004dff20 */
int __cdecl fcn_004de610(int a)
{
	int c;
	int r;
	int out;
	c = *(int*) 0x772f60;
	r = c % *(int*) 0x68bfc8;
	out = *(int*) (0x9afe00 + r * 4) % a;
	*(int*) 0x772f60 = c + 1;
	return out;
}
