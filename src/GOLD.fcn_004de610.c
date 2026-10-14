/* ADDRESS: GOLD 0x004de610 */
// fcn_004de610 — out = [0x92bcc0 + ([0x6f0db0] % [0x60d350])*4] % a; [0x6f0db0]++; return out.

int __cdecl fcn_004de610(int a)
{
	int c;
	int r;
	int out;
	c = *(int*) 0x6f0db0;
	r = c % *(int*) 0x60d350;
	out = *(int*) (0x92bcc0 + r * 4) % a;
	*(int*) 0x6f0db0 = c + 1;
	return out;
}
