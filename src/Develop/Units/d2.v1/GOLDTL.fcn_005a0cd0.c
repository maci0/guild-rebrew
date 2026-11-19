void __cdecl io_FormatTextBuffer(char*, int, ...);
int __cdecl fcn_005373e0(int, int);
void __cdecl d2_SetForm(int, int);
void __cdecl fcn_005a0a40(int);
void __cdecl fcn_005a0ad0(int, unsigned char*);
void __cdecl fcn_005a0be0(int, unsigned char*);
extern volatile int g_6b7fac; extern unsigned short g_774970; extern char g_7f4ca4[];
/* ADDRESS: GOLDTL 0x005a0cd0 */
void __cdecl fcn_005a0cd0(unsigned char* a0, unsigned char* a1, int mode, int windowId, int formId, int duration, int a6)
{
	unsigned int target;
	char buf[256];
	int step;
	unsigned int last;

	step = 2;
	if (a6 == 0) {
		switch (mode) {
		case 1:
			io_FormatTextBuffer(buf, 0x1883, *(int*) a1 + 0x30);
			target = (*(int*) &g_6b7fac) + duration;
			last = (*(int*) &g_6b7fac);
			while (target > (*(volatile int*) &g_6b7fac)) {
				fcn_005373e0(0, 0x777c7);
				if (!*(char*) ((char*) &g_7f4ca4 + (*(unsigned short*) &g_774970) * 0x21c + 4)) {
					break;
				}
				if (last + step < (*(volatile int*) &g_6b7fac)) {
					d2_SetForm(windowId, formId);
					fcn_005a0a40((int) buf);
					step += step / 2;
					last = (*(volatile int*) &g_6b7fac);
				}
			}
			break;
		case 2:
			io_FormatTextBuffer(buf, 0x1884, *(int*) a1 + 0x30, *(int*) (a0 + 4));
			target = (*(int*) &g_6b7fac) + duration;
			last = (*(int*) &g_6b7fac);
			while (target > (*(volatile int*) &g_6b7fac)) {
				fcn_005373e0(0, 0x777c7);
				if (!*(char*) ((char*) &g_7f4ca4 + (*(unsigned short*) &g_774970) * 0x21c + 4)) {
					break;
				}
				if (last + step < (*(volatile int*) &g_6b7fac)) {
					d2_SetForm(windowId, formId);
					fcn_005a0ad0((int) buf, a1);
					step += step / 2;
					last = (*(volatile int*) &g_6b7fac);
				}
			}
			break;
		case 3:
			io_FormatTextBuffer(buf, 0x1885, *(int*) a1 + 0x30, *(int*) (a0 + 4));
			last = (*(int*) &g_6b7fac);
			d2_SetForm(windowId, formId);
			fcn_005a0be0((int) buf, a1);
			target = last + duration;
			while (target > (*(volatile int*) &g_6b7fac)) {
				if (!*(char*) ((char*) &g_7f4ca4 + (*(unsigned short*) &g_774970) * 0x21c + 4)) {
					break;
				}
				fcn_005373e0(0, 0x777c7);
			}
			break;
		case 4:
			io_FormatTextBuffer(buf, 0x1886, *(int*) a1 + 0x30, *(int*) (a0 + 4));
			last = (*(int*) &g_6b7fac);
			d2_SetForm(windowId, formId);
			fcn_005a0be0((int) buf, a1);
			target = last + duration;
			while (target > (*(volatile int*) &g_6b7fac)) {
				if (!*(char*) ((char*) &g_7f4ca4 + (*(unsigned short*) &g_774970) * 0x21c + 4)) {
					break;
				}
				fcn_005373e0(0, 0x777c7);
			}
			break;
		}
	}
	else {
		switch (mode) {
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
		last = (*(int*) &g_6b7fac);
		d2_SetForm(windowId, formId);
		fcn_005a0be0((int) buf, a1);
		target = last + duration;
		while (target > (*(volatile int*) &g_6b7fac)) {
			if (!(*(char*) ((char*) &g_7f4ca4 + (*(unsigned short*) &g_774970) * 0x21c + 4))) {
				break;
			}
			fcn_005373e0(0, 0x777c7);
		}
	}
}
