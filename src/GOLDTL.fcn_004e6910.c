// FUNCTION: GOLDTL 0x4e6910
// SIZE: 193

extern char g_7f4ca4[];
extern char* g_aed32c;

int* __cdecl fcn_004e68d0(void);
int __cdecl fcn_004e6200(int, int*);
void __cdecl fcn_004e5a00(int*);
void __cdecl fcn_004e6b10(int);
void __cdecl fcn_004c4510(char*, int);
int __cdecl fcn_004c4700(unsigned char, unsigned char, short, void*);
void __cdecl fcn_004c53a0(void);

char __cdecl fcn_004e6910(int idx)
{
	char ok;
	int* p;
	int saved;

	ok = 0;
	saved = *(int*) (g_7f4ca4 + idx * 0x21c + 0x208);
	p = fcn_004e68d0();
	while (p != 0) {
		if (fcn_004e6200(*(int*) (g_7f4ca4 + idx * 0x21c), p) != 0) {
			*(int*) (g_7f4ca4 + idx * 0x21c + 0x208) = *p;
			fcn_004e5a00(p);
			*(int*) (g_7f4ca4 + idx * 0x21c + 0x208) = -1;
			ok = 1;
		}
		fcn_004e6b10(*p);
		p = fcn_004e68d0();
	}
	fcn_004c4510(g_7f4ca4 + idx * 0x21c - 4, *(int*) (g_7f4ca4 + idx * 0x21c));
	fcn_004c4700(4, 1, (short) (g_7f4ca4 + idx * 0x21c + 0x208 - g_aed32c), &saved);
	fcn_004c53a0();
	return ok;
}
