

char* __cdecl fcn_005463a0(int, int, int, ...);
char* __cdecl fcn_005462a0(void);

int __cdecl fcn_0055c1a0(unsigned short* e, char* b)
{
	char* r;

	for (r = fcn_005463a0(2, 2, *e, 0, 0x18); r != 0; r = fcn_005462a0()) {
		if (*(int*) (b + 4) == *(int*) (r + 0xc4)) {
			return 0;
		}
	}
	return 1;
}
