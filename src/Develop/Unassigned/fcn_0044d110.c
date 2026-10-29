int __cdecl fcn_0064f026(int a, char* b);
int __cdecl fcn_0064eeec(int a);

/* ADDRESS: GOLDTL 0x0044d110 */
void __cdecl fcn_0044d110(int unused, char* p)
{
	unsigned char v;

	(void) unused;
	v = (unsigned char) fcn_0064eeec(fcn_0064f026(0, (char*) 0x662d18));
	((char*) *(int*) (p + 0x10))[*(int*) (p + 8) * 0xe0 + 0xc1] = (char) v;
}
