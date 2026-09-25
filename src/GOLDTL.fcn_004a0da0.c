void __cdecl fcn_004c5530(char* msg);

// FUNCTION: GOLDTL 0x4a0da0
// SIZE: 114
int __cdecl fcn_004a0da0(char* a1, char* x, char* y)
{
	char msg[0xf8];

	if (x[0] == 7 && y[0] == 0x17) {
		*(int*) (msg + 8) = *(int*) (x + 4);
		msg[0x36] = 0x12;
		*(int*) (msg + 0x58) = *(int*) (a1 + 4);
		msg[4] = 0x5e;
		*(int*) (msg + 0xc) = -1;
		msg[0x5c] = y[4];
		*(int*) (msg + 0x60) = *(int*) (y + 0x10);
		fcn_004c5530(msg);
		return 0x3a;
	}
	return 0;
}
