

/* GOLD twin of GOLDTL fcn_00465920: 0x2ff slots of 0x2ec bytes here,
 * 0x3ff slots of 0x2f4 bytes in GOLDTL. */

extern char* g_f8f080;

int __cdecl fcn_00468850(void)
{
	int i;
	char* p;

	for (i = 0, p = (char*) ((*(int*)&g_f8f080) + 4); i < 0x2ff; i++, p += 0x2ec) {
		if (*(int*) p == 0) {
			return i;
		}
	}
	return -1;
}
