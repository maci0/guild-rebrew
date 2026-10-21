extern char* g_entity_type_table;
extern char* g_item_def_table;

unsigned short* __cdecl fcn_00502cd0(int, int, int, int);
unsigned short* __cdecl fcn_00502850(void);

/* ADDRESS: GOLDTL 0x004a4fb0 */
unsigned int __cdecl fcn_004a4fb0(unsigned int* a0, unsigned int* a1, unsigned char* a2)
{
	unsigned char* rec;
	unsigned char* v6;
	unsigned short* v11;
	unsigned short* v10;
	unsigned short* v12;
	unsigned short* v5;
	unsigned char v1;
	int container;
	int v7;
	int v4;
	int idx;

	container = *(int*) (a2 + 0x5d);
	rec = (unsigned char*) (g_entity_type_table + *a2 * 0x24d);
	v11 = 0;
	idx = 0;
	if ((unsigned char) rec[0x22] <= 0) {
		return 0;
	}
	v12 = (unsigned short*) (rec + 0xa5);
	v10 = (unsigned short*) (rec + 0x23);
	v6 = a2;
	do {
		v1 = *(unsigned char*) (g_item_def_table + (*v10 & 0x7fff) * 0x41);
		if (v1 != '!') {
			if (v1 != 2 && v1 != 6) {
label:
				if (!fcn_00502cd0(container, 1, 0, *v10 & 0x7fff)) {
					if (!*(unsigned short*) ((char*) v12 - 2) ||
					    fcn_00502cd0(container, 1, 0, *(unsigned short*) ((char*) v12 - 2))) {
						if (!*v12 || fcn_00502cd0(container, 1, 0, *v12)) {
							*a0 = *(unsigned short*) (rec + 0x23 + idx * 2) & 0x7fff;
							if (v11 != 0) {
								*a1 = *(unsigned int*) ((char*) v11 + 2);
								return 1;
							}
							*a1 = 0xffffffff;
							return 1;
						}
					}
				}
			} else {
				v7 = 0;
				v4 = 0;
				v11 = 0;
				v5 = fcn_00502cd0(*(int*) (v6 + 0x5d), 1, 4, 2);
				while (v5 != 0) {
					if (*v5 != 0xfd) {
						v7 += 1;
					}
					if (*v5 == (*v10 & 0x7fff)) {
						container = *(int*) ((char*) v5 + 0x14);
						v4 = 1;
						v11 = v5;
						break;
					}
					v5 = fcn_00502850();
				}
				if (v7 < (int) (unsigned char) rec[0x21] && !v4) {
					v5 = fcn_00502cd0(*(int*) (a2 + 0x5d), 1, 4, 6);
					do {
						if (!v5) {
							break;
						}
						if (*v5 == (*v10 & 0x7fff)) {
							container = *(int*) ((char*) v5 + 0x14);
							v4 = 1;
							v11 = v5;
							break;
						}
						v5 = fcn_00502850();
					} while (1);
					if (v7 < (int) (unsigned char) rec[0x21] && !v4) {
						goto label;
					}
				}
			}
			v6 = a2;
		}
		v12 += 2;
		idx += 1;
		v10 += 1;
		if (idx >= (int) (unsigned char) rec[0x22]) {
			return 0;
		}
	} while (1);
}
