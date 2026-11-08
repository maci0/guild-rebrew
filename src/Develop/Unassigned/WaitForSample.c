int __cdecl fcn_00423460(int);
void __cdecl WaitForSample(int* a0);

extern int* g_6b7ebc;
extern int* g_6b7e98;

/* ADDRESS: GOLDTL 0x004110e0 */
void __cdecl WaitForSample(int* a0)
{
	int v;

	v = *a0;
	if (g_6b7ebc != 0 && *(int*) ((char*) g_6b7ebc + 0x44) == (int) WaitForSample) {
		if (fcn_00423460(v) != 0) {
			*(int*) ((char*) g_6b7e98 + 0xc60) = (int) WaitForSample;
		}
	} else if (*(int*) ((char*) g_6b7e98 + 0xc84) == 1) {
		*(int*) ((char*) g_6b7e98 + 0xc60) = (int) WaitForSample;
	}
}
