// FUNCTION: GOLDTL 0x4cc450
// SIZE: 53

int __cdecl fcn_004e8360(void*);

int __cdecl fcn_004cb910(char* a, char* b)
{
	int r;
	r = fcn_004e8360(a + 0x10);
	if (b != 0) {
		b[1] = 0;
		b[0] = (char) ((r == 0) + 1);
		*(int*) (b + 6) = 0;
	}
	return r == 0;
}
