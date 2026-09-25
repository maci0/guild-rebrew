// FUNCTION: GOLDTL 0x004263b0
// SIZE: 224

extern char* g_6b7e98;

#define POS (*(char**) (g_6b7e98 + 0x118))
#define BASE (*(char**) (g_6b7e98 + 0x11c))
#define LEN (*(int*) (g_6b7e98 + 0x120))

int __cdecl fcn_004263b0(char dir)
{
	int depth;

	depth = 0;
	if (dir == 1) {
		while (POS < BASE + LEN) {
			if (*POS == '{') {
				depth++;
			} else if (*POS == '}') {
				depth--;
				if (depth <= 0) {
					POS++;
					return 1;
				}
			}
			POS++;
		}
	} else if (dir == 2) {
		while (POS >= BASE) {
			if (*POS == '{') {
				depth--;
				if (depth <= 0) {
					return 1;
				}
				depth--;
			} else if (*POS == '}') {
				depth++;
			}
			POS--;
		}
	}
	return 0;
}
