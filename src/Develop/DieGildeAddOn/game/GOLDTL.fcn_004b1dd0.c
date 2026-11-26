


#include <string.h>

extern unsigned char g_773d75;

char* __cdecl gm_LookupEntityRecordById(int);
int __cdecl fcn_004ae130(unsigned short);
int __cdecl fcn_0064fcaf(char*);
int __cdecl gm_FindObjektPrototypeByName(char*);
int __cdecl cm_SendSellObjekt(int, int, int, int, unsigned char, int);

int __cdecl hst_CmdInventarPlus(char* tbl, int idx, char* arg)
{
	char* e;
	char* s;
	int r;

	e = gm_LookupEntityRecordById(*(int*) (tbl + idx * 8 + 4));
	if (e != 0 && fcn_004ae130(*(unsigned short*) e) != 0 && *arg == '-') {
		s = arg + 1;
		if (strlen(s) >= 4) {
			s += 3;
			fcn_0064fcaf(s + 1);
			r = gm_FindObjektPrototypeByName(s);
			if (r != 0) {
				cm_SendSellObjekt(*(int*) (e + 4), -1, r, 1, g_773d75, 0);
				return 1;
			}
		}
	}
	return 0;
}
