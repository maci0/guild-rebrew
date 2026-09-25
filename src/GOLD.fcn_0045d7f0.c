// FUNCTION: GOLD 0x45d7f0
// SIZE: 124

/* GOLD twin of GOLDTL fcn_004597f0: the list head is owner+0xac0 (GOLDTL 0x24)
 * and the next link n+0x28 (GOLDTL 0x20). */

void __cdecl fcn_0045fbb0(int);
void __cdecl fcn_0041ddd0(void*);

void __cdecl fcn_0045d7f0(char* owner, char* n)
{
	char* p;

	if (owner == 0 || n == 0) {
		return;
	}
	p = *(char**) (owner + 0xac0);
	if (p == n) {
		*(char**) (owner + 0xac0) = *(char**) (n + 0x28);
	} else {
		while (p != 0 && *(char**) (p + 0x28) != n) {
			p = *(char**) (p + 0x28);
		}
		if (p != 0 && *(char**) (p + 0x28) == n) {
			*(char**) (p + 0x28) = *(char**) (n + 0x28);
		}
	}
	fcn_0045fbb0(*(int*) (n + 0x1c));
	fcn_0041ddd0(n);
}
