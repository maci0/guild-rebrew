


/* The T&L build of fcn_004ffd90 (SERVER 0x100151e0). The
 * Processor Pack code generator needs the weight test spelled as
 * !(f < w) to emit the reference's test ah,5 / jnp. */

#define SIM_ENT_OFF(i) (((i) & 0xffff) * 0x21c)

extern char g_7f4ca0[];

int __cdecl gm_RandomMod(unsigned short range);
int __cdecl fcn_0050a7e0(int a, int b, int c, int d, int e, int f, int g, int h);

unsigned short __cdecl fcn_004ffd90(unsigned int param)
{
	int weights[6];
	unsigned int off;
	unsigned int rnd;
	unsigned int count;
	unsigned short parentA;
	unsigned short parentB;
	int i;
	int j = 0;
	int k;
	float f1;
	float f2;

	weights[0] = 0x60;
	weights[1] = 0x4b;
	weights[2] = 0x28;
	weights[3] = 0x17;
	weights[4] = 9;
	weights[5] = 0;
	i = 0x300;
	for (; j < 0x10; j++) {
		rnd = gm_RandomMod(i);
		parentA = rnd;
		off = SIM_ENT_OFF(rnd);
		if (*(unsigned short*) &((unsigned char*)g_7f4ca0)[off] == 0xffff) {
			i = i * 3 / 4;
			continue;
		}
		f1 = (float) *(unsigned short*) &((unsigned char*)g_7f4ca0)[off + 0xa];
		if (((unsigned char*)g_7f4ca0)[off + 0x2] < 6 && !(f1 < *(float*) &((unsigned char*)g_7f4ca0)[off + 0x20]) &&
		    ((unsigned char*)g_7f4ca0)[off + 0x8] != 0) {
			count = 0;
			for (k = 0; k < 5; k++) {
				if (((int*) &((unsigned char*)g_7f4ca0)[off + 0x68])[k] != -1) {
					count++;
				}
			}
			if ((int) ((gm_RandomMod(0x100) & 0xffff) + 1) < weights[count]) {
				goto done1;
			}
		} else {
			parentA = 0xffff;
		}
	}
done1:
	if (parentA == 0xffff) {
		return 0;
	}

	for (j = 0; j < 0x10; j++) {
		rnd = gm_RandomMod(i);
		parentB = rnd;
		off = SIM_ENT_OFF(rnd);
		if (*(unsigned short*) &((unsigned char*)g_7f4ca0)[off] == 0xffff) {
			i = i * 3 / 4;
			continue;
		}
		f2 = (float) *(unsigned short*) &((unsigned char*)g_7f4ca0)[off + 0xa];
		if (((unsigned char*)g_7f4ca0)[off + 0x2] < 6 && !(f2 < *(float*) &((unsigned char*)g_7f4ca0)[off + 0x20]) &&
		    ((unsigned char*)g_7f4ca0)[off + 0x8] != 0) {
			count = 0;
			for (k = 0; k < 5; k++) {
				if (((int*) &((unsigned char*)g_7f4ca0)[off + 0x68])[k] != -1) {
					count++;
				}
			}
			if ((int) ((gm_RandomMod(0x100) & 0xffff) + 1) < weights[count]) {
				goto done2;
			}
		} else {
			parentB = 0xffff;
		}
	}
done2:
	if (parentB == 0xffff) {
		return 0;
	}

	return (unsigned short) fcn_0050a7e0(
		0,
		*(int*) &((unsigned char*)g_7f4ca0)[SIM_ENT_OFF(parentA) + 0x4],
		*(int*) &((unsigned char*)g_7f4ca0)[SIM_ENT_OFF(parentB) + 0x4],
		(int) param,
		0, 0, 0, 2);
}
