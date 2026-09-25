// FUNCTION: GOLDTL 0x00422910
// SIZE: 160

extern int g_6b7d70;
extern int g_6b7d74;
char* __cdecl fcn_004227c0(void);
void __cdecl fcn_0041ddd0(void* p);

int __cdecl fcn_00422910(int need)
{
	char* s;

	while (g_6b7d70 - g_6b7d74 < need) {
		s = fcn_004227c0();
		if (s != 0) {
			if (*(char**) (s + 0x38) == 0) {
				return -1;
			}
			if (s[0x36] == 1) {
				g_6b7d74 += -12 - *(int*) (*(char**) (s + 0x38) + 4);
			} else {
				g_6b7d74 += -12 - *(int*) (*(char**) (s + 0x38) + 8);
			}
			fcn_0041ddd0(*(char**) (s + 0x38));
			*(char**) (s + 0x38) = 0;
		} else if (g_6b7d70 - g_6b7d74 < need) {
			return -1;
		}
	}
	return 0;
}
