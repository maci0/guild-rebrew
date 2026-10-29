/* Spionage job.  Picks a spy target in the watched house's neighbourhood,
   books the operation and walks it through the spy states until the report
   is delivered.  State 1 scans the residential descriptors for a matching
   house type, state 2 waits for the target, state 3 hands the record over. */

#include "client_types.h"

extern char g_7f4ca0[];
extern char* lpGebaeudePROT;
extern char lpGebaeudeINST[];
extern unsigned char g_773d75;
extern pos14_7f4c00 g_7f4c00;
extern char s_6a6578[];
extern char s_67ed14[];

char* __cdecl fcn_00508e40(int);
float __cdecl fcn_005101e0(unsigned char*, int, int, int);
int __cdecl gm_AccumulateTyped2(char*);
int __cdecl fcn_0050d320(char*, int);
void __cdecl fcn_0051af00(char*, int, ...);
void __cdecl he_MessageBoxQuickjump(int, int, char*, int, int, int, int, int, char*);
void __cdecl fcn_00545d40(int, int, char*, int, int, char*);
void __cdecl fcn_00546190(void*);
void __cdecl fcn_004c51a0(int, int, unsigned char, int);
int __cdecl fcn_004c4450(int);
char* __cdecl fcn_004c4480(int);
int __cdecl fcn_004c5620(int, void*);
void __cdecl fcn_004c57e0(int, int);
void __cdecl fcn_004c5c80(unsigned int);
void __cdecl fcn_004c5da0(int, int, int, int, int, char*);
void __cdecl fcn_00500bb0(void*, int, int, int);
void __cdecl gm_ResolveEntityById(void**, int, int, int);
int __cdecl fcn_00500cb0(void*, void*);
int __cdecl fcn_00529670(void*, void*);
char* __cdecl gm_GetEntityTableEntry(char*);

/* ADDRESS: GOLDTL 0x005624a0 */
void __cdecl fcn_005624a0(char* ctx)
{
	char text[0x400];
	unsigned char* rec;
	unsigned char* ent;
	unsigned char* hit;
	char* house;
	int state;
	int handle;
	int item;
	int mask;
	int mask2;
	int tries;
	int idx;
	unsigned char type;
	int left;

	hit = 0;
	state = *(int*) (ctx + 0x70);
	if (state == -1 || state == -2) {
		if ((*(unsigned char*) (ctx + 0x78) & 2)
		    && *(int*) (ctx + 0xd8) != -1) {
			ent = fcn_00508e40(*(int*) (ctx + 0xd8));
			if (ent != 0) {
				fcn_004c5c80(*(int*) (ent + 4));
				fcn_004c57e0(*(int*) (ent + 4), 1);
			}
		}
		fcn_00546190(ctx);
		return;
	}
	if (*(unsigned char*) (ctx + 0x78) & 4) {
		return;
	}
	handle = *(int*) (ctx + 0x84);
	if (handle != -1 && !fcn_004c4450(handle)) {
		return;
	}
	switch (state) {
	case 0:
		handle = *(int*) (ctx + 0xd8);
		if (handle != -1 && !fcn_004c4450(handle)) {
			return;
		}
		ent = fcn_004c4480(*(int*) (ctx + 0xd8));
		if (ent != 0) {
			house = gm_GetEntityTableEntry(g_7f4ca0
			    + *(unsigned short*) (ctx + 8) * 0x21c);
			item = *(int*) (ctx + 0xe4);
			if (house != 0) {
				*(int*) (house + 0x28) = *(int*) (house + 0x28) + item;
			}
			*(int*) (ctx + 0xd8) = *(int*) (ent + 4);
			fcn_004c51a0(-1, *(int*) (g_7f4ca0
			    + *(unsigned short*) (ctx + 8) * 0x21c + 4), g_773d75, item);
			fcn_00529160(0, 0, *(unsigned short*) ent, ctx);
			*(int*) (ctx + 0x52) = g_7f4c00.a;
			*(int*) (ctx + 0x56) = g_7f4c00.b;
			*(int*) (ctx + 0x5a) = g_7f4c00.c;
			*(unsigned short*) (ctx + 0x5e) = g_7f4c00.d;
			*(int*) (ctx + 0x84) = fcn_004c5620(1, ctx);
			return;
		}
		*(int*) (ctx + 0xd8) = -1;
		*(int*) (ctx + 0x52) = *(int*) (ctx + 0xc8);
		*(int*) (ctx + 0x56) = *(int*) (ctx + 0xcc);
		*(int*) (ctx + 0x5a) = *(int*) (ctx + 0xd0);
		*(unsigned short*) (ctx + 0x5e) = *(unsigned short*) (ctx + 0xd4);
		*(int*) (ctx + 0x84) = fcn_004c5620(4, ctx);
		return;
	case 1:
		idx = *(int*) (ctx + 0xbc);
		tries = 0x100;
		do {
			rec = (unsigned char*) (lpGebaeudeINST + idx * 0xa9);
			mask = 0;
			mask2 = 0;
			type = *(unsigned char*) (lpGebaeudePROT
			    + (unsigned int) *rec * 0x24d);
			if (type >= 0x20) {
				mask2 = 1 << ((type - 0x20) & 0x1f);
			} else {
				mask = 1 << (type & 0x1f);
			}
			if (((mask & 0xa7fcc3a6) || (mask2 & 1))
			    && *(int*) (rec + 1) != *(int*) (ctx + 0xac)) {
				hit = rec;
				break;
			}
			rec = 0;
			tries--;
			idx = (idx + *(int*) (ctx + 0xc0)) & 0xff;
			hit = 0;
		} while (tries != 0);
		idx = (*(int*) (ctx + 0xc0) + idx) & 0xff;
		*(int*) (ctx + 0xbc) = idx;
		if (hit == 0) {
			break;
		}
		fcn_0051af00(text, 0x6a6578, hit);
		ent = fcn_00508e40(*(int*) (ctx + 0xd8));
		if (ent == 0) {
			break;
		}
		fcn_004c5c80(*(int*) (ent + 4));
		fcn_004c5da0(*(int*) (ent + 4), *(int*) (hit + 1), -1, 0, 1, s_67ed14);
		fcn_00500bb0(ctx + 0x52, 0, 5, 0);
		*(int*) (ctx + 0xb4) = *(int*) (hit + 1);
		*(int*) (ctx + 0x84) = fcn_004c5620(2, ctx);
		return;
	case 2:
		gm_ResolveEntityById((void**) &hit, 0, 0, *(int*) (ctx + 0xb4));
		fcn_00500bb0(ctx + 0x52, 0, 5, 0);
		if (hit == 0) {
			*(int*) (ctx + 0x84) = fcn_004c5620(-1, ctx);
			return;
		}
		ent = fcn_00508e40(*(int*) (ctx + 0xd8));
		if (ent == 0) {
			break;
		}
		if (fcn_00529670(ent, hit) == 0) {
			*(int*) (ctx + 0x70) = 2;
			fcn_00500bb0(ctx + 0x52, 0, 5, 0);
			*(int*) (ctx + 0x84) = fcn_004c5620(2, ctx);
			return;
		}
		gm_ResolveEntityById((void**) &hit, 0, 0, *(int*) (ctx + 0xac));
		if (hit != 0 && *(short*) (hit + 0x27) != -1) {
			if (fcn_00500cb0(ctx + 0xc8, &g_7f4c00) == -1) {
				fcn_004c5c80(*(int*) (ent + 4));
				fcn_004c5da0(*(int*) (ent + 4), *(int*) (hit + 1),
				    -1, 0, 1, s_67ed14);
				*(int*) (ctx + 0x84) = fcn_004c5620(3, ctx);
				return;
			}
			*(int*) (ctx + 0x84) = fcn_004c5620(1, ctx);
			return;
		}
		break;
	case 3:
		fcn_00500bb0(ctx + 0x52, 0, 5, 0);
		gm_ResolveEntityById((void**) &hit, 0, 0, *(int*) (ctx + 0xac));
		if (hit != 0 && *(short*) (hit + 0x27) != -1) {
			ent = fcn_00508e40(*(int*) (ctx + 0xd8));
			if (ent != 0 && fcn_00529670(ent, hit) == 0) {
				*(int*) (ctx + 0x70) = 3;
				fcn_00500bb0(ctx + 0x52, 0, 5, 0);
				*(int*) (ctx + 0x84) = fcn_004c5620(3, ctx);
				return;
			}
			rec = fcn_00508e40(*(int*) (ctx + 0xc4));
			if (rec != 0) {
				fcn_0051af00(text, 0x1734, *(unsigned short*) rec);
				fcn_00545d40(*(int*) (g_7f4ca0
				    + *(unsigned short*) (ctx + 8) * 0x21c + 4),
				    -1, text, 0, 0x5fa, 0);
			}
		}
		*(int*) (ctx + 0x84) = fcn_004c5620(-1, ctx);
		return;
	case 4:
		break;
	default:
		return;
	}
	fcn_00500bb0(ctx + 0x52, 0, 1, 0);
	*(int*) (ctx + 0x84) = fcn_004c5620(-1, ctx);
}
