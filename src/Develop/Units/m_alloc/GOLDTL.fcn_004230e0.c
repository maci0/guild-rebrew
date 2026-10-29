extern int g_6b7d7c;
extern int g_6b7d74;
extern char* g_6b7d78;
extern char g_14cbae0[];
extern char g_678f70[]; /* Unloading Samplebank %s ... MemUsed before unloading %d bytes. */
extern char g_678f28[]; /* Finished unloading Samplebank %s ... MemUsed after unloading %d bytes. */

char* __cdecl fcn_00422760(int, int*);
void __cdecl fcn_004237f0(char*, int);
void __cdecl m_FreeTracked(void*);
int __cdecl fcn_0064d41a(char*, char*, ...);

/* ADDRESS: GOLDTL 0x004230e0 */
int __cdecl fcn_004230e0(char* a0)
{
	int r;
	char* bank;
	char* prev;
	char* name;
	char* s;
	int n;
	int i;
	int left;

	r = 0;
	if (g_6b7d7c == 0) {
		return 1;
	}
	if (g_6b7d74 == 0 || a0 == 0) {
		return -1;
	}
	prev = 0;
	bank = g_6b7d78;
	while (bank != 0 && bank != a0) {
		prev = bank;
		bank = *(char**) (bank + 0x13c);
	}
	if (bank == 0) {
		return r;
	}
	left = *(int*) (bank + 0x140) - 1;
	*(int*) (bank + 0x140) = left;
	if (left > 0) {
		return r;
	}
	if (prev != 0) {
		*(char**) (prev + 0x13c) = *(char**) (bank + 0x13c);
	} else {
		g_6b7d78 = *(char**) (bank + 0x13c);
	}
	name = a0 + 0x32;
	fcn_0064d41a(g_14cbae0, g_678f70, name, g_6b7d74);
	i = 0;
	if (*(int*) (bank + 0x134) > 0) {
		do {
			if (*(int*) (*(char**) (bank + 0x138) + i * 0x40 + 0x38) != 0) {
				n = 0;
				s = fcn_00422760(*(char**) (bank + 0x138) + i * 0x40, &n);
				while (s != 0) {
					fcn_004237f0(s, 0);
					*(int*) (s + 4) = 0;
					n++;
					s = fcn_00422760(*(char**) (bank + 0x138) + i * 0x40, &n);
				}
				if (*(char*) (*(char**) (bank + 0x138) + i * 0x40 + 0x36) == 1) {
					g_6b7d74 += -12 - *(int*) (*(char**) (*(char**) (bank + 0x138) + i * 0x40 + 0x38) + 4);
				} else {
					g_6b7d74 += -12 - *(int*) (*(char**) (*(char**) (bank + 0x138) + i * 0x40 + 0x38) + 8);
				}
				m_FreeTracked(*(char**) (*(char**) (bank + 0x138) + i * 0x40 + 0x38));
				*(char**) (*(char**) (bank + 0x138) + i * 0x40 + 0x38) = 0;
				*(char**) (*(char**) (bank + 0x138) + i * 0x40 + 0x38) = 0;
			}
			i++;
		} while (i < *(int*) (bank + 0x134));
	}
	g_6b7d74 += -0x144 - *(int*) (bank + 0x134) * 0x40;
	fcn_0064d41a(g_14cbae0, g_678f28, name, g_6b7d74);
	m_FreeTracked(bank);
	return r;
}
