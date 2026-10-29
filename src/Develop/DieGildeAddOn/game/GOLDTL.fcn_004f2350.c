#include <string.h>

extern char* lpGebaeudePROT;
extern char* g_773da8;
extern int g_6652f8[];
extern int g_7f4c00;
extern char g_7f4ca0[];

void __cdecl gm_ResolveEntityById(void**, void**, void**, int);
int __cdecl gv_CheckSlotActive(int, int);
void* __cdecl gv_GetSlotEntry(int, int, char);

/* ADDRESS: GOLDTL 0x004f2350 */
int __cdecl fcn_004f2350(int e)
{
	char* p;
	char* q;
	char* ent;
	char* slot;
	int* base;
	int* cur;
	int* best;
	int i;
	int n;
	int kind;

	gm_ResolveEntityById((void**) &p, 0, 0, *(int*) (e + 8));
	if (p == 0 || *(unsigned short*) (p + 0x27) == 0xffff
		|| g_7f4ca0 + *(unsigned short*) (p + 0x27) * 0x21c == g_773da8) {
		return -1;
	}
	kind = *(unsigned char*) p;
	if (lpGebaeudePROT[kind * 0x24d] != 0x1d) {
		return -2;
	}
	ent = *(char**) (p + 0x65);
	if (ent == 0) {
		return -3;
	}
	if (gv_CheckSlotActive((int) ent, *(int*) (e + 0xc)) == 0) {
		return -4;
	}
	gm_ResolveEntityById(0, 0, (void**) &q, *(int*) (e + 4));
	if (q == 0) {
		return -6;
	}
	slot = (char*) gv_GetSlotEntry((int) ent, *(int*) (e + 0xc), *(char*) (e + 0x10));
	if (slot == 0) {
		return -7;
	}
	if (*(short*) (slot + 8) != *(short*) (q + 0x50)) {
		return -7;
	}
	n = g_6652f8[*(int*) (e + 0xc)];
	base = *(int**) (slot + 0x10);
	best = base;
	cur = base;
	for (i = 0; i < n; i++) {
		if (*best == -1) {
			break;
		}
		if (*cur == -1) {
			best = base + i * 0x11;
			break;
		}
		if (best[0x10] > cur[0x10]) {
			best = cur;
		}
		cur += 0x11;
	}
	*best = *(int*) (q + 4);
	strcpy((char*) best + 4, q + 0x30);
	strcpy((char*) best + 0x14, q + 0x40);
	*(int*) ((char*) best + 0x24) = *(int*) (q + 0x80);
	*(unsigned char*) ((char*) best + 0x28) = *(unsigned char*) (q + 0x84);
	*(int*) ((char*) best + 0x2c) = *(unsigned char*) (q + 0x167);
	*(int*) ((char*) best + 0x30) = *(unsigned char*) (q + 0xd);
	*(int*) ((char*) best + 0x34) = *(unsigned char*) (q + 0x164);
	*(int*) ((char*) best + 0x38) = *(unsigned char*) (q + 9);
	*(int*) ((char*) best + 0x40) = g_7f4c00;
	*(int*) ((char*) best + 0x3c) = *(int*) (q + 0x18c);
	return 0;
}
