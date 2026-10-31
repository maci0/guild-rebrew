extern int g_100f1dc;
extern int g_14abaac;
extern int g_14ce8e0;
extern int g_774654;

int __cdecl fcn_00525fb0(char* obj);
void __cdecl fcn_0052a0c0(char* obj, int a);
int __cdecl fcn_00470820(int, int, char*);
void __cdecl d2_SetOverlayAnimation(int, int);
void __cdecl fcn_00471b60(int);
int __cdecl d2_SetForm(int, int);
int __cdecl io_AppendText(int, ...);
void __cdecl fcn_00529890(char* obj);
void __cdecl fcn_00526120(int a, int b);
void __cdecl fcn_004c5530(int a1);
void __cdecl fcn_004c35f0(void);
void __cdecl fcn_0052ae70(void);
int __cdecl fcn_005373e0(int, int);
void __cdecl fcn_00471e30(int);
void __cdecl fcn_0052a2d0(void);
int __cdecl fcn_00532ef0(void);

/* ADDRESS: GOLDTL 0x005ae000 */
int __cdecl fcn_005ae000(char* obj)
{
	char packet[0x100];
	int ids[6];
	char* e;
	int dlg;
	int n;
	int i;
	int r;
	int idx;

	r = fcn_00525fb0(obj);
	if (r != 0) {
		return r;
	}
	fcn_0052a0c0(obj, 0);
	dlg = fcn_00470820(0, 0, "locations\\diebesgilde\\taschendiebstahl");
	d2_SetOverlayAnimation(0, 0);
	fcn_00471b60(dlg);
	d2_SetForm(dlg, 1);
	io_AppendText(0x19f0);
	for (i = 0; i < 6; i++) {
		ids[i] = -1;
	}
	g_100f1dc = -1;
	n = 0;
	do {
		fcn_00529890(obj);
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		}
		if (g_100f1dc != -1) {
			if (g_100f1dc == 2) {
				for (e = (char*) 0x7e4260; n < 6 && (int) e < 0x7e42e0; e += 4) {
					char* p;

					p = *(char**) e;
					if (p != 0 && *(char*) (p + 0x188) != 0) {
						ids[n] = *(int*) (p + 4);
						n++;
					}
				}
				if (n != 0) {
					idx = *(unsigned short*) (obj + 0x27);
					*(char*) (packet + 4) = 0x61;
					*(int*) (packet + 8) = *(int*) (idx * 0x21c + 0x7f4ca4);
					*(int*) (packet + 0xc) = *(int*) (obj + 1);
					*(int*) (packet + 0x28) = *(int*) 0x7f4c00;
					*(int*) (packet + 0x2c) = *(int*) 0x7f4c04;
					*(int*) (packet + 0x30) = *(int*) 0x7f4c08;
					*(unsigned short*) (packet + 0x34) = *(unsigned short*) 0x7f4c0c;
					*(char*) (packet + 0x36) = 1;
					*(int*) (packet + 0x80) = *(int*) (idx * 0x21c + 0x7f4ca4);
					fcn_004c5530((int) packet);
					fcn_004c35f0();
					fcn_0052ae70();
					g_774654 = 1;
				} else {
					fcn_00526120(g_14abaac, 0);
				}
			} else if (g_100f1dc == 1) {
				g_774654 = 1;
			}
		}
	} while (fcn_005373e0(0x5ae000, 0x677c7) != 0);
	fcn_00471e30(dlg);
	fcn_0052a2d0();
	return fcn_00532ef0();
}
