
/* Return the index of the matching 0x2d-byte table entry, or -1. */

#if defined(REBREW_GOLD)
#define TABLE_START 0x91f700
#define TABLE_END 0x925100
#else
#define TABLE_START 0x9a3800
#define TABLE_END 0x9a9200
#endif

/* ADDRESS: GOLD 0x004f36e0 */
/* ADDRESS: GOLDTL 0x004f5810 */
int __cdecl FindStraftatIndexById(int a)
{
	int i;
	int p;
	i = 0;
	p = TABLE_START;
	while (p < TABLE_END) {
		if (*(int*) p == a) {
			return i;
		}
		p += 0x2d;
		i++;
	}
	return -1;
}

#undef TABLE_START
#undef TABLE_END
