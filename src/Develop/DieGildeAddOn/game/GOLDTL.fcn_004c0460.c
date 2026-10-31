typedef struct Slots {
	int v[0x2d];
	char* obj;
} Slots;
// SIZE 0xb8

extern unsigned char* lpGebaeudePROT;
extern char g_868060[];
extern unsigned char g_773d75;

int* __cdecl fcn_004be320(int, int);
char* __cdecl gm_ResolveParentEntity(char*);
char* __cdecl gm_SearchTable67(int);
int __cdecl fcn_0050cce0(char*, Slots*, int);
int __cdecl fcn_0050de80(char*, Slots*);
char* __cdecl fcn_00503d10(int);
char* __cdecl fcn_00502cd0(int, int, int, ...);
int __cdecl gm_GetMsgField(char*, char*);
int __cdecl gm_eval_SlotVoll(char*, int, int);
float __cdecl fcn_0050bb50(int, unsigned char);
int __cdecl fcn_0050d320(char*, char);
void __cdecl fcn_00517b10(char*, char*);
void __cdecl io_FormatTextBuffer(char*, int, ...);
void __cdecl fcn_00545d40(int, int, char*, int, int, char*);
int __cdecl fcn_004c51f0(int, int, int, int, char, int);

/* ADDRESS: GOLDTL 0x004c0460 */
void __cdecl fcn_004c0460(char* e, char who)
{
	int* p;
	char* q;
	char* par;
	int k;
	unsigned char* t;
	Slots a = {0};
	Slots b = {0};
	char name[0x80];
	char text[0x400];
	char* src;
	char* o;
	int n;
	int m;
	int val;
	int* d;

	if (*(int*) (e + 0x29) == 0) {
		return;
	}
	d = fcn_004be320(*(int*) (e + 0x29), *(int*) (e + 0x2d));
	par = gm_ResolveParentEntity(e);
	q = gm_SearchTable67(d[1]);
	if (q == 0) {
		return;
	}
	t = lpGebaeudePROT + *(unsigned char*) q * 0x24d;
	if (*t != 10 && *t != 0x1c) {
		if (fcn_0050cce0(q, &a, 0) == 0) {
			return;
		}
	}
	if (fcn_0050de80(e, &b) == 0) {
		return;
	}
	for (k = 3, p = d + 2; k != 0; k--, p += 2) {
		if (p[0] == 0) {
			continue;
		}
		val = 0;
		if (*t == 10) {
			src = fcn_00503d10(p[0]);
		} else if (*t == 0x1c) {
			src = fcn_00502cd0(*(int*) (q + 0x5d), 2, 0, 0x1dc, 6);
		} else {
			src = a.obj;
		}
		o = fcn_00502cd0(*(int*) (src + 0x14), 1, 0, p[0]);
		if (o == 0) {
			continue;
		}
		n = p[1];
		if (n >= gm_GetMsgField(src, o)) {
			n = gm_GetMsgField(src, o);
		}
		m = gm_eval_SlotVoll(b.obj, p[0], n);
		if (*(short*) (q + 0x27) != *(short*) par) {
			if (*t == 10) {
				val = (int) (fcn_0050bb50(*(unsigned short*) o, g_773d75) * 1.1f);
			} else if (*t == 0x1c) {
				val = (int) (fcn_0050bb50(*(unsigned short*) o, q[0x65]) * 1.1f);
			} else {
				val = (int) (fcn_0050bb50(*(unsigned short*) o, g_773d75) * *(float*) (q + 0x49));
			}
		}
		if (m > 0) {
			if (fcn_0050d320(par, who) < m * val) {
				fcn_00517b10(g_868060 + who * 756, name);
				io_FormatTextBuffer(text, 0x42f0, name, 0xc14, name, who);
				fcn_00545d40(*(int*) (par + 4), -1, text, 0, 0x5ef, "");
			}
			fcn_004c51f0(*(int*) (b.obj + 2), *(int*) (src + 2), p[0], m, who, val);
		}
	}
}
