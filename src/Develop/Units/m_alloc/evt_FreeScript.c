#include <string.h>

// SIZE 0x30
struct EVT_SYMBOL {
	char pad0[0x2c];
	void* data;
};

void __cdecl m_FreeTracked(void*);


/* Frees a script with its symbol data, child scripts and buffers. */
/* ADDRESS: GOLDTL 0x00429d30 */
/* ADDRESS: GOLDDE 0x00424700 */
int __cdecl evt_FreeScript(char* script)
{
	int i;
	char** child;

	if (script == 0) {
		return 0;
	}
	if (*(struct EVT_SYMBOL**) (script + 0x108) != 0) {
		for (i = 0; i < *(int*) (script + 0x114); i++) {
			if ((*(struct EVT_SYMBOL**) (script + 0x108))[i].data != 0) {
				m_FreeTracked((*(struct EVT_SYMBOL**) (script + 0x108))[i].data);
				(*(struct EVT_SYMBOL**) (script + 0x108))[i].data = 0;
				(*(struct EVT_SYMBOL**) (script + 0x108))[i].data = 0;
			}
		}
	}
	child = (char**) (script + 0xc3c);
	for (i = 8; i != 0; i--) {
		if (*child != 0) {
			evt_FreeScript(*child);
			*child = 0;
		}
		child++;
	}
	if (*(void**) (script + 0x108) != 0) {
		m_FreeTracked(*(void**) (script + 0x108));
		*(void**) (script + 0x108) = 0;
	}
	if (*(void**) (script + 0x10c) != 0) {
		m_FreeTracked(*(void**) (script + 0x10c));
		*(void**) (script + 0x10c) = 0;
	}
	if (*(void**) (script + 0x11c) != 0) {
		m_FreeTracked(*(void**) (script + 0x11c));
		*(void**) (script + 0x11c) = 0;
	}
	if (*(void**) (script + 0xc30) != 0) {
		m_FreeTracked(*(void**) (script + 0xc30));
		*(void**) (script + 0xc30) = 0;
	}
	if (*(void**) (script + 0xc34) != 0) {
		m_FreeTracked(*(void**) (script + 0xc34));
		*(void**) (script + 0xc34) = 0;
	}
	memset(script, 0, 0xc98);
	*(int*) (script + 0x100) = -1;
	return 1;
}
