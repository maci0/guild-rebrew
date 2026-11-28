


// fcn_004bd9b0 — unlink a from 0x38/0x3c chain; free; return 1.

int __cdecl m_FreeTracked(int);

/* ADDRESS: GOLDDE 0x004abdd0 */
int __cdecl m_UnlinkAndFreeNode(char* a)
{
	char* p;
	char* q;
	p = *(char**) (a + 0x38);
	if (p != 0) {
		*(char**) (p + 0x3c) = *(char**) (a + 0x3c);
	}
	q = *(char**) (a + 0x3c);
	if (q != 0) {
		*(char**) (q + 0x38) = *(char**) (a + 0x38);
	}
	m_FreeTracked((int) a);
	return 1;
}

