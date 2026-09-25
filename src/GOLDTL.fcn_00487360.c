// FUNCTION: GOLD 0x00487e90
// SIZE: 265
// FUNCTION: GOLDTL 0x487360
// SIZE: 265

typedef struct Ent {
	unsigned short id;
	unsigned char x2;
	char pad3[0x165 - 3];
	unsigned char x165;
	char pad166[0x16c - 0x166];
	char* owner;
	char pad170[0x21c - 0x170];
} Ent;
// SIZE 0x21c

extern Ent g_7f4ca0[768];
extern short g_7f4c04;
extern unsigned char* g_868050;

unsigned short __cdecl fcn_0042e410(int n);
void __cdecl fcn_004f36f0(char* o);

void __cdecl fcn_00487360(char* e)
{
	short k;
	char* o;
	unsigned char kind;
	int n;
	int i;

	k = g_7f4c04;
	if (k != 7 && k != 12 && k != 18) {
		*(int*) (e + 0x1b4) &= ~0x40;
		return;
	}
	if (*(int*) (e + 0x1b4) & 0x40) {
		return;
	}
	o = *(char**) (e + 0x16c);
	*(int*) (e + 0x1b4) |= 0x40;
	kind = g_7f4ca0[*(unsigned short*) (o + 0x27)].x2;
	if ((kind == 6 || kind == 7) && !(*(int*) (e + 0x1b4) & 2)) {
		return;
	}
	n = 0;
	for (i = 0; i < 768; i++) {
		if (g_7f4ca0[i].id != 0xffff && g_7f4ca0[i].owner == o && g_7f4ca0[i].x165 != 0) {
			n++;
		}
	}
	if (n >= g_868050[*(unsigned char*) o * 0x24d + 0x232] + g_868050[*(unsigned char*) o * 0x24d + 0x231]) {
		return;
	}
	if (n != 0) {
		if (e[0x1c8] & 8) {
			return;
		}
		if (fcn_0042e410(0x48) < (0x12 - n) * 2) {
			return;
		}
	}
	fcn_004f36f0(*(char**) (e + 0x16c));
}
