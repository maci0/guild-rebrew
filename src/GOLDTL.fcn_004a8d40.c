extern int g_7f4c00;
extern int g_7f4c04;

unsigned short __cdecl fcn_0042e410(int);

// FUNCTION: GOLDTL 0x4a8d40
// SIZE: 87

int __cdecl fcn_004a8d40(int a, char* e)
{
	if (*(unsigned int*) (e + 4) % 4 == g_7f4c00 % 4 && *(unsigned int*) (e + 4) % 8 == (unsigned short) g_7f4c04 % 8)
		return fcn_0042e410(4) == 0;
	return 0;
}
