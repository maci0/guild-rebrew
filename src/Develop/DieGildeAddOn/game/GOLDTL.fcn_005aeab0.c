/* Menu action: the recruitable thief (diebesgilde) offer.  Looks the selected
   record up, finds the matching action record of type 0x3e (loesegeld) or
   0x3d, fills the payment packet and runs the modal button loop until the
   player answers. */

extern char* g_aed32c;
extern int g_14aba40;
extern int g_14aba48;
extern int g_14ce8e0;
extern int g_774654;
extern int g_67d370;
extern int g_100f1dc;
extern unsigned short g_774970;
extern double g_662908;
extern double g_6640f8;
extern double g_665fc0;
extern char g_6ab2e0[];

int __cdecl fcn_00525fb0(char*);
char* __cdecl gm_LookupEntityRecordById(int);
int __cdecl fcn_00526120(char*, int);
char* __cdecl fcn_005463a0(int, int, int);
char* __cdecl he_fn_Handlung(void);
void __cdecl io_FormatTextBuffer(char*, int, ...);
int __cdecl gm_WalkEntityChain(unsigned short);
float __cdecl gm_RandomFloat01(void);
int __cdecl fcn_00470820(int, int, char*);
void __cdecl d2_SetOverlayAnimation(int, int);
void __cdecl fcn_00471b60(int);
void __cdecl d2_SetForm(int, int);
int __cdecl fcn_00472250(int, int, int);
int __cdecl io_AppendText(int, ...);
void __cdecl fcn_004c5530(char*);
void __cdecl fcn_004c4510(char*, int);
void __cdecl fcn_004c4570(int, int, int, int*);
void __cdecl fcn_004c5360(void);
void __cdecl fcn_004c6b20(int, int, int);
int __cdecl fcn_005373e0(void*, int);
void __cdecl fcn_00532ef0(void);
int __cdecl fcn_00471e30(int);

/* ADDRESS: GOLDTL 0x005aeab0 */
void __cdecl fcn_005aeab0(char* rec)
{
	char text[0x400];
	char line[0x200];
	char note[0x200];
	char pkt[0x68];
	char* ent;
	char* act;
	char* ctx;
	unsigned char cls;
	int v;
	int cnt;
	int b1;
	int b2;
	int b3;
	int flags;
	float weight;
	double prob;

	if (fcn_00525fb0(rec) != 0) {
		return;
	}
	ent = gm_LookupEntityRecordById(*(int*) (rec + 0x65));
	if (ent == 0) {
		fcn_00526120((char*) g_14aba40, 0);
		return;
	}
	act = fcn_005463a0(1, 0, 0x3e);
	while (act != 0) {
		if (*(int*) (act + 0xac) == *(int*) (ent + 4)) {
			io_FormatTextBuffer(text, 0x19c9, *(unsigned short*) ent);
			fcn_00526120(text, 0);
			return;
		}
		act = he_fn_Handlung();
	}
	act = fcn_005463a0(1, 0, 0x3d);
	while (act != 0) {
		if (*(int*) (act + 0xac) == *(int*) (ent + 4)) {
			break;
		}
		act = he_fn_Handlung();
	}
	if (act == 0) {
		fcn_00526120((char*) g_14aba48, 0);
		return;
	}
	cls = *(unsigned char*) (ent + 0x1b1);
	if (cls >= 4) {
		weight = 0.1f;
	} else if (cls == 3) {
		weight = 0.06f;
	} else if (cls == 2) {
		weight = 0.04f;
	} else if (cls == 1) {
		weight = 0.02f;
	} else {
		weight = 0.0f;
	}
	cnt = 0;
	prob = (double) cnt;
	v = gm_WalkEntityChain(*(unsigned short*) ent);
	if (((double) gm_RandomFloat01() * g_662908 + g_6640f8) * g_665fc0
	    < prob) {
		prob = (double) gm_RandomFloat01() * g_662908 + g_6640f8;
	}
	cnt = (int) prob;
	cnt = (int) ((double) cnt * (double) weight);
	ctx = (char*) fcn_00470820(0, 0, g_6ab2e0);
	d2_SetOverlayAnimation(0, 0);
	fcn_00471b60((int) ctx);
	d2_SetForm((int) ctx, 1);
	*(unsigned char*) (pkt + 4) = 0x3e;
	*(int*) (pkt + 8) = *(int*) (ent + 4);
	*(int*) (pkt + 0xc) = *(int*) (rec + 1);
	*(unsigned char*) (pkt + 0x3a) = 9;
	*(int*) (pkt + 0x58) = *(int*) (ent + 4);
	*(int*) (pkt + 0x60) = *(int*) (g_774970 * 0x21c + 0x7f4ca4);
	*(int*) (pkt + 0x64) = cnt;
	b1 = io_AppendText(0x19c4, *(unsigned short*) ent, (int) (act + 0xb4),
	    2, cnt, *(unsigned short*) ent, *(unsigned short*) ent);
	b1 = fcn_00472250((int) ctx, 1, b1);
	b2 = fcn_00472250((int) ctx, 1, b1 + 1);
	b3 = fcn_00472250((int) ctx, 1, b1 + 2);
	g_100f1dc = -1;
	for (;;) {
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		}
		if (g_100f1dc != -1) {
			if (g_67d370 == b1) {
				fcn_004c5530(pkt);
				io_FormatTextBuffer(note, 0x19c5, cnt, *(unsigned short*) ent);
				fcn_00526120(note, 0);
				g_774654 = 1;
			} else if (g_67d370 == b2) {
				flags = -1;
				fcn_004c4510(rec, *(int*) (rec + 1));
				fcn_004c4570(4, 1, (int) (rec - g_aed32c) + 0x65,
				    &flags);
				fcn_004c5360();
				fcn_004c6b20(*(int*) (ent + 4),
				    -(int) *(unsigned char*) (ent + 0x1b1), 0);
				io_FormatTextBuffer(line, 0x19c6, *(unsigned short*) ent);
				fcn_00526120(line, 0);
				g_774654 = 1;
			} else if (g_67d370 == b3) {
				io_FormatTextBuffer(text, 0x19c7, *(unsigned short*) ent);
				fcn_00526120(text, 0);
				g_774654 = 1;
			}
		}
		if (fcn_005373e0((void*) 0x5aeab0, 0x677c7) == 0) {
			fcn_00532ef0();
			fcn_00471e30((int) ctx);
			return;
		}
	}
}
