// FUNCTION: GOLDTL 0x40c430

int __cdecl rand(void);

int __cdecl fcn_0040c430(int* p)
{
	if (*p == 0) {
		return 0;
	}
	return rand() % *p;
}
