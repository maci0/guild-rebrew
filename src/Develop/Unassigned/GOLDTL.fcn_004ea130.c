typedef struct {
	int f0;
	int id;
	unsigned char c8;
	int n;
	unsigned char type;
	int ref;
} EVT_ARG;

int __cdecl fcn_004e8b80(unsigned int a0, int a1, EVT_ARG* a2);
char* __cdecl gm_LookupEntityRecordById(int a0);

/* ADDRESS: GOLDTL 0x004ea130 */
unsigned int __cdecl fcn_004ea130(unsigned int a0)
{
	EVT_ARG args[6];
	int flag;
	int n;
	int i;
	int j;
	int id;
	char* obj;
	char* obj2;
	char* p;

	flag = 0;
	n = fcn_004e8b80(a0, 6, args);
	if (n <= 0) {
		goto done;
	}
	for (i = 0; i < n; i++) {
		if ((char) args[i].type == 2) {
			id = args[i].ref;
			obj = gm_LookupEntityRecordById(id);
			obj2 = gm_LookupEntityRecordById(args[i].id);
			if (obj == 0 || obj[8] == 0 || obj[0x1b1] != 0 || obj2 == 0 || obj2[8] == 0) {
				continue;
			}
			for (j = 0; j < n; j++) {
				if (args[j].id == id) {
					break;
				}
			}
			if (j < n) {
				flag = flag | 1;
			}
		} else if ((char) args[i].type == 3) {
			if (args[i].n <= 0) {
				continue;
			}
			p = (char*) 0x7f4ca2;
			while (p < (char*) 0x85a0a2) {
				if ((char) p[0x166] == (char) args[i].c8) {
					flag = flag | 1;
					if ((*p == 6 || *p == 7) && p[0x1af] == 0) {
						flag = flag | 2;
						break;
					}
				}
				p += 0x21c;
			}
		}
	}
done:
	if ((flag & 1) != 0) {
		for (i = 0; i < n; i++) {
			obj = gm_LookupEntityRecordById(args[i].id);
			if (obj == 0) {
				continue;
			}
			if ((*(unsigned char*) (obj + 2) != 6 && *(unsigned char*) (obj + 2) != 7) ||
			    *(unsigned char*) (obj + 0x1b1) != 0) {
				continue;
			}
			args[i].id = args[i].id | 2;
			break;
		}
	}
	return (unsigned int) ((flag & 2) >> 1);
}
