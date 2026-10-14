typedef struct Cmd {
	int op;
	int id;
	char pad8[0x14];
	int level;
} Cmd;
// SIZE 0x20

typedef struct Spec {
	char pad0[0x14];
	int need;
} Spec;
// SIZE 0x18

extern char g_774964;
extern int g_7728d8;
extern signed char g_6a3440;

Spec* __cdecl fcn_004b3c50(int op);
char* __cdecl fcn_00508e40(int id);
int __cdecl fcn_004b46c0(char* t, Spec* s);
int __cdecl fcn_004b4700(char* t, Spec* s);
int __cdecl fcn_004b4730(char* t, Cmd* c, Spec* s);
int __cdecl fcn_004b4760(char* t, Spec* s);
int __cdecl fcn_004b47a0(char* t, Spec* s);
int __cdecl fcn_004b47e0(char* t, Spec* s);
int __cdecl fcn_004b4830(char* t, Cmd* c, Spec* s);
int __cdecl fcn_004b4860(char* t, Spec* s);
int __cdecl fcn_004b48d0(char* t, Spec* s);
int __cdecl fcn_004b49a0(char* t, Spec* s);
int __cdecl fcn_004b49e0(char* t, Spec* s);
int __cdecl fcn_004b4a20(char* t, Spec* s);
int __cdecl fcn_004b4a60(char* t, Spec* s);
int __cdecl fcn_004b4ad0(char* t, Spec* s);
int __cdecl fcn_004b4b70(char* t, Spec* s);
int __cdecl fcn_004b4c10(char* t, Cmd* c, Spec* s);
int __cdecl fcn_004b4c60(char* t, Spec* s);
int __cdecl fcn_004b4dc0(char* t, Cmd* c, Spec* s);
int __cdecl fcn_004b4fa0(char* t, Spec* s);
int __cdecl fcn_004b4f30(char* t, Cmd* c, Spec* s);
int __cdecl fcn_004b4ec0(char* t, Spec* s);
int __cdecl fcn_004b4f00(char* t, Spec* s);
int __cdecl fcn_004b5020(char* t, Spec* s);

/* ADDRESS: GOLD 0x004b4f00 */
/* ADDRESS: GOLDTL 0x004b5070 */
int __cdecl fcn_004b5070(Cmd* c)
{
	Spec* s;
	char* t;

	s = fcn_004b3c50(c->op);
	if (g_774964 == 0 || s == 0) {
		return 0;
	}
	if (g_7728d8 == 1 && g_6a3440 >= 0 && g_6a3440 <= 5) {
		g_7728d8 = 0;
		return 1;
	}
	t = fcn_00508e40(c->id);
	if (t == 0) {
		return 0;
	}
	switch (c->op) {
	case 1:
	case 6:
	case 14:
	case 22:
	case 32:
		return fcn_004b46c0(t, s);
	case 2:
	case 7:
		return fcn_004b4700(t, s);
	case 3:
	case 10:
	case 24:
		return fcn_004b4730(t, c, s);
	case 5:
	case 13:
	case 21:
	case 30:
		return fcn_004b4760(t, s);
	case 31:
		return fcn_004b47a0(t, s);
	case 4:
	case 9:
	case 29:
		return fcn_004b47e0(t, s);
	case 15:
	case 16:
	case 17:
	case 18:
	case 34:
	case 35:
		return fcn_004b4830(t, c, s);
	case 11:
	case 19:
	case 23:
	case 28:
	case 40:
		return c->level >= s->need;
	case 8:
		return fcn_004b4860(t, s);
	case 12:
		return fcn_004b48d0(t, s);
	case 20:
	case 25:
	case 36:
		return fcn_004b49a0(t, s);
	case 26:
	case 37:
		return fcn_004b49e0(t, s);
	case 27:
		return fcn_004b4a20(t, s);
	case 41:
		return fcn_004b4a60(t, s);
	case 39:
		return fcn_004b4ad0(t, s);
	case 38:
		return fcn_004b4b70(t, s);
	case 33:
		return fcn_004b4c10(t, c, s);
	case 43:
		return fcn_004b4c60(t, s);
	case 44:
		return fcn_004b4dc0(t, c, s);
	case 45:
		return fcn_004b4fa0(t, s);
	case 46:
		return fcn_004b4f30(t, c, s);
	case 47:
		return fcn_004b4ec0(t, s);
	case 48:
		return fcn_004b4f00(t, s);
	case 49:
		return fcn_004b5020(t, s);
	}
	return 0;
}
