#include "Develop/Units/m_alloc/m_alloc.h"

/* Frees the light node with the given id from the object's list at
 * +0x1e8 -> +0x198 (next at +8, id at +4); id 0 frees the whole list. */
/* ADDRESS: GOLD 0x00452e30 */
char __cdecl fcn_00452e30(char* obj, int id)
{
	char* n;
	char* next;

	if (obj == 0 || *(char**) (obj + 0x1e8) == 0) {
		return 1;
	}
	if (id == 0) {
		n = *(char**) (*(char**) (obj + 0x1e8) + 0x198);
		while (n != 0) {
			next = *(char**) (n + 8);
			m_FreeTracked(n);
			n = next;
		}
		*(char**) (*(char**) (obj + 0x1e8) + 0x198) = 0;
		return 1;
	}
	n = *(char**) (*(char**) (obj + 0x1e8) + 0x198);
	if (n == 0) {
		return 1;
	}
	if (*(int*) (n + 4) == id) {
		*(char**) (*(char**) (obj + 0x1e8) + 0x198) = *(char**) (n + 8);
		m_FreeTracked(n);
		return 1;
	}
	do {
		next = *(char**) (n + 8);
		if (next != 0 && *(int*) (next + 4) == id) {
			*(char**) (n + 8) = *(char**) (next + 8);
			m_FreeTracked(next);
			return 1;
		}
		n = next;
	} while (next != 0);
	return 1;
}
