// FUNCTION: GOLD 0x00502e30
// FUNCTION: GOLDTL 0x00505c80

extern unsigned char* g_868050;

void* __cdecl fcn_00502cd0(int list, int a, int b, int c);
void* __cdecl fcn_00502850(void);
void __cdecl fcn_005058b0(unsigned char* e, void* q, int k);

void __cdecl fcn_00505c80(unsigned char* e)
{
	void* list[32];
	void* q;
	int n;
	int i;

	n = 0;
	if (g_868050[e[0] * 0x24d] == 2) {
		q = fcn_00502cd0(*(int*) (e + 0x5d), 1, 4, 2);
		while (q != 0) {
			list[n++] = q;
			q = fcn_00502850();
		}
		for (i = 0; i < n; i++) {
			fcn_005058b0(e, list[i], *(unsigned short*) (e + 0x27));
		}
	}
}
