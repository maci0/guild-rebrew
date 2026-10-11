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

char* __cdecl gm_StartFilteredEntitySearch(int arg_count, ...);
char* __cdecl fcn_00502cd0(int, int, int, int, int);
int __cdecl fcn_00495400(int kind, int id, int a3, Msg* b, Msg* a);
int __cdecl fcn_00577850(int id);
unsigned short __cdecl gm_RandomMod(int n);
int __cdecl fcn_0048dbc0(char* e, Msg* a, Msg* b);
int __cdecl fcn_0048dcd0(char* e, Msg* a, Msg* b);
int __cdecl fcn_0048ddd0(char* e, Msg* a, Msg* b);
int __cdecl fcn_0048df90(char* e, Msg* a, Msg* b);

// FUNCTION: GOLD 0x0048e460
// FUNCTION: GOLDTL 0x0048da10
int __cdecl fcn_0048da10(int kind, char* e, int busy, Msg* out1, Msg* out2)
{
	Msg a;
	Msg b;
	char* t;
	int r;

	if (e[2] == 3 || busy != 0 || (kind != 0x41 && kind != 0)) {
		return 0;
	}
	t = gm_StartFilteredEntitySearch(2, 5, 0x1e, 4, *(unsigned short*) e);
	if (t == 0) {
		return 0;
	}
	if (fcn_00502cd0(*(int*) (t + 0x5d), 2, 6, 0, 0x266) == 0) {
		a.type = 2;
		a.a = 0x266;
		a.b = 1;
		a.f = 0.22f;
		b.type = 4;
		b.a = *(int*) (t + 1);
		b.b = 1;
		r = fcn_00495400(0x41, *(unsigned short*) e, 1, &a, &b);
		if (r != 0) {
			*out1 = a;
			*out2 = b;
		}
		return r;
	}
	if (fcn_00577850(*(int*) (t + 1)) != 0) {
		return 0;
	}
	switch (gm_RandomMod(4)) {
	case 0:
		r = fcn_0048dbc0(e, &a, &b);
		break;
	case 1:
		r = fcn_0048dcd0(e, &a, &b);
		break;
	case 2:
		r = fcn_0048ddd0(e, &a, &b);
		break;
	case 3:
		r = fcn_0048df90(e, &a, &b);
		break;
	default:
		return 0;
	}
	if (r == 0) {
		return 0;
	}
	*out1 = a;
	*out2 = b;
	out1->c = *(int*) (t + 1);
	return 0x41;
}
