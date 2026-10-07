// FUNCTION: GOLD 0x0055ce60
// fcn_0055ce60 — copy 0x770ae0 block into a+0x52.

void __cdecl fcn_0055ce60(char* a)
{
	char* d;
	d = a + 0x52;
	*(int*) d = *(int*) 0x770ae0;
	*(int*) (d + 4) = *(int*) 0x770ae4;
	*(int*) (d + 8) = *(int*) 0x770ae8;
	*(short*) (d + 0xc) = *(short*) 0x770aec;
}
