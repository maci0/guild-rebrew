/* ADDRESS: GOLD 0x0055ce60 */
// fcn_0055ce60 — copy 0x770ae0 block into a+0x52.

void __cdecl fcn_0055ce60(char* a)
{
	a += 0x52;
	*(int*) a = *(int*) 0x770ae0;
	*(int*) (a + 4) = *(int*) 0x770ae4;
	*(int*) (a + 8) = *(int*) 0x770ae8;
	*(short*) (a + 0xc) = *(short*) 0x770aec;
}
