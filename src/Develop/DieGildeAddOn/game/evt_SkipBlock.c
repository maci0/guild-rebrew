


extern char* evt_CurrentScript;

#define POS (*(char**) (evt_CurrentScript + 0x118))
#define BASE (*(char**) (evt_CurrentScript + 0x11c))
#define LEN (*(int*) (evt_CurrentScript + 0x120))

/* ADDRESS: GOLDDE 0x00420e80 */
int __cdecl evt_SkipBlock(char dir)
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
