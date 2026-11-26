#include <string.h>

extern char s_67da58[];

extern void* __cdecl m_alloc(int, char*);
extern void __cdecl m_FreeTracked(void*);
extern void* __cdecl fcn_00479620(char*, int);
extern void __cdecl d2_AppendShapeToBank(void*, void*);


/* Clones a packed record tree. a1 == 1 selects the copy path; the record
 * header decides whether the clone is placed before or after the base region.
 * a2 == 0 frees the source. Returns 0 for a record without a payload. */
/* ADDRESS: GOLDTL 0x00479660 */
void* __cdecl fcn_00479660(char* bank, int mode, int keepOriginal)
{
	int size = *(int*) (bank + 0x30);
	int sum = 0;
	char* n;
	char* p;
	int total;

	if (size == 0)
		return 0;
	for (total = 0; total < *(unsigned short*) (bank + 0x2a); total++) {
		sum += *(int*) (bank + ((int*) (bank + 0x45))[total] + 0x2e);
	}
	if (*(unsigned char*) (bank + 0x34) == 2 && mode == 1) {
		n = (char*) m_alloc(size - sum, s_67da58);
		memcpy(n, bank, 0x845);
		*(int*) (n + 0x30) = 0;
		*(unsigned char*) (n + 0x34) = 1;
		*(unsigned short*) (n + 0x2a) = 0;
		for (total = 0; total < *(unsigned short*) (bank + 0x2a); total++) {
			p = (char*) fcn_00479620(bank + ((int*) (bank + 0x45))[total], 1);
			d2_AppendShapeToBank(p, n);
			if (p)
				m_FreeTracked(p);
		}
		if (*(int*) (bank + 0x3e) != 0) {
			*(int*) (n + 0x3e) = *(int*) (n + 0x30);
			memcpy(n + *(int*) (n + 0x30), bank + *(int*) (bank + 0x3e),
				*(unsigned short*) (bank + 0x43) * 8);
		}
		if (keepOriginal == 0)
			m_FreeTracked(bank);
		return n;
	}
	if (*(unsigned char*) (bank + 0x34) != 0 || mode != 1)
		return bank;
	n = (char*) m_alloc(size + sum, s_67da58);
	memcpy(n, bank, 0x845);
	*(int*) (n + 0x30) = 0;
	*(unsigned char*) (n + 0x34) = 1;
	*(unsigned short*) (n + 0x2a) = 0;
	for (total = 0; total < *(unsigned short*) (bank + 0x2a); total++) {
		p = (char*) fcn_00479620(bank + ((int*) (bank + 0x45))[total], 1);
		d2_AppendShapeToBank(p, n);
		if (p)
			m_FreeTracked(p);
	}
	if (*(int*) (bank + 0x3e) != 0) {
		*(int*) (n + 0x3e) = *(int*) (n + 0x30);
		memcpy(n + *(int*) (n + 0x30), bank + *(int*) (bank + 0x3e),
			*(unsigned short*) (bank + 0x43) * 8);
	}
	if (keepOriginal == 0)
		m_FreeTracked(bank);
	return n;
}
