extern char g_9a3825[];

// FUNCTION: GOLDTL 0x004f5bf0
int __cdecl fcn_004f5bf0(unsigned int key, int start)
{
	int r;
	int i;

	r = -1;
	if (start < 0 || start >= 0x200) {
		return -2;
	}
	if (key < 2) {
		return -3;
	}
	for (i = start; i < 0x200; i++) {
		if (*(unsigned int*) (g_9a3825 + i * 0x2d) == key) {
			r = i;
			break;
		}
	}
	return r;
}
