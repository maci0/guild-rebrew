#pragma pack(2)
typedef struct Pos14 {
	int a;
	int b;
	int c;
	short d;
} Pos14;
#pragma pack()

typedef struct Place579 {
	char pad0[8];
	unsigned short idx;      /* 0x08 */
	char padA[2];
	int xc;                  /* 0x0c */
	int x10;                 /* 0x10 */
	char pad14[0x52 - 0x14];
	Pos14 pos52;             /* 0x52 */
	char pad60[0x70 - 0x60];
	int status;              /* 0x70 */
	char pad74[0x8c - 0x74];
	int x8c;                 /* 0x8c */
	char pad90[0xac - 0x90];
	float add;               /* 0xac */
	int xb0;                 /* 0xb0 */
	unsigned char xb4;       /* 0xb4 */
	char padb5[0xb8 - 0xb5];
	int xb8;                 /* 0xb8 */
	Pos14 posBC;             /* 0xbc */
} Place579;

extern Pos14 g_7f4c00;
extern char g_7f4ca0[];
extern float g_696540[];
extern float g_696550[];

int __cdecl fcn_00500e20(int* pos);
void __cdecl fcn_00500bb0(Pos14* pos, int a, int b, int c);
char* __cdecl gm_LookupEntityRecordById(int id);
void __cdecl fcn_00529160(int a, int b, int id, int d);
void* __cdecl gm_StartFilteredEntitySearch(int a, int b, int c);
char* __cdecl gv_GetSlotEntry(int a, int b, int c);
int __cdecl fcn_00500d20(Pos14* a, Pos14* b);
int __cdecl _ftol(void);
int __cdecl fcn_004f2d30(char* p, int a, int b, int c);
char* __cdecl fcn_0050dc90(char* p);
void __cdecl io_FormatTextBuffer(char* buf, int a, int b, int c, char* p);
void __cdecl he_MessageBoxQuickjump(int a, int b, char* text, int c, int d, int e,
	int f, int g, char* fmt);
void __cdecl fcn_00546190(char* a0);

/* Placement step for the transport/warehouse action: validates the current
   map cell, advances the hauled amount along the way, places the icon and
   reports the action text. */
/* ADDRESS: GOLDTL 0x00579de0 */
void __cdecl fcn_00579de0(char* a0)
{
	Place579* p;
	char text[1024];
	char* s;
	char* q;
	char* fig;
	char* rec;
	int win;
	int value;
	int v;
	int row;
	float f;

	win = fcn_00500e20((int*) &g_7f4c00);
	value = *(int*) &g_7f4c00.b & 0xffff;
	if (((float) value >= g_696550[win] || (float) value < g_696540[win])
		&& ((Place579*) a0)->status != -1
		&& ((Place579*) a0)->status != -2) {
		((Place579*) a0)->posBC = g_7f4c00;
		fcn_00500bb0(&((Place579*) a0)->pos52, 0, 5, 0);
		return;
	}
	p = (Place579*) a0;
	if (p->idx == 0xffff || p->xc == -1) {
		goto end;
	}
	s = gm_LookupEntityRecordById(p->x8c);
	if (s) {
		fcn_00529160(0, 0, *(unsigned short*) s, (int) p);
	} else {
		p->status = -1;
	}
	rec = (char*) gm_StartFilteredEntitySearch(1, 1, p->x10);
	if (!rec) {
		p->status = -1;
	}
	q = gv_GetSlotEntry(*(int*) (rec + 0x65), p->xb0, p->xb4);
	if (!q) {
		p->status = -1;
	}
	if (p->status == 0) {
		v = fcn_00500d20(&p->posBC, &g_7f4c00);
		f = (float) ((4 - *(int*) q) * v) * *(float*) 0x662a3c;
		if ((s[0x165] == 0x1b || s[0x165] == 0x1c)
			&& (*(unsigned char*) (s + 0x1b4) & 1)) {
			f *= *(float*) 0x6628bc;
		}
		p->add += f;
		p->pos52 = g_7f4c00;
		fcn_00500bb0(&p->pos52, 0, 5, 0);
		v = p->xb8 - v;
		p->xb8 = v;
		p->posBC = g_7f4c00;
		if (v <= 0) {
			p->status = -1;
		}
		if ((int) (*(unsigned char*) (q + 0xc)) + _ftol() >= 0xff) {
			p->status = -1;
		}
	}
	if (p->status < -2) {
		return;
	}
	if (p->status >= 0) {
		return;
	}
	v = _ftol();
	if (q != 0 && v >= 1) {
		fcn_004f2d30(rec, p->xb0, p->xb4, v);
		if (!s) {
			fcn_00546190(a0);
			return;
		}
		fig = fcn_0050dc90(rec);
		io_FormatTextBuffer(text, 0x4126, 0x411e, *(unsigned short*) s, rec);
		row = (int) (*(unsigned short*) (a0 + 8)) * 0x21c;
		if ((g_7f4ca0[row + 2] == 6 || g_7f4ca0[row + 2] == 7)
			&& (!fig || !(*(unsigned char*) (fig + 0x1b4) & 1))) {
			he_MessageBoxQuickjump(*(int*) (g_7f4ca0 + row + 4), -1, text, 0, 0x5ec,
				*(int*) (rec + 1), -1, 0, (char*) 0x6a7f70);
		}
	}
	if (s) {
		fcn_00529160(0, 0, *(unsigned short*) s, 0);
	}
end:
	fcn_00546190(a0);
}
