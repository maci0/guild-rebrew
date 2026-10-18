#include <string.h>
#pragma intrinsic(memcpy)

/* ADDRESS: GOLD 0x00461e90 */
void __cdecl fcn_00461e90(int s)
{
	int inner;
	unsigned int n;

	inner = *(int *)(s + 0x1c);
	n = *(unsigned int *)(inner + 0x14);
	if (n > *(unsigned int *)(s + 0x10))
		n = *(unsigned int *)(s + 0x10);
	if (n == 0)
		return;
	memcpy((void *)*(int *)(s + 0xc), (void *)*(int *)(inner + 0x10), n);
	*(int *)(s + 0xc) += (int)n;
	*(int *)(*(int *)(s + 0x1c) + 0x10) += (int)n;
	*(int *)(s + 0x14) += (int)n;
	*(int *)(s + 0x10) -= (int)n;
	*(unsigned int *)(*(int *)(s + 0x1c) + 0x14) -= n;
	inner = *(int *)(s + 0x1c);
	if (*(int *)(inner + 0x14) == 0)
		*(int *)(inner + 0x10) = *(int *)(inner + 8);
}
