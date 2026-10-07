// FUNCTION: GOLD 0x0059b180
// FUNCTION: GOLDTL 0x005a4360

extern unsigned char g_773d75;
extern char g_7f4ca0[];

unsigned short* __cdecl fcn_00508e40(int);
void __cdecl fcn_0051af00(void*, int, ...);
int __cdecl fcn_00526010(void*, int, char);
int __cdecl fcn_00526120(char*, int);
void __cdecl fcn_004c5150(int, int, char, int);
char* __cdecl fcn_00509570(unsigned short*);
void __cdecl fcn_00545e80(int, int, char*, int, int, int, int, int, int);
void __cdecl fcn_00546190(char*);

void __cdecl fcn_005a4360(char* e, char* s)
{
	char txt[0x200];
	char msg[0x400];
	unsigned short* g;
	char* slot;
	char* p;

	g = fcn_00508e40(*(int*) (s + 0xb0));
	fcn_0051af00(msg, 0x18d5, *(int*) (s + 0xb4));
	if (e == 0) {
		return;
	}
	if (fcn_00526010(g, *(int*) (s + 0xb4), (*(char*)&g_773d75)) == 0) {
		return;
	}
	if (fcn_00526120(msg, 1) == 0) {
		return;
	}
	slot = g_7f4ca0 + *(unsigned short*) (e + 0x27) * 540;
	fcn_004c5150(*(int*) (e + 1), *(int*) (s + 0xb0), (*(char*)&g_773d75), *(int*) (s + 0xb4));
	p = fcn_00509570(g);
	if (p != 0) {
		*(int*) (p + 0x48) += *(int*) (s + 0xb4);
	}
	if (slot[2] != 5) {
		fcn_0051af00(txt, 0x18d8, *g, e, *(int*) (s + 0xb4));
		fcn_00545e80(*(int*) (slot + 4), -1, txt, 0, 0x5ec, *(int*) (e + 1), -1, 0, 0);
	}
	fcn_00546190(s);
}
