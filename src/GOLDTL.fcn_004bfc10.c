// FUNCTION: GOLDTL 0x4bfc10
// SIZE: 33

void __cdecl fcn_004bfbc0(void*);

void __cdecl fcn_004bfc10(void)
{
	int a;

	for (a = 0x10058a0; a < 0x10058e0; a += 8) {
		if (*(int*) a != -1) {
			fcn_004bfbc0((void*) a);
		}
	}
}
