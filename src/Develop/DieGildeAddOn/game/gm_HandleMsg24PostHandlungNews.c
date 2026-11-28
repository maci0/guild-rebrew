#include <string.h>

extern char gm_TownTable[];

void* __cdecl gm_LookupEntityRecordById(int);

void* __cdecl he_StartHandlungSearch(int, int, int);
void* __cdecl he_fn_Handlung(void);
void __cdecl fcn_005015e0(void*, void*, void*, int);
int __cdecl fcn_00505370(char*);
unsigned short __cdecl fcn_0042e410(int);
void __cdecl io_FormatTextBuffer(char*, int, ...);
void __cdecl he_PostEntityMessage(int, int, char*, int, int, int);

/* ADDRESS: GOLDTL 0x004b9320 */
int __cdecl gm_HandleMsg24PostHandlungNews(char* request)
{
	char* e;
	char* it;
	char* obj;
	char* o1;
	char* o2;

	char buf[0x800];
	int ids[8];
	char* cand[8];
	int v84c;
	int v848;
	int resolvedObject;
	int n;
	int r;
	int k;
	int len;

	n = 0;
	e = (char*) gm_LookupEntityRecordById(*(int*) request);
	if (e == 0) {
		return 1;
	}



	it = (char*) he_StartHandlungSearch(1, 0, 0xf);
	while (it != 0) {
		if (n >= 8) {
			break;
		}
		fcn_005015e0(0, &resolvedObject, 0, *(int*) (it + 0xac));
		obj = (char*) resolvedObject;
		if (obj != 0 && *(int*) (obj + 0xa) == *(unsigned short*) e) {
			fcn_005015e0(&v848, 0, 0, *(int*) (it + 0xb4));
			fcn_005015e0(&v84c, 0, 0, *(int*) (it + 0xb0));
			if ((v848 != 0 && fcn_00505370((char*) v848) != 0)
			    || (v84c != 0 && fcn_00505370((char*) v84c) != 0)) {
				if ((*(char*) v84c == 0x47)
				    || *(char*) v848 == 0x47) {
					cand[n] = it;
					ids[n] = resolvedObject;
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
	resolvedObject = ids[r];
	fcn_005015e0(&v84c, 0, 0, *(int*) (obj + 0xb0));
	fcn_005015e0(&v848, 0, 0, *(int*) (obj + 0xb4));
	o1 = (char*) v84c;
	o2 = (char*) v848;
	if (*(char*) o1 == 0x47) {
		k = *(int*) (o1 + 0x65);
		io_FormatTextBuffer(buf, *(unsigned short*) (request + 4) + 0x12e7,
		             gm_TownTable + ((k << 6) - k) * 3 * 4, gm_TownTable, gm_TownTable);

	} else {
		k = *(int*) (o2 + 0x65);
		io_FormatTextBuffer(buf, *(unsigned short*) (request + 4) + 0x12e7, gm_TownTable,
		             gm_TownTable + ((k << 6) - k) * 3 * 4, gm_TownTable + ((k << 6) - k) * 3 * 4);
	}
	len = (int) strlen(buf);
	he_PostEntityMessage(*(int*) (e + 4), *(int*) (e + 4), buf, (unsigned int) len > 0x100 ? 1 : 0, 0x5ef, 0);
	return 0;
}
