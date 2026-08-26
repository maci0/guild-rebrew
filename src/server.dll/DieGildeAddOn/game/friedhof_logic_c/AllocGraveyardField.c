/* AllocGraveyardField - proper C */

// FUNCTION: SERVER 0x100109d0
// SYMBOL: _AllocGraveyardField
// SIZE: 832

extern char* dword_100a8c30;
extern int g_1002575c[];
extern int g_1002576c[];
extern void* __cdecl m_AllocTracked(unsigned int size, const char* tag);
extern void __cdecl m_FreeTracked(void* ptr);
extern void* __cdecl memset(void* dest, int c, unsigned int count);

/* Allocates a graveyard field slot: verifies the field type, allocates
 * the slot plus its worker table and slot-entry table, initializes the
 * production slots for the field type, and links the slot to the field. */

int __cdecl AllocGraveyardField(unsigned char* field)
{
	unsigned char* entry;
	void* slot;
	char* p;
	char* e;
	int i;

	entry = (unsigned char*) (dword_100a8c30 + field[0] + field[0] * 588);
	if (entry[0] != 0x1d) {
		return 0;
	}
	if (entry[0x247] < 1 || entry[0x247] > 3) {
		return 0;
	}
	slot = m_AllocTracked(0x24, (const char*) 0x1002d474);
	if (!slot) {
		return 0;
	}
	memset(slot, 0, 0x24);
	*(int*) slot = *(int*) (field + 1);
	*(int*) ((char*) slot + 4) = entry[0x247];
	*(void**) ((char*) slot + 0x1c) = (char*) m_AllocTracked(g_1002575c[entry[0x247]] * 20,
	    (const char*) 0x1002d45c);
	if (!*(void**) ((char*) slot + 0x1c)) {
		goto cleanup;
	}
	memset(*(void**) ((char*) slot + 0x1c), 0, g_1002575c[entry[0x247]] * 20);
	*(void**) ((char*) slot + 0x20) = (char*) m_AllocTracked(g_1002576c[entry[0x247]] * 68,
	    (const char*) 0x1002d444);
	if (*(void**) ((char*) slot + 0x20) == 0) {
cleanup:
		if (*(void**) ((char*) slot + 0x1c)) {
			m_FreeTracked(*(void**) ((char*) slot + 0x1c));
			*(void**) ((char*) slot + 0x1c) = 0;
		}
		if (*(void**) ((char*) slot + 0x20)) {
			m_FreeTracked(*(void**) ((char*) slot + 0x20));
			*(void**) ((char*) slot + 0x20) = 0;
		}
		m_FreeTracked(slot);
		return 0;
	}
	memset(*(void**) ((char*) slot + 0x20), 0, g_1002576c[entry[0x247]] * 68);
	for (i = 0; i < g_1002576c[entry[0x247]]; i++)
		*(unsigned*) ((char*) *(void**) ((char*) slot + 0x20) + i * 0x44) = 0xFFFFFFFFu;
	*(void**) ((char*) slot + 8) = *(void**) ((char*) slot + 0x1c);
	*(char*) ((char*) slot + 0x18) = 1;
	*(char*) ((char*) slot + 0x19) = 0;
	*(char*) ((char*) slot + 0x1a) = 0;
	*(char*) ((char*) slot + 0x1b) = 0;
	p = (char*) *(void**) ((char*) slot + 0x1c);
	e = (char*) *(void**) ((char*) slot + 0x20);
	if (*(int*) ((char*) slot + 4) == 1) {
		*(void**) ((char*) slot + 0x10) = 0;
		*(void**) ((char*) slot + 0xc) = p + 0xa0;
		*(void**) ((char*) slot + 0x14) = 0;
		for (i = 0; i < 8; i++) {
			*(int*) p = 0;
			*(void**) (p + 0x10) = e;
			*(unsigned*) (p + 4) = 0xFFFFFFFFu;
			*(unsigned short*) (p + 8) = 0xFFFFu;
			e += 0x44;
			p += 0x14;
		}
		for (i = 0; i < 4; i++) {
			*(int*) p = 1;
			*(void**) (p + 0x10) = e;
			*(unsigned*) (p + 4) = 0xFFFFFFFFu;
			*(unsigned short*) (p + 8) = 0xFFFFu;
			e += 0x88;
			p += 0x14;
		}
	} else if (*(int*) ((char*) slot + 4) == 2) {
		*(void**) ((char*) slot + 0x14) = 0;
		*(void**) ((char*) slot + 0xc) = p + 0xf0;
		*(void**) ((char*) slot + 0x10) = p + 0x168;
		for (i = 0; i < 0xc; i++) {
			*(int*) p = 0;
			*(void**) (p + 0x10) = e;
			*(unsigned*) (p + 4) = 0xFFFFFFFFu;
			*(unsigned short*) (p + 8) = 0xFFFFu;
			e += 0x44;
			p += 0x14;
		}
		for (i = 0; i < 6; i++) {
			*(int*) p = 1;
			*(void**) (p + 0x10) = e;
			*(unsigned*) (p + 4) = 0xFFFFFFFFu;
			*(unsigned short*) (p + 8) = 0xFFFFu;
			e += 0x88;
			p += 0x14;
		}
		for (i = 0; i < 2; i++) {
			*(int*) p = 2;
			*(void**) (p + 0x10) = e;
			*(unsigned*) (p + 4) = 0xFFFFFFFFu;
			*(unsigned short*) (p + 8) = 0xFFFFu;
			e += 0x110;
			p += 0x14;
		}
	} else {
		*(void**) ((char*) slot + 0xc) = p + 0x140;
		*(void**) ((char*) slot + 0x10) = p + 0x1e0;
		*(void**) ((char*) slot + 0x14) = p + 0x230;
		for (i = 0; i < 0x10; i++) {
			*(int*) p = 0;
			*(void**) (p + 0x10) = e;
			*(unsigned*) (p + 4) = 0xFFFFFFFFu;
			*(unsigned short*) (p + 8) = 0xFFFFu;
			e += 0x44;
			p += 0x14;
		}
		for (i = 0; i < 8; i++) {
			*(int*) p = 1;
			*(void**) (p + 0x10) = e;
			*(unsigned*) (p + 4) = 0xFFFFFFFFu;
			*(unsigned short*) (p + 8) = 0xFFFFu;
			e += 0x88;
			p += 0x14;
		}
		for (i = 0; i < 4; i++) {
			*(int*) p = 2;
			*(void**) (p + 0x10) = e;
			*(unsigned*) (p + 4) = 0xFFFFFFFFu;
			*(unsigned short*) (p + 8) = 0xFFFFu;
			e += 0x110;
			p += 0x14;
		}
		for (i = 0; i < 2; i++) {
			*(int*) p = 3;
			*(void**) (p + 0x10) = e;
			*(unsigned*) (p + 4) = 0xFFFFFFFFu;
			*(unsigned short*) (p + 8) = 0xFFFFu;
			e += 0x220;
			p += 0x14;
		}
	}
	*(void**) (field + 0x65) = slot;
	return (int) slot;
}
