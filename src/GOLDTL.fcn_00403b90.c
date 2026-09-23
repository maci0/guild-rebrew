// FUNCTION: GOLD 0x00403390
// SIZE: 48
// FUNCTION: GOLDTL 0x403b90
// SIZE: 48

void* __cdecl fcn_00403200(void);
int __cdecl fcn_00403880(void*, int, int);
void __cdecl fcn_004030e0(void*);

void* __cdecl fcn_00403b90(int a1, int a2)
{
	void* p;

	p = fcn_00403200();
	if (fcn_00403880(p, a1, a2) == 0) {
		fcn_004030e0(p);
		return 0;
	}
	return p;
}
