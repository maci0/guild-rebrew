// FUNCTION: GOLDTL 0x56df50
// SIZE: 439

// SIZE 0x21c
struct house {
	unsigned short id;
	unsigned char type;
	char pad3;
	int owner;
	char pad8[0x214];
};

extern struct house g_7f4ca0[];
extern unsigned char g_773d75;
extern char g_699874[];
extern char g_6a6b70[];

int __cdecl fcn_004c4450(int);
char* __cdecl fcn_004c4480(int);
char* __cdecl gm_SearchTable67(int);
void __cdecl fcn_004c5f60(int, int, int);
int __cdecl fcn_0050b750(int, unsigned char);
void __cdecl fcn_004c5150(int, int, unsigned char, int);
void __cdecl fcn_0051af00(char*, int, ...);
void __cdecl fcn_00545e80(int, int, char*, int, int, int, int, int, char*);
int __cdecl fcn_00567030(char*, int*, int*);
void __cdecl fcn_004c5da0(int, int, int, int, int, char*);
void __cdecl fcn_00546190(char*);

void __cdecl fcn_0056df50(char* u)
{
	int site;
	int target;
	char text[0x400];
	char* p;
	char* t;
	struct house* h;

	switch (*(int*) (u + 0x70)) {
	case 0:
		if (fcn_004c4450(*(int*) (u + 0xac)) == 0) {
			break;
		}
		p = fcn_004c4480(*(int*) (u + 0xac));
		t = gm_SearchTable67(*(int*) (u + 0xb4));
		if (p == 0 || t == 0) {
			goto kill;
		}
		if (*(unsigned short*) (t + 0x25) != 0xffff) {
			fcn_004c5f60(*(int*) (t + 1), g_7f4ca0[*(unsigned short*) (t + 0x25)].owner, *(int*) (p + 4));
		} else {
			fcn_004c5f60(*(int*) (t + 1), *(int*) (p + 4), *(int*) (p + 4));
		}
		fcn_004c5150(*(int*) (p + 4), -1, g_773d75, fcn_0050b750(0xbb8, g_773d75));
		if (*(int*) (u + 0xbc) == 0) {
			goto kill;
		}
		h = &g_7f4ca0[*(unsigned short*) (t + 0x25)];
		if (h != 0) {
			if (h->type == 6 || h->type == 7) {
				fcn_0051af00(text, 0x17e6, t, *(unsigned short*) p, *(int*) (u + 0xbc));
				fcn_00545e80(h->owner, -1, text, 0, 0x5ec, *(int*) (t + 1), -1, 0, g_699874);
			}
			fcn_004c5150(h->owner, -1, g_773d75, *(int*) (u + 0xbc));
		}
		fcn_004c5f60(*(int*) (t + 1), *(int*) (p + 4), *(int*) (p + 4));
		if (fcn_00567030(p, &site, &target) != 0) {
			fcn_004c5da0(*(int*) (p + 4), site, target, 0, 0, g_6a6b70);
		}
	case -2:
	case -1:
kill:
		fcn_00546190(u);
		break;
	}
}
