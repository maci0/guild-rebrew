extern int g_7f4c00;
extern int g_7f4c04;
extern int g_7f4c08;
extern short g_7f4c0c;
extern short g_aed32c;

int __cdecl fcn_005bdc30(int a, int* dlg, char* txt, int c, int d);
void __cdecl io_FormatTextBuffer(char* buf, int fmt, ...);
void __cdecl fcn_004c5530(char* msg);
void __cdecl fcn_004c4510(int a, int b);
void __cdecl fcn_004c4570(int a, int b, int c, int d);
void __cdecl fcn_004c5360(void);
void __cdecl fcn_00508280(char* slot, int a, int b);
int __cdecl fcn_005c6270(char* slot, int mode);
float __cdecl fcn_0042e450();
int __cdecl fcn_00503fe0(int a, int b, int c);
void __cdecl fcn_00545d40(int a, int b, char* buf, int c, int d, int e);

/* Handles the two result kinds of a diebesgilde spionage dialog: report the
 * outcome packet and tear the slot down. Native body: 869 bytes. */
/* ADDRESS: GOLDTL 0x005dc270 */
int __cdecl fcn_005dc270(char* cmd, char* arg2)
{
	int dlg[0x14];
	char txt[0x110];
	char msg[0xf8];
	char line[0x7f0];
	char* esi;
	char* slot;
	short h;
	int i;

	if ((unsigned char) cmd[2] == 6) {
		memset(dlg, 0, 0x50);
		for (i = 7; i < 15; i++) {
			dlg[i] = -1;
		}
		dlg[0] = 1;
		dlg[1] = -1;
		dlg[2] = 4;
		dlg[4] = 6;
		io_FormatTextBuffer(txt, 0x9a);
		esi = (char*) fcn_005bdc30(1, dlg, txt, 0, 0);
		if (esi == 0 || *(short*) (esi + 0x27) == 0) {
			return 0;
		}
		msg[4] = 0x76;
		*(int*) (msg + 8) = *(int*) (cmd + 4);
		*(int*) (msg + 0xc) = -1;
		*(int*) (msg + 0x28) = g_7f4c00;
		*(int*) (msg + 0x2c) = g_7f4c04;
		*(int*) (msg + 0x30) = g_7f4c08;
		*(short*) (msg + 0x34) = g_7f4c0c;
		msg[0x36] = 0xa;
		*(int*) (msg + 0x58) = *(int*) (esi + 1);
		*(short*) (msg + 0x6e) = 0x177;
		fcn_004c5530(msg);
		fcn_004c4510(*(int*) arg2, *(int*) (*(int*) arg2 + 2));
		h = *(short*) arg2;
		fcn_004c4570(4, 1, h - g_aed32c + 0x25, (int) (esi + 1));
		fcn_004c5360();
		slot = (char*) (0x7f4ca0 + *(unsigned short*) (esi + 0x27) * 0x21c);
		fcn_00508280(slot, 0, 0);
		if (slot[2] == 6 || slot[2] == 7) {
			io_FormatTextBuffer(line, 0xff1);
			fcn_00545d40(*(int*) (slot + 4), -1, line, 0, 0x5fb, 0);
		}
		return 1;
	}
	esi = (char*) fcn_00503fe0(1, 1, *(int*) (arg2 + 4));
	if (esi == 0 || *(short*) (esi + 0x27) == 0) {
		return 0;
	}
	msg[4] = 0x76;
	*(int*) (msg + 8) = *(int*) (cmd + 4);
	*(int*) (msg + 0xc) = -1;
	*(int*) (msg + 0x28) = g_7f4c00;
	*(int*) (msg + 0x2c) = g_7f4c04;
	*(int*) (msg + 0x30) = g_7f4c08;
	*(short*) (msg + 0x34) = g_7f4c0c;
	msg[0x36] = 0xa;
	*(int*) (msg + 0x58) = *(int*) (esi + 1);
	*(short*) (msg + 0x6e) = 0x177;
	fcn_004c5530(msg);
	fcn_004c4510(*(int*) arg2, *(int*) (*(int*) arg2 + 2));
	h = *(short*) arg2;
	fcn_004c4570(4, 1, h - g_aed32c + 0x25, (int) (esi + 1));
	fcn_004c5360();
	slot = (char*) (0x7f4ca0 + *(unsigned short*) (esi + 0x27) * 0x21c);
	if (fcn_005c6270(slot, 0x2c4) == 0 || 0.75f < fcn_0042e450()) {
		fcn_00508280(slot, 0, 0);
	}
	if (slot[2] == 6 || slot[2] == 7) {
		io_FormatTextBuffer(line, 0xff1);
		fcn_00545d40(*(int*) (slot + 4), -1, line, 0, 0x5fb, 0);
	}
	return 1;
}
