// FUNCTION: GOLD 0x0053d690
// fcn_0053d690 — buf[0x100]; fcn_005de7a2(&buf, 0x626680, a[0], 0x770bb0 + [a+8]*540).

int __cdecl fcn_005de7a2(void*, int, int, int);

void __cdecl fcn_0053d690(char* a)
{
	char buf[0x100];
	fcn_005de7a2(&buf, 0x626680, (unsigned char) a[0], 0x770bb0 + (unsigned int) *(unsigned short*) (a + 8) * 540);
}
