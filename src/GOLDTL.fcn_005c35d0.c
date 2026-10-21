/* Dialog message loop for 0x6ac5d8: validates the click id through
   fcn_00504f30, shows the dialog, then forwards the 0x39 packet to
   fcn_004c5530 while fcn_005373e0 keeps the loop alive. */

int __cdecl fcn_00504f30(int, int);
int __cdecl fcn_00526120(int, int);
void* __cdecl fcn_00470820(int, int, char*);
void __cdecl fcn_00471b60(void*);
void __cdecl fcn_00471e30(void*);
int __cdecl fcn_0050cf50(char*, signed char);
int __cdecl fcn_0050b710(int, char);
int __cdecl fcn_004727a0(void*, int);
int __cdecl fcn_00519190(int, ...);
int __cdecl fcn_00472250(void*, int, int);
void __cdecl fcn_00472380(int, int, int, int);
void __cdecl fcn_00473a90(int, int);
int __cdecl fcn_005373e0(void*, int);
int __cdecl fcn_00504e70(int);
int __cdecl fcn_0050b750(int, char);
int __cdecl fcn_00471f80(int, char);
int __cdecl fcn_00526010(char*, int);
void __cdecl fcn_004c5530(void*);
void __cdecl fcn_004c5420(int, int, int, int, int);

/* ADDRESS: GOLDTL 0x005c35d0 */
void __cdecl fcn_005c35d0(char* e)
{
	char pkt[0xf4];
	int w;
	int ctl;
	int x;
	int y;
	void* dlg;

	if (fcn_00504f30(*(unsigned char*) e, *(unsigned short*) 0x774970) != 1) {
		fcn_00526120(*(int*) 0x14ab29c, 0);
		return;
	}
	dlg = fcn_00470820(0, 0, (char*) 0x6ac5d8);
	fcn_00471b60(dlg);
	x = fcn_0050cf50(e, *(signed char*) (e + 0x5c));
	w = fcn_0050b710(x, *(unsigned char*) 0x773d75);
	fcn_004727a0(dlg, 2);
	ctl = fcn_00472250(dlg, 2,
	                   fcn_00519190(0x17de, *(unsigned short*) (e + 0x25), e,
	                                *(unsigned char*) 0x773d75));
	x = (int) ((double) w * *(double*) 0x662aa0);
	y = (int) ((double) x * *(double*) 0x662908);
	fcn_00472380(ctl, y, x, w);
	fcn_00473a90(0, 0);
	fcn_005373e0(0, 0x677c7);
	do {
		x = fcn_00504e70(w);
		if ((*(unsigned char*) (e + 0x5b) & 4) != 0 || x == 0) {
			*(int*) 0x774654 = 1;
		}
		if (*(int*) 0x14ce8e0 != 0) {
			*(int*) 0x774654 = 1;
		}
		if (*(int*) 0x100f1dc == 2) {
			x = fcn_0050b750(
			    fcn_00471f80(ctl, *(unsigned char*) 0x773d75),
			    *(unsigned char*) 0x773d75);
			if (fcn_00526010((char*) (0x7f4ca0 +
			                          *(unsigned short*) 0x774970 * 0x21c),
			                 x)) {
				*(char*) (pkt + 4) = 0x21;
				*(int*) (pkt + 8) = *(int*) (0x7f4ca4 +
				                             *(unsigned short*) 0x774970 * 0x21c);
				*(int*) (pkt + 0xc) = -1;
				*(char*) (pkt + 0x36) = 9;
				*(int*) (pkt + 0x58) = *(int*) (e + 1);
				*(int*) (pkt + 0x5c) = fcn_0050b750(
				    fcn_00471f80(ctl, *(unsigned char*) 0x773d75),
				    *(unsigned char*) 0x773d75);
				*(int*) (pkt + 0x60) = *(int*) (0x7f4ca4 +
				                                *(unsigned short*) 0x774970 * 0x21c);
				fcn_004c5530(pkt);
				fcn_004c5420(*(int*) (e + 1), 0x5a, 2, 0x200, 0);
			}
			*(int*) 0x774654 = 1;
		} else if (*(int*) 0x100f1dc == 1) {
			*(int*) 0x774654 = 1;
		}
	} while (fcn_005373e0((void*) 0x5c35d0, 0x677c7) != 0);
	fcn_00471e30(dlg);
}
