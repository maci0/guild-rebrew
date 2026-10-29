int __cdecl fcn_00443bf0(float, float, int, int);
int __cdecl fcn_00442c00(int, int);
int __cdecl fcn_0045bad0(int, int, int, int*, int*);
float __cdecl fcn_0045b920(int, int, int, char*);
int __cdecl fcn_004cef70(int, int);
int* __cdecl fcn_004ce610(int);
int __cdecl fcn_0064f170(char*, char*, int);
int __cdecl strncmp(char*, char*, unsigned int);

/* ADDRESS: GOLDTL 0x004d06d0 */
void __cdecl fcn_004d06d0(void)
{
	int ids[3];
	char buf[4];
	char* obj;
	int* rec;
	unsigned int v4;
	int i;
	int count;
	int x;
	int y;
	int kind;
	int same;
	unsigned short code;

	v4 = *(unsigned int*) (*(int*) 0x67a370 + 0xb0);
	count = 0;
	code = 0x23;
	i = 0;
	*(int*) 0x7746a4 = 0;
	*(int*) 0x7725c4 = 0;
	if (1 <= *(short*) 0x14ce8c0 && *(short*) 0x14ce8c0 < *(int*) 0x1040494
		&& 1 <= *(short*) 0x14ce8c2 && *(short*) 0x14ce8c2 < *(int*) 0x1040490
		&& *(int*) 0x67d370 == -1) {
		x = *(short*) 0x14ce8c0;
		y = *(short*) 0x14ce8c2;
		*(int*) 0x7746a4 = fcn_00443bf0((float) x, (float) y, 0x40, 1);
		if (*(int*) 0x7746a4 != 0) {
			/* object spawned */
		}
		else if (*(int*) 0x772eb8 != 0) {
			if (*(int*) 0x772ea0 != 0) {
				fcn_00442c00(*(int*) 0x772ea0, 0);
			}
		}
		else if ((fcn_0045bad0(v4, x + 0x1a, y + 0x1a, &ids[0], &ids[1]) & 0xff) != 0xffffffff) {
			fcn_0045b920(v4, ids[0], ids[1], buf);
			*(float*) 0x7725c8 = *(float*) 0x7725c8 + *(float*) 0x6640cc;
			*(int*) 0x7725c4 = 0;
		}
		if (*(int*) 0x7746a4 != 0) {
			for (rec = (int*) 0x7e4260; rec < (int*) 0x7e42dc; rec++) {
				i = *rec;
				if (i != 0 && *(char*) (i + 0x188) != 0) {
					if ((fcn_004cef70(*(unsigned short*) 0x772f24, i) & 0x800) != 0
						&& *(int*) 0x14cf736 == 0) {
						kind = 0;
						rec = fcn_004ce610(i);
						if (rec != 0) {
							switch (*rec) {
							case 0x160: code = 0x18; break;
							case 0x174: code = 0x19; break;
							case 0x16e: code = 0x1e; break;
							case 0x154: code = 0x1a; break;
							case 0x158: code = 0x1f; break;
							case 0x15e: code = 0x21; break;
							case 0x156: code = 0x23; break;
							case 0x176: code = 0x25; break;
							default: break;
							}
						}
						count += 1;
					}
				}
			}
			if (2 <= count) {
				code = 0x23;
			}
			if (*(int*) 0x7746a4 == 0 || *(int*) 0x67d370 != -1) {
				*(int*) 0x7725c4 = 0;
				return;
			}
			obj = (char*) *(int*) 0x7746a4;
			if (strncmp(obj, (char*) 0x68b82c, 10) == 0 && count != 0) {
				*(int*) 0x7725c4 = 0x1c;
				*(int*) 0x772e90 = (int) *(int*) 0x7746a4;
				return;
			}
			if (fcn_0064f170((char*) *(int*) 0x7746a4, (char*) 0x68b820, 10) == 0 && count != 0) {
				*(int*) 0x7725c4 = 0x1b;
				*(int*) 0x772e90 = (int) *(int*) 0x7746a4;
				return;
			}
			if (fcn_0064f170((char*) *(int*) 0x7746a4, (char*) 0x68b818, 4) == 0 && count != 0) {
				*(int*) 0x7725c4 = 0xe;
				*(int*) 0x772e90 = (int) *(int*) 0x7746a4;
				return;
			}
			if (*(int*) (*(int*) 0x7746a4 + 0x220) == 2 && count != 0) {
				v4 = *(unsigned int*) (*(int*) 0x7746a4 + 0x204);
				if ((fcn_004cef70(*(unsigned short*) 0x772f24, v4) & 0x800) != 0
					&& *(int*) 0x14cf736 == 0) {
					*(int*) 0x7725c4 = code;
					*(int*) 0x772e90 = (int) *(int*) 0x7746a4;
					return;
				}
			}
			else {
				*(int*) 0x7725c4 = 0;
			}
			*(int*) 0x772e90 = (int) *(int*) 0x7746a4;
			return;
		}
	}
	*(int*) 0x772e90 = 0;
	*(int*) 0x7746b4 = 0;
}
