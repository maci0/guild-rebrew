#include <string.h>

#include "client_types.h"

extern void __cdecl fcn_00546190(char*);
extern char* __cdecl gm_LookupEntityRecordById(int);
extern void __cdecl fcn_00529160(int, int, int, char*);
extern void __cdecl fcn_004c5c80(int);
extern int __cdecl fcn_004c5da0(int, int, int, char*, int, char*);
extern int __cdecl fcn_004c5620(int, char*);
extern char* __cdecl fcn_005463a0(int, int, int);
extern char* __cdecl he_fn_Handlung(void);
extern int __cdecl gm_RandomMod(int);
extern int __cdecl fcn_004c4450(int);
extern char* __cdecl fcn_004c4480(int);
extern int __cdecl fcn_004e6a30(int);
extern char* __cdecl fcn_00445600(int, int, int, char*);
extern void __cdecl fcn_00455350(char*, char*, float*);
extern void __cdecl he_CharacterBehavior(char*, int);
extern void __cdecl fcn_00500bb0(pos14_7f4c00*, int, int, int);
extern int __cdecl fcn_00500cb0(pos14_7f4c00*, pos14_7f4c00*);
extern pos14_7f4c00 g_7f4c00;

/* ADDRESS: GOLDTL 0x00554170 */
void __cdecl fcn_00554170(char* obj)
{
	unsigned char msg[0x114];
	pos14_7f4c00 stamp;
	pos14_7f4c00* time;
	char* rec;
	char* found;
	char* iter;
	int count = 0;
	int idx;
	int i;
	int added;

	found = 0;
	added = 0;

	if (*(int*) (obj + 0x70) == -2) {
		if (*(unsigned char*) (obj + 0x78) & 4) {
			fcn_00546190(obj);
			return;
		}
		*(int*) (obj + 0x70) = 5;
		added = 1;
	}
	if (*(int*) (obj + 0x70) == -1) {
		fcn_00546190(obj);
		return;
	}
	if (*(unsigned char*) (obj + 0x78) & 4)
		return;
	time = (pos14_7f4c00*) (obj + 0x52);
	*(pos14_7f4c00*) (obj + 0x52) = g_7f4c00;
	switch (*(int*) (obj + 0x70)) {
	case 0:
		iter = obj + 0x8c;
		for (count = 6; count != 0; count--) {
			rec = gm_LookupEntityRecordById(*(int*) iter);
			if (rec != 0 && *(int*) (rec + 0x184) != 0) {
				fcn_00529160(0, 0, *(unsigned short*) rec, obj);
				fcn_004c5c80(*(int*) (rec + 4));
				fcn_004c5da0(*(int*) (rec + 4), -1, -1, obj + 0xac, 1, (char*) 0x6a5c7c);
			}
			iter += 4;
		}
		fcn_00500bb0(time, 0, 5, 0);
		*(int*) (obj + 0x84) = fcn_004c5620(1, obj);
		return;
	case 1:
		iter = obj + 0x8c;
		while (count < 6) {
			rec = gm_LookupEntityRecordById(*(int*) iter);
			if (rec != 0 && *(int*) (rec + 0x184) != 0 && *(int*) (*(char**) (rec + 0x184) + 0x128) != 0) {
				fcn_00500bb0(time, 0, 4, 0);
				*(int*) (obj + 0x84) = fcn_004c5620(1, obj);
				return;
			}
			count++;
			iter += 4;
		}
		*(pos14_7f4c00*) (obj + 0x44) = g_7f4c00;
		fcn_00500bb0(time, 0, 0xa, 0);
		*(int*) (obj + 0x84) = fcn_004c5620(2, obj);
		return;
	case 2:
		stamp = *(pos14_7f4c00*) (obj + 0x44);
		fcn_00500bb0(&stamp, 0x18, 0, 0);
		if (fcn_00500cb0((pos14_7f4c00*) 0x7f4c00, &stamp) > 0) {
			fcn_00500bb0(time, 0, 2, 0);
			*(int*) (obj + 0x84) = fcn_004c5620(5, obj);
			return;
		}
		found = fcn_005463a0(1, 0, 0x48);
		if (found != 0) {
			for (;;) {
				if (strcmp(obj + 0xac, found + 0xac) == 0 &&
				    *(unsigned short*) (found + 8) != *(unsigned short*) (obj + 8))
					break;
				found = he_fn_Handlung();
				if (found == 0)
					goto not_found;
			}
			if (gm_RandomMod(2) != 0 &&
			    *(unsigned short*) (found + 8) != *(unsigned short*) (obj + 8)) {
				memset(msg, 0, sizeof(msg));
				msg[8] = 3;
				msg[0x26] = 0xa2;
				*(int*) (msg + 0xc) = *(int*) ((unsigned int) *(unsigned short*) 0x774970 * 0x21c + 0x7f4ca4);
				*(int*) (msg + 0x14) = -1;
				msg[0x30] = 2;
				msg[0x7c] = 4;
				*(int*) (msg + 0x34) = *(int*) ((unsigned int) *(unsigned short*) (obj + 8) * 0x21c + 0x7f4ca4);
				*(int*) (msg + 0x38) = *(int*) ((unsigned int) *(unsigned short*) (found + 8) * 0x21c + 0x7f4ca4);
				for (i = 0; i < 0x10; i++) {
					*(int*) (msg + 0x80 + i * 4) = -1;
					*(int*) (msg + 0xc0 + i * 4) = -1;
				}
				for (i = 0, idx = 0; i < 8; i++) {
					if (idx >= 6)
						break;
					if (*(int*) (found + 0x8c + i * 4) != -1) {
						*(int*) (msg + 0x80 + idx * 4) = *(int*) (found + 0x8c + i * 4);
						idx++;
					}
				}
				for (i = 0, idx = 0; i < 6; i++) {
					if (idx >= 6)
						break;
					if (*(int*) (obj + 0x8c + i * 4) != -1) {
						*(int*) (msg + 0xc0 + idx * 4) = *(int*) (obj + 0x8c + i * 4);
						idx++;
					}
				}
				*(pos14_7f4c00*) (msg + 0x18) = g_7f4c00;
				*(int*) (msg + 0x100) = -1;
				*(int*) (msg + 0x104) = -1;
				*(int*) (msg + 0x108) = -1;
				*(int*) (msg + 0x10c) = *(int*) (obj + 0xcc);
				fcn_00500bb0((pos14_7f4c00*) (msg + 0x18), 0x1e, 0, 0);
				*(int*) (obj + 0xd8) = fcn_004c5980(msg);
				*(int*) (obj + 0x70) = 3;
				fcn_00500bb0(time, 0, 0xa, 0);
				*(int*) (obj + 0x84) = fcn_004c5620(3, obj);
				return;
			}
		}
	not_found:
		fcn_00500bb0(time, 0, 0xa, 0);
		if (*(int*) 0x6b8010 == 0) {
			rec = fcn_00445600(0, 0x140, 0, obj + 0xac);
			if (rec != 0) {
				float pos[4];

				fcn_00455350(rec, rec + 0x4c, pos);
				he_CharacterBehavior(obj, (int) pos);
			}
		}
		*(int*) (obj + 0x84) = fcn_004c5620(2, obj);
		return;
	case 3:
		fcn_00500bb0(time, 0, 1, 0);
		if (fcn_004c4450(*(int*) (obj + 0xd8)) != 0) {
			rec = fcn_004c4480(*(int*) (obj + 0xd8));
			if (rec != 0) {
				*(int*) (obj + 0xd4) = *(int*) rec;
				*(int*) (obj + 0x84) = fcn_004c5620(4, obj);
				return;
			}
			*(int*) (obj + 0x84) = fcn_004c5620(5, obj);
			return;
		}
		*(int*) (obj + 0x84) = fcn_004c5620(3, obj);
		return;
	case 4:
		fcn_00500bb0(time, 0, 5, 0);
		if (fcn_004e6a30(*(int*) (obj + 0xd4)) != 0) {
			*(int*) (obj + 0x84) = fcn_004c5620(4, obj);
			return;
		}
		*(int*) (obj + 0x84) = fcn_004c5620(5, obj);
		return;
	case 5:
		iter = obj + 0x8c;
		for (count = 6; count != 0; count--) {
			rec = gm_LookupEntityRecordById(*(int*) iter);
			if (rec != 0 && *(int*) (rec + 0x184) != 0) {
				fcn_00529160(0, 0, *(unsigned short*) rec, 0);
				fcn_004c5c80(*(int*) (rec + 4));
				fcn_004c5da0(*(int*) (rec + 4), *(int*) (obj + 0xcc), *(int*) (obj + 0xd0), 0, 0,
					     (char*) 0x6a5c7c);
			}
			iter += 4;
		}
		fcn_00500bb0(time, 0, 2, 0);
		if (added) {
			fcn_00546190(obj);
			return;
		}
		*(int*) (obj + 0x84) = fcn_004c5620(-1, obj);
		return;
	default:
		return;
	}
}
