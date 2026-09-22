// FUNCTION: GOLDTL 0x4c4890
// SIZE: 37

void __cdecl fcn_004c5790(int, void*);

void __cdecl fcn_004c4890(void)
{
	char buf[0x7c];

	if (*(unsigned*) 0x68a9cc < 4) {
		*(int*) buf = *(unsigned*) 0x68a9cc + 1;
		fcn_004c5790(0x12, buf);
	}
}
