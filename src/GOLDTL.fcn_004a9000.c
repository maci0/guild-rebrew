int __cdecl fcn_00507b00(int);
unsigned short __cdecl fcn_0042e410(int);

// FUNCTION: GOLDTL 0x4a9000
// SIZE: 64

int __cdecl fcn_004a9000(int a, char* e)
{
	if (fcn_00507b00(*(unsigned char*) (e + 0x164)) == 7 && fcn_0042e410(3) != 0)
		return 1;
	return fcn_0042e410(4) == 0;
}
