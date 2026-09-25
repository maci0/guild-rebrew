// FUNCTION: GOLDTL 0x4597f0
// SIZE: 118

void __cdecl fcn_0045bfb0(int);
void __cdecl fcn_0041ddd0(void*);

void __cdecl fcn_004597f0(char* owner, char* n)
{
	char* p;

	if (owner == 0 || n == 0) {
		return;
	}
	p = *(char**) (owner + 0x24);
	if (p == n) {
		*(char**) (owner + 0x24) = *(char**) (n + 0x20);
	} else {
		while (p != 0 && *(char**) (p + 0x20) != n) {
			p = *(char**) (p + 0x20);
		}
		if (p != 0 && *(char**) (p + 0x20) == n) {
			*(char**) (p + 0x20) = *(char**) (n + 0x20);
		}
	}
	fcn_0045bfb0(*(int*) (n + 0x1c));
	fcn_0041ddd0(n);
}
