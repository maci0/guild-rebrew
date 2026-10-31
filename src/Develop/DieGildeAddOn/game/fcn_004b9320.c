#include <string.h>

extern char g_868060[];

void* __cdecl gm_LookupEntityRecordById(int);
int __cdecl fcn_005c6270(char*, int);
void* __cdecl fcn_005463a0(int, int, int);
void* __cdecl he_fn_Handlung(void);
void __cdecl fcn_005015e0(void*, int, int, int);
int __cdecl fcn_00505370(char*);
unsigned short __cdecl fcn_0042e410(int);
void __cdecl io_FormatTextBuffer(char*, int, ...);
void __cdecl fcn_00545d40(char*, char*, char*, int, int, int);

/* ADDRESS: GOLDTL 0x004b9320 */
int __cdecl fcn_004b9320(char* a0)
{
	char* e;
	char* it;
	char* obj;
	char* o1;
	char* o2;
	char* p;
	char buf[0x800];
	int ids[8];
	char* cand[8];
	int v84c;
	int v848;
	int v844;
	int n;
	int r;
	int k;
	int len;

	n = 0;
	e = (char*) gm_LookupEntityRecordById(*(int*) a0);
	if (e == 0) {
		return 1;
	}
	if (fcn_005c6270(e, 0x290) != 0) {
		return 0x400;
	}
	it = (char*) fcn_005463a0(0xf, 0, 1);
	while (it != 0) {
		if (n >= 8) {
			break;
		}
		fcn_005015e0(&v844, 0, 0, *(int*) (it + 0xac));
		obj = (char*) v844;
		if (obj != 0 && *(int*) (obj + 0xa) == *(unsigned short*) e) {
			fcn_005015e0(&v848, 0, 0, *(int*) (it + 0xb4));
			fcn_005015e0(&v84c, 0, 0, *(int*) (it + 0xb0));
			if ((v848 != 0 && fcn_00505370((char*) v848) != 0)
			    || (v84c != 0 && fcn_00505370((char*) v84c) != 0)) {
				if ((v84c != 0 && v848 != 0 && *(char*) v84c == 0x47)
				    || *(char*) v848 == 0x47) {
					cand[n] = it;
					ids[n] = v844;
					n++;
				}
			}
		}
		it = (char*) he_fn_Handlung();
	}
	if (n == 0) {
		return 0x400;
	}
	r = (int) fcn_0042e410(n) & 0xffff;
	obj = cand[r];
	v844 = ids[r];
	fcn_005015e0(&v84c, 0, 0, *(int*) (obj + 0xb0));
	fcn_005015e0(&v848, 0, 0, *(int*) (obj + 0xb4));
	o1 = (char*) v84c;
	o2 = (char*) v848;
	if (*(char*) o1 == 0x47) {
		k = *(int*) (o1 + 0x65);
		p = (char*) (0x868060 + ((k << 6) - k) * 3 * 4);
		io_FormatTextBuffer(buf, *(unsigned short*) (a0 + 4) + 0x12e7, p,
		             g_868060, g_868060);
	} else {
		k = *(int*) (o2 + 0x65);
		p = (char*) (0x868060 + ((k << 6) - k) * 3 * 4);
		io_FormatTextBuffer(buf, *(unsigned short*) (a0 + 4) + 0x12e7, g_868060, p, p);
	}
	len = (int) strlen(buf);
	fcn_00545d40(a0, a0, buf, len > 0x100 ? 1 : 0, 0x5ef, 0);
	return 0;
}
