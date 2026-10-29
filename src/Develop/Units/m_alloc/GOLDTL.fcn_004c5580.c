#include <string.h>

int __cdecl fcn_00508e40(int value);
void* __cdecl m_alloc(unsigned int size, const char* tag);
void __cdecl m_FreeTracked(void* p);
void __cdecl fcn_004c4df0(int size, void* p);
int __cdecl fcn_004c4330(void* rec);

/* ADDRESS: GOLDTL 0x004c5580 */
int __cdecl fcn_004c5580(char* rec, int size, char* src)
{
	char tmp[0x9c];
	char* p;

	tmp[0] = 0x1c;
	if (fcn_00508e40(*(int*) (rec + 8)) == 0)
		return -1;
	p = (char*) m_alloc(size + 0xf8, (const char*) 0x67d940);
	memcpy(p, rec, 0xf8);
	memcpy(p + 0xf8, src, size);
	fcn_004c4df0(size + 0xf8, p);
	m_FreeTracked(p);
	return fcn_004c4330(tmp);
}
