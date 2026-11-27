


#include <string.h>

// SIZE 0x21c
struct house {
	unsigned short id;
	unsigned char type;
	char pad3;
	int owner;
	char pad8[0x78];
	unsigned char mood[5];
	char pad85[0x197];
};

void __cdecl cm_RequestModifyEntityLevel(int, int, int);
void __cdecl io_FormatTextBuffer(char*, int, ...);
int __cdecl he_PostEntityMessage(int, int, char*, unsigned char, int, char*);

void __cdecl he_SwapZigeunerMoods(struct house* a, struct house* b)
{
	char name[0x64];
	char text1[0x400];
	char text2[0x400];
	int i;
	int hi;
	int lo;
	int hii;
	int loi;
	int id;

	lo = 0xff;
	hi = -1;
	loi = -1;
	hii = -1;
	for (i = 0; i < 5; i++) {
		if (b->mood[i] > hi) {
			hi = b->mood[i];
			hii = i;
		}
		if (b->mood[i] < lo) {
			lo = b->mood[i];
			loi = i;
		}
	}
	if (loi == hii || loi <= -1 || hii <= -1) {
		return;
	}
	cm_RequestModifyEntityLevel(b->owner, loi, hi - lo);
	cm_RequestModifyEntityLevel(b->owner, hii, lo - hi);
	if (b == a) {
		id = 0x41dd;
		strcpy(name, "_NACHRICHTEN_ZIGEUNER_02");
	} else {
		id = 0x41dc;
		strcpy(name, "_NACHRICHTEN_ZIGEUNER_01");
	}
	io_FormatTextBuffer(text1, 0x41e1, loi + 0x16b7, hii + 0x16b7);
	io_FormatTextBuffer(text2, id, text1);
	he_PostEntityMessage(b->owner, -1, text2, 1, 0x5fb, name);
}
