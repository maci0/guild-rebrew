#include "client_types.h"

int __cdecl fcn_00503fe0(int a, int b, int c);
void* __cdecl fcn_00502cd0(int a, int b, int c, int d, int e);
void* __cdecl gm_LookupEntityRecordById(int id);
void __cdecl he_AssignActionSlot(int a, int b, int c, void* d);
void __cdecl he_FreeAction(void* p);
void __cdecl gm_AddTime(void* p, int a, int b, int c);

extern pos14_7f4c00 gm_GameTime;

/* ADDRESS: GOLDTL 0x00579690 */
void __cdecl he_StartRohstoffsuchen(char* event)
{
	void* h;
	void* q;
	int obj;
	int found;
	int i;
	int* p;

	found = 0;
	obj = fcn_00503fe0(1, 1, *(int*) (event + 0x10));
	h = fcn_00502cd0(*(int*) (obj + 0x5d), 2, found, 0xfd, 6);
	p = (int*) (event + 0x8c);
	for (i = 4; i != 0; i--) {
		q = gm_LookupEntityRecordById(*p);
		if (q != 0) {
			found++;
			he_AssignActionSlot(obj, (int) h, *(unsigned short*) q, event);
		}
		p++;
	}
	if (found == 0) {
		he_FreeAction(event);
		return;
	}
	*(int*) (event + 0xb0) = 0;
	*(pos14_7f4c00*) (event + 0xb8) = gm_GameTime;
	*(int*) (event + 0xb4) = 0x168;
	*(pos14_7f4c00*) (event + 0x52) = gm_GameTime;
	*(int*) (event + 0x70) = 0;
	gm_AddTime(event + 0x52, 0, 5, 0);
}
