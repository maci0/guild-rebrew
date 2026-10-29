#include <string.h>

// SIZE 0x30
struct sym_429d30 {
	char pad0[0x2c];
	void* data;
};

void __cdecl m_FreeTracked(void*);


/* Frees a script with its symbol data, child scripts and buffers. */
/* ADDRESS: GOLDTL 0x00429d30 */
int __cdecl fcn_00429d30(char* s)
{
	int i;
	char** child;

	if (s == 0) {
		return 0;
	}
	if (*(struct sym_429d30**) (s + 0x108) != 0) {
		for (i = 0; i < *(int*) (s + 0x114); i++) {
			if ((*(struct sym_429d30**) (s + 0x108))[i].data != 0) {
				m_FreeTracked((*(struct sym_429d30**) (s + 0x108))[i].data);
				(*(struct sym_429d30**) (s + 0x108))[i].data = 0;
				(*(struct sym_429d30**) (s + 0x108))[i].data = 0;
			}
		}
	}
	child = (char**) (s + 0xc3c);
	for (i = 8; i != 0; i--) {
		if (*child != 0) {
			fcn_00429d30(*child);
			*child = 0;
		}
		child++;
	}
	if (*(void**) (s + 0x108) != 0) {
		m_FreeTracked(*(void**) (s + 0x108));
		*(void**) (s + 0x108) = 0;
	}
	if (*(void**) (s + 0x10c) != 0) {
		m_FreeTracked(*(void**) (s + 0x10c));
		*(void**) (s + 0x10c) = 0;
	}
	if (*(void**) (s + 0x11c) != 0) {
		m_FreeTracked(*(void**) (s + 0x11c));
		*(void**) (s + 0x11c) = 0;
	}
	if (*(void**) (s + 0xc30) != 0) {
		m_FreeTracked(*(void**) (s + 0xc30));
		*(void**) (s + 0xc30) = 0;
	}
	if (*(void**) (s + 0xc34) != 0) {
		m_FreeTracked(*(void**) (s + 0xc34));
		*(void**) (s + 0xc34) = 0;
	}
	memset(s, 0, 0xc98);
	*(int*) (s + 0x100) = -1;
	return 1;
}
