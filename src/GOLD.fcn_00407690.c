// FUNCTION: GOLD 0x00407690
// fcn_00407690 — e = fcn_004223c0(0x14, 0x5f1a48); e[0x10]=a.

void* __cdecl m_AllocTracked(int, int);

int __cdecl fcn_00407690(int a)
{
	char* e;
	e = (char*) m_AllocTracked(0x14, 0x5f1a48);
	*(int*) (e + 0x10) = a;
	return (int) e;
}
