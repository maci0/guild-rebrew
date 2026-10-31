#include <string.h>

#pragma intrinsic(memcpy, memset, strcpy, strlen)

extern char g_7f4c00[];
extern char g_7f4ca0[];
extern unsigned char g_773d75;
extern char g_6a58ec[];
extern char g_6a6ddc[];
extern char g_6a6dcc[];
extern char g_6a6d78[];
extern char g_6b5c60[];
extern char s_6a6dc4[];
extern char s_6a6a60[];
extern char s_6a6a40[];
extern char s_6a6a4c[];
extern char s_68be9c[];
extern char s_68bea4[];
extern double g_6629f8;
extern double g_665ed0;

char* __cdecl gm_StartFilteredEntitySearch(int, int, int);
char* __cdecl gm_LookupEntityRecordById(int);
void __cdecl fcn_00529160(int, int, unsigned short, int);
void __cdecl fcn_004c5c80(int);
void __cdecl fcn_004c5da0(int, int, int, int, int, char*);
int __cdecl fcn_00529670(int, int);
void __cdecl fcn_00500bb0(void*, int, int, int);
int __cdecl fcn_0055be70(int*);
int __cdecl fcn_004f4f60(int, int, int, int, int);
void __cdecl fcn_004c5ed0(int, char*, int);
unsigned short __cdecl gm_RandomMod(int);
char* __cdecl fcn_005463a0(int, int, int);
int __cdecl fcn_004c4450(int);
int* __cdecl fcn_004c4480(int);
void __cdecl fcn_004c58b0(int, int);
void __cdecl fcn_004c4510(int, int);
void __cdecl fcn_004c4670(int, int, int, int*);
void __cdecl fcn_004c5360(void);
int __cdecl fcn_0050b750(int, unsigned char);
void __cdecl io_FormatTextBuffer(char*, int, ...);
void __cdecl fcn_00545d40(int, int, char*, int, int, char*);
void __cdecl he_MessageBoxQuickjump(unsigned int, int, char*, int, int, int, int, int, char*);
void __cdecl fcn_004c51a0(int, int, unsigned char, int);
float __cdecl fcn_004ff210(int, int);
char* __cdecl gm_SetupEntityQuery(char*);
void __cdecl fcn_004c51f0(int, int, int, int, unsigned char, int);
void __cdecl fcn_00507e30(char*, int);
void __cdecl fcn_0050c5d0(char*, int*);
float __cdecl fcn_0050bb50(int, unsigned char);
int __cdecl fcn_0055c050(char*);
int __cdecl _ftol(void);
int* __cdecl fcn_00502cd0(int, ...);
int* __cdecl gm_NextEntityQueryMatch(void);
char* __cdecl gm_GetEntityTableEntry(char*);
void __cdecl fcn_00546190(char*);
void __cdecl fcn_004c5150(int, int, unsigned char, int);
int __cdecl gm_GetMsgField(int, int*);
int __cdecl fcn_0064d41a(char*, char*, ...);

/* ADDRESS: GOLDTL 0x0056ee80 */
void __cdecl fcn_0056ee80(char* a0)
{
	char msg[0x400];
	char str[0x100];
	char buf[0x200];
	char gestik[3][0x40];
	int req[4];
	int count;
	int rec1;
	int q;
	int h;
	int row;
	int val;
	int ent;
	int i;
	int cnt;

	memcpy(gestik[0], g_6a58ec, 0x16);
	memset(gestik[0] + 0x16, 0, 0x2a);
	memcpy(gestik[1], g_6a6ddc, 0x15);
	memset(gestik[1] + 0x15, 0, 0x2b);
	memcpy(gestik[2], g_6a6dcc, 0x10);
	memset(gestik[2] + 0x10, 0, 0x30);
	i = 0;
	count = 0;
	switch (*(int*) (a0 + 0x70)) {
	case 0:
		rec1 = (int) gm_StartFilteredEntitySearch(1, 1, *(int*) (a0 + 0xac));
		if (rec1 == 0) {
			goto tail;
		}
		for (cnt = 0; cnt < 8; cnt++) {
			if (*(int*) (a0 + 0x8c + cnt * 4) != -1) {
				ent = (int) gm_LookupEntityRecordById(*(int*) (a0 + 0x8c + cnt * 4));
				if (ent != 0) {
					fcn_00529160(rec1, 0, *(unsigned short*) ent, (int) a0);
					fcn_004c5c80(*(int*) (a0 + 0x8c + cnt * 4));
					fcn_004c5da0(*(int*) (a0 + 0x8c + cnt * 4), *(int*) (rec1 + 1), -1, 0, 1, s_6a6dc4);
				}
			}
		}
		*(int*) (a0 + 0x52) = *(int*) g_7f4c00;
		*(int*) (a0 + 0x56) = *(int*) (g_7f4c00 + 4);
		*(int*) (a0 + 0x5a) = *(int*) (g_7f4c00 + 8);
		*(unsigned short*) (a0 + 0x5e) = *(unsigned short*) (g_7f4c00 + 0xc);
		fcn_00500bb0(a0 + 0x52, 0, 4, 0);
		*(int*) (a0 + 0x70) = 1;
		return;
	case 1:
		rec1 = (int) gm_StartFilteredEntitySearch(1, 1, *(int*) (a0 + 0xac));
		i = 0;
		for (;;) {
			if (*(int*) (a0 + 0x8c + i * 4) != -1) {
				ent = (int) gm_LookupEntityRecordById(*(int*) (a0 + 0x8c + i * 4));
				if (ent != 0 && *(int*) (ent + 0x184) != 0 && fcn_00529670(ent, rec1) == 0) {
					break;
				}
			}
			i++;
			if (i >= 8) {
				*(int*) (a0 + 0x52) = *(int*) g_7f4c00;
				*(int*) (a0 + 0x56) = *(int*) (g_7f4c00 + 4);
				*(int*) (a0 + 0x5a) = *(int*) (g_7f4c00 + 8);
				*(unsigned short*) (a0 + 0x5e) = *(unsigned short*) (g_7f4c00 + 0xc);
				fcn_00500bb0(a0 + 0x52, 0, 0, 1);
				*(int*) (a0 + 0x70) = 2;
				return;
			}
		}
		*(int*) (a0 + 0x52) = *(int*) g_7f4c00;
		*(int*) (a0 + 0x56) = *(int*) (g_7f4c00 + 4);
		*(int*) (a0 + 0x5a) = *(int*) (g_7f4c00 + 8);
		*(unsigned short*) (a0 + 0x5e) = *(unsigned short*) (g_7f4c00 + 0xc);
		fcn_00500bb0(a0 + 0x52, 0, 4, 0);
		return;
	case 2:
		rec1 = (int) gm_StartFilteredEntitySearch(1, 1, *(int*) (a0 + 0xac));
		if (rec1 == 0) {
			goto label_1bc;
		}
		row = (int) ((unsigned short) *(unsigned short*) (rec1 + 0x27) * 0x21c + (int) g_7f4ca0);
		req[0] = rec1;
		req[1] = 0x451c4000;
		req[2] = (int) a0;
		req[3] = 0;
		if (fcn_0055be70(req) != 0) {
			h = req[3];
			*(int*) (a0 + 0xb4) = fcn_004f4f60(0x17, 1,
			    *(int*) (g_7f4ca0 + (unsigned short) *(unsigned short*) (a0 + 8) * 0x21c + 4),
			    *(int*) (row + 4), *(int*) (rec1 + 1));
			*(int*) (a0 + 0xb8) = *(int*) (h + 4);
			*(int*) (a0 + 0xbc) = *(int*) (h + 0xb0);
			*(int*) (a0 + 0x70) = 3;
			*(int*) (a0 + 0x52) = *(int*) g_7f4c00;
			*(int*) (a0 + 0x56) = *(int*) (g_7f4c00 + 4);
			*(int*) (a0 + 0x5a) = *(int*) (g_7f4c00 + 8);
			*(unsigned short*) (a0 + 0x5e) = *(unsigned short*) (g_7f4c00 + 0xc);
			return;
		}
label_1bc:
		for (cnt = 0; cnt < 8; cnt++) {
			if (*(int*) (a0 + 0x8c + cnt * 4) != -1) {
				ent = (int) gm_LookupEntityRecordById(*(int*) (a0 + 0x8c + cnt * 4));
				if (ent != 0) {
					fcn_00529160(rec1, 0, *(unsigned short*) ent, (int) a0);
					fcn_004c5c80(*(int*) (a0 + 0x8c + cnt * 4));
					fcn_004c5da0(*(int*) (a0 + 0x8c + cnt * 4), *(int*) (rec1 + 1), -1, 0, 0, s_6a6dc4);
					fcn_004c5ed0(*(int*) (a0 + 0x8c + cnt * 4), gestik[gm_RandomMod(3) & 0xffff], 1);
				}
			}
		}
		*(int*) (a0 + 0x70) = 5;
		*(int*) (a0 + 0x52) = *(int*) g_7f4c00;
		*(int*) (a0 + 0x56) = *(int*) (g_7f4c00 + 4);
		*(int*) (a0 + 0x5a) = *(int*) (g_7f4c00 + 8);
		*(unsigned short*) (a0 + 0x5e) = *(unsigned short*) (g_7f4c00 + 0xc);
		fcn_00500bb0(a0 + 0x52, 0, 0xf, 0);
		return;
	case 3:
		if (*(int*) (a0 + 0xb4) != -1 && fcn_004c4450(*(int*) (a0 + 0xb4)) == 0) {
			return;
		}
		rec1 = (int) gm_StartFilteredEntitySearch(1, 1, *(int*) (a0 + 0xac));
		q = (int) fcn_005463a0(1, 1, *(int*) (a0 + 0xb8));
		if (rec1 != 0 && q != 0 && *(int*) (q + 0xd4) == *(int*) (a0 + 4) && *(int*) (a0 + 0xb4) != -1) {
			ent = (int) gm_LookupEntityRecordById(*(int*) (a0 + 0xb8));
			h = (int) fcn_004c4480(*(int*) (a0 + 0xb4));
			if (ent != 0 && h != 0) {
				fcn_004c58b0(*(int*) h, *(int*) (ent + 4));
			}
			*(int*) (a0 + 0x70) = 4;
			fcn_00500bb0(a0 + 0x52, 0, 10, 0);
			return;
		}
		*(int*) (a0 + 0x70) = -1;
		return;
	case 4:
		q = (int) fcn_005463a0(1, 1, *(int*) (a0 + 0xb8));
		if (q == 0) {
			*(int*) (a0 + 0x70) = -1;
			return;
		}
		if (*(int*) (q + 0xd4) == *(int*) (a0 + 4)) {
			fcn_00500bb0(a0 + 0x52, 0, 6, 0);
			return;
		}
		rec1 = (int) gm_StartFilteredEntitySearch(1, 1, *(int*) (a0 + 0xac));
		if (rec1 != 0) {
			val = (int) gm_LookupEntityRecordById(*(int*) (g_7f4ca0 + (unsigned short) *(unsigned short*) (a0 + 8) * 0x21c + 4));
			row = (int) ((unsigned short) *(unsigned short*) (q + 8) * 0x21c + (int) g_7f4ca0);
			if (row != 0 && val != 0) {
				ent = fcn_0050b750((gm_RandomMod(200) & 0xffff) + 0x226, g_773d75);
				io_FormatTextBuffer(buf, 0x19ea, rec1, ent, *(unsigned short*) row);
				fcn_00545d40(*(int*) (val + 4), *(int*) (val + 4), buf, 1, 0x5f0, s_6a6a60);
				io_FormatTextBuffer(buf, 0x19eb, rec1, ent);
				fcn_004c51a0(*(int*) (row + 4), *(int*) (val + 4), g_773d75, ent);
			}
			q = (int) gm_StartFilteredEntitySearch(1, 1, *(int*) (a0 + 0xbc));
			if (q != 0) {
				fcn_004c4510(q, *(int*) (q + 1));
				fcn_004c4670(4, 1, 0x65, &ent);
				fcn_004c5360();
			}
		}
		for (cnt = 0; cnt < 8; cnt++) {
			if (*(int*) (a0 + 0x8c + cnt * 4) != -1) {
				val = (int) gm_LookupEntityRecordById(*(int*) (a0 + 0x8c + cnt * 4));
				if (val != 0) {
					fcn_004ff210(*(unsigned short*) val, 0xffffff9c - (gm_RandomMod(100) & 0xffff));
				}
			}
		}
		rec1 = (int) gm_StartFilteredEntitySearch(1, 1, *(int*) (a0 + 0xb0));
		if (rec1 == 0) {
			goto tail;
		}
		q = (int) gm_SetupEntityQuery((char*) rec1);
		for (i = 0; i < 8; i++) {
			if (*(int*) (a0 + 0x8c + i * 4) != -1) {
				fcn_004c5c80(*(int*) (a0 + 0x8c + i * 4));
				fcn_004c5da0(*(int*) (a0 + 0x8c + i * 4), *(int*) (rec1 + 1), *(int*) (q + 2), 0, 0, s_6a6a40);
			}
		}
		fcn_00546190(a0);
		return;
	case 5:
		rec1 = (int) gm_StartFilteredEntitySearch(1, 1, *(int*) (a0 + 0xac));
		ent = (int) gm_LookupEntityRecordById(*(int*) (g_7f4ca0 + (unsigned short) *(unsigned short*) (a0 + 8) * 0x21c + 4));
		if (rec1 == 0 || ent == 0) {
			*(int*) (a0 + 0x70) = 0xfffffffe;
			return;
		}
		row = (int) ((unsigned short) *(unsigned short*) (rec1 + 0x27) * 0x21c + (int) g_7f4ca0);
		h = (int) gm_StartFilteredEntitySearch(1, 1, *(int*) (a0 + 0xb0));
		if (h != 0) {
			q = (int) gm_SetupEntityQuery((char*) h);
			i = (int) fcn_00502cd0(*(int*) (h + 0x5d), 2, 6, 0, 0x116);
			cnt = 8;
			do {
				if (*(int*) (a0 + 0x8c + (8 - cnt) * 4) != -1) {
					val = (int) gm_LookupEntityRecordById(*(int*) (a0 + 0x8c + (8 - cnt) * 4));
					if (val != 0) {
						fcn_004c5c80(*(int*) (a0 + 0x8c + (8 - cnt) * 4));
						fcn_004c5da0(*(int*) (a0 + 0x8c + (8 - cnt) * 4), *(int*) (h + 1), *(int*) (q + 2), 0, 0, s_6a6dc4);
						count++;
						fcn_00507e30((char*) val, 2);
						fcn_00529160(h, 0, *(unsigned short*) val, 0);
					}
				}
				cnt--;
			} while (cnt != 0);
			val = 1;
			fcn_004f4f60(0x17, 1,
			    *(int*) (g_7f4ca0 + (unsigned short) *(unsigned short*) (a0 + 8) * 0x21c + 4),
			    *(int*) (row + 4), *(int*) (h + 1));
		} else {
			val = 0;
		}
		if (fcn_0055c050((char*) row) == 0 || val == 0) {
			goto label_fa92;
		}
		msg[0] = g_6b5c60[0];
		memset(msg + 1, 0, 0x3ff);
		rec1 = (int) gm_StartFilteredEntitySearch(1, 1, *(int*) (a0 + 0xac));
		h = (int) fcn_00502cd0(*(int*) (rec1 + 0x5d), 2, 6, 0, 0x2a);
		fcn_0050c5d0((char*) rec1, req);
		val = (int) (*(int*) req * g_665ed0);
		io_FormatTextBuffer(str, 0x68bea4, val);
		strcpy(msg, str);
		fcn_004c5150(*(int*) (ent + 4), *(int*) (row + 4), g_773d75, val);
		fcn_004c4510(rec1, *(int*) (rec1 + 1));
		fcn_004c4670(4, 1, 0x69, &val);
		fcn_004c5360();
		if (h != 0) {
			if (i != 0) {
				q = (int) fcn_00502cd0(*(int*) (h + 0x14), 1, 5);
				while (q != 0) {
					if ((gm_RandomMod(100) & 0xffff) >= 0x33) {
						cnt = gm_GetMsgField(h, (int*) q);
						cnt = (int) (cnt * count * g_6629f8);
						if (cnt <= 0) {
							cnt = 1;
						}
						fcn_0064d41a(str, s_68be9c, cnt, *(int*) (*(int*) q * 8 + 0x14a79c0));
						strcpy(msg, str);
						fcn_004c51f0(*(int*) (i + 2), *(int*) (h + 2), *(int*) q, cnt, g_773d75, strlen(msg));
						val = (int) (fcn_0050bb50(*(int*) q, g_773d75) * cnt + val);
					}
					q = (int) gm_NextEntityQueryMatch();
				}
			} else {
				memcpy(msg, g_6a6d78, 0x4c);
			}
		}
		q = (int) gm_GetEntityTableEntry((char*) ent);
		if (q != 0) {
			*(int*) (q + 0x14) = *(int*) (q + 0x14) + val;
		}
		if (*(char*) (ent + 2) == 6 || *(char*) (ent + 2) == 7) {
			io_FormatTextBuffer(buf, 0x1a85, *(unsigned short*) row, rec1);
			strcpy(msg, buf);
			he_MessageBoxQuickjump(*(int*) (ent + 4), *(int*) (ent + 4), msg, 1, 0x5f0, *(int*) (rec1 + 1), -1, 0, g_6b5c60);
		}
		if (*(char*) (row + 2) == 6 || *(char*) (row + 2) == 7) {
			io_FormatTextBuffer(buf, 0x1a86, rec1, val);
			he_MessageBoxQuickjump(*(int*) (row + 4), *(int*) (row + 4), buf, 0, 0x5f0, *(int*) (rec1 + 1), -1, 0, g_6b5c60);
			fcn_00546190(a0);
			return;
		}
label_fa92:
		rec1 = (int) gm_StartFilteredEntitySearch(1, 1, *(int*) (a0 + 0xac));
		if (rec1 == 0) {
			goto tail;
		}
		if (*(char*) (ent + 2) == 6 || *(char*) (ent + 2) == 7) {
			io_FormatTextBuffer(buf, 0x19e7, *(unsigned short*) row, rec1, 0x19c1);
			he_MessageBoxQuickjump(*(int*) (ent + 4), *(int*) (ent + 4), buf, 1, 0x5f0, *(int*) (rec1 + 1), -1, 0, g_6b5c60);
		}
		if (*(char*) (row + 2) == 6 || *(char*) (row + 2) == 7) {
			io_FormatTextBuffer(buf, 0x19e9, rec1);
			he_MessageBoxQuickjump(*(int*) (row + 4), *(int*) (row + 4), buf, 1, 0x5f0, *(int*) (rec1 + 1), -1, 0, 0);
			fcn_00546190(a0);
			return;
		}
		goto tail;
	case -2:
	case -1:
		h = (int) gm_StartFilteredEntitySearch(1, 1, *(int*) (a0 + 0xb0));
		if (h != 0) {
			q = (int) gm_SetupEntityQuery((char*) h);
		}
		for (i = 0; i < 8; i++) {
			if (*(int*) (a0 + 0x8c + i * 4) != -1) {
				ent = (int) gm_LookupEntityRecordById(*(int*) (a0 + 0x8c + i * 4));
				if (ent != 0) {
					fcn_004c5c80(*(int*) (a0 + 0x8c + i * 4));
					if (h != 0 && q != 0) {
						row = *(int*) (q + 2);
						val = *(int*) (h + 1);
					} else {
						row = -1;
						val = -1;
					}
					fcn_004c5da0(*(int*) (a0 + 0x8c + i * 4), val, row, 0, 0, s_6a6dc4);
					fcn_00529160(0, 0, *(unsigned short*) ent, 0);
				}
			}
		}
		break;
	default:
		return;
	}
tail:
	fcn_00546190(a0);
}
