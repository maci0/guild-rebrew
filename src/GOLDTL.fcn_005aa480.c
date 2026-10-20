int __cdecl fcn_0046f740(int, int, int, int);
int __cdecl fcn_00470820(int, int, char*);
void __cdecl fcn_00471b60(int);
void __cdecl fcn_00471e30(int);
void __cdecl fcn_004727a0(int, int);
void __cdecl fcn_00473a90(int, int);
int __cdecl fcn_004eb220(char*);
int __cdecl fcn_004eb3e0(int, int*);
int __cdecl fcn_00519190();
int __cdecl fcn_00525f60(void*, int);
int __cdecl fcn_00526120(void*, int);
void __cdecl fcn_00532ef0(void);
int __cdecl fcn_00533a60(int, int, int*, int, ...);
void __cdecl fcn_005340f0(int);
int __cdecl fcn_005373e0(void*, int);

/* ADDRESS: GOLDTL 0x005aa480 */
void __cdecl fcn_005aa480(void)
{
	int sel[3];
	int pos[7][2] = {
		{0x40, 0x50},
		{0xc0, 0x50},
		{0x140, 0x50},
		{0x1c0, 0x50},
		{0x80, 0xb8},
		{0x100, 0xb8},
		{0x180, 0xb8}
	};
	int pa[5];
	int pb[5];
	int ids[7];
	int cur;
	int i;
	int j;
	int n;
	int h;

	n = fcn_004eb220((char*) (0x7f4ca0 + (unsigned int) *(unsigned short*) 0x774970 * 0x21c));
	if (n != 1) {
		if (n == -1) {
			fcn_00526120((void*) *(int*) 0x14aad38, 0);
			return;
		}
		fcn_00525f60((void*) (0x7f4ca0 + (unsigned int) *(unsigned short*) 0x774970 * 0x21c), 3);
		return;
	}
	h = fcn_00470820(0, 0, "LOCATIONS\\ZUNFTHAUS\\LEVEL1");
	fcn_00471b60(h);
	fcn_00473a90(0, 0);
	fcn_004727a0(h, 0);
	fcn_005340f0(*(int*) 0x772514);
	fcn_004727a0(h, 1);
	fcn_00519190(0x1643);
	fcn_004727a0(h, 2);
	i = 0;
	do {
		n = fcn_0046f740(pos[i][0] - 0x28, pos[i][1] - 0x46, i + 0x5a2, *(int*) 0x772514);
		ids[i] = n;
		i++;
		*(int*) ((char*) *(void**) 0x1015ea0 + n * 0x2f4 + 0x5c) = 1;
	} while (i < 7);
	cur = 0;
	*(int*) ((char*) *(void**) 0x1015ea0 + ids[0] * 0x2f4 + 0x3c) = 1;
	fcn_004727a0(h, 3);
	n = (unsigned int) *(unsigned short*) 0x774970 * 0x21c;
	if (*(char*) (0x7f4ca0 + n + 9) == 0) {
		n = *(unsigned char*) (0x7f4ca0 + n + 0x169) + 0x253;
	} else {
		n = *(unsigned char*) (0x7f4ca0 + n + 0x169) + 0x27b;
	}
	fcn_00519190(0x1644, n, 3, 0x1649);
	fcn_004727a0(h, 4);
	fcn_00533a60(*(int*) 0x772514, 0, sel, 3,
	    *(char**) 0x14aac34, *(char**) 0x14aac38, *(char**) 0x14aac3c);
	*(int*) 0x100f1dc = -1;
	do {
		if (*(int*) 0x14ce8e0 != 0) {
			*(int*) 0x774654 = 1;
		}
		if (*(int*) 0x100f1dc != -1) {
			n = *(int*) 0x67d370;
			if (n == sel[2]) {
				*(int*) 0x774654 = 1;
			} else if (n == sel[0]) {
				pb[0] = 3;
				pb[1] = cur + 1;
				pb[2] = 1;
				fcn_004eb3e0((int) (0x7f4ca0 + (unsigned int) *(unsigned short*) 0x774970 * 0x21c), pb);
				*(int*) 0x774654 = 1;
			} else if (n == sel[1]) {
				pa[0] = 3;
				pa[1] = cur + 1;
				pa[2] = -1;
				fcn_004eb3e0((int) (0x7f4ca0 + (unsigned int) *(unsigned short*) 0x774970 * 0x21c), pa);
				*(int*) 0x774654 = 1;
			} else {
				j = 0;
				do {
					if (n == ids[j] && cur != j) {
						*(int*) ((char*) *(void**) 0x1015ea0 + ids[cur] * 0x2f4 + 0x3c) = 0;
						cur = j;
						*(int*) ((char*) *(void**) 0x1015ea0 + ids[j] * 0x2f4 + 0x3c) = 1;
						fcn_004727a0(h, 3);
						fcn_00519190(0x6811b0);
						n = (unsigned int) *(unsigned short*) 0x774970 * 0x21c;
						if (*(char*) (0x7f4ca0 + n + 9) == 0) {
							n = *(unsigned char*) (0x7f4ca0 + n + 0x169) + 0x253;
						} else {
							n = *(unsigned char*) (0x7f4ca0 + n + 0x169) + 0x27b;
						}
						fcn_00519190(0x1644, n, 3, j + 0x1649);
						break;
					}
					j++;
				} while (j < 7);
			}
		}
	} while (fcn_005373e0((void*) fcn_005aa480, 0x677c7) != 0);
	fcn_00471e30(h);
	fcn_00532ef0();
}
