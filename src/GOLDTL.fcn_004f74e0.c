// FUNCTION: GOLDTL 0x4f74e0
// SIZE: 153

void* __cdecl fcn_005463a0(int, int, int);
void* __cdecl fcn_005462a0(void);
void  __cdecl fcn_005da250(void*, void*);
void  __cdecl fcn_0051af00(void*, int, int);

int __cdecl fcn_004f74e0(void* a1, void* a2)
{
	void* p;

	if (*(int*) a2 != 3 && *(int*) a2 != 1) {
		return 1;
	}
	if (*(char*) ((char*) a1 + 0x166) == 0xd) {
		return 1;
	}
	p = fcn_005463a0(1, 0, 0x2c);
	while (p != 0) {
		if (*(int*) ((char*) p + 0xac) == *(int*) ((char*) a1 + 4)) {
			return 1;
		}
		p = fcn_005462a0();
	}
	if (*(int*) a2 == 3) {
		fcn_005da250(a1, a2);
		return 2;
	}
	if (*(int*) a2 == 1 && *(char*) ((char*) a1 + 2) == 6) {
		fcn_0051af00((char*) a2 + 0x14, 0x679060, 0x1d44);
	}
	return 2;
}
