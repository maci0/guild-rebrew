void* __cdecl m_alloc(unsigned int size, const char* source);
void* __cdecl fcn_0045c5b0(int a0, unsigned int a1, int a2, int a3);
void __cdecl fcn_0045ce90(void* a0);

/* ADDRESS: GOLDTL 0x00459870 */
unsigned int* __cdecl fcn_00459870(char* a0, unsigned int a1, int a2, unsigned int a3, unsigned int a4, unsigned int a5, unsigned int a6, unsigned int a7)
{
	unsigned int* v2;
	int v3;
	int* v1;

	if (a0 == 0)
		return 0;
	if (a2 == 0)
		return 0;
	v2 = (unsigned int*) m_alloc(0x2c, (const char*) 0x67bcc4);
	if (v2 != 0) {
		*v2 = a4;
		v2[1] = a5;
		v2[2] = 0;
		v2[3] = 0x3f800000;
		v2[4] = 0;
		v2[5] = a7;
		v2[6] = a6;
		*(char*) ((char*) v2 + 0x28) = (char) a3;
		*(char*) ((char*) v2 + 0x29) = (char) a3;
		v2[9] = a3;
		v3 = (int) fcn_0045c5b0(a2, a3, 0, 0);
		v2[7] = v3;
		if (v3 != 0)
			fcn_0045ce90((void*) v3);
		if (a1 != 0) {
			v2[8] = *(unsigned int*) (a0 + 0x24);
		} else {
			v2[8] = 0;
			v1 = (int*) *(int*) (a0 + 0x24);
			if (v1 != 0) {
				while (*(int*) ((char*) v1 + 0x20) != 0)
					v1 = (int*) *(int*) ((char*) v1 + 0x20);
				*(int**) ((char*) v1 + 0x20) = (int*) v2;
			}
		}
		*(int**) (a0 + 0x24) = (int*) v2;
	}
	return v2;
}
