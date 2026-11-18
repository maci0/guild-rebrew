


extern int g_6b7d70;
extern int MemUsed;
char* __cdecl fcn_004227c0(void);
void __cdecl m_FreeTracked(void* p);

int __cdecl fcn_00422910(int need)
{
	char* s;

	while (g_6b7d70 - MemUsed < need) {
		s = fcn_004227c0();
		if (s != 0) {
			if (*(char**) (s + 0x38) == 0) {
				return -1;
			}
			if (s[0x36] == 1) {
				MemUsed += -12 - *(int*) (*(char**) (s + 0x38) + 4);
			} else {
				MemUsed += -12 - *(int*) (*(char**) (s + 0x38) + 8);
			}
			m_FreeTracked(*(char**) (s + 0x38));
			*(char**) (s + 0x38) = 0;
		} else if (g_6b7d70 - MemUsed < need) {
			return -1;
		}
	}
	return 0;
}
