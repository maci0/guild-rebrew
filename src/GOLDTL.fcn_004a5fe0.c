extern int g_6643d8[];
extern unsigned char* g_entity_ptr;

int __cdecl gm_RandomMod(int a0);
int __cdecl fcn_005cfb00(unsigned short* a0, int* a1, int a2);
float __cdecl fcn_0050f980(unsigned short a0, unsigned short a1, int a2);

/* ADDRESS: GOLDTL 0x004a5fe0 */
int __cdecl fcn_004a5fe0(unsigned short* a0, int a1, int a2, int a3, float a4, float a5, int a6, int* a7)
{
	int flag;
	int step;
	int buf[20];
	int limit;
	int count;
	int ent;
	int i;
	unsigned short idx;
	float f;

	flag = 0;
	step = g_6643d8[(unsigned short) gm_RandomMod(0x10)];
	buf[2] = a2;
	buf[3] = a3 | 0x80000000;
	buf[4] = a1;
	buf[5] = 0;
	if ((a4 > 0.0 || a5 < 100.0) && a4 < a5) {
		flag = 1;
	}
	i = 0x100;
	idx = (unsigned short) gm_RandomMod(0x100);
	limit = a6 & 0xff;
	count = 0;
	if (limit > 0) {
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
			a7[count] = *(int*) (ent + 1);
			count++;
next:
			i--;
			idx = (unsigned short) (idx + step);
		} while (count < limit);
	}
	return count;
}
