/* ADDRESS: GOLDTL 0x004127a0 */
void __cdecl fcn_004127a0(int save)
{
	int a;
	int b;
	int c;
	int d;

	if (save == 0) {
		a = *(int*) 0x6772bc;
		b = *(int*) 0x6772c0;
		c = *(int*) 0x6b5c80;
		*(int*) 0x6b5c64 = a;
		*(int*) 0x6b5c6c = b;
		*(int*) 0x6b5c70 = *(int*) 0x6b5c84;
		*(int*) 0x6772bc = 0x7d00;
		*(int*) 0x6772c0 = 0x7d00;
		*(int*) 0x6b5c74 = c;
		*(int*) 0x6b5c84 = (int) 0xffff8300;
		*(int*) 0x6b5c80 = (int) 0xffff8300;
	} else {
		c = *(int*) 0x6b5c74;
		a = *(int*) 0x6b5c64;
		b = *(int*) 0x6b5c6c;
		*(int*) 0x6772bc = a;
		d = *(int*) 0x6b5c70;
		*(int*) 0x6772c0 = b;
		*(int*) 0x6b5c84 = d;
		*(int*) 0x6b5c80 = c;
	}
}
