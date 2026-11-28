


extern char g_9a3825[];

/* ADDRESS: GOLDDE 0x004e17e0 */
int __cdecl gs_CollectStraftatenByState(int state, int* out)
{
	int count;
	int i;
	int p;

	count = 0;
	i = 0;
	for (p = (int) g_9a3825; p < (int) (g_9a3825 + 0x5a00); p += 0x2d) {
		if (count >= 0x20) {
			break;
		}
		if (*(int*) p == state) {
			out[count] = i;
			count++;
		}
		i++;
	}
	return count;
}
