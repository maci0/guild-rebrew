#include <stdlib.h>

char* __cdecl fcn_005b1a80(int id);

/* ADDRESS: GOLDTL 0x005b1ce0 */
void __cdecl gm_AdjustProductionShare(char* building, int entryKey, unsigned char requestedShare)
{
	char* p;
	int used;
	int avail;
	int i;
	int idx;
	int cur;
	int delta;
	int step;

	p = fcn_005b1a80(*(int*) (building + 1));
	avail = 100;
	if (entryKey == 0) {
		return;
	}
	used = 0;
	for (i = 0; i < 7; i++) {
		if (*(int*) (p + 0xc + i * 8) != 0) {
			used++;
		}
	}
	for (i = 0; i < 7; i++) {
		if (*(int*) (p + 0xc + i * 8) != 0 && *(unsigned char*) (p + 0x11 + i * 8) != 0) {
			avail -= *(unsigned char*) (p + 0x10 + i * 8);
			used--;
		}
	}
	if ((int) requestedShare > avail || used < 2) {
		return;
	}
	for (idx = 0; idx < 7; idx++) {
		if (*(int*) (p + 0xc + idx * 8) == entryKey && requestedShare != *(unsigned char*) (p + 0x10 + idx * 8)) {
			goto found;
		}
	}
	return;
found:
	step = *(unsigned char*) (p + 0x10 + idx * 8) < requestedShare ? -1 : 1;
	delta = abs(*(unsigned char*) (p + 0x10 + idx * 8) - requestedShare);
	cur = *(unsigned char*) (p + 8);
	while (delta != 0) {
		if (idx != cur && *(int*) (p + 0xc + cur * 8) != 0 && *(unsigned char*) (p + 0x11 + cur * 8) == 0) {
			if (*(unsigned char*) (p + 0x10 + cur * 8) + step > -1 && *(unsigned char*) (p + 0x10 + cur * 8) + step < avail + 1) {
				*(unsigned char*) (p + 0x10 + cur * 8) += (unsigned char) step;
				delta--;
			}
		}
		cur = (cur + 1) % 7;
	}
	*(unsigned char*) (p + 0x10 + idx * 8) = requestedShare;
	*(unsigned char*) (p + 8) = (unsigned char) cur;
}
