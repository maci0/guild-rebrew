extern int g_6acf80;
extern int g_6acf84;

/* ADDRESS: GOLDTL 0x005387c0 */
int __cdecl fcn_005387c0(int count, char* list)
{
	int ids[5];
	int* p;
	int i;
	int found;

	found = -1;
	ids[0] = 0x17;
	ids[1] = 0x18;
	ids[2] = 0x19;
	ids[3] = 0x1a;
	ids[4] = 0;
	for (p = ids; *p != 0; p++) {
		for (i = 0; i < count; i++) {
			if (*(int*) (list + i * 0x10) == g_6acf80 && *(int*) (list + i * 0x10 + 4) == g_6acf84) {
				if (found == -1) {
					found = i;
				}
				if (*p == *(int*) (list + i * 0x10 + 0xc)) {
					return i;
				}
			}
		}
	}
	return found;
}
