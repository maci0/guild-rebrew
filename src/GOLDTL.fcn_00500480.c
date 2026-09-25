// FUNCTION: GOLDTL 0x00500480
// SIZE: 256

extern int g_773d64;
extern char* g_90e094;
extern char* g_868050;

char* __cdecl sim_StartEntityQueryByType(char* e);

char* __cdecl fcn_00500480(char* obj, int* id, int* sub)
{
	char* q;
	int k;
	int n;
	char* d;

	n = 255;
	if (*(char**) (obj + 0x170) != 0) {
		q = sim_StartEntityQueryByType(*(char**) (obj + 0x170));
		if (q != 0) {
			*sub = *(int*) (q + 2);
		} else {
			*sub = -1;
		}
		*id = *(int*) (*(char**) (obj + 0x170) + 1);
		return *(char**) (obj + 0x170);
	}
	k = g_773d64;
	do {
		if (g_90e094[k * 169] != 0) {
			d = g_868050 + (unsigned char) g_90e094[k * 169] * 589;
			if (*d == 3 || *d == 0x16 || *d == 0xf) {
				g_773d64 = k + 1;
				*sub = -1;
				*id = *(int*) (g_90e094 + k * 169 + 1);
				return g_90e094 + k * 169;
			}
		}
		k = (k + 1) % 256;
	} while (--n != 0);
	return 0;
}
