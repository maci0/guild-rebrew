// FUNCTION: GOLDTL 0x47b620
// SIZE: 32

int __cdecl fcn_0047b620(char* p, int i)
{
	if (i >= *(unsigned short*) (p + 4)) {
		return 0;
	}
	return *(int*) (*(int*) (p + 0x18) + i * 4);
}
