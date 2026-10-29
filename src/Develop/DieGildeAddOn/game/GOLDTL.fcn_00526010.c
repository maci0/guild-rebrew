


int __cdecl gm_QueryEntitySum(int, int);
void __cdecl fcn_0051af00(void*, int, ...);
int  __cdecl fcn_00526120(void*, int);

int __cdecl fcn_00526010(void* a1, int a2, int a3)
{
	char buf[0x40];

	if (gm_QueryEntitySum(*(int*) ((char*) a1 + 0x178), a3) < a2 && a2 != 0) {
		fcn_0051af00(buf, 0x75, (unsigned char) a3);
		fcn_00526120(buf, 0);
		return 0;
	}
	return 1;
}
