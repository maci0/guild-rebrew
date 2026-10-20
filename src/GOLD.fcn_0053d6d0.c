int __cdecl fcn_005de7a2(void*, int, int, int);

/* ADDRESS: GOLD 0x0053d6d0 */
void __cdecl fcn_0053d6d0(char* a)
{
	char buf[0x100];
	unsigned int idx;

	idx = *(unsigned short*) (a + 8);
	fcn_005de7a2(buf, 0x6266b8, *(unsigned char*) a, 0x770bb0 + idx * 0x21c);
}
