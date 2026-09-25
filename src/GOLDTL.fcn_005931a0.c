// FUNCTION: GOLDTL 0x5931a0
// SIZE: 83

void __cdecl fcn_004727a0(int, int);
void __cdecl fcn_00533f40(int, int, int, int, int, int*, int*, int*);

void __cdecl fcn_005931a0(void)
{
	int a;
	int b;
	int c;
	int s;

	if (*(int*) 0x6a9b9c != -1) {
		fcn_004727a0(*(int*) 0x6a9b9c, 5);
		s = *(int*) 0x772514;
		fcn_004727a0(*(int*) 0x6a9b9c, 6);
		fcn_00533f40(0, 0, *(int*) 0x772514, s, 0x35, &c, &b, &a);
	}
}
