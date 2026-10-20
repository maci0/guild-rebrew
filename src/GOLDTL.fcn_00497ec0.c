typedef struct Cmd {
	char kind;
	int f1;
	int f2;
	int f3;
	int f4;
	int f5;
} Cmd;

extern unsigned char* g_entity_ptr;
extern unsigned char* g_entity_type_table;
extern unsigned char g_773d75;

int __cdecl fcn_005463a0(int, int, int, int, int);
int __cdecl fcn_0050d320(short*, unsigned char);
int __cdecl fcn_0050d200(short*, int);
int __cdecl fcn_0050d170(int);
int __cdecl fcn_004a4bb0(int, short*, int, Cmd*, Cmd*, int);
int __cdecl fcn_0049e900(int, short*, int, Cmd*, Cmd*);

/* ADDRESS: GOLDTL 0x00497ec0 */
int __cdecl fcn_00497ec0(int a0, short* a1, int a2, Cmd* a3, Cmd* a4)
{
	int n;
	int chain[4] = {7, 6, 5, 4};
	Cmd cmd;
	Cmd out;
	int p;
	unsigned char* q;
	unsigned char* rec;
	unsigned char id;
	unsigned char t;
	int j;
	unsigned int lo;
	unsigned int hi;

	if (*(char*) ((char*) a1 + 2) == 3)
		return 0;
	if (a2 == 0) {
		if (*(char*) a3 != 0)
			return 0;
	} else {
		if (a2 == 1) {
			if (*(char*) a3 != 5 && *(char*) a3 != 4)
				return 0;
		}
	}
	if (fcn_005463a0(2, 0, 0xd, 2, *(unsigned short*) a1) != 0)
		return 0;
	p = (int) g_entity_ptr;
	n = 0;
	do {
		if (*(unsigned char*) p != 0) {
			id = *(unsigned char*) p;
			rec = g_entity_type_table + id * 0x24d;
			lo = 0;
			hi = 0;
			if (rec[0] > 0x1f) {
				hi = 1 << (rec[0] - 0x20);
			} else {
				lo = 1 << rec[0];
			}
			if (*(unsigned short*) (p + 0x27) == *(unsigned short*) a1
				&& ((*(unsigned int*) 0x666028 & lo) || (*(unsigned int*) 0x66602c & hi))) {
				int need;
				int rem;
				int v;

				/* scan address and money value share one stack slot in the
				 * native body; every hit path returns before the scan resumes */
				p = fcn_0050d320(a1, g_773d75);
				p = (int) ((float) p * *(float*) 0x664178);
				out.kind = 0;
				out.f1 = 0;
				out.f2 = 0;
				if (*(char*) a3 == 0) {
					q = *(unsigned char**) ((char*) a1 + 0x170);
					if (q != 0) {
						id = *q;
						rec = g_entity_type_table + id * 0x24d;
						if (rec[0] == 2 && !(q[0x5a] & 0x41)) {
							t = rec[0x247];
							if (t < 2 || t == 3) {
								cmd.kind = 5;
								id = *q;
								j = 0;
								if (id != 7) {
									do {
										j += 1;
									} while (chain[j] != id);
								}
								cmd.f1 = chain[j - 1];
								cmd.f2 = 1;
								out.kind = 4;
								out.f1 = *(int*) (q + 1);
								out.f2 = 1;
								if (!fcn_004a4bb0(a0, a1, a2, &cmd, &out, 0))
									return 0;
								need = fcn_0050d200(a1, cmd.f1);
								if (p >= need) {
									*a3 = cmd;
									*a4 = out;
									return 0x11;
								}
								rem = need - p;
								if ((float) rem / (float) need < *(float*) 0x6628bc) {
									a3->kind = 0x12;
									a3->f2 = rem;
									return fcn_0049e900(0x11, a1, a2, a3, a4);
								}
								return 0;
							}
							if (t == 5)
								return 0;
						}
					}
					cmd.kind = 5;
					cmd.f1 = 6;
					cmd.f2 = 1;
					if (fcn_004a4bb0(a0, a1, a2, &cmd, &out, 1)) {
						need = fcn_0050d200(a1, cmd.f1);
						if (p >= need) {
							*a3 = cmd;
							*a4 = out;
							return 0x11;
						}
						rem = need - p;
						if ((float) rem / (float) need < *(float*) 0x6628bc) {
							a3->kind = 0x12;
							a3->f2 = rem;
							return fcn_0049e900(0x11, a1, a2, a3, a4);
						}
					}
					cmd.kind = 5;
					cmd.f1 = 4;
					cmd.f2 = 1;
					if (!fcn_004a4bb0(a0, a1, a2, &cmd, &out, 1))
						return 0;
					need = fcn_0050d200(a1, cmd.f1);
					if (p >= need) {
						*a3 = cmd;
						*a4 = out;
						return 0x11;
					}
					rem = need - p;
					if ((float) rem / (float) need < *(float*) 0x6628bc) {
						a3->kind = 0x12;
						a3->f2 = rem;
						return fcn_0049e900(0x11, a1, a2, a3, a4);
					}
					return 0;
				}
				if (*(char*) a3 != 5)
					return 0;
				cmd = *a3;
				q = *(unsigned char**) ((char*) a1 + 0x170);
				if (q != 0) {
					id = *q;
					if (g_entity_type_table[id * 0x24d] != 2)
						return 0;
					v = *(int*) ((char*) a3 + 4);
					if (v - id != 1)
						return 0;
					if (id == 5 || id == 7)
						return 0;
					cmd.f1 = v;
					cmd.f2 = 1;
					out.kind = 4;
					out.f1 = *(int*) (q + 1);
					out.f2 = 1;
					need = (int) ((float) fcn_0050d170(cmd.f1) * *(float*) 0x66414c);
					if (!fcn_004a4bb0(a0, a1, a2, &cmd, &out, 0))
						return 0;
					if (p >= need) {
						*a3 = cmd;
						*a4 = out;
						return 0x11;
					}
					rem = need - p;
					if ((float) rem / (float) need < *(float*) 0x6628bc) {
						a3->kind = 0x12;
						a3->f2 = rem;
						return fcn_0049e900(0x11, a1, a2, a3, a4);
					}
					return 0;
				}
				if (g_entity_type_table[a3->f1 * 0x24d] != 2)
					return 0;
				if (!fcn_004a4bb0(a0, a1, a2, &cmd, &out, 1))
					return 0;
				if (*(char*) ((char*) a1 + 2) != 5)
					return 0;
				need = fcn_0050d200(a1, cmd.f1);
				if (p >= need) {
					*a3 = cmd;
					*a4 = out;
					return 0x11;
				}
				rem = need - p;
				if ((float) rem / (float) need < *(float*) 0x6628bc) {
					a3->kind = 0x12;
					a3->f2 = rem;
					return fcn_0049e900(0x11, a1, a2, a3, a4);
				}
				return 0;
			}
		}
		n += 1;
		p += 0xa9;
	} while (n < 0x100);
	return 0;
}
