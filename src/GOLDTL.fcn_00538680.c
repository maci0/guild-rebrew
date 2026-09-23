// FUNCTION: GOLDTL 0x538680
// SIZE: 48

typedef void* (__stdcall* fcn_00538680_a)(int, int, char*);
typedef unsigned long (__stdcall* fcn_00538680_b)(void);

int __cdecl fcn_00538680(void** a1)
{
	void* h;

	h = (*(fcn_00538680_a*) 0x6620a8)(0, 1, (char*) 0x6a37fc);
	if (h != 0) {
		*a1 = h;
		return (*(fcn_00538680_b*) 0x6620f0)() == 0xb7;
	}
	return -1;
}
