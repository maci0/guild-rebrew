// FUNCTION: GOLDTL 0x4e99c0
// SIZE: 31

void __cdecl fcn_004e8b40(int, void*);

int __cdecl fcn_004e99c0(int a1)
{
	char buf[0x18];

	fcn_004e8b40(a1, buf);
	return *(int*) (buf + 8) & 0xff;
}
