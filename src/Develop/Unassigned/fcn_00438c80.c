typedef struct {
	int a;
	int b;
	int c;
	int d;
} Unk438c80;

void __cdecl fcn_00438c40(int, void*);

/* ADDRESS: GOLDTL 0x00438c80 */
void __cdecl fcn_00438c80(int a, int b, int c, int d)
{
	Unk438c80 t;

	t.a = b;
	t.b = c;
	t.c = d;
	fcn_00438c40(a, &t);
}
