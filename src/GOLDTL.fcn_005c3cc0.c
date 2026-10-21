extern char g_7f4ca0[];


extern unsigned short g_774970;
extern int g_14ce8e0;




int __cdecl fcn_00470820(int, int, char*);
void __cdecl fcn_00471b60(int);
void __cdecl fcn_004727a0(int, int);
int __cdecl fcn_00519190(int, ...);
int __cdecl fcn_00472250(int, int, int);
void __cdecl fcn_00473a90(int, int);
int __cdecl fcn_005373e0(void*, int);
int __cdecl fcn_00504e70(int);
int __cdecl fcn_00525f60(char*, int);
void __cdecl fcn_005100f0(int, int);
void __cdecl fcn_00471af0(int, int);
double __cdecl gm_RandomFloat01(void);
int __cdecl fcn_00526120(int, int);
char* __cdecl fcn_005463a0(int, int, int);
char* __cdecl fcn_005462a0(void);
int __cdecl fcn_004c5620(int, int);
void __cdecl fcn_00471e30(int);

/* ADDRESS: GOLDTL 0x005c3cc0 */
void __cdecl fcn_005c3cc0(char* e)
{
	char* ent;
	int id;
	int win;
	int base;
	int h1;
	int h2;
	int h3;
	int cur;
	int n;
	float p;

	id = *(int*) (e + 1);
	win = fcn_00470820(0, 0, "Panel\\Gebaeude_Brand_loeschen");
	fcn_00471b60(win);
	fcn_004727a0(win, 1);
	fcn_00519190(0x17e4, e);
	fcn_004727a0(win, 2);
	base = fcn_00519190(0x17e5, 1, 2, 4);
	h1 = fcn_00472250(win, 2, base);
	h2 = fcn_00472250(win, 2, base + 1);
	h3 = fcn_00472250(win, 2, base + 2);
	fcn_00473a90(0, 0);
	fcn_005373e0(0, 0x677c7);
	do {
		cur = fcn_00504e70(id);
		if ((*(unsigned char*) (e + 0x5b) & 4) != 0 || cur == 0) {
			(*(int*) 0x774654) = 1;
		}
		n = 1;
		if (g_14ce8e0 != 0) {
			(*(int*) 0x774654) = 1;
		}
		if ((*(int*) 0x100f1dc) == 2) {
			if ((*(int*) 0x67d370) == h1) {
				p = 0.2f;
			} else if ((*(int*) 0x67d370) == h2) {
				p = 0.5f;
				n = 2;
			} else if ((*(int*) 0x67d370) == h3) {
				p = 0.8f;
				n = 4;
			} else {
				goto next;
			}
			if (fcn_00525f60(g_7f4ca0 + g_774970 * 0x21c, n)) {
				fcn_005100f0(*(int*) (g_7f4ca0 + g_774970 * 0x21c + 4), -n);
				fcn_00471af0(win, 0);
				if (p <= (float) gm_RandomFloat01()) {
					fcn_00526120((*(int*) 0x14ab300), 4);
					fcn_00471af0(win, 1);
				} else {
					ent = fcn_005463a0(1, 0, 0x4f);
					if (ent != 0) {
						do {
							if (*(int*) (ent + 0xac) == *(int*) (e + 1)) {
								*(int*) (ent + 0x84) = fcn_004c5620(-1, (int) ent);
								fcn_00526120((*(int*) 0x14ab2fc), 4);
								goto done;
							}
							ent = fcn_005462a0();
						} while (ent != 0);
					}
done:
					(*(int*) 0x774654) = 1;
					fcn_00471af0(win, 1);
				}
			}
		} else if ((*(int*) 0x100f1dc) == n) {
			(*(int*) 0x774654) = n;
		}
next:
		if (fcn_005373e0((void*) fcn_005c3cc0, 0x677c7) == 0) {
			break;
		}
	} while (1);
	fcn_00471e30(win);
}
