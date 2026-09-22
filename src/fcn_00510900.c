// FUNCTION: GOLDTL 0x510900
// SIZE: 37

char __cdecl fcn_00510900(void)
{
	int i;

	for (i = 0; i < 0xb7; i++) {
		((int*) 0x7f3b40)[i] = -1;
	}
	for (i = 0; i < 17; i++) {
		((short*) 0x7f3b00)[i] = -1;
	}
	return 0;
}
