// FUNCTION: GOLD 0x5d1530
// FUNCTION: GOLDTL 0x005dda60

typedef struct Ent {
	unsigned short id;
	unsigned char kind;
	char pad3;
	int handle;
	char pad8;
	char side;
	char pada[0x166 - 0xa];
	char ready;
	char pad167[0x21c - 0x167];
} Ent;
// SIZE 0x21c

extern char g_7f4ca0[];

int __cdecl fcn_0042e410(int);
void __cdecl fcn_004c54c0(int, int, int, int);
void __cdecl fcn_0051af00(char*, int, ...);
void __cdecl fcn_00545d40(int, int, char*, int, int, int);
char* __cdecl fcn_005c6220(int, int*);
void __cdecl fcn_005dbe90(char*);

int __cdecl fcn_005dda60(Ent* ent, int* arg)
{
	Ent* picks[3];
	int tmp;
	char text[0x800];
	char* rec;
	int r;
	int n;
	int m;
	int i;

	arg[4] = 1;
	r = fcn_0042e410(0x300) & 0xffff;
	n = 0x300;
	while (n != 0) {
		if (r != ent->id && ((Ent*)g_7f4ca0)[r].id != 0xffff && ((Ent*)g_7f4ca0)[r].kind < 10 &&
		    ((Ent*)g_7f4ca0)[r].side != ent->side && ((Ent*)g_7f4ca0)[r].ready != 0) {
			picks[0] = &((Ent*)g_7f4ca0)[r];
			break;
		}
		n--;
		r = (r + 1) % 0x300;
	}
	r = fcn_0042e410(0x300) & 0xffff;
	m = 0x300;
	while (m != 0) {
		if (r != ent->id && r != picks[0]->id && ((Ent*)g_7f4ca0)[r].id != 0xffff &&
		    ((Ent*)g_7f4ca0)[r].kind < 10 && ((Ent*)g_7f4ca0)[r].side != ent->side) {
			picks[1] = &((Ent*)g_7f4ca0)[r];
			break;
		}
		m--;
		r = (r + 7) % 0x300;
	}
	r = fcn_0042e410(0x300) & 0xffff;
	m = 0x300;
	while (m != 0) {
		if (r != ent->id && r != picks[0]->id && r != picks[1]->id && ((Ent*)g_7f4ca0)[r].id != 0xffff &&
		    ((Ent*)g_7f4ca0)[r].kind < 10 && ((Ent*)g_7f4ca0)[r].side != ent->side) {
			picks[2] = &((Ent*)g_7f4ca0)[r];
			break;
		}
		m--;
		r = (r + 13) % 0x300;
	}
	fcn_004c54c0(ent->handle, picks[0]->handle, 0x14, 1);
	fcn_004c54c0(ent->handle, picks[1]->handle, 0x14, 1);
	fcn_004c54c0(ent->handle, picks[2]->handle, 0x14, 1);
	fcn_0051af00(text, 0xfef, ent->id);
	for (i = 0; i < 3; i++) {
		if (picks[i]->kind == 6 || picks[i]->kind == 7) {
			fcn_00545d40(picks[i]->handle, -1, text, 0, 0x5ec, 0);
		}
	}
	if (ent->kind == 6) {
		rec = fcn_005c6220(**(unsigned short**) arg, &tmp);
		fcn_0051af00(text, 0xfe8, *(unsigned short*) (rec + 0x18) + 1, picks[0]->id, picks[1]->id,
		    picks[2]->id);
		fcn_005dbe90(text);
	}
	return 1;
}
