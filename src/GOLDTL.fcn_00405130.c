// FUNCTION: GOLDTL 0x405130
// SIZE: 78

void __cdecl fcn_0041ddd0(int);
void __cdecl fcn_004050c0(void*);

int __cdecl fcn_00405130(void* a1)
{
	void* e;

	e = *(void**) ((char*) a1 + 0x128);
	while (e != 0) {
		if (*(char*) ((char*) e + 9) == 0x2d && *(int*) ((char*) e + 0xf4) != 0) {
			fcn_0041ddd0(*(int*) ((char*) e + 0xf4));
			*(int*) ((char*) e + 0xf4) = 0;
		}
		fcn_004050c0(e);
		e = *(void**) ((char*) a1 + 0x128);
	}
	return 1;
}
