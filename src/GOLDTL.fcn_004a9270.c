extern int g_7f4c00;

unsigned short __cdecl fcn_0042e410(int);

// FUNCTION: GOLDTL 0x4a9270
// SIZE: 66

int __cdecl fcn_004a9270(int a, char* e)
{
	if (*(int*) (e + 0x194) >= 8 && *(unsigned int*) (e + 4) % 4 == g_7f4c00 % 4 && fcn_0042e410(4) == 0)
		return 1;
	return 0;
}
