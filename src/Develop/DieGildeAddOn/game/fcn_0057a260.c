char* __cdecl gm_LookupEntityRecordById(int);
char* __cdecl gm_StartFilteredEntitySearch(int, int, int);
int __cdecl fcn_00502cd0(int, int, int, int, int);
int __cdecl fcn_00529160(char*, int, int, char*);
int __cdecl fcn_00500bb0(char*, int, int, int);
int __cdecl fcn_00546190(char*);

#include "client_types.h"

extern pos14_7f4c00 g_7f4c00;

/* ADDRESS: GOLDTL 0x0057a260 */
int __cdecl fcn_0057a260(char* p)
{
	int v;
	char* s;
	char* e;

	v = 0;
	s = (char*) gm_LookupEntityRecordById(*(int*)(p + 0xac));
	if (s != 0
	    && (*(char**)(s + 0x17c) == 0 || *(unsigned char*)*(char**)(s + 0x17c) != 0x8f)
	    && (e = (char*) gm_StartFilteredEntitySearch(1, 1, *(int*)(p + 0x10))) != 0) {
		if (*(int*)(p + 0xb4) != -1)
			v = fcn_00502cd0(*(int*)(e + 0x5d), 2, 6, 1, *(int*)(p + 0xb4));
		*(pos14_7f4c00*) (p + 0x52) = g_7f4c00;
		*(pos14_7f4c00*) (p + 0x44) = g_7f4c00;
		if (v)
			fcn_00529160(e, v, *(unsigned short*)s, p);
		else
			fcn_00529160(e, 0, *(unsigned short*)s, p);
		*(pos14_7f4c00*) (p + 0x60) = g_7f4c00;
		fcn_00500bb0(p + 0x52, 0, 0x1e, 0);
		*(pos14_7f4c00*) (p + 0xb8) = *(pos14_7f4c00*) (p + 0x52);
		return fcn_00500bb0(p + 0xb8, 3, 0, 0);
	}
	return fcn_00546190(p);
}
