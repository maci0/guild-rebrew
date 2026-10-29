extern unsigned short g_774970;

int __cdecl fcn_00567030(char* slot, int* out1, int* out2);
void __cdecl cm_RequestChrMoveToUniverse(int h, int a, int b, char* tag);
void __cdecl fcn_004c5ba0(int h, int a, int b, char* tag);

/* ADDRESS: GOLDTL 0x0057f9a0 */
void __cdecl fcn_0057f9a0(int a0)
{
	char* p;
	int idx;
	char* rec;
	char* slot;
	unsigned short key;
	int v1;
	int v2;

	if (a0 != 0) {
		return;
	}
	key = g_774970;
	idx = 0;
	p = (char*) 0x7f4e0c;
	for (;;) {
		rec = *(char**) p;
		if (rec != 0 && *(unsigned short*) (rec + 0x27) == key) {
			break;
		}
		p += 0x21c;
		idx++;
		if ((int) p >= 0x85a20c) {
			return;
		}
	}
	slot = (char*) (0x7f4ca0 + idx * 0x21c);
	if (slot == 0) {
		return;
	}
	if (fcn_00567030(slot, &v1, &v2)) {
		cm_RequestChrMoveToUniverse(*(volatile int*) (slot + 4), v1, v2, (char*) 0x675908);
		fcn_004c5ba0(*(volatile int*) (slot + 4), v1, v2, (char*) 0x6b5c60);
	}
}
