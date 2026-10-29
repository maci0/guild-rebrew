#include <string.h>

extern char s_67da58[];

extern void* __cdecl m_alloc(int, char*);
extern void __cdecl m_FreeTracked(void*);
extern void* __cdecl fcn_00479620(char*, int);
extern void __cdecl fcn_004798c0(void*, void*);


/* Clones a packed record tree. a1 == 1 selects the copy path; the record
 * header decides whether the clone is placed before or after the base region.
 * a2 == 0 frees the source. Returns 0 for a record without a payload. */
/* ADDRESS: GOLDTL 0x00479660 */
void* __cdecl fcn_00479660(char* a0, int a1, int a2)
{
	int size = *(int*) (a0 + 0x30);
	int sum = 0;
	char* n;
	char* p;
	int* tbl;
	int total;

	if (size == 0)
		return 0;
	total = *(unsigned short*) (a0 + 0x2a);
	if (total > 0) {
		tbl = (int*) (a0 + 0x45);
		do {
			sum += *(int*) (a0 + *tbl + 0x2e);
			tbl++;
		} while (--total);
	}
	if (*(unsigned char*) (a0 + 0x34) == 2 && a1 == 1) {
		n = (char*) m_alloc(size - sum, s_67da58);
		memcpy(n, a0, 0x845);
		*(int*) (n + 0x30) = 0;
		*(unsigned char*) (n + 0x34) = 1;
		*(unsigned short*) (n + 0x2a) = 0;
		if (*(unsigned short*) (a0 + 0x2a) > 0) {
			total = 0;
			tbl = (int*) (a0 + 0x45);
			do {
				p = (char*) fcn_00479620(a0 + *tbl, 1);
				fcn_004798c0(p, n);
				if (p)
					m_FreeTracked(p);
				total++;
				tbl++;
			} while (total < *(unsigned short*) (a0 + 0x2a));
		}
		if (*(int*) (a0 + 0x3e) != 0) {
			*(int*) (n + 0x3e) = *(int*) (n + 0x30);
			memcpy(n + *(int*) (n + 0x30), a0 + *(int*) (a0 + 0x3e),
				*(unsigned short*) (a0 + 0x43) * 8);
		}
		if (a2 == 0)
			m_FreeTracked(a0);
		return n;
	}
	if (*(unsigned char*) (a0 + 0x34) != 0 || a1 != 1)
		return a0;
	n = (char*) m_alloc(size + sum, s_67da58);
	memcpy(n, a0, 0x845);
	*(int*) (n + 0x30) = 0;
	*(unsigned char*) (n + 0x34) = 1;
	*(unsigned short*) (n + 0x2a) = 0;
	if (*(unsigned short*) (a0 + 0x2a) > 0) {
		total = 0;
		tbl = (int*) (a0 + 0x45);
		do {
			p = (char*) fcn_00479620(a0 + *tbl, 1);
			fcn_004798c0(p, n);
			if (p)
				m_FreeTracked(p);
			total++;
			tbl++;
		} while (total < *(unsigned short*) (a0 + 0x2a));
	}
	if (*(int*) (a0 + 0x3e) != 0) {
		*(int*) (n + 0x3e) = *(int*) (n + 0x30);
		memcpy(n + *(int*) (n + 0x30), a0 + *(int*) (a0 + 0x3e),
			*(unsigned short*) (a0 + 0x43) * 8);
	}
	if (a2 == 0)
		m_FreeTracked(a0);
	return n;
}
