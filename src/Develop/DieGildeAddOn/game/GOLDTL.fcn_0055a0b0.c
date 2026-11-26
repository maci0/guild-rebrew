typedef struct EvRec EvRec;
struct EvRec {
	unsigned char f00;
	char pad0[3];
	int id;
	unsigned char kind;
	char pad1[15];
};
#include "client_actions.h"
int __cdecl fcn_004e8b40(int, int*);
int __cdecl amt_FindOfficeSlotsByKind(int, int, EvRec*);
unsigned char* __cdecl gm_LookupEntityRecordById(int);
unsigned short __cdecl gm_RandomMod(unsigned short);
int __cdecl amt_SendOfficeCommand(unsigned char, unsigned char*, unsigned char*, int, int);
void __cdecl fcn_004c54c0(int, int, int, int);
void __cdecl fcn_00545d40(int, int, void*, int, int, void*);
void __cdecl io_FormatTextBuffer(void*, int, ...);
void __cdecl gm_AddTime(void*, int, int, int);
void __cdecl he_FreeAction(void*);

/* ADDRESS: GOLDTL 0x0055a0b0 */
void __cdecl fcn_0055a0b0(char* action)
{
	int cnt;
	int i;
	unsigned short b;
	int idx;
	int n;
	int tmp[6];
	EvRec arr[6];
	char buf[0x800];
	unsigned char* p;
	unsigned char* r;
	unsigned char* v3;

	idx = *(int*) (action + 0x70);
	if (idx == 0xc) {
		if (*(int*) (action + 0xac) == 0) {
			io_FormatTextBuffer(buf, 0x10bc, (unsigned char*) 0x868080 + g_773d75 * 0x2f4);
		} else {
			io_FormatTextBuffer(buf, 0x10be, (unsigned char*) 0x868080 + g_773d75 * 0x2f4);
		}
		p = (unsigned char*) 0x7f4ca2;
		do {
			if (*p == 6 || *p == 7) {
				fcn_00545d40(*(unsigned int*) (p + 2), -1, buf, 0x20, 0x600, (void*) 0x6b5c60);
			}
			p += 0x21c;
		} while ((int) p < 0x85a0a2);
		*(int*) (action + 0x70) = 0;
		gm_AddTime((unsigned char*) action + 0x52, 1, 0, 0);
		return;
	} else {
		if (idx >= 0 && idx < 6) {
			cnt = amt_FindOfficeSlotsByKind(*(int*) (action + 0xb0 + idx * 4), 6, arr);
			for (i = 0, r = (unsigned char*) arr; i < cnt; i++) {
					v3 = gm_LookupEntityRecordById(*(int*) (r + 4));
					if (v3 != 0 && fcn_004e8b40(*(unsigned char*) (r + 8), tmp)) {
						if (*(int*) (action + 0xac) == 1
						    && ((unsigned char) *(tmp + 2) == 9 || ((*(2 + tmp)) & 0xFF) == 6)) {
							if ((short) gm_RandomMod(3) != 0) {
								amt_SendOfficeCommand(*(unsigned char*) r, 0, 0, 4, 0xff);
							}
						}
						if (*(unsigned char*) (v3 + 2) != 3) {
							n = 0;
							p = (unsigned char*) 0x7f4ca4;
							do {
								if (*(unsigned int*) (p + 0x168) != 0
								    && *(unsigned int*) p != *(unsigned int*) (v3 + 4)
								    && *(unsigned short*) (*(unsigned int*) (p + 0x168) + 0x27) == *(unsigned short*) v3) {
									++n;
									b = (unsigned char) tmp[2] * 3;
									fcn_004c54c0(*(int*) (v3 + 4), *(int*) p,
									             -((unsigned short) gm_RandomMod(b) + (tmp[2] & 0xff) * 3), 1);
								}
								p += 0x21c;
							} while ((int) p < 0x85a0a4);
							if (n != 0) {
								if ((*(unsigned char*) (v3 + 2) == 6 || *(unsigned char*) (v3 + 2) == 7)) {
									if (!(*(int*) (action + 0xac) != 0)) {
										io_FormatTextBuffer(buf, 0x10bd, *(unsigned short*) v3);
										fcn_00545d40(*(int*) (v3 + 4), -1, buf, 1, 0x5fd, (void*) 0x6b5c60);
									} else {
										io_FormatTextBuffer(buf, 0x10bf, *(unsigned short*) v3);
										fcn_00545d40(*(int*) (v3 + 4), -1, (buf), 1, 0x5fd, (void*) 0x6b5c60);
									}
								}
							}
						}
					}
					r = r + 0x18;
			}
			(*(int*) (action + 0x70))++;
			gm_AddTime((unsigned char*) action + 0x52, 1, 0, 0);
			return;
		}
		he_FreeAction((unsigned char*) action);
	}
}
