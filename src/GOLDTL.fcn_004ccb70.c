// FUNCTION: GOLD 0x004cbff0
// SIZE: 84
// FUNCTION: GOLDTL 0x4ccb70
// SIZE: 84

char* __cdecl fcn_00508e40(int);
int __cdecl fcn_00426cc0(int);
void __cdecl fcn_00428720(int);

int __cdecl fcn_004ccb70(char* a1, char* a2)
{
	char* p;
	char* q;
	int v;

	p = fcn_00508e40(*(int*) (a1 + 0x10));
	if (p == 0) {
		return 1;
	}
	q = *(char**) (p + 0x184);
	if (q != 0) {
		v = *(int*) (q + 0x28);
		if (v != -1) {
			fcn_00428720(fcn_00426cc0(v));
		}
	}
	if (a2 != 0) {
		a2[0] = 1;
		a2[1] = 0;
		*(int*) (a2 + 6) = 0;
	}
	return 0;
}
