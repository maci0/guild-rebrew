
// fcn_004eea70 twin — same shape as fcn_004eea70 (GOLDTL 0x4f08d0 / GOLD
// 0x4eea70) but the leading constant is 0x6454436e instead of 0x6154436e.

int __cdecl cm_RequestSlot170Command(int*);

void __cdecl fcn_004f0900(char* a)
{
	int x[2];
	x[0] = 0x6454436e;
	x[1] = *(int*) (a + 1);
	cm_RequestSlot170Command(x);
}
