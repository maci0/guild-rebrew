/* Resident-capacity message job.  A four-state machine: wait for the clock,
   book the move-in, wait for the booking to be accepted, then take one
   resident out of the house counters and report the result. */

#include "client_types.h"

extern char g_7f4ca0[];
extern int g_7f4ca4;
extern unsigned char g_773d75;
extern pos14_7f4c00 g_7f4c00;
extern char s_675908[];
extern char s_6a625c[];
extern char s_6a5b54[];

int __cdecl fcn_00500cb0(void*, void*);
void __cdecl fcn_00500bb0(void*, int, int, int);
char* __cdecl gm_StartFilteredEntitySearch(int, int, int);
float __cdecl fcn_005101e0(unsigned char*, int, int, int);
int __cdecl gm_AccumulateTyped2(char*);
int __cdecl fcn_0050d320(char*, int);
void __cdecl io_FormatTextBuffer(char*, int, ...);
void __cdecl he_MessageBoxQuickjump(int, int, char*, int, int, int, int, int, char*);
void __cdecl fcn_00545d40(int, int, char*, int, int, char*);
void __cdecl fcn_00546190(void*);
int __cdecl fcn_004c4450(int);
char* __cdecl fcn_004c4480(int);
int __cdecl fcn_004c6090(unsigned char*, int, int, int);
void __cdecl cm_RequestChrMoveToUniverse(int, int, int, char*);
void __cdecl fcn_004c51a0(int, int, unsigned char, int);
char* __cdecl fcn_005049a0(char*);
int __cdecl gm_LookupEntityRecordById(int);
char* __cdecl fcn_0050dc90(char*);
char* __cdecl gm_GetEntityTableEntry(char*);
int __cdecl gm_RandomMod(int);

/* ADDRESS: GOLDTL 0x0055c740 */
void __cdecl fcn_0055c740(char* ctx)
{
	char text[0x400];
	char* rec;
	char* ent;
	char* h;
	unsigned short* obj;
	unsigned short bank;
	unsigned char kind;
	int state;
	int ver;
	int i;
	int pri;

	state = *(int*) (ctx + 0x70);
	switch (state) {
	case 0:
		*(int*) (ctx + 0x70) = state + 1;
		return;
	case 1:
		if (fcn_00500cb0(ctx + 0x52, &g_7f4c00) >= 0) {
			return;
		}
		rec = gm_StartFilteredEntitySearch(1, 1, *(int*) (ctx + 0x10));
		if (rec == 0) {
			break;
		}
		bank = *(unsigned short*) (rec + 0x27);
		ver = (int) fcn_005101e0((unsigned char*) (g_7f4ca0 + bank * 0x21c),
		    *rec, -1, 1);
		if (gm_AccumulateTyped2(g_7f4ca0 + *(unsigned short*) (rec + 0x27) * 0x21c) < ver) {
			io_FormatTextBuffer(text, 0x1a40, rec);
			he_MessageBoxQuickjump(*(int*) (g_7f4ca0 + bank * 0x21c + 4),
			    *(int*) (ctx + 0x10), text, 0, 0x5f2, *(int*) (rec + 1),
			    *(int*) (ctx + 0xe0), 0, 0);
			fcn_00546190(ctx);
			return;
		}
		for (i = 0; i < 0xc; i++) {
			if (*(int*) (ctx + 0xb0 + i * 4) > 0) {
				kind = *(unsigned char*) (ctx + 0xac);
				*(int*) (ctx + 0xe4) = fcn_004c6090((unsigned char*) rec,
				    0, kind, 0);
				*(int*) (ctx + 0x52) = g_7f4c00.a;
				*(int*) (ctx + 0x56) = g_7f4c00.b;
				*(int*) (ctx + 0x5a) = g_7f4c00.c;
				*(unsigned short*) (ctx + 0x5e) = g_7f4c00.d;
				fcn_00500bb0(ctx + 0x52, 0, 0, 1);
				*(int*) (ctx + 0x70) = *(int*) (ctx + 0x70) + 1;
				return;
			}
		}
		break;
	case 2:
		ver = *(int*) (ctx + 0xe4);
		if (ver == -1) {
			return;
		}
		if (!fcn_004c4450(ver)) {
			return;
		}
		ent = fcn_004c4480(*(int*) (ctx + 0xe4));
		if (ent == 0) {
			fcn_00545d40(*(int*) (g_7f4ca0
			    + *(unsigned short*) (ctx + 8) * 0x21c + 4),
			    -1, s_6a625c, 0, 0x5f2, 0);
			fcn_00546190(ctx);
			return;
		}
		*(int*) (ctx + 0xe8) = *(int*) (ent + 4);
		rec = gm_StartFilteredEntitySearch(1, 1, *(int*) (ctx + 0x10));
		if (rec == 0) {
			break;
		}
		if (*(int*) (ctx + 0xe0) == -1) {
			h = fcn_005049a0(rec);
			if (h != 0) {
				*(int*) (ctx + 0xe0) = *(int*) (h + 2);
			}
		}
		cm_RequestChrMoveToUniverse(*(int*) (ctx + 0xe8), *(int*) (ctx + 0x10),
		    *(int*) (ctx + 0xe0), s_675908);
		*(int*) (ctx + 0x70) = 3;
		*(int*) (ctx + 0x52) = g_7f4c00.a;
		*(int*) (ctx + 0x56) = g_7f4c00.b;
		*(int*) (ctx + 0x5a) = g_7f4c00.c;
		*(unsigned short*) (ctx + 0x5e) = g_7f4c00.d;
		fcn_00500bb0(ctx + 0x52, 0, 0, 1);
		return;
	case 3:
		rec = gm_StartFilteredEntitySearch(1, 1, *(int*) (ctx + 0x10));
		if (rec == 0) {
			break;
		}
		obj = (unsigned short*) gm_LookupEntityRecordById(*(int*) (ctx + 0xe8));
		for (i = 0; i < 0xc; i++) {
			if (obj == 0 || *(int*) (ctx + 0xb0 + i * 4) <= 0) {
				continue;
			}
			ver = (int) fcn_005101e0((unsigned char*) (g_7f4ca0
			    + *(unsigned short*) (rec + 0x27) * 0x21c), *rec, -1, 1);
			*(int*) (ctx + 0xb0 + i * 4) = *(int*) (ctx + 0xb0 + i * 4) - 1;
			bank = *(unsigned short*) (ctx + 8);
			kind = *(unsigned char*) (g_7f4ca0 + bank * 0x21c + 2);
			if (kind == 6 || kind == 7) {
				h = fcn_0050dc90(rec);
				io_FormatTextBuffer(text, 0x1bab, ver, *obj, rec);
				if (h != 0 && (*(unsigned char*) (h + 0x1b4) & 1)) {
					pri = 0x60c;
				} else {
					pri = 0x5f2;
				}
				he_MessageBoxQuickjump(*(int*) (g_7f4ca0 + bank * 0x21c + 4),
				    *(int*) (rec + 1), text, 0, pri, *(int*) (rec + 1),
				    *(int*) (ctx + 0xe0), 0, s_6a5b54);
			}
			fcn_004c51a0(*(int*) (obj + 2),
			    *(int*) (g_7f4ca0 + bank * 0x21c + 4), g_773d75, ver);
			h = gm_GetEntityTableEntry((char*) (g_7f4ca0 + bank * 0x21c));
			if (h != 0) {
				*(int*) (h + 0x4c) = *(int*) (h + 0x4c) + ver;
			}
			break;
		}
		for (i = 0; i < 0xc; i++) {
			if (*(int*) (ctx + 0xb0 + i * 4) > 0) {
				break;
			}
		}
		if (i >= 0xc) {
			fcn_00546190(ctx);
			return;
		}
		*(int*) (ctx + 0x52) = g_7f4c00.a;
		*(int*) (ctx + 0x56) = g_7f4c00.b;
		*(int*) (ctx + 0x5a) = g_7f4c00.c;
		*(unsigned short*) (ctx + 0x5e) = g_7f4c00.d;
		fcn_00500bb0(ctx + 0x52, 0, (gm_RandomMod(10) & 0xffff) + 0x1e, 0);
		*(int*) (ctx + 0x70) = 1;
		return;
	case -2:
	case -1:
		break;
	default:
		return;
	}
	fcn_00546190(ctx);
}
