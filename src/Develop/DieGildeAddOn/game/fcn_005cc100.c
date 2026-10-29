int __cdecl fcn_004e93d0(unsigned char* a1, int max, int* out);
int __cdecl fcn_005ca560(void* sel);
int __cdecl fcn_005cf720(unsigned short a, unsigned short b, int c, int d);

/* ADDRESS: GOLDTL 0x005cc100 */
int __cdecl fcn_005cc100(char* a1, unsigned int a2, char* a3, int a4)
{
	int n;
	int i;
	int ids[4];
	char* ent;
	char* out;
	int count;

	count = 0;
	if (*(char*) (a1 + 0x166) == 0) {
		return 0;
	}
	n = fcn_004e93d0((unsigned char*) a1, 4, ids);
	if (n == 0) {
		return 0;
	}
	if (a2 == 0) {
		ent = (char*) 0x7f4e08;
		do {
			if (*ent != 0) {
				i = 0;
				if (n > 0) {
					do {
						if (ids[i] == (int) (unsigned char) *ent) {
							count++;
							break;
						}
						i++;
					} while (i < n);
				}
			}
			ent += 0x21c;
		} while ((int) ent < 0x85a208);
		return count;
	}
	i = 0;
	if (n > 0) {
		do {
			if ((unsigned int) count >= a2) {
				break;
			}
			out = a3 + count * 0x38;
			ent = (char*) 0x7f4ca0;
			do {
				if (ids[i] == (int) (unsigned char) ent[0x168]) {
					*(char**) out = ent;
					*(int*) (out + 0x34) = ids[i];
					fcn_005ca560(out);
					*(int*) (out + 0x30) = fcn_005cf720(*(unsigned short*) a1,
						*(unsigned short*) *(char**) out, a4, 0);
					count++;
					out += 0x38;
					if ((unsigned int) count >= a2) {
						break;
					}
				}
				ent += 0x21c;
			} while ((int) ent < 0x85a0a0);
			i++;
		} while (i < n);
	}
	return count;
}
