#include "client_types.h"
extern pos14_7f4c00 gm_GameTime;

void __cdecl gm_AddTime(char* dst, int a, int b, int c);
void* __cdecl gm_StartFilteredEntitySearch(int a, int b, int c);
char* __cdecl fcn_004bcc50(int a, int b);
char* __cdecl gm_LookupEntityRecordById(int id);
int __cdecl fcn_00502cd0(int a, int b, int c, int d);
void __cdecl fcn_00529160(char* obj, int a, int id, int b);
int __cdecl fcn_004c5aa0(int a, char b, char c, short d, char e, int f);
void __cdecl he_FreeAction(char* obj);

/* ADDRESS: GOLDTL 0x00565980 */
void __cdecl fcn_00565980(char* obj)
{
	char* e;
	char* t;
	unsigned short* pal;
	int v;

	*(pos14_7f4c00*) (obj + 0x52) = gm_GameTime;
	gm_AddTime(obj + 0x52, 0, 0, 1);
	*(int*) (obj + 0x70) = 0;
	e = (char*) gm_StartFilteredEntitySearch(1, 1, *(int*) (obj + 0xac));
	if (e != 0) {
		t = (char*) fcn_004bcc50(*(int*) (e + 0x71), *(int*) (obj + 0xb8));
		pal = (unsigned short*) gm_LookupEntityRecordById(*(int*) (obj + 0xb0));
		if (t != 0 && *(int*) (t + 0x10) == -1) {
			if (pal != 0) {
				if (*(unsigned char*) ((char*) pal + 0x180) != 0x28) {
					v = fcn_00502cd0(*(int*) (e + 0x5d), 1, 0, 0xfd);
					fcn_00529160(e, v, (int) *pal, (int) obj);
					v = *(int*) (obj + 4);
					*(int*) (obj + 0xc0) = fcn_004c5aa0(*(int*) (obj + 0xac),
						*(char*) (t + 8),
						*(char*) (t + 9),
						*(unsigned short*) (t + 0xa), 1, v);
					*(unsigned short*) (obj + 0xbc) = *(unsigned short*) (t + 0xa);
					*(int*) (obj + 0xb4) = -1;
					return;
				}
			}
		}
		else if (pal != 0) {
			fcn_00529160(e, 0, (int) *pal, 0);
		}
	}
	he_FreeAction(obj);
}
