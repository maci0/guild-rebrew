

void __cdecl d3_ReleaseTexture(int);
void __cdecl m_FreeTracked(void*);

void __cdecl fcn_004597f0(char* owner, char* n)
{
	char* p;

	if (owner == 0 || n == 0) {
		return;
	}
	p = *(char**) (owner + 0x24);
	if (p == n) {
		*(char**) (owner + 0x24) = *(char**) (n + 0x20);
	} else {
		while (p != 0 && *(char**) (p + 0x20) != n) {
			p = *(char**) (p + 0x20);
		}
		if (p != 0 && *(char**) (p + 0x20) == n) {
			*(char**) (p + 0x20) = *(char**) (n + 0x20);
		}
	}
	d3_ReleaseTexture(*(int*) (n + 0x1c));
	m_FreeTracked(n);
}
