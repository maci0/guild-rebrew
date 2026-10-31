/* entity record, 0x21c stride, table g_7f4ca0 (768 entries) */
typedef struct Ent {
	unsigned short id;      /* +0x00 */
	char pad2[2];           /* +0x02 */
	int field4;             /* +0x04 */
	char pad8[0x184];       /* +0x08 .. +0x187 */
	unsigned char flag188;  /* +0x188 */
	char pad189[0x21c - 0x189];
} Ent;
/* SIZE 0x21c */

/* unit type record, 0x24d stride, table g_868050 */
typedef struct TypeRec {
	char pad[0x247];
	unsigned char maxcount;  /* +0x247 */
	char pad248[0x24d - 0x248];
} TypeRec;
/* SIZE 0x24d */

/* message handed to fcn_004c5530; the trailing object list is filled first and
   scanned before the message is posted, so it is modelled as part of the same
   stack object (the split between +0x60 and +0xf8 has no native evidence). */
typedef struct ObjMsg {
	char pad0[4];            /* +0x00 */
	unsigned char type;      /* +0x04: 0x40 */
	char pad5[3];            /* +0x05 */
	int value;               /* +0x08 */
	char pad0c[0x2a];        /* +0x0c */
	unsigned char flag;      /* +0x36: 1 */
	char pad37[1];           /* +0x37 */
	int ids[8];              /* +0x38 */
	int owner;               /* +0x58 */
	int owner2;              /* +0x5c */
	char pad60[0x98];        /* +0x60 */
	unsigned char* objs[16]; /* +0xf8 */
} ObjMsg;
/* SIZE 0x138 */

extern unsigned char* g_7746c4;
extern unsigned char* g_7746c8;
extern unsigned char* lpGebaeudePROT;
extern unsigned short g_774970;
extern Ent g_7f4ca0[];
extern int g_100f1dc;
extern int g_774654;
extern int g_14ce8e0;
extern int g_67d370;
extern int g_14abc98;
extern char s_6ab1b8[];

int __cdecl fcn_0055c050(void*);
void __cdecl io_FormatTextBuffer(char* buf, int id, ...);
int __cdecl fcn_00526120(char* buf, int zero);
int __cdecl fcn_00502cd0(int val, int a, int b, int c);
int __cdecl fcn_00502850(void);
int __cdecl fcn_005463a0(int a, int b, int idx, int c, int d);
int __cdecl he_fn_Handlung(void);
void* __cdecl fcn_00470820(short a, short b, char* name);
void __cdecl fcn_00471b60(int h);
void __cdecl d2_SetOverlayAnimation(int a, int b);
void __cdecl d2_SetForm(int h, int stage);
int __cdecl io_AppendText(int id, int a, void* p);
int __cdecl fcn_00472250(int h, int a, int b);
void __cdecl fcn_004c5530(void* p);
void __cdecl fcn_004c35f0(void);
int __cdecl fcn_005373e0(void* fn, int msg);
void __cdecl fcn_00471e30(int h);
void __cdecl fcn_005305a0(void);

/* ADDRESS: GOLDTL 0x005ad640 */
int __cdecl fcn_005ad640(void* a0, char* obj)
{
	int cnt;
	int ret;
	ObjMsg msg;
	char buf_a[0x100];
	char buf_b[0x400];
	unsigned char* rec;
	TypeRec* typerec;
	int item;
	int n;
	int i;
	int k;
	void* dlg;
	int r1;
	int r2;
	unsigned int* p;
	char* t;

	cnt = 0;
	ret = 0;
	if (obj == 0) {
		return 0;
	}
	if (*(unsigned short*) (obj + 0x27) == 0xffff) {
		return 0;
	}
	if (fcn_0055c050(obj) == 0) {
		io_FormatTextBuffer(buf_b, 0x1a92, *(unsigned short*) (obj + 0x27), obj);
		fcn_00526120(buf_b, 0);
		return 0;
	}
	rec = 0;
	if (g_7746c4) {
		rec = g_7746c4;
	} else if (g_7746c8) {
		rec = g_7746c8;
	}
	typerec = &((TypeRec*) lpGebaeudePROT)[g_7746c4[0]];
	n = 0;
	if (rec) {
		item = fcn_00502cd0(*((int*) (rec + 0x5d)), 1, 0, 0xca);
		while (item) {
			if (*((int*) (item + 0x2a)) != *((int*) (obj + 1))) {
				msg.objs[n] = (unsigned char*) item;
				n = n + 1;
			}
			item = fcn_00502850();
		}
	}
	item = fcn_005463a0(2, 2, g_774970, 0, 0x40);
	while (item) {
		for (k = 0; k < n; k++) {
			if (*((int*) (item + 0xac)) == *((int*) (msg.objs[k] + 0x2a))) {
				break;
			}
		}
		if (k < n) {
			item = he_fn_Handlung();
			continue;
		}
		cnt = cnt + 1;
		item = he_fn_Handlung();
	}
	if (n + cnt < (int) (typerec->maxcount * 2)) {
		dlg = fcn_00470820(0, 0, s_6ab1b8);
		fcn_00471b60((int) dlg);
		d2_SetOverlayAnimation(0, 0);
		d2_SetForm((int) dlg, 1);
		r1 = io_AppendText(0x19f7,
			(int) g_7f4ca0[*(unsigned short*) (obj + 0x27)].id, obj);
		r2 = fcn_00472250((int) dlg, 1, r1);
		r1 = fcn_00472250((int) dlg, 1, r1 + 1);
		g_100f1dc = -1;
		do {
			if (g_14ce8e0) {
				g_774654 = 1;
			}
			if (g_100f1dc != -1) {
				if (g_67d370 != r2) {
					if (g_67d370 == r1) {
						g_774654 = 1;
					}
				} else {
					for (i = 0; i < 8; i = i + 1) {
						msg.ids[i] = -1;
					}
					msg.type = 0x40;
					msg.flag = 1;
					msg.owner = *((int*) (obj + 1));
					msg.value = g_7f4ca0[g_774970].field4;
					msg.owner2 = *((int*) (g_7746c4 + 1));
					t = (char*) 0x7f4ca4;
					for (i = 0; i < 8 && t < (char*) 0x85a0a4; t = t + 0x21c) {
						if (*((unsigned char*) (t + 0x184))) {
							msg.ids[i] = *((int*) t);
							i = i + 1;
						}
					}
					if (i) {
						fcn_004c5530(&msg);
						ret = 1;
						fcn_004c35f0();
						g_774654 = 1;
					} else {
						fcn_00526120((char*) g_14abc98, 0);
						g_774654 = 1;
					}
				}
			}
		} while (fcn_005373e0(fcn_005ad640, 0x677c7));
		fcn_00471e30((int) dlg);
		fcn_005305a0();
		return ret;
	}
	io_FormatTextBuffer(buf_a, 0x19fa, n + cnt, g_7746c4);
	fcn_00526120(buf_a, 0);
	return 0;
}
