typedef struct Msg {
	unsigned char type;
	char pad[3];
	int a;
	int b;
	int c;
	int d;
	float f;
} Msg;
// SIZE 0x18

extern unsigned char g_773d75;

char* __cdecl gm_FindRecordById(int);
char* __cdecl gm_SearchTable67(int);
char* __cdecl fcn_00508e40(int);
float __cdecl fcn_0050bb50(int, unsigned char);
int __cdecl fcn_005015e0(char**, char**, char**, int);
void __cdecl fcn_004c5150(int, int, unsigned char, int);
void __cdecl fcn_004c51f0(int, int, int, int, unsigned char, int);

// FUNCTION: GOLDTL 0x004973a0
// SIZE: 287
int __cdecl fcn_004973a0(int a1, Msg* m, Msg* ev)
{
	char* r;
	char* home;
	int id;
	int n;

	id = -1;
	if (ev->type == 1) {
		r = gm_FindRecordById(ev->a);
		if (r == 0) {
			return 0;
		}
		id = *(int*) (r + 2);
	} else if (ev->type == 4) {
		r = gm_SearchTable67(ev->a);
		if (r == 0) {
			return 0;
		}
		id = *(int*) (r + 1);
	} else if (ev->type == 7) {
		r = fcn_00508e40(ev->a);
		if (r == 0) {
			return 0;
		}
		id = *(int*) (r + 4);
	}
	if (id == -1) {
		return 0;
	}
	if (m->type != 2) {
		return 0;
	}
	if (m->d == 0x39) {
		n = (int) fcn_0050bb50(m->a, g_773d75);
		fcn_005015e0(0, &home, 0, m->c);
		if (home == 0) {
			return 0;
		}
		fcn_004c5150(-1, *(int*) (home + 2), g_773d75, n);
		fcn_004c51f0(id, -1, m->a, m->b, g_773d75, 0);
		return 0x39;
	}
	fcn_004c51f0(id, -1, m->a, m->b, g_773d75, (int) fcn_0050bb50(m->a, g_773d75));
	return 0xb;
}
