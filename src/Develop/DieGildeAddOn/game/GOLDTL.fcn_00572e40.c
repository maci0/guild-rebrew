#include <string.h>

char* __cdecl fcn_005463a0(int, int, int, int, int);
char* __cdecl he_fn_Handlung(void);
void __cdecl fcn_00546190(char*);
void __cdecl fcn_00500bb0(int, int, int, char*);
void* __cdecl gm_FindRecordById(int, int, int, char*, int);
int __cdecl fcn_004c5530(char*);
char* __cdecl gm_LookupEntityRecordById(int);

/* ADDRESS: GOLDTL 0x00572e40 */
void __cdecl fcn_00572e40(char* c)
{
	char buf[0xf8];
	char* x;

	x = fcn_005463a0(2, 0, 0xb, 3, *(int*) (c + 0x10));
	if (x != 0) {
		do {
			if (*(int*) (x + 0xac) == *(int*) (c + 0xac) &&
			    *(int*) (x + 4) == *(int*) (c + 4)) {
				fcn_00546190(c);
				return;
			}
			x = he_fn_Handlung();
		} while (x != 0);
	}
	memcpy(c + 0x52, c + 0x44, 0xe);
	memcpy(c + 0x60, c + 0x44, 0xe);
	*(int*) (c + 0xe8) = -1;
	*(int*) (c + 0xec) = -1;
	fcn_00500bb0(0, 1, 0, c + 0x52);
	memset(buf, 0, 0xf8);
	*(int*) (buf + 0x28) = *(int*) (c + 0x44);
	*(short*) (buf + 0x34) = *(short*) (c + 0x50);
	buf[4] = 0xf;
	*(int*) (buf + 0xc) = -1;
	buf[0x36] = 2;
	*(int*) (buf + 0x60) = *(int*) (c + 0xb0);
	*(int*) (buf + 8) = *(int*) ((char*) 0x7f4ca0 + (short) *(short*) (c + 8) * 0x21c + 4);
	*(int*) (buf + 0x30) = *(int*) (c + 0x4c);
	*(int*) (buf + 0x2c) = *(int*) (c + 0x48);
	*(int*) (buf + 0x5c) = *(int*) (c + 0x10);
	*(int*) (buf + 0xa0) = *(int*) (c + 4);
	*(int*) (buf + 0x58) = *(int*) (c + 0xac);
	if (gm_FindRecordById(0, 1, 0, c + 0x52, *(int*) (c + 0xac))) {
		if (*(char*) (c + 0xf1)) {
			fcn_00500bb0(0, 0x1e, 1, c + 0x52);
		} else {
			*(int*) (c + 0xec) = fcn_004c5530(buf);
		}
	} else {
		fcn_00546190(c);
	}
	*(char*) (c + 0xf0) = 0;
	if (gm_LookupEntityRecordById(*(int*) (c + 0xb4))) {
		*(char*) (c + 0xf0) = 4;
	}
}
