// FUNCTION: GOLDTL 0x004f5740
// SIZE: 47

extern char g_9a3825[];

int __cdecl fcn_004f5740(int key, int* out)
{
	int n;
	int i;
	int p;

	n = 0;
	i = 0;
	for (p = (int) g_9a3825; p < (int) (g_9a3825 + 0x5a00); p += 0x2d) {
		if (n >= 0x20) {
			break;
		}
		if (*(int*) p == key) {
			out[n] = i;
			n++;
		}
		i++;
	}
	return n;
}
