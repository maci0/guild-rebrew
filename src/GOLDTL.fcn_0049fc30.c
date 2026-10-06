void __cdecl fcn_004eb780(int, int*);

// FUNCTION: GOLD 0x004a01f0
// FUNCTION: GOLDTL 0x49fc30

int __cdecl fcn_0049fc30(int a, char* e)
{
	int msg[5];

	if (*e == 4) {
		msg[0] = 2;
		msg[1] = *(int*) (e + 4);
		msg[2] = *(int*) (e + 0x10);
		fcn_004eb780(a, msg);
		return 0x37;
	}
	return 0;
}
