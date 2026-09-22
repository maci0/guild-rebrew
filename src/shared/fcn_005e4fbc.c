// FUNCTION: GOLD 0x005e4fbc
// SIZE: 43
// fcn_005e4fbc — if([a+0xc]&0x83 && &8){ fcn_005dec24(a[8]); a[0xc]&=~0xfbf7; a[0]=0; a[4]=0; a[8]=0; }.

int __cdecl fcn_005dec24(int);

void __cdecl fcn_005e4fbc(char* a)
{
	int fl;
	fl = *(int*) (a + 0xc);
	if ((fl & 0x83) == 0 || (fl & 8) == 0) {
		return;
	}
	fcn_005dec24(*(int*) (a + 8));
	*(short*) (a + 0xc) &= 0xfbf7;
	*(int*) a = 0;
	*(int*) (a + 4) = 0;
	*(int*) (a + 8) = 0;
}
