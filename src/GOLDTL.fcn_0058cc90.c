// FUNCTION: GOLD 0x005846d0
// SIZE: 264
// FUNCTION: GOLDTL 0x0058cc90
// SIZE: 264

typedef struct
{
	int x0;
	char pad4[0x14];
	int x18;
	int* x1c;
	int x20;
	unsigned char x24;
} Req;
// SIZE 0x28

extern int g_14b5780;
extern int g_14b5784;
extern int g_100f1dc;
extern int g_14ce8e0;
extern int g_67d370;
extern int g_774654;

void __cdecl fcn_00533a60(int, int, int*, int, int, int);
void __cdecl fcn_00472640(int, int);
void __cdecl fcn_00471af0(int, int);
int __cdecl fcn_0058c670(char*, int, unsigned char);
int __cdecl fcn_0058cae0(char*, int, unsigned char);
int __cdecl fcn_005373e0(void*, int);

void __cdecl fcn_0058cc90(char* a1, Req* s)
{
	int ids[2];
	int ok;
	int cancel;

	fcn_00533a60(s->x18, 0, ids, 2, g_14b5780, g_14b5784);
	ok = ids[0];
	cancel = ids[1];
	if (*s->x1c == 3) {
		fcn_00472640(cancel, 0);
	}
	g_100f1dc = -1;
	do {
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		} else if (g_100f1dc != -1) {
			if (g_67d370 == ok) {
				fcn_00471af0(s->x0, 0);
				if (fcn_0058c670(a1, s->x20, s->x24) == 1) {
					g_774654 = 1;
				}
				fcn_00471af0(s->x0, 1);
			} else if (g_67d370 == cancel) {
				fcn_00471af0(s->x0, 0);
				if (fcn_0058cae0(a1, s->x20, s->x24) == 1) {
					g_774654 = 1;
				}
				fcn_00471af0(s->x0, 1);
			}
		}
	} while (fcn_005373e0((void*) fcn_0058cc90, 0x677c7) != 0);
}
