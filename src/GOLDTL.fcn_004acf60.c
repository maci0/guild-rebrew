extern int g_7f4c00;
extern int g_7728c8;
extern int g_7728c0;
extern char g_7f4ca0[];

int __cdecl fcn_004e8a80(int, void*);
unsigned short* __cdecl fcn_00508e40(int);
int* __cdecl fcn_004ad130(int, int*);
void __cdecl fcn_004e8240(int, int, int, int, int);
void __cdecl fcn_004c57e0(int, int);
void __cdecl fcn_0051af00(void*, int, ...);
void __cdecl fcn_00545d40(int, int, char*, int, int, char*);

struct slot_4acf60 {
	int kind;
	int id;
	int pad[4];
};
// SIZE 0x18

// FUNCTION: GOLD 0x4ace40
// SIZE: 457
// FUNCTION: GOLDTL 0x4acf60
// SIZE: 457

void __cdecl fcn_004acf60(void)
{
	int out;
	struct slot_4acf60 a;
	struct slot_4acf60 b;
	char buf[0x100];
	unsigned short* e1;
	unsigned short* e2;
	int* r;
	int lim;
	int i;

	lim = g_7f4c00 + 0x578;
	if (fcn_004e8a80(0x26, &a) == 0)
		return;
	if (fcn_004e8a80(0x27, &b) == 0)
		return;
	e1 = fcn_00508e40(a.id);
	e2 = fcn_00508e40(b.id);
	if (a.id != -1 && g_7728c8 != -1) {
		r = fcn_004ad130(g_7728c8, &out);
		if (r != 0 && r[2] <= lim) {
			fcn_004e8240(a.kind, 0, 0, 1, 0xff);
			fcn_004c57e0(a.id, 1);
			if (e1 != 0) {
				fcn_0051af00(buf, 0x42b2, *e1);
				for (i = 0; i < 768; i++) {
					if (g_7f4ca0[i * 540 + 2] == 6 || g_7f4ca0[i * 540 + 2] == 7)
						fcn_00545d40(*(int*) (g_7f4ca0 + i * 540 + 4), -1, buf, 0, 0x602, "_NACHRICHTEN_NEU_00");
				}
			}
		}
	}
	if (b.id != -1 && g_7728c0 != -1) {
		r = fcn_004ad130(g_7728c0, &out);
		if (r != 0 && r[2] <= lim) {
			fcn_004e8240(b.kind, 0, 0, 1, 0xff);
			fcn_004c57e0(b.id, 1);
			if (e2 != 0) {
				fcn_0051af00(buf, 0x42b4, *e2);
				for (i = 0; i < 768; i++) {
					if (g_7f4ca0[i * 540 + 2] == 6 || g_7f4ca0[i * 540 + 2] == 7)
						fcn_00545d40(*(int*) (g_7f4ca0 + i * 540 + 4), -1, buf, 0, 0x602, "_NACHRICHTEN_NEU_02");
				}
			}
		}
	}
}
