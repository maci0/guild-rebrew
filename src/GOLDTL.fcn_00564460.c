/* Float block used by the reward calculation. */
typedef struct Gfx {
	float f[10];
} Gfx;
// SIZE 0x28

extern char* g_868050;
extern unsigned char g_773d75;
extern int g_100f1dc;
extern int g_100f884;
extern int g_7f4c00;
extern float g_662a08;
extern float g_662910;

char* __cdecl fcn_00508e40(int id);
char* __cdecl fcn_00504e70(int id);
void __cdecl fcn_00546190(char* e);
void __cdecl fcn_00545670(char* e, int a, int b, char* tag, int c);
void __cdecl fcn_004727a0(int dlg, int page);
int __cdecl fcn_00519190(int id, ...);
int __cdecl fcn_00500cb0(int* pos, int base);
int __cdecl fcn_0050cf50(char* e, int n);
char* __cdecl gm_StartFilteredEntitySearch(int a, int b, int id, int c, int d);
int __cdecl fcn_00503e80(void);
float __cdecl fcn_0050f980(int a, int b, int c);
void __cdecl fcn_0051af00(char* buf, int id, ...);
void __cdecl fcn_00545e80(int a, int b, char* text, int c, int d, int e, int f, int g, int h);
void __cdecl fcn_004c5420(int a, int b, int c, int d, int e);
void __cdecl fcn_004c51a0(int a, int b, unsigned char k, int n);
void __cdecl fcn_004c5f60(int a, int b, int c);
void __cdecl fcn_00545780(char* e);

/* ADDRESS: GOLDTL 0x00564460 */
void __cdecl fcn_00564460(char* e)
{
	char buf[1024];
	Gfx gfx;
	unsigned char* p;
	unsigned char* rec;
	unsigned short* q;
	unsigned char type;
	float f;
	int n;
	int k;
	int a;
	int b;
	int c;

	switch (*(int*) (e + 0x70)) {
	case 0:
		q = (unsigned short*) fcn_00508e40(*(int*) (e + 0xb4));
		p = (unsigned char*) fcn_00504e70(*(int*) (e + 0xac));
		if (q == 0 || p == 0) {
			fcn_00546190(e);
			return;
		}
		type = *(unsigned char*) (*(unsigned short*) (p + 0x25) * 0x21c + 0x7f4ca2);
		if (type == 6 || type == 7) {
			fcn_00545670(e, 0, 0, "misc\\EventMessagebox_NULL", 0x5ec);
			fcn_004727a0(*(int*) (*(char**) (e + 0x74) + 8), 0);
			fcn_00519190(0x17e8, *q, p, *(int*) (e + 0xb0));
			*(int*) (e + 0x70) = *(int*) (e + 0x70) + 1;
			return;
		}
		if (fcn_00500cb0((int*) (e + 0x52), 0x7f4c00) >= 0) {
			return;
		}
		f = 15.0f;
		q = (unsigned short*) fcn_00508e40(*(int*) (e + 0xb4));
		p = (unsigned char*) fcn_00504e70(*(int*) (e + 0xac));
		rec = (unsigned char*) (g_868050 + *p * 0x24d);
		n = fcn_0050cf50(p, (int) (char) p[0x5c]);
		if (*rec != 2) {
			k = 0;
			type = *(unsigned char*) (g_868050 + *p * 0x24d);
			c = *(unsigned short*) (*(unsigned short*) (p + 0x25) * 0x21c + 0x7f4ca0);
			if (gm_StartFilteredEntitySearch(2, 4, c, 5, type) != 0) {
				do {
					k++;
				} while (fcn_00503e80());
				if (k > 1) {
					f = 1.6f;
				}
			} else {
				type = *(unsigned char*) (*(unsigned short*) (p + 0x25) * 0x21c + 0x7f4ca2);
				if (type != 6 && type != 7 && type != 5) {
					f = 1.6f;
				} else {
					f = 8.0f;
				}
			}
		} else {
			unsigned char* v4;

			v4 = *(unsigned char**) (*(unsigned short*) (p + 0x25) * 0x21c + 0x7f4e10);
			if (v4 != 0) {
				if (v4 != p) {
					if (v4 != 0 && *v4 < *p) {
						f = 1.2f;
					}
				} else {
					f = 5.0f;
				}
			}
		}
		if ((double) n * (g_662a08 - (double) fcn_0050f980(*q, *(unsigned short*) (p + 0x25), 1) * g_662910)
			* (double) f < (double) *(int*) (e + 0xb0)) {
			fcn_0051af00(buf, 0x17e9, *(unsigned short*) (p + 0x27), p);
			fcn_00545e80(*(int*) (q + 2), -1, buf, 0, 0x5ec, *(int*) (p + 1), -1, 0, 0);
			fcn_004c5420(*(int*) (p + 1), 0x5a, 2, 2, 0x200);
			fcn_004c51a0(*(int*) (*(unsigned short*) (p + 0x25) * 0x21c + 0x7f4ca4),
				*(int*) (q + 2), g_773d75, *(int*) (e + 0xb0));
			if (*(short*) (p + 0x27) != *(short*) (p + 0x25)) {
				a = *(int*) (p + 1);
				b = *(int*) (q + 2);
				c = -1;
			} else {
				a = *(int*) (p + 1);
				b = *(int*) (q + 2);
				c = b;
			}
			fcn_004c5f60(a, b, c);
			fcn_004c5420(*(int*) (p + 1), 0x5a, 2, 0, 2);
			fcn_00546190(e);
			return;
		}
		fcn_0051af00(buf, 0x17ea, *(unsigned short*) (p + 0x27), p);
		fcn_00545e80(*(int*) (q + 2), -1, buf, 0, 0x5ec, *(int*) (p + 1), -1, 0, 0);
		fcn_004c5420(*(int*) (p + 1), 0x5a, 2, 0, 0x200);
		fcn_00545780(e);
		fcn_00546190(e);
		fcn_00546190(e);
		return;
	case 1:
		if (g_100f884 != *(int*) (*(char**) (e + 0x74) + 8)) {
			return;
		}
		if (g_100f1dc == -1) {
			return;
		}
		q = (unsigned short*) fcn_00508e40(*(int*) (e + 0xb4));
		p = (unsigned char*) fcn_00504e70(*(int*) (e + 0xac));
		if (g_100f1dc == 2) {
			fcn_0051af00(buf, 0x17e9, *(unsigned short*) (p + 0x27), p);
			fcn_00545e80(*(int*) (q + 2), -1, buf, 0, 0x5ec, *(int*) (p + 1), -1, 0, 0);
			fcn_004c5420(*(int*) (p + 1), 0x5a, 2, 2, 0x200);
			fcn_004c51a0(*(int*) (*(unsigned short*) (p + 0x25) * 0x21c + 0x7f4ca4),
				*(int*) (q + 2), g_773d75, *(int*) (e + 0xb0));
			if (*(short*) (p + 0x27) != *(short*) (p + 0x25)) {
				a = *(int*) (p + 1);
				b = *(int*) (q + 2);
				c = -1;
			} else {
				a = *(int*) (p + 1);
				b = *(int*) (q + 2);
				c = b;
			}
			fcn_004c5f60(a, b, c);
			fcn_004c5420(*(int*) (p + 1), 0x5a, 2, 0, 2);
			fcn_00545780(e);
			fcn_00546190(e);
			return;
		}
		if (g_100f1dc != 1) {
			return;
		}
		fcn_0051af00(buf, 0x17ea, *(unsigned short*) (p + 0x27), p);
		fcn_00545e80(*(int*) (q + 2), -1, buf, 0, 0x5ec, *(int*) (p + 1), -1, 0, 0);
		fcn_004c5420(*(int*) (p + 1), 0x5a, 2, 0, 0x200);
		break;
	case -2:
	case -1:
		p = (unsigned char*) fcn_00504e70(*(int*) (e + 0xac));
		if (p != 0) {
			fcn_004c5420(*(int*) (p + 1), 0x5a, 2, 0, 0x200);
		}
		break;
	default:
		return;
	}
	fcn_00545780(e);
	fcn_00546190(e);
}
