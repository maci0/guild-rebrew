// FUNCTION: GOLDTL 0x4c48c0
// SIZE: 36

void __cdecl fcn_004c5790(int, void*);

void __cdecl fcn_004c48c0(void)
{
	char buf[0x7c];

	if (*(unsigned*) 0x68a9cc > 0) {
		*(int*) buf = *(unsigned*) 0x68a9cc - 1;
		fcn_004c5790(0x12, buf);
	}
}
