// FUNCTION: GOLDTL 0x4c4900
// SIZE: 50

int __cdecl fcn_004c5790(int, void*);

void __cdecl fcn_0053d690(void)
{
	char buf[0x7c];
	*(int*) (buf + 0x10) = *(int*) (0x7f4ca4 + *(unsigned short*) 0x774970 * 2160);
	fcn_004c5790(0x13, &buf);
}
