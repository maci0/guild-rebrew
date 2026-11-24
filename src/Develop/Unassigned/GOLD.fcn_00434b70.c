extern unsigned int g_5f927c;

unsigned int __cdecl d3_GetAnimSize(char*);
char __cdecl d3_ReleaseUnusedAnimations(unsigned int, unsigned int);
void __cdecl m_FreeTracked(void*);

/* ADDRESS: GOLD 0x00434b70 */
void __cdecl fcn_00434b70(char* a, char force)
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
		for (e = *(char**) 0xfc26e0; e != (char*) 0xfe7440; e = *(char**) (e + 0x160)) {
			if (*(int*) (e + 0x14c) == 0) {
				n += d3_GetAnimSize(e);
			}
		}
		size = d3_GetAnimSize(a);
		if (size + n <= g_5f927c) {
			return;
		}
		if (d3_ReleaseUnusedAnimations(g_5f927c - size, n)) {
			return;
		}
		force = 1;
	}
}
