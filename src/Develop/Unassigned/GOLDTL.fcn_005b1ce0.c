char* __cdecl fcn_005b1a80(int id);

/* ADDRESS: GOLDTL 0x005b1ce0 */
void __cdecl fcn_005b1ce0(char* a0, int a1, unsigned int a2)
{
	char* p;
	int used;
	int avail;
	int i;
	int idx;
	int cur;
	int delta;
	int step;
	int v;

	p = fcn_005b1a80(*(int*) (a0 + 1));
	avail = 100;
	if (a2 == 0) {
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
	if ((int) (a2 & 0xff) > avail || used < 2) {
		return;
	}
	idx = 0;
	while (idx < 7) {
		if (*(int*) (p + 0xc + idx * 8) == a1 && (unsigned char) a2 != *(unsigned char*) (p + 0x10 + idx * 8)) {
			break;
		}
		idx++;
	}
	if (idx >= 7) {
		return;
	}
	v = *(unsigned char*) (p + 0x10 + idx * 8);
	delta = v - (int) (a2 & 0xff);
	step = v < (int) (a2 & 0xff) ? -1 : 1;
	cur = *(unsigned char*) (p + 8);
	if (delta < 0) {
		delta = -delta;
	}
	while (delta != 0) {
		if (idx != cur && *(int*) (p + 0xc + cur * 8) != 0 && *(unsigned char*) (p + 0x11 + cur * 8) == 0) {
			v = *(unsigned char*) (p + 0x10 + cur * 8);
			if (v + step >= 0 && v + step < avail + 1) {
				delta--;
				*(unsigned char*) (p + 0x10 + cur * 8) = (unsigned char) (v + step);
			}
		}
		cur = (cur + 1) % 7;
	}
	*(unsigned char*) (p + 0x10 + idx * 8) = (unsigned char) a2;
	*(unsigned char*) (p + 8) = (unsigned char) cur;
}
