#include <string.h>

extern void* __cdecl m_alloc(unsigned int size, const char* file_and_line);

#pragma optimize("y", off)
/* ADDRESS: GOLDTL 0x00418bc0 */
int __cdecl fcn_00418bc0(int a0)
{
	int result;
	unsigned int n;
	char* p;

	result = 0;
	if (*(int*) 0x6b5d08 != 0)
		return -1;
	if (a0 != 0)
		*(int*) 0x677680 = a0;
	n = *(unsigned int*) 0x677680 * 0x54;
	p = (char*) m_alloc(n, (const char*) 0x677750);
	*(int*) 0x6b5d08 = (int) p;
	if (p == 0)
		return -1;
	memset(p, 0, *(unsigned int*) 0x677680 * 0x54);
	return result;
}
#pragma optimize("", on)
