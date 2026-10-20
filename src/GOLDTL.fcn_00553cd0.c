/* Location record: 0x21c-byte entries in the g_7f4ca0 table. */
typedef struct Rec {
	unsigned short id;       /* 0x000 */
	unsigned char type;      /* 0x002 */
	char pad3;
	int owner;               /* 0x004 */
	char pad8[0x16c - 8];
	char* home;              /* 0x16c */
	char pad170[0x21c - 0x170];
} Rec;
// SIZE 0x21c

extern char g_7f4ca0[];
extern int g_7f4c00;
extern int g_7f4c04;
extern int g_7f4c08;
extern short g_7f4c0c;
extern float g_662cf8;
extern float g_662910;
extern float g_665bf0;
extern double g_6628f0;

char* __cdecl gm_StartFilteredEntitySearch(int a, int b, int id);
char* __cdecl fcn_00508e40(int id);
void __cdecl fcn_00546190(char* e);
void __cdecl fcn_00529160(char* e, int a, int id, char* rec);
void __cdecl fcn_004c5c80(int owner);
void __cdecl fcn_004c5da0(int a, int b, int c, int d, int e, char* tag);
void __cdecl fcn_00500bb0(int* pos, int a, int b, int c);
int __cdecl fcn_0050bfe0(char* e);
char* __cdecl fcn_00502cd0(int a, int b, int c, int d, int e);
char* __cdecl fcn_00502850(void);
int __cdecl fcn_0050cf50(char* e, int n);
void __cdecl fcn_004c51a0(int a, int b, int c, int d);
void __cdecl fcn_00545d40(int a, int b, char* text, int c, int d, char* tag);
void __cdecl fcn_00545e80(int a, int b, char* text, int c, int d, int e, int f, int g,
	char* tag);
void __cdecl fcn_0051af00(char* buf, int id, ...);

/* ADDRESS: GOLDTL 0x00553cd0 */
void __cdecl fcn_00553cd0(char* v3)
{
	char buf[1024];
	char* e;
	char* q;
	unsigned short* v5;
	char* p;
	unsigned char type;
	float f;
	int state;
	int x;
	int found;
	int a;
	int b;

	e = gm_StartFilteredEntitySearch(1, 1, *(int*) (v3 + 0xb0));
	v5 = (unsigned short*) fcn_00508e40(*(int*) (v3 + 0xac));
	state = *(int*) (v3 + 0x70);
	if (state == -2 || v5 == 0 || e == 0 || *(short*) (e + 0x27) == -1) {
		fcn_00546190(v3);
		return;
	}
	if (state == 0) {
		fcn_00529160(e, 0, *v5, v3);
		fcn_004c5c80(*(int*) (v5 + 2));
		fcn_004c5da0(*(int*) (v5 + 2), *(int*) (e + 1), -1, 0, 1, "BetriebsPr");
		*(int*) (v3 + 0x52) = g_7f4c00;
		*(int*) (v3 + 0x56) = g_7f4c04;
		*(int*) (v3 + 0x5a) = g_7f4c08;
		*(short*) (v3 + 0x5e) = g_7f4c0c;
		fcn_00500bb0((int*) (v3 + 0x52), 0, 10, 0);
		*(int*) (v3 + 0x70) = 1;
		return;
	}
	if (state == 1) {
		*(int*) (v3 + 0x52) = g_7f4c00;
		*(int*) (v3 + 0x56) = g_7f4c04;
		*(int*) (v3 + 0x5a) = g_7f4c08;
		*(short*) (v3 + 0x5e) = g_7f4c0c;
		fcn_00500bb0((int*) (v3 + 0x52), 0, 4, 0);
		p = *(char**) ((char*) v5 + 0x184);
		if (*(int*) (p + 0x128)) {
			*(int*) (v3 + 0x70) = 1;
			return;
		}
		f = (g_662cf8 - (float) fcn_0050bfe0(e)) * g_662910;
		found = 0;
		for (q = fcn_00502cd0(0, 2, 7, 4, 0x1d); q != 0; q = fcn_00502850()) {
			if (*(int*) (q + 0x1c) == *(int*) (v3 + 1)
				&& *(unsigned char*) (q + 0x12) < 0x50) {
				found = 1;
				break;
			}
		}
		if (f <= g_6628f0 && found == 0) {
			fcn_0051af00(buf, 0x1a76, *(unsigned short*) (e + 0x27), e);
			a = ((Rec*) g_7f4ca0)[*(unsigned short*) (v3 + 8)].owner;
			fcn_00545d40(a, a, buf, 0, 0x5f0, "_NACHRICHTEN_HS_88");
			fcn_0051af00(buf, 0x1a78, *(unsigned short*) (v3 + 8), e);
			b = ((Rec*) g_7f4ca0)[*(unsigned short*) (e + 0x27)].owner;
			fcn_00545e80(b, b, buf, 0, 0x5f0, *(int*) (e + 1), -1, 0,
				"_NACHRICHTEN_HS_86");
			*(int*) (v3 + 0x70) = 2;
			return;
		}
		x = (int) ((float) fcn_0050cf50(e, 100) * f * g_665bf0);
		fcn_004c51a0(((Rec*) g_7f4ca0)[*(unsigned short*) (v3 + 8)].owner,
			((Rec*) g_7f4ca0)[*(unsigned short*) (e + 0x27)].owner, 0, x);
		type = ((Rec*) g_7f4ca0)[*(unsigned short*) (v3 + 8)].type;
		if (type == 6 || type == 7) {
			fcn_0051af00(buf, 0x1a75, x, *(unsigned short*) (e + 0x27), e);
			a = ((Rec*) g_7f4ca0)[*(unsigned short*) (v3 + 8)].owner;
			fcn_00545d40(a, a, buf, 0, 0x5f0, "_NACHRICHTEN_HS_87");
		}
		type = ((Rec*) g_7f4ca0)[*(unsigned short*) (e + 0x27)].type;
		if (type == 6 || type == 7) {
			fcn_0051af00(buf, 0x1a77, *(unsigned short*) (v3 + 8), e, x);
			b = ((Rec*) g_7f4ca0)[*(unsigned short*) (e + 0x27)].owner;
			fcn_00545e80(b, b, buf, 0, 0x5f0, *(int*) (e + 1), -1, 0,
				"_NACHRICHTEN_HS_86");
		}
		*(int*) (v3 + 0x70) = 2;
		return;
	}
	if (state == 2) {
		fcn_00529160(e, 0, *v5, 0);
		fcn_004c5c80(*(int*) (v5 + 2));
		fcn_004c5da0(*(int*) (v5 + 2), *(int*) (v3 + 0xb4), *(int*) (v3 + 0xb8), 0,
			0, "BetriebsPr");
		fcn_00546190(v3);
		return;
	}
}
