typedef struct Ent {
	unsigned short id;
	char pad2[2];
	int x4;
	char pad8[0x166 - 8];
	unsigned char x166;
	char pad167[0x21c - 0x167];
} Ent;
/* SIZE 0x21c */

extern char g_7f4ca0[];

unsigned short __cdecl gm_RandomMod(int n);
int __cdecl fcn_004a5340(char* e, int a, int* b, int c, float r, int* out);
int __cdecl fcn_004e99c0(int k);
int __cdecl fcn_0050b810(int a, char b);
int __cdecl gm_WalkEntityChain(unsigned short raw_idx);

/* ADDRESS: GOLDTL 0x0048ddd0 */
int __cdecl fcn_0048ddd0(char* e, char* a2, char* a3)
{
	int mask;
	int idx;
	int n;
	int nv;
	int tot[3];
	int thr[3];
	Ent* t;
	int total;

	mask = 0xf00500;
	if (fcn_004a5340(e, 1, &mask, 0, gm_RandomMod(0x20) + *(float*) 0x664154, &idx) == 0) {
		return 0;
	}
	t = &((Ent*) g_7f4ca0)[(unsigned short) idx];
	n = fcn_004e99c0(t->x166) / 3 + 2;
	thr[0] = (int) (float) n;
	thr[1] = (int) ((float) n * *(float*) 0x662acc);
	thr[2] = (int) ((float) n * 2);
	if (*(int*) (e + 0x194) >= thr[2]) {
		n = 2;
	} else if (*(int*) (e + 0x194) >= thr[1]) {
		n = 1;
	} else if (*(int*) (e + 0x194) >= thr[0]) {
		n = 0;
	} else {
		return 0;
	}
	fcn_0050b810(*(int*) (e + 0x178), *(char*) 0x773d75);
	total = gm_WalkEntityChain(*(unsigned short*) e);
	total += gm_WalkEntityChain(t->id);
	tot[0] = (int) ((float) total * *(float*) 0x662910);
	tot[1] = (int) ((float) total * *(float*) 0x664150);
	tot[2] = (int) ((float) total * *(float*) 0x6628ac);
	if (total >= thr[2]) {
		nv = 2;
	} else if (total >= thr[1]) {
		nv = 1;
	} else if (total >= thr[0]) {
		nv = 0;
	} else {
		return 0;
	}
	if (nv >= n) {
		nv = n;
	}
	*(int*) (a3 + 8) = tot[nv];
	*(int*) (a2 + 8) = thr[nv];
	*(int*) (a3 + 0xc) = t->x4;
	*(int*) (a3 + 0x10) = nv;
	*(int*) (a2 + 0x10) = 2;
	return 1;
}
