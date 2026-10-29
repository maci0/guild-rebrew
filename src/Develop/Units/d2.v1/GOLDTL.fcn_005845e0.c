char* __cdecl fcn_00470820(int, int, char*);
void __cdecl fcn_00471b60(char*);
void __cdecl fcn_00471e30(char*);
int __cdecl fcn_00472250(char*, int, char*);
void __cdecl fcn_00472640(int, int);
void __cdecl d2_SetForm(char*, int);
char* __cdecl fcn_00519190(char*, int);
int __cdecl fcn_005373e0(char*, int);

/* ADDRESS: GOLDTL 0x005845e0 */
int __cdecl fcn_005845e0(void)
{
	char* menu;
	char* item;
	int ids[5];
	char* base;
	int i;
	int k;
	int n;
	int index;
	int result;
	int flag;

	menu = fcn_00470820(0, 0, (char*) 0x6a9298);
	fcn_00471b60(menu);
	d2_SetForm(menu, 1);
	fcn_00519190((char*) 0x6a2f5c, 0x3f1a);
	d2_SetForm(menu, 2);
	for (i = 0; i < 5; i++) {
		item = fcn_00519190((char*) 0x681140, 0x3f1b + i);
		item = fcn_00472250(menu, 2, item);
		ids[i] = (int) item;
		index = (int) item;
		base = (char*) *(int*) 0x1015ea0;
		index = index * 0x3c - index;
		index = index * 0xc;
		*(int*) (base + index + 0x58) = 1;
		*(int*) (base + index + 0x38) = *(int*) (0x6a81dc + i * 4);
		*(int*) (base + index + 0x1d0) &= -3;
	}
	item = fcn_00519190((char*) 0x681140, 0x3f20);
	result = (int) fcn_00472250(menu, 2, item);
	item = fcn_00519190((char*) 0x681140, 0x3f21);
	fcn_00472250(menu, 2, item);
	d2_SetForm(menu, 2);
	if (fcn_005373e0((char*) 0x5845e0, 0x86) != 0) {
		do {
			base = (char*) *(int*) 0x1015ea0;
			n = 0;
			for (k = 0; k < 5; k++) {
				index = ids[k];
				index = index * 0x3c - index;
				index = index * 0xc;
				if (*(int*) (base + index + 0x38) != 0) {
					fcn_00472640((char*) result, 1);
					base = (char*) *(int*) 0x1015ea0;
					break;
				}
				n++;
			}
			if (n == 5) {
				fcn_00472640((char*) result, 0);
				base = (char*) *(int*) 0x1015ea0;
			}
			if (*(int*) 0x14ce8e0 != 0 || *(char*) 0x14cf950 == 1 || *(int*) 0x100f1dc == 1) {
				*(int*) 0x774654 = 1;
			}
			if (*(int*) 0x100f1dc != -1) {
				if (*(int*) 0x67d370 == ids[0]) {
					*(int*) 0x774654 = 1;
				} else if (*(int*) 0x67d370 == result) {
					*(int*) 0x774654 = 1;
					n = 0;
					for (k = 0; k < 5; k++) {
						index = ids[k];
						index = index * 0x3c - index;
						index = index * 0xc;
						if (*(int*) (base + index + 0x38) != 0) {
							n++;
							*(int*) (0x6a81dc + k * 4) = 1;
						} else {
							*(int*) (0x6a81dc + k * 4) = 0;
						}
					}
					if (n != 0) {
						flag = 1;
					}
				}
			}
		} while (fcn_005373e0((char*) 0x5845e0, 0x86) != 0);
	}
	fcn_00471e30(menu);
	return result;
}
