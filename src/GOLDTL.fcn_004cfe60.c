extern char* g_67a370;

char* __cdecl fcn_004ceac0(int, char*);
char* __cdecl fcn_004ce610(char*);
char* __cdecl fcn_004cef30(int);
char __cdecl fcn_0045b990(int, int, void*, void*, void*);
void __cdecl fcn_00414be0(int, int, int, int);
void __cdecl fcn_0051af00(char*, int, ...);
void __cdecl fcn_00533a40(char*);

/* ADDRESS: GOLDTL 0x004cfe60 */
void __cdecl fcn_004cfe60(int a, char* b)
{
	char buf[0x100];
	char* rec;
	char* ent;
	char* slot;
	int top;
	int x;
	int p;
	int q;
	int r;

	top = *(int*) (g_67a370 + 0xb0);
	rec = fcn_004ceac0(a, b);
	ent = fcn_004ce610(b);
	if (rec == 0) {
		return;
	}
	switch (*(int*) (rec + 4)) {
	case 1:
		fcn_0051af00(buf, 0x1174, *(int*) (ent + 0x54), *(unsigned short*) b);
		fcn_00533a40(buf);
		return;
	case 2:
		slot = fcn_004cef30(*(int*) (rec + 0x10));
		x = *(int*) (*(int*) (slot + 0x184) + 0x34);
		if (fcn_0045b990(top, x + 0x4c, &p, &q, &r)) {
			fcn_00414be0(x, 0xff, 0, 0);
		}
		fcn_0051af00(buf, 0x1177, *(int*) (ent + 0x54), *(unsigned short*) b,
			*(int*) (fcn_004ce610(slot) + 0x54), *(unsigned short*) slot);
		fcn_00533a40(buf);
		return;
	case 3:
		fcn_0051af00(buf, 0x1175, *(int*) (ent + 0x54), *(unsigned short*) b);
		fcn_00533a40(buf);
		return;
	case 4:
		fcn_0051af00(buf, 0x117c, *(int*) (ent + 0x54), *(unsigned short*) b);
		fcn_00533a40(buf);
		return;
	}
}
