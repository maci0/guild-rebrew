// FUNCTION: GOLD 0x00495760
// SIZE: 23
// fcn_00495760 — store into array 0xf86900 at index [0xf83ea4], bump counter.

int __cdecl fcn_00495760(int a)
{
	int idx;
	idx = *(int*) 0xf83ea4;
	*(int*) ((char*) 0xf86900 + idx * 4) = a;
	*(int*) 0xf83ea4 = idx + 1;
	return idx + 1;
}
