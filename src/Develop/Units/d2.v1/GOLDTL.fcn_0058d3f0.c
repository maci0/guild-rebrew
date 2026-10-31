


typedef struct
{
	int* x0;
	int x4;
	unsigned char x8;
	int* xc;
	int x10;
} Req;
// SIZE 0x14

extern int g_772514;
extern int g_100f1dc;
extern int g_14ce8e0;
extern int g_67d370;
extern int g_774654;
extern char s_6a9748[];
extern char s_6a9714[];
extern char s_6a96d8[];

int __cdecl fcn_004f3e60(int, int*);
void __cdecl io_FormatTextBuffer(void*, int, ...);
void __cdecl fcn_00526120(char*, int);
int __cdecl fcn_00470820(int, int, int);
void __cdecl d2_SetOverlayAnimation(int, int);
void __cdecl fcn_00471b60(int);
void __cdecl d2_SetForm(int, int);
void __cdecl fcn_005340f0(int);
int __cdecl io_AppendText(int, ...);
int __cdecl fcn_00472250(int, int, int);
int __cdecl fcn_004f3280(int, int, int, int, int);
int __cdecl fcn_004c4450(int);
char* __cdecl fcn_004c4480(int);
int __cdecl sprintf(char*, const char*, ...);
int __cdecl fcn_00426fd0(char*);
void __cdecl fcn_00428340(int, int, char*);
int __cdecl fcn_005373e0(void*, int);
void __cdecl fcn_00471e30(int);

int __cdecl fcn_0058d3f0(int a1, Req* a2)
{
	int cancel;
	int info;
	int ok;
	char line[0x40];
	char buf[0x200];
	int r;
	int s;
	int dlg;
	int id;
	int h;
	char* p;

	r = 0;
	s = fcn_004f3e60(a1, &info);
	if (s != 1) {
		if (s == 0) {
			io_FormatTextBuffer(buf, 0x4135, info, 0x229, a1);
			fcn_00526120(buf, 0);
		}
		return 0;
	}
	dlg = fcn_00470820(0, 0, (int) s_6a96d8);
	d2_SetOverlayAnimation(0, 0);
	fcn_00471b60(dlg);
	d2_SetForm(dlg, 0);
	fcn_005340f0(g_772514);
	d2_SetForm(dlg, 1);
	io_AppendText(0x4132, 0x4131, 0x229);
	d2_SetForm(dlg, 2);
	id = io_AppendText(0x4133);
	ok = fcn_00472250(dlg, 2, id);
	cancel = fcn_00472250(dlg, 2, id + 1);
	g_100f1dc = -1;
	do {
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		} else if (g_100f1dc != -1) {
			if (g_67d370 == ok) {
				if (*a2->xc == -1) {
					g_774654 = 1;
				} else {
					h = fcn_004f3280(a1, *a2->x0, a2->x8, a2->x10, 0x1c);
					while (h != -1 && (s = fcn_004c4450(h)) == 0) {
						fcn_005373e0((void*) s, 0x20007);
					}
					p = fcn_004c4480(h);
					if (p != 0) {
						sprintf(line, s_6a9748, *(int*) (p + 4));
						id = fcn_00426fd0(s_6a9714);
						fcn_00428340(id, 1, line);
					}
					r = 1;
					g_774654 = 1;
				}
			} else if (g_67d370 == cancel) {
				g_774654 = 1;
			}
		}
	} while (fcn_005373e0((void*) fcn_0058d3f0, 0x677c7) != 0);
	fcn_00471e30(dlg);
	return r;
}
