


// SIZE 0x194
typedef struct {
	char pad0[9];
	char kind;
	char pada[0xf4 - 0xa];
	void* data;
	char padf8[0x194 - 0xf8];
} Slot;

extern void* g_6b5c5c;
extern char* g_6b5c20;
extern void* g_14d0020[];
void __cdecl fcn_00408240(void* p);
void __cdecl m_FreeTracked(void* p);
void __cdecl fcn_004030e0(char* e);

void __cdecl fcn_0040bfd0(void)
{
	int i;
	char** p;
	void** d;

	if (g_6b5c5c != 0) {
		fcn_00408240(g_6b5c5c);
	}
	if ((*(Slot**)&g_6b5c20) != 0) {
		for (i = 0; i < 2000; i++) {
			if ((*(Slot**)&g_6b5c20)[i].kind == 0x2d && (*(Slot**)&g_6b5c20)[i].data != 0) {
				d = &(*(Slot**)&g_6b5c20)[i].data;
				m_FreeTracked(*d);
				*d = 0;
			}
		}
	}
	p = ((char**)g_14d0020);
	do {
		if (*p != 0) {
			fcn_004030e0(*p);
		}
		p++;
	} while ((int) p < (int) &((char**)g_14d0020)[0x300]);
	if ((*(Slot**)&g_6b5c20) != 0) {
		m_FreeTracked((*(Slot**)&g_6b5c20));
		(*(Slot**)&g_6b5c20) = 0;
	}
}
