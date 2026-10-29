


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

extern char g_7f4ca0[];
extern unsigned short g_7f4c04;
extern unsigned char* lpGebaeudePROT;

unsigned short __cdecl gm_RandomMod(int n);
void __cdecl fcn_004f36f0(char* o);

void __cdecl fcn_00487360(char* e)
{
	short k;
	char* o;
	unsigned char kind;
	int n;
	int i;

	k = (*(short*)&g_7f4c04);
	if (k != 7 && k != 12 && k != 18) {
		*(int*) (e + 0x1b4) &= ~0x40;
		return;
	}
	if (*(int*) (e + 0x1b4) & 0x40) {
		return;
	}
	o = *(char**) (e + 0x16c);
	*(int*) (e + 0x1b4) |= 0x40;
	kind = ((Ent*)g_7f4ca0)[*(unsigned short*) (o + 0x27)].x2;
	if ((kind == 6 || kind == 7) && !(*(int*) (e + 0x1b4) & 2)) {
		return;
	}
	n = 0;
	for (i = 0; i < 768; i++) {
		if (((Ent*)g_7f4ca0)[i].id != 0xffff && ((Ent*)g_7f4ca0)[i].owner == o && ((Ent*)g_7f4ca0)[i].x165 != 0) {
			n++;
		}
	}
	if (n >= lpGebaeudePROT[*(unsigned char*) o * 0x24d + 0x232] + lpGebaeudePROT[*(unsigned char*) o * 0x24d + 0x231]) {
		return;
	}
	if (n != 0) {
		if (e[0x1c8] & 8) {
			return;
		}
		if (gm_RandomMod(0x48) < (0x12 - n) * 2) {
			return;
		}
	}
	fcn_004f36f0(*(char**) (e + 0x16c));
}
