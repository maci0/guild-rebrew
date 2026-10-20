extern char* g_14ab248;
extern char* g_773da8;
extern char g_7f4ca0[];
extern int g_100f1dc;
extern int g_14ce8e0;
extern int g_67d370;
extern int g_774654;
extern unsigned char g_773d75;
extern unsigned short g_774970;

int __cdecl fcn_00470820(int, int, char*);
void __cdecl fcn_00471b60(int);
void __cdecl fcn_00471e30(int);
int __cdecl fcn_00472250(int, int, int);
void __cdecl fcn_004727a0(int, int);
void __cdecl fcn_00473a90(int, int);
void __cdecl fcn_004c4eb0(char*);
void __cdecl fcn_004c4ef0(char*);
void __cdecl fcn_004c5150(int, int, char, int);
int __cdecl fcn_004c5530(void*);
int __cdecl fcn_00504e70(int);
char* __cdecl fcn_00507a10(char*);
int __cdecl fcn_00509570(char*);
int __cdecl fcn_0050cf50(char*, int);
int __cdecl fcn_00519190(int, char*, int, int, int);
int __cdecl fcn_00526010(char*, int, char);
int __cdecl fcn_00526070(char*, int, int, char);
int __cdecl fcn_00526120(char*, int);
int __cdecl fcn_005373e0(void*, int);

/* ADDRESS: GOLDTL 0x005c2580 */

/* Renovation order dialog of the currently selected building. The handler
 * polls its own dialog until the user closes it and dispatches the order to
 * the owning building or to the local player entity. */
void __cdecl fcn_005c2580(char* e)
{
	char msg[0xf8];
	float x;
	int p;
	int n;
	int id;
	int a;
	int b;
	int c;
	int h0;
	int h1;
	int h2;
	int h3;
	int dur;
	int val;
	int win;
	int h;

	id = *(int*) (e + 1);
	p = fcn_0050cf50(e, 100);
	x = (float) p;
	n = 100 - (int) *(char*) (e + 0x5c);
	if (n <= 0) {
		fcn_00526120(g_14ab248, 4);
		return;
	}
	x = x * 0.005f;
	if (128.0f > x) {
		x = 128.0f;
	}
	win = fcn_00470820(0, 0, "Panel\\Gebaeude_Renovieren");
	fcn_00471b60(win);
	fcn_004727a0(win, 2);
	a = (int) (n * x);
	b = (int) (n * x * 0.5);
	c = (int) (n * x * 0.25);
	h = fcn_00519190(0x17c8, e, c, b, a);
	h0 = fcn_00472250(win, 2, h);
	h1 = fcn_00472250(win, 2, h + 1);
	h2 = fcn_00472250(win, 2, h + 2);
	h3 = fcn_00472250(win, 2, h + 3);
	fcn_00473a90(0, 0);
	fcn_005373e0(0, 0x677c7);
	do {
		p = fcn_00504e70(id);
		if ((*(unsigned char*) (e + 0x5b) & 4) || p == 0) {
			g_774654 = 1;
		}
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		}
		if (g_100f1dc != -1) {
			if (g_67d370 != h0 && g_67d370 != h1 && g_67d370 != h2) {
				if (g_67d370 == h3) {
					g_774654 = 1;
				}
			} else {
				dur = 0;
				val = 0;
				*(unsigned char*) (msg + 4) = 0x1c;
				*(int*) (msg + 0xc) = -1;
				*(unsigned char*) (msg + 0x36) = 1;
				*(int*) (msg + 8) = *(int*) (g_7f4ca0 + (unsigned int) *(unsigned short*) 0x774970 * 0x21c + 4);
				*(int*) (msg + 0x58) = id;
				if (g_67d370 == h0) {
					dur = (int) (n * 0.25);
					val = c;
				} else if (g_67d370 == h1) {
					dur = (int) (n * 0.5);
					val = b;
				} else if (g_67d370 == h2) {
					dur = n;
					val = a;
				}
				if (*(unsigned short*) (e + 0x27) == *(unsigned short*) g_773da8) {
					char* q;

					q = fcn_00507a10(e);
					if (q != 0 && fcn_00526070(q, *(int*) (q + 0x14), val, (char) g_773d75) != 0) {
						*(int*) (msg + 0x5c) = dur;
						fcn_004c4eb0("renovieren");
						fcn_004c5150(-1, *(int*) (q + 2), (char) g_773d75, val);
						fcn_004c5530(msg);
						fcn_004c4ef0("renovieren");
						g_774654 = 1;
					}
				} else if (fcn_00526010(g_7f4ca0 + (unsigned int) *(unsigned short*) 0x774970 * 0x21c, val, (char) g_773d75) != 0) {
					char* q;

					q = fcn_00509570(g_7f4ca0 + (unsigned int) *(unsigned short*) 0x774970 * 0x21c);
					if (q != 0) {
						*(int*) (q + 0x44) += val;
					}
					*(int*) (msg + 0x5c) = dur;
					fcn_004c4eb0("renovieren");
					fcn_004c5150(-1, *(int*) (g_7f4ca0 + (unsigned int) *(unsigned short*) 0x774970 * 0x21c + 4), (char) g_773d75, val);
					fcn_004c5530(msg);
					fcn_004c4ef0("renovieren");
					g_774654 = 1;
				}
			}
		}
	} while (fcn_005373e0((void*) fcn_005c2580, 0x677c7) != 0);
	fcn_00471e30(win);
}
