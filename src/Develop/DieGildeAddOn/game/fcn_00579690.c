#include "client_types.h"

int __cdecl fcn_00503fe0(int a, int b, int c);
void* __cdecl fcn_00502cd0(int a, int b, int c, int d, int e);
void* __cdecl gm_LookupEntityRecordById(int id);
void __cdecl fcn_00529160(int a, int b, int c, void* d);
void __cdecl fcn_00546190(void* p);
void __cdecl fcn_00500bb0(void* p, int a, int b, int c);

extern pos14_7f4c00 g_7f4c00;

/* ADDRESS: GOLDTL 0x00579690 */
void __cdecl fcn_00579690(char* a0)
{
	void* h;
	void* q;
	int obj;
	int found;
	int i;
	int* p;

	found = 0;
	obj = fcn_00503fe0(1, 1, *(int*) (a0 + 0x10));
	h = fcn_00502cd0(*(int*) (obj + 0x5d), 2, found, 0xfd, 6);
	p = (int*) (a0 + 0x8c);
	for (i = 4; i != 0; i--) {
		q = gm_LookupEntityRecordById(*p);
		if (q != 0) {
			found++;
			fcn_00529160(obj, (int) h, *(unsigned short*) q, a0);
		}
		p++;
	}
	if (found == 0) {
		fcn_00546190(a0);
		return;
	}
	*(int*) (a0 + 0xb0) = 0;
	*(pos14_7f4c00*) (a0 + 0xb8) = g_7f4c00;
	*(int*) (a0 + 0xb4) = 0x168;
	*(pos14_7f4c00*) (a0 + 0x52) = g_7f4c00;
	*(int*) (a0 + 0x70) = 0;
	fcn_00500bb0(a0 + 0x52, 0, 5, 0);
}
