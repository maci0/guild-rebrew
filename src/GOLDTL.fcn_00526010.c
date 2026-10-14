


int __cdecl fcn_0050b7c0(int, int);
void __cdecl fcn_0051af00(void*, int, ...);
int  __cdecl fcn_00526120(void*, int);

int __cdecl fcn_00526010(void* a1, int a2, int a3)
{
	char buf[0x40];

	if (fcn_0050b7c0(*(int*) ((char*) a1 + 0x178), a3) < a2 && a2 != 0) {
		fcn_0051af00(buf, 0x75, (unsigned char) a3);
		fcn_00526120(buf, 0);
		return 0;
	}
	return 1;
}
