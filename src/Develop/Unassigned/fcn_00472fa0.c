typedef struct
{
	char pad00[0x38];
	int f38;
	char pad3c[0x3cc - 0x3c];
} F472Table;

int __cdecl fcn_00466190(int a);
void __cdecl fcn_0047cba0(int a1, int a2, int a3, int a4, int a5);

/* ADDRESS: GOLDTL 0x00472fa0 */
void __cdecl fcn_00472fa0(int a1, int a2, int a3)
{
	F472Table* t;
	int v;

	t = (F472Table*) (0x1015f40 + 0x3cc * *(int*) 0x772514);
	v = fcn_00466190(a3);
	fcn_0047cba0(a1, a2, t->f38, v, *(int*) 0x772568);
}
