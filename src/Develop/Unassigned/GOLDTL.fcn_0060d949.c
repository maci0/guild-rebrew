/* Native ABI is __thiscall with two stack arguments (ret 8); the object is in
   ECX. C89 cannot declare __thiscall, so the object arrives as the first
   __fastcall register argument and the unused second register argument keeps
   the two stack arguments in their native slots. Resolves the four record
   indices of the entry against the three-dword record table at self->0x88,
   caches them in the entry, then dispatches the first non-negative pair to
   fcn_0060da5b with the entry, the pair values and the second object. */
typedef struct E0060d949 {
	char pad0[0x10];
	int f10;
	char pad14[0xc];
	int f20;
	int f24;
	int f28;
	int f2c;
	int f30;
	int f34;
	int f38;
	int f3c;
	char pad40[0x1c];
	int f5c;
	int f60;
	int f64;
	int f68;
} E0060d949;

typedef struct S0060d949 {
	char pad[0x88];
	int* f88;
} S0060d949;

int __fastcall fcn_0060da5b(S0060d949*, int, int, int, int, int, int, int, int, int);

/* ADDRESS: GOLDTL 0x0060d949 */
int __fastcall fcn_0060d949(S0060d949* self, int unused, E0060d949* e, int a2)
{
	int v20;
	int v28;
	int v30;
	int v38;
	int edx;
	int arg4;
	int arg5;

	if (e->f20 == -1) {
		v20 = -1;
	}
	else {
		v20 = self->f88[e->f20 * 3 + e->f24];
	}
	if (e->f28 == -1) {
		v28 = -1;
	}
	else {
		v28 = self->f88[(e->f2c + 1) % 3 + e->f28 * 3];
		arg5 = v28;
	}
	e->f5c = v20;
	arg5 = (int)e;
	if (e->f10 != -1) {
		if (e->f30 == -1) {
			v30 = -1;
		}
		else {
			v30 = self->f88[(e->f34 + 1) % 3 + e->f30 * 3];
		}
		e->f64 = v30;
		if (e->f38 == -1) {
			v38 = -1;
		}
		else {
			v38 = self->f88[e->f38 * 3 + e->f3c];
		}
		e->f68 = v38;
	}
	if (e->f20 != -1) {
		edx = e->f20;
		arg4 = v20;
	}
	else if (e->f28 != -1) {
		edx = e->f28;
		arg4 = v28;
	}
	else if (e->f10 == -1) {
		return 0;
	}
	else if (e->f30 != -1) {
		edx = e->f30;
		arg4 = e->f64;
	}
	else if (e->f38 != -1) {
		edx = e->f38;
		arg4 = e->f68;
	}
	else {
		return 0;
	}
	fcn_0060da5b(self, 0, edx, arg4, 0, e->f28, arg5, e->f38, e->f68, a2);
	return 0;
}
