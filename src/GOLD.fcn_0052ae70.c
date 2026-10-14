/* ADDRESS: GOLD 0x0052ae70 */
// fcn_0052ae70 — [0x7662c0]=0; [0x6f2304]=0; zero bytes 0x770d08..0x7d6108 (0x21c); [0x6f2334]=0.

void __cdecl fcn_0052ae70(void)
{
	int p;
	*(int*) 0x7662c0 = 0;
	*(int*) 0x6f2304 = 0;
	for (p = 0x770d08; p < 0x7d6108; p += 0x21c) {
		*(char*) p = 0;
	}
	*(int*) 0x6f2334 = 0;
}
