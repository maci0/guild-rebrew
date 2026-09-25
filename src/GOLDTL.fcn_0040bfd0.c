// FUNCTION: GOLDTL 0x0040bfd0
// SIZE: 155

// SIZE 0x194
typedef struct {
	char pad0[9];
	char kind;
	char pada[0xf4 - 0xa];
	void* data;
	char padf8[0x194 - 0xf8];
} Slot;

extern void* g_6b5c5c;
extern Slot* g_6b5c20;
extern char* g_14d0020[];
void __cdecl fcn_00408240(void* p);
void __cdecl fcn_0041ddd0(void* p);
void __cdecl fcn_004030e0(char* e);

void __cdecl fcn_0040bfd0(void)
{
	int i;
	char** p;
	void** d;

	if (g_6b5c5c != 0) {
		fcn_00408240(g_6b5c5c);
	}
	if (g_6b5c20 != 0) {
		for (i = 0; i < 2000; i++) {
			if (g_6b5c20[i].kind == 0x2d && g_6b5c20[i].data != 0) {
				d = &g_6b5c20[i].data;
				fcn_0041ddd0(*d);
				*d = 0;
			}
		}
	}
	p = g_14d0020;
	do {
		if (*p != 0) {
			fcn_004030e0(*p);
		}
		p++;
	} while ((int) p < 0x14d0c20);
	if (g_6b5c20 != 0) {
		fcn_0041ddd0(g_6b5c20);
		g_6b5c20 = 0;
	}
}
