void __cdecl io_FormatTextBuffer(char*, int, ...);
int __cdecl fcn_005373e0(int, int);
void __cdecl d2_SetForm(int, int);
void __cdecl fcn_005a0a40(int);
void __cdecl fcn_005a0ad0(int, unsigned char*);
void __cdecl fcn_005a0be0(int, unsigned char*);

/* ADDRESS: GOLDTL 0x005a0cd0 */
void __cdecl fcn_005a0cd0(unsigned char* a0, unsigned char* a1, int a2, int a3, int a4, int a5, int a6)
{
	unsigned int target;
	char buf[256];
	int step;
	unsigned int last;

	step = 2;
	if (a6 == 0) {
		switch (a2) {
		case 1:
			io_FormatTextBuffer(buf, 0x1883, *(int*) a1 + 0x30);
			target = (*(volatile int*) 0x6b7fac) + a5;
			last = (*(volatile int*) 0x6b7fac);
			while (target > (*(volatile int*) 0x6b7fac)) {
				fcn_005373e0(0, 0x777c7);
				if (!*(char*) ((char*) 0x7f4ca4 + (*(unsigned short*) 0x774970) * 0x21c + 4)) {
					break;
				}
				if (last + step < (*(volatile int*) 0x6b7fac)) {
					d2_SetForm(a3, a4);
					fcn_005a0a40((int) buf);
					step += step / 2;
					last = (*(volatile int*) 0x6b7fac);
				}
			}
			break;
		case 2:
			io_FormatTextBuffer(buf, 0x1884, *(int*) a1 + 0x30, *(int*) (a0 + 4));
			target = (*(volatile int*) 0x6b7fac) + a5;
			last = (*(volatile int*) 0x6b7fac);
			while (target > (*(volatile int*) 0x6b7fac)) {
				fcn_005373e0(0, 0x777c7);
				if (!*(char*) ((char*) 0x7f4ca4 + (*(unsigned short*) 0x774970) * 0x21c + 4)) {
					break;
				}
				if (last + step < (*(volatile int*) 0x6b7fac)) {
					d2_SetForm(a3, a4);
					fcn_005a0ad0((int) buf, a1);
					step += step / 2;
					last = (*(volatile int*) 0x6b7fac);
				}
			}
			break;
		case 3:
			io_FormatTextBuffer(buf, 0x1885, *(int*) a1 + 0x30, *(int*) (a0 + 4));
			last = (*(volatile int*) 0x6b7fac);
			d2_SetForm(a3, a4);
			fcn_005a0be0((int) buf, a1);
			target = last + a5;
			while (target > (*(volatile int*) 0x6b7fac)) {
				if (!*(char*) ((char*) 0x7f4ca4 + (*(unsigned short*) 0x774970) * 0x21c + 4)) {
					break;
				}
				fcn_005373e0(0, 0x777c7);
			}
			break;
		case 4:
			io_FormatTextBuffer(buf, 0x1886, *(int*) a1 + 0x30, *(int*) (a0 + 4));
			last = (*(volatile int*) 0x6b7fac);
			d2_SetForm(a3, a4);
			fcn_005a0be0((int) buf, a1);
			target = last + a5;
			while (target > (*(volatile int*) 0x6b7fac)) {
				if (!*(char*) ((char*) 0x7f4ca4 + (*(unsigned short*) 0x774970) * 0x21c + 4)) {
					break;
				}
				fcn_005373e0(0, 0x777c7);
			}
			break;
		}
	}
	else {
		switch (a2) {
		case 1:
			io_FormatTextBuffer(buf, 0x1883, *(int*) a1 + 0x30);
			break;
		case 2:
			io_FormatTextBuffer(buf, 0x1884, *(int*) a1 + 0x30, *(int*) (a0 + 4));
			break;
		case 3:
			io_FormatTextBuffer(buf, 0x1885, *(int*) a1 + 0x30, *(int*) (a0 + 4));
			break;
		case 4:
			io_FormatTextBuffer(buf, 0x1886, *(int*) a1 + 0x30, *(int*) (a0 + 4));
			break;
		}
		last = (*(volatile int*) 0x6b7fac);
		d2_SetForm(a3, a4);
		fcn_005a0be0((int) buf, a1);
		target = last + a5;
		while (target > (*(volatile int*) 0x6b7fac)) {
			if (!(*(char*) ((char*) 0x7f4ca4 + (*(unsigned short*) 0x774970) * 0x21c + 4))) {
				break;
			}
			fcn_005373e0(0, 0x777c7);
		}
	}
}
