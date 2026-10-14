typedef struct
{
	int i[0x2f4 / 4];
} fcn_0046f9b0_Ent;
// SIZE 0x2f4

extern char* g_1015ea0;
extern int g_67d398;

char* __cdecl fcn_0047b620(int p, int i);
int __cdecl fcn_0046b520(char* s, int font);
int __cdecl fcn_00472050(int slot, int* w, int* h);
void __cdecl fcn_0064d530(char* dst, char* src, int n);

/* ADDRESS: GOLDTL 0x0046f9b0 */
void __cdecl fcn_0046f9b0(int idx, char* text)
{
	fcn_0046f9b0_Ent* e;
	int w;
	int h;
	int c;
	char* p0;
	char* p1;

	e = &((fcn_0046f9b0_Ent*)g_1015ea0)[idx];
	if (e->i[0x20 / 4] == 9) {
		c = e->i[0xc / 4];
		p0 = fcn_0047b620(c, 0);
		p1 = fcn_0047b620(c, 1);
		w = fcn_0046b520(text, g_67d398) + *(unsigned short*) (p1 + 2) + *(unsigned short*) (p0 + 2) + 4;
		fcn_0064d530((char*) e + 0x8c, text, 0x3f);
		((fcn_0046f9b0_Ent*)g_1015ea0)[idx].i[0x18 / 4] = w;
		return;
	}
	if (fcn_00472050(idx, &w, &h) == 0) {
		w = 0x18;
	}
	fcn_0064d530((char*) &((fcn_0046f9b0_Ent*)g_1015ea0)[idx] + 0x8c, text, 0x3f);
	if (((fcn_0046f9b0_Ent*)g_1015ea0)[idx].i[0x6c / 4] == 0) {
		((fcn_0046f9b0_Ent*)g_1015ea0)[idx].i[0x18 / 4] = fcn_0046b520(text, ((fcn_0046f9b0_Ent*)g_1015ea0)[idx].i[0x84 / 4]) + w + 6;
	} else {
		((fcn_0046f9b0_Ent*)g_1015ea0)[idx].i[0x18 / 4] = w;
	}
}
