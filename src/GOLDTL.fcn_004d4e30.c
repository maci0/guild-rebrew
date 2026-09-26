extern unsigned short* g_772f24;
extern int g_68b79c;
extern char* g_aed32c;

char* __cdecl fcn_004ce680(char* o);
void __cdecl fcn_004c4510(char* q, int k);
void __cdecl fcn_004c4670(int a, int b, int c, int* d);
void __cdecl fcn_004c5360(void);
void __cdecl fcn_004cf450(char* pos, int a, int b);

// FUNCTION: GOLD 0x004d3a30
// SIZE: 136
// FUNCTION: GOLDTL 0x004d4e30
// SIZE: 136
void __cdecl fcn_004d4e30(char* e)
{
	char* o;
	char* q;

	o = *(char**) (e + 0x17c);
	if (*(int*) (((char*)g_772f24) + 4) == g_68b79c) {
		q = fcn_004ce680(o);
		if (q != 0) {
			int v = -1;

			fcn_004c4510(q, *(int*) (q + 2));
			fcn_004c4670(4, 1, q - g_aed32c + 0x20, &v);
			fcn_004c5360();
		}
	}
	fcn_004cf450(*(char**) (*(char**) (o + 0x184) + 0x34) + 0x4c, *(int*) (e + 0x180), *(int*) (e + 0x184));
}
