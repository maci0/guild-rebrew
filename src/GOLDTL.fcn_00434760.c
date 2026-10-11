extern char* g_1042320;
extern char g_1052a40[];
extern unsigned int g_67a0d8;

unsigned int __cdecl fcn_004346f0(char*);
char __cdecl fcn_004348f0(unsigned int, unsigned int);
void __cdecl m_FreeTracked(void*);

// FUNCTION: GOLD 0x00434b70
// FUNCTION: GOLDTL 0x434760

/* Drops a reference to an animation; an unreferenced one stays cached
 * while the cache has room, otherwise it is unlinked and freed. */
void __cdecl fcn_00434760(char* a, char force)
{
	char* e;
	unsigned int n;
	unsigned int size;

	while (--*(int*) (a + 0x14c) <= 0) {
		n = 0;
		if (force) {
			*(char**) (*(char**) (a + 0x160) + 0x164) = *(char**) (a + 0x164);
			*(char**) (*(char**) (a + 0x164) + 0x160) = *(char**) (a + 0x160);
			for (; (int) n < *(int*) (a + 0x148); n++) {
				if (*(void**) (*(char**) (a + 0x15c) + n * 0xc0 + 0xbc) != 0) {
					m_FreeTracked(*(void**) (*(char**) (a + 0x15c) + n * 0xc0 + 0xbc));
					*(void**) (*(char**) (a + 0x15c) + n * 0xc0 + 0xbc) = 0;
				}
				if (*(void**) (*(char**) (a + 0x15c) + n * 0xc0 + 0xb4) != 0) {
					m_FreeTracked(*(void**) (*(char**) (a + 0x15c) + n * 0xc0 + 0xb4));
					*(void**) (*(char**) (a + 0x15c) + n * 0xc0 + 0xb4) = 0;
				}
				if (*(void**) (*(char**) (a + 0x15c) + n * 0xc0 + 0xb8) != 0) {
					m_FreeTracked(*(void**) (*(char**) (a + 0x15c) + n * 0xc0 + 0xb8));
					*(void**) (*(char**) (a + 0x15c) + n * 0xc0 + 0xb8) = 0;
				}
			}
			m_FreeTracked(*(void**) (a + 0x15c));
			*(void**) (a + 0x15c) = 0;
			m_FreeTracked(a);
			return;
		}
		*(int*) (a + 0x14c) = 0;
		for (e = *(char**) ((char*)&g_1042320); e != g_1052a40; e = *(char**) (e + 0x160)) {
			if (*(int*) (e + 0x14c) == 0) {
				n += fcn_004346f0(e);
			}
		}
		size = fcn_004346f0(a);
		if (size + n <= g_67a0d8) {
			return;
		}
		if (fcn_004348f0(g_67a0d8 - size, n)) {
			return;
		}
		force = 1;
	}
}
