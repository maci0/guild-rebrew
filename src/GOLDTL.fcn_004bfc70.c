/* fcn_004bfc70 — release the entry's handle and clear the pair. */

void __cdecl fcn_0046b2b0(int);

// FUNCTION: GOLDTL 0x4bfc70
void __cdecl fcn_004bfc70(int a1)
{
	fcn_0046b2b0(*(int*) (0x10058a0 + a1 * 8));
	*(int*) (0x10058a0 + a1 * 8) = -1;
	*(int*) (0x10058a4 + a1 * 8) = 0;
}
