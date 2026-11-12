
/* fcn_00407690: e=m_alloc(0x14, 0x5f1a48); *(int*)(e+0x10)=a; return e. */

void* __cdecl m_alloc(int, int);

int __cdecl fcn_00407690(int a)
{
	char* e;
	e = (char*) m_alloc(0x14, 0x5f1a48);
	*(int*) (e + 0x10) = a;
	return (int) e;
}
