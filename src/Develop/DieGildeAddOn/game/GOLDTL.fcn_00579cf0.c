void __cdecl fcn_00546190(char*);

#include "client_types.h"
extern pos14_7f4c00 g_7f4c00;




unsigned short* __cdecl gm_LookupEntityRecordById(int);
char* __cdecl gm_SearchTable67(int);
char* __cdecl fcn_00502cd0(int, int, int, int);
void __cdecl fcn_00529160(char*, char*, int, char*);
void __cdecl fcn_00500bb0(pos14_7f4c00*, int, int, int);

void __cdecl fcn_00579cf0(char* o)
{
	unsigned short* x;
	char* r;
	char* q;

	x = gm_LookupEntityRecordById(*(int*) (o + 0x8c));
	if (x != 0) {
		r = gm_SearchTable67(*(int*) (o + 0x10));
		if (r != 0) {
			q = fcn_00502cd0(*(int*) (r + 0x5d), 1, 0, 0xfd);
			fcn_00529160(r, q, *x, o);
			*(int*) (o + 0xac) = 0;
			*(int*) (o + 0xb8) = 0x1fe;
			*(pos14_7f4c00*) (o + 0xbc) = g_7f4c00;
			*(pos14_7f4c00*) (o + 0x52) = g_7f4c00;
			*(int*) (o + 0x70) = 0;
			fcn_00500bb0((pos14_7f4c00*) (o + 0x52), 0, 5, 0);
			return;
		}
	}
	fcn_00546190(o);
}
