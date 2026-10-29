#include <string.h>

extern float g_662acc;
extern float g_662910;
extern float g_664150;
extern float g_6628ac;

int __cdecl gm_WalkEntityChain(unsigned short);
void* __cdecl fcn_005cd440(void*, int, int, int);
int __cdecl fcn_004e99c0(int);
int __cdecl fcn_00470820(int, int, char*);
void __cdecl fcn_00473a90(int, int);
void __cdecl fcn_00471b60(int);
void __cdecl d2_SetForm(int, int);
void __cdecl fcn_005340f0(int);
int __cdecl fcn_0046fac0(int, int, int, int);
void __cdecl fcn_00472900(int, int);
int __cdecl fcn_004677e0(int, int, int, int, int, int, int, int);
void __cdecl fcn_00472380(int, int, int, int, int);
void __cdecl fcn_00468bb0(int, int, int, int, int);
int __cdecl fcn_00519190(int, ...);
int __cdecl fcn_00472250(int, int, int);
int __cdecl fcn_00471f80(int);
int __cdecl fcn_005373e0(void*, int);
void __cdecl fcn_00471e30(int);
int __cdecl fcn_00526010(char*, int, char);
int __cdecl fcn_00525f60(char*, int);
int __cdecl fcn_005898f0(void*);
char* __cdecl gm_GetEntityTableEntry(char*);
void __cdecl fcn_004c51a0(int, int, unsigned char, int);
void __cdecl fcn_005100f0(int, int);
int __cdecl fcn_004a5e60(unsigned short*, int, int, int, float, float, int*);
int __cdecl fcn_004c5530(void*);
int __cdecl fcn_004c4450(int);
void __cdecl fcn_004c3030(int, int, char*, int);
void __cdecl fcn_00532ef0(void);

/* ADDRESS: GOLDTL 0x00589d00 */
void __cdecl fcn_00589d00(int a0)
{
	char* v6;
	char req[0xf8];
	int q[20];
	int amt[3];
	int dlg;
	int no;
	int yes;
	int ids[3];
	int total;
	int n;
	int elem;
	int btn;
	int sel;
	int pick;
	int id;
	int i;

	total = gm_WalkEntityChain(*(unsigned short*) 0x774970);
	for (i = 0; i < 20; i++)
		q[i] = 0;
	for (i = 7; i < 15; i++)
		q[i] = -1;
	q[1] = 0x400;
	q[4] = 6;
	q[0] = 1;
	v6 = (char*) fcn_005cd440(q, *(int*) 0x14b5354, 0, 0);
	if (v6 == 0)
		return;
	total += gm_WalkEntityChain(*(unsigned short*) v6);
	n = fcn_004e99c0(*(unsigned char*) (v6 + 0x166)) / 3 + 2;
	amt[0] = (int) (float) n;
	amt[1] = (int) (g_662acc * (float) n);
	amt[2] = (int) ((float) n + (float) n);
	ids[0] = (int) (g_662910 * (float) total);
	ids[1] = (int) (g_664150 * (float) total);
	ids[2] = (int) ((float) total * g_6628ac);
	dlg = fcn_00470820(0, 0, (char*) 0x6a9514);
	fcn_00473a90(0, 0);
	fcn_00471b60(dlg);
	d2_SetForm(dlg, 0);
	fcn_005340f0(*(int*) 0x772514);
	d2_SetForm(dlg, 2);
	elem = fcn_0046fac0(0, 3, *(int*) 0x14b5360, *(int*) 0x772514);
	*(int*) (*(int*) 0x1015ea0 + elem * 0x2f4 + 0x6c) = 1;
	*(int*) (*(int*) 0x1015ea0 + elem * 0x2f4 + 0x18) =
	    *(int*) (*(int*) 0x772514 * 0x3cc + 0x1015f4c);
	fcn_00472900(elem, 0x54);
	elem = fcn_004677e0(0x57, 0x14, 0xc8, 0, 0x64, 0x7b, 2, *(int*) 0x772514);
	fcn_00472380(elem, 0, 2, 0, 1);
	fcn_00468bb0(elem, 3, *(int*) 0x14b5364, *(int*) 0x14b5368,
	             *(int*) 0x14b536c);
	d2_SetForm(dlg, 3);
	btn = fcn_00519190(0x4014);
	no = fcn_00472250(dlg, 3, btn);
	yes = fcn_00472250(dlg, 3, btn + 1);
	*(int*) 0x100f1dc = -1;
	do {
		sel = fcn_00471f80(elem);
		d2_SetForm(dlg, 1);
		fcn_00519190(0x6811b0);
		fcn_00519190(0x400e, 0x400c, *(unsigned short*) v6);
		fcn_00519190(0x400f, amt[sel], ids[sel]);
		if (*(int*) 0x14ce8e0 != 0) {
			*(int*) 0x774654 = 1;
		} else if (*(int*) 0x100f1dc != -1) {
			pick = *(int*) 0x67d370;
			if (pick == no) {
				char* p;

				if (fcn_00526010(
				        (char*) (0x7f4ca0 +
				                 (unsigned int) *(unsigned short*) 0x774970 *
				                     0x21c),
				        ids[sel], *(char*) 0x773d75) != 0 &&
				    fcn_00525f60(
				        (char*) (0x7f4ca0 +
				                 (unsigned int) *(unsigned short*) 0x774970 *
				                     0x21c),
				        amt[sel]) == 1 &&
				    fcn_005898f0((void*) a0) != 0) {
					p = gm_GetEntityTableEntry(
					    (char*) (0x7f4ca0 +
					             (unsigned int) *(unsigned short*)
					                     0x774970 *
					                 0x21c));
					if (p != 0)
						*(int*) (p + 0x28) += ids[sel];
					fcn_004c51a0(
					    -1,
					    *(int*) (0x7f4ca4 +
					             (unsigned int) *(unsigned short*)
					                     0x774970 *
					                 0x21c),
					    *(char*) 0x773d75, ids[sel]);
					fcn_005100f0(
					    *(int*) (0x7f4ca4 +
					             (unsigned int) *(unsigned short*)
					                     0x774970 *
					                 0x21c),
					    -amt[sel]);
					memset(req, 0, 0xf8);
					req[4] = 0x99;
					req[0x36] = 2;
					*(int*) (req + 0x64) = -1;
					*(int*) (req + 0x68) = 2;
					*(int*) (req + 0x6c) = sel;
					*(int*) (req + 8) =
					    *(int*) (0x7f4ca4 +
					             (unsigned int) *(unsigned short*) (a0 + 0x27) *
					                 0x21c);
					*(int*) (req + 0xc) = *(int*) (a0 + 1);
					*(int*) (req + 0x28) = *(int*) 0x7f4c00;
					*(int*) (req + 0x2c) = *(int*) 0x7f4c04;
					*(int*) (req + 0x30) = *(int*) 0x7f4c08;
					*(short*) (req + 0x34) = *(short*) 0x7f4c0c;
					*(int*) (req + 0x5c) = *(int*) (a0 + 1);
					*(int*) (req + 0x60) = *(int*) (v6 + 4);
					if (*(int*) (v6 + 0x170) != 0)
						sel = *(int*) (*(int*) (v6 + 0x170) + 1);
					else if (*(int*) (v6 + 0x16c) != 0) {
						*(int*) (req + 0x58) =
						    *(int*) (*(int*) (v6 + 0x16c) + 1);
						goto sent;
					} else {
						n = -1;
						fcn_004a5e60(
						    (unsigned short*) (0x7f4ca0 +
						                       (unsigned int) *(unsigned short*)
						                               0x774970 *
						                           0x21c),
						    0, 0x7b4c4a0, 0, 0.0f, 100.0f, &n);
						sel = n;
					}
					*(int*) (req + 0x58) = sel;
sent:
					id = fcn_004c5530(req);
					if (id != -1) {
						do {
							if (fcn_004c4450(id) != 0)
								break;
							fcn_005373e0(0, 0x20007);
						} while (1);
					}
					fcn_004c3030(-7, 0, (char*) 0x6a9508, 0);
					*(int*) 0x774654 = 1;
				}
			} else if (pick == yes) {
				*(int*) 0x774654 = 1;
			}
		}
	} while (fcn_005373e0((void*) 0x589d00, 0x677c7) != 0);
	fcn_00471e30(dlg);
	fcn_00532ef0();
}
