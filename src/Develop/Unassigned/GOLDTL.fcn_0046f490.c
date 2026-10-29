

void __cdecl fcn_0046f280(int);

void __cdecl fcn_0046f490(void)
{
	int i;
	int a;

	i = 0;
	for (a = 0x10161d0; a < 0x102ce50; a += 0x3cc, i++) {
		if (*(int*) a != 0) {
			fcn_0046f280(i);
		}
	}
}
