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

int __cdecl ai_FindMissingBuildingUpgrade(int* x, int* y, void* home, int a4);
int __cdecl ai_SelectBestMethod(int kind, int id, int a3, Msg* b, Msg* a);

/* ADDRESS: GOLDTL 0x00498570 */
int __cdecl fcn_00498570(int a1, char* e, int y, Msg* out1, Msg* out2)
{
	Msg a;
	Msg b;
	int x;
	int r;

	if (e[2] != 3 && (y || out1->type == 0) && *(char**) (e + 0x170) && out1->type == 0 && ai_FindMissingBuildingUpgrade(&x, &y, *(char**) (e + 0x170), 0)) {
		b.type = 2;
		b.a = x;
		b.b = 1;
		if (y != -1) {
			a.type = 1;
			a.a = y;
		} else {
			a.type = 4;
			a.a = *(int*) (*(char**) (e + 0x170) + 1);
		}
		a.b = 1;
		a.f = 0.44f;
		r = ai_SelectBestMethod(0x15, *(unsigned short*) e, 1, &b, &a);
		if (r) {
			*out1 = b;
			*out2 = a;
			return r;
		}
	}
	return 0;
}
