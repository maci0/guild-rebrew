


#include "client_types.h"
extern pos14_7f4c00 g_7f4c00;

char* __cdecl gm_LookupEntityRecordById(int);
char* __cdecl gm_SearchTable67(int);
int __cdecl gm_FindRecordById(int);
void __cdecl fcn_00529160(char*, int, int, char*);
void __cdecl fcn_00500bb0(pos14_7f4c00*, int, int, int);

void __cdecl fcn_0056db10(char* u)
{
	char* h;
	char* t;
	int rec;

	rec = 0;
	h = gm_LookupEntityRecordById(*(int*) (u + 0xac));
	t = gm_SearchTable67(*(int*) (u + 0x10));
	if (*(int*) (u + 0xc4) != -1) {
		rec = gm_FindRecordById(*(int*) (u + 0xc4));
	}
	fcn_00529160(t, rec, *(unsigned short*) h, u);
	*(int*) (u + 0xb0) = 200;
	*(pos14_7f4c00*) (u + 0xb4) = g_7f4c00;
	*(pos14_7f4c00*) (u + 0x44) = g_7f4c00;
	*(pos14_7f4c00*) (u + 0x52) = g_7f4c00;
	*(pos14_7f4c00*) (u + 0x60) = g_7f4c00;
	fcn_00500bb0((pos14_7f4c00*) (u + 0xb4), 0, 400, 0);
}
