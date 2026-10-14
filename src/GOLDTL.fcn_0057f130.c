/* ADDRESS: GOLDTL 0x0057f130 */

int __cdecl fcn_0057f130(int* msg)
{
	short* e;

	if (*msg == 0x19) {
		e = (short*) msg[1];
		if (e != 0 && *e == 0x10e) {
			(*(int**) 0x665f08)[0] = 0xb;
			(*(int**) 0x665f08)[1] = 0xb;
			(*(int**) 0x665f08)[3] = *(volatile int*) 0x6b7fac;
			return 1;
		}
	}
	return 3;
}
