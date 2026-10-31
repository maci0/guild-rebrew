#include <string.h>

struct msg58 {
	char pad0[4];
	unsigned char b4;
	char pad5[3];
	int f8;
	int fc;
	char pad10[0x18];
	int f28;
	int f2c;
	int f30;
	unsigned short w34;
	unsigned char b36;
	char pad37;
	int f38;
	char pad3c[0x1c];
	int f58;
	char pad5c[0x9c];
};

void __cdecl fcn_0052a0c0(void* a1, int a2);
int __cdecl fcn_00470820(int a1, int a2, char* path);
void __cdecl d2_SetOverlayAnimation(int a1, int a2);
void __cdecl fcn_00471b60(int a1);
void __cdecl d2_SetForm(int a1, int a2);
void __cdecl fcn_005340f0(int a1);
int __cdecl io_AppendText(int a1, ...);
int __cdecl fcn_00472250(int a1, int a2, int a3);
int __cdecl fcn_005373e0(void* a1, int a2);
void __cdecl fcn_004c5530(struct msg58* m);
void __cdecl fcn_00471e30(int a1);
void __cdecl fcn_0052a2d0(void);
void __cdecl fcn_005305a0(void);
int __cdecl fcn_00532ef0(void);
void __cdecl fcn_00526120(int a1, int a2);

/* ADDRESS: GOLDTL 0x0058fbd0 */
int __cdecl fcn_0058fbd0(char* a1)
{
	int id1;
	struct msg58 m;
	int id2;
	int dlg;
	int i;
	int one;
	int sel;

	fcn_0052a0c0(a1, 0);
	dlg = fcn_00470820(0, 0, (char*) 0x6a96d8);
	d2_SetOverlayAnimation(0, 0);
	fcn_00471b60(dlg);
	d2_SetForm(dlg, 0);
	fcn_005340f0(*(int*) 0x772514);
	one = 1;
	d2_SetForm(dlg, one);
	io_AppendText(0x40f6, 0x40f5, 0x228);
	d2_SetForm(dlg, 2);
	i = io_AppendText(0x40f7);
	id1 = fcn_00472250(dlg, 2, i);
	id2 = fcn_00472250(dlg, 2, i + 1);
	*(int*) 0x100f1dc = -1;
	do {
		if (*(int*) 0x14ce8e0 != 0) {
			*(int*) 0x774654 = one;
		} else if (*(int*) 0x100f1dc != -1) {
			sel = *(int*) 0x67d370;
			if (sel == id1) {
				char* p;
				char* h;

				i = 0;
				p = (char*) 0x7f4e28;
				do {
					if (*(char*) p != 0) {
						goto found;
					}
					p += 0x21c;
					i++;
				} while ((int) p < 0x85a228);
				goto nofree;
found:
				h = (char*) (0x7f4ca0 + i * 0x21c);
				if (h != 0) {
					memset(&m, 0, sizeof(m));
					m.b4 = 0x8a;
					m.b36 = 1;
					m.f8 = *(int*) (*(unsigned short*) (a1 + 0x27) * 0x21c + 0x7f4ca4);
					m.fc = *(int*) (a1 + 1);
					m.f28 = *(int*) 0x7f4c00;
					m.f2c = *(int*) 0x7f4c04;
					m.f30 = *(int*) 0x7f4c08;
					m.w34 = *(unsigned short*) 0x7f4c0c;
					m.f38 = *(int*) (h + 4);
					m.f58 = *(int*) (h + 4);
					fcn_004c5530(&m);
					*(int*) 0x774654 = 1;
				} else {
nofree:
					fcn_00526120(*(int*) 0x14b556c, 0);
				}
			} else if (sel == id2) {
				*(int*) 0x774654 = one;
			}
		}
	} while (fcn_005373e0((void*) fcn_0058fbd0, 0x677c7) != 0);
	fcn_00471e30(dlg);
	fcn_0052a2d0();
	fcn_005305a0();
	return fcn_00532ef0();
}
