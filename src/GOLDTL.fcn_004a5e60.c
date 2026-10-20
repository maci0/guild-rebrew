extern int g_6643d8[];
extern unsigned char* g_entity_ptr;

int __cdecl gm_RandomMod(int a0);
int __cdecl fcn_005cfb00(unsigned short* a0, int* a1, int a2);
float __cdecl fcn_0050f980(unsigned short a0, unsigned short a1, int a2);

/* ADDRESS: GOLDTL 0x004a5e60 */
int __cdecl fcn_004a5e60(unsigned short* a0, int a1, int a2, int a3, float a4, float a5, int* a6)
{
	int buf[20];
	int step;
	int flag;
	int found;
	int ent;
	int i;
	int idx;
	float f;

	step = g_6643d8[(unsigned short) gm_RandomMod(0x10)];
	buf[4] = a2;
	buf[1] = step;
	buf[6] = a1;
	flag = 0;
	buf[5] = 0;
	buf[3] = a3 | 0x80000000;
	*a6 = -1;
	found = 0;
	if ((a4 > 0.0 || a4 < 100.0) && a4 < a5) {
		flag = 1;
	}
	i = 0x100;
	idx = (unsigned short) gm_RandomMod(0x100);
	do {
		if (i == 0) {
			break;
		}
		ent = (int) &g_entity_ptr[idx * 169];
		if (*(char*) ent == 0) {
			goto next;
		}
		if (fcn_005cfb00(a0, buf, ent) == 0) {
			goto next;
		}
		if (flag != 0) {
			f = fcn_0050f980(*(unsigned short*) (ent + 0x27), *a0, 1);
			if (!(f >= *(float*) (buf + 0x11) && f <= *(float*) (buf + 0x11))) {
				goto next;
			}
		}
		*a6 = *(int*) (ent + 1);
		found = 1;
next:
		i--;
		idx = (idx + step) % 256;
	} while (found == 0);
	return found;
}
