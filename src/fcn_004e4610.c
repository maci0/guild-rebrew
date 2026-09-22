// FUNCTION: GOLDTL 0x4e4610
// SIZE: 36

int __cdecl fcn_00426cc0(int);
void __cdecl fcn_00428720(void*);

void __cdecl fcn_004e4610(int a1)
{
	void* p;

	if (*(int*) 0x772f3c != 0) {
		return;
	}
	p = (void*) fcn_00426cc0(a1);
	if (p != 0) {
		fcn_00428720(p);
	}
}
