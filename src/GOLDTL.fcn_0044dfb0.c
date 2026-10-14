void __cdecl fcn_004011f0(void* a, int* b);
void* __cdecl m_alloc(int size, char* tag);

/* ADDRESS: GOLDTL 0x0044dfb0 */
void __cdecl fcn_0044dfb0(void* a, char* s)
{
	int* n;

	n = (int*) (s + 0x14);
	fcn_004011f0(a, n);
	if (*n > 0 && *(void**) (s + 0x20) == 0) {
		*(int*) (s + 0x18) = 0;
		*(int*) (s + 0x1c) = 0;
		*(void**) (s + 0x20) = m_alloc(0xe0000, (char*) 0x67b888);
	}
}
