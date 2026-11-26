#include <string.h>

char* __cdecl he_StartHandlungSearch(int, int, int, int, int);
char* __cdecl he_fn_Handlung(void);
void __cdecl he_FreeAction(char*);
void __cdecl gm_AddTime(char*, int, int, int);
void* __cdecl gm_FindRecordById(int);
int __cdecl cm_SendCopyEntityData(char*);
char* __cdecl gm_LookupEntityRecordById(int);

/* ADDRESS: GOLDTL 0x00572e40 */
void __cdecl he_StartHandelsrouteTrade(char* c)
{
	char buf[0xf8];
	char* x;
	char* p44;
	char* p52;

	x = he_StartHandlungSearch(2, 0, 0xb, 3, *(int*) (c + 0x10));
	if (x != 0) {
		do {
			if (*(int*) (x + 0xac) == *(int*) (c + 0xac) &&
			    *(int*) (x + 4) != *(int*) (c + 4)) {
				he_FreeAction(c);
				return;
			}
			x = he_fn_Handlung();
		} while (x != 0);
	}
	p44 = c + 0x44;
	p52 = c + 0x52;
	memcpy(p52, p44, 0xe);
	memcpy(c + 0x60, p44, 0xe);
	*(int*) (c + 0xe8) = -1;
	*(int*) (c + 0xec) = -1;
	gm_AddTime(p52, 0, 1, 0);
	memset(buf, 0, 0xf8);
	buf[4] = 0xf;
	*(int*) (buf + 8) = *(int*) ((char*) 0x7f4ca0 + *(unsigned short*) (c + 8) * 0x21c + 4);
	memcpy(buf + 0x28, p44, 0xe);

	*(int*) (buf + 0xc) = -1;
	buf[0x36] = 2;
	*(int*) (buf + 0x60) = *(int*) (c + 0xb0);


	*(int*) (buf + 0x5c) = *(int*) (c + 0x10);
	*(int*) (buf + 0x58) = *(int*) (c + 0xac);
	*(int*) (buf + 0xa0) = *(int*) (c + 4);
	if (gm_FindRecordById(*(int*) (c + 0xac))) {
		if (*(char*) (c + 0xf1)) {
			gm_AddTime(p52, 1, 0x1e, 0);
		} else {
			*(int*) (c + 0xec) = cm_SendCopyEntityData(buf);
		}
	} else {
		he_FreeAction(c);
	}
	*(char*) (c + 0xf0) = 0;
	if (gm_LookupEntityRecordById(*(int*) (c + 0xb4))) {
		*(char*) (c + 0xf0) = 4;
	}
}
